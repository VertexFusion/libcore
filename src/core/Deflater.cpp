//
//  Deflater.cpp
//  jameo
//
//  Created by Uwe Runtemund on 15.09.15.
//  Copyright (c) 2015 Jameo Software. All rights reserved.
//

#include "Precompiled.h"

using std::max;
using namespace jm;

Deflater::Deflater(): Object()
{
}

Deflater::~Deflater()
{
}

void Deflater::SetInput(uint8* buffer, uint32 length)
{
	mUncompBytes = buffer;
	mUncompLength = length;
	mUncompIndex = 0;
}

void Deflater::Deflate(uint8* &buffer, uint32 &length)
{
	mUncompIndex = 0;

	buffer = new uint8[mUncompLength];

	z_stream defstream;
	defstream.zalloc = Z_NULL;
	defstream.zfree = Z_NULL;
	defstream.opaque = Z_NULL;
	// setup "a" as the input and "b" as the compressed output
	defstream.avail_in = mUncompLength; // size of input, string + terminator
	defstream.next_in = (Bytef *)mUncompBytes; // input char array
	defstream.avail_out = (uInt)mUncompLength; // size of output
	defstream.next_out = (Bytef *)buffer; // output char array

	// the actual compression work.
	deflateInit(&defstream, Z_BEST_COMPRESSION);
	deflate(&defstream, Z_FINISH);
	deflateEnd(&defstream);

	length = (uint32)defstream.total_out;
}

void Deflater::Reset()
{
	mUncompBytes = NULL;
	mUncompLength = 0;
	mUncompIndex = 0;
	mTotalIn = 0;
	mTotalOut = 0;
}

int32 Deflater::GetTotalIn()
{
	return mTotalIn;
}

int32 Deflater::GetTotalOut()
{
	return mTotalOut;
}
