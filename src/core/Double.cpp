////////////////////////////////////////////////////////////////////////////////////////////////////
// Name:        Double.cpp
// Library:     Jameo Core Library
// Purpose:     Enhancement for Double Types
//
// Author:      Uwe Runtemund (2016-today)
// Modified by:
// Created:     30.10.2016
//
// Copyright:   (c) 2016 Jameo Software, Germany. https://jameo.de
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

#include "Precompiled.h"













Double::Double()
{
   mValue = 0.0;
}

Double::Double(const Double& value)
{
   mValue = value.mValue;
}

Double::Double(float value)
{
   mValue = value;
}

Double::Double(double value)
{
   mValue = value;
}

Double::Double(int32 value)
{
   mValue = value;
}

Double::Double(uint32 value)
{
   mValue = value;
}

Double::Double(Integer value)
{
   mValue = value.Dbl();
}

int32 Double::CompareTo(const Double& another) const
{
   if (mValue > another.mValue)return 1;
   if (mValue < another.mValue)return -1;
   return 0;
}

double Double::Dbl()const
{
   return mValue;
}

Double Double::ValueOf(const jm::String& string)
{
   jm::ByteArray cstr = string.ToCString();
   std::stringstream ss;
   double d = 0;
   ss << cstr.ConstData();
   ss >> d;
   return d;
}

Integer Double::Floor() const
{
   return Integer((int64)std::floor(mValue));
}

Integer Double::Ceil() const
{
   return Integer((int64)std::ceil(mValue));
}

bool Double::IsNaN() const
{
   return jm::IsNaN(mValue);
}


Integer Double::Round() const
{
   return Integer((int64)((mValue > 0.0) ? std::floor(mValue + 0.5) : std::ceil(mValue - 0.5)));
}

Double Double::RoundFrac(Integer digits) const
{
   Double factor = std::pow(10, digits.Int32());
   Double value = mValue * factor;
   value = value.Round().Dbl();
   return Double(value / factor);
}

Double::operator double() const
{
   return mValue;
}

Double& Double::operator=(const Double& another)
{
   if (this != &another)
   {
      mValue = another.mValue;
   }

   return *this;
}

Double& Double::operator++()
{
   mValue++;
   return *this;
}

Double Double::operator++(int32)
{
   Double i = *this;
   mValue++;
   return i;
}

bool operator>(Double left, Double right)
{
   return left.mValue > right.mValue;
}

bool operator>(Double left, double right)
{
   return left.mValue > right;
}

bool operator>(double left, Double right)
{
   return left > right.mValue;
}

bool operator>(Double left, float right)
{
   return left.mValue > right;
}

bool operator>(float left, Double right)
{
   return left > right.mValue;
}

bool operator>(Double left, Integer right)
{
   return left.mValue > right.mValue;
}

bool operator>(Integer left, Double right)
{
   return left.mValue > right.mValue;
}

bool operator>(Double left, int32 right)
{
   return left.mValue > right;
}

bool operator>(int32 left, Double right)
{
   return left > right.mValue;
}

bool operator<(Double left, Double right)
{
   return left.mValue < right.mValue;
}

bool operator<(Double left, double right)
{
   return left.mValue < right;
}

bool operator<(double left, Double right)
{
   return left < right.mValue;
}

bool operator<(Double left, Integer right)
{
   return left.mValue < right.mValue;
}

bool operator<(Integer left, Double right)
{
   return left.mValue < right.mValue;
}

bool operator<(Double left, int32 right)
{
   return left.mValue < right;
}

bool operator<(int32 left, Double right)
{
   return left < right.mValue;
}

Double& Double::operator+=(const Double& another)
{
   mValue += another.mValue;
   return *this;
}

Double& Double::operator-=(const Double& another)
{
   mValue -= another.mValue;
   return *this;
}

Double& Double::operator*=(const Double& another)
{
   mValue *= another.mValue;
   return *this;
}

Double& Double::operator/=(const Double& another)
{
   mValue /= another.mValue;
   return *this;
}

Double operator+(Double left, Double right)
{
   return Double(left.mValue + right.mValue);
}

Double operator+(Double left, double right)
{
   return Double(left.mValue + right);
}

Double operator+(double left, Double right)
{
   return Double(left + right.mValue);
}

Double operator+(Double left, float right)
{
   return Double(left.mValue + right);
}

Double operator+(float left, Double right)
{
   return Double(left + right.mValue);
}

Double operator+(Double left, int32 right)
{
   return Double(left.mValue + right);
}

Double operator+(int32 left, Double right)
{
   return Double(left + right.mValue);
}

Double operator-(Double left, Double right)
{
   return Double(left.mValue - right.mValue);
}

Double operator-(Double left, double right)
{
   return Double(left.mValue - right);
}

Double operator-(double left, Double right)
{
   return Double(left - right.mValue);
}

Double operator-(Double left, float right)
{
   return Double(left.mValue - right);
}

Double operator-(float left, Double right)
{
   return Double(left - right.mValue);
}

Double operator-(Double left, int32 right)
{
   return Double(left.mValue - right);
}

Double operator-(int32 left, Double right)
{
   return Double(left - right.mValue);
}

Double operator*(Double left, Double right)
{
   return Double(left.mValue * right.mValue);
}

Double operator*(Double left, double right)
{
   return Double(left.mValue * right);
}

Double operator*(double left, Double right)
{
   return Double(left * right.mValue);
}

Double operator*(Double left, float right)
{
   return Double(left.mValue * right);
}

Double operator*(float left, Double right)
{
   return Double(left * right.mValue);
}

Double operator*(Double left, Integer right)
{
   return Double(left.mValue * right.Dbl());
}

Double operator*(Integer left, Double right)
{
   return Double(left.Dbl() * right.mValue);
}

Double operator*(Double left, int32 right)
{
   return Double(left.mValue * right);
}

Double operator*(int32 left, Double right)
{
   return Double(left * right.mValue);
}

Double operator*(Double left, uint32 right)
{
   return Double(left.mValue * right);
}

Double operator*(uint32 left, Double right)
{
   return Double(left * right.mValue);
}

Double operator/(Double left, Double right)
{
   return Double(left.mValue / right.mValue);
}

Double operator/(Double left, double right)
{
   return Double(left.mValue / right);
}

Double operator/(double left, Double right)
{
   return Double(left / right.mValue);
}

Double operator/(Double left, float right)
{
   return Double(left.mValue / right);
}

Double operator/(float left, Double right)
{
   return Double(left / right.mValue);
}

Double operator/(Double left, Integer right)
{
   return Double(left.mValue / right.mValue);
}

Double operator/(Integer left, Double right)
{
   return Double(left.mValue / right.mValue);
}

Double operator/(Double left, int32 right)
{
   return Double(left.mValue / right);
}

Double operator/(int32 left, Double right)
{
   return Double(left / right.mValue);
}

Double Min(Double left, Double right)
{
   return std::min(left, right);
}

Double Max(Double left, Double right)
{
   return std::max(left, right);
}



