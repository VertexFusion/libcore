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


#include "Precompiled.h"

using namespace jm;

DiffDiag::DiffDiag(DiffDistance* dist, std::vector<Object*>* u, std::vector<Object*>* v, Integer offset)
{
   mU = u;
   mV = v;
   below = NULL;
   above = NULL;
   this->offset = offset;
   elements = new std::vector<Integer>();
   elements->push_back(std::abs(offset));
   this->dist = dist;
}

DiffDiag::~DiffDiag()
{
   elements->clear();
   delete elements;
}


DiffDiag* DiffDiag::GetAbove()
{
   if(above == NULL)
   {
      above = new DiffDiag(dist, mU, mV, offset >= 0 ? offset + 1 : offset - 1);
      above->below = this;
   }
   return above;
}

DiffDiag* DiffDiag::GetBelow()
{
   if(below == NULL)
   {
      // lower half has a, b switched, so see themselves
      // as the upper half of the transpose
      below = new DiffDiag(dist, mV, mU, -1);
      below->below = this;
      //		below = new DiffDiag(dist, u, v, offset - 1 );
   }
   return below;
}

Integer DiffDiag::GetUpperEntry(Integer i)
{
   return GetAbove()->GetEntry(i - 1);
}

Integer DiffDiag::GetLeftEntry(Integer i)
{
   // If diagonals are "below", then diagonal 1 is shorter

   return GetBelow()->GetEntry((offset == 0) ? i - 1 : i);
   //	return GetBelow()->GetEntry( i-1 );
}

Integer DiffDiag::GetEntry(Integer j)
{
   if(j < elements->size())return elements->at(j);

   Integer x = elements->at(elements->size() - 1);

   while(elements->size() <= j)
   {
      Integer lu = x;
      Integer i = elements->size();

      //  \ \  \
      //   \ \  \
      //    \lu  u
      //     \  \
      //      l  x
      Object* o1 = GetObjU(i);
      Object* o2 = GetObjV(i);

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

         Integer l = GetLeftEntry(i);
         if(l < lu)
         {
            x = l + 1;
         }
         else
         {
            Integer u = GetUpperEntry(i);
            x = (lu < u ? lu : u) + 1;
         }
      }

      dist->calc++;
      elements->push_back(x);
   }
   return x;
}

Object* DiffDiag::GetObjU(Integer i)
{
   return mU->at(i - 1);
}

Object* DiffDiag::GetObjV(Integer i)
{
   return mV->at(std::abs(offset) + i - 1);
}

Integer DiffDiag::GetOffset()
{
   return offset;
}
