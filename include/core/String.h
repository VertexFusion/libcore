////////////////////////////////////////////////////////////////////////////////////////////////////
// Name:        Strings.h
// Library:     Jameo Core Library
// Purpose:     Declaration of String class
//
// Author:      Uwe Runtemund (2012-today)
// Modified by:
// Created:     08.10.2012
//
// Copyright:   (c) 2012 Jameo Software, Germany. https://jameo.de
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

#ifndef jm_String_h
#define jm_String_h

#ifdef __APPLE__
#include <CoreFoundation/CFString.h>
#endif

#include "Object.h"
#include "ByteArray.h"
#include "CharArray.h"
#include "Integer.h"
#include "Double.h"

namespace jm
{
   class Charset;
   class ByteArray;
   class StringList;

   /*!
    \brief \c string implements our generic string because \c std::string is inadequate and
    inconvenient. The internal character encoding is Unicode (UTF-8).

    For the conversion from std::string to jm::String the following call can be used:
    \code{.cpp}
    std::string msg = "Hello World!";
    jm::String str = jm::String(msg.c_str());
    \endcode

     \ingroup core
    */
   class DllExport String: public Object, public Comparable<String>
   {

      public:

         /*!
          \brief Constructor for empty string.
          */
         String();

         /*!
          \brief This constructor generates a character string. The encoding is the standard encoding (UTF-8).
          \param cstring A C-string that represents the character string. A C string is characterized by the fact that the end of the character string is symbolized by a 0 byte.
          */
         String(const char* cstring);

         /*!
          \brief This constructor generates a character string. The encoding is the standard encoding (UTF-8).
          \param buffer A C-string that represents the character string. A C string is characterized by the fact that the end of the character string is symbolized by a 0 byte.
          */
         String(const ByteArray& buffer);

         /*!
          \brief This constructor generates a character string.
          \param cstring A C-string that represents the character string. A C string is characterized by the fact that the end of the character string is symbolized by a 0 byte.
          \param charset The coding with which the character string is encoded.
          */
         String(const char* cstring, Charset* charset);

         /*!
          \brief This constructor generates a character string.
          \param buffer A C-string that represents the character string. A C string is characterized by the fact that the end of the character string is symbolized by a 0 byte.
          \param charset The coding with which the character string is encoded.
          */
         String(const ByteArray& buffer, Charset* charset);

         /*!
          \brief This constructor generates a character string. The encoding is the standard encoding (UTF-8).
          \param buffer An array, which contains the string.
          \param size The length of the string.
          */
         String(const char* buffer, Integer size);

         /*!
          \brief This constructor generates a character string. The encoding is the standard encoding (UTF-8).
          \param buffer An array, which contains the string.
          \param size The length of the string.
          */
         String(const uint16* buffer, Integer size);

         /*!
          \brief This constructor generates a character string. The encoding is the standard encoding (UTF-8).
          \param buffer An array, which contains the string.
          \param size The length of the string.
          \param charset The coding with which the character string is encoded.
          */
         String(const char* buffer, Integer size, Charset* charset);

         /*!
          \brief Copy constructor
          */
         String(const String& another);

         /*!
          \brief Destructor
          */
         ~String();

         #ifdef __APPLE__

         /*! \brief Converts from CFString
          \note Only visible on mac
         */
         static String fromCFString(CFStringRef cfstring);

         /*! \brief Converts to CFString
         	\note Only visible on mac
           */
         CFStringRef toCFString()const;
         #endif
         /*!
          \brief Returns the size of the string.
          */
         Integer size() const;

         /*!
          \brief Diese Methode erzeugt unter Berücksichtigung der Standardkodierung (UTF-8) einen
          C-String aus der Zeichenkette.
          \discussion Der erzeugt C-String ist von der Anwendung später wieder freizugeben (delete).
          */
         ByteArray toCString()const;

         /*!
          \brief Diese Methode erzeugt unter Berücksichtigung der Unicode-Kodierung einen
          C-String mit 16bit-Elementen. Defacto ist es eine Kopie des Buffers.
          \discussion Der erzeugt C-String ist von der Anwendung später wieder freizugeben (delete).
          */
         uint16* toWString() const;

         /*!
          \brief Diese Methode erzeugt unter Berücksichtigung der Kodierung einen C-String aus
          der Zeichenkette.
          \param charset Die Zeichenkodierung, mit der die Zeichenkette im C-String kodiert werden
          soll.
          \discussion Der erzeugt C-String ist von der Anwendung später wieder freizugeben (delete).
          */
         ByteArray toCString(Charset* charset)const;

         /*!
          \brief Count the occurences of the character in the string
          */
         Integer count(Char character)const;

         /*!
          \brief Diese Methode löscht den Inhalt der Zeichenkette. GGf. wird Speicher Freigegeben.
          */
         void clear();

         /*!
          \brief Setzt die Länge auf 0, ohne Speicher freizugeben.
          */
         void zero();

         /*!
          \brief Diese Methode hängt eine andere Zeichenkette an diese an.
          \param another Die Zeichenkette, die an das Ende dieser Zeichenkette angehängt werden
          soll.
          */
         void append(const String& another);

         /*!
          \brief Diese Methode hängt einen Buchstaben an diese Zeichenkette an.
          \param unicodechar Der Unicode-Codepunkt, Buchstabe, der an diese Zeichenkette angehängt
          werden soll.
          */
         void append(Char unicodechar);

         /*!
          \brief Diese Methode löscht einen Buchstaben aus dieser Zeichenkette heraus.
          \param index Der 0-basierte Index der Position des Buchstabens.
          */
         void deleteCharAt(Integer index);

         /*!
          \brief Diese Methode löscht einen Abschnitt aus dieser Zeichenkette heraus.
          \param index Der 0-basierte Index der Position des Anfangs.
          \param length Die Länge des Abschnitts
          */
         void deleteCharRangeAt(Integer index, Integer length);

         /*!
          \copydoc jm::Object::equals()
          */
         bool equals(const Object* other) const override;

         /*!
          \brief Diese Methode prüft, ob diese Zeichenkette identisch zu einer anderen ist. Dabei
          wird Buchstabe für Buchstabe geprüft, ob die Zeichen exakt übereinstimmen.
          \param another Die Zeichenkette, mit der diese verglichen wird.
          \return Gibt "wahr" zurück, wenn beide Zeichenketten identsich sind, ansonsten "falsch".
          Z.B. "abc" == "abc" ist wahr, aber "aBc" == "abc" ist falsch.
          */
         bool equals(const String& another) const;

         /*!
          \brief Diese Methode vergleicht die Reihenfolge der Strings. Es wird streng
          Zeichenweise von links nach rechts verglichen.
          \param another Die Zeichenkette, mit der diese verglichen wird.
          */
         int32 compareTo(const String& another) const override;

         /*!
          \brief Diese Methode vergleicht die Reihenfolge der Strings. Es wird unter
          Berücksichtigung von Zahlen verglichen. Bestandteile, die als Zahl verstanden werden,
          werden für sich verglichen. Aufgrund von Einschränkungen im MS-C++-Kompiler werden zur
          Zeit aus Effizienzgründen nur maximal die ersten 256 Zeichen verglichen.
          \param another Die Zeichenkette, mit der diese verglichen wird.
          */
         int32 compareFancyTo(const String& another) const;

         /*!
          \brief Diese Methode prüft unter vernachlässigung der Klein- und Großbuchstaben, ob
          diese Zeichenkette mit der anderen identisch ist.
          \param another Die Zeichenkette, mit der diese verglichen wird.
          \return Gibt "wahr" zurück, wenn beide Zeichenketten identsich sind, ansonsten "falsch".
          Z.B. "abc" == "abc" ist wahr, aber "aBc" == "abc" ist auch wahr.
          */
         bool equalsIgnoreCase(const String& another) const;

         /*!
          \brief Diese Methode prüft, ob der Anfang dieser Zeichenkette mit der anderen
          Zeichenkette übereinstimmt.
          \param another Die Zeichenkette mit der geprüft wird.
          \return Diese Methode gibt wahr zurück, wenn diese Zeichenkette mit der andereren beginnt.
          Sollte another länger sein, als diese Zeichenkette, wird immer falsch zurückgegeben.
          */
         bool startsWith(const String& another) const;

         /*!
          \brief Diese Methode prüft, ob das Ende dieser Zeichenkette mit der anderen
          Zeichenkette übereinstimmt.
          \param another Die Zeichenkette mit der geprüft wird.
          \return Diese Methode gibt wahr zurück, wenn diese Zeichenkette mit der andereren endet.
          Sollte another länger sein, als diese Zeichenkette, wird immer falsch zurückgegeben.
          */
         bool endsWith(const String& another) const;

         /*!
          \brief This method checks, is the string at position is the same as the other string.
          \param position The position where another string is expected
          \param another The comaring string
          \return Returns \c true is the substring sequence at position is the same as \c another.
          Otherwise \c false
          */
         bool atIs(Integer position, const String& another);

         /*!
          \brief Same as atIs, but ignoring case.
          \param position The position where another string is expected
          \param another The comaring string
          \return Returns \c true is the substring sequence at position is the same as \c another.
          Otherwise \c false
          */
         bool atIsIgnoreCase(Integer position, const String& another);

         /*!
          \brief Diese Methode berechnet den Hashcode für diese Zeichenkette und gibt ihn zurück.
          */
         Integer hashCode();
         Integer constHashCode() const;

         /*!
          \brief Diese Methode gibt eine Zeichenkette zurück, in der alle Großbuchstaben durch
          Kleinbuchstaben ersetzt wurden
          */
         String toLowerCase() const;

         /*!
          \brief Diese Methode gibt eine Zeichenkette zurück, in der alle Kleinbuchstaben durch
          Großbuchstaben ersetzt wurden
          */
         String toUpperCase() const;

         /*!
          \brief Diese Methode erzeugt eine Zeichenkette, die nur auf einem Teil dieser
          Zeichenkette besteht.
          \param beginIndex Der 0-basierte Index auf den ersten Buchstaben, der in der neuen
          Zeichenkette übernommen werden soll.
          \return Eine neue Zeichenkette, die ab dem beginIndex beginnt und bis zum Ende der
          Zeichenkette geht.
          */
         String substring(Integer beginIndex)const;

         /*!
          \brief Diese Methode erzeugt eine Zeichenkette, die nur auf einem Teil dieser
          Zeichenkette besteht.
          \param beginIndex Der 0-basierte Index auf den ersten Buchstaben, der in der neuen
          Zeichenkette übernommen werden soll.
          \param endIndex Der 0-basierte Index auf den ersten Buchstaben, der in der neuen
          Zeichenkette nicht übernommen werden soll.
          \return Eine neue Zeichenkette, die ab dem beginIndex beginnt und einen Buchstaben vor dem
          endIndex endet..
          */
         String substring(Integer beginIndex, Integer endIndex) const;

         /*!
          \brief Diese Methode gibt eine neue Zeichenkette zurück, an der alle nicht sichtbaren
          Textzeichen (Whitespaces) am Anfang und am Ende der Zeichenkette entfernt wurden.
          */
         String trim() const;

         /*!
          \brief Diese Methode ersetzt Buchstaben in der Zeichenkette. Der "alte" Buchstabe wird
          an allen Positionen durch den "neuen" Buchstaben ersetzt.
          \param oldChar Der alte Buchstabe, der ersetzt werden soll.
          \param newChar Der neue Buchstabe, mit dem der alte ersetzt werden soll.
          \return Die Zeichenkette mit den Ersetzungen.
          */
         String replace(Char oldChar, Char newChar) const;

         /*!
          \brief Diese Methode ersetzt Zeichenketten in der Zeichenkette. Die "alte" Zeichenkette
          wird an allen Positionen durch die "neue" Zeichenkette ersetzt.
          \param oldStr Die alte Zeichenkette, die ersetzt werden soll.
          \param newStr Die neue Zeichenkette, mit der die alte ersetzt werden soll.
          \return Die Zeichenkette mit den Ersetzungen.
          */
         String replaceAll(String oldStr, String newStr) const;

         /*!
          \brief Diese Methode dreht die Reihenfolge der Zeichen um
          */
         String reverse() const;

         /*!
          \brief Splits the string into a list of strings, using the char as separator.
          */
         StringList split(Char character);

         /*!
          \brief Diese Methode gibt die 0-basiert Position des ersten Vorkommens des gewünschten
          Zeichens in der Zeichenkette zurück.
          \param character Das Zeichen, nach dem gesucht wird.
          \return Gibt den 0-basierten Index zurück, oder -1, wenn das Zeichen in der Zeichenkette
          nicht vorkommt.
          */
         Integer indexOf(Char character) const;

         /*!
          \brief Diese Methode gibt die 0-basiert Position des ersten Vorkommens der gewünschten
          Zeichenkette in der Zeichenkette zurück.
          \param str Die Zeichenkette, nach der gesucht wird.
          \return Gibt den 0-basierten Index zurück, oder -1, wenn das Zeichen in der Zeichenkette
          nicht vorkommt.
          */
         Integer indexOf(const String& str) const;


         /*!
          \brief Diese Methode gibt die 0-basiert Position des ersten Vorkommens des gewünschten
          Zeichens in der Zeichenkette zurück.
          \param character Das Zeichen, nach dem gesucht wird.
          \param fromIndex Die 0-basierte Position, ab der nach dem Zeichen gesucht werden soll.
          \return Gibt den 0-basierten Index zurück, oder -1, wenn das Zeichen in der Zeichenkette
          nicht vorkommt.
          */
         Integer indexOf(Char character, Integer fromIndex) const;

         /*!
          \brief Diese Methode gibt die 0-basiert Position des ersten Vorkommens der gewünschten
          Zeichenkette in der Zeichenkette zurück.
          \param str Die Zeichenkette, nach der gesucht wird.
          \param fromIndex Die Position, ab der gesucht wird.
          \return Gibt den 0-basierten Index zurück, oder -1, wenn das Zeichen in der Zeichenkette
          nicht vorkommt.
          */
         Integer indexOf(const String& str, Integer fromIndex) const;

         /*!
          \brief Diese Methode gibt die 0-basiert Position des letzten Vorkommens des gewünschten
          Zeichens in der Zeichenkette zurück.
          \discussion Man kann diese Methode auch so verstehen, dass vom Ende der Zeichenkette nach
          dem ersten Vorkommend des Zeichens gesucht wird.
          \param character Das Zeichen, nach dem gesucht wird.
          \return Gibt den 0-basierten Index zurück, oder -1, wenn das Zeichen in der Zeichenkette
          nicht vorkommt.
          */
         Integer lastIndexOf(Char character) const;

         /*!
          \brief Diese Methode gibt die 0-basiert Position des letzten Vorkommens der gewünschten
          Zeichenkette in der Zeichenkette zurück.
          \discussion Man kann diese Methode auch so verstehen, dass vom Ende der Zeichenkette nach
          dem ersten Vorkommend des Zeichens gesucht wird.
          \param str Die Zeichenkette, nach der gesucht wird.
          \return Gibt den 0-basierten Index zurück, oder -1, wenn das Zeichen in der Zeichenkette
          nicht vorkommt.
          */
         Integer lastIndexOf(const String& str) const;


         /*!
          \brief Diese Methode gibt die 0-basiert Position des letzten Vorkommens des gewünschten
          Zeichens in der Zeichenkette zurück.
          \discussion Man kann diese Methode auch so verstehen, dass vom Ende der Zeichenkette nach
          dem ersten Vorkommend des Zeichens gesucht wird.
          \param character Das Zeichen, nach dem gesucht wird.
          \param fromIndex Der 0-basierte Index, ab dem (von hinten) gesucht wird
          \return Gibt den 0-basierten Index zurück, oder -1, wenn das Zeichen in der Zeichenkette
          nicht vorkommt.
          */
         Integer lastIndexOf(Char character, Integer fromIndex) const;

         /*!
          \brief Diese Methode gibt die 0-basiert Position des letzten Vorkommens der gewünschten
          Zeichenkette in der Zeichenkette zurück.
          \discussion Man kann diese Methode auch so verstehen, dass vom Ende der Zeichenkette nach
          dem ersten Vorkommend des Zeichens gesucht wird.
          \param str Die Zeichenkette, nach der gesucht wird.
          \param fromIndex Der 0-basierte Index, ab dem (von hinten) gesucht wird
          \return Gibt den 0-basierten Index zurück, oder -1, wenn das Zeichen in der Zeichenkette
          nicht vorkommt.
          */
         Integer lastIndexOf(const String& str, Integer fromIndex) const;

         /*!
          \brief Diese Methode gibt das Zeichen an einer bestimmten Position in der Zeichenkette
          zurück.
          \param index Der 0-basierte Index, dessen Zeichen gewünscht ist.
          */
         Char charAt(Integer index) const;

         /*!
          \brief Diese Methode ersetzt ein Zeichen in der Zeichenkette durch ein Neues.
          \param index Der 0-basierte Index des Zeichens, der ersetzt werden soll.
          \param character Das Zeichen, welches eingesetzt werden soll.
          */
         void setCharAt(Integer index, Char character);

         /*!
          \brief Diese Methode fügt ein Zeichen in die Zeichenkette an der Position index ein
          und veschiebt alle Zeichen danach nach rechts
          \param index Der 0-basierte Index des Zeichens, an dem der Buchstabe eingefügt werden soll
          \param character Das Zeichen, welches eingefügt werden soll
          */
         void insert(Integer index, Char character);

         /*!
          \brief Diese Methode fügt eine Zeichenkette in die Zeichenkette an der Position index ein
          und veschiebt alle Zeichen danach nach rechts
          \param index Der 0-basierte Index des Zeichens, an dem der Buchstabe eingefügt werden soll
          \param string Die Zeichenkette, welchee eingefügt werden soll
          */
         void insert(Integer index, const String& string);

         /*!
          \brief Searches in the string for a %n (e.g. %1, %2 etc) with the lowest number and
          replace it by a string representation of the number
          */
         String arg(Integer valueInteger,
                    Integer fieldwidth = 0,
                    Char fillchar = Char(' '));

         /*!
          \brief Searches in the string for a %n (e.g. %1, %2 etc) with the lowest number and
          replace it by a string representation of the number
          */
         String arg(const String& value,
                    Integer fieldwidth = 0,
                    Char fillchar = Char(' '));

         String arg(Char character,
                    Integer fieldwidth = 0,
                    Char fillchar = Char(' '));

         /*!
          \brief Searches in the string for a %n (e.g. %1, %2 etc) with the lowest number and
          replace it by a string representation of the number
          \param value The number value.
          \param fieldwidth The (minimum) number of characters for the value. If fieldwidth is >0
          the leading space is filled (right align). If fieldwidth is < 0 the trailing space is
          filled (left align).
          \param precision The number of digits after the descimal separator.
          \param fillchar The character for filling the space, until fieldwidth chars are reached.
          */
         String arg(Double value,
                    Integer fieldwidth = 0,
                    Integer precision = -1,
                    Char fillchar = Char(' '));

         String arg(double value,
                    Integer fieldwidth = 0,
                    Integer precision = -1,
                    Char fillchar = Char(' '))
         {
            return arg(Double(value), fieldwidth, precision, fillchar);
         };

         static void setConsoleCharset(Charset* cs);

         // Operators
         String& operator=(const String& another);
         String& operator+=(const String& another);

         // Friends
         DllExport
         friend bool operator==(String const& v1, String const& v2);

         DllExport
         friend bool operator!=(String const& v1, String const& v2);

         DllExport
         friend std::ostream& operator<< (std::ostream& out, const String& str);

         DllExport
         friend String& operator<< (String& out, const String& str);

         DllExport
         friend String& operator<< (String& out, const Integer& i);

         DllExport
         friend String& operator<< (String& out, const uint64& i);

         DllExport
         friend String& operator<< (String& out, const int64& i);

         DllExport
         friend String& operator<< (String& out, const int32& i);

         DllExport
         friend String& operator<< (String& out, const uint32& i);

         DllExport
         friend String& operator<< (String& out, const double& d);

         DllExport
         friend String& operator<< (String& out, const char& c);

         DllExport
         friend String& operator<< (String& out, const Char& c);

         DllExport
         friend std::istream& operator>> (std::istream& in, String& str);

         DllExport
         friend String operator+(const String& left, const String& right);

         DllExport
         friend String operator+(const char*& left, const String& right);

         DllExport
         friend String operator+(const String& left, const char*& right);

         DllExport
         friend String operator+(int64& left, const String& right);

         DllExport
         friend String operator+(const String& left, int64& right);

         DllExport
         friend String operator+(double& left, const String& right);

         DllExport
         friend String operator+(const String& left, double& right);

         DllExport
         friend String operator+(const int8& left, const String& right);

         DllExport
         friend String operator+(const String& left, const int8& right);

         DllExport
         friend bool operator<(const String& left, const String& right);

         /*
          *
          * STATIC METHODS
          *
          */

         /*!
            \brief Converts a double into a string.
            \param number The double value.
            \return A string representing the double value. eg. "12.23" or "24.0".
            */
         static String valueOf(double number);

         /*!
          \brief Converts the double to decimal String
          \param number The double value.
          \param precision Number of digits after .
          \param trunc Truncate trailing 0 ?
          */
         static String valueOf(double number, Integer precision, bool trunc);


         /*!
          \brief Converts a integer into a string.
          \param number The value
          \return A String representing the int value. eg. "12" or "24".
          */
         static String valueOf(int64 number);
         static String valueOf(uint64 number);
         static String valueOf(int32 number);
         static String valueOf(uint32 number);

         /*!
          \brief Converts a bool value into a string.
          \param value The value.
          \return "true" if true and "false" if false.
          */
         static String valueOf(bool value);

         /*!
          \brief Returns operation system dependent line separator.
          */
         static String lineSeparator();

         /*!
          \brief This method checks, if the string has the capacity to hold more bytes.
          If not, the array will be enlarged.
          \param more The number of additional bytes.
          */
         void checkCapacity(Integer more);

      private:

         //! This char array stores the content of the string. The length of the string can be
         //! bigger than the string itself. In principle, the characters are unicode encoded.
         //! Valid values are in the range of 0x0000 - 0xFFFF.
         Char* mValue;

         //! Length of array.
         Integer mArrLength;

         //! Length of string.
         Integer mStrLength;

         //! Stored hashvalue for operation. Is 0 if not initialized.
         int32 mHash;

         /*!
          \brief This method copies the content of CharArrays into this string.
          \param array The source CharArray.
          */
         void copy(const CharArray& array);

         //! Helper method for arg.
         bool argIndicies(Integer& first, Integer& second);

   };

   /*!
    \brief Method converts a String into a double.

    This method is similar to Double::ValueFrom(), but as a decimal divider a point
    or a comma is accepted.
    \param str The string in form: "1.23".
    \return The expected double number.
    */
   extern DllExport
   double ConvertToDouble(String str);

   extern DllExport
   String URLDecode(const String& str);

   extern DllExport
   String URLEncode(const String& str);

   static String kEmptyString = "";
}

#endif
