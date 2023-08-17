//
//  UndoChange.cpp
//  jameo
//
//  Created by Uwe Runtemund on 11.02.14.
//  Copyright (c) 2014 Jameo Software. All rights reserved.
//
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
