////////////////////////////////////////////////////////////////////////////////////////////////////
// Name:        Deflater.cpp
// Library:     Jameo Core Library
// Purpose:     Implementation of Deflater
//
// Author:      Uwe Runtemund (2015-today)
// Modified by:
// Created:     15.09.2015
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

Deflater::Deflater(): Object()
{
   mTotalIn=0;
   mTotalOut=0;
}

Deflater::~Deflater()
{
}

void Deflater::setInput(uint8* buffer, int64 length)
{
   mUncompBytes = buffer;
   mUncompLength = length;
   mUncompIndex = 0;
   mTotalIn += length;
}

void Deflater::deflate(uint8*& buffer, int64& length)
{
   mUncompIndex = 0;

   buffer = new uint8[mUncompLength];

   z_stream defstream;
   defstream.zalloc = Z_NULL;
   defstream.zfree = Z_NULL;
   defstream.opaque = Z_NULL;
   // setup "a" as the input and "b" as the compressed output
   defstream.avail_in = (uInt) mUncompLength; // size of input, string + terminator
   defstream.next_in = reinterpret_cast<Bytef*>(mUncompBytes);  // input char array
   defstream.avail_out = (uInt)mUncompLength; // size of output
   defstream.next_out = reinterpret_cast<Bytef*>(buffer);  // output char array

   // the actual compression work.
   deflateInit(&defstream, Z_BEST_COMPRESSION);
   ::deflate(&defstream, Z_FINISH);
   deflateEnd(&defstream);

   length = (uint32)defstream.total_out;
   mTotalOut += length;
}

void Deflater::reset()
{
   mUncompBytes = nullptr;
   mUncompLength = 0;
   mUncompIndex = 0;
   mTotalIn = 0;
   mTotalOut = 0;
}

int64 Deflater::totalInSize()
{
   return mTotalIn;
}

int64 Deflater::totalOutSize()
{
   return mTotalOut;
}
