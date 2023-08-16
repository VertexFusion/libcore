////////////////////////////////////////////////////////////////////////////////////////////////////
// Name:        Base64.h
// Library:     VertexFusion Library
// Purpose:     Base64 Encoding/Decoding
//
// Author:      Uwe Runtemund (2020-today)
// Modified by:
// Created:     28.12.2020
//
// Copyright:   (c) 2020 Jameo Software, Germany. https://jameo.de
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
#ifndef jm_Base64_h
#define jm_Base64_h

#include "String.h"

namespace jm
{

	/*!
	 \brief Implementation of the BASE64-algorithm.
	 \ingroup core
	 */
	class DllExport Base64
	{
		public:

			/*!
			 \brief Kodiert den Datenstrom mit dem BASE64-Algorithmus
			 \param data Die Daten, die kodiert werden sollen,
			 \param length Die Länge des Eingabepuffers. Nach Verlassen der Methode wird hier die Länge
			        des Ausgabepuffers zurückgegeben
			 \return Den Ausgabepuffer. Der Aufrufer der Methode übernimmt das Array und muss es selbst
			         aufräumen.
			 */
			static uint8* Encode(const uint8* data, uint32 &length);

			/*!
			 \brief Dekodiert den Datenstrom mit dem BASE64-Algorithmus
			 \param data Die Daten, die kodiert werden sollen,
			 \param length Die Länge des Eingabepuffers. Nach Verlassen der Methode wird hier die Länge
			        des Ausgabepuffers zurückgegeben
			 \return Den Ausgabepuffer. Der Aufrufer der Methode übernimmt das Array und muss es selbst
			         aufräumen.
			 */
			static uint8* Decode(const uint8* data, uint32 &length);

	};

}

#endif /* Base64_h */
