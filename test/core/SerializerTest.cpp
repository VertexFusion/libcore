//
//  MatrixTest.cpp
//  jameo
//
//  Created by Uwe Runtemund on 18.04.14.
//  Copyright (c) 2014 Jameo Software. All rights reserved.
//

#include "SerializerTest.h"

#include "core/Serializer.h"

using namespace jm;

SerializerTest::SerializerTest(): Test()
{
   setName("Test Serializer");
}

void SerializerTest::doTest()
{
   //
   // int16 conversion
   //
   int16 i16in = -32768;
   int16 i16out = 0;
   uint8 buffer[8];

   size_t count = jm::serializeBEInt16(buffer, 0, i16in);
   i16out = jm::deserializeBEInt16(buffer, 0);
   testTrue(count == 2, "int16 conversion failed");
   testEquals(i16in, i16out, "int16 conversion failed");
   testEquals(buffer[0], 0x80, "int16 conversion failed");
   testEquals(buffer[1], 0x00, "int16 conversion failed");

   count = jm::serializeLEInt16(buffer, 0, i16in);
   i16out = jm::deserializeLEInt16(buffer, 0);
   testTrue(count == 2, "int16 conversion failed");
   testEquals(i16in, i16out, "int16 conversion failed");
   testEquals(buffer[0], 0x00, "int16 conversion failed");
   testEquals(buffer[1], 0x80, "int16 conversion failed");

   i16in = 1234;
   count = jm::serializeBEInt16(buffer, 0, i16in);
   i16out = jm::deserializeBEInt16(buffer, 0);
   testTrue(count == 2, "int16 conversion failed");
   testEquals(i16in, i16out, "int16 conversion failed");
   testEquals(buffer[0], 0x04, "int16 conversion failed");
   testEquals(buffer[1], 0xd2, "int16 conversion failed");

   count = jm::serializeLEInt16(buffer, 0, i16in);
   i16out = jm::deserializeLEInt16(buffer, 0);
   testTrue(count == 2, "int16 conversion failed");
   testEquals(i16in, i16out, "int16 conversion failed");
   testEquals(buffer[0], 0xd2, "int16 conversion failed");
   testEquals(buffer[1], 0x04, "int16 conversion failed");

   //
   // int24 conversion
   //
   int32 i32in = 0x123456;
   int32 i32out = 0;

   count = jm::serializeBEInt24(buffer, 0, i32in);
   i32out = jm::deserializeBEInt24(buffer, 0);
   testTrue(count == 3, "int24 conversion failed");
   testEquals(i32in, i32out, "int24 conversion failed");
   testEquals(buffer[0], 0x12, "int24 conversion failed");
   testEquals(buffer[1], 0x34, "int24 conversion failed");
   testEquals(buffer[2], 0x56, "int24 conversion failed");

   count = jm::serializeLEInt24(buffer, 0, i32in);
   i32out = jm::deserializeLEInt24(buffer, 0);
   testTrue(count == 3, "int24 conversion failed");
   testEquals(i32in, i32out, "int24 conversion failed");
   testEquals(buffer[0], 0x56, "int24 conversion failed");
   testEquals(buffer[1], 0x34, "int24 conversion failed");
   testEquals(buffer[2], 0x12, "int24 conversion failed");

   //
   // int32 conversion
   //
   i32in = 0x12345678;
   i32out = 0;

   count = jm::serializeBEInt32(buffer, 0, i32in);
   i32out = jm::deserializeBEInt32(jm::ByteArray(buffer), 0);
   testTrue(count == 4, "int32 conversion failed");
   testEquals(i32in, i32out, "int32 conversion failed");
   testEquals(buffer[0], 0x12, "int32 conversion failed");
   testEquals(buffer[1], 0x34, "int32 conversion failed");
   testEquals(buffer[2], 0x56, "int32 conversion failed");
   testEquals(buffer[3], 0x78, "int32 conversion failed");

   count = jm::serializeLEInt32(buffer, 0, i32in);
   i32out = jm::deserializeLEInt32(buffer, 0);
   testTrue(count == 4, "int32 conversion failed");
   testEquals(i32in, i32out, "int32 conversion failed");
   testEquals(buffer[0], 0x78, "int32 conversion failed");
   testEquals(buffer[1], 0x56, "int32 conversion failed");
   testEquals(buffer[2], 0x34, "int32 conversion failed");
   testEquals(buffer[3], 0x12, "int32 conversion failed");

   //
   // int64 conversion
   //
   int64 i64in = 0x123456789abcdef0;
   int64 i64out = 0;
   count = jm::serializeBEInt64(buffer, 0, i64in);
   i64out = jm::deserializeBEInt64(buffer, 0);
   testTrue(count == 8, "int64 conversion failed");
   testEquals(i64in, i64out, "int64 conversion failed");
   testEquals(buffer[0], 0x12, "int64 conversion failed");
   testEquals(buffer[1], 0x34, "int64 conversion failed");
   testEquals(buffer[2], 0x56, "int64 conversion failed");
   testEquals(buffer[3], 0x78, "int64 conversion failed");
   testEquals(buffer[4], 0x9a, "int64 conversion failed");
   testEquals(buffer[5], 0xbc, "int64 conversion failed");
   testEquals(buffer[6], 0xde, "int64 conversion failed");
   testEquals(buffer[7], 0xf0, "int64 conversion failed");

   count = jm::serializeLEInt64(buffer, 0, i64in);
   i64out = jm::deserializeLEInt64(buffer, 0);
   testTrue(count == 8, "int64 conversion failed");
   testEquals(i64in, i64out, "int64 conversion failed");
   testEquals(buffer[0], 0xf0, "int64 conversion failed");
   testEquals(buffer[1], 0xde, "int64 conversion failed");
   testEquals(buffer[2], 0xbc, "int64 conversion failed");
   testEquals(buffer[3], 0x9a, "int64 conversion failed");
   testEquals(buffer[4], 0x78, "int64 conversion failed");
   testEquals(buffer[5], 0x56, "int64 conversion failed");
   testEquals(buffer[6], 0x34, "int64 conversion failed");
   testEquals(buffer[7], 0x12, "int64 conversion failed");

   //
   // uint16 conversion
   //
   uint16 u16in = 0x1234;
   uint16 u16out = 0;

   count = jm::serializeBEUInt16(buffer, 0, u16in);
   u16out = jm::deserializeBEUInt16(buffer, 0);
   testTrue(count == 2, "uint16 conversion failed");
   testEquals(u16in, u16out, "uint16 conversion failed");
   testEquals(buffer[0], 0x12, "uint16 conversion failed");
   testEquals(buffer[1], 0x34, "uint16 conversion failed");

   count = jm::serializeLEUInt16(buffer, 0, u16in);
   u16out = jm::deserializeLEUInt16(buffer, 0);
   testTrue(count == 2, "uint16 conversion failed");
   testEquals(u16in, u16out, "uint16 conversion failed");
   testEquals(buffer[0], 0x34, "uint16 conversion failed");
   testEquals(buffer[1], 0x12, "uint16 conversion failed");

   //
   // float conversion
   //
   float f32in = 1234.5678f;
   float f32out = 0.0f;
   count = jm::serializeLEFloat(buffer, 0, f32in);
   f32out = jm::deserializeLEFloat(buffer, 0);
   testTrue(count == 4, "float conversion failed");
   testEquals(f32in, f32out, "float conversion failed");
   testEquals(buffer[0], 0x2b, "float conversion failed 0");
   testEquals(buffer[1], 0x52, "float conversion failed 1");
   testEquals(buffer[2], 0x9a, "float conversion failed 2");
   testEquals(buffer[3], 0x44, "float conversion failed 3");

   //
   // double conversion
   //
   double f64in = 1234.56789124;
   double f64out = 0.0;
   count = jm::serializeLEDouble(buffer, 0, f64in);
   f64out = jm::deserializeLEDouble(buffer, 0);
   testTrue(count == 8, "double conversion failed");
   testEquals(f64in, f64out, "double conversion failed");
   testEquals(buffer[0], 0xF1, "double conversion failed 0");
   testEquals(buffer[1], 0xFd, "double conversion failed 1");
   testEquals(buffer[2], 0x47, "double conversion failed 2");
   testEquals(buffer[3], 0x85, "double conversion failed 3");
   testEquals(buffer[4], 0x45, "double conversion failed 4");
   testEquals(buffer[5], 0x4A, "double conversion failed 5");
   testEquals(buffer[6], 0x93, "double conversion failed 6");
   testEquals(buffer[7], 0x40, "double conversion failed 7");

}
