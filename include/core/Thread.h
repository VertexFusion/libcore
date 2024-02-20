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

#ifdef __APPLE__//macOS, iOS

#include <pthread.h>

#endif

#include "Types.h"
#include "Object.h"

#if defined __APPLE__ || defined __linux__
extern "C" void* StartThread(void* arg);
#elif defined _WIN32
extern "C" unsigned long __stdcall StartThread(void* lpParameter);
#endif



namespace jm
{
   class DllExport Thread: public Object
   {
         //Diese Methode wird für das Starten der Threads gebraucht
         #if defined __APPLE__ || defined __linux__
         friend void* ::StartThread(void* arg);
         #elif defined _WIN32
         friend unsigned long __stdcall ::StartThread(void* lpParameter);
         #endif


      private:

         //macOS, iOS
         #if defined __APPLE__ || defined __linux__

         pthread_t thread;
         pthread_condattr_t attrc;
         pthread_cond_t cond;
         pthread_mutex_t criticalSection;
         pthread_mutexattr_t attra;

         #elif defined _WIN32

         unsigned long mThreadID;
         void* mHandle;
         void* mCriticalSection;

         #endif
         /*!
          \brief Status, wenn diese Thread aktiv ist und läuft. Wenn der Thread läuft und diese
         Variable falsch wird, dann wird eine Exception auf diesem Thread ausgelöst.
          */
         bool alive;

         /*!
          \brief Diese Methode muss von den beerbten Klassen implementiert werden. Sie ist die
         Hauptmethode auf dem neuen Thread. Sie wird ausfegührt, wenn der Thread gestartet wurde.
          */
         virtual void Run() = 0;

      protected:

         /*!
          \brief Diese Methode block diesen Thread für Zugriffe auf anderen Threads, um einen
         kritischen Abschnitt zu markieren, der nicht unterbrochen werden darf, oder um
         Racingconditions zu vermeiden.
          */
         void Lock();

         /*!
          \brief Diese Methode beendet die Sperre dieses Threads für Zugriffe auf anderen Threads,
         um einen Kritischen Abschnitt zu markieren, der nicht unterbrochen werden darf, oder um
         Racingconditions zu vermeiden.
          */
         void Unlock();

      public:

         /*!
          \brief Prüft. ob man auf dem Mainthread ist
          */
         static bool IsMainThread();

         /*!
          \brief Standardkonstruktor
          */
         Thread();


         /*!
          \brief Standarddestruktor
          */
         virtual ~Thread();

         /*!
          \brief Diese Methode startet den Thread.
         */
         void Start();

         /*!
          \brief Diese Methode legt den Thread schlafen und lässt ihn
          nach Ablauf der Zeit wieder aufwachen.
          Der Thread wacht auch auf, wenn er von extern aufgeweckt wird.
          */
         void Sleep(int millis);

         /*!
          \brief Diese Methode legt den Thread schlafen.
          Der Thread muss von extern neu aufgerwacht werden.
          */
         void Sleep();

         /*!
          \brief Wenn der Thread schläft, wird er mit dem Aufruf dieser Methode
          */
         void WakeUp();

         /*!
         \brief Diese Methode beendet die Ausführung dieses Threads.
         Es wird auf das Beenden gewartet?
         */
         void Interrupt();

         /*!
         \brief Um einen Thread kontrolliert zu beenden, ist diese Methode regelmäßig abzufragen.
          Wenn diese Methode falsch zurückgibt, soll der Thread beendet werden.
         */
         bool IsAlive();

         /*!
          \brief Set the name of the thread.
          \note This method is intended for help debugging.
          */
         void SetName(const String& name);

   };

}


#endif
