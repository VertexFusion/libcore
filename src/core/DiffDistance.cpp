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


#include "Precompiled.h"

using namespace jm;

DiffDistance::DiffDistance()
{
   m = 0;
   n = 0;
   diagonal = NULL;
   distance = 0;
   calc = 0;
   u = new std::vector<Object*>();
   v = new std::vector<Object*>();
}

DiffDistance::~DiffDistance()
{
   Clear();
   delete u;
   delete v;
}

void DiffDistance::Clear()
{
   if(diagonal != NULL)
   {
      delete diagonal;
      diagonal = NULL;
   }
   u->clear();
   v->clear();
   distance = 0;
   calc = 0;
}

void DiffDistance::AddU(Object* obj)
{
   u->push_back(obj);
}

void DiffDistance::AddV(Object* obj)
{
   v->push_back(obj);
}

DiffBacktrace* DiffDistance::Solve()
{
   m = u->size();
   n = v->size();


   //Speed-Up: Durch Betrachtung der Diagonalen....
   //http://www.csse.monash.edu.au/~lloyd/tildeStrings/Alignment/92.IPL.html
   //

   //Berechnung nach:
   // http://de.wikipedia.org/wiki/Levenshtein-Distanz
   // http://en.wikipedia.org/wiki/Levenshtein_distance


   // which is the diagonal containing the bottom R.H. element?
   Integer lba = v->size() - u->size();

   DiffDiag* main = new DiffDiag(this, u, v, 0);


   if(lba >= 0)
   {
      diagonal = main;
      for(Integer i = 0; i < lba; i++)
         diagonal = diagonal->GetAbove();
   }
   else
   {
      diagonal = main->GetBelow();
      for(Integer i = 0; i < ~lba; i++)
         diagonal = diagonal->GetAbove();
   }

   distance = diagonal->GetEntry(Min(m, n));

   Integer sz = m * n;
   std::cout << Tr("Distance %1").arg(distance) << std::endl;
   std::cout << Tr("Calculated %1/%2: %3%")
      .arg(calc)
      .arg(sz)
      .arg(calc * 100.0 / sz.Dbl())
   << std::endl;

   int i = (int) std::min(m, n);
   return DiffBacktrace::Backtrace(diagonal, i);
}


Integer DiffDistance::GetDistance() const
{
   return distance;
}


