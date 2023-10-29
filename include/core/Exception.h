////////////////////////////////////////////////////////////////////////////////////////////////////
// Name:        Exception.h
// Library:     Jameo Core Library
// Purpose:     Iterator Interface
//
// Author:      Uwe Runtemund (2013-today)
// Modified by:
// Created:     16.01.2013
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

#ifndef jm_Exception_h
#define jm_Exception_h

#ifdef __APPLE__ //macOS
#include <pthread.h>
#elif defined __linux__//Linux
#include <pthread.h>
#elif defined _WIN32//Windows
//Keine Threadbib
#endif

#include "String.h"

namespace jm
{

	/*!
	 \brief This class represents an exception that can be "thrown" in case of unexpected errors.
	 \deprected We want to do without it in the future because memory management does not work well
	 with it.
	 */
	class DllExport Exception: public Object
	{
		private:

			/*!
			 @internal
			 \brief Die Fehlermeldung, die dem Anwender angezeigt werden soll.
			 */
			String message;

			/*!
			 @internal
			 \brief Die Thread-ID
			 */
			#ifdef __APPLE__ //macOS
			pthread_t tid;
			#elif defined __linux__//Linux
			pthread_t tid;
			#elif defined _WIN32//Windows
			//Keine Threadbib
			#endif


			// retrieve current stack addresses
			uint32 addrlen;

			String* symbollist;


		public:

			/*!
			 \brief Konstruktor
			 \param message Die Fehlermeldung, die dem Anwender angezeigt werden soll.
			 */
			Exception(const String message);

			/*!
			 \brief Destructor
			 */
			~Exception();

			/*!
			 \brief Gibt die Fehlermeldung zurück.
			 \return Die Fehlermeldung
			 */
			String GetErrorMessage() const;

			/*!
			 \brief Schreibt den Stacktrace in den Fehlerstream
			 */
			void PrintStackTrace() const;

			/*!
			 \brief Gibt den Stacktrace als String zurück
			 */
			String GetStrackTrace() const;

	};


}

#endif
