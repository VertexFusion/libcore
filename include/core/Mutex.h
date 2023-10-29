////////////////////////////////////////////////////////////////////////////////////////////////////
// Name:        Mutex.h
// Library:     VertexFusion Library
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

#ifndef jm_Synchronized_h
#define jm_Synchronized_h

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
			//the default constructor
			Mutex();

			//destructor
			~Mutex();

			//lock
			void Lock();

			//unlock
			void Unlock();

			//sleep
			void Sleep();

			//wake Up
			void WakeUp();

		private:
			#if defined(__APPLE__) || defined(__linux__)   //macOS & Linux
			pthread_mutex_t criticalSection;
			pthread_mutexattr_t attr;
			pthread_condattr_t attrc;
			pthread_cond_t cond;

			#elif defined _WIN32//Windows

			//Unter Windows 7 und 10 liefert sizeof(CRITICAL_SECTION) 40 Bytes
			uint8 mCriticalSection[40];

			#endif
	};


	//synchronization controller object
	class DllExport Lock
	{
		public:
			//the default constructor
			Lock(Mutex &mutex);

			//the destructor
			~Lock();

			//report the state of locking when used as a boolean
			operator bool () const
			{
				return locked;
			}

			//unlock
			void SetUnlock();

		private:
			Mutex &mutex;
			bool locked;

	};

}



#endif
