////////////////////////////////////////////////////////////////////////////////////////////////////
// Name:        Integer.h
// Library:     Jameo Core Library
// Purpose:     Double class
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

#ifndef jm_Double_h
#define jm_Double_h



/*!
\brief This class represents an double number as an object. This makes it easy to perform
certain object operations.
\ingroup core
*/
class DllExport Double
{
   public:

      Double();
      Double(const Double& value);

      Double(float value);
      Double(double value);
      explicit Double(int32 value);
      explicit Double(uint32 value);
      explicit Double(Integer value);

      // bool Equals(const Double& another) const;

      int32 compareTo(const Double& another) const;

      /*!
       \brief Converts a string to double.
       \param string string in the form "1.23" with colon (.) as decimal divider.
       */
      static Double valueOf(const jm::String& string);

      Integer floor() const;

      Integer ceil() const;

      bool IsNaN() const;

      /*!
       \brief  This function rounds a number to the nearest integer.
       \return Nearest integer.
       */
      Integer Round() const;

      /*!
       \brief  This function rounds a number to the desired number of decimal places.
       \note Due to machine precision, the exact value may not always be achieved.
       \param digits Number of decimal places to round to.
       \return Rounded number.
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

      Double& operator+=(const Double& another);

      Double& operator-=(const Double& another);

      Double& operator*=(const Double& another);

      Double& operator/=(const Double& another);

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
