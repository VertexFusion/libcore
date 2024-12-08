////////////////////////////////////////////////////////////////////////////////////////////////////
// Name:        Diff.cpp
// Library:     Jameo Core Library
// Purpose:     Implementation of dif algorithm
//
// Author:      Uwe Runtemund (2014-today)
// Modified by:
// Created:     23.03.2014
//
// Copyright:   (c) 2014 Jameo Software, Germany. https://jameo.de
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

DiffDiag::DiffDiag(DiffDistance* dist, std::vector<Object*>* u, std::vector<Object*>* v,
                   int64 offset)
{
   mU = u;
   mV = v;
   mBelow = nullptr;
   mAbove = nullptr;
   this->mOffset = offset;
   mElements = new std::vector<int64>();
   mElements->push_back(std::abs(offset));
   this->mDistance = dist;
}

DiffDiag::~DiffDiag()
{
   mElements->clear();
   delete mElements;
}


DiffDiag* DiffDiag::above()
{
   if(mAbove == nullptr)
   {
      mAbove = new DiffDiag(mDistance, mU, mV, mOffset >= 0 ? mOffset + 1 : mOffset - 1);
      mAbove->mBelow = this;
   }
   return mAbove;
}

DiffDiag* DiffDiag::below()
{
   if(mBelow == nullptr)
   {
      // lower half has a, b switched, so see themselves
      // as the upper half of the transpose
      mBelow = new DiffDiag(mDistance, mV, mU, -1);
      mBelow->mBelow = this;
      //		mBelow = new DiffDiag(dist, u, v, offset - 1 );
   }
   return mBelow;
}

int64 DiffDiag::upperEntry(int64 i)
{
   return above()->entry(i - 1);
}

int64 DiffDiag::leftEntry(int64 i)
{
   // If diagonals are "mBelow", then diagonal 1 is shorter

   return below()->entry((mOffset == 0) ? i - 1 : i);
   //	return GetBelow()->GetEntry( i-1 );
}

int64 DiffDiag::entry(int64 j)
{
   if(j < int64(mElements->size()))return mElements->at(j);

   int64 x = mElements->at(mElements->size() - 1);

   while(int64(mElements->size()) <= j)
   {
      int64 lu = x;
      int64 i = mElements->size();

      //  \ \  \
      //   \ \  \
      //    \lu  u
      //     \  \
      //      l  x
      Object* o1 = objectU(i);
      Object* o2 = objectV(i);

      if(o1->equals(o2))
      {
         x = lu;
      }
      else
      {
         // see L. Allison, Lazy Dynamic-Programming can be Eager
         //     Inf. Proc. Letters 43(4) pp207-212, Sept' 1992
         // computes min3 (w, nw, n)
         // but does not always evaluate n
         // this makes it O(|a|*D(a,b))

         int64 l = leftEntry(i);
         if(l < lu)
         {
            x = l + 1;
         }
         else
         {
            int64 u = upperEntry(i);
            x = (lu < u ? lu : u) + 1;
         }
      }

      mDistance->calc++;
      mElements->push_back(x);
   }
   return x;
}

Object* DiffDiag::objectU(int64 i)
{
   return mU->at(i - 1);
}

Object* DiffDiag::objectV(int64 i)
{
   return mV->at(std::abs(mOffset) + i - 1);
}

int64 DiffDiag::offset()
{
   return mOffset;
}
