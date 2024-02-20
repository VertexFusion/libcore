////////////////////////////////////////////////////////////////////////////////////////////////////
// Name:        Object.cpp
// Library:     Jameo Core Library
// Purpose:     Implementation of Object class
//
// Author:      Uwe Runtemund (2014-today)
// Modified by:
// Created:     20.04.2014
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

Object::Object()
{
   mRefCount = 1;
   mPool = System::GetAutoreleasePool();
   // Find Zombie
   //mRefCount=2;
}

Object::~Object()
{
   mPool = NULL;
}

void Object::Release()
{
   if(mPool == NULL)return;

   int32 count;
   Mutex* mutex = mPool->GetMutex();

   mutex->Lock();
   mRefCount--;
   count = GetReferenceCount();
   mutex->Unlock();

   if(count == 0)
   {
      // Find Zombie
      //std::cout<<"Zombie delete"<<std::endl;

      //! If mRefCount==0, Release() or Retain() must not called.
      delete this;
   }
}

Object* Object::Retain()
{
   Mutex* mutex = mPool->GetMutex();
   mutex->Lock();
   mRefCount++;
   mutex->Unlock();
   return this;
}

Object* Object::Autorelease()
{
   mPool->AddObject(this);
   return this;
}

int32 Object::GetReferenceCount() const
{
   return mRefCount & 0x7FFFFFFF;
}

bool Object::Equals(const Object*) const
{
   return false;
}

String Object::GetDisplayName() const
{
   return "jm::Object";
}

void Object::PrintDiffInfo(DiffOperation, Object*) const
{
   // Nothing to do here. Placeholder method.
}

void Object::SetHighBit(bool status)
{
   mRefCount = GetReferenceCount() | (status ? 0x80000000 : 0x00000000);
}

bool Object::GetHighBit()const
{
   return (mRefCount & 0x80000000) != 0;
}
