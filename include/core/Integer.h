////////////////////////////////////////////////////////////////////////////////////////////////////
// Name:        Integer.h
// Library:     Jameo Core Library
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

class Double;

struct DllExport Bool
{
   public:

      Bool()
      {
         mValue = false;
      };

      Bool(int8 value)
      {
         mValue = value;
      };

      Bool(const Bool& value)
      {
         mValue = value.mValue;
      };

      Bool& operator=(const Bool& another)
      {
         if(this != &another)
         {
            mValue = another.mValue;
         }

         return *this;
      };

      static Bool valueOf(const jm::String& value);

      bool isTrue() const
      {
         return mValue == BoolTrue;
      };

      bool IsFalse() const
      {
         return mValue == BoolFalse;
      };

      bool IsIndeterminate() const
      {
         return mValue < 0;
      };

      // Implicit conversion
      operator bool() const
      {
         return isTrue();
      };

      /*!
       \brief Implementation of the equality operator.
       */
      DllExport
      friend bool operator==(Bool v1, Bool v2)
      {
         return v1.mValue == v2.mValue;
      };

      DllExport
      friend bool operator==(Bool v1, bool v2)
      {
         return v2 ? v1.isTrue() : v1.IsFalse();
      };

      DllExport
      friend bool operator==(bool v1, Bool v2)
      {
         return v1 ? v2.isTrue() : v2.IsFalse();
      };

      /*!
       \brief Implementation of the equality operator.
       */
      DllExport
      friend bool operator!=(Bool v1, Bool v2)
      {
         return v1.mValue != v2.mValue;
      };

   private:

      int8 mValue;


};


/*!
 \brief This class represents an integer number. This makes it easy to perform certain object
 operations. We assume it as 64 bit value.
 \ingroup core
 */
class DllExport Integer
{
   public:

      Integer();
      Integer(const Integer& other);
      Integer(uint8 value);
      Integer(int8 value);
      Integer(uint16 value);
      Integer(int16 value);
      Integer(int32 value);
      Integer(uint32 value);
      Integer(int64 value);
      Integer(uint64 value);
      //      Integer(slong value); double under linux
      #ifdef WITHULONG
      Integer(ulong value);
      #endif
      bool equals(const Integer& another) const;

      int32 compareTo(const Integer& another) const;

      /*!
       \brief Returns the number of digits, this number has.
       \return return 1 for a number between 0 and 9, 2 for a number between 10 and 99 and so on...
       */
      uint8 digits() const;

      /*!
       \brief Converts a string to an integer value.
       \param string The string, e.g. "1", that should be converted to an integer.
       \return The desired integer value.
       */
      static Integer valueOf(const jm::String& string);

      /*!
       \brief Method converts a hexadecimal string value into an integer number.
       \param str A character string that represents a hexadecimal coded number. E.g. "FF" for 255.
       \return Returns the desired number as an integer value.
       */
      static Integer fromHex(const jm::String& str);

      /*!
       \brief Method converts a hexadecimal string value into an integer number.
       \param str A character string that represents a hexadecimal coded number. E.g. "FF" for 255.
       \param begin start index of hex string
       \param size Size of hex string
       \return Returns the desired number as an integer value.
       */
      static Integer fromHex(const jm::String& str, uint32 begin, uint32 size);

      /*!
       \brief Converts an integer number to a hexadecimal string value.
       \return Returns the desired number as a string, which is a hexadecimal representation.
       For example, "FF" for 255.
       */
      jm::String toHexString();

      /*!
       \brief Converts an integer number to a string representation of a Roman numeral.
       \return The desired number as a string with the value of a Roman numeral.
       */
      jm::String toRomanString();

      /*!
       \brief Converts an integer number to a string representation of a capital letter.
       \return The desired number as a string with the value of a capital letter.
       */
      jm::String toLatinAlphabetString();

      int8 Int8()const;
      int16 Int16()const;
      int64 Int64()const;
      int32 Int32()const;
      uint8 Uint8()const;
      uint16 Uint16()const;
      uint32 Uint32()const;
      double Dbl()const;

      Integer abs() const;

      operator int64() const;

      /*!
      	\brief Implementation of the increment operator (PRE).
      	*/
      Integer& operator++();

      /*!
      \brief Implementation of the increment operator (POST).
      */
      Integer operator++(int32);

      /*!
      	\brief Implementation of the increment operator (PRE).
      	*/
      Integer& operator--();

      /*!
      \brief Implementation of the increment operator (POST).
      */
      Integer operator--(int32);

      /*!
      \brief Implementation of the assignment operator.
      */
      Integer& operator=(const Integer& another);

      Integer& operator+=(const Integer& another);

      Integer& operator-=(const Integer& another);

      Integer& operator*=(const Integer& another);

      Integer operator<<(const Integer& shift);

      Integer operator<<(int32 shift);

      Integer operator>>(const Integer& shift);

      Integer operator>>(int32 shift);

      DllExport
      friend Integer operator+(Integer left, Integer right);

      DllExport
      friend Integer operator+(Integer left, int64 right);

      DllExport
      friend Integer operator+(int64 left, Integer right);

      DllExport
      friend Integer operator+(Integer left, int32 right);

      DllExport
      friend Integer operator+(int32 left, Integer right);

      DllExport
      friend Integer operator+(Integer left, uint32 right);

      DllExport
      friend Integer operator+(uint32 left, Integer right);

      DllExport
      friend Integer operator+(Integer left, uint16 right);

      DllExport
      friend Integer operator+(uint16 left, Integer right);

      DllExport
      friend Integer operator-(Integer left, Integer right);

      DllExport
      friend Integer operator-(Integer left, int32 right);

      DllExport
      friend Integer operator-(int32 left, Integer right);

      DllExport
      friend Integer operator-(Integer left, uint32 right);

      DllExport
      friend Integer operator-(uint32 left, Integer right);

      DllExport
      friend Integer operator-(Integer left, int16 right);

      DllExport
      friend Integer operator-(int16 left, Integer right);

      DllExport
      friend Integer operator-(Integer left, uint16 right);

      DllExport
      friend Integer operator-(uint16 left, Integer right);

      DllExport
      friend Integer operator-(Integer left, float right);

      DllExport
      friend Integer operator*(Integer left, Integer right);

      DllExport
      friend Integer operator*(Integer left, int32 right);

      DllExport
      friend Integer operator*(int32 left, Integer right);

      DllExport
      friend Integer operator*(Integer left, uint32 right);

      DllExport
      friend Integer operator*(uint32 left, Integer right);

      DllExport
      friend Integer operator*(Integer left, uint64 right);

      DllExport
      friend Integer operator*(uint64 left, Integer right);

      DllExport
      friend Integer operator*(Integer left, ulong right);

      DllExport
      friend Integer operator*(ulong left, Integer right);

      DllExport
      friend Double operator*(Integer left, double right);

      DllExport
      friend Double operator*(double left, Integer right);

      DllExport
      friend Double operator*(Integer left, float right);

      DllExport
      friend Double operator*(float left, Integer right);

      DllExport
      friend Integer operator/(Integer left, Integer right);

      DllExport
      friend Integer operator/(Integer left, int32 right);

      DllExport
      friend Integer operator/(Integer left, uint32 right);

      DllExport
      friend Double operator/(Double left, Integer right);

      DllExport
      friend Double operator/(Integer left, Double right);

      DllExport
      friend bool operator<(Integer left, Integer right);

      DllExport
      friend bool operator<(Integer left, int32 right);

      DllExport
      friend bool operator<(int32 left, Integer right);

      DllExport
      friend bool operator<(Integer left, uint32 right);

      DllExport
      friend bool operator<(uint32 left, Integer right);

      DllExport
      friend bool operator<(Integer left, int16 right);

      DllExport
      friend bool operator<(int16 left, Integer right);

      DllExport
      friend bool operator<(Integer left, uint16 right);

      DllExport
      friend bool operator<(uint16 left, Integer right);

      DllExport
      friend bool operator<(Integer left, ulong right);

      DllExport
      friend bool operator<(ulong left, Integer right);

      DllExport
      friend bool operator<(Integer left, int64 right);

      DllExport
      friend bool operator<(int64 left, Integer right);

      DllExport
      friend bool operator<(Integer left, uint64 right);

      DllExport
      friend bool operator<(uint64 left, Integer right);

      DllExport
      friend bool operator<(Integer left, Double right);

      DllExport
      friend bool operator<(Integer left, float right);

      DllExport
      friend bool operator<(Double left, Integer right);

      DllExport
      friend bool operator<=(Integer left, Integer right);

      DllExport
      friend bool operator<=(Integer left, int32 right);

      DllExport
      friend bool operator<=(int32 left, Integer right);

      DllExport
      friend bool operator<=(Integer left, uint32 right);

      DllExport
      friend bool operator<=(uint32 left, Integer right);

      DllExport
      friend bool operator<=(Integer left, ulong right);

      DllExport
      friend bool operator<=(ulong left, Integer right);

      DllExport
      friend bool operator<=(Integer left, slong right);

      DllExport
      friend bool operator<=(slong left, Integer right);

      DllExport
      friend bool operator<=(Integer left, int64 right);

      DllExport
      friend bool operator<=(int64 left, Integer right);

      DllExport
      friend bool operator<=(Integer left, uint64 right);

      DllExport
      friend bool operator<=(uint64 left, Integer right);

      DllExport
      friend bool operator>(Integer left, Integer right);

      DllExport
      friend bool operator>(Integer left, int32 right);

      DllExport
      friend bool operator>(int32 left, Integer right);

      DllExport
      friend bool operator>(Integer left, uint32 right);

      DllExport
      friend bool operator>(uint32 left, Integer right);

      DllExport
      friend bool operator>(Double left, Integer right);

      DllExport
      friend bool operator>(Integer left, Double right);

      DllExport
      friend bool operator>=(Integer left, Integer right);

      DllExport
      friend bool operator>=(Integer left, int32 right);

      DllExport
      friend bool operator>=(int32 left, Integer right);

      DllExport
      friend bool operator>=(Integer left, uint32 right);

      DllExport
      friend bool operator>=(uint32 left, Integer right);

      DllExport
      friend bool operator==(Integer left, Integer right);

      DllExport
      friend bool operator==(Integer left, int32 right);

      DllExport
      friend bool operator==(int32 left, Integer right);

      DllExport
      friend bool operator==(Integer left, uint32 right);

      DllExport
      friend bool operator==(uint32 left, Integer right);

      DllExport
      friend bool operator!=(Integer left, Integer right);

      DllExport
      friend bool operator!=(Integer left, int16 right);

      DllExport
      friend bool operator!=(Integer left, uint16 right);

      DllExport
      friend bool operator!=(Integer left, int32 right);

      DllExport
      friend bool operator!=(Integer left, uint32 right);

      DllExport
      friend bool operator!=(uint32 left, Integer right);

   private:

      int64 mValue;
};

namespace jm
{
   DllExport
   Integer Min(Integer left, Integer right);

   DllExport
   Integer Max(Integer left, Integer right);
}
#endif
