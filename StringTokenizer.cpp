//
//  StringTokenizer.cpp
//  jameo
//
//  Created by Uwe Runtemund on 02.02.13.
//  Copyright (c) 2013 Jameo Software. All rights reserved.
//

#include "Precompiled.h"

using namespace jm;

StringTokenizer::StringTokenizer(String _str, String _delimiter, bool _retDelim): Object()
{
	str = _str;
	delimiters = _delimiter;
	retDelim = _retDelim;
	position = 0;
	newStart = -1;
}


bool StringTokenizer::IsDelimiter(int32 index)
{
	int32 cnt = 0;
	int32 l = delimiters.Length();
	uint16 c = str.CharAt(index);

	while(cnt < l)
	{
		if(delimiters.CharAt(cnt++) == c)return true;
	}
	return false;
}

int32 StringTokenizer::FindTokenEnd(int32 startPos)
{
	int32 pos = startPos;
	int32 l = str.Length();

	while(pos < l)
	{
		if(IsDelimiter(pos))break;
		pos++;
	}
	return pos;
}

int32 StringTokenizer::FindDelimEnd(int startPos)
{
	int32 pos = startPos;
	int32 l = str.Length();

	if(retDelim && pos < l && IsDelimiter(pos))return pos;

	while(pos < l)
	{
		if(!IsDelimiter(pos))break;
		pos++;
	}
	return pos;
}

bool StringTokenizer::HasMoreTokens()
{
	if(newStart < 0)newStart = FindDelimEnd(position);

	return newStart < (int) str.Length();
}

String StringTokenizer::NextToken()
{
	position = (newStart > -1) ? newStart : FindDelimEnd(position);
	newStart = -1;

	if(position >= (int32)str.Length())throw new Exception("No such element.");

	if(retDelim && IsDelimiter(position))
	{
		int32 start = position;
		int32 end = position + 1;
		position = end;
		return str.Substring(start, end);
	}
	else
	{
		int32 start = position;
		int32 end = FindTokenEnd(start);
		position = end;
		return str.Substring(start, end);
	}

}
