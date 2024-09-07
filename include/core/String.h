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
         String(const char* buffer, int64 size);

         /*!
          \brief This constructor generates a character string. The encoding is the standard encoding (UTF-8).
          \param buffer An array, which contains the string.
          \param size The length of the string.
          */
         String(const uint16* buffer, int64 size);

         /*!
          \brief This constructor generates a character string. The encoding is the standard encoding (UTF-8).
          \param buffer An array, which contains the string.
          \param size The length of the string.
          \param charset The coding with which the character string is encoded.
          */
         String(const char* buffer, int64 size, Charset* charset);

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
         int64 size() const;

          /*!
           \brief This method generates a C-string from the string, taking into account the standard encoding (UTF-8).
           \details The generated C-string must be freed by the application later (delete).
           */
         ByteArray toCString()const;

          /*!
           \brief This method generates a C-string with 16-bit elements, taking into account the Unicode encoding. It is essentially a copy of the buffer.
           \details The generated C-string must be freed by the application later (delete).
           */
         uint16* toWString() const;

          /*!
           \brief This method generates a C-string from the string, taking into account the specified character encoding.
           \param charset The character encoding to use for encoding the string into the C-string.
           \details The generated C-string must be freed by the application later (delete).
           */
         ByteArray toCString(Charset* charset)const;

         /*!
          \brief Count the occurrences of the character in the string
          */
         int64 count(Char character)const;

         /*!
          \brief This method clears the content of the string and releases any allocated memory.
          */
         void clear();

          /*!
           \brief This method sets the length to 0 without freeing any memory.
           \details This method sets the length of the string to 0 without releasing any memory. It effectively clears the content of the string without deallocating the underlying buffer.
           */
         void zero();

          /*!
           \brief This method appends another string to this string.
           \param another The string to be appended to the end of this string.
           */
         void append(const String& another);

          /*!
           \brief This method appends a character to this string.
           \param unicodechar The Unicode code point, character, to be appended to this string.
           \details The character is appended to the end of the string.
           */
         void append(Char unicodechar);

          /*!
           \brief This method deletes a character from this string.
           \param index The zero-based index of the position of the character.
           */
         void deleteCharAt(int64 index);

          /*!
           \brief This method deletes a section from this string.
           \param index The zero-based index of the starting position.
           \param length The length of the section to delete.
           \details This method deletes a section of characters from this string, starting at the specified index and with the specified length.
           */
         void deleteCharRangeAt(int64 index, int64 length);

         /*!
          \copydoc jm::Object::equals()
          */
         bool equals(const Object* other) const override;

          /*!
           \brief This method checks if this string is identical to another string. It compares each character to determine if the characters are exactly the same.
           \param another The string to compare with.
           \return Returns true if both strings are identical, otherwise false.
           For example, "abc" == "abc" is true, but "aBc" == "abc" is false.
           */
         bool equals(const String& another) const;

          /*!
           \brief This method compares the order of the strings. It compares character by character from left to right.
           \param another The string to compare with.
           \details Returns a negative value if this string is less than \c another, zero if they are equal, and a positive value if this string is greater than \c another.
           */
         int32 compareTo(const String& another) const override;

          /*!
           \brief This method compares the order of the strings, taking into account numbers. Components that can be interpreted as numbers are compared separately. Due to limitations in the MS C++ compiler, currently only the first 256 characters are compared for efficiency reasons.
           \param another The string to compare with.
           \details Returns a negative value if this string is less than \c another, zero if they are equal, and a positive value if this string is greater than \c another.
           */
         int32 compareFancyTo(const String& another) const;

          /*!
           \brief This method checks if this string is identical to another string, ignoring case.
           \param another The string to compare with.
           \return Returns true if both strings are identical, ignoring case, otherwise false.
           For example, "abc" == "abc" is true, but "aBc" == "abc" is also true.
           */
         bool equalsIgnoreCase(const String& another) const;

          /*!
           \brief This method checks if the beginning of this string matches another string.
           \param another The string to be checked.
           \return Returns true if this string starts with the specified string, otherwise false.
           If the specified string is longer than this string, false is always returned.
           */
         bool startsWith(const String& another) const;

          /*!
           \brief This method checks if the end of this string matches another string.
           \param another The string to be checked.
           \return Returns true if this string ends with the specified string, otherwise false.
           If the specified string is longer than this string, false is always returned.
           */
         bool endsWith(const String& another) const;

         /*!
          \brief This method checks, is the string at position is the same as the other string.
          \param position The position where another string is expected
          \param another The comparing string
          \return Returns \c true is the substring sequence at position is the same as \c another.
          Otherwise \c false
          */
         bool atIs(int64 position, const String& another);

         /*!
          \brief Same as atIs, but ignoring case.
          \param position The position where another string is expected
          \param another The comparing string
          \return Returns \c true is the substring sequence at position is the same as \c another.
          Otherwise \c false
          */
         bool atIsIgnoreCase(int64 position, const String& another);

          /*!
           \brief This method calculates the hash code for this string and returns it.
           \details The hash code is calculated based on the content of the string.
           \return The hash code for this string.
           */
         int64 hashCode();

         /*!
         \brief This method calculates the hash code for this string and returns it.
         \details The hash code is calculated based on the content of the string.
         \return The hash code for this string.
         */
         int64 constHashCode() const;

          /*!
           \brief This method returns a string in which all uppercase letters have been replaced with lowercase letters.
           \details The method creates a new string with all uppercase letters replaced by their lowercase counterparts.
           \return A new string with all uppercase letters replaced by lowercase letters.
           */
         String toLowerCase() const;

          /*!
           \brief This method returns a string in which all lowercase letters have been replaced with uppercase letters.
           \details The method creates a new string with all lowercase letters replaced by their uppercase counterparts.
           \return A new string with all lowercase letters replaced by uppercase letters.
           */
         String toUpperCase() const;

          /*!
           \brief This method creates a substring that consists of a portion of this string.
           \param beginIndex The zero-based index of the first character to be included in the new substring.
           \return A new string that starts from the beginIndex and goes until the end of the string.
           */
         String substring(int64 beginIndex)const;

          /*!
           \brief This method creates a substring that consists of a portion of this string.
           \param beginIndex The zero-based index of the first character to be included in the new substring.
           \param endIndex The zero-based index of the first character that should not be included in the new substring.
           \return A new string that starts from the beginIndex and ends one character before the endIndex.
           \details This method creates a new string that contains a portion of the original string, starting from the character at the beginIndex and ending one character before the endIndex.
           */
         String substring(int64 beginIndex, int64 endIndex) const;

          /*!
           \brief This method returns a new string with all non-visible text characters (whitespaces) removed from the beginning and end of the string.
           \details The method creates a new string by removing all non-visible text characters (whitespaces) from the beginning and end of the original string.
           \return A new string with all non-visible text characters (whitespaces) removed from the beginning and end.
           */
         String trim() const;

          /*!
           \brief This method replaces characters in the string. The "old" character is replaced with the "new" character at all positions.
           \param oldChar The old character to be replaced.
           \param newChar The new character to replace the old character.
           \return The string with the replacements.
           \details This method replaces occurrences of the "old" character with the "new" character in the string.
           */
         String replace(Char oldChar, Char newChar) const;

          /*!
           \brief This method replaces substrings in the string. The "oldStr" substring is replaced with the "newStr" substring at all positions.
           \param oldStr The substring to be replaced.
           \param newStr The substring to replace the old substring.
           \return The string with the replacements.
           \details This method replaces occurrences of the "oldStr" substring with the "newStr" substring in the string.
           */
         String replaceAll(String oldStr, String newStr) const;

          /*!
           \brief This method reverses the order of characters in the string.
           \details This method reverses the order of characters in the string.
           */
         String reverse() const;

          /*!
           \brief Splits the string into a list of strings, using the specified character as a separator.
           \param character The character to use as a separator.
           \return A list of strings resulting from the split operation.
           \details This method splits the string into multiple substrings based on the specified character. Each substring is added to a list of strings, which is then returned.
           */
         StringList split(Char character);

          /*!
           \brief This method returns the zero-based position of the first occurrence of the desired character in the string.
           \param character The character to search for.
           \return Returns the zero-based index, or -1 if the character is not found in the string.
           \details This method searches for the first occurrence of the desired character in the string and returns its zero-based position.
           */
         int64 indexOf(Char character) const;

          /*!
           \brief This method returns the zero-based position of the first occurrence of the desired
           string in the string.
           \param str The string to search for.
           \return Returns the zero-based index, or -1 if the string is not found in the string.
           \details This method searches for the first occurrence of the desired string in the string and returns its zero-based position.
           */
         int64 indexOf(const String& str) const;


          /*!
           \brief This method returns the zero-based position of the first occurrence of the desired
           character in the string.
           \param character The character to search for.
           \param fromIndex The zero-based position to start searching from.
           \return Returns the zero-based index, or -1 if the character is not found in the string.
           \details This method searches for the first occurrence of the desired character in the string starting from the specified position and returns its zero-based index.
           */
         int64 indexOf(Char character, int64 fromIndex) const;

          /*!
           \brief This method returns the zero-based position of the first occurrence of the desired
           string in the string.
           \param str The string to search for.
           \param fromIndex The position to start searching from.
           \return Returns the zero-based index, or -1 if the string is not found in the string.
           \details This method searches for the first occurrence of the desired string in the string starting from the specified position and returns its zero-based index.
           */
         int64 indexOf(const String& str, int64 fromIndex) const;

          /*!
           \brief This method returns the zero-based position of the last occurrence of the desired character in the string.
           \details This method can also be understood as searching from the end of the string for the first occurrence of the character.
           \param character The character to search for.
           \return Returns the zero-based index, or -1 if the character is not found in the string.
           */
         int64 lastIndexOf(Char character) const;

          /*!
           \brief This method returns the zero-based position of the last occurrence of the desired
           string in the string.
           \details This method can also be understood as searching from the end of the string for the first occurrence of the string.
           \param str The string to search for.
           \return Returns the zero-based index, or -1 if the string is not found in the string.
           */
         int64 lastIndexOf(const String& str) const;


          /*!
           \brief This method returns the zero-based position of the last occurrence of the desired
           character in the string.
           \details This method can also be understood as searching from the end of the string for the first occurrence of the character.
           \param character The character to search for.
           \param fromIndex The zero-based index to start searching from (from the end).
           \return Returns the zero-based index, or -1 if the character is not found in the string.
           */
         int64 lastIndexOf(Char character, int64 fromIndex) const;

          /*!
           \brief This method returns the zero-based position of the last occurrence of the desired
           string in the string.
           \details This method can also be understood as searching from the end of the string for the first occurrence of the string.
           \param str The string to search for.
           \param fromIndex The zero-based index to start searching from (from the end).
           \return Returns the zero-based index, or -1 if the string is not found in the string.
           */
         int64 lastIndexOf(const String& str, int64 fromIndex) const;

          /*!
           \brief This method returns the character at a specific position in the string.
           \param index The zero-based index of the desired character.
           \return The character at the specified position.
           \details This method returns the character at the specified position in the string.
           */
         Char charAt(int64 index) const;

          /*!
           \brief This method replaces a character in the string with a new one.
           \param index The zero-based index of the character to be replaced.
           \param character The character to be inserted.
           \details This method replaces the character at the specified index in the string with the new character.
           */
         void setCharAt(int64 index, Char character);

          /*!
           \brief This method inserts a character into the string at the specified index and shifts all subsequent characters to the right.
           \param index The zero-based index of the character where the letter should be inserted.
           \param character The character to be inserted.
           \details This method inserts the character at the specified index in the string and shifts all subsequent characters to the right.
           */
         void insert(int64 index, Char character);

          /*!
           \brief This method inserts a string into the string at the specified index and shifts all subsequent characters to the right.
           \param index The zero-based index of the character where the string should be inserted.
           \param string The string to be inserted.
           \details This method inserts the string at the specified index in the string and shifts all subsequent characters to the right.
           */
         void insert(int64 index, const String& string);

         /*!
          \brief Searches in the string for a %n (e.g. %1, %2 etc) with the lowest number and
          replace it by a string representation of the number
          */
         String arg(int64 valueint64,
                    int64 fieldwidth = 0,
                    Char fillchar = Char(' '));

         /*!
          \brief Searches in the string for a %n (e.g. %1, %2 etc) with the lowest number and
          replace it by a string representation of the number
          */
         String arg(int32 valueint64,
                    int64 fieldwidth = 0,
                    Char fillchar = Char(' '));

         /*!
          \brief Searches in the string for a %n (e.g. %1, %2 etc) with the lowest number and
          replace it by a string representation of the number
          */
         String arg(uint32 valueint64,
                    int64 fieldwidth = 0,
                    Char fillchar = Char(' '));

         /*!
          \brief Searches in the string for a %n (e.g. %1, %2 etc) with the lowest number and
          replace it by a string representation of the number
          */
         String arg(const String& value,
                    int64 fieldwidth = 0,
                    Char fillchar = Char(' '));

         /*!
          \brief Searches in the string for a %n (e.g. %1, %2 etc) with the lowest number and
          replace it by a character.
          */
         String arg(Char character,
                    int64 fieldwidth = 0,
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
         String arg(double value,
                    int64 fieldwidth = 0,
                    int64 precision = -1,
                    Char fillchar = Char(' '));

         static void setConsoleCharset(Charset* cs);

         /*!
          \brief Returns a boolean representation of the string.
          */
         bool toBool() const;

         /*!
          \brief Returns a double representation of the string.
          */
         double toDouble() const;

         /*!
          \brief Returns a int representation of the string.
          */
         int64 toInt() const;

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
         friend String& operator<< (String& out, const int64& i);

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
         static String valueOf(double number, int64 precision, bool trunc);


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
         void checkCapacity(int64 more);

      private:

         //! This char array stores the content of the string. The length of the string can be
         //! bigger than the string itself. In principle, the characters are unicode encoded.
         //! Valid values are in the range of 0x0000 - 0xFFFF.
         Char* mValue;

         //! Length of array.
         int64 mArrLength;

         //! Length of string.
         int64 mStrLength;

         //! Stored hashvalue for operation. Is 0 if not initialized.
         int32 mHash;

         /*!
          \brief This method copies the content of CharArrays into this string.
          \param array The source CharArray.
          */
         void copy(const CharArray& array);

         //! Helper method for arg.
         bool argIndicies(int64& first, int64& second);

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


   /*!
    \class StringList
    \author Uwe Runtemund
    \brief This is a list of strings. It provides useful methods for manipulating string lists.
    */
   class DllExport StringList: public Object
   {

      public:

         StringList();

         StringList(const StringList& other);

         StringList(const jm::String& string);

         virtual ~StringList();

         void append(const jm::String& string);

         int64 size() const;

         void sort();

         const String& get(int64 index) const;

         void set(::int64 index, const String& item);

         String& operator[](const int64 index) const;

         StringList& operator=(const StringList& another);

         void clear();

         bool contains(const String& str) const;

         DllExport
         friend StringList& operator<< (StringList& out, const String& str);

      private:

         //! The length of the array.
         int64 mLength;

         //! The data size (can be less then length
         int64 mSize;

         //! The data array itself.
         String* mData;

         void checkSize(int64 size);
   };
}

#endif
