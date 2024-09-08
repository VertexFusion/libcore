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

#include "Precompiled.hpp"


int16 jm::serializeBEInt16(uint8* buffer, uint32 offset, int16 value)
{
   buffer[offset + 1] = (uint8)value;
   value >>= 8;
   buffer[offset] = (uint8)value;
   return 2;
}

int16 jm::serializeBEInt24(uint8* buffer, uint32 offset, int32 value)
{
   buffer[offset + 2] = (uint8)value;
   value >>= 8;
   buffer[offset + 1] = (uint8)value;
   value >>= 8;
   buffer[offset] = (uint8)value;
   return 3;
}

int16 jm::serializeBEInt32(uint8* buffer, uint32 offset, int32 value)
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

int16 jm::serializeBEInt64(uint8* buffer, uint32 offset, int64 value)
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

int16 jm::serializeLEInt16(uint8* buffer, uint32 offset, int16 value)
{
   buffer[offset] = (uint8)value;
   value >>= 8;
   buffer[offset + 1] = (uint8)value;
   return 2;
}

int16 jm::serializeLEUInt16(uint8* buffer, uint32 offset, uint16 value)
{
   buffer[offset] = (uint8)value;
   value >>= 8;
   buffer[offset + 1] = (uint8)value;
   return 2;
}

int16 jm::serializeLEInt24(uint8* buffer, uint32 offset, int32 value)
{
   buffer[offset] = (uint8)value;
   value >>= 8;
   buffer[offset + 1] = (uint8)value;
   value >>= 8;
   buffer[offset + 2] = (uint8)value;
   return 3;
}

int16 jm::serializeLEInt32(uint8* buffer, uint32 offset, int32 value)
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

int16 jm::serializeLEInt64(uint8* buffer, uint32 offset, int64 value)
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

uint16 jm::deserializeBEUInt16(uint8* buffer, uint32 offset)
{
   return (buffer[offset] << 8 | buffer[offset + 1]);
}

int16 jm::deserializeBEInt16(uint8* buffer, uint32 offset)
{
   return (buffer[offset] << 8 | buffer[offset + 1]);
}

uint32 jm::deserializeBEUInt32(uint8* buffer, uint32 offset)
{
   return (buffer[offset] << 24 | buffer[offset + 1] << 16 | buffer[offset + 2] << 8 | buffer[offset +
           3]);
}

int64 jm::deserializeBEInt64(uint8* buffer, uint32 offset)
{
   int64 p1 = deserializeBEUInt32(buffer, offset);
   int64 p2 = deserializeBEUInt32(buffer, offset + 4);
   return (p1 << 32 | p2);
}

uint16 jm::deserializeLEUInt16(const uint8* buffer, uint32 offset)
{
   return (buffer[offset + 1] << 8 | buffer[offset]);
}

uint16 jm::deserializeLEUInt16(const jm::ByteArray& buffer, uint32 offset)
{
   return (buffer[offset + 1] << 8 | buffer[offset]);
}

int16 jm::deserializeLEInt16(uint8* buffer, uint32 offset)
{
   return (buffer[offset + 1] << 8 | buffer[offset]);
}

int16 jm::deserializeLEInt16(const jm::ByteArray& buffer, int64 offset)
{
   return (buffer[offset + 1] << 8 | buffer[offset]);
}

uint32 jm::deserializeLEUInt32(uint8* buffer, uint32 offset)
{
   return (buffer[offset + 3] << 24 | buffer[offset + 2] << 16 | buffer[offset + 1] << 8 |
           buffer[offset]);
}

uint32 jm::deserializeLEUInt32(const jm::ByteArray& buffer, int64 offset)
{
   return (buffer[offset + 3] << 24 | buffer[offset + 2] << 16 | buffer[offset + 1] << 8 |
           buffer[offset]);
}

int32 jm::deserializeLEInt32(uint8* buffer, uint32 offset)
{
   return (buffer[offset + 3] << 24 | buffer[offset + 2] << 16 | buffer[offset + 1] << 8 |
           buffer[offset]);
}

int32 jm::deserializeLEInt32(const jm::ByteArray& buffer, int64 offset)
{
   return (buffer[offset + 3] << 24 | buffer[offset + 2] << 16 | buffer[offset + 1] << 8 |
           buffer[offset]);
}

int64 jm::deserializeLEInt64(uint8* buffer, uint32 offset)
{
   int64 p1 = deserializeLEUInt32(buffer, offset + 4);
   int64 p2 = deserializeLEUInt32(buffer, offset);
   return (p1 << 32 | p2);
}

int64 jm::deserializeLEInt64(const jm::ByteArray& buffer, int64 offset)
{
   int64 p1 = deserializeLEUInt32(buffer, offset + 4);
   int64 p2 = deserializeLEUInt32(buffer, offset);
   return (p1 << 32 | p2);
}

int16 jm::serializeLEDouble(uint8* buffer, uint32 offset, double value)
{
   union conv
   {
      uint64 ival;
      double dval;
   };

   conv c;
   c.dval = value;

   buffer[offset] = (uint8)c.ival;
   c.ival >>= 8;
   buffer[offset + 1] = (uint8)c.ival;
   c.ival >>= 8;
   buffer[offset + 2] = (uint8)c.ival;
   c.ival >>= 8;
   buffer[offset + 3] = (uint8)c.ival;
   c.ival >>= 8;
   buffer[offset + 4] = (uint8)c.ival;
   c.ival >>= 8;
   buffer[offset + 5] = (uint8)c.ival;
   c.ival >>= 8;
   buffer[offset + 6] = (uint8)c.ival;
   c.ival >>= 8;
   buffer[offset + 7] = (uint8)c.ival;

   return 8;
}

int16 jm::serializeLEFloat(uint8* buffer, uint32 offset, float value)
{
   union conv
   {
      uint64 ival;
      float fval;
   };

   conv c;
   c.fval = value;

   buffer[offset] = (uint8)c.ival;
   c.ival >>= 8;
   buffer[offset + 1] = (uint8)c.ival;
   c.ival >>= 8;
   buffer[offset + 2] = (uint8)c.ival;
   c.ival >>= 8;
   buffer[offset + 3] = (uint8)c.ival;

   return 4;
}

double jm::deserializeLEDouble(uint8* buffer, uint32 offset)
{
   return *(double*)&buffer[offset];
}

double jm::deserializeLEDouble(const jm::ByteArray& buffer, int64 offset)
{
   return *(double*)&buffer[offset];
}

float jm::deserializeLEFloat(uint8* buffer, uint32 offset)
{
   return *(float*)&buffer[offset];
}
