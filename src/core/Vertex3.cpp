////////////////////////////////////////////////////////////////////////////////////////////////////
// Name:        Vector.cpp
// Library:     Jameo Core Library
// Purpose:     3d vector for linea algebra
//
// Author:      Uwe Runtemund (2012-today)
// Modified by:
// Created:     22.10.2012
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

#include "Precompiled.hpp"

using namespace jm;

Vertex3::Vertex3(double x_, double y_, double z_):
   x(x_),
   y(y_),
   z(z_)
{}

Vertex3::Vertex3(const Vertex3& another):
   x(another.x),
   y(another.y),
   z(another.z)
{}

Vertex3::Vertex3(const Vertex2 xy, double z_):
   x(xy.x),
   y(xy.y),
   z(z_)
{}

Vertex3 Vertex3::crossProduct(const Vertex3& another) const
{
   return Vertex3(y * another.z - z * another.y,
                  z * another.x - x * another.z,
                  x * another.y - y * another.x);
}

double Vertex3::dotProduct(const Vertex3& another) const
{
   return x * another.x + y * another.y + z * another.z;
}

bool Vertex3::isCollinear(const Vertex3& another) const
{
   return isEqual(crossProduct(another).abs(), 0.0);
}

bool Vertex3::isOrthogonal(const Vertex3& another) const
{
   return isEqual(dotProduct(another), 0.0);
}

double Vertex3::angleTo(const Vertex3& another) const
{
   double angle = this->dotProduct(another) / (this->abs() * another.abs());
   return acos(angle);
}

double Vertex3::abs() const
{
   return std::sqrt(x * x + y * y + z * z);
}

bool Vertex3::isNull() const
{
   return (isEqual(x, 0.0) && isEqual(y, 0.0) && isEqual(z, 0.0));
}

bool Vertex3::isValid() const
{
   return  !(isNaN(x) || isNaN(y) || isNaN(z));
}


void Vertex3::rotateX(double angle)
{
   Matrix r = Matrix::generate3x3RotationXMatrix(angle);

   Vertex3 b = *this;
   Vertex3 v = r * b;
   x = v.x;
   y = v.y;
   z = v.z;
}

void Vertex3::rotateY(double angle)
{
   Matrix r = Matrix::generate3x3RotationYMatrix(angle);

   Vertex3 b = *this;
   Vertex3 v = r * b;
   x = v.x;
   y = v.y;
   z = v.z;
}

void Vertex3::rotateZ(double angle)
{
   Matrix r = Matrix::generate3x3RotationZMatrix(angle);

   Vertex3 b = *this;
   Vertex3 v = r * b;
   x = v.x;
   y = v.y;
   z = v.z;
}

void Vertex3::rotate(double angle, const Vertex3& axis)
{
   Matrix r = Matrix::generate3x3RotationMatrix(angle, axis);
   Vertex3 n = r * (*this);
   x = n.x;
   y = n.y;
   z = n.z;
}

Vertex3& Vertex3::normalize()
{
   double absolute = abs();
   if(jm::isEqual(absolute, 0.0))return *this;
   return *this = *this * (1.0 / absolute);
}

Vertex3 Vertex3::normalized() const
{
   double absolute = abs();
   if(jm::isEqual(absolute, 0.0))return *this;
   return *this * (1.0 / absolute);
}

Vertex3 Vertex3::scale(const Vertex3& another)const
{
   return Vertex3(x * another.x, y * another.y, z * another.z);
}

double Vertex3::biggest() const
{
   return (x > y && x > z) ? x : ((y > x && y > z) ? y : z);
}

/*
Vertex3 jm::Min(const Vertex3 &v1, const Vertex3 &v2)
{
	Vertex3 v;
	v.x = std::min(v1.x, v2.x);
	v.y = std::min(v1.y, v2.y);
	v.z = std::min(v1.z, v2.z);
	return v;
}

Vertex3 jm::Max(const Vertex3 &v1, const Vertex3 &v2)
{
	Vertex3 v;
	v.x = std::max(v1.x, v2.x);
	v.y = std::max(v1.y, v2.y);
	v.z = std::max(v1.z, v2.z);
	return v;
}*/


Vertex3 Vertex3::operator+(const Vertex3& other) const
{
   return Vertex3(x + other.x, y + other.y, z + other.z);
}

Vertex3 Vertex3::operator-(const Vertex3& other) const
{
   return Vertex3(x - other.x, y - other.y, z - other.z);
}

Vertex3 Vertex3::operator*(double d) const
{
   return Vertex3(d * x, d * y, d * z);
}

const Vertex3 jm::operator*(const double& d, const Vertex3& b)
{
   return Vertex3(d * b.x, d * b.y, d * b.z);
}

std::ostream& jm::operator<< (std::ostream& out, const Vertex3& vertex)
{
   out << "[" << vertex.x << " " << vertex.y << " " << vertex.z << "]";
   return out;
}

String& jm::operator<< (String& out, const Vertex3& vertex)
{
   out << "[" << vertex.x << " " << vertex.y << " " << vertex.z << "]";
   return out;
}

Vertex3 Vertex3::operator/(double d) const
{
   return Vertex3(x / d, y / d, z / d);
}

bool jm::operator!=(Vertex3 const& v1, Vertex3 const& v2)
{
   return isNotEqual(v1.x, v2.x) || isNotEqual(v1.y, v2.y) || isNotEqual(v1.z, v2.z);
}


bool jm::operator==(Vertex3 const& v1, Vertex3 const& v2)
{
   return isEqual(v1.x, v2.x) && isEqual(v1.y, v2.y) && isEqual(v1.z, v2.z);
}

Vertex3& Vertex3::operator+=(const Vertex3& v)
{
   x += v.x;
   y += v.y;
   z += v.z;
   return *this;
}

Vertex3& Vertex3::operator-=(const Vertex3& v)
{
   x -= v.x;
   y -= v.y;
   z -= v.z;
   return *this;
}

Vertex3& jm::Vertex3::operator=(const Vertex3& another)
{
   if(this != &another)
   {
      x = another.x;
      y = another.y;
      z = another.z;
   }
   return *this;
}


bool jm::isLinearIndependent(const Vertex3& v1, const Vertex3& v2, const Vertex3& v3)
{
   Matrix m = Matrix(v1, v2, v3, false);
   double det = 0;
   m.det(det);
   return isNotEqual(det, 0);
}


