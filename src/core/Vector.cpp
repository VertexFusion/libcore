////////////////////////////////////////////////////////////////////////////////////////////////////
// Name:        Vector.cpp
// Library:     Jameo Core Library
// Purpose:     General vector for linea algebra
//
// Author:      Uwe Runtemund (2012-today)
// Modified by:
// Created:     30.10.2012
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

jm::Vector::Vector()
{
   m = 0;
   data = nullptr;
}

jm::Vector::Vector(Integer rows)
{
   m = rows;
   data = new double[rows];
   for(Integer a = 0; a < m; a++)data[a] = 0.0;
}

jm::Vector::Vector(const Vector& another)
{
   m = another.m;
   if(m > 0)
   {
      data = new double[m];
      for(Integer a = 0; a < m; a++)data[a] = another.data[a];
   }
   else data = nullptr;
}

jm::Vector::~Vector()
{
   if(data != nullptr)delete[] data;
   data = nullptr;
   m = 0;
}

double jm::Vector::abs() const
{
   double ret = 0;

   for(Integer a = 0; a < m; a++)ret += data[a] * data[a];

   ret = std::sqrt(ret);

   return ret;
}

void jm::Vector::normalize()
{
   double v = abs();

   for(Integer a = 0; a < m; a++)data[a] /= v;
}

void jm::Vector::zeros()
{
   for(Integer a = 0; a < m; a++)data[a] = 0.0;
}

void jm::Vector::ones()
{
   for(Integer a = 0; a < m; a++)data[a] = 1.0;
}

double jm::Vector::dotProduct(const Vector& another) const
{
   double prod = 0.0;
   for(Integer a = 0; a < m; a++)
   {
      prod += data[a] * another.data[a];
   }
   return prod;
}

std::ostream& jm::operator<< (std::ostream& out, const Vector& vec)
{
   out << "[ ";
   for(Integer a = 0; a < vec.m; a++)out << vec.data[a] << ' ' ;
   out << " ]";
   return out;
}

jm::Vector& jm::Vector::operator=(const jm::Vector& another)
{
   if(this != &another)
   {
      if(data != nullptr)delete[] data;
      m = another.m;
      if(m > 0)
      {
         data = new double[m];
         for(Integer a = 0; a < m; a++)data[a] = another.data[a];
      }
      else data = nullptr;
   }

   return *this;
}

const jm::Vector jm::operator+(const jm::Vector& v1, const jm::Vector& v2)
{
   if(v1.m != v2.m) throw new Exception("dimensions don't match");
   jm::Vector v = jm::Vector(v1.m);

   for(Integer a = 0; a < v.m; a++)v.data[a] = v1.data[a] + v2.data[a];

   return v;
}

const jm::Vector jm::operator-(const jm::Vector& v1, const jm::Vector& v2)
{
   if(v1.m != v2.m) throw new Exception("dimensions don't match");

   Vector v = Vector(v1.m);

   for(Integer a = 0; a < v.m; a++)v.data[a] = v1.data[a] - v2.data[a];

   return v;
}

const jm::Vector jm::operator*(const double& d, const jm::Vector& v)
{
   jm::Vector r = jm::Vector(v.m);

   for(Integer a = 0; a < v.m; a++)r.data[a] = d * v.data[a];

   return r;

}
