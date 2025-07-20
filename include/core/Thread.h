////////////////////////////////////////////////////////////////////////////////////////////////////
// Name:        Thread.h
// Library:     Jameo Core Library
// Purpose:     Thread Management
//
// Author:      Uwe Runtemund (2013-today)
// Modified by:
// Created:     30.05.2013
//
// Copyright:   (c) 2013 Jameo Software, Germany. https://jameo.de
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

#ifndef jm_Thread_h
#define jm_Thread_h

#if defined(JM_MACOS) || defined(JM_IOS)

#include <pthread.h>

#endif

#include "Types.h"
#include "Object.h"

#if defined(JM_MACOS) || defined(JM_IOS) || defined(JM_LINUX) || defined(JM_ANDROID)
extern "C" void* StartThread(void* arg);
#elif defined JM_WINDOWS
extern "C" unsigned long __stdcall StartThread(void* lpParameter);
#endif


/*!
 \defgroup thread Mutex and Threads

 \brief A collection of classes for a unified interface for mutex and threads.
 */

namespace jm
{
   /*!
    \brief Thread implementation
    \ingroup thread
    */
   class DllExport Thread: public Object
   {
         // This method is needed for starting the thread
#if defined(JM_MACOS) || defined(JM_IOS) || defined(JM_LINUX) || defined(JM_ANDROID)
         friend void* ::StartThread(void* arg);
#elif defined JM_WINDOWS
         friend unsigned long __stdcall ::StartThread(void* lpParameter);
#endif

      private:

         //macOS, iOS
#if defined(JM_MACOS) || defined(JM_IOS) || defined(JM_LINUX) || defined(JM_ANDROID)

         pthread_t thread = 0;
         pthread_condattr_t attrc;
         pthread_cond_t cond;
         pthread_mutex_t criticalSection;
         pthread_mutexattr_t attra;

#elif defined JM_WINDOWS

         unsigned long mThreadID = 0;
         void* mHandle = nullptr;
         void* mCriticalSection = nullptr;

#endif
         /*!
          \brief Status indicating whether this thread is active and running.
          If the thread is running and this variable becomes false, an exception will be thrown in this thread.
          */
         bool alive = false;

         /*!
          \brief This method must be implemented by derived classes. It is the main method
          that runs on the new thread. It is executed when the thread is started.
          */
         virtual void run() = 0;

      protected:

         /*!
          \brief  This method blocks this thread from accessing other threads to mark a critical section
         that must not be interrupted or to avoid race conditions.
          */
         void lock();

         /*!
          \brief This method releases the lock held by this thread, allowing other threads to access
          the critical section. This is used to mark a critical section that must not be interrupted
          or to avoid race conditions.
          */
         void unlock();

      public:

         /*!
          \brief Checks if the current thread is the main thread.
          */
         static bool isMainThread();

         /*!
          \brief Default constructor.
          */
         Thread();

         /*!
          \brief Destructor
          */
         ~Thread() override;

         /*!
          \brief This method starts the thread.
         */
         void start();

         /*!
          \brief This method puts the thread to sleep and wakes it up after the specified time has elapsed.
          The thread can also be woken up externally before the time has elapsed.
          \param duration The time duration (in milliseconds) for which the thread should sleep.
          */
         void sleep(int64 duration);

         /*!
          \brief This method puts the thread to sleep. The thread must be externally awakened.
          */
         void sleep();

         /*!
          \brief If the thread is sleeping, it will be woken up by calling this method.
          */
         void wakeUp();

         /*!
         \brief This method terminates the execution of this thread.
         It waits for the thread to finish execution ???
         */
         void interrupt();

         /*!
          \brief This method should be called regularly to check if the thread should be terminated.
          If this method returns false, the thread should be terminated.
          \return Returns true if the thread should continue running.
          */
         bool isAlive();

         /*!
          \brief Set the name of the thread.
          \note This method is intended for help debugging.
          */
         void setName(const String& name);

   };

}


#endif
