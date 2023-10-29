//
//  UndoManager.cpp
//  dxf
//
//  Created by Uwe Runtemund on 11.02.14.
//  Copyright (c) 2014 Jameo Software. All rights reserved.
//

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

bool UndoManager::IsActive()
{
	return mActive;
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

void UndoManager::RegisterChange(UndoChange* change)
{
	if(!mActive || mUndoing)
	{
		delete change;
		return;
	}

	mCurrent->AddChange(change);

	ClearRedoStack();
	mOpen = true;
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
