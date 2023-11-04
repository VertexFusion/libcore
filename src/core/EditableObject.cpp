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

void EditableObject::Regenerate()
{
	mRegenerate = true;
}

void EditableObject::RegenerationDone()
{
	mRegenerate = false;
}

bool EditableObject::ShouldRegenerate() const
{
	return mRegenerate;
}

VxfErrorStatus EditableObject::SetMember(String* pointer, const String& value)
{
	if (value.Equals(*pointer))return eNotChanged;

	UndoManager* um = mDocument->GetUndoManager();
	if (um != NULL)um->RegisterChange(this, pointer);
	*pointer = value;
	return eOK;
}

VxfErrorStatus EditableObject::SetMember(Integer* pointer,
	Integer value,
	Integer rangeMin,
	Integer rangeMax)
{
	if (value == *pointer)return eNotChanged;

	UndoManager* um = mDocument->GetUndoManager();
	if (! (value>=rangeMin && value<=rangeMax))
	{
		VxfErrorStatus status = eInvalidInput;
		if (um != NULL)um->RegisterTransactionStatus(status);
		return status;
	}
	if (um != NULL)um->RegisterChange(this, pointer);
	*pointer = value;
	return eOK;
}

VxfErrorStatus EditableObject::SetMember(Double* pointer, const Double value)
{
	if (value.IsNaN())return eInvalidInput;
	if (value == *pointer)return eNotChanged;

	UndoManager* um = mDocument->GetUndoManager();
	if (um != NULL)um->RegisterChange(this, pointer);
	*pointer = value;
	return eOK;
}

VxfErrorStatus EditableObject::SetMember(double* pointer, double value)
{
	if (IsNaN(value))return eInvalidInput;
	if (value == *pointer)return eNotChanged;

	UndoManager* um = mDocument->GetUndoManager();
	if (um != NULL)um->RegisterChange(this, pointer);
	*pointer = value;
	return eOK;
}


VxfErrorStatus EditableObject::OpenTransaction()
{
	UndoManager* um = mDocument->GetUndoManager();
	if (um != NULL)um->OpenTransaction();
	return eOK;
}

VxfErrorStatus EditableObject::CloseTransaction()
{
	UndoManager* um = mDocument->GetUndoManager();
	if (um != NULL)
	{
		return um->CloseTransaction();
	}
	return eNotChanged;
}

