////////////////////////////////////////////////////////////////////////////////////////////////////
// Name:        NURBS.cpp
// Library:     Jameo Core Library
// Purpose:     NURBS
//
// Author:      Uwe Runtemund (2013-today)
// Modified by:
// Created:     06.01.2013
//
// Copyright:   (c) 2013 Jameo Software, Germany. https://jameo.de
//
// Licence:     The MIT License
//              Permission is hereby granted, free of charge, to any person obtaining a copy of this
//              software and associated documentation files (the "Software"), to deal in the
//              Software without restriction, including without limitation the rights to use, copy,
//              modify, merge, publish, distribute, sublicense, and/or sell copies of the Software,
//              and to permit persons to whom the Software is furnished to do so, subject to the
//              following conditions:
//
//              The above copyright notice and this permission notice shall be included in all
//              copies or substantial portions of the Software.
//
//              THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
//              INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
//              PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
//              HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF
//              CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE
//              OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
//
////////////////////////////////////////////////////////////////////////////////////////////////////

#include "PrecompiledCore.hpp"

using namespace jm;

Nurbs::Nurbs(): Object()
{
   mDegree = 1;
   mControlpoints = nullptr;
   mControlCount = 0;
   mKnots = nullptr;
   mKnotCount = 0;
   mWeights = nullptr;
   mWeightCount = 0;
   mClamped=false;
   mClosed=false;
}

Nurbs::Nurbs(uint32 degree,
             Vertex3* controlpoints,
             size_t controlCount,
             double* knots,
             size_t knotCount,
             double* weights,
             size_t weightCount): Object()
{
   mDegree = degree;
   if(mDegree < 1)throw Exception(Tr("Degree of NURBS must be greater 0."));

   mControlCount = controlCount;
   mControlpoints = new Vertex3[mControlCount];
   for(size_t a = 0; a < mControlCount; a++)mControlpoints[a] = controlpoints[a];

   mKnotCount = knotCount;
   mKnots = new double[mKnotCount];
   for(size_t a = 0; a < mKnotCount; a++)mKnots[a] = knots[a];

   mWeightCount = weightCount;
   mWeights = new double[mWeightCount];
   for(size_t a = 0; a < mWeightCount; a++)mWeights[a] = weights[a];

   mClamped=calcClamped();
   mClosed=calcClosed();
}

Nurbs::~Nurbs()
{
   if(mControlpoints != nullptr)delete[] mControlpoints;
   if(mKnots != nullptr)delete[] mKnots;
   if(mWeights != nullptr)delete[] mWeights;
}

double Nurbs::N(size_t i, uint32 k, double t)
{

   if(k == 0)
   {
      if((jm::isLessEqual(mKnots[i%mKnotCount] , t) && jm::isLess(t , mKnots[(i + 1)%mKnotCount]))
         || (jm::isEqual(t,mKnots[mKnotCount-1]) && jm::isEqual(t, mKnots[(i + 1)%mKnotCount]))) return 1.0;
      return 0.0;
   }

   double a = t - mKnots[i%mKnotCount];
   double b = mKnots[(i + k)%mKnotCount] - mKnots[i%mKnotCount];
   double c = mKnots[(i + k + 1)%mKnotCount] - t;
   double d = mKnots[(i + k + 1)%mKnotCount] - mKnots[(i + 1)%mKnotCount];

   double N1 = 0.0;
   double N2 = 0.0;

   if(!jm::isEqual(b, 0.0))
   {
      N1 = N(i, k - 1, t) * a / b;
   }

   if(!jm::isEqual(d, 0.0))
   {
      N2 = N(i + 1, k - 1, t) * c / d;
   }
   return N1 + N2;
}

double Nurbs::R(size_t i, uint32 k, double t)
{
   double a = mWeights[i] * N(i, k, t);
   double b = 0.0;

   for(size_t j = 0; j < mControlCount; j++)b += mWeights[j] * N(j, k, t);

   if (jm::isEqual(b, 0.0)) return 0.0;

   return a / b;
}

Vertex3 Nurbs::point(double t)
{
   Vertex3 p;
   double denominator = 0.0;

   size_t endIdx = mControlCount;

   for (size_t i = 0; i < endIdx; ++i)
   {
      double Ni = N(i, mDegree, t);
      double weightedNi = mWeights[i] * Ni;

      p += mControlpoints[i] * weightedNi;
      denominator += weightedNi;
   }

   if (jm::isEqual(denominator, 0.0))
   {
      return Vertex3();
   }

   return p / denominator;
}

bool Nurbs::isClamped() const
{
   return mClamped;
}

bool Nurbs::isClosed() const
{
   return mClosed;
}

bool Nurbs::calcClamped() const
{
    if (mKnotCount == 0) return false;

    // Check start clamping: first degree+1 knots equal?
    double startKnot = mKnots[0];
    bool startClamped = true;
    for (uint32 i = 1; i <= mDegree; ++i)
    {
       if(jm::isNotEqual(mKnots[i] , startKnot))
       {
            startClamped = false;
            break;
       }
    }

    // Check end clamping: last degree+1 knots equal?
    double endKnot = mKnots[mKnotCount - 1];
    bool endClamped = true;
    for (size_t i = mKnotCount - mDegree - 1; i < mKnotCount - 1; ++i)
    {
        if (jm::isNotEqual(mKnots[i] , endKnot))
        {
            endClamped = false;
            break;
        }
    }

    return startClamped && endClamped;
}

bool Nurbs::calcClosed() const
{
   if (mControlCount < 2) return false;

   // 1. Geometric closure check
   bool geomClosed = (mControlpoints[0]==mControlpoints[mControlCount-1]);

   // 2. Knot vector size heuristic for periodicity
   size_t expectedKnots = mControlCount + mDegree + 1;
   bool paramClosed = mKnotCount< expectedKnots;

   return geomClosed || paramClosed;
}

double Nurbs::start() const
{
   if (mKnotCount == 0) return 0.0;
   if (mDegree >= mKnotCount - 1) return mKnots[0];

   return mKnots[mDegree];
}

double Nurbs::end() const
{
   if (mKnotCount == 0)return 0;
   if (mDegree >= mKnotCount - 1) return mKnots[mKnotCount-1];

   return mKnots[mKnotCount - mDegree - 1];
}

size_t Nurbs::startIndex() const
{
   return mDegree;
}

size_t Nurbs::endIndex() const
{
   return mKnotCount - mDegree - 1;
}

size_t Nurbs::controlPointCount()
{
   return mControlCount;
}

size_t Nurbs::knotCount()const
{
   return mKnotCount;
}

double Nurbs::knot(size_t index)const
{
   return mKnots[index];
}

uint32 Nurbs::degree() const
{
   return mDegree;
}

jm::Vertex3 Nurbs::controlPoint(size_t index) const
{
   return mControlpoints[index];
}

double Nurbs::weight(size_t index) const
{
   return mWeights[index];
}
