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
   Iterator* i = keys();
   while(i->hasNext())
   {
      String* s = static_cast<String*>(i->next());
      String* p = static_cast<String*>(get(*s));
      delete p;
   }
   delete i;
}


void Preferences::load(File file)
{
   if(!file.exists())return;

   Integer l = file.size();
   ByteArray buffer = ByteArray(l, 0);
   file.open(kFmRead);
   Integer check = file.Stream::readFully(buffer);
   file.close();
   String data = String(buffer);

   if(check != l)throw new Exception("Property file incomplete loaded.");

   StringTokenizer* st = new StringTokenizer(data, "\r\n", false);

   //Zeilenweise einlesen
   while(st->hasNext())
   {
      String line = st->next();

      Integer pos = line.indexOf('=');
      if(pos > 0)
      {
         String key = line.substring(0, pos).trim();
         String value = line.substring(pos + 1).trim();

         //Prüfe auf Zeilenumbruch
         while((pos = value.indexOf("\\n")) > 0)
         {
            value = value.substring(0, pos) + "\n" + value.substring(pos + 2);
         }

         //Ersetze
         Integer index = 0;
         while(index < value.size())
         {
            Char c = value.charAt(index);

            if(c == '\\' && index + 1 < value.size())
            {
               Char d = value.charAt(index + 1);
               if(d == 't')
               {
                  value.setCharAt(index, '\t');
                  value.deleteCharAt(index + 1);
               }
               if(d == '\\')
               {
                  value.deleteCharAt(index + 1);
               }
            }
            index++;
         }

         setValue(key, value);
      }
   }
   delete st;

}

void Preferences::save(File file)
{
   try
   {
      if(file.exists() == false)
      {
         jm::File dir = jm::File(file.parent());
         if(dir.exists() == false)dir.makeDirectory();
         file.createNewFile();
      }
      VxfErrorStatus status = file.open(kFmWrite);
      if(status != eOK)
      {
         jm::System::log(Tr("cannot store preferences in '%1'").arg(file.absolutePath()), jm::kLogError);
         return;
      }

      Iterator* keyiter = keys();

      while(keyiter->hasNext())
      {
         String key = *static_cast<String*>(keyiter->next());
         String val = value(key);

         //Ersetzungen
         //Ersetze
         uint32 index = 0;
         while(index < val.size())
         {
            Char c = val.charAt(index);

            if(c == '\\')
            {
               val.insert(index + 1, '\\');
               index++;
            }
            else if(c == '\t')
            {
               val.setCharAt(index, '\\');
               val.insert(index + 1, 't');
               index++;
            }
            index++;
         }

         //Zeile bilden
         key.append('=');
         key.append(val);
         key.append(String::lineSeparator());
         ByteArray cstr = key.toCString();
         file.write((uint8*)cstr.constData(), cstr.size());
      }
      delete keyiter;

      file.close();
   }
   catch(Exception* e)
   {
      e->PrintStackTrace();
      System::log("Cannot save property file: " + file.absolutePath(), kLogError);
      delete e;
   }
}

bool Preferences::hasValue(const String& key)const
{
   return get(key) != NULL;
}

void Preferences::setValue(const String& key, const String& value)
{
   String tmp = value;
   tmp = tmp.replaceAll("\r\n", "\\n");
   tmp = tmp.replaceAll("\r", "\\n");
   tmp = tmp.replaceAll("\n", "\\n");
   String* actual = new String(tmp);
   String* old = static_cast<String*>(put(key, actual));
   if(old != NULL)delete old;
}

void Preferences::setValue(const String& key, int32 value)
{
   setValue(key, String::valueOf(value));
}


void Preferences::setValue(const String& key, bool value)
{
   setValue(key, static_cast<String>(value ? "true" : "false"));
}

String Preferences::value(const String& key) const
{
   String* result = (String*)get(key);
   if(result == NULL)return kEmptyString;
   return *result;
}

String Preferences::value(const String& key, String const& defaultValue) const
{
   String* result = static_cast<String*>(get(key));
   if(result == NULL)return defaultValue;
   return *result;
}

int32 Preferences::valueInt(const String& key, int32 defaultValue) const
{
   String result = value(key);

   if(result.size() == 0)return defaultValue;

   int32 value = defaultValue;
   try
   {
      value = static_cast<int32>(Integer::valueOf(result));
   }
   catch(Exception* e)
   {
      delete e;
   }

   return value;
}

bool Preferences::valueBool(const String& key, bool defaultValue) const
{
   String result = value(key);

   if(result.size() == 0)return defaultValue;

   return result.equals("true");
}
