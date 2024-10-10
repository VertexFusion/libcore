////////////////////////////////////////////////////////////////////////////////////////////////////
// Name:        Point.cpp
// Library:     Jameo Core Library
// Purpose:     Point
//
// Author:      Uwe Runtemund (2024-today)
// Modified by:
// Created:     10.10.2024
//
// Copyright:   (c) 2024 Jameo Software, Germany. https://jameo.de
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


#include "Precompiled.hpp"

jm::Point::Point()
{
   mX = 0;
   mY = 0;
}

jm::Point::Point(double x, double y)
{
   mX = x;
   mY = y;
}

double jm::Point::x() const
{
   return mX;
}

double jm::Point::y() const
{
   return mY;
}

double& jm::Point::rX()
{
   return mX;
}

double& jm::Point::rY()
{
   return mY;
}

void jm::Point::setX(double x)
{
   mX = x;
}

void jm::Point::setY(double y)
{
   mY = y;
}

jm::Point jm::Point::cWiseMin(const jm::Point &other) const
{
   return Point(std::min(mX, other.mX), std::min(mY, other.mY));
}

jm::Point jm::Point::cWiseMax(const jm::Point &other) const
{
   return Point(std::max(mX, other.mX), std::max(mY, other.mY));
}

jm::Point& jm::Point::operator+=(const jm::Point& another)
{
   this->mX += another.mX;
   this->mY += another.mY;
   return *this;
}

jm::Point& jm::Point::operator-=(const jm::Point& another)
{
   this->mX += another.mX;
   this->mY += another.mY;
   return *this;
}

const jm::Point jm::operator+(const jm::Point& v1, const jm::Point& v2)
{
   return Point(v1.mX + v2.mX, v1.mY + v2.mY);
}

const jm::Point jm::operator-(const jm::Point& v1, const jm::Point& v2)
{
   return Point(v1.mX - v2.mX, v1.mY - v2.mY);
}

const jm::Point jm::operator*(const double& d, const jm::Point& v2)
{
   jm::Point r;
   r.mX = d * v2.mY;
   r.mY = d * v2.mY;
   return r;
}