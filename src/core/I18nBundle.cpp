////////////////////////////////////////////////////////////////////////////////////////////////////
// Name:        I18NBundle.cpp
// Library:     Jameo Core Library
// Purpose:     Helper Class for Internationalization
//
// Author:      Uwe Runtemund (2012-today)
// Modified by:
// Created:     03.06.2013
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

#include "Precompiled.hpp"

using namespace jm;

I18nBundle* gDefaultTranslation = NULL;

I18nBundle::I18nBundle(const String& language)
{
   mLanguage = language;
}

void I18nBundle::appendMo(File file)
{
   if(!file.exists())
   {
      String appID, name;
      System::log(Tr("Cannot find translation file: %1 %2")
                  .arg(file.path())
                  .arg(mLanguage),
                  kLogError);

      return;
   }

   // Read file from disk
   Integer length = file.size();
   ByteArray buf = ByteArray(length, 0);
   VxfErrorStatus status = file.open(kFmRead);
   if(status != eOK)
   {
      System::log(Tr("Cannot open file: %1").arg(file.path()), kLogError);
      return;
   }
   Integer check = file.Stream::readFully(buf);
   file.close();

   if(check != length)
   {
      System::log(Tr("File not fully read: %1").arg(file.path()), kLogError);
      return;
   }
   uint8* buffer = (uint8*)buf.constData();

   // Process content
   uint32 magic = jm::DeserializeLEUInt32(buffer, 0);
   uint32 version = jm::DeserializeLEUInt32(buffer, 4);
   uint32 stringCount = jm::DeserializeLEUInt32(buffer, 8);
   uint32 origOffset = jm::DeserializeLEUInt32(buffer, 12);
   uint32 transOffset = jm::DeserializeLEUInt32(buffer, 16);

   if(magic != 0x950412de)
   {
      System::log(Tr("File magic wrong: %1").arg(file.path()), kLogError);
      return;
   }
   if(version != 0)
   {
      System::log(Tr("MO file version not supported: %1").arg(file.path()), kLogError);
      return;
   }

   struct Record
   {
      uint32 origOffset = 0;
      uint32 origLength = 0;
      uint32 transOffset = 0;
      uint32 transLength = 0;
   };

   std::vector<Record>records;

   // Read the string records
   uint32 offset = 0;
   for(uint32 a = 0; a < stringCount; a++)
   {
      Record rec;
      rec.origLength = jm::DeserializeLEUInt32(buffer, origOffset + offset);
      rec.origOffset = jm::DeserializeLEUInt32(buffer, origOffset + offset + 4);
      rec.transLength = jm::DeserializeLEUInt32(buffer, transOffset + offset);
      rec.transOffset = jm::DeserializeLEUInt32(buffer, transOffset + offset + 4);

      offset += 8;

      records.push_back(rec);
   }

   // Process the records
   for(Integer index = 0; index < stringCount; index++)
   {
      const Record rec = records[index];
      const jm::String orig = jm::String((char*)&buffer[rec.origOffset], rec.origLength);
      const jm::String trans = jm::String((char*)&buffer[rec.transOffset], rec.transLength);
      setValue(orig, trans);
   }
}

String I18nBundle::translate(const String& key) const
{
   return value(key, key);
}


I18nBundle* I18nBundle::getDefault()
{
   return gDefaultTranslation;
}

void I18nBundle::initDefault()
{
   jm::String language = System::language();
   gDefaultTranslation = new I18nBundle(language);

   // Append Data
   gDefaultTranslation->appendMo(transFileByBundleId(jm::kEmptyString,
                                 gDefaultTranslation->mLanguage));
}

jm::File I18nBundle::transFileByBundleId(const String& filename,
      const String& lang)
{
   String language = lang;

   if(language.size() == 0)language = System::language();

   language = language.replace('-', '_');

   // Resource of translations
   const File resDir = ResourceDir(jm::System::bundleId());
   const File translationDir = File(resDir, "translations");

   // Bundle-id + language
   File translationFile = File(translationDir, filename + "." + language + ".mo");

   // Maybe without bundle id ?
   if(translationFile.exists() == false)
   {
      translationFile = File(translationDir, language + ".mo");
   }
   else return translationFile;

   // Maybe without region?
   if(translationFile.exists() == false && language.indexOf('_') > 0)
   {
      language = language.substring(0, language.indexOf('_'));
      translationFile = File(translationDir, filename + "." + language + ".mo");
   }
   else return translationFile;

   // Maybe without region and without bundle id?
   if(translationFile.exists() == false && language.indexOf('_') > 0)
   {
      language = language.substring(0, language.indexOf('_'));
      translationFile = File(translationDir, language + ".mo");
   }
   else return translationFile;

   return translationFile;
}
