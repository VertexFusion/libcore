////////////////////////////////////////////////////////////////////////////////////////////////////
// Name:        Charset.h
// Library:     Jameo Core Library
// Purpose:     Character Encodings
//
// Author:      Uwe Runtemund (2013-today)
// Modified by:
// Created:     18.01.2013
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

#ifndef jm_Charset_h
#define jm_Charset_h

#include "CharArray.h"
#include "String.h"

namespace jm
{

	/*!
	 \brief The class Charset is a mapping function to make a string out of arbitrarily coded
	 C-strings, or vice versa.
	 \ingroup core
	 */
	class DllExport CharsetDecoder: public Object
	{
		public:
			/*!
			 \brief Constructor
			 */
			CharsetDecoder();

			/*!
			 \brief Destructor
			 */
			virtual ~CharsetDecoder();

			/*!
			 \brief Diese Methode dekodiert einen C-String unter Verwendung der in dem Dekoder
			 implementierten Kodierung und wandelt ihn in ein Unicodecodiertes CharArray.
			 \param cString Der C-String, der umgewandelt werden soll.
			 \return Das CharArray, welches die Unicode-codierte Repräsentation des C-Strings enthält.
			 */
			virtual CharArray Decode(const int8* cString) = 0;

			/*!
			 \brief Diese Methode kodiert unter Verwendung der in dem Dekoder implementierten
			 Kodierung den übergebenen String in einen kodierten C-String.
			 \param string der Unicodecodierte String, der umgewandelt werden sollt.
			 \return Einen C-String, dessen Kodierung durch diesen Dekoder bestimmt ist.
			 */
			virtual int8* Encode(const CharArray &string) = 0;

	};

	/*!
	 \brief  The class Charset is a factory class to make a string out of arbitrarily coded C-strings
	 and vice versa.
	 \ingroup core
	 */
	class DllExport Charset: public Object
	{

		public:

			/*!
			 \brief Spezialkonstruktor für die statische Initialisierung des DefaultDecoders. Das
			 ist immer die UTF-8-Kodierung.
			 */
			Charset(CharsetDecoder* decoder);

			/*!
			 \brief Konstruktor für statische Initialisierung (daher kein String)
			 \param name Name des Zeichensatzes
			 \param decoder Der Dekoder für diesen Zeichensatz
			 */
			Charset(const int8* name,
			        CharsetDecoder* decoder);

			/*!
			 \brief Konstruktor
			 \param name Name des Zeichensatzes
			 \param alternatives Alternative Namen für den Zeichensatz
			 \param altCount Anzahl der Alternativen Namen für diesen Zeichensatz
			 \param decoder Der Dekoder für diesen Zeichensatz
			 */
			Charset(const String &name,
			        const String* alternatives,
			        uint8 altCount, CharsetDecoder*
			        decoder);

			/*!
			 \brief Destructor
			 */
			virtual ~Charset();

			/*!
			 \brief Diese Methode gibt den Namen des Zeichensatzes zurück.
			 */
			String Name();

			/*!
			 \brief Diese Methode prüft, ob dieser Zeichensatz unter dem gewünschten Namen
			 angesprochen wird.
			 \param name der Name, nach dem geprüft werden soll.
			 \return Gibt wahr zurück, wenn entweder der Name des Zeichensatzes mit name übereinstimmt,
			 oder wenn einer der alternativen Namen mit name übereinstimmt. Andernfalls wird falsch
			 zurückgegebn.
			 */
			bool HasName(const String &name);

			/*!
			 \brief Diese Methode dekodiert den C-String und erzeugt ein Chararray, welches durch
			 die Kodierung umgewandelt wurde.
			 \param cString Der C-String, welcher umgewandelt werden soll.
			 */
			CharArray Decode(const int8* cString);

			/*!
			 \brief Diese Methode erzeugt aus einem String den entsprechenden C-String unter
			 Verwendung dieses Zeichensatzes.
			 \param string Der String, welcher umgewandlet werden soll.
			 */
			int8* Encode(const CharArray &string);

			/*!
			 \brief This method returns the desired charset by name.
			 \param name The name of the charset.
			 \return The charset, or NULL, if the charset for name was not found.
			 */
			static Charset* ForName(const String &name);

			/*!
			 \brief Diese Methode gibt das Standardcharset zurück (UTF-8)
			 */
			static Charset* GetDefault();

			/*!
			 \brief Diese Methode errät vom übergebenen Array die Zeichenkodierung und gibt den
			 erratenen Namen zurück. Wird kein Zeichensatz erkannt, wir je nach Betriebsyste der
			 Standardzeichensatz zurüclgegeben.
			 Dies ist unter
			 - Windows: Windows-1252
			 - Mac: MacRoman
			 - Linux: UTF-8
			 Es heißt aber nicht, dass automatisch Kein Zeichensatz erkannt wurde, wenn einer der
			 obigen Werte zurückgegeben wurde.
			 */
			static String Guess(uint8* stream,
			                    uint32 length);

		private:

			/*!
			 \brief Anzahl der Zeichenkodierungen
			 */
			static uint16 gCharsetCount;

			/*!
			 \brief Array mit den Zeichenkodierungen
			 */
			static Charset* gCharsets[];

			/*!
			\brief Der Name dieses Zeichensatzes. Z.B. UTF-8
			*/
			String mName;

			/*!
			\brief Ein Feld mit alternativen Namen, wenn dieser Zeichensatz mehrere gebräuchliche
			 Namen besitzt.
			*/
			String* mAlternatives;

			/*!
			\brief Anzahl der alternativen Namen.
			*/
			uint8 mAltCount;

			/*!
			\brief Die Kodierfunktion für diesen Zeichensatz.
			*/
			CharsetDecoder* mDecoder;

			friend void QuitCharsets();
	};

	/*!
	 \brief Decoder converts the bytes 1 to 1. Only the LSB is taken into account. Values > 255 are
	 therefore truncated.
	 \ingroup core
	 */
	class DllExport RawDecoder: public CharsetDecoder
	{
		public:
			RawDecoder();
			CharArray Decode(const int8* cString);
			int8* Encode(const CharArray &string);
	};

	/*!
	 \brief Decoder for UTF8 encoding.
	 \ingroup core
	 */
	class DllExport UTF8Decoder: public CharsetDecoder
	{
		public:
			UTF8Decoder();
			CharArray Decode(const int8* cString);
			int8* Encode(const CharArray &string);
	};


	/*!
	 \brief Decoder for UTF16 encoding.
	 \ingroup core
	 */
	class DllExport UTF16Decoder: public CharsetDecoder
	{
		private:
			bool be;
		public:
			UTF16Decoder(bool isBE);
			CharArray Decode(const int8* cString);
			int8* Encode(const CharArray &string);
	};

	/*!
	 \brief  Decoder for Windows CP 1252 encoding.
	 \ingroup core
	 */
	class DllExport Windows1252Decoder: public CharsetDecoder
	{
		private:
			uint16* codepage;

		public:
			Windows1252Decoder();
			~Windows1252Decoder();
			CharArray Decode(const int8* cString);
			int8* Encode(const CharArray &string);
	};

	/*!
	 \brief Decoder for Macintosh Roman Codierung (CP 10000) encoding.
	 \ingroup core
	 */
	class DllExport MacRomanDecoder: public CharsetDecoder
	{
		private:
			uint16* codepage;

		public:
			MacRomanDecoder();
			~MacRomanDecoder();
			CharArray Decode(const int8* cString);
			int8* Encode(const CharArray &string);

			uint16 DecodeCharacter(uint8 macencode);
			uint8 EncodeCharacter(uint16 unicode);
	};

	/*!
	\brief Initialisisiert die Charsets.
	\discussion Wird von System::Init aufgerufen. Daher kein Export notwendig
	*/
	void InitCharsets();

	/*!
	\brief Löscht die Charsetobjekte
	\discussion Wird von System::Quit aufgerufen. Dahr kein Export notwendig
	*/
	void QuitCharsets();


	/*!
	 \brief Diese Methode wandelt einen Unicodezeichen in den entsprechen Kleinbuchstaben um, wenn
	 er einen korrespondierenden Kleinbuchstaben besitzt.
	 \param input Das Unicodezeichen, welches umgewandelt werden soll.
	 \return Den korrespondierenden Kleinbuchstaben, wenn er existiert, ansonsten den Eingabewert.
	 */
	uint16 DllExport CharacterToLowerCase(uint16 input);

	/*!
	 \brief Diese Methode wandelt einen Unicodezeichen in den entsprechen Großbuchstaben um, wenn
	 er einen korrespondierenden Großbuchstaben besitzt.
	 \param input Das Unicodezeichen, welches umgewandelt werden soll.
	 \return Den korrespondierenden Großbuchstaben, wenn er existiert, ansonsten den Eingabewert.
	 */
	uint16 DllExport CharacterToUpperCase(uint16 input);

	/*!
	 \brief Diese Methode prüft, ob ein Unicodezeichen ein unsichtbares Textzeichen ist.
	 \param input Das Unicodezeichen, welches geprüft werden soll
	 */
	bool DllExport CharacterIsWhitespace(uint16 input);

	/*!
	 \brief Diese Methode prüft, ob ein Unicodezeichen ein unsichtbares Textzeichen ist.
	 \param input Das Unicodezeichen, welches geprüft werden soll
	 */
	bool DllExport CharacterIsDigit(uint16 input);

}

#endif
