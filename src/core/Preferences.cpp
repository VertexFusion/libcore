////////////////////////////////////////////////////////////////////////////////////////////////////
// Name:        Preferences.cpp
// Library:     Jameo Core Library
// Purpose:     Implementation of hashtable based property container
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

#include "Precompiled.h"

using namespace jm;

Preferences::Preferences(): Hashtable()
{
}


Preferences::~Preferences()
{
   Iterator* i = Keys();
   while(i->HasNext())
   {
      String* s = static_cast<String*>(i->Next());
      String* p = static_cast<String*>(Get(*s));
      delete p;
   }
   delete i;
}


void Preferences::Load(File file)
{
   if(!file.Exists())return;

   Integer l = file.Length();
   ByteArray buffer = ByteArray(l, 0);
   file.Open(kFmRead);
   Integer check = file.Stream::ReadFully(buffer);
   file.Close();
   String data = String(buffer);

   if(check != l)throw new Exception("Property file incomplete loaded.");

   StringTokenizer* st = new StringTokenizer(data, "\r\n", false);

   //Zeilenweise einlesen
   while(st->HasMoreTokens())
   {
      String line = st->NextToken();

      Integer pos = line.IndexOf('=');
      if(pos > 0)
      {
         String key = line.Substring(0, pos).Trim();
         String value = line.Substring(pos + 1).Trim();

         //Prüfe auf Zeilenumbruch
         while((pos = value.IndexOf("\\n")) > 0)
         {
            value = value.Substring(0, pos) + "\n" + value.Substring(pos + 2);
         }

         //Ersetze
         Integer index = 0;
         while(index < value.Length())
         {
            Char c = value.CharAt(index);

            if(c == '\\' && index + 1 < value.Length())
            {
               Char d = value.CharAt(index + 1);
               if(d == 't')
               {
                  value.SetCharAt(index, '\t');
                  value.DeleteCharAt(index + 1);
               }
               if(d == '\\')
               {
                  value.DeleteCharAt(index + 1);
               }
            }
            index++;
         }

         SetPreference(key, value);
      }
   }
   delete st;

}

void Preferences::Store(File file)
{
   try
   {
      if(file.Exists() == false)
      {
         jm::File dir = jm::File(file.GetParent());
         if(dir.Exists() == false)dir.MakeDirectory();
      }
      file.Open(kFmWrite);

      Iterator* keys = Keys();

      while(keys->HasNext())
      {
         String key = *static_cast<String*>(keys->Next());
         String value = GetPreference(key);

         //Ersetzungen
         //Ersetze
         uint32 index = 0;
         while(index < value.Length())
         {
            Char c = value.CharAt(index);

            if(c == '\\')
            {
               value.Insert(index + 1, '\\');
               index++;
            }
            else if(c == '\t')
            {
               value.SetCharAt(index, '\\');
               value.Insert(index + 1, 't');
               index++;
            }
            index++;
         }

         //Zeile bilden
         key.Append('=');
         key.Append(value);
         key.Append(String::LineSeparator());
         ByteArray cstr = key.ToCString();
         file.Write((uint8*)cstr.ConstData(), cstr.Size());
      }
      delete keys;

      file.Close();
   }
   catch(Exception* e)
   {
      e->PrintStackTrace();
      System::Log("Cannot save property file: " + file.GetAbsolutePath(), kLogError);
      delete e;
   }
}

bool Preferences::HasPreference(const String& key)const
{
   return Get(key) != NULL;
}

void Preferences::SetPreference(const String &key, const String &value)
{
   String tmp = value;
   tmp = tmp.ReplaceAll("\r\n", "\\n");
   tmp = tmp.ReplaceAll("\r", "\\n");
   tmp = tmp.ReplaceAll("\n", "\\n");
   String* actual = new String(tmp);
   String* old = static_cast<String*>(Put(key, actual));
   if(old != NULL)delete old;
}

void Preferences::SetPreference(const String &key, int32 value)
{
   SetPreference(key, String::ValueOf(value));
}


void Preferences::SetPreference(const String &key, bool value)
{
   SetPreference(key, static_cast<String>(value ? "true" : "false"));
}

String Preferences::GetPreference(const String &key) const
{
   String* result = (String*)Get(key);
   if(result == NULL)return kEmptyString;
   return *result;
}

String Preferences::GetPreference(const String &key, String const &defaultValue) const
{
   String* result = static_cast<String*>(Get(key));
   if(result == NULL)return defaultValue;
   return *result;
}

int32 Preferences::GetPreferenceInt(const String &key, int32 defaultValue) const
{
   String result = GetPreference(key);

   if(result.Length() == 0)return defaultValue;

   int32 value = defaultValue;
   try
   {
      value = static_cast<int32>(Integer::ValueOf(result));
   }
   catch(Exception* e)
   {
      delete e;
   }

   return value;
}

bool Preferences::GetPreferenceBool(const String &key, bool defaultValue) const
{
   String result = GetPreference(key);

   if(result.Length() == 0)return defaultValue;

   return result.Equals("true");
}
