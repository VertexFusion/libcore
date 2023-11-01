////////////////////////////////////////////////////////////////////////////////////////////////////
// Name:        UndoChange.cpp
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

UndoChange::UndoChange(Object* object)
{
	mPrev = NULL;
	mNext = NULL;
	mObject = object;
	mObject->Retain();
}

UndoChange::~UndoChange()
{
	mObject->Release();
}

void UndoChange::Swap()
{
	EditableObject* eo = dynamic_cast<EditableObject*>(mObject);
	if(eo != NULL)eo->Regenerate();
}

//
// Bool
//

UndoChangeBool::UndoChangeBool(Object* object, bool *ptr): UndoChange(object)
{
	mPointer = ptr;
	mValue = *ptr;
}

void UndoChangeBool::Swap()
{
	bool tmp = *mPointer;
	*mPointer = mValue;
	mValue = tmp;
	UndoChange::Swap();
}

//
// Int8
//

UndoChangeInt8::UndoChangeInt8(Object* object, int8 *ptr): UndoChange(object)
{
	mPointer = ptr;
	mValue = *ptr;
}

void UndoChangeInt8::Swap()
{
	int8 tmp = *mPointer;
	*mPointer = mValue;
	mValue = tmp;
	UndoChange::Swap();
}

//
// UInt8
//

UndoChangeUInt8::UndoChangeUInt8(Object* object, uint8 *ptr): UndoChange(object)
{
	mPointer = ptr;
	mValue = *ptr;
}

void UndoChangeUInt8::Swap()
{
	uint8 tmp = *mPointer;
	*mPointer = mValue;
	mValue = tmp;
	UndoChange::Swap();
}

//
// Int16
//

UndoChangeInt16::UndoChangeInt16(Object* object, int16 *ptr): UndoChange(object)
{
	mPointer = ptr;
	mValue = *ptr;
}

void UndoChangeInt16::Swap()
{
	int16 tmp = *mPointer;
	*mPointer = mValue;
	mValue = tmp;
	UndoChange::Swap();
}

//
// Uint16
//

UndoChangeUInt16::UndoChangeUInt16(Object* object, uint16 *ptr): UndoChange(object)
{
	mPointer = ptr;
	mValue = *ptr;
}

void UndoChangeUInt16::Swap()
{
	uint16 tmp = *mPointer;
	*mPointer = mValue;
	mValue = tmp;
	UndoChange::Swap();
}

//
// Int32
//

UndoChangeInt32::UndoChangeInt32(Object* object, int32 *ptr): UndoChange(object)
{
	mPointer = ptr;
	mValue = *ptr;
}

void UndoChangeInt32::Swap()
{
	int32 tmp = *mPointer;
	*mPointer = mValue;
	mValue = tmp;
	UndoChange::Swap();
}

//
// Uint32
//

UndoChangeUInt32::UndoChangeUInt32(Object* object, uint32 *ptr): UndoChange(object)
{
	mPointer = ptr;
	mValue = *ptr;
}

void UndoChangeUInt32::Swap()
{
	uint32 tmp = *mPointer;
	*mPointer = mValue;
	mValue = tmp;
	UndoChange::Swap();
}

//
// Integer
//

UndoChangeInteger::UndoChangeInteger(Object* object, Integer* ptr) : UndoChange(object)
{
	mPointer = ptr;
	mValue = *ptr;
}

void UndoChangeInteger::Swap()
{
	Integer tmp = *mPointer;
	*mPointer = mValue;
	mValue = tmp;
	UndoChange::Swap();
}

//
// Int64
//

UndoChangeInt64::UndoChangeInt64(Object* object, int64 *ptr): UndoChange(object)
{
	mPointer = ptr;
	mValue = *ptr;
}

void UndoChangeInt64::Swap()
{
	int64 tmp = *mPointer;
	*mPointer = mValue;
	mValue = tmp;
	UndoChange::Swap();
}

//
// Uint64
//

UndoChangeUInt64::UndoChangeUInt64(Object* object, uint64 *ptr): UndoChange(object)
{
	mPointer = ptr;
	mValue = *ptr;
}

void UndoChangeUInt64::Swap()
{
	uint64 tmp = *mPointer;
	*mPointer = mValue;
	mValue = tmp;
	UndoChange::Swap();
}

//
// Float
//

UndoChangeFloat::UndoChangeFloat(Object* object, float *ptr): UndoChange(object)
{
	mPointer = ptr;
	mValue = *ptr;
}

void UndoChangeFloat::Swap()
{
	float tmp = *mPointer;
	*mPointer = mValue;
	mValue = tmp;
	UndoChange::Swap();
}

//
// Double
//

UndoChangeDouble::UndoChangeDouble(Object* object, double *ptr): UndoChange(object)
{
	mPointer = ptr;
	mValue = *ptr;
}

void UndoChangeDouble::Swap()
{
	double tmp = *mPointer;
	*mPointer = mValue;
	mValue = tmp;
	UndoChange::Swap();
}

//
// String
//

UndoChangeString::UndoChangeString(Object* object, String *ptr): UndoChange(object)
{
	mPointer = ptr;
	mValue = *ptr;
}

void UndoChangeString::Swap()
{
	String tmp = *mPointer;
	*mPointer = mValue;
	mValue = tmp;
	UndoChange::Swap();
}

//
// Vertex2
//

UndoChangeVertex2::UndoChangeVertex2(Object* object, Vertex2* ptr) : UndoChange(object)
{
	mPointer = ptr;
	mValue = *ptr;
}

void UndoChangeVertex2::Swap()
{
	Vertex2 tmp = *mPointer;
	*mPointer = mValue;
	mValue = tmp;
	UndoChange::Swap();
}

//
// Vertex3
//

UndoChangeVertex3::UndoChangeVertex3(Object* object, Vertex3 *ptr): UndoChange(object)
{
	mPointer = ptr;
	mValue = *ptr;
}

void UndoChangeVertex3::Swap()
{
	Vertex3 tmp = *mPointer;
	*mPointer = mValue;
	mValue = tmp;
	UndoChange::Swap();
}

//
// Date
//

UndoChangeDate::UndoChangeDate(Object* object, Date *ptr): UndoChange(object)
{
	mPointer = ptr;
	mValue = *ptr;
}

void UndoChangeDate::Swap()
{
	Date tmp = *mPointer;
	*mPointer = mValue;
	mValue = tmp;
	UndoChange::Swap();
}

//
// Colour
//

UndoChangeColour::UndoChangeColour(Object* object, Colour *ptr): UndoChange(object)
{
	mPointer = ptr;
	mValue = *ptr;
}

void UndoChangeColour::Swap()
{
	Colour tmp = *mPointer;
	*mPointer = mValue;
	mValue = tmp;
	UndoChange::Swap();
}

//
// ObjectRef
//

UndoChangeObjectRef::UndoChangeObjectRef(Object* object, Object **ptr): UndoChange(object)
{
	mPointer = ptr;
	mValue = *ptr;

	//Wenn "alter" Pointer einen Wert enthält, erhöhe Referenzzähler um 1.
	if(mValue != NULL)mValue->Retain();
}

UndoChangeObjectRef::~UndoChangeObjectRef()
{
	if(mValue != NULL)mValue->Release();
}


void UndoChangeObjectRef::Swap()
{
	//Diese Methode ändert an den Referenzzählern nichts.
	//Auch wenn eine Referenz NULL ist, dann ändert sich von der "Logik" zwar der Besitzer,
	//aber unter dem Strich bleibt der Zähler gleich. Der Besitzer wird ja nicht "gespeichert".
	//Daher darf hier kein Referenzzähler manipuliert werden.

	Object* tmpValue = *mPointer;

	if(tmpValue!=NULL)tmpValue->Retain();
    if(mValue!=NULL)mValue->Release();

	*mPointer = mValue;
	mValue = tmpValue;

	UndoChange::Swap();
}

//
// Buffer
//

UndoChangeBuffer::UndoChangeBuffer(Object* object, uint8** pointer, uint64 length): UndoChange(object)
{
	mLength = length;
	if(length <= 8)
	{
		mPointer = pointer;
		//memcpy( &*mValue, *pointer, length );
		mValue = *pointer;
	}
	else
	{
		mPointer = pointer;
		mValue = new uint8[length];
		memcpy(mValue, *pointer, length);
	}
	throw new Exception("Undo not implemented");

}

void UndoChangeBuffer::Swap()
{
	uint8* tmpValue = new uint8[mLength];

	memcpy(tmpValue, *mPointer, mLength);
	//memcpy(*mPointer, mValue,mLength);
	//memcpy(mValue, tmpValue, mLength);

	delete[] tmpValue;

	UndoChange::Swap();
	throw new Exception("Undo not implemented");

}

UndoRegenerationMarker::UndoRegenerationMarker(EditableObject* object): UndoChange(object)
{
}

void UndoRegenerationMarker::Swap()
{
	//Hier wird automatisch ein Regenerate ausgelöst...
	UndoChange::Swap();
}

UndoObjectRelease::UndoObjectRelease(Object* object,bool release): UndoChange(object)
{
    // Nothing to do here. The super method will Retain() the object.
    // This is just the one thing we want to do.
    mReleased=release;
    mObject=object;
}

UndoObjectRelease::~UndoObjectRelease()
{
    // Nothing to do here. The super method will Release() the object.
    // This is just the one thing we want to do.
}

void UndoObjectRelease::Swap()
{
    // We swap the reference counter here
    if(mReleased)mObject->Retain();
    else mObject->Release();

    mReleased=!mReleased;

	UndoChange::Swap();
}
