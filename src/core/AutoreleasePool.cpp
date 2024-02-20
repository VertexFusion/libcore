////////////////////////////////////////////////////////////////////////////////////////////////////
// Name:        AutoreleasePool.cpp
// Library:     Jameo Core Library
// Purpose:     Implementation of AutoreleasePool
//
// Author:      Uwe Runtemund (2015-today)
// Modified by:
// Created:     28.11.2015
//
// Copyright:   (c) 2015 Jameo Software, Germany. https://jameo.de
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


AutoreleasePool::AutoreleasePool(): Object()
{
   //1st Entry is a dummy to avoid if-queries with AddObject
   mPool = new PoolEntry();
   mPool->object = NULL;
   mPool->next = NULL;

   mTop = mPool;
}

AutoreleasePool::~AutoreleasePool()
{
   // Cleanup Autorelease
   Drain();

   // Delete dummy
   delete mPool;
}

void AutoreleasePool::Drain()
{
   PoolEntry* pool = mPool->next;

   while(pool != NULL)
   {
      //Release objects
      pool->object->Release();

      PoolEntry* next = pool->next;
      delete pool;
      pool = next;
   }

   mTop = mPool;
   mPool->next = NULL;
}

void AutoreleasePool::AddObject(Object* object)
{
   PoolEntry* entry = new PoolEntry();
   entry->object = object;
   entry->next = NULL;
   mTop->next = entry;
   mTop = entry;
}

Mutex* AutoreleasePool::GetMutex()
{
   return &mMutex;
}
