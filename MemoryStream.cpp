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

Integer MemoryStream::Read(uint8* buffer, Integer length)
{
	Integer available = (mPosition + length < mStreamlength) ? length : mStreamlength - mPosition;
	if(available > 0)memcpy(buffer, &mStream[mPosition], available);
	else return 0;

	mPosition += available;
	return available;
}

Integer MemoryStream::ReadFully(uint8* buffer, Integer length)
{
	return Read(buffer, length);
}

void MemoryStream::Seek(Integer newPosition)
{
	mPosition = (newPosition < mStreamlength) ? newPosition : mPosition;
}

void MemoryStream::Move(Integer offset)
{
	Integer newPosition = mPosition + offset;
	mPosition = (newPosition < mStreamlength) ? (uint32)newPosition : mPosition;
}

Integer MemoryStream::GetPosition()
{
	return mPosition;
}

Integer MemoryStream::Write(uint8* buffer, Integer length)
{
	Integer available = (mPosition + length < mStreamlength) ? length : mStreamlength - mPosition;
	memcpy(&mStream[mPosition], buffer, length);
	mPosition += available;
	if(mPosition > mWritelength) mWritelength = mPosition;
	return available;
}

Integer MemoryStream::Length()
{
	return mStreamlength;
}

uint8* MemoryStream::GetBuffer()
{
	return mStream;
}
