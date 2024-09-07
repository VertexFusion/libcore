////////////////////////////////////////////////////////////////////////////////////////////////////
// Name:        Vertex2.cpp
// Library:     Jameo Core Library
// Purpose:     2d vector for linea algebra
//
// Author:      Uwe Runtemund (2013-today)
// Modified by:
// Created:     16.01.2013
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

#include "Precompiled.hpp"

using namespace jm;


Vertex2::Vertex2()
{}

Vertex2::Vertex2(double xx, double yy):
   x(xx),
   y(yy)
{}

Vertex2::Vertex2(const Vertex3& v3):
   x(v3.x),
   y(v3.y)
{}

double Vertex2::abs() const
{
   return sqrt(x * x + y * y);
}

Vertex2& Vertex2::normalize()
{
   double absolute = abs();
   if(jm::isEqual(absolute, 0.0))return *this;
   return *this = *this * (1.0 / absolute);
}

Vertex2 Vertex2::normalized()const
{
   double absolute = abs();
   if(jm::isEqual(absolute, 0.0))return *this;
   return *this * (1.0 / absolute);
}

double Vertex2::crossProduct(const Vertex2& another) const
{
   return x * another.y - y * another.x;
}

double Vertex2::dotProduct(const Vertex2& another) const
{
   return x * another.x + y * another.y;
}

bool Vertex2::isCollinear(const Vertex2& another) const
{
   return isEqual(crossProduct(another), 0);
}

bool Vertex2::isOrthogonal(const Vertex2& another) const
{
   return isEqual(dotProduct(another), 0);
}

double Vertex2::angleTo(const Vertex2& another) const
{
   // Enclosed angles returned
   double tmp = this->dotProduct(another) / (this->abs() * another.abs());

   // Same sign convention as in SVG
   double sgn = (x * another.y - y * another.x) > 0 ? 1 : -1;
   double angle = acos(tmp) * sgn;

   return angle;
}

bool Vertex2::isRightTo(const Vertex2& another) const
{
   double dot = another.x * -y + another.y * x;
   if(dot > 0)return true;
   return false;
}

bool Vertex2::isLeftTo(const Vertex2& another) const
{
   double dot = another.x * -y + another.y * x;
   if(dot < 0)return true;
   return false;
}

Vertex2& Vertex2::rotate(double angle)
{
   // Direction of rotation is counterclockwise.
   double nx = x * cos(angle) - y * sin(angle);
   double ny = x * sin(angle) + y * cos(angle);
   x = nx;
   y = ny;

   return *this;
}

Vertex2 Vertex2::scale(const Vertex2& another) const
{
   return Vertex2(x * another.x, y * another.y);
}

bool Vertex2::isValid() const
{
   return  !(isNaN(x) || isNaN(y));
}


Vertex2& Vertex2::operator+=(const Vertex2& another)
{
   this->x += another.x;
   this->y += another.y;
   return *this;
}

Vertex2& Vertex2::operator-=(const Vertex2& another)
{
   this->x -= another.x;
   this->y -= another.y;
   return *this;
}


const Vertex2 jm::operator+(const Vertex2& v1, const Vertex2& v2)
{
   Vertex2 r;
   r.x = v1.x + v2.x;
   r.y = v1.y + v2.y;
   return r;
}

const Vertex2 jm::operator-(const Vertex2& v1, const Vertex2& v2)
{
   Vertex2 r;
   r.x = v1.x - v2.x;
   r.y = v1.y - v2.y;
   return r;
}

const Vertex2 jm::operator*(double const& d, Vertex2 const& v)
{
   Vertex2 r;
   r.x = d * v.x;
   r.y = d * v.y;
   return r;
}

const Vertex2 jm::operator*(const Integer& i, const Vertex2& v)
{
   Vertex2 r;
   r.x = i.Dbl() * v.x;
   r.y = i.Dbl() * v.y;
   return r;
}

Vertex2 Vertex2::operator*(double d) const
{
   return Vertex2(d * x, d * y);
}

Vertex2 Vertex2::operator/(double d) const
{
   return Vertex2(x / d, y / d);
}

bool jm::operator!=(Vertex2 const& v1, Vertex2 const& v2)
{
   return isNotEqual(v1.x, v2.x) || isNotEqual(v1.y, v2.y) ;
}

std::ostream& jm::operator<< (std::ostream& out, const Vertex2& vertex)
{
   out << "[" << vertex.x << " " << vertex.y << "]";
   return out;
}

Vertex2 jm::SolveLinearSystem(Vertex2 a, Vertex2 b, Vertex2 r)
{
   //Mache eine kurze LR-Zerlegung
   //    dir off     point-origin
   //  | A1 B1 | = | R1 |
   //  | A2 B2 |   | R2 |
   double A1 = a.x;
   double A2 = a.y;
   double B1 = b.x;
   double B2 = b.y;
   double R1 = r.x;
   double R2 = r.y;

   //Pivotisierung
   if(isEqual(A1, 0))
   {
      swap(A1, A2);
      swap(B1, B2);
      swap(R1, R2);
   }

   //Eliminiere (also so, dass A2 zu 0 wird)
   double F = A2 / A1;
   B2 = B2 - F * B1;
   R2 = R2 - F * R1;

   //Berechne B
   double B = R2 / B2;

   //Berechne A
   double A = (R1 - B * B1) / A1;

   return Vertex2(A, B);
}
