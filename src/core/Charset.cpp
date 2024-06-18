////////////////////////////////////////////////////////////////////////////////////////////////////
// Name:        Charset.cpp
// Library:     Jameo Core Library
// Purpose:     Implementation of Charset
//
// Author:      Uwe Runtemund (2013-today)
// Modified by:
// Created:     18.01.2013
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

uint16 Charset::gCharsetCount = 7;
Charset* Charset::gCharsets[7] = { new Charset(new UTF8Decoder()),
                                   new Charset("Windows-1252", new Windows1252Decoder()),
                                   new Charset("MacRoman", new MacRomanDecoder()),
                                   new Charset("UTF-16LE", new UTF16Decoder(false)),
                                   new Charset("UTF-16BE", new UTF16Decoder(true)),
                                   new Charset("RAW", new RawDecoder()),
                                   new Charset("ASCII", new RawDecoder())
                                 };

CharArray::CharArray()
{
   length = 0;
   buffer = NULL;
}

CharArray::CharArray(const CharArray &another)
{
   length = another.length;
   buffer = new Char[length];
   memcpy(buffer, another.buffer, length * 2);
}

CharArray::CharArray(Integer alength)
{
   length = alength;
   buffer = new Char[length];
}

CharArray::~CharArray()
{
   length = 0;
   if(buffer != NULL)
   {
      delete[] buffer;
      buffer = NULL;
   }
}

namespace jm
{
   CharArray &CharArray::operator=(const CharArray &another)
   {
      if(this == &another) return *this;
      if(buffer != NULL)delete[] buffer;
      length = another.length;
      buffer = new Char[length];
      memcpy(buffer, another.buffer, length * 2);

      return *this;
   }
}

Charset::Charset(CharsetDecoder* decoder): Object()
{
   mName.Append('U');
   mName.Append('T');
   mName.Append('F');
   mName.Append('-');
   mName.Append('8');
   mAlternatives = NULL;
   mAltCount = 0;
   mDecoder = decoder;
}

Charset::Charset(const char *name, CharsetDecoder* decoder): Object()
{
   uint32 index = 0;
   while(name[index] != 0)mName.Append(name[index++]);

   mAlternatives = NULL;
   mAltCount = 0;
   mDecoder = decoder;
}

Charset::Charset(const String &name, const String* alternatives, uint8 altCount, CharsetDecoder* decoder): Object()
{
   mName = name;
   mAlternatives = new String[mAltCount];
   mAltCount = altCount;
   for(uint8 a = 0; a < mAltCount; a++)mAlternatives[a] = alternatives[a];
   mDecoder = decoder;
}

Charset::~Charset()
{
   delete mDecoder;
   if(mAlternatives != NULL)delete [] mAlternatives;
   mDecoder = NULL;
   mAlternatives = NULL;
   mAltCount = 0;
}

String Charset::Name()
{
   return mName;
}

bool Charset::HasName(const String &name)
{
   if(mName.Equals(name))return true;

   for(uint8 a = 0; a < mAltCount; a++)
   {
      if(mAlternatives[a].Equals(name))return true;
   }

   return false;
}

CharArray Charset::Decode(const char* cString)
{
   return mDecoder->Decode(cString);
}

ByteArray Charset::Encode(const CharArray &string)
{
   return mDecoder->Encode(string);
}

Charset* Charset::ForName(const String &name)
{
   for(uint16 a = 0; a < Charset::gCharsetCount; a++)
   {
      if(Charset::gCharsets[a]->HasName(name))return Charset::gCharsets[a];
   }
   return NULL;
}

String Charset::Guess(const char* stream, Integer length)
{

   String encoding;

   #ifdef __APPLE__ //macOS
   encoding = "MacRoman";
   #elif defined __linux__ //Linux
   encoding = "UTF-8";
   #elif defined _WIN32 //Windows
   encoding = "Windows-1252";
   #endif

   //
   // If UTF markers are set, it's easy.
   //


   //UTF-16BE
   if(stream[0] == static_cast<char>(0xFE) &&
      stream[1] == static_cast<char>(0xFF))return "UTF-16BE";

   //UTF-16LE
   else if(stream[0] == static_cast<char>(0xFF) &&
           stream[1] == static_cast<char>(0xFE))return "UTF-16LE";

   //UTF-8
   else if(stream[0] == static_cast<char>(0xEF) &&
           stream[1] == static_cast<char>(0xBB) &&
           stream[2] == static_cast<char>(0xBF))return "UTF-8";

   //
   // Check for UTF-16
   //

   // It is possible that a UTF16 encoding without markers is present. The probability of this is
   // high if every second byte of "European" text is 0.
   uint16 frame = (uint16) std::min(4096, length.Int32());
   float count1 = 0;
   float count2 = 0;
   for(uint16 a = 0; a < frame; a++)
   {
      if(stream[a] == 0)
      {
         (a % 2 == 0) ? count1++ : count2++;
      }
   }

   if(count1 / (0.5f * frame) > 0.9)// Equivalent to 00 XX 00 XX 00 XX ...
   {
      return "UTF-16BE";
   }
   else if(count2 / (0.5 * frame) > 0.9)// Equivalent to XX 00 XX 00 XX 00 XX 00 ...
   {
      return "UTF-16LE";
   }

   // Undefined characters in Windows-1252
   if(encoding.Equals("Windows-1252"))
   {
      for(uint32 a = 0; a < length; a++)
      {
         switch(stream[a])
         {
            case 0x81:
            case 0x8D:
            case 0x8F:
            case 0x90:
            case 0x9D:
               // The above characters do not exist in Windows-1252! Use MacRoman.
               encoding = "MacRoman";
               break;

            default:
               ;//Tue nichts

         }
      }
   }

   // Assume ASCII if no byte is greater than 0x7F
   bool isASCII = true;
   for(uint32 a = 0; a < length; a++)
   {
      if(stream[a] > 0x7F)
      {
         isASCII = false;
         break;
      }
   }
   if(isASCII)return "ASCII";

   // TODO: Make a statistical analysis, or dictionary of non-ASCII characters
   // See also: http://stackoverflow.com/questions/4198804/how-to-reliably-guess-the-encoding-between-macroman-cp1252-latin1-utf-8-and

   return encoding;
}


Charset* Charset::GetDefault()
{
   return Charset::gCharsets[0];
}

void jm::InitCharsets()
{
   // Nothing needs to be done. Charsets are initialized automatically when loading.
   // However, the order is not clear....
}

void jm::QuitCharsets()
{
   for(uint16 a = 0; a < Charset::gCharsetCount; a++)delete Charset::gCharsets[a];
}

