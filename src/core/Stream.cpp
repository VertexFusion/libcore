////////////////////////////////////////////////////////////////////////////////////////////////////
// Name:        Stream.cpp
// Library:     Jameo Core Library
// Purpose:     Parent for all stream objects
//
// Author:      Uwe Runtemund (2015-today)
// Modified by:
// Created:     15.08.2015
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

Stream::Stream(): Object()
{

}

size_t Stream::write(const String& string)
{
   ByteArray cstr = string.toCString();
   size_t ret = write((const uint8*)cstr.constData(), cstr.size());
   return ret;
}

size_t Stream::write(const int8* buffer, size_t length)
{
   return write((const uint8*)buffer, length);
}

size_t Stream::readFully(ByteArray& buffer)
{
   return readFully(buffer, buffer.size());
};
