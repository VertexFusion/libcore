////////////////////////////////////////////////////////////////////////////////////////////////////
// Name:        Deflater.h
// Library:     Jameo Core Library
// Purpose:     Deflate Algorithm
//
// Author:      Uwe Runtemund (2015-today)
// Modified by:
// Created:     15.09.2013
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

#ifndef jm_Deflater_h
#define jm_Deflater_h

#include "Types.h"
#include "Object.h"

namespace jm
{

	/*!
	 \brief Compression class for DEFLATE-compressed data.
	 The basis is RFC 1950 and RFC 1951.
	 As of 2017-01-14, the own implementation was exchanged in favour of zlib.
	 \ingroup core
	 */
	class DllExport Deflater: public Object
	{

		public:

			/*!
			 \brief Konstruktor
			 */
			Deflater();

			/*!
			 \brief Konstruktor
			 \param wrap Status, ob zlib-Header und CRC weggelassen wird
			 */
			//Deflater( bool wrap );

			/*!
			 \brief Destructor
			 */
			~Deflater();

			/*!
			 \brief Übergibt einen Block an Bytes zum Kompriemieren an diese Klasse.
			 \param buffer Die unkomprimierten Daten
			 \param length Die Länge der Daten
			 */
			void SetInput(uint8* buffer,
							  Integer length);

			/*!
			 \brief Diese Methode komprimiert die Daten in den Puffer
			 \discussion beide Parameter sind Ausgabewerte und werden durch diese Methode initialisiert.
			 Der Aufrufer muss das Array hinterher selbst aufräumen.
			 \param buffer Der Puffer, in den die Daten geschrieben werden sollen.
			 \param length Die Länge des Puffers
			 */
			void Deflate(uint8* &buffer,
							 Integer &length);

			/*!
			 \brief Setzt den Komprimierer zurück, damit ein neues Objekt komprimiert werden kann
			 */
			void Reset();

			/*!
			 \brief Gibt die Gesamtanzahl der Bytes des unkomprimierten Inputs zurück
			 */
			Integer GetTotalIn();

			/*!
			 \brief Gibt die Gesamtanzahl der Bytes des komprimierten Outputs zurück
			 */
			Integer GetTotalOut();

		private:

			//Aktueller Block
			uint8* mUncompBytes;
			Integer mUncompLength;
			Integer mUncompIndex;

			//Zählvariablen für verarbeitete Bytes
			Integer mTotalIn;
			Integer mTotalOut;

	};

}

#endif
