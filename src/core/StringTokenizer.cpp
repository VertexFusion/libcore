////////////////////////////////////////////////////////////////////////////////////////////////////
// Name:        StringTokenizer.cpp
// Library:     Jameo Core Library
// Purpose:     Implementation of string tokenizer
//
// Author:      Uwe Runtemund (2013-today)
// Modified by:
// Created:     02.02.2013
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

StringTokenizer::StringTokenizer(const String& str,
                                 const String& delimiters,
                                 bool retDelim): Object(),
mStr(str),
mDelimiters(delimiters),
mPosition(0),
mNewStart(-1),
mRetDelim(retDelim)
{}

bool StringTokenizer::isDelimiter(int64 index) const
{
   int64 cnt = 0;
   int64 l = mDelimiters.size();
   Char c = mStr.charAt(index);

   while(cnt < l)
   {
      if(mDelimiters.charAt(cnt++) == c)return true;
   }
   return false;
}

int64 StringTokenizer::findTokenEnd(int64 startPos) const
{
   int64 pos = startPos;
   int64 l = mStr.size();

   while(pos < l)
   {
      if(isDelimiter(pos))break;
      pos++;
   }
   return pos;
}

int64 StringTokenizer::findDelimiterEnd(int64 startPos) const
{
   int64 pos = startPos;
   int64 l = mStr.size();

   if(mRetDelim && pos < l && isDelimiter(pos))return pos;

   while(pos < l)
   {
      if(!isDelimiter(pos))break;
      pos++;
   }
   return pos;
}

bool StringTokenizer::hasNext()
{
   if(mNewStart < 0)mNewStart = findDelimiterEnd(mPosition);

   return mNewStart < mStr.size();
}

String StringTokenizer::next()
{
   mPosition = (mNewStart > -1) ? mNewStart : findDelimiterEnd(mPosition);
   mNewStart = -1;

   if(mPosition >= mStr.size())throw Exception(Tr("No such element."));

   if(mRetDelim && isDelimiter(mPosition))
   {
      int64 start = mPosition;
      int64 end = mPosition + 1;
      mPosition = end;
      return mStr.substring(start, end);
   }
   else
   {
      int64 start = mPosition;
      int64 end = findTokenEnd(start);
      mPosition = end;
      return mStr.substring(start, end);
   }

}
