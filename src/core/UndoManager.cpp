////////////////////////////////////////////////////////////////////////////////////////////////////
// Name:        UndoManager.cpp
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

UndoManager::UndoManager(): Object()
{
   mActive = false;
   mUndoing = false;
   mOpen = false;

   mCurrent = new UndoStep();
   mUndoStack = NULL;
   mRedoStack = NULL;

   mUndoCount = 0;
   mRedoCount = 0;

   mDocument = NULL;

   mTransactionLevel = 0;
   mTransaction = NULL;
   mTransactionStatus = eOK;
}

UndoManager::~UndoManager()
{
   clearStacks();
   delete mCurrent;
}

void UndoManager::setDocument(Document* document)
{
   mDocument = document;
}

void UndoManager::setActive(bool status)
{
   mActive = status;
}

bool UndoManager::isActive()const
{
   return mActive;
}

bool UndoManager::hasOpenUndoStep() const
{
   return mOpen;
}

bool UndoManager::undo()
{
   if(mOpen)return false;
   if(mUndoStack == NULL)return false;
   mUndoing = true;

   //Hole Schritt vom Undo-Stack
   UndoStep* step = mUndoStack;
   mUndoStack = step->prev;

   //Mache Undo-Step rückgängig und wandle ihn zum Redo-Step
   //Druchlaufe die Schritte rückwärts, damit doppelte Änderungen sich nicht überschreiben
   UndoChange* change = step->recent;
   while(change != NULL)
   {
      change->swap();
      change = change->mPrev;
   }

   //Schiebe Schritt auf den Redo-Stack
   step->prev = mRedoStack;
   mRedoStack = step;

   mUndoCount--;
   mRedoCount++;

   mUndoing = false;

   if(mDocument != NULL)mDocument->setDocumentChanged(true);
   return true;
}

bool UndoManager::redo()
{
   if(mOpen) return false;
   if(mRedoStack == NULL)return false;
   mUndoing = true;

   //Hole Schritt vom Redo-Stack
   UndoStep* step = mRedoStack;
   mRedoStack = step->prev;

   //Mache Redo-Step rückgängig und wandle ihn zum Undo-Step
   //Druchlaufe die Schritte vorwärts, damit doppelte Änderungen sich nicht überschreiben
   UndoChange* change = step->eldest;
   while(change != NULL)
   {
      change->swap();
      change = change->mNext;
   }

   //Schiebe Schritt auf den Undo-Stack
   step->prev = mUndoStack;
   mUndoStack = step;

   mUndoCount++;
   mRedoCount--;

   mUndoing = false;

   if(mDocument != NULL)mDocument->setDocumentChanged(true);
   return true;
}

void UndoManager::close()
{
   // Only close, if changes are present
   if(mCurrent->count == 0)return;

   mCurrent->prev = mUndoStack;
   mUndoStack = mCurrent;
   mCurrent = new UndoStep();
   mOpen = false;
   mUndoCount++;
   if(mDocument != NULL)mDocument->setDocumentChanged(true);
}

void UndoManager::clearStacks()
{
   close();
   clearUndoStack();
   clearRedoStack();
}

void UndoManager::clearUndoStack()
{
   UndoStep* step = mUndoStack;
   while(step != NULL)
   {
      UndoStep* victim = step;
      step = step->prev;
      delete victim;
   }
   mUndoStack = NULL;
   mUndoCount = 0;
}

void UndoManager::clearRedoStack()
{
   UndoStep* step = mRedoStack;
   while(step != NULL)
   {
      UndoStep* prev = step->prev;
      delete step;
      step = prev;
   }
   mRedoStack = NULL;
   mRedoCount = 0;
}

uint32 UndoManager::undoCount()
{
   return mUndoCount;
}

uint32 UndoManager::redoCount()
{
   return mRedoCount;
}

void UndoManager::registerChange(Object* object, int8* pointer)
{
   registerChange(new UndoChangeInt8(object, pointer));
}

void UndoManager::registerChange(Object* object, uint8* pointer)
{
   registerChange(new UndoChangeUInt8(object, pointer));
}

void UndoManager::registerChange(Object* object, int16* pointer)
{
   registerChange(new UndoChangeInt16(object, pointer));
}

void UndoManager::registerChange(Object* object, uint16* pointer)
{
   registerChange(new UndoChangeUInt16(object, pointer));
}

void UndoManager::registerChange(Object* object, int32* pointer)
{
   registerChange(new UndoChangeInt32(object, pointer));
}

void UndoManager::registerChange(Object* object, uint32* pointer)
{
   registerChange(new UndoChangeUInt32(object, pointer));
}

void UndoManager::registerChange(Object* object, Integer* pointer)
{
   registerChange(new UndoChangeInteger(object, pointer));
}

void UndoManager::registerChange(Object* object, int64* pointer)
{
   registerChange(new UndoChangeInt64(object, pointer));
}

void UndoManager::registerChange(Object* object, uint64* pointer)
{
   registerChange(new UndoChangeUInt64(object, pointer));
}

void UndoManager::registerChange(Object* object, float* pointer)
{
   registerChange(new UndoChangeFloat(object, pointer));
}

void UndoManager::registerChange(Object* object, double* pointer)
{
   registerChange(new UndoChangeDouble(object, pointer));
}

void UndoManager::registerChange(Object* object, bool* pointer)
{
   registerChange(new UndoChangeBool(object, pointer));
}

void UndoManager::registerChange(Object* object, jm::Vertex2* pointer)
{
   registerChange(new UndoChangeVertex2(object, pointer));
}

void UndoManager::registerChange(Object* object, jm::Vertex3* pointer)
{
   registerChange(new UndoChangeVertex3(object, pointer));
}

void UndoManager::registerChange(Object* object, jm::String* pointer)
{
   registerChange(new UndoChangeString(object, pointer));
}

void UndoManager::registerChange(Object* object, jm::Date* pointer)
{
   registerChange(new UndoChangeDate(object, pointer));
}

void UndoManager::registerChange(Object* object, jm::Color* pointer)
{
   registerChange(new UndoChangeColour(object, pointer));
}

void UndoManager::registerChange(Object* object, Object** pointer)
{
   registerChange(new UndoChangeObjectRef(object, pointer));
}

void UndoManager::registerChange(Object* object, uint8** pointer, uint64 length)
{
   registerChange(new UndoChangeBuffer(object, pointer, length));
}

void UndoManager::registerRegenerationMarker(jm::EditableObject* object)
{
   registerChange(new UndoRegenerationMarker(object));
}

void UndoManager::registerRelease(Object* object)
{
   registerChange(new UndoObjectRelease(object, true));
}

void UndoManager::registerRetain(Object* object)
{
   registerChange(new UndoObjectRelease(object, false));
}


void UndoManager::registerChange(UndoChange* change)
{
   if(!mActive || mUndoing)
   {
      delete change;
      return;
   }

   if(mTransactionLevel > 0)
   {
      mTransaction->add(change);
   }
   else
   {
      mCurrent->add(change);

      clearRedoStack();
      mOpen = true;
   }
}

//
// Transaction management
//

void UndoManager::openTransaction()
{
   if(mTransactionLevel == 0)
   {
      mTransactionStatus = eOK;
      mTransaction = new UndoStep();
   }

   mTransactionLevel++;
}

VxfErrorStatus UndoManager::closeTransaction()
{
   VxfErrorStatus status = transactionStatus();

   if(status == eOK)commit();
   else rollback();

   return status;
}

void UndoManager::commit()
{
   if(mTransactionLevel == 0)return;

   mTransactionLevel--;

   if(mTransactionLevel == 0)
   {
      UndoStep* step = mTransaction;

      // Move all steps to the change step
      UndoChange* change = step->eldest;
      while(change != NULL)
      {
         UndoChange* trans = change;
         change = change->mNext;
         trans->mPrev = NULL;
         trans->mNext = NULL;
         registerChange(trans);
      }

      // Set all to null, to prevent deletion in next step.
      mTransaction->prev = NULL;
      mTransaction->recent = NULL;
      mTransaction->eldest = NULL;
      mTransaction->count = 0;

      delete mTransaction;
      mTransaction = NULL;
      mTransactionStatus = eOK;
   }
}

void UndoManager::rollback()
{
   if(mTransactionLevel == 0)return;

   // The rollback
   mTransactionLevel--;

   if(mTransactionLevel == 0)
   {
      UndoStep* step = mTransaction;

      // Undo all changes
      UndoChange* change = step->recent;
      while(change != NULL)
      {
         change->swap();
         change = change->mPrev;
      }

      delete mTransaction;
      mTransaction = NULL;
      mTransactionStatus = eOK;
   }
}

bool UndoManager::hasOpenTransaction() const
{
   return mTransactionLevel > 0;
}

void UndoManager::registerTransactionStatus(VxfErrorStatus status)
{
   if(status != eOK &&
         status != eNotChanged)mTransactionStatus = status;
}

VxfErrorStatus UndoManager::transactionStatus()const
{
   return mTransactionStatus;
}

UndoStep* UndoManager::openStep()
{
   return mCurrent;
}
