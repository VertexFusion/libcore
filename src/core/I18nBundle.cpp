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

#include "Precompiled.h"

using namespace jm;

I18nBundle* gDefaultTranslation = NULL;

I18nBundle::I18nBundle(const String &language)
{
   mLanguage = language;
}

void I18nBundle::AppendMO(File file)
{
   if(!file.Exists())
   {
      String appID, name;
      System::Log(Tr("Cannot find translation file: %1 %2")
                  .Arg(file.GetPath())
                  .Arg(mLanguage),
                  kLogError);

      return;
   }

   // Read file from disk
   Integer length = file.Length();
   ByteArray buf = ByteArray(length, 0);
   file.Open(kFmRead);
   Integer check = file.Stream::ReadFully(buf);
   file.Close();

   if(check != length)
   {
      System::Log(Tr("File not fully read: %1").Arg(file.GetPath()), kLogError);
      return;
   }
   uint8* buffer = (uint8*)buf.ConstData();

   // Process content
   uint32 magic = jm::DeserializeLEUInt32(buffer, 0);
   uint32 version = jm::DeserializeLEUInt32(buffer, 4);
   uint32 stringCount = jm::DeserializeLEUInt32(buffer, 8);
   uint32 origOffset = jm::DeserializeLEUInt32(buffer, 12);
   uint32 transOffset = jm::DeserializeLEUInt32(buffer, 16);

   if(magic != 0x950412de)
   {
      System::Log(Tr("File magic wrong: %1").Arg(file.GetPath()), kLogError);
      return;
   }
   if(version != 0)
   {
      System::Log(Tr("MO file version not supported: %1").Arg(file.GetPath()), kLogError);
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
      const jm::String orig = jm::String(&buffer[rec.origOffset], rec.origLength);
      const jm::String trans = jm::String(&buffer[rec.transOffset], rec.transLength);
      SetPreference(orig, trans);
   }
}

String I18nBundle::Translate(const String& key) const
{
   return GetPreference(key, key);
}


I18nBundle* I18nBundle::GetDefault()
{
   return gDefaultTranslation;
}

void I18nBundle::InitDefault()
{
   jm::String language = System::GetLanguage();
   gDefaultTranslation = new I18nBundle(language);

   // Append Data
   gDefaultTranslation->AppendMO(GetTansFileByBundleId(jm::kEmptyString,
                                                       gDefaultTranslation->mLanguage));
}

jm::File I18nBundle::GetTansFileByBundleId(const String &filename,
                                           const String& lang)
{
   String language = lang;

   if(language.Length() == 0)language = System::GetLanguage();

   language = language.Replace('-', '_');

   // Resource of translations
   const File resDir = ResourceDir(jm::System::GetBundleId());
   const File translationDir = File(resDir, "translations");

   // Bundle-id + language
   File translationFile = File(translationDir, filename + "." + language + ".mo");

   // Maybe without bundle id ?
   if(translationFile.Exists() == false)
   {
      translationFile = File(translationDir, language + ".mo");
   }
   else return translationFile;

   // Maybe without region?
   if(translationFile.Exists() == false && language.IndexOf('_') > 0)
   {
      language = language.Substring(0, language.IndexOf('_'));
      translationFile = File(translationDir, filename + "." + language + ".mo");
   }
   else return translationFile;

   // Maybe without region and without bundle id?
   if(translationFile.Exists() == false && language.IndexOf('_') > 0)
   {
      language = language.Substring(0, language.IndexOf('_'));
      translationFile = File(translationDir, language + ".mo");
   }
   else return translationFile;

   return translationFile;
}
