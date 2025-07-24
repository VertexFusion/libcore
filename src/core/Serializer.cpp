////////////////////////////////////////////////////////////////////////////////////////////////////
// Name:        Serializer.cpp
// Library:     Jameo Core Library
// Purpose:     Serialization of core data types
//
// Author:      Uwe Runtemund (2013-today)
// Modified by:
// Created:     02.05.2013
//
// Copyright:   (c) 2013 Jameo Software, Germany. https://jameo.de
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


size_t jm::serializeBEInt16(uint8* buffer, size_t offset, int16 value)
{
   buffer[offset + 1] = (uint8)value;
   value >>= 8;
   buffer[offset] = (uint8)value;
   return 2;
}

size_t jm::serializeBEUInt16(uint8* buffer, size_t offset, uint16 value)
{
   buffer[offset + 1] = (uint8)value;
   value >>= 8;
   buffer[offset] = (uint8)value;
   return 2;
}

size_t jm::serializeBEInt24(uint8* buffer, size_t offset, int32 value)
{
   buffer[offset + 2] = (uint8)value;
   value >>= 8;
   buffer[offset + 1] = (uint8)value;
   value >>= 8;
   buffer[offset] = (uint8)value;
   return 3;
}

size_t jm::serializeBEInt32(uint8* buffer, size_t offset, int32 value)
{
   buffer[offset + 3] = (uint8)value;
   value >>= 8;
   buffer[offset + 2] = (uint8)value;
   value >>= 8;
   buffer[offset + 1] = (uint8)value;
   value >>= 8;
   buffer[offset] = (uint8)value;
   return 4;
}

size_t jm::serializeBEInt64(uint8* buffer, size_t offset, int64 value)
{
   buffer[offset + 7] = (uint8)value;
   value >>= 8;
   buffer[offset + 6] = (uint8)value;
   value >>= 8;
   buffer[offset + 5] = (uint8)value;
   value >>= 8;
   buffer[offset + 4] = (uint8)value;
   value >>= 8;
   buffer[offset + 3] = (uint8)value;
   value >>= 8;
   buffer[offset + 2] = (uint8)value;
   value >>= 8;
   buffer[offset + 1] = (uint8)value;
   value >>= 8;
   buffer[offset] = (uint8)value;
   return 8;
}

size_t jm::serializeLEInt16(uint8* buffer, size_t offset, int16 value)
{
   buffer[offset] = (uint8)value;
   value >>= 8;
   buffer[offset + 1] = (uint8)value;
   return 2;
}

size_t jm::serializeLEUInt16(uint8* buffer, size_t offset, uint16 value)
{
   buffer[offset] = (uint8)value;
   value >>= 8;
   buffer[offset + 1] = (uint8)value;
   return 2;
}

size_t jm::serializeLEInt24(uint8* buffer, size_t offset, int32 value)
{
   buffer[offset] = (uint8)value;
   value >>= 8;
   buffer[offset + 1] = (uint8)value;
   value >>= 8;
   buffer[offset + 2] = (uint8)value;
   return 3;
}

size_t jm::serializeLEInt32(uint8* buffer, size_t offset, int32 value)
{
   buffer[offset] = (uint8)value;
   value >>= 8;
   buffer[offset + 1] = (uint8)value;
   value >>= 8;
   buffer[offset + 2] = (uint8)value;
   value >>= 8;
   buffer[offset + 3] = (uint8)value;
   return 4;
}

size_t jm::serializeLEInt32(jm::ByteArray& buffer, size_t offset, int32 value)
{
   return jm::serializeLEInt32((uint8*)buffer.data(),offset,value);
}


size_t jm::serializeLEInt64(uint8* buffer, size_t offset, int64 value)
{
   buffer[offset] = (uint8)value;
   value >>= 8;
   buffer[offset + 1] = (uint8)value;
   value >>= 8;
   buffer[offset + 2] = (uint8)value;
   value >>= 8;
   buffer[offset + 3] = (uint8)value;
   value >>= 8;
   buffer[offset + 4] = (uint8)value;
   value >>= 8;
   buffer[offset + 5] = (uint8)value;
   value >>= 8;
   buffer[offset + 6] = (uint8)value;
   value >>= 8;
   buffer[offset + 7] = (uint8)value;
   return 8;
}

uint16 jm::deserializeBEUInt16(const uint8* buffer, size_t offset)
{
   return (buffer[offset] << 8 | buffer[offset + 1]);
}

int16 jm::deserializeBEInt16(const uint8* buffer, size_t offset)
{
   return (buffer[offset] << 8 | buffer[offset + 1]);
}

int16 jm::deserializeBEInt16(const jm::ByteArray& buffer, size_t offset)
{
   return (buffer[offset] << 8 | buffer[offset + 1]);
}

int32 jm::deserializeBEInt24(const uint8* buffer, size_t offset)
{
   return (buffer[offset] << 16
           | buffer[offset + 1] << 8
           | buffer[offset + 2]);
}

int32 jm::deserializeLEInt24(const uint8* buffer, size_t offset)
{
   return (buffer[offset + 2] << 16
           | buffer[offset + 1] << 8
           | buffer[offset]);
}


uint32 jm::deserializeBEUInt32(const uint8* buffer, size_t offset)
{
   return static_cast<uint32>(buffer[offset] << 24
                              | buffer[offset + 1] << 16
                              | buffer[offset + 2] << 8
                              | buffer[offset + 3]);
}

uint32 jm::deserializeBEUInt32(const jm::ByteArray& buffer, size_t offset)
{
   return static_cast<uint32>(buffer[offset] << 24
                              | buffer[offset + 1] << 16
                              | buffer[offset + 2] << 8
                              | buffer[offset + 3]);
}

int32 jm::deserializeBEInt32(const jm::ByteArray& buffer, size_t offset)
{
   return (buffer[offset] << 24
           | buffer[offset + 1] << 16
           | buffer[offset + 2] << 8
           | buffer[offset + 3]);
}

int64 jm::deserializeBEInt64(const uint8* buffer, size_t offset)
{
   int64 p1 = deserializeBEUInt32(buffer, offset);
   int64 p2 = deserializeBEUInt32(buffer, offset + 4);
   return (p1 << 32) | p2;
}

int64 jm::deserializeBEInt64(const jm::ByteArray& buffer, size_t offset)
{
   int64 p1 = deserializeBEUInt32(buffer, offset);
   int64 p2 = deserializeBEUInt32(buffer, offset + 4);
   return (p1 << 32 | p2);
}

uint16 jm::deserializeLEUInt16(const uint8* buffer, size_t offset)
{
   return (buffer[offset + 1] << 8 | buffer[offset]);
}

uint16 jm::deserializeLEUInt16(const jm::ByteArray& buffer, size_t offset)
{
   return (buffer[offset + 1] << 8 | buffer[offset]);
}

int16 jm::deserializeLEInt16(const uint8* buffer, size_t offset)
{
   return (buffer[offset + 1] << 8 | buffer[offset]);
}

int16 jm::deserializeLEInt16(const jm::ByteArray& buffer, size_t offset)
{
   return (buffer[offset + 1] << 8 | buffer[offset]);
}

uint32 jm::deserializeLEUInt32(const uint8* buffer, size_t offset)
{
   return static_cast<uint32>(buffer[offset + 3] << 24
                              | buffer[offset + 2] << 16
                              | buffer[offset + 1] << 8
                              | buffer[offset]);
}

uint32 jm::deserializeLEUInt32(const jm::ByteArray& buffer, size_t offset)
{
   return static_cast<uint32>(buffer[offset + 3] << 24
                              | buffer[offset + 2] << 16
                              | buffer[offset + 1] << 8
                              | buffer[offset]);
}

int32 jm::deserializeLEInt32(const uint8* buffer, size_t offset)
{
   return (buffer[offset + 3] << 24 | buffer[offset + 2] << 16 | buffer[offset + 1] << 8 |
           buffer[offset]);
}

int32 jm::deserializeLEInt32(const jm::ByteArray& buffer, size_t offset)
{
   return (buffer[offset + 3] << 24 | buffer[offset + 2] << 16 | buffer[offset + 1] << 8 |
           buffer[offset]);
}

int64 jm::deserializeLEInt64(const uint8* buffer, size_t offset)
{
   int64 p1 = deserializeLEUInt32(buffer, offset + 4);
   int64 p2 = deserializeLEUInt32(buffer, offset);
   return (p1 << 32 | p2);
}

int64 jm::deserializeLEInt64(const jm::ByteArray& buffer, size_t offset)
{
   int64 p1 = deserializeLEUInt32(buffer, offset + 4);
   int64 p2 = deserializeLEUInt32(buffer, offset);
   return (p1 << 32 | p2);
}

size_t jm::serializeLEDouble(uint8* buffer, size_t offset, double value)
{
   uint64 ival = std::bit_cast<uint64>(value);

   buffer[offset] = (uint8)ival;
   ival >>= 8;
   buffer[offset + 1] = (uint8)ival;
   ival >>= 8;
   buffer[offset + 2] = (uint8)ival;
   ival >>= 8;
   buffer[offset + 3] = (uint8)ival;
   ival >>= 8;
   buffer[offset + 4] = (uint8)ival;
   ival >>= 8;
   buffer[offset + 5] = (uint8)ival;
   ival >>= 8;
   buffer[offset + 6] = (uint8)ival;
   ival >>= 8;
   buffer[offset + 7] = (uint8)ival;

   return 8;
}

size_t jm::serializeLEDouble(jm::ByteArray& buffer, size_t offset, double value)
{
   return jm::serializeLEDouble((uint8*)buffer.data(), offset, value);
}


size_t jm::serializeLEFloat(uint8* buffer, size_t offset, float value)
{
   uint32 ival = std::bit_cast<uint32>(value);

   buffer[offset] = (uint8)ival;
   ival >>= 8;
   buffer[offset + 1] = (uint8)ival;
   ival >>= 8;
   buffer[offset + 2] = (uint8)ival;
   ival >>= 8;
   buffer[offset + 3] = (uint8)ival;

   return 4;
}

double jm::deserializeLEDouble(const uint8* buffer, size_t offset)
{
   return *(const double*)&buffer[offset];
}

double jm::deserializeLEDouble(const jm::ByteArray& buffer, size_t offset)
{
   return *(const double*)&buffer.constData()[offset];
}

float jm::deserializeLEFloat(const uint8* buffer, size_t offset)
{
   return *(const float*)&buffer[offset];
}
