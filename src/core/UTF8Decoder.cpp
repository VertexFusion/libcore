////////////////////////////////////////////////////////////////////////////////////////////////////
// Name:        UTF8Decoder.cpp
// Library:     Jameo Core Library
// Purpose:     Decoder for utf-8 encoded text.
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

UTF8Decoder::UTF8Decoder(): CharsetDecoder()
{

}

CharArray UTF8Decoder::Decode(const int8* cstring)
{
   //Bestimme Länge
   uint32 strLength = 0;
   uint32 cntV = 0;
   uint32 cntC = 0;
   uint32 start = 0;


   //Prüfe auf Steuerzeichen am Anfang des cstring. Wenn vorhanden ignoriere
   if((cstring[0]) == static_cast<int8>(0xFE) && cstring[1] == static_cast<int8>(0xFF))
   {
      throw new Exception("UTF-16 (BE) encoding detected.");
   }
   else if(cstring[0] == static_cast<int8>(0xFF) && cstring[1] == static_cast<int8>(0xFE))
   {
      throw new Exception("UTF-16 (LE) encoding detected.");
   }
   else if(cstring[0] == static_cast<int8>(0xEF) && cstring[1] == static_cast<int8>(0xBB) && cstring[2] == static_cast<int8>(0xBF))
   {
      cntC = 3;
      start = 3;
   }

   while(cstring[cntC] != 0)
   {
      uint8 c = cstring[cntC];

      if((c & 0x80) == 0)     //1 Zeichen
      {
         strLength++;
         cntC++;
      }
      else if((c & 0xE0) == 0xC0)     //2 Zeichen
      {
         strLength++;
         cntC += 2;
      }
      else if((c & 0xF0) == 0xE0)     //3 Zeichen
      {
         strLength++;
         cntC += 3;
      }
      else if((c & 0xF8) == 0xF0)     //4 Zeichen
      {
         strLength++;
         cntC += 4;
      }
      else
      {
         // In fact an encoding error, but we then take the byte as a single character
         strLength++;
         cntC++;
      }
   }
   cntC = start;

   CharArray ret = CharArray(strLength);
   uint16 d, e, f;
   while(cntV < strLength)
   {
      uint16 c = (uint8)cstring[cntC];

      if((c & 0x80) == 0)     //1 Zeichen
      {
         ret.buffer[cntV] = Char(c);
         cntV++;
         cntC++;
      }
      else if((c & 0xE0) == 0xC0)     //2 Zeichen
      {
         c = (c & 0x001F) << 6;
         d = cstring[cntC + 1] & 0x3F;
         ret.buffer[cntV] = Char(c | d);
         cntV++;
         cntC += 2;
      }
      else if((c & 0xF0) == 0xE0)     //3 Zeichen
      {
         c = (c & 0x000F) << 12;
         d = (cstring[cntC + 1] & 0x3F) << 6;
         e = cstring[cntC + 2] & 0x3F;
         ret.buffer[cntV] = Char(c | d | e);
         cntV++;
         cntC += 3;
      }
      else if((c & 0xF8) == 0xF0)     //4 Zeichen
      {
         c = (c & 0x0007) << 18;
         d = (cstring[cntC + 1] & 0x3F) << 12;
         e = (cstring[cntC + 2] & 0x3F) << 6;
         f = cstring[cntC + 3] & 0x3F;
         ret.buffer[cntV] = Char(c | d | e | f);
         cntV++;
         cntC += 4;
      }
      else if(c == 0xFF && ((uint8)cstring[cntC + 1]) == 0xFE)cntC += 2; //Steuerzeichen. erstmal ignorieren http://de.wikipedia.org/wiki/Unicodeblock_Spezielles
      else
      {
         //Friss Encoding-Fehler
         ret.buffer[cntV] = Char(c);
         cntV++;
         cntC++;
      }
   }
   return ret;
}

ByteArray UTF8Decoder::Encode(const CharArray &string)
{
   uint32 cntC = 0;
   for(uint32 a = 0; a < string.length; a++)
   {
      uint16 character = string.buffer[a].Unicode();
      if(character < 0x80)   //1 Zeichen
      {
         cntC += 1;
      }
      else if(character < 0x800)   //2 Zeichen
      {
         cntC += 2;
      }
      else//3 Zeichen
      {
         cntC += 3;
      }
   }

   ByteArray cstring = ByteArray(cntC, 0);
   cntC = 0;
   for(Integer a = 0; a < string.length; a++)
   {
      uint16 character = string.buffer[a].Unicode();
      if(character < 0x80)   //1 Zeichen
      {
         cstring[cntC] = (int8)character;
         cntC += 1;
      }
      else if(character < 0x800)   //2 Zeichen
      {
         cstring[cntC] = (int8)((character >> 6) & 0x1F) | 0xC0;
         cstring[cntC + 1] = (int8)(character & 0x3F) | 0x80;
         cntC += 2;
      }
      else//3 Zeichen
      {
         cstring[cntC] = (int8)((character >> 12) & 0x0F) | 0xE0;
         cstring[cntC + 1] = (int8)((character >> 6) & 0x3F) | 0x80;
         cstring[cntC + 2] = (int8)(character & 0x3F) | 0x80;
         cntC += 3;
      }
   }
   return cstring;
}
