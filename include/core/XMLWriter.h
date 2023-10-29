////////////////////////////////////////////////////////////////////////////////////////////////////
// Name:        XMLWriter.h
// Library:     VertexFusion Library
// Purpose:     Write XML-Files
//
// Author:      Uwe Runtemund (2020-today)
// Modified by:
// Created:     27.12.2020
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

#ifndef jm_XMLWriter_h
#define jm_XMLWriter_h

#include "String.h"
#include "Stack.h"

namespace jm
{

	/*!
	 \brief Diese Klasse \c XMLWriter stellt Methoden zur Verfügung, um XML-Daten zu schreiben.
	 */
	class DllExport XMLWriter: public Object
	{
		public:

			/*!
			 \brief Konstruktor
			 \param output Der \c Stream, in dem die XML-Daten geschrieben werden sollen.
			 */
			XMLWriter(Stream* output);

			virtual ~XMLWriter();

			/*!
			 \brief Diese Methode muss am Anfang aufgerufen werden. Hier wird der Stream geöffnet,
			 falls das noch nicht geschehen ist.
			 \return true Wenn alles in Ordnung ist.
			 */
			bool StartDocument();

			/*!
			 \brief Diese Methode muss am Ende aufgerufen werden. Hier wird der Stream geschlossen
			 \return true Wenn alles in Ordnung ist.
			 */
			bool EndDocument();

			/*!
			 \brief Einzug erhöhen
			 \discussion In XML sind Whitespaces zum Teil relevant. Wo sie relevant sind und wo nicht,
			 ist vom Dokument abhängig.  Diese Methode führt einen Einzug aus und erhöht ihn.
			 */
			void StartIndent();
			/*!
			 \brief Einzug erniedrigen
			 \discussion In XML sind Whitespaces zum Teil relevant. Wo sie relevant sind und wo nicht,
			 ist vom Dokument abhängig. Diese Methode führt einen Einzug aus und erhöht ihn.
			 */
			void EndIndent();


			/*!
			 \brief Diese Methode öffnet ein neues XML-Element
			 */
			void StartElement(const String &name);

			/*!
			 \brief Diese Methode schreibt ein XML-Attribut in das offene Start-Element.
			 \warning Diese Methode muss aufgerufen werden, bevor Inhalte zu einem Element geschrieben
			 werden.
			 */
			void WriteAttribute(const String &name, const String &content);

			/*!
			 \brief Diese Methode schreibt ein XML-Attribut in das offene Start-Element.
			 \warning Diese Methode muss aufgerufen werden, bevor Inhalte zu einem Element geschrieben
			 werden.
			 */
			void WriteAttribute(const String &name, int32 content);

			/*!
			 \brief Diese Methode schreibt ein XML-Attribut in das offene Start-Element.
			 \warning Diese Methode muss aufgerufen werden, bevor Inhalte zu einem Element geschrieben
			 werden.
			 */
			void WriteAttribute(const String &name, uint32 content);

			/*!
			 \brief Diese Methode schreibt ein XML-Attribut in das offene Start-Element.
			 \warning Diese Methode muss aufgerufen werden, bevor Inhalte zu einem Element geschrieben
			 werden.
			 */
			void WriteAttribute(const String &name, float content);

			/*!
			 \brief Diese Methode schließt das aktuell offene XML-Element. Wenn das Element keine
			 Inhalte hat, wird ein <.../>-Element geschrieben
			 */
			void EndElement();

			/*!
			 \brief Schreibt Daten.
			 \param cdata Die Buchstaben
			 \param xmlencode Wenn wahr (Standard), dann werden bestimmte Zeichen (z.B. & -> &amp;)
			 "xml"-kodiert.
			 */
			void WriteCDATA(const String &cdata, bool xmlencode = true);

			/*!
			 \brief Schreibt Daten und kodiert sie mit dem BASE64-Algorithmus
			 \param data Die uncodierten Daten
			 */
			void WriteBase64(uint8 *data, uint32 length);


		private:

			Stream* mOutput;

			int32 mIndent;

			bool mLastIndent;

			struct ElementInfo
			{
				String name;
				bool indent;
				bool hasContent;
				bool hasCharacters;

				ElementInfo()
				{
					indent = false;
					hasContent = false;
					hasCharacters = false;
				}

			};

			Stack<ElementInfo>* mOpenElements;

			String Encode(const String &input);

			void WriteIndent();
	};

}

#endif /* XMLWriter_h */
