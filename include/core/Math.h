////////////////////////////////////////////////////////////////////////////////////////////////////
// Name:        Math.h
// Library:     Jameo Core Library
// Purpose:     Useful math functions
//
// Author:      Uwe Runtemund (2012-today)
// Modified by:
// Created:     14.10.2012
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

#ifndef jm_Math_h
#define jm_Math_h

#include "Types.h"

namespace jm
{
   /*!
    \brief This value defines when two points or values are considered identical. This serves to
    catch numerical inaccuracies and the resulting errors. The predefined value can be changed, but
    this may change the calculations considerably. 1E-6 is highly recommended as the highest value.
    */
   double const RESABS = 1E-6;

   /*!
    \brief This function converts the angle from degrees into radians.
    \param deg Given angle in degrees (e.g. 30 for 30°).
    \return Returns the angle in radians.
    */
   DllExport
   double degToRad(double deg);

   /*!
    \brief  This function converts the angle from radians into degrees.
    \param rad Given angle in radians (e.g. PI/2 for 90°).
    \return Returns the angle in degrees.
    */
   DllExport
   double radToDeg(double rad);

   /*!
    \brief This function returns the sign of a number.
    \param d The number whose sign is to be determined.
    \return -1, if negative, 0 for 0 and 1 for positive d.
    */
   DllExport
   int16 sign(double d);

   /*!
    \brief This function rounds a number commercially to the integral number.
    \param d Number to be rounded.
    \return Integer number.
    */
   DllExport
   int64 round(double d);

   /*!
    \brief This function rounds a number to the desired number of decimal places.
    \note Please note that the exact value cannot always be determined due to the accuracy of the machine.
    \param f Number to be rounded.
    \return Rounded number
    */
   DllExport
   float roundFrac(float f, int32 digits);

   /*!
    \brief This function rounds a number to the desired number of decimal places.
    \note Please note that the exact value cannot always be determined due to the accuracy of the machine.
    \param f Number to be rounded.
    \return Rounded number
    */
   DllExport
   double roundFrac(double f, int64 digits);

   /*!
    \brief This method checks whether the two values are identical, taking resabs into account,
    are identical. Therefore |v2-v1| < RESABS applies. So if RESABS is the different, then the value is already
    is no longer the same. IT MUST BE LESS THAN EPSILON
    \return The result of v1==v2
    */
   DllExport
   bool isEqual(double v1, double v2);

   /*!
    \brief This method checks whether the first value is not equal to the second, taking resabs into account.
    \return The result of v1!=v2
    */
   DllExport
   bool isNotEqual(double v1, double v2);

   /*!
    \brief This method checks whether the first value is lower than the second, taking resabs into account.
    \return The result of v1<v2
    */
   DllExport
   bool isLess(double v1, double v2);

   /*!
    \brief This method checks whether the first value is lower or equal to the second, taking resabs into account.
    \return The result of v1<=v2
    */
   DllExport
   bool isLessEqual(double v1, double v2);

   /*!
    \brief This method checks whether the first value is greater than the second, taking resabs into account.
    \return The result of v1>v2
    */
   DllExport
   bool isGreater(double v1, double v2);

   /*!
    \brief This method checks whether the first value is greater than or equal to the second, taking resabs into account.
    \return The result of v1<v2
    */
   DllExport
   bool isGreaterEqual(double v1, double v2);

   /*!
    \brief This method checks whether the number is "Not a Number".
    \param d The value to be checked.
    \return The result of d!=d
    */
   DllExport
   bool isNaN(double d);

   /*!
    \brief This method swaps the two variables in place.
    */
   DllExport
   void swap(double& v1, double& v2);

   /*!
    \brief This method swaps the two variables in place.
    */
   DllExport
   void swap(int32& v1, int32& v2);

   /*!
    \brief This method swaps the two variables in place.
    */
   DllExport
   void swap(uint32& v1, uint32& v2);

   /*!
    \brief This method swaps the two variables in place.
    */
   DllExport
   void swap(uint16& v1, uint16& v2);

   /*!
    \brief This method swaps the two variables in place.
    */
   DllExport
   void swap(uint8& v1, uint8& v2);

   /*!
    \brief Returna a random number between 0.0 and 1.0
    \note Not safe in sense of cryptography. Just an arbitrary number.
    */
   DllExport
   double random();

   /*!
    \brief Returns a random integer number.
    \note Not safe in sense of cryptography. Just an arbitrary number.
    \param lower Lower inclusive limit of the value range to be returned.
    \param upper Upper inclusive limit of the value range to be returned.
    */
   DllExport
   int32 random(int32 lower, int32 upper);

   /*!
    \brief randomly determines whether the specified probability is fulfilled.
    */
   DllExport
   bool probability(double percent);

   /*!
    \brief This method interpolates the numerical value between begin and end.
    \param begin Start value for interpolation.
    \param end End value for the interpolation.
    \param percent Shift value between 0 and 1
    */
   DllExport
   float interpolate(float begin, float end, float percent);

   /*!
    \brief This method interpolates the numerical value between begin and end.
    \param begin Start value for interpolation.
    \param end End value for the interpolation.
    \param percent Shift value between 0 and 1
    */
   DllExport
   double interpolate(double begin, double end, double percent);


   /*!
    \brief This method interpolates the numerical value between vbegin and vend.
    \param vbegin Start value for interpolation.
    \param vend End value for the interpolation.
    \param begin lower value than position. Begin of range to calculate the percentage for interpolation.
    \param end bigger value than position. End of range to calculate the percentage for interpolation.
    \param position Value between begin and end to calculate the percentage for interpolation
    */
   DllExport
   double interpolate(double vbegin, double vend, double begin, double end, double position);

   /*!
    \brief This method checks whether the number passed is a power of 2.
    \param x The number to be checked.
    \return Returns true if the number is a power of 2 (i.e. 1,2,4,8,16 etc.), otherwise false.
    */
   DllExport
   bool powerOf2(int x);

   /*!
    \brief This method specifies the smallest power of 2 over the given value. If the value
    itself is a power of 2, then the value is returned
    */
   DllExport
   uint32 ceilPowerOf2(uint32 x);

   /*!
    \brief This function calculates the relative machine accuracy for double values. Should
    be 1.11022e-16 for 64 bit. Some literature sources also give 2.22045e-16 as accuracy.
    */
   DllExport
   double doubleMaschineEpsilon();

   /*!
    \brief This function calculates the relative machine accuracy for float values. Should be at
    32 bit should be 5.96046e-08. Some literature sources also give 1.19209e-07 as accuracy.
    */
   DllExport
   float floatMaschineEpsilon();

   /*!
    \brief Divide one integer by another and round towards minus infinity.
    \param x Dividend
    \param y Divisor
    \return The quotient, rounded towards minus infinity.
    */
   DllExport
   int64 divFloor(int64 x, int64 y);

   /*!
    \brief Calculates the residual value after dividing one integer by another and rounds the
    quotient towards minus infinity.
    \param x Dividend
    \param y Divisor
    \return Residual value
    */
   DllExport
   int64 modFloor(int64 x, int64 y);

   template<typename T>
   T min(T a,T b)
   {
      return (a < b) ? a : b;
   }

   template<typename T>
   T max(T a,T b)
   {
      return (a > b) ? a : b;
   }
}
#endif
