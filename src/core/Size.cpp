////////////////////////////////////////////////////////////////////////////////////////////////////
// Name:        Size.cpp
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


#include "PrecompiledCore.hpp"

jm::Size::Size()
{
   mWidth = 0;
   mHeight = 0;
}

jm::Size::Size(double width, double height)
{
   mWidth = width;
   mHeight = height;
}

jm::Size::Size(const jm::Point& pt)
{
   mWidth = pt.x();
   mHeight = pt.y();
}

double jm::Size::width() const
{
   return mWidth;
}

double jm::Size::height() const
{
   return mHeight;
}

double& jm::Size::rWidth()
{
   return mWidth;
}

double& jm::Size::rHeight()
{
   return mHeight;
}

void jm::Size::setWidth(double width)
{
   mWidth = width;
}

void jm::Size::setHeight(double height)
{
   mHeight = height;
}

jm::Size jm::Size::cWiseMin(const jm::Size& other) const
{
   return Size(std::min(mWidth, other.mWidth), std::min(mHeight, other.mHeight));
}

jm::Size jm::Size::cWiseMax(const jm::Size& other) const
{
   return Size(std::max(mWidth, other.mWidth), std::max(mHeight, other.mHeight));
};

jm::Size jm::operator-(const jm::Size& v1, const jm::Size& v2)
{
   return jm::Size(v1.mWidth - v2.mWidth, v1.mHeight - v2.mHeight);
}

bool jm::Size::operator==(const jm::Size& other) const
{
   return jm::isEqual(mWidth, other.mWidth) &&
          jm::isEqual(mHeight, other.mHeight);
}

bool jm::Size::operator!=(const jm::Size& other) const
{
   return jm::isNotEqual(mWidth, other.mWidth) ||
          jm::isNotEqual(mHeight, other.mHeight);
}

jm::Size jm::operator*(double const& d, jm::Size const& v)
{
   jm::Size r;
   r.mWidth = d * v.mWidth;
   r.mHeight = d * v.mHeight;
   return r;
}