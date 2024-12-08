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
}

Nurbs::Nurbs(uint32 degree,
             Vertex3* controlpoints,
             uint32 controlCount,
             double* knots,
             uint32 knotCount,
             double* weights,
             uint32 weightcount): Object()
{
   mDegree = degree;
   if(mDegree < 1)throw Exception(Tr("Degree of NURBS must be greater 0."));

   mControlCount = controlCount;
   mControlpoints = new Vertex3[mControlCount];
   for(uint32 a = 0; a < mControlCount; a++)mControlpoints[a] = controlpoints[a];

   mKnotCount = knotCount;
   mKnots = new double[mKnotCount];
   for(uint32 a = 0; a < mKnotCount; a++)mKnots[a] = knots[a];

   mWeightCount = weightcount;
   mWeights = new double[mWeightCount];
   for(uint32 a = 0; a < mWeightCount; a++)mWeights[a] = weights[a];
}

Nurbs::~Nurbs()
{
   if(mControlpoints != nullptr)delete[] mControlpoints;
   if(mKnots != nullptr)delete[] mKnots;
   if(mWeights != nullptr)delete[] mWeights;
}

double Nurbs::N(uint32 i, uint32 k, double t)
{

   if(k == 0)
   {
      if(mKnots[i] <= t && t < mKnots[i + 1]) return 1.0;
      return 0.0;
   }

   double a = t - mKnots[i];
   double b = mKnots[i + k] - mKnots[i];
   double c = mKnots[i + k + 1] - t;
   double d = mKnots[i + k + 1] - mKnots[i + 1];

   double N1 = 0;
   double N2 = 0;

   if(!isEqual(b, 0.0))
   {
      N1 = N(i, k - 1, t) * a / b;
   }

   if(!isEqual(d, 0.0))
   {
      N2 = N(i + 1, k - 1, t) * c / d;
   }
   return N1 + N2;
}

double Nurbs::R(uint32 i, uint32 k, double t)
{
   double a = mWeights[i] * N(i, k, t);
   double b = 0;

   for(uint32 j = 0; j < mControlCount; j++)b += mWeights[j] * N(j, k, t);

   return a / b;
}

Vertex3 Nurbs::point(double t)
{
   Vertex3 P;

   for(uint32 i = 0; i < mControlCount; i++)P += mControlpoints[i] * R(i, mDegree, t);

   return P;
}

double Nurbs::start()
{
   return 0;
}

double Nurbs::end()
{
   if(mKnotCount < 1)return 0;
   double m = mControlCount - mDegree + 2;
   if(m < mKnots[mKnotCount - 1])m = mKnots[mKnotCount - 1];
   return m;
}

uint32 Nurbs::controlPointCount()
{
   return mControlCount;
}

uint32 Nurbs::knotCount()const
{
   return mKnotCount;
}

double Nurbs::knot(uint32 index)const
{
   return mKnots[index];
}
