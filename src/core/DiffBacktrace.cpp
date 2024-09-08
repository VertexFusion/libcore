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
   mSize = 0;
   mOperation = DiffOperation::kDiffStart;
   mObj1 = nullptr;
   mObj2 = nullptr;
   mPrev = nullptr;
   mNext = nullptr;
}

DiffBacktrace::DiffBacktrace(const DiffBacktrace& another)
{
   mSize = another.mSize;
   mOperation = another.mOperation;
   mObj1 = another.mObj1;
   mObj2 = another.mObj2;
   mPrev = another.mPrev;
   mNext = another.mNext;
}

DiffBacktrace::~DiffBacktrace()
{

   if(mNext != nullptr)
   {
      delete mNext;
      mNext = nullptr;
   }

}


void DiffBacktrace::print()
{
   DiffBacktrace* step = this;

   DiffInfo di;

   do
   {
      di.print(step->mOperation, step->mObj1, step->mObj2);
      step = step->mNext;
   }
   while(step != nullptr);
}

DiffBacktrace* DiffBacktrace::backtrace(DiffDiag* diag, int64 i)
{
   bool loop = true;

   std::vector<DiffBacktrace*> stack;

   while(loop)
   {

      DiffOperation op;

      if(i == 0)
      {
         if(diag->offset() == 0)
         {
            op = DiffOperation::kDiffStart;
         }
         else if(diag->offset() > 0)
         {
            op = DiffOperation::kDiffAdd;
         }
         else
         {
            op = DiffOperation::kDiffDelete;
         }
      }
      else if(diag->objectU(i)->equals(diag->objectV(i)))
      {
         op = DiffOperation::kDiffEqual;
      }
      else
      {
         int64 me = diag->entry(i);
         int64 w = diag->leftEntry(i);
         int64 nw = diag->entry(i - 1);

         if(me == 1 + w)
         {
            if(diag->offset() >= 0)
            {
               op = DiffOperation::kDiffAdd;
            }
            else
            {
               op = DiffOperation::kDiffDelete;
            }
         }
         else if(me == 1 + nw)
         {
            op = DiffOperation::kDiffModified;
         }
         else
         {
            if(diag->offset() >= 0)
            {
               op = DiffOperation::kDiffDelete;
            }
            else
            {
               op = DiffOperation::kDiffAdd;
            }
         }
      }

      DiffBacktrace* ret = new DiffBacktrace();

      ret->mOperation = op;
      switch(op)
      {
         case DiffOperation::kDiffEqual:
            //			ret->last=Backtrace(diag,i-1);
            i--;
            break;

         case DiffOperation::kDiffModified:
            //			ret->last=Backtrace(diag,i-1);
            ret->mObj1 = diag->objectU(i);
            ret->mObj2 = diag->objectV(i);
            i--;
            break;

         case DiffOperation::kDiffAdd:
            if(diag->offset() == 0)
            {
               //				ret->last=Backtrace(diag->GetBelow(),i-1);
               ret->mObj1 = diag->objectV(i);
               diag = diag->below();
               i--;
            }
            else if(diag->offset() >= 0)
            {
               //				ret->last=Backtrace(diag->GetBelow(),i);
               ret->mObj1 = diag->objectV(i);
               diag = diag->below();
            }
            else
            {
               //				ret->last=Backtrace(diag->GetAbove(),i-1);
               ret->mObj1 = diag->objectV(i);
               diag = diag->above();
               i--;
            }
            break;

         case DiffOperation::kDiffDelete:
            if(diag->offset() == 0)
            {
               //				ret->last =Backtrace(diag->GetAbove(),i-1);
               ret->mObj1 = diag->objectV(i);
               diag = diag->above();
               i--;
            }
            else if(diag->offset() >= 0)
            {
               //				ret->last =Backtrace(diag->GetAbove(),i-1);
               ret->mObj1 = diag->objectV(i);
               diag = diag->above();
               i--;
            }
            else
            {
               //				ret->last =Backtrace(diag->GetBelow(),i);
               ret->mObj1 = diag->objectV(i);
               diag = diag->below();
            }
            break;

         case DiffOperation::kDiffStart:
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
      step->mNext = stack.back();
      stack.pop_back();
      step->mNext->mPrev = step;
      step = step->mNext;
   }

   return top;
}


DiffOperation DiffBacktrace::operation() const
{
   return mOperation;
}



