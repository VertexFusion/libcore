////////////////////////////////////////////////////////////////////////////////////////////////////
// Name:        System.h
// Library:     Jameo Core Library
// Purpose:     System Things
//
// Author:      Uwe Runtemund (2013-today)
// Modified by:
// Created:     18.09.2013
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

#ifndef jm_System_h
#define jm_System_h

#include "AutoreleasePool.h"
#include "String.h"
#include "File.h"

namespace jm
{
   class Preferences;

   enum class LogLevel
   {
      kDebug,
      kInformation,
      kWarning,
      kError
   };

   class DllExport System
   {

      public:

         /*!
          \brief returns the global application settings
          */
         static Preferences* preferences();

         static void savePreferences();

         /*!
          \brief This method returns the language of the system that is currently set.
          The programme can use this variable to decide which language it should display.
          \return The string has the form "de-DE"
          */
         static String language();

          /*!
           \brief This method returns the username of the currently logged-in user.
           This function determines the "system name" UserID. Typically, this is the account name.
           */
         static String userId();

          /*!
           \brief This method returns the username of the currently logged-in user.
           This function determines the "natural language" user name. It usually contains spaces and
           is not identical to the account name.
           */
         static String userFullName();

         /*!
          \brief Returns the first available MAC address of the system.
          */
         static String macAddress1();

         /*!
          \brief Returns the bundleId which was provided on init()
          */
         static const String& bundleId();

          /*!
           \brief This method must be called first to set up important static objects
           \note When exiting, \c quit() must be called
           */
         static void init(const jm::String& bundleId);

          /*!
           \brief This method cleans up static system objects. After calling this method, the program
           must be terminated because otherwise unwanted side effects may occur when using objects
           from this library.
           \note \c init() must be called at startup
           */
         static void quit();

         /*!
          \brief Turns logging of timestamp on or of.
          \param status If \c true the timestamp will be logged. Otherwise false.
          */
         static void logEnableDate(bool status);

         /*!
          \brief Set the minimum level where the level label will be logged.
          \param logLevel The minimum level.
          */
         static void logEnableLabel(LogLevel logLevel);

          /*!
           \brief Logs a message.
           */
         static void log(const String& message, LogLevel logLevel);

          /*!
           \brief Returns the last error message
           */
         static const String& lastErrorMessage();

          /*!
           \brief This method loads a dynamic library. On macOS *.dylib, Windows *.dll, and Linux *.so
           \param file File of the library.
           \return Pointer to the library or NULL if it was not found.
           */
         static void* loadDynamicLibrary(File* file);

          /*!
           \brief This method unloads a loaded dynamic library
           */
         static void unloadDynamicLibrary(void* library);

          /*!
           \brief This method searches for symbols in the library.
           \param library Reference to the library to search in.
           \param name Name of the symbol.
           */
         static void* findSymbol(void* library, const String& name);

         /*!
          \brief This method returns the path to the autoreleased objects pool.
          */
         static AutoreleasePool* autoreleasePool();

   };

   //
   // System API (only on Android necessary)
   //
   jm::String osSystemLanguage();

}

#endif
