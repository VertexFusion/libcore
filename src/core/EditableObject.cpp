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

#include "Precompiled.hpp"

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

Status EditableObject::setMember(String* pointer, const String& value)
{
   if(value.equals(*pointer))return Status::eNotChanged;

   UndoManager* um = mDocument->undoManager();
   if(um != nullptr)um->registerChange(this, pointer);
   *pointer = value;
   return Status::eOK;
}

Status EditableObject::setMember(int64* pointer,
      int64 value,
      int64 rangeMin,
      int64 rangeMax)
{
   if(value == *pointer)return Status::eNotChanged;

   UndoManager* um = mDocument->undoManager();
   if(!(value >= rangeMin && value <= rangeMax))
   {
      Status status = Status::eInvalidInput;
      if(um != nullptr)um->registerTransactionStatus(status);
      return status;
   }
   if(um != nullptr)um->registerChange(this, pointer);
   *pointer = value;
   return Status::eOK;
}

Status EditableObject::setMember(double* pointer, double value)
{
   if(isNaN(value))return Status::eInvalidInput;
   if(value == *pointer)return Status::eNotChanged;

   UndoManager* um = mDocument->undoManager();
   if(um != nullptr)um->registerChange(this, pointer);
   *pointer = value;
   return Status::eOK;
}

Status EditableObject::setMember(bool* pointer, bool value)
{
   if(value == *pointer)return Status::eNotChanged;

   UndoManager* um = mDocument->undoManager();
   if(um != nullptr)um->registerChange(this, pointer);
   *pointer = value;
   return Status::eOK;
}

Status EditableObject::setMember(uint8* pointer, uint8 value)
{
   if(value == *pointer)return Status::eNotChanged;

   UndoManager* um = mDocument->undoManager();
   if(um != nullptr)um->registerChange(this, pointer);
   *pointer = value;
   return Status::eOK;
}

Status EditableObject::setMember(int16* pointer, int16 value)
{
   if(value == *pointer)return Status::eNotChanged;

   UndoManager* um = mDocument->undoManager();
   if(um != nullptr)um->registerChange(this, pointer);
   *pointer = value;
   return Status::eOK;
}

Status EditableObject::setMember(Vertex3* pointer, const Vertex3 &value)
{
   if(value == *pointer)return Status::eNotChanged;

   UndoManager* um = mDocument->undoManager();
   if(um != nullptr)um->registerChange(this, pointer);
   *pointer = value;
   return Status::eOK;
}

Status EditableObject::openTransaction()
{
   UndoManager* um = mDocument->undoManager();
   if(um != nullptr)um->openTransaction();
   return Status::eOK;
}

Status EditableObject::closeTransaction()
{
   UndoManager* um = mDocument->undoManager();
   if(um != nullptr)
   {
      return um->closeTransaction();
   }
   return Status::eNotChanged;
}

Document* EditableObject::document() const
{
   return mDocument;
}
