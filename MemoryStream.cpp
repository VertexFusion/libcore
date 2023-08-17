//
//  MemoryStream.cpp
//  jameo
//
//  Created by Uwe Runtemund on 18.08.15.
//  Copyright (c) 2013 Jameo Software. All rights reserved.
//

#include "Precompiled.h"

using namespace jm;

MemoryStream::MemoryStream(uint8* stream, uint32 length): Stream()
{
	mStream = stream;
	mStreamlength = length;
	mPosition = 0;
	mWritelength = 0;
}

void MemoryStream::Open(FileMode)
{
	mPosition = 0;
	mWritelength = 0;
}

bool MemoryStream::IsOpen()
{
	return true;
}

void MemoryStream::Close()
{
	mPosition = 0;
}

uint32 MemoryStream::Read(uint8* buffer, uint32 length)
{
	uint32 available = (mPosition + length < mStreamlength) ? length : mStreamlength - mPosition;
	if(available > 0)memcpy(buffer, &mStream[mPosition], available);
	else return 0;

	mPosition += available;
	return available;
}

uint32 MemoryStream::ReadFully(uint8* buffer, uint32 length)
{
	return Read(buffer, length);
}

void MemoryStream::Seek(uint64 newPosition)
{
	mPosition = (newPosition < mStreamlength) ? (uint32)newPosition : mPosition;
}

void MemoryStream::Move(int64 offset)
{
	uint64 newPosition = mPosition + offset;
	mPosition = (newPosition < mStreamlength) ? (uint32)newPosition : mPosition;
}

uint64 MemoryStream::GetPosition()
{
	return mPosition;
}

uint32 MemoryStream::Write(uint8* buffer, uint32 length)
{
	uint32 available = (mPosition + length < mStreamlength) ? length : mStreamlength - mPosition;
	memcpy(&mStream[mPosition], buffer, length);
	mPosition += available;
	if(mPosition > mWritelength)mWritelength = mPosition;
	return available;
}

uint32 MemoryStream::Length()
{
	return mStreamlength;
}

uint8* MemoryStream::GetBuffer()
{
	return mStream;
}
