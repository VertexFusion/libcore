////////////////////////////////////////////////////////////////////////////////////////////////////
// Name:        Mutex.cpp
// Library:     Jameo Core Library
// Purpose:     Mutex object for threas safety
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

#include "PrecompiledCore.hpp"

using namespace jm;

Mutex::Mutex()
{
#if defined(JM_MACOS) || defined(JM_IOS) || defined(JM_LINUX) || defined(JM_ANDROID)
   pthread_condattr_init(&attrc);
   pthread_cond_init(&cond, &attrc);
   pthread_mutexattr_init(&attr);
   pthread_mutex_init(&criticalSection, &attr);

#elif defined JM_WINDOWS
   InitializeCriticalSection((CRITICAL_SECTION*)&mCriticalSection);
#endif
}

Mutex::~Mutex()
{
#if defined JM_WINDOWS
   CRITICAL_SECTION* ptr = (CRITICAL_SECTION*)&mCriticalSection;
   DeleteCriticalSection(ptr);
#endif
}

void Mutex::lock()
{
#if defined(JM_MACOS) || defined(JM_IOS) || defined(JM_LINUX) || defined(JM_ANDROID)
   pthread_mutex_lock(&criticalSection);
#elif defined JM_WINDOWS

   EnterCriticalSection((CRITICAL_SECTION*)&mCriticalSection);

#endif
}

void Mutex::unlock()
{
#if defined(JM_MACOS) || defined(JM_IOS) || defined(JM_LINUX) || defined(JM_ANDROID)
   pthread_mutex_unlock(&criticalSection);

#elif defined JM_WINDOWS

   LeaveCriticalSection((CRITICAL_SECTION*)&mCriticalSection);

#endif
}

void Mutex::sleep()
{
#if defined(JM_MACOS) || defined(JM_IOS) || defined(JM_LINUX) || defined(JM_ANDROID)
   pthread_mutex_lock(&criticalSection);
   pthread_cond_wait(&cond, &criticalSection);
   pthread_mutex_unlock(&criticalSection);

#elif defined JM_WINDOWS

   throw jm::Exception("jm::Mutex::Sleep() Not implemented");

#endif
}

void Mutex::wakeUp()
{
#if defined(JM_MACOS) || defined(JM_IOS) || defined(JM_LINUX) || defined(JM_ANDROID)
   pthread_cond_signal(&cond);

#elif defined JM_WINDOWS

   throw jm::Exception("jm::Mutex::WakeUp() Not implemented");

#endif
}

