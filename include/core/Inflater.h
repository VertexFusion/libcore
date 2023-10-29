////////////////////////////////////////////////////////////////////////////////////////////////////
// Name:        Inflater.h
// Library:     Jameo Core Library
// Purpose:     Itrator Interface
//
// Author:      Uwe Runtemund (2013-today)
// Modified by:
// Created:     06.09.2013
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

#ifndef jm_Inflater_h
#define jm_Inflater_h

#include "Array.h"

namespace jm
{

	/*!
	 \brief Decompression class for DEFLATE-compressed data.
	 Basis are RFC 1950 and RFC 1951.
	 \ingroup core
	 */
	class DllExport Inflater: public Object
	{
		private:

			//Der Baum wird analog zu RFC 1951 aufgebaut.
			//
			struct HuffmanTree
			{
				HuffmanTree* node0;
				HuffmanTree* node1;
				uint16 symbol;
				uint16 length;
				uint16 code;
				uint16 tmp;
				HuffmanTree();
				~HuffmanTree();
				HuffmanTree* Find(uint16 code, uint16 bits);
			};

			//Aktueller Block
			uint8* mCompBytes;
			uint32 mCompLength;
			uint32 mCompIndex;

			//Aktueller Block
			uint8* mUncompBytes;
			uint32 mUncompLength;
			uint32 mUncompIndex;

			//Zählvariablen für verarbeitete Bytes
			uint32 mTotalIn;
			uint32 mTotalOut;

			int32 mBit;//index auf das aktuelle Bit im aktuellen byte.

			//Status, ob der letzte Block eingelesen wurde
			bool mLastBlock;

			//Status, ob Ende des Streams erreicht wurde
			bool mEof;

			//Status, ob zlib-Header und CRC weggelassen wird
			bool mWrap;

			//Größte Bitanzahl im Aktuellen Hufmann tree
			uint16 MAX_BITS;

			/*!
			 \brief Liest nächstes Bit ein aus dem Eingabestrom ein.
			 */
			uint8 NextBit();

			/*!
			 \brief Überspringt alle Bits bis zum Ende des aktuellen Bytes im Eingabestrom und springt zum Anfang des nächsten Bytes.
			 Steht man bereits an einem Byteanfang, passiert nichts.
			 */
			void SkipByteBits();

			/*!
			 \brief Gibt das nächste "ausgerichtete" Byte zurück. Man muss am Byteanfang stehen.
			 @throws Wenn man nicht am Byteanfang steht, gibts einen Fehler.
			 */
			uint8 NextAlignedUInt8();

			/*!
			 \brief Liest ein UINT16 nach LE ein. Man muss am Byteanfang stehen.
			 @throws Wenn man nicht am Byteanfang steht, gibts einen Fehler.
			 */
			uint16 NextAlignedUInt16();

			/*!
			 \brief Liest die nächsten X bits als Zahl ein. Bytegrenzen werden ignoriert.
			 Das MSB (Most significant bit) wird als erstes eingelesen.
			 \param bits Die Anzahl der Bits
			 */
			uint16 NextUIntX(uint8 bits);

			/*!
			 \brief Liest die nächsten X bits als Zahl ein. Bytegrenzen werden ignoriert
			 Das LSB (Least significant bit) wird als erstes eingelesen.
			 \param bits Die Anzahl der Bits
			 */
			uint16 NextUIntXR(uint8 bits);

			HuffmanTree* CreateTree(Array<uint16>* lengths, Array<uint16>* codes);

			uint16 DecodeHuffmanSymbol(Inflater::HuffmanTree* tree);

			Array<uint16>* GetHuffmanCodes(Array<uint16>* codelengths);

			//Schreibt das Byte in den die Ausgabe
			void WriteUncompressed(uint8 byte);

			/*!
			 \brief Diese Methode wird für die "BTYPE=01" Kodierung "Fixed Huffman Codes" gebraucht.
			 Sie liest den nächsten "Fixed Huffman Code" ein und dekodiert ihn zu dem gewünschten Zahlenwert.
			 */
			uint16 NextFixedHuffmanCode();

			void HandleUncompressedBlock();

			void HandleCompressedFixHuffman();

			void HandleCompressedDynamicHuffman();

			void ReadLengthDists(Array<uint16>* target, Inflater::HuffmanTree* tree, int32 count);

			void Inflate();

			void CheckCapacity();


		public:
			/*!
			 \brief Konstruktor
			 */
			Inflater();

			/*!
			 \brief Konstruktor
			 \param wrap Status, ob zlib-Header und CRC weggelassen wird
			 */
			Inflater(bool wrap);

			/*!
			 \brief Destructor
			 */
			~Inflater();

			/*!
			 \brief Übergibt einen Block an Bytes zum Dekomprimieren an diese Klasse.
			 \param buffer Die komprimierten Daten
			 \param length Die Länge der Daten
			 */
			void SetInput(uint8* buffer, uint32 length);

			/*!
			 \brief Gibt "wahr" zurück, wenn das Ende des Inputblocks erreicht ist, aber das Ende des Eingabestroms
			 noch nicht erreicht wurde
			 */
			bool NeedsInput();

			/*!
			 \brief Gibt "wahr" zurück, wenn das Ende des Eingabestroms erreicht wurde.
			 */
			bool Finished();

			/*!
			 \brief Diese Methode dekomprimiert die Daten in den Puffer
			 \discussion beide Parameter sind Ausgabewerte und werden durch diese Methode initialisiert. Der Aufrufer muss das Array hinterher selbst aufräumen.
			 \param buffer Der Puffer, in den die Daten geschrieben werden sollen.
			 \param length Die Länge des Puffers
			 */
			void Inflate(uint8* &buffer, uint32 &length);

			/*!
			 \brief Setzt den Dekomprimierer zurück, damit ein neues Objekt dekomprimiert werden kann
			 */
			void Reset();

			/*!
			 \brief Gibt die Anzahl der "übrig gebliebenen" Bytes im Inputpuffer zurück
			 */
			int32 GetRemaining();

			/*!
			 \brief Gibt die Gesamtanzahl der Bytes des komprimierten Inputs zurück
			 */
			int32 GetTotalIn();

			/*!
			 \brief Gibt die Gesamtanzahl der Bytes des dekomprimierten Outputs zurück
			 */
			int32 GetTotalOut();

	};

}
#endif
