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

#include "Precompiled.h"

using namespace jm;

StringTokenizer::StringTokenizer(const String &str, const String &delimiters, Bool retDelim): Object()
{
	mStr = str;
	mDelimiters = delimiters;
	mRetDelim = retDelim;
	mPosition = 0;
	mNewStart = -1;
}


Bool StringTokenizer::IsDelimiter(Integer index) const
{
	Integer cnt = 0;
	Integer l = mDelimiters.Length();
	uint16 c = mStr.CharAt(index);

	while(cnt < l)
	{
		if(mDelimiters.CharAt(cnt++) == c)return true;
	}
	return false;
}

Integer StringTokenizer::FindTokenEnd(Integer startPos) const
{
	Integer pos = startPos;
	Integer l = mStr.Length();

	while(pos < l)
	{
		if(IsDelimiter(pos))break;
		pos++;
	}
	return pos;
}

Integer StringTokenizer::FindDelimEnd(Integer startPos) const
{
	Integer pos = startPos;
	Integer l = mStr.Length();

	if(mRetDelim && pos < l && IsDelimiter(pos))return pos;

	while(pos < l)
	{
		if(!IsDelimiter(pos))break;
		pos++;
	}
	return pos;
}

Bool StringTokenizer::HasMoreTokens()
{
	if(mNewStart < 0)mNewStart = FindDelimEnd(mPosition);

	return mNewStart < mStr.Length();
}

String StringTokenizer::NextToken()
{
	mPosition = (mNewStart > -1) ? mNewStart : FindDelimEnd(mPosition);
	mNewStart = -1;

	if(mPosition >= mStr.Length())throw new Exception(Tr("No such element."));

	if(mRetDelim && IsDelimiter(mPosition))
	{
		Integer start = mPosition;
		Integer end = mPosition + 1;
		mPosition = end;
		return mStr.Substring(start, end);
	}
	else
	{
		Integer start = mPosition;
		Integer end = FindTokenEnd(start);
		mPosition = end;
		return mStr.Substring(start, end);
	}

}
