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

#include "PrecompiledCore.hpp"

using namespace jm;

Object::Object() noexcept:
   mRefCount(1),
   mPool(System::autoreleasePool())
{
   // Find Zombie
   //mRefCount=2;
}

Object::~Object() noexcept
{
   mPool = nullptr;
}

void Object::release() noexcept
{
   if(mPool == nullptr)return;

   int32 count;
   Mutex* mutex = mPool->mutex();

   mutex->lock();
   mRefCount--;
   count = referenceCount();
   mutex->unlock();

   if(count == 0)
   {
      // Find Zombie
      //std::cout<<"Zombie delete"<<std::endl;

      //! If mRefCount==0, release() or retain() must not called.
      delete this;
   }
}

Object* Object::retain() noexcept
{
   Mutex* mutex = mPool->mutex();
   mutex->lock();
   mRefCount++;
   mutex->unlock();
   return this;
}

Object* Object::autorelease() noexcept
{
   mPool->add(this);
   return this;
}

int32 Object::referenceCount() const noexcept
{
   return mRefCount & 0x7FFFFFFF;
}

bool Object::equals(const Object*) const
{
   return false;
}

String Object::displayName() const
{
   return "jm::Object";
}

void Object::printDiffInfo(DiffOperation, Object*) const
{
   // Nothing to do here. Placeholder method.
}

void Object::setHighBit(bool status) noexcept
{
   mRefCount = referenceCount() | static_cast<int32>(status ? 0x80000000 : 0x00000000);
}

bool Object::highBit()const noexcept
{
   return (mRefCount & static_cast<int32>(0x80000000)) != 0;
}
