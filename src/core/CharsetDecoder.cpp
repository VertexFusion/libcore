////////////////////////////////////////////////////////////////////////////////////////////////////
// Name:        CharsetDecoder.cpp
// Library:     Jameo Core Library
// Purpose:     Implementation of CharsetDecoder
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

CharsetDecoder::CharsetDecoder(): Object()
{

}

CharsetDecoder::~CharsetDecoder()
{
}


RawDecoder::RawDecoder(): CharsetDecoder()
{
}

CharArray RawDecoder::Decode(const char* cstring)
{
   //Länge bestimmen
   uint32 length = 0;
   while(cstring[length] != 0)length++;

   CharArray array = CharArray(length);

   for(uint32 a = 0; a < length; a++)
   {
      array.buffer[a] = Char(cstring[a]);
   }

   return array;
}

ByteArray RawDecoder::Encode(const CharArray& string)
{
   ByteArray cstring = ByteArray(string.length, 0);

   for(uint32 a = 0; a < string.length; a++)
   {
      cstring[a] = (uint8)string.buffer[a].unicode();
   }

   return cstring;
}
