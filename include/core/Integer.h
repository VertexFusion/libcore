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

      Bool(const Bool &value)
      {
         mValue = value.mValue;
      };

      Bool &operator=(const Bool &another)
      {
         if(this != &another)
         {
            mValue = another.mValue;
         }

         return *this;
      };

      static Bool ValueOf(const jm::String& value);

      bool IsTrue() const
      {
         return mValue == BoolTrue;
      };

      bool IsFalse() const
      {
         return mValue == BoolFalse;
      };

      bool IsIndeterminate() const
      {
         return mValue == indet;
      };

      //Implizit conversion
      operator bool() const
      {
         return IsTrue();
      };

      /*!
       \brief Implementierung des Operators ==
       */
      DllExport
      friend bool operator==(Bool v1, Bool v2)
      {
         return v1.mValue == v2.mValue;
      };

      DllExport
      friend bool operator==(Bool v1, bool v2)
      {
         return v2 ? v1.IsTrue() : v1.IsFalse();
      };

      DllExport
         friend bool operator==(bool v1, Bool v2)
      {
         return v1 ? v2.IsTrue() : v2.IsFalse();
      };

      /*!
       \brief Implementierung des Operators ==
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
      Integer(const Integer &other);
      Integer(uint8 value);
      Integer(int8 value);
      Integer(uint16 value);
      Integer(int16 value);
      Integer(int32 value);
      Integer(uint32 value);
      Integer(int64 value);
      Integer(uint64 value);
      Integer(slong value);
      #ifdef WITHULONG
      Integer(ulong value);
      #endif
      bool Equals(const Integer& another) const;

      int32 CompareTo(const Integer& another) const;

      /*!
       \brief Returns the number of digits, this number has.
       \return return 1 for a number between 0 and 9, 2 for a number between 10 and 99 and so on...
       */
      uint8 Digits() const;

      /*!
       \brief Methode wandelt einen String in einen Integer-Wert um.
       \param string Die Zeichenkette, z.B. "1", die in eine Gleitkommazahl umgewandelt werden
       soll.
       \return Die gewünschte Integer-Zahl.
       */
      static Integer ValueOf(const jm::String& string);

      /*!
       \brief Method converts a hexadecimal string value into an integer number.
       \param str A character string that represents a hexadecimal coded number. E.g. "FF" for 255.
       \return Returns the desired number as an integer value.
       */
      static Integer FromHex(const jm::String& str);

      /*!
       \brief Method converts a hexadecimal string value into an integer number.
       \param str A character string that represents a hexadecimal coded number. E.g. "FF" for 255.
       \param begin start index of hex string
       \param size Size of hex string 
       \return Returns the desired number as an integer value.
       */
      static Integer FromHex(const jm::String& str, uint32 begin, uint32 size);

      /*!
       \brief Methode wandelt einen eine Integer-Zahl in einen hexadezimalen String-Wert um.
       \return Gibt die gewünschte Zahl als String zurück, der eine hexadezimale Darstellung ist.
       Also z.B. "FF" für 255.
       */
      jm::String ToHexString();

      /*!
       \brief Methode wandelt eine Integer-Zahl in einen String um, der eine Römische Zahl
       darstellt.
       \return Gibt die gewünschte Zahl als String mit dem Wert einer Römischen Zahl zurück.
       */
      jm::String ToRomanString();

      /*!
       \brief Methode wandelt eine Integer-Zahl in einen String um, der einm Großbuchstaben
       entspricht. 1=A,2=C,3=C usw-
       \return Gibt die gewünschte Zahl als String mit dem Wert eines Großbuchstaben zurück.
       */
      jm::String ToLatinAlphabetString();

      int8 Int8()const;
      int16 Int16()const;
      int64 Int64()const;
      int32 Int32()const;
      uint8 Uint8()const;
      uint16 Uint16()const;
      uint32 Uint32()const;
      double Dbl()const;

      Integer Abs() const;

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

      Integer &operator+=(const Integer &another);

      Integer &operator-=(const Integer &another);

      Integer &operator*=(const Integer &another);

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

DllExport
Integer Min(Integer left, Integer right);

DllExport
Integer Max(Integer left, Integer right);


/*!
\brief This class represents an double number as an object. This makes it easy to perform
certain object operations.
\ingroup core
*/
class DllExport Double
{
   public:

      Double();
      Double(const Double &value);

      Double(float value);
      Double(double value);
      explicit Double(int32 value);
      explicit Double(uint32 value);
      explicit Double(Integer value);

      // bool Equals(const Double& another) const;

      int32 CompareTo(const Double& another) const;

      /*!
       \brief Methode wandelt einen String in einen Float-Wert um.
       \param string Die Zeichenkette, z.B. "1.23", die in eine Gleitkommazahl umgewandelt werden soll.
       \return Die gewünschte Gleitkommazahl.
       */
      static Double ValueOf(const jm::String& string);

      Integer Floor() const;

      Integer Ceil() const;

      bool IsNaN() const;

      /*!
       \brief  Diese Funktion rundet eine Zahl kaufmännisch auf die Ganze Zahl
       \return Ganze Zahl.
       */
      Integer Round() const;

      /*!
       \brief  Diese Funktion rundet eine Zahl auf die gewünschte Anzahl der Nachkommastellen.
       \note Beachte, dass aufgrund der Maschinengenauigkeigt nicht immer der exakte Wert getroffen
       werden kann.
       \param digits Number of decimal places.
       \return Gerundete Zahl
       */
      Double RoundFrac(Integer digits) const;

      double Dbl()const;

      operator double() const;

      /*!
        \brief Implementation of the increment operator (PRE).
        */
      Double& operator++();

      /*!
       \brief Implementation of the increment operator (POST).
       */
      Double operator++(int32);

      /*!
        \brief Implementation of the increment operator (PRE).
        */
      //Integer& operator--();

      /*!
       \brief Implementation of the increment operator (POST).
       */
      //Integer operator--(int32);

      /*!
       \brief Implementation of the assignment operator.
       */
      Double& operator=(const Double& another);

      Double &operator+=(const Double &another);

      Double &operator-=(const Double &another);

      Double &operator*=(const Double &another);

      Double &operator/=(const Double &another);

      DllExport
      friend Double operator+(Double left, Double right);

      DllExport
      friend Double operator+(Double left, double right);

      DllExport
      friend Double operator+(double left, Double right);

      DllExport
      friend Double operator+(Double left, float right);

      DllExport
      friend Double operator+(float left, Double right);

      DllExport
      friend Double operator+(Double left, int32 right);

      DllExport
      friend Double operator+(int32 left, Double right);

      /*  DllExport
      friend Integer operator+(uint32 left, Integer right);

      DllExport
      friend Integer operator+(Integer left, uint32 right);
      */
      DllExport
      friend Double operator-(Double left, Double right);

      DllExport
      friend Double operator-(Double left, double right);

      DllExport
      friend Double operator-(double left, Double right);

      DllExport
      friend Double operator-(Double left, float right);

      DllExport
      friend Double operator-(float left, Double right);

      DllExport
      friend Double operator-(Double left, int32 right);

      DllExport
      friend Double operator-(int32 left, Double right);

      DllExport
      friend Double operator*(Double left, Double right);

      DllExport
      friend Double operator*(Double left, double right);

      DllExport
      friend Double operator*(double left, Double right);

      DllExport
      friend Double operator*(Double left, float right);

      DllExport
      friend Double operator*(float left, Double right);

      DllExport
      friend Double operator*(Double left, Integer right);

      DllExport
      friend Double operator*(Integer left, Double right);

      DllExport
      friend Double operator*(Double left, int32 right);

      DllExport
      friend Double operator*(int32 left, Double right);

      DllExport
      friend Double operator*(Double left, uint32 right);

      DllExport
      friend Double operator*(uint32 left, Double right);

      DllExport
      friend Double operator/(Double left, Double right);

      DllExport
      friend Double operator/(Double left, double right);

      DllExport
      friend Double operator/(double left, Double right);

      DllExport
      friend Double operator/(Double left, float right);

      DllExport
      friend Double operator/(float left, Double right);

      DllExport
      friend Double operator/(Double left, Integer right);

      DllExport
      friend Double operator/(Integer left, Double right);

      DllExport
      friend Double operator/(Double left, int32 right);

      DllExport
      friend Double operator/(int32 left, Double right);

      DllExport
      friend bool operator<(Double left, Double right);

      DllExport
      friend bool operator<(Double left, double right);

      DllExport
      friend bool operator<(double left, Double right);

      DllExport
      friend bool operator<(Double left, Integer right);

      DllExport
      friend bool operator<(Integer left, Double right);

      DllExport
      friend bool operator<(Double left, int32 right);

      DllExport
      friend bool operator<(int32 left, Double right);

      /*  DllExport
      friend bool operator<(int32 left, Integer right);

      DllExport
      friend bool operator<(uint32 left, Integer right);

      DllExport
      friend bool operator<=(Integer left, Integer right);

      DllExport
      friend bool operator<=(Integer left, int32 right);

      DllExport
      friend bool operator<=(int32 left, Integer right);

      DllExport
      friend bool operator<=(Integer left, uint32 right);

      DllExport
      friend bool operator<=(uint32 left, Integer right);*/

      DllExport
      friend bool operator>(Double left, Double right);

      DllExport
      friend bool operator>(Double left, double right);

      DllExport
      friend bool operator>(double left, Double right);

      DllExport
      friend bool operator>(Double left, float right);

      DllExport
      friend bool operator>(float left, Double right);

      DllExport
      friend bool operator>(Double left, Integer right);

      DllExport
      friend bool operator>(Integer left, Double right);

      DllExport
      friend bool operator>(Double left, int32 right);

      DllExport
      friend bool operator>(int32 left, Double right);
      /*
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
      friend bool operator!=(Integer left, int32 right);

      DllExport
      friend bool operator!=(Integer left, uint32 right);
      */

   private:

      double mValue;

};

DllExport
Double Min(Double left, Double right);

DllExport
Double Max(Double left, Double right);



#endif
