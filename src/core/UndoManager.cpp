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
	ClearStacks();
	delete mCurrent;
}

void UndoManager::SetDocument(Document* document)
{
	mDocument = document;
}

void UndoManager::SetActive(bool status)
{
	mActive = status;
}

bool UndoManager::IsActive()const
{
	return mActive;
}

bool UndoManager::HasOpenUndoStep() const
{
	return mOpen;
}

bool UndoManager::Undo()
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
		change->Swap();
		change = change->mPrev;
	}

	//Schiebe Schritt auf den Redo-Stack
	step->prev = mRedoStack;
	mRedoStack = step;

	mUndoCount--;
	mRedoCount++;

	mUndoing = false;

	if(mDocument != NULL)mDocument->SetDocumentChanged(true);
	return true;
}

bool UndoManager::Redo()
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
		change->Swap();
		change = change->mNext;
	}

	//Schiebe Schritt auf den Undo-Stack
	step->prev = mUndoStack;
	mUndoStack = step;

	mUndoCount++;
	mRedoCount--;

	mUndoing = false;

	if(mDocument != NULL)mDocument->SetDocumentChanged(true);
	return true;
}

void UndoManager::Close()
{
	//Nur Abschließen, wenn Änderungen vorhanden sind.
	if(mCurrent->count == 0)return;

	mCurrent->prev = mUndoStack;
	mUndoStack = mCurrent;
	mCurrent = new UndoStep();
	mOpen = false;
	mUndoCount++;
	if(mDocument != NULL)mDocument->SetDocumentChanged(true);
}

void UndoManager::ClearStacks()
{
	Close();
	ClearUndoStack();
	ClearRedoStack();
}

void UndoManager::ClearUndoStack()
{
	UndoStep* step = mUndoStack;
	while(step != NULL)
	{
		UndoStep* victim=step;
		step = step->prev;
		delete victim;
	}
	mUndoStack = NULL;
	mUndoCount = 0;
}

void UndoManager::ClearRedoStack()
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

uint32 UndoManager::GetUndoCount()
{
	return mUndoCount;
}

uint32 UndoManager::GetRedoCount()
{
	return mRedoCount;
}

void UndoManager::RegisterChange(Object* object, int8* pointer)
{
	RegisterChange(new UndoChangeInt8(object, pointer));
}

void UndoManager::RegisterChange(Object* object, uint8* pointer)
{
	RegisterChange(new UndoChangeUInt8(object, pointer));
}

void UndoManager::RegisterChange(Object* object, int16* pointer)
{
	RegisterChange(new UndoChangeInt16(object, pointer));
}

void UndoManager::RegisterChange(Object* object, uint16* pointer)
{
	RegisterChange(new UndoChangeUInt16(object, pointer));
}

void UndoManager::RegisterChange(Object* object, int32* pointer)
{
	RegisterChange(new UndoChangeInt32(object, pointer));
}

void UndoManager::RegisterChange(Object* object, uint32* pointer)
{
	RegisterChange(new UndoChangeUInt32(object, pointer));
}

void UndoManager::RegisterChange(Object* object, Integer* pointer)
{
	RegisterChange(new UndoChangeInteger(object, pointer));
}

void UndoManager::RegisterChange(Object* object, int64* pointer)
{
	RegisterChange(new UndoChangeInt64(object, pointer));
}

void UndoManager::RegisterChange(Object* object, uint64* pointer)
{
	RegisterChange(new UndoChangeUInt64(object, pointer));
}

void UndoManager::RegisterChange(Object* object, float* pointer)
{
	RegisterChange(new UndoChangeFloat(object, pointer));
}

void UndoManager::RegisterChange(Object* object, double* pointer)
{
	RegisterChange(new UndoChangeDouble(object, pointer));
}

void UndoManager::RegisterChange(Object* object, Double* pointer)
{
	RegisterChange(new UndoChangeDouble(object, (double*)pointer));
}

void UndoManager::RegisterChange(Object* object, bool* pointer)
{
	RegisterChange(new UndoChangeBool(object, pointer));
}

void UndoManager::RegisterChange(Object* object, jm::Vertex2* pointer)
{
	RegisterChange(new UndoChangeVertex2(object, pointer));
}

void UndoManager::RegisterChange(Object* object, jm::Vertex3* pointer)
{
	RegisterChange(new UndoChangeVertex3(object, pointer));
}

void UndoManager::RegisterChange(Object* object, jm::String* pointer)
{
	RegisterChange(new UndoChangeString(object, pointer));
}

void UndoManager::RegisterChange(Object* object, jm::Date* pointer)
{
	RegisterChange(new UndoChangeDate(object, pointer));
}

void UndoManager::RegisterChange(Object* object, jm::Colour* pointer)
{
	RegisterChange(new UndoChangeColour(object, pointer));
}

void UndoManager::RegisterChange(Object* object, Object** pointer)
{
	RegisterChange(new UndoChangeObjectRef(object, pointer));
}

void UndoManager::RegisterChange(Object* object, uint8** pointer, uint64 length)
{
	RegisterChange(new UndoChangeBuffer(object, pointer, length));
}

void UndoManager::RegisterRegenerationMarker(jm::EditableObject* object)
{
	RegisterChange(new UndoRegenerationMarker(object));
}

void UndoManager::RegisterRelease(Object* object)
{
    RegisterChange(new UndoObjectRelease(object,true));
}

void UndoManager::RegisterRetain(Object* object)
{
    RegisterChange(new UndoObjectRelease(object,false));
}


void UndoManager::RegisterChange(UndoChange* change)
{
	if (!mActive || mUndoing)
	{
		delete change;
		return;
	}

	if (mTransactionLevel > 0)
	{
		mTransaction->AddChange(change);
	}
	else
	{
		mCurrent->AddChange(change);

		ClearRedoStack();
		mOpen = true;
	}
}

//
// Transaction management
//

void UndoManager::OpenTransaction()
{
	if (mTransactionLevel == 0)
	{
		mTransactionStatus = eOK;
		mTransaction = new UndoStep();
	}

	mTransactionLevel++;
}

VxfErrorStatus UndoManager::CloseTransaction()
{
	VxfErrorStatus status = GetTransactionStatus();

	if (status == eOK)Commit();
	else Rollback();

	return status;
}

void UndoManager::Commit()
{
	if (mTransactionLevel == 0)return;

	mTransactionLevel--;

	if (mTransactionLevel == 0)
	{
		UndoStep* step = mTransaction;

		// Move all steps to the change step
		UndoChange* change = step->eldest;
		while (change != NULL)
		{
			UndoChange* trans = change;
			change = change->mNext;
			trans->mPrev = NULL;
			trans->mNext = NULL;
			RegisterChange(trans);
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

void UndoManager::Rollback()
{
	if (mTransactionLevel == 0)return;

	// The rollback
	mTransactionLevel--;

	if (mTransactionLevel == 0)
	{
		UndoStep* step = mTransaction;

		// Undo all changes
		UndoChange* change = step->recent;
		while (change != NULL)
		{
			change->Swap();
			change = change->mPrev;
		}

		delete mTransaction;
		mTransaction = NULL;
		mTransactionStatus = eOK;
	}
}

bool UndoManager::HasOpenTransaction() const
{
	return mTransactionLevel > 0;
}

void UndoManager::RegisterTransactionStatus(VxfErrorStatus status)
{
	if (status != eOK)mTransactionStatus = status;
}

VxfErrorStatus UndoManager::GetTransactionStatus()const
{
	return mTransactionStatus;
}
