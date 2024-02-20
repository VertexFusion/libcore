////////////////////////////////////////////////////////////////////////////////////////////////////
// Name:        Math.cpp
// Library:     Jameo Core Library
// Purpose:     Useful Math Functions
//
// Author:      Uwe Runtemund (2023-today)
// Modified by:
// Created:     14.10.2012
//
// Copyright:   (c) 2023 Jameo Software, Germany. https://jameo.de
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

using namespace jm;

const double T_PI = 1.0 / M_PI;
const double T_180 = 1.0 / 180.0;

double jm::DegToRad(double deg)
{
   return deg * M_PI * T_180;
}

double jm::RadToDeg(double rad)
{
   return rad * 180.0 * T_PI;
}

int16 jm::Sgn(double d)
{
   return (0 < d) - (d < 0);
}

int64 jm::Round(double d)
{
   return (int64)((d > 0.0) ? std::floor(d + 0.5) : std::ceil(d - 0.5));
}

float jm::RoundFrac(float f, int32 digits)
{
   double factor = std::pow(10, digits);
   double value = f * factor;
   int64 result = Round(value);
   value = static_cast<double>(result);
   return static_cast<float>(value / factor);
}

bool jm::IsEqual(double v1, double v2)
{
   double d = v2 - v1;
   return (d < RESABS) && (d > -RESABS);
}

bool jm::IsNotEqual(double v1, double v2)
{
   double d = v2 - v1;
   return !((d < RESABS) && (d > -RESABS));
}

bool jm::IsLess(double v1, double v2)
{
   return v1 + RESABS <= v2;
}

bool jm::IsLessEqual(double v1, double v2)
{
   return v1 < v2 + RESABS;
}

bool jm::IsGreater(double v1, double v2)
{
   return v1 >= v2 + RESABS;
}

bool jm::IsGreaterEqual(double v1, double v2)
{
   return v1 > v2 - RESABS;
}

bool jm::IsNaN(double d)
{
   return d != d;
}

void jm::Swap(Double &v1, Double &v2)
{
   double tmp = v1;
   v1 = v2;
   v2 = tmp;
}

void jm::Swap(double& v1, double& v2)
{
   double tmp = v1;
   v1 = v2;
   v2 = tmp;
}

void jm::Swap(int32 &v1, int32 &v2)
{
   v1 = v1 ^ v2;
   v2 = v2 ^ v1;
   v1 = v1 ^ v2;
}

void jm::Swap(uint32 &v1, uint32 &v2)
{
   v1 = v1 ^ v2;
   v2 = v2 ^ v1;
   v1 = v1 ^ v2;
}

void jm::Swap(uint16 &v1, uint16 &v2)
{
   v1 = v1 ^ v2;
   v2 = v2 ^ v1;
   v1 = v1 ^ v2;
}

void jm::Swap(uint8 &v1, uint8 &v2)
{
   v1 = v1 ^ v2;
   v2 = v2 ^ v1;
   v1 = v1 ^ v2;
}

double jm::Random()
{
   #ifdef __APPLE__
   uint16 x[3] = {(uint16)rand(), (uint16)rand(), (uint16)rand()};
   return erand48(x);
   #elif defined __linux__
   uint16 x[3] = {(uint16)rand(), (uint16)rand(), (uint16)rand()};
   return erand48(x);
   #elif defined _WIN32
   uint32 i = rand();
   uint32 m = RAND_MAX;
   return ((double)i) / ((double)m);
   #endif
}


int32 jm::Random(int32 lower, int32 upper)
{
   int32 z = rand() % (upper + 1 - lower);

   return z + lower;
}

bool jm::Probability(double percent)
{
   int32 value = Random(0, 10000);
   int32 threshold = (int32)(percent * 10000);
   return value <= threshold;
}

float jm::Interpolate(float begin, float end, float percent)
{
   return begin + percent * (end - begin);
}

double jm::Interpolate(double begin, double end, double percent)
{
   return begin + percent * (end - begin);
}

double jm::Interpolate(double vbegin, double vend, double begin, double end, double position)
{
   double percent = (position - begin) / (end - begin);
   return Interpolate(vbegin, vend, percent);
}

bool jm::PowerOf2(int32 x)
{
   return (x > 0) && ((x & (x - 1)) == 0);
}

uint32 jm::CeilPowerOf2(uint32 x)
{
   // Taken from https://github.com/keon/awesome-bits
   x--;
   x |= x >> 1;
   x |= x >> 2;
   x |= x >> 4;
   x |= x >> 8;
   x |= x >> 16;
   x++;
   return x;
}

double jm::DoubleMaschineEpsilon()
{
   double epsilon = 1.0;

   while(1.0 + 0.5 * epsilon != 1.0)epsilon = 0.5 * epsilon;

   return epsilon / 2.0;
}

float jm::FloatMaschineEpsilon()
{
   float epsilon = 1.0f;

   while(1.0f + 0.5f * epsilon != 1.0f)epsilon = 0.5f * epsilon;

   return epsilon / 2.0f;
}

int64 jm::DivFloor(int64 x, int64 y)
{
   int64 q = x / y;
   int64 r = x % y;
   if((r != 0) && ((r < 0) != (y < 0))) --q;
   return q;
}

int64 jm::ModFloor(int64 x, int64 y)
{
   int64 r = x % y;
   if((r != 0) && ((r < 0) != (y < 0)))
   {
      r += y;
   }
   return r;
}
