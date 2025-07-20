////////////////////////////////////////////////////////////////////////////////////////////////////
// Name:        AutoreleasePool.h
// Library:     Jameo Core Library
// Purpose:     Memory Management for objects
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

#ifndef jm_AutoreleasePool_h
#define jm_AutoreleasePool_h

#include "Object.h"
#include "Mutex.h"

namespace jm
{
   /*!
    \brief This class provides the memory pool component to release objects at regular intervals
    that the programmer has designated for delayed release by Object::autorelease().
    \ingroup datamgr
    */
   class DllExport AutoreleasePool: public Object
   {

      public:

         /*!
          \brief Constructor
          */
         AutoreleasePool();

         /*!
          \brief Destructor
          */
         ~AutoreleasePool() override;

         /*!
          \brief Sends a release() to all objects accumulated in the AutoreleasePool.
          */
         void drain();

         /*!
          \brief Returns the pointer to the mutex object.
          */
         Mutex* mutex();

      private:

         //! Struct for the entries of the pool. The pool is a linked list.
         struct PoolEntry
         {
            Object* object;
            PoolEntry* next;
         };

         //! First element in the pool.
         PoolEntry* mPool;

         //! Top pool element to realise FIFO.
         PoolEntry* mTop;

         //! Mutex for reference counter manipulation
         Mutex mMutex;

         //! Mutex for autoreleasepool itself
         Mutex mPoolMutex;

         //! Adds an object. Called in Object::autorelease().
         void add(Object* object);

         //! Allow Object::autorelease() access to AddObject().
         friend Object* Object::autorelease() noexcept;

   };
}


#endif
