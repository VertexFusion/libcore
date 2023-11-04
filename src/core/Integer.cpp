////////////////////////////////////////////////////////////////////////////////////////////////////
// Name:        Integer.cpp
// Library:     Jameo Core Library
// Purpose:     Enhancement for Integer Types
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

const uint16 gMask[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
const int32 gArabic[] = {1, 4, 5, 9, 10, 40, 50, 90, 100, 400, 500, 900, 1000};
const jm::String gRoman[] = {"I", "IV", "V", "IX", "X", "XL", "L", "XC", "C", "CD", "D", "CM", "M"};


Bool Bool::ValueOf(const jm::String& value)
{
	return value.EqualsIgnoreCase("true");
}


	Integer::Integer(): Comparable<Integer>()
	{
		mValue = 0;
	}

	Integer::Integer(int8 value): Comparable<Integer>()
	{
		mValue = value;
	}

	Integer::Integer(uint8 value): Comparable<Integer>()
	{
		mValue = value;
	}

	Integer::Integer(int16 value): Comparable<Integer>()
	{
		mValue = value;
	}

	Integer::Integer(uint16 value): Comparable<Integer>()
	{
		mValue = value;
	}

	Integer::Integer(int32 value): Comparable<Integer>()
	{
		mValue = value;
	}

	Integer::Integer(uint32 value): Comparable<Integer>()
	{
		mValue = value;
	}

	Integer::Integer(int64 value): Comparable<Integer>()
	{
		mValue = value;
	}

	Integer::Integer(uint64 value): Comparable<Integer>()
	{
		mValue = value;
	}

#ifdef WITHULONG
	Integer::Integer(ulong value): Comparable<Integer>()
	{
		mValue = (int32)value;
	}
#endif
	bool Integer::Equals(const Integer &another) const
	{
		return mValue == another.mValue;
	}

	int32 Integer::CompareTo(const Integer &another) const
	{
		if(mValue > another.mValue)return 1;
		if(mValue < another.mValue)return -1;
		return 0;
	}

	Integer Integer::ValueOf(const jm::String &string)
	{
		int32 val = 0;
		bool neg = false;

		for(Integer a = 0; a < string.Length(); a++)
		{
			uint16 c = string.CharAt(a);

			if(c >= '0' && c <= '9')
			{
				val *= 10;
				val += c - '0';
			}
			else if(c == '-')neg = true;
			else throw new jm::Exception("Number format exception for input string: \"" + string + "\"");
		}

		if(neg)val *= -1;
		return val;
	}

	jm::String Integer::ToHexString()
	{
		jm::String ret;
		
		Integer number=mValue;

		//Prüfe auf 0
		if(number == 0)
		{
			ret.Append('0');
			return ret;
		}

		int32 base = 16;

		//Löse die einzelnen Zahlen auf... Achtung: die letzte Ziffer kommt zuerst
		while(number > 0)
		{
			int64 digit = number % base;
			number = number / base;
			ret.Append(gMask[digit]);
		}

		//Zahlen umkehren
		return ret.Reverse();
	}

	jm::String Integer::ToRomanString()
	{
		jm::String output;

		Integer index = 12;

		Integer number = mValue;

		while(index >= 0)
		{
			Integer div = number / gArabic[index];
			Integer rest = number % gArabic[index];
			number = rest;

			while(div > 0)
			{
				output.Append(gRoman[index]);
				div--;
			}
			index--;
		}

		return output;
	}

	jm::String Integer::ToLatinAlphabetString()
	{
		jm::String output;
		
		Integer number=mValue;

		while(number > 0)
		{
			int32 div = static_cast<int32>(number / 26);
			int16 rest = (int16)(number % 26 - 1);

			output.Append('A' + rest);

			number = div;
		}

		//Zahlen umkehren
		return output.Reverse();
	}

	int8 Integer::Int8()const
	{
		return (int8)mValue;
	}

	int16 Integer::Int16()const
	{
		return (int16)mValue;
	}

	int64 Integer::Int64()const
	{
		return mValue;
	}

	int32 Integer::Int32()const
	{
		return (int32) mValue; 
	}

	uint8 Integer::Uint8()const
	{
		return (uint8)mValue;
	}

	uint16 Integer::Uint16()const
	{
		return (uint16)mValue;
	}

	uint32 Integer::Uint32()const
	{
		return (uint32)mValue;
	}

	double Integer::Dbl()const
	{
		return (double)mValue;
	}

	Integer Integer::Abs() const
	{
		return std::abs(mValue);
	}

	Integer::operator int64() const
	{
		return mValue;
	}

	Integer& Integer::operator++()
	{
		mValue++;
		return *this;
	}

	Integer Integer::operator++(int32)
	{
		Integer i = *this;
		mValue++;
		return i;
	}

	Integer& Integer::operator--()
	{
		mValue--;
		return *this;
	}

	Integer Integer::operator--(int32)
	{
		Integer i = *this;
		mValue--;
		return i;
	}

	Integer& Integer::operator=(const Integer &another)
	{
		if(this != &another)
		{
			mValue=another.mValue;
		}

		return *this;
	}

	bool operator<(Integer left, Integer right)
	{
		return left.mValue < right.mValue;
	}

	bool operator<(Integer left, int32 right)
	{
		return left.mValue < right;
	}

	bool operator<(int32 left, Integer right)
	{
		return left < right.mValue;
	}

	bool operator<(Integer left, uint32 right)
	{
		return left.mValue < (int32)right;
	}

	bool operator<(uint32 left, Integer right)
	{
		return (int32)left < right.mValue;
	}

#ifdef WITHULONG
	bool operator<(Integer left, ulong right)
	{
		return left.mValue < (slong)right;
	}

	bool operator<(ulong left, Integer right)
	{
		return (slong)left < right.mValue;
	}
#endif
	bool operator<(Integer left, int64 right)
	{
		return left.mValue < right;
	}

	bool operator<(int64 left, Integer right)
	{
		return left < right.mValue;
	}

	bool operator<(Integer left, uint64 right)
	{
		return left.mValue < (int64)right;
	}

	bool operator<(uint64 left, Integer right)
	{
		return (int64)left < right.mValue;
	}

	bool operator<=(Integer left, Integer right)
	{
		return left.mValue <= right.mValue;
	}

	bool operator<=(Integer left, int32 right)
	{
		return left.mValue <= right;
	}

	bool operator<=(int32 left, Integer right)
	{
		return left <= right.mValue;
	}

	bool operator<=(Integer left, uint32 right)
	{
		return left.mValue <= (int32)right;
	}

	bool operator<=(uint32 left, Integer right)
	{
		return (int32)left <= right.mValue;
	}

#ifdef WITHULONG
	bool operator<=(Integer left, ulong right)
	{
		return left.mValue <= (slong)right;
	}

	bool operator<=(ulong left, Integer right)
	{
		return (slong)left <= right.mValue;
	}
#endif

	bool operator<=(Integer left, int64 right)
	{
		return left.mValue <= right;
	}

	bool operator<=(int64 left, Integer right)
	{
		return left <= right.mValue;
	}

	bool operator<=(Integer left, uint64 right)
	{
		return left.mValue <= (int64)right;
	}

	bool operator<=(uint64 left, Integer right)
	{
		return (int64)left <= right.mValue;
	}

	bool operator>(Integer left, Integer right)
	{
		return left.mValue > right.mValue;
	}

	bool operator>(Integer left, int32 right)
	{
		return left.mValue > right;
	}

	bool operator>(int32 left, Integer right)
	{
		return left > right.mValue;
	}

	bool operator>(Integer left, uint32 right)
	{
		return left.mValue > (int32)right;
	}

	bool operator>(uint32 left, Integer right)
	{
		return (int32)left > right.mValue;
	}

	bool operator>=(Integer left, Integer right)
	{
		return left.mValue >= right.mValue;
	}

	bool operator>=(Integer left, int32 right)
	{
		return left.mValue >= right;
	}

	bool operator>=(int32 left, Integer right)
	{
		return left >= right.mValue;
	}

	bool operator>=(Integer left, uint32 right)
	{
		return left.mValue >= (int32)right;
	}

	bool operator>=(uint32 left, Integer right)
	{
		return (int32)left >= right.mValue;
	}

	bool operator==(Integer left, Integer right)
	{
		return left.mValue == right.mValue;
	}

	bool operator==(Integer left, int32 right)
	{
		return left.mValue == right;
	}

	bool operator==(int32 left, Integer right)
	{
		return left == right.mValue;
	}

	bool operator!=(Integer left, Integer right)
	{
		return left.mValue != right.mValue;
	}

	bool operator!=(Integer left, int16 right)
	{
		return left.mValue != right;
	}

	bool operator!=(Integer left, uint16 right)
	{
		return left.mValue != right;
	}

	bool operator!=(Integer left, int32 right)
	{
		return left.mValue != right;
	}

	bool operator!=(Integer left, uint32 right)
	{
		return left.mValue != (int32)right;
	}

	bool operator!=(uint32 left, Integer right)
	{
		return (int32)left != right.mValue;
	}

	bool operator==(uint32 left, Integer right)
	{
		return (int32)left == right.mValue;
	}

	bool operator==(Integer left, uint32 right)
	{
		return left.mValue == (int32)right;
	}

	Integer& Integer::operator+=(const Integer &another)
	{
		mValue+=another.mValue;
		return *this;
	}

	Integer& Integer::operator-=(const Integer &another)
	{
		mValue-=another.mValue;
		return *this;
	}

	Integer Integer::operator<<(const Integer& shift)
	{
		return Integer(mValue << shift.mValue);
	}

	Integer Integer::operator<<(int32 shift)
	{
		return Integer(mValue << shift);
	}

	Integer Integer::operator>>(const Integer& shift)
	{
		return Integer(mValue >> shift.mValue);
	}

	Integer Integer::operator>>(int32 shift)
	{
		return Integer(mValue >> shift);
	}

	Integer operator+(Integer left, Integer right)
	{
		return Integer(left.mValue+right.mValue);
	}

	Integer operator+(Integer left, int64 right)
	{
		return Integer(left.mValue + right);
	}

	Integer operator+(int64 left, Integer right)
	{
		return Integer(left+right.mValue);
	}

	Integer operator+(Integer left, int32 right)
	{
		return Integer(left.mValue + right);
	}

	Integer operator+(int32 left, Integer right)
	{
		return Integer(left + right.mValue);
	}

	Integer operator+(Integer left, uint32 right)
	{
		return Integer(left.mValue + right);
	}

	Integer operator+(uint32 left, Integer right)
	{
		return Integer(left+right.mValue);
	}

	Integer operator+(Integer left, uint16 right)
	{
		return Integer(left.mValue + right);
	}

	Integer operator+(uint16 left, Integer right)
	{
		return Integer(left + right.mValue);
	}

	Integer operator-(Integer left, Integer right)
	{
		return Integer(left.mValue-right.mValue);
	}

	Integer operator-(Integer left, int32 right)
	{
		return Integer(left.mValue-right);
	}

	Integer operator-(int32 left, Integer right)
	{
		return Integer(left-right.mValue);
	}

	Integer operator-(Integer left, uint32 right)
	{
		return Integer(left.mValue-right);
	}

	Integer operator-(uint32 left, Integer right)
	{
		return Integer(left-right.mValue);
	}

	Integer operator*(Integer left, Integer right)
	{
		return Integer(left.mValue*right.mValue);
	}

	Integer operator*(Integer left, int32 right)
	{
		return Integer(left.mValue*right);
	}

	Integer operator*(int32 left, Integer right)
	{
		return Integer(left*right.mValue);
	}

	Integer operator*(Integer left, uint32 right)
	{
		return Integer(left.mValue*right);
	}

	Integer operator*(uint32 left, Integer right)
	{
		return Integer(left*right.mValue);
	}

	Integer operator*(Integer left, uint64 right)
	{
		return Integer(left.mValue * right);
	}

	Integer operator*(uint64 left, Integer right)
	{
		return Integer(left * right.mValue);
	}

#ifdef WITHULONG
	Integer operator*(Integer left, ulong right)
	{
		return Integer(left.mValue * right);
	}

	Integer operator*(ulong left, Integer right)
	{
		return Integer(left * right.mValue);
	}
#endif

	Double operator*(Integer left, double right)
	{
		return Double(left.mValue*right);
	}

	Double operator*(double left, Integer right)
	{
		return Double(left * right.mValue);
	}

	Double operator*(Integer left, float right)
	{
		return Double(left.mValue * right);
	}

	Double operator*(float left, Integer right)
	{
		return Double(left * right.mValue);
	}

	Integer operator/(Integer left, Integer right)
	{
		return Integer(left.mValue/right.mValue);
	}

	Integer operator/(Integer left, int32 right)
	{
		return Integer(left.mValue/right);
	}

	Integer Min(Integer left,Integer right)
	{
		return std::min(left,right);
	}

	Integer Max(Integer left,Integer right)
	{
		return std::max(left,right);
	}
















	Double::Double(): Comparable<Double>()
	{
		mValue=0.0;
	}

	Double::Double(const Double &value): Comparable<Double>()
	{
		mValue=value.mValue;
	}

	Double::Double(float value): Comparable<Double>()
	{
		mValue=value;
	}

	Double::Double(double value): Comparable<Double>()
	{
		mValue=value;
	}

	Double::Double(int32 value): Comparable<Double>()
	{
		mValue=value;
	}

	Double::Double(Integer value) : Comparable<Double>()
	{
		mValue = value.Dbl();
	}

	int32 Double::CompareTo(const Double& another) const
	{
		if(mValue > another.mValue)return 1;
		if(mValue < another.mValue)return -1;
		return 0;
	}

	double Double::Dbl()const
	{
		return mValue;
	}

	Double Double::ValueOf(const jm::String& string)
	{
		int8* cstr = string.ToCString();
		std::stringstream ss;
		double d = 0;
		ss << cstr;
		ss >> d;
		delete[] cstr;
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

	Double& Double::operator=(const Double &another)
	{
		if(this != &another)
		{
			mValue=another.mValue;
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

	Double& Double::operator+=(const Double &another)
	{
		mValue+=another.mValue;
		return *this;
	}

	Double& Double::operator-=(const Double &another)
	{
		mValue-=another.mValue;
		return *this;
	}

	Double& Double::operator*=(const Double &another)
	{
		mValue*=another.mValue;
		return *this;
	}

	Double& Double::operator/=(const Double &another)
	{
		mValue/=another.mValue;
		return *this;
	}

	Double operator+(Double left, Double right)
	{
		return Double(left.mValue+right.mValue);
	}

	Double operator+(Double left, double right)
	{
		return Double(left.mValue+right);
	}

	Double operator+(double left, Double right)
	{
		return Double(left+right.mValue);
	}

	Double operator+(Double left, float right)
	{
		return Double(left.mValue+right);
	}

	Double operator+(float left, Double right)
	{
		return Double(left+right.mValue);
	}

	Double operator+(Double left, int32 right)
	{
		return Double(left.mValue+right);
	}

	Double operator+(int32 left, Double right)
	{
		return Double(left+right.mValue);
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
		return Double(left.mValue*right.mValue);
	}

	Double operator*(Double left, double right)
	{
		return Double(left.mValue*right);
	}

	Double operator*(double left, Double right)
	{
		return Double(left*right.mValue);
	}

	Double operator*(Double left, float right)
	{
		return Double(left.mValue*right);
	}

	Double operator*(float left, Double right)
	{
		return Double(left*right.mValue);
	}

	Double operator*(Double left, Integer right)
	{
		return Double(left.mValue*right.Dbl());
	}

	Double operator*(Integer left, Double right)
	{
		return Double(left.Dbl()*right.mValue);
	}

	Double operator*(Double left, int32 right)
	{
		return Double(left.mValue*right);
	}

	Double operator*(int32 left, Double right)
	{
		return Double(left*right.mValue);
	}

	Double operator*(Double left, uint32 right)
	{
		return Double(left.mValue*right);
	}

	Double operator*(uint32 left, Double right)
	{
		return Double(left*right.mValue);
	}

	Double operator/(Double left, Double right)
	{
		return Double(left.mValue/right.mValue);
	}

	Double operator/(Double left, double right)
	{
		return Double(left.mValue/right);
	}

	Double operator/(double left, Double right)
	{
		return Double(left/right.mValue);
	}

	Double operator/(Double left, float right)
	{
		return Double(left.mValue/right);
	}

	Double operator/(float left, Double right)
	{
		return Double(left/right.mValue);
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
		return Double(left.mValue/right);
	}

	Double operator/(int32 left, Double right)
	{
		return Double(left/right.mValue);
	}

	Double Min(Double left,Double right)
	{
		return std::min(left,right);
	}

	Double Max(Double left,Double right)
	{
		return std::max(left,right);
	}
