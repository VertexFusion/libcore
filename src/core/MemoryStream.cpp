////////////////////////////////////////////////////////////////////////////////////////////////////
// Name:        MemoryStream.cpp
// Library:     Jameo Core Library
// Purpose:     In Memory Stream Object
//
// Author:      Uwe Runtemund (2015-today)
// Modified by:
// Created:     18.08.2015
//
// Copyright:   (c) 2015 Jameo Software, Germany. https://jameo.de
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

#include "PrecompiledCore.hpp"

using namespace jm;

MemoryStream::MemoryStream(uint8* stream, int64 length): Stream()
{
   mStream = stream;
   mStreamlength = length;
   mPosition = 0;
   mWritelength = 0;
}

Status MemoryStream::open(FileMode)
{
   mPosition = 0;
   mWritelength = 0;
   return Status::eOK;
}

bool MemoryStream::isOpen()
{
   return true;
}

void MemoryStream::close()
{
   mPosition = 0;
}

int64 MemoryStream::read(uint8* buffer, int64 length)
{
   int64 available = (mPosition + length < mStreamlength) ? length : mStreamlength - mPosition;
   if(available > 0)memcpy(buffer, &mStream[mPosition], available);
   else return 0;

   mPosition += available;
   return available;
}

int64 MemoryStream::readFully(ByteArray& buffer, int64 length)
{
   return read((uint8*)buffer.data(), length);
}

void MemoryStream::seek(int64 newPosition)
{
   mPosition = (newPosition < mStreamlength) ? newPosition : mPosition;
}

void MemoryStream::move(int64 offset)
{
   int64 newPosition = mPosition + offset;
   mPosition = (newPosition < mStreamlength) ? newPosition : mPosition;
}

int64 MemoryStream::position()
{
   return mPosition;
}

int64 MemoryStream::write(const uint8* buffer, int64 length)
{
   int64 available = (mPosition + length < mStreamlength) ? length : mStreamlength - mPosition;
   memcpy(&mStream[mPosition], buffer, length);
   mPosition += available;
   if(mPosition > mWritelength) mWritelength = mPosition;
   return available;
}

int64 MemoryStream::size() const
{
   return mStreamlength;
}

uint8* MemoryStream::buffer()
{
   return mStream;
}
