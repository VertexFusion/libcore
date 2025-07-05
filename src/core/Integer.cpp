////////////////////////////////////////////////////////////////////////////////////////////////////
// Name:        Integer.cpp
// Library:     Jameo Core Library
// Purpose:     Enhancement for Integer Types
//
// Author:      Uwe Runtemund (2016-today)
// Modified by:
// Created:     30.10.2016
//
// Copyright:   (c) 2016 Jameo Software, Germany. https://jameo.de
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

#include "PrecompiledCore.hpp"

using namespace jm;

const uint16 gMask[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
const int32 gArabic[] = {1, 4, 5, 9, 10, 40, 50, 90, 100, 400, 500, 900, 1000};
const jm::String gRoman[] = {"I", "IV", "V", "IX", "X", "XL", "L", "XC", "C", "CD", "D", "CM", "M"};

uint8 Integer::digits(int64 number)
{
   uint8 i = 1;
   if(number < 0)
   {
      number *= -1;
      i++;
   }

   while(number > 9)
   {
      number = number / 10;
      i++;
   }
   return i;
}

int64 Integer::fromHex(const jm::String& str)
{
   return fromHex(str, 0, str.size());
}

int64 Integer::fromHex(const jm::String& str, size_t begin, size_t size)
{
   int64 r = 0;

   size_t cnt = begin;
   size_t sz = begin + size;

   while(cnt < sz)
   {
      jm::Char c = str.charAt(cnt);
      cnt++;

      int64 i = 0;

      if(c.isDigit())
      {
         i = c.digitValue();
      }
      else if(c >= 'a' && c <= 'f')
      {
         i = c.unicode() - 'a' + 10;
      }
      else if(c >= 'A' && c <= 'F')
      {
         i = c.unicode() - 'A' + 10;
      }

      r <<= 4;
      r |= i;

   }

   return r;
}


jm::String Integer::toHexString(int64 number)
{
   jm::String ret;

   //Prüfe auf 0
   if(number == 0)
   {
      ret.append('0');
      return ret;
   }

   int32 base = 16;

   //Löse die einzelnen Zahlen auf... Achtung: die letzte Ziffer kommt zuerst
   while(number > 0)
   {
      int64 digit = number % base;
      number = number / base;
      ret.append(gMask[digit]);
   }

   //Zahlen umkehren
   return ret.reverse();
}

jm::String Integer::toRomanString(int64 number)
{
   jm::String output;

   int64 index = 12;

   while(index >= 0)
   {
      int64 div = number / gArabic[index];
      int64 rest = number % gArabic[index];
      number = rest;

      while(div > 0)
      {
         output.append(gRoman[index]);
         div--;
      }
      index--;
   }

   return output;
}

jm::String Integer::toLatinAlphabetString(int64 number)
{
   jm::String output;

   while(number > 0)
   {
      number--;
      int32 digit = number % 26;
      number = number / 26;
      output.append(jm::Char('A' + digit));
   }

   //Zahlen umkehren
   return output.reverse();
}
