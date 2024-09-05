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

#include "Precompiled.hpp"

using namespace jm;

UndoChange::UndoChange(Object* object)
{
   mPrev = nullptr;
   mNext = nullptr;
   mObject = object;
   mObject->retain();
   objname = mObject->displayName();
}

UndoChange::~UndoChange()
{
   if(mObject->referenceCount() == 0)
   {
      std::cout << objname;
      std::cout << " ZOMBIE" << std::endl;
   }
   mObject->release();
}

void UndoChange::swap()
{
   EditableObject* eo = dynamic_cast<EditableObject*>(mObject);
   if(eo != nullptr)eo->regenerate();
}

//
// Bool
//

UndoChangeBool::UndoChangeBool(Object* object, bool* ptr): UndoChange(object)
{
   mPointer = ptr;
   mValue = *ptr;
}

void UndoChangeBool::swap()
{
   bool tmp = *mPointer;
   *mPointer = mValue;
   mValue = tmp;
   UndoChange::swap();
}

//
// Int8
//

UndoChangeInt8::UndoChangeInt8(Object* object, int8* ptr): UndoChange(object)
{
   mPointer = ptr;
   mValue = *ptr;
}

void UndoChangeInt8::swap()
{
   int8 tmp = *mPointer;
   *mPointer = mValue;
   mValue = tmp;
   UndoChange::swap();
}

//
// UInt8
//

UndoChangeUInt8::UndoChangeUInt8(Object* object, uint8* ptr): UndoChange(object)
{
   mPointer = ptr;
   mValue = *ptr;
}

void UndoChangeUInt8::swap()
{
   uint8 tmp = *mPointer;
   *mPointer = mValue;
   mValue = tmp;
   UndoChange::swap();
}

//
// Int16
//

UndoChangeInt16::UndoChangeInt16(Object* object, int16* ptr): UndoChange(object)
{
   mPointer = ptr;
   mValue = *ptr;
}

void UndoChangeInt16::swap()
{
   int16 tmp = *mPointer;
   *mPointer = mValue;
   mValue = tmp;
   UndoChange::swap();
}

//
// Uint16
//

UndoChangeUInt16::UndoChangeUInt16(Object* object, uint16* ptr): UndoChange(object)
{
   mPointer = ptr;
   mValue = *ptr;
}

void UndoChangeUInt16::swap()
{
   uint16 tmp = *mPointer;
   *mPointer = mValue;
   mValue = tmp;
   UndoChange::swap();
}

//
// Int32
//

UndoChangeInt32::UndoChangeInt32(Object* object, int32* ptr): UndoChange(object)
{
   mPointer = ptr;
   mValue = *ptr;
}

void UndoChangeInt32::swap()
{
   int32 tmp = *mPointer;
   *mPointer = mValue;
   mValue = tmp;
   UndoChange::swap();
}

//
// Uint32
//

UndoChangeUInt32::UndoChangeUInt32(Object* object, uint32* ptr): UndoChange(object)
{
   mPointer = ptr;
   mValue = *ptr;
}

void UndoChangeUInt32::swap()
{
   uint32 tmp = *mPointer;
   *mPointer = mValue;
   mValue = tmp;
   UndoChange::swap();
}

//
// Integer
//

UndoChangeInteger::UndoChangeInteger(Object* object, Integer* ptr) : UndoChange(object)
{
   mPointer = ptr;
   mValue = *ptr;
}

void UndoChangeInteger::swap()
{
   Integer tmp = *mPointer;
   *mPointer = mValue;
   mValue = tmp;
   UndoChange::swap();
}

//
// Int64
//

UndoChangeInt64::UndoChangeInt64(Object* object, int64* ptr): UndoChange(object)
{
   mPointer = ptr;
   mValue = *ptr;
}

void UndoChangeInt64::swap()
{
   int64 tmp = *mPointer;
   *mPointer = mValue;
   mValue = tmp;
   UndoChange::swap();
}

//
// Uint64
//

UndoChangeUInt64::UndoChangeUInt64(Object* object, uint64* ptr): UndoChange(object)
{
   mPointer = ptr;
   mValue = *ptr;
}

void UndoChangeUInt64::swap()
{
   uint64 tmp = *mPointer;
   *mPointer = mValue;
   mValue = tmp;
   UndoChange::swap();
}

//
// Float
//

UndoChangeFloat::UndoChangeFloat(Object* object, float* ptr): UndoChange(object)
{
   mPointer = ptr;
   mValue = *ptr;
}

void UndoChangeFloat::swap()
{
   float tmp = *mPointer;
   *mPointer = mValue;
   mValue = tmp;
   UndoChange::swap();
}

//
// Double
//

UndoChangeDouble::UndoChangeDouble(Object* object, double* ptr): UndoChange(object)
{
   mPointer = ptr;
   mValue = *ptr;
}

void UndoChangeDouble::swap()
{
   double tmp = *mPointer;
   *mPointer = mValue;
   mValue = tmp;
   UndoChange::swap();
}

//
// String
//

UndoChangeString::UndoChangeString(Object* object, String* ptr): UndoChange(object)
{
   mPointer = ptr;
   mValue = *ptr;
}

void UndoChangeString::swap()
{
   String tmp = *mPointer;
   *mPointer = mValue;
   mValue = tmp;
   UndoChange::swap();
}

//
// Vertex2
//

UndoChangeVertex2::UndoChangeVertex2(Object* object, Vertex2* ptr) : UndoChange(object)
{
   mPointer = ptr;
   mValue = *ptr;
}

void UndoChangeVertex2::swap()
{
   Vertex2 tmp = *mPointer;
   *mPointer = mValue;
   mValue = tmp;
   UndoChange::swap();
}

//
// Vertex3
//

UndoChangeVertex3::UndoChangeVertex3(Object* object, Vertex3* ptr): UndoChange(object)
{
   mPointer = ptr;
   mValue = *ptr;
}

void UndoChangeVertex3::swap()
{
   Vertex3 tmp = *mPointer;
   *mPointer = mValue;
   mValue = tmp;
   UndoChange::swap();
}

//
// Date
//

UndoChangeDate::UndoChangeDate(Object* object, Date* ptr): UndoChange(object)
{
   mPointer = ptr;
   mValue = *ptr;
}

void UndoChangeDate::swap()
{
   Date tmp = *mPointer;
   *mPointer = mValue;
   mValue = tmp;
   UndoChange::swap();
}

//
// Colour
//

UndoChangeColour::UndoChangeColour(Object* object, Color* ptr): UndoChange(object)
{
   mPointer = ptr;
   mValue = *ptr;
}

void UndoChangeColour::swap()
{
   Color tmp = *mPointer;
   *mPointer = mValue;
   mValue = tmp;
   UndoChange::swap();
}

//
// ObjectRef
//

UndoChangeObjectRef::UndoChangeObjectRef(Object* object, Object** ptr): UndoChange(object)
{
   mPointer = ptr;
   mValue = *ptr;

   //Wenn "alter" Pointer einen Wert enthält, erhöhe Referenzzähler um 1.
   if(mValue != nullptr)mValue->retain();
}

UndoChangeObjectRef::~UndoChangeObjectRef()
{
   if(mValue != nullptr)mValue->release();
}


void UndoChangeObjectRef::swap()
{
   // This method does not change the reference counters.
   // Even if a reference is NULL, the "logic" changes the owner, but the bottom line is that the
   // counter remains the same. The owner is not "saved".
   // Therefore, no reference meter may be manipulated here.

   Object* tmpValue = *mPointer;

   //	if(tmpValue!=NULL)tmpValue->retain();
   //   if(mValue!=NULL)mValue->release();

   *mPointer = mValue;
   mValue = tmpValue;

   UndoChange::swap();
}

//
// Buffer
//

UndoChangeBuffer::UndoChangeBuffer(Object* object, uint8** pointer,
                                   uint64 length): UndoChange(object)
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

void UndoChangeBuffer::swap()
{
   uint8* tmpValue = new uint8[mLength];

   memcpy(tmpValue, *mPointer, mLength);
   //memcpy(*mPointer, mValue,mLength);
   //memcpy(mValue, tmpValue, mLength);

   delete[] tmpValue;

   UndoChange::swap();
   throw new Exception("Undo not implemented");

}

UndoRegenerationMarker::UndoRegenerationMarker(EditableObject* object): UndoChange(object)
{
}

void UndoRegenerationMarker::swap()
{
   //Hier wird automatisch ein Regenerate ausgelöst...
   UndoChange::swap();
}

UndoObjectRelease::UndoObjectRelease(Object* object, bool release): UndoChange(object)
{
   // Nothing to do here. The super method will retain() the object.
   // This is just the one thing we want to do.
   mReleased = release;
   mObject = object;
}

UndoObjectRelease::~UndoObjectRelease()
{
   // Nothing to do here. The super method will release() the object.
   // This is just the one thing we want to do.
}

void UndoObjectRelease::swap()
{
   // We swap the reference counter here
   if(mReleased)mObject->retain();
   else mObject->release();

   mReleased = !mReleased;

   UndoChange::swap();
}
