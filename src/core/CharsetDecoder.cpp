//
//  CharsetDecoder.cpp
//  jameo
//
//  Created by Uwe Runtemund on 18.01.13.
//  Copyright (c) 2013 Jameo Software. All rights reserved.
//

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

CharArray RawDecoder::Decode(const int8* cstring)
{
	//Länge bestimmen
	uint32 length = 0;
	while(cstring[length] != 0)length++;

	CharArray array = CharArray(length);

	for(uint32 a = 0; a < length; a++)
	{
		array.buffer[a] = cstring[a];
	}

	return array;
}

int8* RawDecoder::Encode(const CharArray &string)
{
	int8* cstring = new int8[string.length + 1];
	cstring[string.length] = 0;

	for(uint32 a = 0; a < string.length; a++)
	{
		cstring[a] = (char)string.buffer[a];
	}

	return cstring;
}
