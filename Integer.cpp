//
//  Date.cpp
//  jameo
//
//  Created by Uwe Runtemund on 24.01.2016.
//  Copyright (c) 2016 Jameo Software. All rights reserved.
//

#include "Precompiled.h"

using namespace jm;

const uint16 gMask[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
const int32 gArabic[] = {1, 4, 5, 9, 10, 40, 50, 90, 100, 400, 500, 900, 1000};
const String gRoman[] = {"I", "IV", "V", "IX", "X", "XL", "L", "XC", "C", "CD", "D", "CM", "M"};

Integer::Integer(): Object(), Comparable<Integer>()
{
	mValue = 0;
}

Integer::Integer(int64 value): Object(), Comparable<Integer>()
{
	mValue = value;
}

bool Integer::Equals(const Object* other) const
{
	const Integer* i = dynamic_cast<const Integer*>(other);
	if(i == NULL)return false;

	return i->Equals(*this);
}

bool Integer::Equals(const Integer &another) const
{
	return mValue == another.mValue;
}

int32 Integer::CompareTo(const Integer &another) const
{
	if(mValue > another.mValue)return 1;
	if(mValue < another.mValue)return -1;
	return 0;
}

int64 Integer::Value() const
{
	return mValue;
}

int64 Integer::ValueOf(const String &string)
{
	int64 val = 0;
	bool neg = false;

	for(uint32 a = 0; a < string.Length(); a++)
	{
		uint16 c = string.CharAt(a);

		if(c >= '0' && c <= '9')
		{
			val *= 10;
			val += c - '0';
		}
		else if(c == '-')neg = true;
		else throw new Exception("Number format exception for input string: \"" + string + "\"");
	}

	if(neg)val *= -1;
	return val;
}

String Integer::ToHexString(uint64 number)
{
	String ret;

	//Prüfe auf 0
	if(number == 0)
	{
		ret.Append('0');
		return ret;
	}

	int32 base = 16;

	//Löse die einzelnen Zahlen auf... Achtung: die letzte Ziffer kommt zuerst
	while(number > 0)
	{
		int64 digit = number % base;
		number = number / base;
		ret.Append(gMask[digit]);
	}

	//Zahlen umkehren
	return ret.Reverse();
}

String Integer::ToHexString(Integer number)
{
	return ToHexString(number.Value());
}

String Integer::ToRomanString(uint64 number)
{
	String output;

	int32 index = 12;


	while(index >= 0)
	{
		int32 div = static_cast<int32>(number / gArabic[index]);
		int32 rest = number % gArabic[index];
		number = rest;

		while(div > 0)
		{
			output.Append(gRoman[index]);
			div--;
		}
		index--;
	}

	return output;
}

String Integer::ToLatinAlphabetString(uint64 number)
{
	String output;

	while(number > 0)
	{
		int32 div = static_cast<int32>(number / 26);
		int16 rest = (int16)(number % 26 - 1);

		output.Append('A' + rest);

		number = div;
	}

	//Zahlen umkehren
	return output.Reverse();
}
