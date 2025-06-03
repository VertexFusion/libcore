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

#if defined(JM_MACOS) || defined(JM_IOS)
#include <pthread.h>
#elif defined(JM_LINUX) || defined(JM_ANDROID)
#include <pthread.h>
#elif defined JM_WINDOWS
//Keine Threadbib
#endif

#include "String.h"

namespace jm
{
   /*!
    \brief This class represents an exception that can be "thrown" in case of unexpected errors.
    \warning Do not use in new implementations
    */
   class DllExport Exception: public Object
   {
      public:

         /*!
          \brief Constructor
          \param message The error message for the developer or user.
          */
         explicit Exception(const String& message);

         /*!
          \brief Constructor
          */
         Exception(const Exception& other);

         /*!
          \brief Destructor
          */
         ~Exception() noexcept override = default;

         /*!
          \brief Returns the error message.
          */
         String errorMessage() const;

         /*!
          \brief Writes the stack trace into the std::cout
          */
         void printStackTrace() const;

         /*!
          \brief Returns the stack trace of the exception. Useful to find the origin of the exception.
          */
         String GetStrackTrace() const;

      private:

         //! The error message.
         String mMessage;

         //! The thread id
#if defined(JM_MACOS) || defined(JM_IOS) || defined(JM_LINUX) || defined(JM_ANDROID)
         pthread_t tid;
#elif defined JM_WINDOWS
         // In Windows a thread id does not exist.
#endif

         // retrieve current stack addresses
         uint32 addrlen;

         StringList mSymbolList;

   };


}

#endif
