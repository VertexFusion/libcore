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

   enum LogLevel
   {
      kLogDebug,
      kLogInformation,
      kLogWarning,
      kLogError
   };

   class DllExport System
   {

      public:

         /*!
          \brief This method returns the language of the system that is currently set.
          The programme can use this variable to decide which language it should display.
          \return The string has the form "de-DE"
          */
         static String GetLanguage();

         /*!
          \brief Diese Methode gibt den Benutzernamen des aktuell angemeldeten Benutzers zurück.
          Diese Funktion ermittelt dabei den "Systemnamen" BenutzerID. In der Regel ist dies der
          Account-Name.
          */
         static String GetUserID();

         /*!
          \brief Diese Methode gibt den Benutzernamen des aktuell angemeldeten Benutzers zurück.
          Diese Funktion ermittelt dabei den Namen in natürlicher Schreibweise. Er hat dann in der
          Regel
          Leerzeichen und ist nicht mit dem Accountnamen identisch.
          */
         static String GetUserFullName();

         /*!
          \brief Diese Methode muss als erstes aufgerufen werden, damit wichtige statische
          Objekte eingerichtet werden
          \note Beim Beenden ist \c Init() aufzurufen
          */
         static void Init(const jm::String &bundleId);

         /*!
          \brief Diese Methode räumt statische Systemobjekte auf. Nach dieser Methode muss das
          Programm beendet werden, weil es sonst bei Verwendung von Objekten dieser Bibliothek zu
          unerwünschten Nebeneffekte kommen kann.
          \note Beim Starten ist \c Init() aufzurufen
          */
         static void Quit();

         /*!
          \brief Turns logging of timestamp on or of.
          \param status If \c true the timestamp will be logged. Otherwise false.
          */
         static void LogEnableDate(bool status);

         /*!
          \brief Set the minimum level where the level label will be logged.
          \param logLevel The minimum level.
          */
         static void LogEnableLabel(LogLevel logLevel);

         /*!
          \brief Loggt eine Nachricht mit...
          */
         static void Log(const String &message, LogLevel logLevel);

         /*!
          \brief Gibt die letzte Fehlermeldung zurück
          */
         static const String& GetLastErrorMessage();

         /*!
          \brief Diese Methode lädt eine dynamische Bibliothek. Unter macOS *.dylib, Windows *.dll
          und Linus *.so
          \param file Datei der Bibliothek.
          \return Pointer auf die Bibliothek oder NULL, wenn sie nicht gefunden wurde.
          */
         static void* LoadDynamicLibrary(File* file);

         /*!
          \brief Diese Methode gibt eine geladene dynamische Bibliothek wieder frei
          */
         static void UnloadDynamicLibrary(void* library);

         /*!
          \brief Diese Methode sicht nach Symbolen in der Bibliothekt
          \param library Referenz auf die Bilbiothek, in der gesucht werden soll.
          \param name Name des Symbols
          */
         static void* FindSymbol(void* library, const String &name);

         static AutoreleasePool* GetAutoreleasePool();

   };

}

#endif
