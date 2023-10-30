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
	 \brief Diese Methode serialisiert eine Zahl nach der Big-Endian-Methode
	 \param buffer Der Bytebuffer, in dem die Zahl geschrieben werden soll.
	 \param offset Der 0-basierte Index der Position an dem das erste Byte steht.
	 \param value Die Zahl, die umgewandelt werden soll
	 \return Gibt die Anzahl der geschriebenen Bytes zurück.
	 */
	DllExport
	int16 SerializeBEInt16(uint8* buffer, uint32 offset, int16 value);

	/*!
	 \brief Diese Methode serialisiert eine Zahl nach der Big-Endian-Methode
	 \param buffer Der Bytebuffer, in dem die Zahl geschrieben werden soll.
	 \param offset Der 0-basierte Index der Position an dem das erste Byte steht.
	 \param value Die Zahl, die umgewandelt werden soll
	 \return Gibt die Anzahl der geschriebenen Bytes zurück.
	 */
	DllExport
	int16 SerializeBEInt24(uint8* buffer, uint32 offset, int32 value);

	/*!
	 \brief Diese Methode serialisiert eine Zahl nach der Big-Endian-Methode
	 \param buffer Der Bytebuffer, in dem die Zahl geschrieben werden soll.
	 \param offset Der 0-basierte Index der Position an dem das erste Byte steht.
	 \param value Die Zahl, die umgewandelt werden soll
	 \return Gibt die Anzahl der geschriebenen Bytes zurück.
	 */
	DllExport
	int16 SerializeBEInt32(uint8* buffer, uint32 offset, int32 value);

	/*!
	 \brief Diese Methode serialisiert eine Zahl nach der Big-Endian-Methode
	 \param buffer Der Bytebuffer, in dem die Zahl geschrieben werden soll.
	 \param offset Der 0-basierte Index der Position an dem das erste Byte steht.
	 \param value Die Zahl, die umgewandelt werden soll
	 \return Gibt die Anzahl der geschriebenen Bytes zurück.
	 */
	DllExport
	int16 SerializeBEInt64(uint8* buffer, uint32 offset, int64 value);

	/*!
	 \brief Diese Methode serialisiert eine Zahl nach der Litte-Endian-Methode
	 \param buffer Der Bytebuffer, in dem die Zahl geschrieben werden soll.
	 \param offset Der 0-basierte Index der Position an dem das erste Byte steht.
	 \param value Die Zahl, die umgewandelt werden soll
	 \return Gibt die Anzahl der geschriebenen Bytes zurück.
	 */
	DllExport
	int16 SerializeLEInt16(uint8* buffer, uint32 offset, int16 value);

	DllExport
	int16 SerializeLEUInt16(uint8* buffer, uint32 offset, uint16 value);

	/*!
	 \brief Diese Methode serialisiert eine Zahl nach der Little-Endian-Methode
	 \param buffer Der Bytebuffer, in dem die Zahl geschrieben werden soll.
	 \param offset Der 0-basierte Index der Position an dem das erste Byte steht.
	 \param value Die Zahl, die umgewandelt werden soll
	 \return Gibt die Anzahl der geschriebenen Bytes zurück.
	 */
	DllExport
	int16 SerializeLEInt24(uint8* buffer, uint32 offset, int32 value);

	/*!
	 \brief Diese Methode serialisiert eine Zahl nach der Little-Endian-Methode
	 \param buffer Der Bytebuffer, in dem die Zahl geschrieben werden soll.
	 \param offset Der 0-basierte Index der Position an dem das erste Byte steht.
	 \param value Die Zahl, die umgewandelt werden soll
	 \return Gibt die Anzahl der geschriebenen Bytes zurück.
	 */
	DllExport
	int16 SerializeLEInt32(uint8* buffer, uint32 offset, int32 value);

	/*!
	 \brief Diese Methode serialisiert eine Zahl nach der Litte-Endian-Methode
	 \param buffer Der Bytebuffer, in dem die Zahl geschrieben werden soll.
	 \param offset Der 0-basierte Index der Position an dem das erste Byte steht.
	 \param value Die Zahl, die umgewandelt werden soll
	 \return Gibt die Anzahl der geschriebenen Bytes zurück.
	 */
	DllExport
	int16 SerializeLEInt64(uint8* buffer, uint32 offset, int64 value);

	/*!
	 \brief Diese Methode serialisiert eine Zahl nach der Little-Endian-Methode
	 \param buffer Der Bytebuffer, in dem die Zahl geschrieben werden soll.
	 \param offset Der 0-basierte Index der Position an dem das erste Byte steht.
	 \param value Die Zahl, die umgewandelt werden soll
	 \return Gibt die Anzahl der geschriebenen Bytes zurück.
	 */
	DllExport
	int16 SerializeLEDouble(uint8* buffer, uint32 offset, double value);

	/*!
	 \brief Diese Methode serialisiert eine Zahl nach der Little-Endian-Methode
	 \param buffer Der Bytebuffer, in dem die Zahl geschrieben werden soll.
	 \param offset Der 0-basierte Index der Position an dem das erste Byte steht.
	 \param value Die Zahl, die umgewandelt werden soll
	 \return Gibt die Anzahl der geschriebenen Bytes zurück.
	 */
	DllExport
	int16 SerializeLEFloat(uint8* buffer, uint32 offset, float value);


	/*!
	 \brief Diese Methode deserialisiert eine Zahl nach der Big-Endian-Methode
	 \param buffer Der Bytebuffer, in dem die Zahl steht.
	 \param offset Der 0-basierte Index der Position an dem das erste Byte steht.
	 \return Gibt die deserialisierte Zahl als uint16 zurück
	 */
	DllExport
	uint16 DeserializeBEUInt16(uint8* buffer, uint32 offset);

	/*!
	 \brief Diese Methode deserialisiert eine Zahl nach der Big-Endian-Methode
	 \param buffer Der Bytebuffer, in dem die Zahl steht.
	 \param offset Der 0-basierte Index der Position an dem das erste Byte steht.
	 \return Gibt die deserialisierte Zahl als uint16 zurück
	 */
	DllExport
	int16 DeserializeBEInt16(uint8* buffer, uint32 offset);

	/*!
	 \brief Diese Methode deserialisiert eine Zahl nach der Big-Endian-Methode
	 \param buffer Der Bytebuffer, in dem die Zahl steht.
	 \param offset Der 0-basierte Index der Position an dem das erste Byte steht.
	 \return Gibt die deserialisierte Zahl als uint16 zurück
	 */
	DllExport
	uint32 DeserializeBEUInt32(uint8* buffer, uint32 offset);

	/*!
	 \brief Diese Methode deserialisiert eine Zahl nach der Big-Endian-Methode
	 \param buffer Der Bytebuffer, in dem die Zahl steht.
	 \param offset Der 0-basierte Index der Position an dem das erste Byte steht.
	 \return Gibt die deserialisierte Zahl als uint16 zurück
	 */
	DllExport
	int64 DeserializeBEInt64(uint8* buffer, uint32 offset);

	/*!
	 \brief Diese Methode deserialisiert eine Zahl nach der Little-Endian-Methode
	 \param buffer Der Bytebuffer, in dem die Zahl steht.
	 \param offset Der 0-basierte Index der Position an dem das erste Byte steht.
	 \return Gibt die deserialisierte Zahl als uint16 zurück
	 */
	DllExport
	uint16 DeserializeLEUInt16(uint8* buffer, uint32 offset);

	/*!
	 \brief Diese Methode deserialisiert eine Zahl nach der Little-Endian-Methode
	 \param buffer Der Bytebuffer, in dem die Zahl steht.
	 \param offset Der 0-basierte Index der Position an dem das erste Byte steht.
	 \return Gibt die deserialisierte Zahl als uint16 zurück
	 */
	DllExport
	int16 DeserializeLEInt16(uint8* buffer, uint32 offset);

	/*!
	 \brief Diese Methode deserialisiert eine Zahl nach der Little-Endian-Methode
	 \param buffer Der Bytebuffer, in dem die Zahl steht.
	 \param offset Der 0-basierte Index der Position an dem das erste Byte steht.
	 \return Gibt die deserialisierte Zahl als uint16 zurück
	 */
	DllExport
	uint32 DeserializeLEUInt32(uint8* buffer, uint32 offset);

	/*!
	 \brief Diese Methode deserialisiert eine Zahl nach der Little-Endian-Methode
	 \param buffer Der Bytebuffer, in dem die Zahl steht.
	 \param offset Der 0-basierte Index der Position an dem das erste Byte steht.
	 \return Gibt die deserialisierte Zahl als uint16 zurück
	 */
	DllExport
	int32 DeserializeLEInt32(uint8* buffer, uint32 offset);

	/*!
	 \brief Diese Methode deserialisiert eine Zahl nach der Little-Endian-Methode
	 \param buffer Der Bytebuffer, in dem die Zahl steht.
	 \param offset Der 0-basierte Index der Position an dem das erste Byte steht.
	 \return Gibt die deserialisierte Zahl als uint16 zurück
	 */
	DllExport
	int64 DeserializeLEInt64(uint8* buffer, uint32 offset);

	/*!
	 \brief Diese Methode deserialisiert eine Zahl nach der Little-Endian-Methode
	 \param buffer Der Bytebuffer, in dem die Zahl steht.
	 \param offset Der 0-basierte Index der Position an dem das erste Byte steht.
	 \return Gibt die deserialisierte Zahl als uint16 zurück
	 */
	DllExport
	double DeserializeLEDouble(uint8* buffer, uint32 offset);

	/*!
	 \brief Diese Methode deserialisiert eine Zahl nach der Little-Endian-Methode
	 \param buffer Der Bytebuffer, in dem die Zahl steht.
	 \param offset Der 0-basierte Index der Position an dem das erste Byte steht.
	 \return Gibt die deserialisierte Zahl als uint16 zurück
	 */
	DllExport
	float DeserializeLEFloat(uint8* buffer, uint32 offset);

}

#endif
