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
    \brief The Preferences class abstracts the reading and writing of properties in a preferences file.
    The file should have the extension .properties.
    */
   class DllExport Preferences: public Hashtable
   {
      public:

          /*!
          \brief Constructor
          */
         Preferences();

          /*!
          \brief Destructor. Deletes all entries in the hashtable.
          */
        ~Preferences() override;

          /*!
           \brief This method reads the data from the file.
           \param file The file containing the properties.
           \throws Exception if the file is not found or is corrupted.
           */
         void load(File file);

          /*!
           \brief This method writes the preferences to the file.
           \param file The name of the file where the properties will be saved.
           \throws Exception if the file cannot be written.
           */
         void save(File file);

          /*!
           \brief Check if the property is present.
           \param key The key of the property to check.
           \return true if the property is present, false otherwise.
           */
         bool hasValue(const String& key)const;

          /*!
           \brief Sets the property. Essentially calls the Put() method of Hashtable, but ensures that strings are used.
           \param key The property key.
           \param value The value.
           */
         void setValue(const String& key, const String& value);

          /*!
           \brief Sets the property. Essentially calls the Put() method of Hashtable, but ensures that strings are used.
           \param key The property key.
           \param value The value.
           */
         void setValue(const String& key, int64 value);

          /*!
           \brief Sets the property. Essentially calls the Put() method of Hashtable, but ensures that strings are used.
           \param key The property key.
           \param value The value.
           */
         void setValue(const String& key, double value);

          /*!
           \brief Sets the property. Essentially calls the Put() method of Hashtable, but ensures that strings are used.
           \param key The property key.
           \param value The value.
           */
         void setValue(const String& key, bool value);

          /*!
           \brief Returns the desired property.
           \param key The property key.
           \return The value of the property.
           */
         String value(const String& key) const;

          /*!
           \brief Returns the desired property.
           \param key The property key.
           \param defaultValue The value of the property if it is not found.
           \return The value of the property.
           */
         String value(const String& key, const String& defaultValue) const;

          /*!
           \brief Returns the desired property.
           \param key The property key.
           \param defaultValue The value of the property if it is not found.
           \return The value of the property.
           */
         int64 valueInt(const String& key, int64 defaultValue) const;

          /*!
           \brief Returns the desired property.
           \param key The property key.
           \param defaultValue The value of the property if it is not found.
           \return The value of the property.
           */
         double valueDouble(const String& key, double defaultValue) const;

          /*!
           \brief Returns the desired property.
           \param key The property key.
           \param defaultValue The value of the property if it is not found.
           \return The value of the property.
           */
         bool valueBool(const String& key, bool defaultValue) const;
   };

}


#endif
