//
//  UTF16Decoder.cpp
//  jameo
//
//  Created by Uwe Runtemund on 11.02.2015.
//  Copyright (c) 2015 Jameo Software. All rights reserved.
//

#include "Precompiled.h"

using namespace jm;

UTF16Decoder::UTF16Decoder(bool isBE): CharsetDecoder()
{
	be = isBE;
}

CharArray UTF16Decoder::Decode(const int8* cstring)
{
	//Bestimme Länge
	uint32 strLength = 0;
	uint32 cntV = 0;
	uint32 cntC = be ? 1 : 0;
	uint32 start = 0;

	//Prüfe auf Steuerzeichen am Anfang des cstring. Wenn vorhanden ignoriere
	if((cstring[0]) == static_cast<int8>(0xFE) && cstring[1] == static_cast<int8>(0xFF))
	{
		cntC = 2;
		start = 2;
	}
	else if(cstring[0] == static_cast<int8>(0xFF) && cstring[1] == static_cast<int8>(0xFE))
	{
		cntC = 2;
		start = 2;
	}
	else if(cstring[0] == static_cast<int8>(0xEF) && cstring[1] == static_cast<int8>(0xBB) && cstring[2] == static_cast<int8>(0xBF))
	{
		throw new Exception("UTF-8 Encoding detected.");
	}


	while(cstring[cntC] != 0)
	{
		cntC += 2;
		strLength++;
	}
	cntC = start;

	CharArray ret = CharArray(strLength);
	while(cntV < strLength)
	{
		uint16 c1 = (uint8)cstring[cntC++];
		uint16 c2 = (uint8)cstring[cntC++];

		if(be)ret.buffer[cntV] = (c1 << 8) | c2;
		else ret.buffer[cntV] = c1 | (c2 << 8);
		cntV++;
	}
	return ret;
}

char* UTF16Decoder::Encode(const CharArray &string)
{
	//Länge bleibt gleich..

	int8* cstring = new int8[1 + 2 * string.length];
	cstring[2 * string.length] = 0;
	uint32 idx = 0;
	for(uint32 a = 0; a < string.length; a++)
	{
		uint16 character = string.buffer[a];
		cstring[idx] = (int8)(character >> 8);
		idx++;
		cstring[idx] = (int8)character;
		idx++;
	}
	return cstring;
}
