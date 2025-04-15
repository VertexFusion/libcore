////////////////////////////////////////////////////////////////////////////////////////////////////
// Name:        Serializer.h
// Library:     Jameo Core Library
// Purpose:     Serialize data type for streams
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

#ifndef jm_Serializer_h
#define jm_Serializer_h

#include "Types.h"

namespace jm
{

   /*!
    \brief This method serializes a number using the Big-Endian method.
    \param buffer The byte buffer where the number will be written.
    \param offset The zero-based index of the position where the first byte is located.
    \param value The number to be converted.
    \return Returns the number of bytes written.
    */
   DllExport
   int16 serializeBEInt16(uint8* buffer, uint32 offset, int16 value);

   /*!
    \brief This method serializes a number using the Big-Endian method.
    \param buffer The byte buffer where the number will be written.
    \param offset The zero-based index of the position where the first byte is located.
    \param value The number to be converted.
    \return Returns the number of bytes written.
    */
   DllExport
   int16 serializeBEInt24(uint8* buffer, uint32 offset, int32 value);

   /*!
    \brief This method serializes a number using the Big-Endian method.
    \param buffer The byte buffer where the number will be written.
    \param offset The zero-based index of the position where the first byte is located.
    \param value The number to be converted.
    \return Returns the number of bytes written.
    */
   DllExport
   int16 serializeBEInt32(uint8* buffer, uint32 offset, int32 value);

   /*!
    \brief This method serializes a number using the Big-Endian method.
    \param buffer The byte buffer where the number will be written.
    \param offset The zero-based index of the position where the first byte is located.
    \param value The number to be converted.
    \return Returns the number of bytes written.
    */
   DllExport
   int16 serializeBEInt64(uint8* buffer, uint32 offset, int64 value);

   /*!
    \brief This method serializes a number using the Little-Endian method.
    \param buffer The byte buffer where the number will be written.
    \param offset The zero-based index of the position where the first byte is located.
    \param value The number to be converted.
    \return Returns the number of bytes written.
    */
   DllExport
   int16 serializeLEInt16(uint8* buffer, uint32 offset, int16 value);

   /*!
    \brief This method serializes a number using the Little-Endian method.
    \param buffer The byte buffer where the number will be written.
    \param offset The zero-based index of the position where the first byte is located.
    \param value The number to be converted.
    \return Returns the number of bytes written.
    */
   DllExport
   int16 serializeLEUInt16(uint8* buffer, uint32 offset, uint16 value);

   /*!
    \brief This method serializes a number using the Little-Endian method.
    \param buffer The byte buffer where the number will be written.
    \param offset The zero-based index of the position where the first byte is located.
    \param value The number to be converted.
    \return Returns the number of bytes written.
    */
   DllExport
   int16 serializeLEInt24(uint8* buffer, uint32 offset, int32 value);

   /*!
    \brief This method serializes a number using the Little-Endian method.
    \param buffer The byte buffer where the number will be written.
    \param offset The zero-based index of the position where the first byte is located.
    \param value The number to be converted.
    \return Returns the number of bytes written.
    */
   DllExport
   int16 serializeLEInt32(uint8* buffer, uint32 offset, int32 value);

   /*!
    \brief This method serializes a number using the Little-Endian method.
    \param buffer The byte buffer where the number will be written.
    \param offset The zero-based index of the position where the first byte is located.
    \param value The number to be converted.
    \return Returns the number of bytes written.
    */
   DllExport
   int16 serializeLEInt64(uint8* buffer, uint32 offset, int64 value);

   /*!
    \brief This method serializes a number using the Little-Endian method.
    \param buffer The byte buffer where the number will be written.
    \param offset The zero-based index of the position where the first byte is located.
    \param value The number to be converted.
    \return Returns the number of bytes written.
    */
   DllExport
   int16 serializeLEDouble(uint8* buffer, uint32 offset, double value);

   /*!
    \brief This method serializes a number using the Little-Endian method.
    \param buffer The byte buffer where the number will be written.
    \param offset The zero-based index of the position where the first byte is located.
    \param value The number to be converted.
    \return Returns the number of bytes written.
    */
   DllExport
   int16 serializeLEFloat(uint8* buffer, uint32 offset, float value);


   /*!
    \brief This method deserializes a number using the Big-Endian method.
    \param buffer The byte buffer where the number is located.
    \param offset The zero-based index of the position where the first byte is located.
    \return Returns the deserialized number as uint16.
    */
   DllExport
   uint16 deserializeBEUInt16(uint8* buffer, uint32 offset);

   /*!
    \brief This method deserializes a number using the Big-Endian method.
    \param buffer The byte buffer where the number is located.
    \param offset The zero-based index of the position where the first byte is located.
    \return Returns the deserialized number as int16.
    */
   DllExport
   int16 deserializeBEInt16(uint8* buffer, uint32 offset);
   int16 deserializeBEInt16(const jm::ByteArray& buffer, int64 offset);

   /*!
    \brief This method deserializes a number using the Big-Endian method.
    \param buffer The byte buffer where the number is located.
    \param offset The zero-based index of the position where the first byte is located.
    \return Returns the deserialized number as uint32.
    */
   DllExport
   uint32 deserializeBEUInt32(uint8* buffer, int64 offset);
   uint32 deserializeBEUInt32(const jm::ByteArray& buffer, int64 offset);

   int32 deserializeBEInt32(const jm::ByteArray& buffer, int64 offset);

   /*!
    \brief This method deserializes a number using the Big-Endian method.
    \param buffer The byte buffer where the number is located.
    \param offset The zero-based index of the position where the first byte is located.
    \return Returns the deserialized number as int64.
    */
   DllExport
   int64 deserializeBEInt64(uint8* buffer, uint32 offset);
   DllExport
      int64 deserializeBEInt64(const jm::ByteArray& buffer, int64 offset);

   /*!
    \brief This method deserializes a number using the Little-Endian method.
    \param buffer The byte buffer where the number is located.
    \param offset The zero-based index of the position where the first byte is located.
    \return Returns the deserialized number as uint16.
    */
   DllExport
   uint16 deserializeLEUInt16(const uint8* buffer, uint32 offset);
   DllExport
      uint16 deserializeLEUInt16(const jm::ByteArray& buffer, uint32 offset);

   /*!
    \brief This method deserializes a number using the Little-Endian method.
    \param buffer The byte buffer where the number is located.
    \param offset The zero-based index of the position where the first byte is located.
    \return Returns the deserialized number as int16.
    */
   DllExport
   int16 deserializeLEInt16(uint8* buffer, uint32 offset);
   DllExport
      int16 deserializeLEInt16(const jm::ByteArray& buffer, int64 offset);

   /*!
    \brief This method deserializes a number using the Little-Endian method.
    \param buffer The byte buffer where the number is located.
    \param offset The zero-based index of the position where the first byte is located.
    \return Returns the deserialized number as uint32.
    */
   DllExport
   uint32 deserializeLEUInt32(uint8* buffer, uint32 offset);
   uint32 deserializeLEUInt32(const jm::ByteArray& buffer, int64 offset);

   /*!
    \brief This method deserializes a number using the Little-Endian method.
    \param buffer The byte buffer where the number is located.
    \param offset The zero-based index of the position where the first byte is located.
    \return Returns the deserialized number as int32.
    */
   DllExport
   int32 deserializeLEInt32(uint8* buffer, uint32 offset);
   int32 deserializeLEInt32(const jm::ByteArray& buffer, int64 offset);

   /*!
    \brief This method deserializes a number using the Little-Endian method.
    \param buffer The byte buffer where the number is located.
    \param offset The zero-based index of the position where the first byte is located.
    \return Returns the deserialized number as int64.
    */
   DllExport
   int64 deserializeLEInt64(uint8* buffer, uint32 offset);
   int64 deserializeLEInt64(const jm::ByteArray& buffer, int64 offset);

   /*!
    \brief This method deserializes a number using the Little-Endian method.
    \param buffer The byte buffer where the number is located.
    \param offset The zero-based index of the position where the first byte is located.
    \return Returns the deserialized number as double.
    */
   DllExport
   double deserializeLEDouble(uint8* buffer, uint32 offset);
   double deserializeLEDouble(const jm::ByteArray& buffer, int64 offset);

   /*!
    \brief This method deserializes a number using the Little-Endian method.
    \param buffer The byte buffer where the number is located.
    \param offset The zero-based index of the position where the first byte is located.
    \return Returns the deserialized number as float.
    */
   DllExport
   float deserializeLEFloat(uint8* buffer, uint32 offset);

}

#endif
