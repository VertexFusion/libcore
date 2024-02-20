////////////////////////////////////////////////////////////////////////////////////////////////////
// Name:        Preferences.h
// Library:     Jameo Core Library
// Purpose:     Specialization of a hash table for storing and handling application properties
//
// Author:      Uwe Runtemund (2013-today)
// Modified by:
// Created:     23.08.2013
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

#ifndef jm_Preferences_h
#define jm_Preferences_h

#include "Hashtable.h"

namespace jm
{

   class File;

   /*!
    \brief Die Klasse Preferences abstrahiert das Lesen und Schreiben von Eigenschaften in einer Preferences-Datei.
    Die Datei sollte die Endung .properties haben
    */
   class DllExport Preferences: public Hashtable
   {
      public:

         /*!
         \brief Konstruktor
         */
         Preferences();

         /*!
         \brief Destructor Löscht alle Einträge in der Hashtabelle
         */
         virtual ~Preferences();

         /*!
          \brief Diese Methode liest die Daten aus der Datei ein
          \param file Die Datei mit den Eigenschaften.
          @throws Exception, wenn die Datei nicht gefunden wurde, oder fehlerhaft ist.
          */
         void Load(File file);

         /*!
          \brief Diese Methode schreibt die Preferences in die Datei.
          \param file Name der Datei, in der die Eigenschaften gespeichert werden
          @throws Exception, wenn die Datei nicht geschrieben werden kann
          */
         void Store(File file);

         /*!
          \brief This method check, if the property is present or not.
          \param key The key of the property of interest.
          */
         bool HasPreference(const String &key)const;

         /*!
          \brief Legt die Eigenschaft fest. Ruft defacto Put() der Hashtable auf, stellt aber sicher, dass Strings verwendet werden.
          \param key Der Property-Schlüssel
          \param value Der Wert
          */
         void SetPreference(const String &key, const String &value);

         /*!
          \brief Legt die Eigenschaft fest. Ruft defacto Put() der Hashtable auf, stellt aber sicher, dass Strings verwendet werden.
          \param key Der Property-Schlüssel
          \param value Der Wert
          */
         void SetPreference(const String &key, int32 value);

         /*!
          \brief Legt die Eigenschaft fest. Ruft defacto Put() der Hashtable auf, stellt aber sicher, dass Strings verwendet werden.
          \param key Der Property-Schlüssel
          \param value Der Wert
          */
         void SetPreference(const String &key, bool value);

         /*!
          \brief Gibt die gewünschte Eigenschaft zurück
          \param key Die Eigenschaft
          */
         String GetPreference(const String &key) const;

         /*!
          \brief Gibt die gewünschte Eigenschaft zurück
          \param key Die Eigenschaft
          \param defaultValue Der Eigenschaftswert, wenn das Property nicht gefunden wurde.
          */
         String GetPreference(const String &key, const String &defaultValue) const;

         /*!
          \brief Gibt die gewünschte Eigenschaft zurück
          \param key Die Eigenschaft
          \param defaultValue Der Eigenschaftswert, wenn das Property nicht gefunden wurde.
          */
         int32 GetPreferenceInt(const String &key, int32 defaultValue) const;

         /*!
          \brief Gibt die gewünschte Eigenschaft zurück
          \param key Die Eigenschaft
          \param defaultValue Der Eigenschaftswert, wenn das Property nicht gefunden wurde.
          */
         bool GetPreferenceBool(const String &key, bool defaultValue) const;
   };

}


#endif
