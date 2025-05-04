////////////////////////////////////////////////////////////////////////////////////////////////////
// Name:        Mutex.h
// Library:     Jameo Core Library
// Purpose:     Helper classes for thread safety
//
// Author:      Uwe Runtemund (2012-today)
// Modified by:
// Created:     07.12.2012
//
// Copyright:   (c) 2012 Jameo Software, Germany. https://jameo.de
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

#ifndef jm_Mutex_h
#define jm_Mutex_h

#include "Types.h"

#if defined(__APPLE__) || defined(__linux__)   //macOS & Linux

#include <pthread.h>

#endif

namespace jm
{

   /*!
    \brief Mutex class.
    */
   class DllExport Mutex
   {
      public:

         /*!
          \brief The default constructor.
          */
         Mutex();

         /*!
          \brief Destructor.
          */
         ~Mutex();

         /*!
          \brief Lock the mutex object.
          */
         void lock();

         /*!
          \brief Unlock the mutex object.
          */
         void unlock();

         /*!
          \brief Sleep
          */
         void sleep();

         /*!
          \brief Wake up.
          */
         void wakeUp();

      private:

#if defined(__APPLE__) || defined(__linux__)//macOS & Linux

         //!pthread data types
         pthread_mutex_t criticalSection;
         pthread_mutexattr_t attr;
         pthread_condattr_t attrc;
         pthread_cond_t cond;

#elif defined _WIN32//Windows

         //On Windows 7 und 10 sizeof(CRITICAL_SECTION) returns 40 Bytes, so he make hardcode here.
         uint8 mCriticalSection[40];

#endif
   };

}



#endif
