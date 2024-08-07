////////////////////////////////////////////////////////////////////////////////////////////////////
// Name:        EditableObject.cpp
// Library:     Jameo Core Library
// Purpose:     Implementation of EditableObject
//
// Author:      Uwe Runtemund (2016-today)
// Modified by:
// Created:     05.06.2016
//
// Copyright:   (c) 2016 Jameo Software, Germany. https://jameo.de
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

EditableObject::EditableObject(Document* doc) : Object()
{
   mDocument = doc;
   mRegenerate = true;
};

void EditableObject::regenerate()
{
   mRegenerate = true;
}

void EditableObject::regenerationDone()
{
   mRegenerate = false;
}

bool EditableObject::shouldRegenerate() const
{
   return mRegenerate;
}

VxfErrorStatus EditableObject::setMember(String* pointer, const String& value)
{
   if(value.equals(*pointer))return eNotChanged;

   UndoManager* um = mDocument->undoManager();
   if(um != NULL)um->registerChange(this, pointer);
   *pointer = value;
   return eOK;
}

VxfErrorStatus EditableObject::setMember(Integer* pointer,
      Integer value,
      Integer rangeMin,
      Integer rangeMax)
{
   if(value == *pointer)return eNotChanged;

   UndoManager* um = mDocument->undoManager();
   if(!(value >= rangeMin && value <= rangeMax))
   {
      VxfErrorStatus status = eInvalidInput;
      if(um != NULL)um->registerTransactionStatus(status);
      return status;
   }
   if(um != NULL)um->registerChange(this, pointer);
   *pointer = value;
   return eOK;
}

VxfErrorStatus EditableObject::setMember(Double* pointer, const Double value)
{
   if(value.IsNaN())return eInvalidInput;
   if(value == *pointer)return eNotChanged;

   UndoManager* um = mDocument->undoManager();
   if(um != NULL)um->registerChange(this, pointer);
   *pointer = value;
   return eOK;
}

VxfErrorStatus EditableObject::setMember(double* pointer, double value)
{
   if(isNaN(value))return eInvalidInput;
   if(value == *pointer)return eNotChanged;

   UndoManager* um = mDocument->undoManager();
   if(um != NULL)um->registerChange(this, pointer);
   *pointer = value;
   return eOK;
}

VxfErrorStatus EditableObject::setMember(bool* pointer, bool value)
{
   if(value == *pointer)return eNotChanged;

   UndoManager* um = mDocument->undoManager();
   if(um != NULL)um->registerChange(this, pointer);
   *pointer = value;
   return eOK;
}

VxfErrorStatus EditableObject::setMember(uint8* pointer, uint8 value)
{
   if(value == *pointer)return eNotChanged;

   UndoManager* um = mDocument->undoManager();
   if(um != NULL)um->registerChange(this, pointer);
   *pointer = value;
   return eOK;
}


VxfErrorStatus EditableObject::openTransaction()
{
   UndoManager* um = mDocument->undoManager();
   if(um != NULL)um->openTransaction();
   return eOK;
}

VxfErrorStatus EditableObject::closeTransaction()
{
   UndoManager* um = mDocument->undoManager();
   if(um != NULL)
   {
      return um->closeTransaction();
   }
   return eNotChanged;
}

