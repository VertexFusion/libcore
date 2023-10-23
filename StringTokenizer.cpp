//
//  StringTokenizer.cpp
//  jameo
//
//  Created by Uwe Runtemund on 02.02.13.
//  Copyright (c) 2013 Jameo Software. All rights reserved.
//

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

	if(mPosition >= mStr.Length())throw new Exception("No such element.");

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
