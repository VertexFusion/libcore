////////////////////////////////////////////////////////////////////////////////////////////////////
// Name:        Integer.h
// Library:     VertexFusion Library
// Purpose:     Integer class
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

#ifndef jm_Integer_h
#define jm_Integer_h

#include "String.h"

namespace jm
{


	/*!
	 \brief This class represents an integer number as an object. This makes it easy to perform
	 certain object operations.
	 \ingroup core
	 */
	class DllExport Integer : public Object, public Comparable<Integer>
	{
		public:

			Integer();

			Integer(int64 value);

			/*!
			 \copydoc jm::Object::Equals()
			 */
			bool Equals(const Object* other) const override;

			bool Equals(const Integer& another) const;

			int32 CompareTo(const Integer& another) const override;

			int64 Value() const;

			/*!
			 \brief Methode wandelt einen String in einen Integer-Wert um.
			 \param string Die Zeichenkette, z.B. "1", die in eine Gleitkommazahl umgewandelt werden
			 soll.
			 \return Die gewünschte Integer-Zahl.
			 */
			static int64 ValueOf(const String& string);

			/*!
			 \brief Methode wandelt einen eine Integer-Zahl in einen hexadezimalen String-Wert um.
			 \param number Die Integer-Zahl, welche in einen std::string umgewandelt werden soll.
			 \return Gibt die gewünschte Zahl als String zurück, der eine hexadezimale Darstellung ist.
			 Also z.B. "FF" für 255.
			 */
			static String ToHexString(uint64 number);

			/*!
			 \brief Methode wandelt einen eine Integer-Zahl in einen hexadezimalen String-Wert um.
			 \param number Die Integer-Zahl, welche in einen std::string umgewandelt werden soll.
			 \return Gibt die gewünschte Zahl als String zurück, der eine hexadezimale Darstellung ist.
			 Also z.B. "FF" für 255.
			 */
			static String ToHexString(Integer number);

			/*!
			 \brief Methode wandelt eine Integer-Zahl in einen String um, der eine Römische Zahl
			 darstellt.
			 @aram number Die Integer-Zahl, welche umgewandelt werden soll.
			 \return Gibt die gewünschte Zahl als String mit dem Wert einer Römischen Zahl zurück.
			 */
			static String ToRomanString(uint64 number);

			/*!
			 \brief Methode wandelt eine Integer-Zahl in einen String um, der einm Großbuchstaben
			 entspricht. 1=A,2=C,3=C usw-
			 \param number Die Integer-Zahl, welche umgewandelt werden soll.
			 \return Gibt die gewünschte Zahl als String mit dem Wert eines Großbuchstaben zurück.
			 */
			static String ToLatinAlphabetString(uint64 number);

		private:

			int64 mValue;
	};
}
#endif
