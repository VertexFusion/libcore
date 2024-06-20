////////////////////////////////////////////////////////////////////////////////////////////////////
// Name:        UndoStep.cpp
// Library:     Jameo Core Library
// Purpose:     Undo Management
//
// Author:      Uwe Runtemund (2014-today)
// Modified by:
// Created:     11.02.2014
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

UndoStep::UndoStep()
{
   prev = NULL;
   recent = NULL;
   eldest = NULL;
   count = 0;
}

UndoStep::~UndoStep()
{
   UndoChange* change = recent;

   while(change != NULL)
   {
      UndoChange* victim = change;
      change = change->mPrev;
      delete victim;
   }

   prev = NULL;
   recent = NULL;
   eldest = NULL;
   count = 0;
}

void UndoStep::add(UndoChange* change)
{
   //Verkette
   change->mPrev = recent;
   if(recent != NULL)recent->mNext = change;
   recent = change;

   //Setze eldest, wenn er noch nicht gesetzt wurde
   if(eldest == NULL)eldest = recent;

   count++;
}
