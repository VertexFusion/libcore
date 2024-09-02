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



double Double::valueOf(const jm::String& string)
{
   jm::ByteArray cstr = string.toCString();
   std::stringstream ss;
   double d = 0;
   ss << cstr.constData();
   ss >> d;
   return d;
}

int64 Double::round(double number)
{
   return ((number > 0.0) ? std::floor(number + 0.5) : std::ceil(number - 0.5));
}

double Double::roundFrac(double value,int64 digits)
{
   double factor = std::pow(10, digits);
   double result = value * factor;
   result = round(result);
   return result / factor;
}
