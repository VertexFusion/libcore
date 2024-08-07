////////////////////////////////////////////////////////////////////////////////////////////////////
// Name:        UTF16Decoder.cpp
// Library:     Jameo Core Library
// Purpose:     Decoder for utf-16 encoded text.
//
// Author:      Uwe Runtemund (2015-today)
// Modified by:
// Created:     11.02.2015
//
// Copyright:   (c) 2015 Jameo Software, Germany. https://jameo.de
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

UTF16Decoder::UTF16Decoder(bool isBE): CharsetDecoder()
{
   be = isBE;
}

CharArray UTF16Decoder::Decode(const char* cstring)
{
   //Bestimme Länge
   uint32 strLength = 0;
   uint32 cntV = 0;
   uint32 cntC = be ? 1 : 0;
   uint32 start = 0;

   //Prüfe auf Steuerzeichen am Anfang des cstring. Wenn vorhanden ignoriere
   if(cstring[0] == static_cast<char>(0xFE) &&
         cstring[1] == static_cast<char>(0xFF))
   {
      cntC = 2;
      start = 2;
   }
   else if(cstring[0] == static_cast<char>(0xFF) &&
           cstring[1] == static_cast<char>(0xFE))
   {
      cntC = 2;
      start = 2;
   }
   else if(cstring[0] == static_cast<char>(0xEF) &&
           cstring[1] == static_cast<char>(0xBB) &&
           cstring[2] == static_cast<char>(0xBF))
   {
      throw new Exception("UTF-8 Encoding detected.");
   }


   while(cstring[cntC] != 0)
   {
      cntC += 2;
      strLength++;
   }
   cntC = start;

   CharArray ret = CharArray(strLength);
   while(cntV < strLength)
   {
      uint16 c1 = (uint8)cstring[cntC++];
      uint16 c2 = (uint8)cstring[cntC++];

      if(be)ret.buffer[cntV] = Char((c1 << 8) | c2);
      else ret.buffer[cntV] = Char(c1 | (c2 << 8));
      cntV++;
   }
   return ret;
}

ByteArray UTF16Decoder::Encode(const CharArray& string)
{
   //Länge bleibt gleich..

   ByteArray cstring = ByteArray(2 * string.length, 0);

   Integer idx = 0;
   for(uint32 a = 0; a < string.length; a++)
   {
      uint16 character = string.buffer[a].unicode();
      cstring[idx] = (int8)(character >> 8);
      idx++;
      cstring[idx] = (int8)character;
      idx++;
   }
   return cstring;
}
