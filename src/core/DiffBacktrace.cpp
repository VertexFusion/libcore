////////////////////////////////////////////////////////////////////////////////////////////////////
// Name:        DiffBacktrace.cpp
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

DiffBacktrace::DiffBacktrace()
{
   size = 0;
   operation = kDiffStart;
   obj1 = NULL;
   obj2 = NULL;
   prev = NULL;
   next = NULL;
}

DiffBacktrace::DiffBacktrace(const DiffBacktrace& another)
{
   size = another.size;
   operation = another.operation;
   obj1 = another.obj1;
   obj2 = another.obj2;
   prev = another.prev;
   next = another.next;
}

DiffBacktrace::~DiffBacktrace()
{

   if(next != NULL)
   {
      delete next;
      next = NULL;
   }

}


void DiffBacktrace::Print()
{
   DiffBacktrace* step = this;

   DiffInfo di;

   do
   {
      di.Print(step->operation, step->obj1, step->obj2);
      step = step->next;
   }
   while(step != NULL);
}

DiffBacktrace* DiffBacktrace::Backtrace(DiffDiag* diag, uint32 i)
{
   bool loop = true;

   std::vector<DiffBacktrace*> stack;

   while(loop)
   {

      DiffOperation op;

      if(i == 0)
      {
         if(diag->GetOffset() == 0)
         {
            op = kDiffStart;
         }
         else if(diag->GetOffset() > 0)
         {
            op = kDiffAdd;
         }
         else
         {
            op = kDiffDelete;
         }
      }
      else if(diag->GetObjU(i)->equals(diag->GetObjV(i)))
      {
         op = kDiffEqual;
      }
      else
      {
         Integer me = diag->GetEntry(i);
         Integer w = diag->GetLeftEntry(i);
         Integer nw = diag->GetEntry(i - 1);

         if(me == 1 + w)
         {
            if(diag->GetOffset() >= 0)
            {
               op = kDiffAdd;
            }
            else
            {
               op = kDiffDelete;
            }
         }
         else if(me == 1 + nw)
         {
            op = kDiffModified;
         }
         else
         {
            if(diag->GetOffset() >= 0)
            {
               op = kDiffDelete;
            }
            else
            {
               op = kDiffAdd;
            }
         }
      }

      DiffBacktrace* ret = new DiffBacktrace();

      ret->operation = op;
      switch(op)
      {
         case kDiffEqual:
            //			ret->last=Backtrace(diag,i-1);
            i--;
            break;

         case kDiffModified:
            //			ret->last=Backtrace(diag,i-1);
            ret->obj1 = diag->GetObjU(i);
            ret->obj2 = diag->GetObjV(i);
            i--;
            break;

         case kDiffAdd:
            if(diag->GetOffset() == 0)
            {
               //				ret->last=Backtrace(diag->GetBelow(),i-1);
               ret->obj1 = diag->GetObjV(i);
               diag = diag->GetBelow();
               i--;
            }
            else if(diag->GetOffset() >= 0)
            {
               //				ret->last=Backtrace(diag->GetBelow(),i);
               ret->obj1 = diag->GetObjV(i);
               diag = diag->GetBelow();
            }
            else
            {
               //				ret->last=Backtrace(diag->GetAbove(),i-1);
               ret->obj1 = diag->GetObjV(i);
               diag = diag->GetAbove();
               i--;
            }
            break;

         case kDiffDelete:
            if(diag->GetOffset() == 0)
            {
               //				ret->last =Backtrace(diag->GetAbove(),i-1);
               ret->obj1 = diag->GetObjV(i);
               diag = diag->GetAbove();
               i--;
            }
            else if(diag->GetOffset() >= 0)
            {
               //				ret->last =Backtrace(diag->GetAbove(),i-1);
               ret->obj1 = diag->GetObjV(i);
               diag = diag->GetAbove();
               i--;
            }
            else
            {
               //				ret->last =Backtrace(diag->GetBelow(),i);
               ret->obj1 = diag->GetObjV(i);
               diag = diag->GetBelow();
            }
            break;

         case kDiffStart:
            loop = false;
            break;

      }

      stack.push_back(ret);
   }

   DiffBacktrace* top = stack.back();
   stack.pop_back();

   DiffBacktrace* step = top;
   while(stack.size() > 0)
   {
      step->next = stack.back();
      stack.pop_back();
      step->next->prev = step;
      step = step->next;
   }

   return top;
}


DiffOperation DiffBacktrace::GetOperation()
{
   return operation;
}



