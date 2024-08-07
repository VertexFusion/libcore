////////////////////////////////////////////////////////////////////////////////////////////////////
// Name:        Base64.cpp
// Library:     Jameo Core Library
// Purpose:     Implementation of Base64 algorithm
//
// Author:      Uwe Runtemund (2020-today)
// Modified by:
// Created:     28.12.20
//
// Copyright:   (c) 2020 Jameo Software, Germany. https://jameo.de
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


const uint8 gBase64fillchar = '=';
const uint8 gBase64cvt[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

const uint8 gBase64rcvt[] =
{
   66, 66, 66, 66, 66, 66, 66, 66, 66, 66, //0
   64, 66, 66, 66, 66, 66, 66, 66, 66, 66,
   66, 66, 66, 66, 66, 66, 66, 66, 66, 66,
   66, 66, 66, 66, 66, 66, 66, 66, 66, 66,
   66, 66, 66, 62, 66, 66, 66, 63, 52, 53,

   54, 55, 56, 57, 58, 59, 60, 61, 66, 66, //50
   66, 65, 66, 66, 66, 0, 1, 2, 3, 4,
   5, 6, 7, 8, 9, 10, 11, 12, 13, 14,
   15, 16, 17, 18, 19, 20, 21, 22, 23, 24,
   25, 66, 66, 66, 66, 66, 66, 26, 27, 28,

   29, 30, 31, 32, 33, 34, 35, 36, 37, 38, //100
   39, 40, 41, 42, 43, 44, 45, 46, 47, 48,
   49, 50, 51, 66, 66, 66, 66, 66, 66, 66,
   66, 66, 66, 66, 66, 66, 66, 66, 66, 66,
   66, 66, 66, 66, 66, 66, 66, 66, 66, 66,

   66, 66, 66, 66, 66, 66, 66, 66, 66, 66, //150
   66, 66, 66, 66, 66, 66, 66, 66, 66, 66,
   66, 66, 66, 66, 66, 66, 66, 66, 66, 66,
   66, 66, 66, 66, 66, 66, 66, 66, 66, 66,
   66, 66, 66, 66, 66, 66, 66, 66, 66, 66,

   66, 66, 66, 66, 66, 66, 66, 66, 66, 66, //200
   66, 66, 66, 66, 66, 66, 66, 66, 66, 66,
   66, 66, 66, 66, 66, 66, 66, 66, 66, 66,
   66, 66, 66, 66, 66, 66, 66, 66, 66, 66,
   66, 66, 66, 66, 66, 66, 66, 66, 66, 66,

   66, 66, 66, 66, 66, 66
};//250

uint8* Base64::encode(const uint8* data, Integer& length)
{
   uint8 c1 = 0, c2 = 0, c3 = 0, c4 = 0, b1, b2, b3;
   Integer len = length;
   Integer lenb64 = ((len / 3) + 1) * 4;

   uint8* ret = new uint8[lenb64];

   Integer index = 0;

   for(Integer i = 0; i < len; i += 3)
   {
      b1 = data[i];
      b2 = data[i + 1];
      b3 = data[i + 2];

      //1. Buchstabe
      c1 = (b1 >> 2) & 0x3f; //mask 00111111

      //2. Buchstabe
      c2 = (b1 << 4) & 0x3f; //mask 00111111
      if(i + 1 < len)
      {
         c2 |= (b2 >> 4) & 0x0f;//mask 00001111

         //3. Buchstabe 00111100
         c3 = (b2 << 2) & 0x3f;//mask 00111111
         if(i + 2 < len)
         {
            c3 |= (b3 >> 6) & 0x03;//mask 00000011

            //4. Buchstabe
            c4 = b3 & 0x3f;//mask 00111111
         }
      }

      ret[index++] = gBase64cvt[c1];
      ret[index++] = gBase64cvt[c2];
      ret[index++] = (i + 1 < len) ? gBase64cvt[c3] : gBase64fillchar;
      ret[index++] = (i + 2 < len) ? gBase64cvt[c4] : gBase64fillchar;

   }
   length = index;
   if(index > lenb64)throw new Exception("Array overflow! Algorithm wrong");
   return ret;
}

uint8* Base64::decode(const uint8* data, uint32& length)
{
   uint8 c1 = 0, c2 = 0, c3 = 0, c4 = 0;
   uint8 b1 = 0, b2 = 0, b3 = 0;
   int len = length;

   uint32 lenb64 = (len * 3) / 4 ;

   uint8* ret = new uint8[lenb64];
   uint32 index = 0;
   bool brk = false;

   for(int32 i = 0; i < len; i = i + 4)
   {
      c1 = gBase64rcvt[data[i]];
      c2 = gBase64rcvt[data[i + 1]];
      c3 = gBase64rcvt[data[i + 2]];
      c4 = gBase64rcvt[data[i + 3]];

      if(c2 >= 65)
      {
         c2 = 0;
         brk = true;
      }
      b1 = ((c1 << 2) | ((c2 >> 4) & 0x3));
      ret[index++] = b1;
      if(brk)break;


      if(c3 >= 65)
      {
         c3 = 0;
         brk = true;
      }
      b2 = ((c2 << 4) & 0xf0) | ((c3 >> 2) & 0xf);
      ret[index++] = b2;
      if(brk)break;

      if(c4 >= 65)
      {
         c4 = 0;
         brk = true;
      }
      b3 = ((c3 << 6) & 0xc0) | c4;
      ret[index++] = b3;
      if(brk)break;

   }
   length = index;
   return ret;
}
