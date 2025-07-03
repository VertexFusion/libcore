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

#include "PrecompiledCore.hpp"

using namespace jm;

StringTokenizer::StringTokenizer(const String& str,
                                 const String& delimiters,
                                 bool retDelim): Object(),
   mStr(str),
   mDelimiters(delimiters),
   mPosition(0),
   mNewStart(npos),
   mRetDelim(retDelim)
{}

bool StringTokenizer::isDelimiter(size_t index) const
{
   size_t cnt = 0;
   size_t l = mDelimiters.size();
   Char c = mStr.charAt(index);

   while(cnt < l)
   {
      if(mDelimiters.charAt(cnt++) == c)return true;
   }
   return false;
}

size_t StringTokenizer::findTokenEnd(size_t startPos) const
{
   size_t pos = startPos;
   size_t l = mStr.size();

   while(pos < l)
   {
      if(isDelimiter(pos))break;
      pos++;
   }
   return pos;
}

size_t StringTokenizer::findDelimiterEnd(size_t startPos) const
{
   size_t pos = startPos;
   size_t l = mStr.size();

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
   if(mNewStart == npos)mNewStart = findDelimiterEnd(mPosition);

   return mNewStart < mStr.size();
}

String StringTokenizer::next()
{
   mPosition = (mNewStart != npos) ? mNewStart : findDelimiterEnd(mPosition);
   mNewStart = npos;

   if(mPosition >= mStr.size())throw Exception(Tr("No such element."));

   if(mRetDelim && isDelimiter(mPosition))
   {
      size_t start = mPosition;
      size_t end = mPosition + 1;
      mPosition = end;
      return mStr.substring(start, end);
   }
   else
   {
      size_t start = mPosition;
      size_t end = findTokenEnd(start);
      mPosition = end;
      return mStr.substring(start, end);
   }

}
