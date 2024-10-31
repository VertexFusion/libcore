////////////////////////////////////////////////////////////////////////////////////////////////////
// Name:        DiffDisance.cpp
// Library:     Jameo Core Library
// Purpose:     Implementation of dif algorithm
//
// Author:      Uwe Runtemund (2013-today)
// Modified by:
// Created:     17.12.2013
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


#include "Precompiled.hpp"

using namespace jm;

DiffDistance::DiffDistance()
{
   mRows = 0;
   mCols = 0;
   mDiagonal = nullptr;
   mDistance = 0;
   calc = 0;
   u = new std::vector<Object*>();
   v = new std::vector<Object*>();
}

DiffDistance::~DiffDistance()
{
   clear();
   delete u;
   delete v;
}

void DiffDistance::clear()
{
   if(mDiagonal != nullptr)
   {
      delete mDiagonal;
      mDiagonal = nullptr;
   }
   u->clear();
   v->clear();
   mDistance = 0;
   calc = 0;
}

void DiffDistance::addU(Object* obj)
{
   u->push_back(obj);
}

void DiffDistance::addV(Object* obj)
{
   v->push_back(obj);
}

DiffBacktrace* DiffDistance::solve()
{
   mRows = u->size();
   mCols = v->size();


   //Speed-Up: Durch Betrachtung der Diagonalen....
   //http://www.csse.monash.edu.au/~lloyd/tildeStrings/Alignment/92.IPL.html
   //

   //Berechnung nach:
   // http://de.wikipedia.org/wiki/Levenshtein-Distanz
   // http://en.wikipedia.org/wiki/Levenshtein_distance


   // which is the diagonal containing the bottom R.H. element?
   int64 lba = v->size() - u->size();

   DiffDiag* main = new DiffDiag(this, u, v, 0);


   if(lba >= 0)
   {
      mDiagonal = main;
      for(int64 i = 0; i < lba; i++)
         mDiagonal = mDiagonal->above();
   }
   else
   {
      mDiagonal = main->below();
      for(int64 i = 0; i < ~lba; i++)
         mDiagonal = mDiagonal->above();
   }

   mDistance = mDiagonal->entry(std::min(mRows, mCols));

   int64 sz = mRows * mCols;
   std::cout << Tr("Distance %1").arg(mDistance) << std::endl;
   std::cout << Tr("Calculated %1/%2: %3%")
             .arg(calc)
             .arg(sz)
             .arg(calc * 100.0 / double(sz))
             << std::endl;

   int i = (int) std::min(mRows, mCols);
   return DiffBacktrace::backtrace(mDiagonal, i);
}


int64 DiffDistance::distance() const
{
   return mDistance;
}


