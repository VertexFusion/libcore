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
   int16 SerializeBEInt16(uint8* buffer, uint32 offset, int16 value);

   /*!
    \brief This method serializes a number using the Big-Endian method.
    \param buffer The byte buffer where the number will be written.
    \param offset The zero-based index of the position where the first byte is located.
    \param value The number to be converted.
    \return Returns the number of bytes written.
    */
   DllExport
   int16 SerializeBEInt24(uint8* buffer, uint32 offset, int32 value);

   /*!
    \brief This method serializes a number using the Big-Endian method.
    \param buffer The byte buffer where the number will be written.
    \param offset The zero-based index of the position where the first byte is located.
    \param value The number to be converted.
    \return Returns the number of bytes written.
    */
   DllExport
   int16 SerializeBEInt32(uint8* buffer, uint32 offset, int32 value);

   /*!
    \brief This method serializes a number using the Big-Endian method.
    \param buffer The byte buffer where the number will be written.
    \param offset The zero-based index of the position where the first byte is located.
    \param value The number to be converted.
    \return Returns the number of bytes written.
    */
   DllExport
   int16 SerializeBEInt64(uint8* buffer, uint32 offset, int64 value);

   /*!
    \brief This method serializes a number using the Little-Endian method.
    \param buffer The byte buffer where the number will be written.
    \param offset The zero-based index of the position where the first byte is located.
    \param value The number to be converted.
    \return Returns the number of bytes written.
    */
   DllExport
   int16 SerializeLEInt16(uint8* buffer, uint32 offset, int16 value);

   /*!
    \brief This method serializes a number using the Little-Endian method.
    \param buffer The byte buffer where the number will be written.
    \param offset The zero-based index of the position where the first byte is located.
    \param value The number to be converted.
    \return Returns the number of bytes written.
    */
   DllExport
   int16 SerializeLEUInt16(uint8* buffer, uint32 offset, uint16 value);

   /*!
    \brief This method serializes a number using the Little-Endian method.
    \param buffer The byte buffer where the number will be written.
    \param offset The zero-based index of the position where the first byte is located.
    \param value The number to be converted.
    \return Returns the number of bytes written.
    */
   DllExport
   int16 SerializeLEInt24(uint8* buffer, uint32 offset, int32 value);

   /*!
    \brief This method serializes a number using the Little-Endian method.
    \param buffer The byte buffer where the number will be written.
    \param offset The zero-based index of the position where the first byte is located.
    \param value The number to be converted.
    \return Returns the number of bytes written.
    */
   DllExport
   int16 SerializeLEInt32(uint8* buffer, uint32 offset, int32 value);

   /*!
    \brief This method serializes a number using the Little-Endian method.
    \param buffer The byte buffer where the number will be written.
    \param offset The zero-based index of the position where the first byte is located.
    \param value The number to be converted.
    \return Returns the number of bytes written.
    */
   DllExport
   int16 SerializeLEInt64(uint8* buffer, uint32 offset, int64 value);

   /*!
    \brief This method serializes a number using the Little-Endian method.
    \param buffer The byte buffer where the number will be written.
    \param offset The zero-based index of the position where the first byte is located.
    \param value The number to be converted.
    \return Returns the number of bytes written.
    */
   DllExport
   int16 SerializeLEDouble(uint8* buffer, uint32 offset, double value);

   /*!
    \brief This method serializes a number using the Little-Endian method.
    \param buffer The byte buffer where the number will be written.
    \param offset The zero-based index of the position where the first byte is located.
    \param value The number to be converted.
    \return Returns the number of bytes written.
    */
   DllExport
   int16 SerializeLEFloat(uint8* buffer, uint32 offset, float value);


   /*!
    \brief This method deserializes a number using the Big-Endian method.
    \param buffer The byte buffer where the number is located.
    \param offset The zero-based index of the position where the first byte is located.
    \return Returns the deserialized number as uint16.
    */
   DllExport
   uint16 DeserializeBEUInt16(uint8* buffer, uint32 offset);

   /*!
    \brief This method deserializes a number using the Big-Endian method.
    \param buffer The byte buffer where the number is located.
    \param offset The zero-based index of the position where the first byte is located.
    \return Returns the deserialized number as int16.
    */
   DllExport
   int16 DeserializeBEInt16(uint8* buffer, uint32 offset);

   /*!
    \brief This method deserializes a number using the Big-Endian method.
    \param buffer The byte buffer where the number is located.
    \param offset The zero-based index of the position where the first byte is located.
    \return Returns the deserialized number as uint32.
    */
   DllExport
   uint32 DeserializeBEUInt32(uint8* buffer, uint32 offset);

   /*!
    \brief This method deserializes a number using the Big-Endian method.
    \param buffer The byte buffer where the number is located.
    \param offset The zero-based index of the position where the first byte is located.
    \return Returns the deserialized number as int64.
    */
   DllExport
   int64 DeserializeBEInt64(uint8* buffer, uint32 offset);

   /*!
    \brief This method deserializes a number using the Little-Endian method.
    \param buffer The byte buffer where the number is located.
    \param offset The zero-based index of the position where the first byte is located.
    \return Returns the deserialized number as uint16.
    */
   DllExport
   uint16 DeserializeLEUInt16(uint8* buffer, uint32 offset);
   uint16 DeserializeLEUInt16(const jm::ByteArray& buffer, uint32 offset);

   /*!
    \brief This method deserializes a number using the Little-Endian method.
    \param buffer The byte buffer where the number is located.
    \param offset The zero-based index of the position where the first byte is located.
    \return Returns the deserialized number as int16.
    */
   DllExport
   int16 DeserializeLEInt16(uint8* buffer, uint32 offset);
   int16 DeserializeLEInt16(const jm::ByteArray& buffer, Integer offset);

   /*!
    \brief This method deserializes a number using the Little-Endian method.
    \param buffer The byte buffer where the number is located.
    \param offset The zero-based index of the position where the first byte is located.
    \return Returns the deserialized number as uint32.
    */
   DllExport
   uint32 DeserializeLEUInt32(uint8* buffer, uint32 offset);
   uint32 DeserializeLEUInt32(const jm::ByteArray& buffer, Integer offset);

   /*!
    \brief This method deserializes a number using the Little-Endian method.
    \param buffer The byte buffer where the number is located.
    \param offset The zero-based index of the position where the first byte is located.
    \return Returns the deserialized number as int32.
    */
   DllExport
   int32 DeserializeLEInt32(uint8* buffer, uint32 offset);
   int32 DeserializeLEInt32(const jm::ByteArray& buffer, Integer offset);

   /*!
    \brief This method deserializes a number using the Little-Endian method.
    \param buffer The byte buffer where the number is located.
    \param offset The zero-based index of the position where the first byte is located.
    \return Returns the deserialized number as int64.
    */
   DllExport
   int64 DeserializeLEInt64(uint8* buffer, uint32 offset);
   Integer DeserializeLEInt64(const jm::ByteArray& buffer, Integer offset);

   /*!
    \brief This method deserializes a number using the Little-Endian method.
    \param buffer The byte buffer where the number is located.
    \param offset The zero-based index of the position where the first byte is located.
    \return Returns the deserialized number as double.
    */
   DllExport
   double DeserializeLEDouble(uint8* buffer, uint32 offset);
   double DeserializeLEDouble(const jm::ByteArray& buffer, Integer offset);

   /*!
    \brief This method deserializes a number using the Little-Endian method.
    \param buffer The byte buffer where the number is located.
    \param offset The zero-based index of the position where the first byte is located.
    \return Returns the deserialized number as float.
    */
   DllExport
   float DeserializeLEFloat(uint8* buffer, uint32 offset);
   DllExport

}

#endif
