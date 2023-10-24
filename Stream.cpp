//
//  Stream.cpp
//  jameo
//
//  Created by Uwe Runtemund on 18.08.15.
//  Copyright (c) 2013 Jameo Software. All rights reserved.
//

#include "Precompiled.h"

using namespace jm;

Stream::Stream(): Object()
{

}

Integer Stream::Write(const String &string)
{
	int8* cstr = string.ToCString();
	Integer length = 0;
	while(cstr[length] != 0)length++;
	Integer ret = Write((uint8*)cstr, length);
	delete[] cstr;
	return ret;
}

