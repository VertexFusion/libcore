////////////////////////////////////////////////////////////////////////////////////////////////////
// Name:        Matrix.cpp
// Library:     Jameo Core Library
// Purpose:     Matrix
//
// Author:      Uwe Runtemund (2012-today)
// Modified by:
// Created:     22.10.2013
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

#include "Precompiled.h"

using namespace jm;

Matrix::Matrix(Integer rows, Integer cols)
{
   m = rows;
   n = cols;

   data = new double[m * n];

   zeros();
}

Matrix::Matrix(const Vertex3& c1,
               const Vertex3& c2,
               const Vertex3& c3,
               bool rowwise)
{
   m = 3;
   n = 3;

   data = new double[9];

   if(rowwise)
   {
      data[0] = c1.x;
      data[1] = c2.x;
      data[2] = c3.x;

      data[3] = c1.y;
      data[4] = c2.y;
      data[5] = c3.y;

      data[6] = c1.z;
      data[7] = c2.z;
      data[8] = c3.z;
   }
   else
   {
      data[0] = c1.x;
      data[1] = c1.y;
      data[2] = c1.z;

      data[3] = c2.x;
      data[4] = c2.y;
      data[5] = c2.z;

      data[6] = c3.x;
      data[7] = c3.y;
      data[8] = c3.z;
   }

}

Matrix::Matrix()
{
   m = 0;
   n = 0;
   data = NULL;
}

Matrix::Matrix(double value)
{
   m = 1;
   n = 1;

   data = new double[1];

   data[0] = value;
}

Matrix::Matrix(const Matrix& other)
{
   m = other.m;
   n = other.n;

   if(m * n > 0)
   {
      data = new double[m * n];

      for(uint32 i = 0; i < m * n; i++)
      {
         data[i] = other.data[i];
      }

   }
   else data = NULL;
}

Matrix::Matrix(const Matrix* other)
{
   m = other->m;
   n = other->n;
   data = new double[m * n];

   for(uint32 i = 0; i < m * n; i++)
   {
      data[i] = other->data[i];
   }
}

Matrix::~Matrix()
{
   if(data != NULL)
   {
      delete [] data;
      data = NULL;
   }
}

void Matrix::set(Integer row, Integer col, double value)
{
   // It is saved column by column
   data[row + col * m] = value;
}

void Matrix::add(Integer row, Integer col, double value)
{
   data[row + col * m] += value;
}

double Matrix::get(Integer row, Integer col) const
{
   return data[row + col * m];
}

void Matrix::zeros()
{
   uint64 count = m * n;
   for(uint32 i = 0; i < count; i++)
   {
      data[i] = 0.0;
   }
}

VxfErrorStatus Matrix::det(double& det) const
{
   if(m == n)
   {
      if(m == 1)
      {
         det = data[0];

         return eOK;
      }
      else if(m == 2)
      {
         // Rule of Sarrus
         // Index
         // | 0 2 |
         // | 1 3 |
         det = data[0] * data[3] - data[1] * data[2];

         return eOK;
      }
      else if(m == 3)
      {
         // Rule of Sarrus
         // Index
         // | 0 3 6 |
         // | 1 4 7 |
         // | 2 5 8 |
         double p1 = data[0] * data[4] * data[8];
         double p2 = data[3] * data[7] * data[2];
         double p3 = data[6] * data[1] * data[5];
         double m1 = data[6] * data[4] * data[2];
         double m2 = data[7] * data[5] * data[0];
         double m3 = data[8] * data[3] * data[1];

         det = p1 + p2 + p3 - m1 - m2 - m3;

         return eOK;
      }
      else if(m == 4)
      {
         // Index
         // | 0 4  8 12 |   | a e i m |   | 11 12 13 14 |
         // | 1 5  9 13 | = | b f j n | = | 21 22 23 24 |
         // | 2 6 10 14 |   | c g k o |   | 31 32 33 34 |
         // | 3 7 11 15 |   | d h l p |   | 41 42 43 44 |
         // Determine the inverse of the matrix
         double a11 = data[0];
         double a21 = data[1];
         double a31 = data[2];
         double a41 = data[3];
         double a12 = data[4];
         double a22 = data[5];
         double a32 = data[6];
         double a42 = data[7];
         double a13 = data[8];
         double a23 = data[9];
         double a33 = data[10];
         double a43 = data[11];
         double a14 = data[12];
         double a24 = data[13];
         double a34 = data[14];
         double a44 = data[15];

         double p1 = a11 * a22 * a33 * a44 + a11 * a23 * a34 * a42 + a11 * a24 * a32 * a43;
         double p2 = a12 * a21 * a34 * a43 + a12 * a23 * a31 * a44 + a12 * a24 * a33 * a41;
         double p3 = a13 * a21 * a32 * a44 + a13 * a22 * a34 * a41 + a13 * a24 * a31 * a42;
         double p4 = a14 * a21 * a33 * a42 + a14 * a22 * a31 * a43 + a14 * a23 * a32 * a41;
         double m1 = a11 * a22 * a34 * a43 + a11 * a23 * a32 * a44 + a11 * a24 * a33 * a42;
         double m2 = a12 * a21 * a33 * a44 + a12 * a23 * a34 * a41 + a12 * a24 * a31 * a43;
         double m3 = a13 * a21 * a34 * a42 + a13 * a22 * a31 * a44 + a13 * a24 * a32 * a41;
         double m4 = a14 * a21 * a32 * a43 + a14 * a22 * a33 * a41 + a14 * a23 * a31 * a42;

         det = p1 + p2 + p3 + p4 - m1 - m2 - m3 - m4;

         return eOK;
      }
      else
      {
         return eError;
      }
   }
   else return eError;
}



VxfErrorStatus Matrix::inverse()
{
   // See http://de.wikipedia.org/wiki/Inverse
   // http://www.cg.info.hiroshima-cu.ac.jp/~miyazaki/knowledge/teche23.html

   if(m == n)
   {
      if(m == 1)
      {
         data[0] = 1 / data[0];

         return eOK;
      }
      else if(m == 2)
      {
         double determinant;
         det(determinant);
         determinant = 1.0 / determinant;

         // Index
         // | 0 2 |   | a b |
         // | 1 3 | = | c d |

         double a = data[0];
         double b = data[2];
         double c = data[1];
         double d = data[3];
         data[0] = d * determinant;
         data[2] = (-b) * determinant;
         data[1] = (-c) * determinant;
         data[3] = a * determinant;

         return eOK;
      }
      else if(m == 3)
      {
         double determinant;
         det(determinant);
         determinant = 1.0 / determinant;

         // Index
         // | 0 3 6 |   | a b c |
         // | 1 4 7 | = | d e f |
         // | 2 5 8 |   | g h i |
         // Determine the inverse of the matrix
         double a = data[0];
         double b = data[3];
         double c = data[6];
         double d = data[1];
         double e = data[4];
         double f = data[7];
         double g = data[2];
         double h = data[5];
         double i = data[8];
         data[0] = (e * i - f * h) * determinant;
         data[3] = (c * h - b * i) * determinant;
         data[6] = (b * f - c * e) * determinant;
         data[1] = (f * g - d * i) * determinant;
         data[4] = (a * i - c * g) * determinant;
         data[7] = (c * d - a * f) * determinant;
         data[2] = (d * h - e * g) * determinant;
         data[5] = (b * g - a * h) * determinant;
         data[8] = (a * e - b * d) * determinant;

         return eOK;
      }
      else if(m == 4)
      {
         double determinant;
         det(determinant);
         determinant = 1.0 / determinant;

         // Index
         // | 0 4  8 12 |   | a e i m |   | 11 12 13 14 |
         // | 1 5  9 13 | = | b f j n | = | 21 22 23 24 |
         // | 2 6 10 14 |   | c g k o |   | 31 32 33 34 |
         // | 3 7 11 15 |   | d h l p |   | 41 42 43 44 |
         // Determine the inverse of the matrix
         double a11 = data[0];
         double a21 = data[1];
         double a31 = data[2];
         double a41 = data[3];
         double a12 = data[4];
         double a22 = data[5];
         double a32 = data[6];
         double a42 = data[7];
         double a13 = data[8];
         double a23 = data[9];
         double a33 = data[10];
         double a43 = data[11];
         double a14 = data[12];
         double a24 = data[13];
         double a34 = data[14];
         double a44 = data[15];

         data[0] = (a22 * a33 * a44 + a23 * a34 * a42 + a24 * a32 * a43 - a22 * a34 * a43 - a23 * a32 * a44 -
                    a24 * a33 * a42) * determinant;
         data[1] = (a21 * a34 * a43 + a23 * a31 * a44 + a24 * a33 * a41 - a21 * a33 * a44 - a23 * a34 * a41 -
                    a24 * a31 * a43) * determinant;
         data[2] = (a21 * a32 * a44 + a22 * a34 * a41 + a24 * a31 * a42 - a21 * a34 * a42 - a22 * a31 * a44 -
                    a24 * a32 * a41) * determinant;
         data[3] = (a21 * a33 * a42 + a22 * a31 * a43 + a23 * a32 * a41 - a21 * a32 * a43 - a22 * a33 * a41 -
                    a23 * a31 * a42) * determinant;
         data[4] = (a12 * a34 * a43 + a13 * a32 * a44 + a14 * a33 * a42 - a12 * a33 * a44 - a13 * a34 * a42 -
                    a14 * a32 * a43) * determinant;
         data[5] = (a11 * a33 * a44 + a13 * a34 * a41 + a14 * a31 * a43 - a11 * a34 * a43 - a13 * a31 * a44 -
                    a14 * a33 * a41) * determinant;
         data[6] = (a11 * a34 * a42 + a12 * a31 * a44 + a14 * a32 * a41 - a11 * a32 * a44 - a12 * a34 * a41 -
                    a14 * a31 * a42) * determinant;
         data[7] = (a11 * a32 * a43 + a12 * a33 * a41 + a13 * a31 * a42 - a11 * a33 * a42 - a12 * a31 * a43 -
                    a13 * a32 * a41) * determinant;
         data[8] = (a12 * a23 * a44 + a13 * a24 * a42 + a14 * a22 * a43 - a12 * a24 * a43 - a13 * a22 * a44 -
                    a14 * a23 * a42) * determinant;
         data[9] = (a11 * a24 * a43 + a13 * a21 * a44 + a14 * a23 * a41 - a11 * a23 * a44 - a13 * a24 * a41 -
                    a14 * a21 * a43) * determinant;
         data[10] = (a11 * a22 * a44 + a12 * a24 * a41 + a14 * a21 * a42 - a11 * a24 * a42 - a12 * a21 * a44
                     - a14 * a22 * a41) * determinant;
         data[11] = (a11 * a23 * a42 + a12 * a21 * a43 + a13 * a22 * a41 - a11 * a22 * a43 - a12 * a23 * a41
                     - a13 * a21 * a42) * determinant;
         data[12] = (a12 * a24 * a33 + a13 * a22 * a34 + a14 * a23 * a32 - a12 * a23 * a34 - a13 * a24 * a32
                     - a14 * a22 * a33) * determinant;
         data[13] = (a11 * a23 * a34 + a13 * a24 * a31 + a14 * a21 * a33 - a11 * a24 * a33 - a13 * a21 * a34
                     - a14 * a23 * a31) * determinant;
         data[14] = (a11 * a24 * a32 + a12 * a21 * a34 + a14 * a22 * a31 - a11 * a22 * a34 - a12 * a24 * a31
                     - a14 * a21 * a32) * determinant;
         data[15] = (a11 * a22 * a33 + a12 * a23 * a31 + a13 * a21 * a32 - a11 * a23 * a32 - a12 * a21 * a33
                     - a13 * a22 * a31) * determinant;

         return eOK;
      }
      else return eError;
   }
   else return eError;
}

void Matrix::transpose()
{
   Matrix tmp = this;
   Integer i = m;
   m = n;
   n = i;

   for(Integer a = 0; a < tmp.m; a++)
   {
      for(Integer b = 0; b < tmp.n; b++)
      {
         set(b, a, tmp.get(a, b));
      }
   }
}


void Matrix::insert(const Matrix& A)
{
   Integer rows = std::min(m, A.m);
   Integer cols = std::min(n, A.n);

   for(Integer r = 0; r < rows; r++)
   {
      for(Integer c = 0; c < cols; c++)
      {
         data[r + c * m] = A.data[r + c * A.m];
      }
   }
}


void Matrix::insert(const Matrix& A, Integer _r, Integer _c)
{
   Integer rows = std::min(m - _r, A.m);
   Integer cols = std::min(n - _c, A.n);

   for(Integer r = 0; r < rows; r++)
   {
      for(Integer c = 0; c < cols; c++)
      {
         data[(r + _r) + (c + _c) * m] = A.data[r + c * A.m];
      }
   }
}

void Matrix::diag(double value)
{
   Integer cnt = std::min(m, n);

   for(Integer i = 0; i < cnt; i++)
   {
      data[i * (m + 1)] = value;
   }
}

const double* Matrix::ref() const
{
   return data;
}

double Matrix::norm(MatrixNorm nm) const
{
   double norm = 0;
   double sum;
   switch(nm)
   {
      // Column sum norm
      case kMatrixNorm1:
         for(uint32 col = 0; col < n; col++)
         {
            sum = 0;
            for(uint32 row = 0; row < m; row++)
            {
               sum += fabs(get(row, col));
            }
            if(sum > norm)norm = sum;
         }
         break;

      // Row sum norm
      case kMatrixNormInf:
         for(uint32 row = 0; row < m; row++)
         {
            sum = 0;
            for(uint32 col = 0; col < n; col++)
            {
               sum += fabs(get(row, col));
            }
            if(sum > norm)norm = sum;
         }
         break;

      default:
         return 0;
   }

   return norm;
}

void Matrix::print() const
{
   for(uint32 r = 0; r < m; r++)
   {
      std::cout << "[ ";
      for(uint32 c = 0; c < n; c++)
      {
         std::cout << data[r + c * m] << ' ';
      }
      std::cout << " ]" << std::endl;
   }

}

uint32 Matrix::nonZeroElementCount() const
{
   uint32 count = 0;

   for(uint32 r = 0; r < m; r++)
   {
      for(uint32 c = 0; c < n; c++)
      {
         if(data[r + c * m] != 0.0)count++;
      }
   }

   return count;
}

double Matrix::trace() const
{
   double sum = 0.0;

   // Just do ensure, that we make no error even if the matrix is not square.
   Integer cnt = std::min(m, n);

   for(Integer i = 0; i < cnt; i++)
   {
      sum += data[i * (m + 1)];
   }

   return sum;
}

Vector Matrix::eigen() const
{
   if(m != n)throw new Exception("Matrix must be square");

   // See: https://en.wikipedia.org/wiki/Eigenvalue_algorithm

   if(m == 1)
   {
      Vector v = Vector(1);
      v.data[0] = get(0, 0);
      return v;
   }
   if(m == 2)
   {
      Vector v = Vector(2);

      double trA = trace();
      double detA;
      det(detA);
      double gapA = sqrt(trA * trA - 4 * detA);

      v.data[0] = (trA - gapA) / 2.0;
      v.data[1] = (trA + gapA) / 2.0;

      return v;
   }
   if(m == 3)
   {
      // Note: Matrix must be symmetric
      Vector v = Vector(3);

      double p1 = pow(get(0, 1), 2.0) + pow(get(0, 2), 2.0) + pow(get(1, 2), 2.0);

      if(p1 == 0.0)
      {
         v.data[0] = get(0, 0);
         v.data[1] = get(1, 1);
         v.data[2] = get(2, 2);
      }
      else
      {
         double q = trace() / 3.0;
         double p2 = pow(get(0, 0) - q, 2.0) + pow(get(1, 1) - q, 2.0) + pow(get(2, 2) - q, 2.0) + 2.0 * p1;
         double p = sqrt(p2 / 6.0);

         Matrix A = *this;
         Matrix I(3, 3);
         I.diag(1.0);

         Matrix B = (1.0 / p) * (A - q * I);

         double detB;
         B.det(detB);

         double r = detB / 2.0;

         double phi;

         if(r <= -1.0)phi = M_PI / 3.0;
         else if(r >= 1.0)phi = 0.0;
         else phi = acos(r) / 3.0;

         double eig1 = q + 2.0 * p * cos(phi);
         double eig3 = q + 2.0 * p * cos(phi + (M_2PI / 3.0));
         double eig2 = 3.0 * q - eig1 - eig3;

         v.data[0] = eig1;
         v.data[1] = eig2;
         v.data[2] = eig3;
      }
      return v;
   }

   throw new Exception("Matrix is greater than 3x3");
}

namespace jm
{
   Matrix& Matrix::operator=(const Matrix& A)
   {
      if(this == &A) return *this;
      m = A.m;
      n = A.n;
      if(data != NULL)delete[] data;

      if(m * n > 0)
      {
         data = new double[m * n];

         for(uint32 i = 0; i < m * n; i++)
         {
            data[i] = A.data[i];
         }

      }
      else data = NULL;

      return *this;
   }
}

const Vertex3 jm::operator*(Matrix const& A, Vertex3 const& b)
{
   // Index
   // | 0 3 6 |   | x |
   // | 1 4 7 | * | y |
   // | 2 5 8 |   | z |

   Vertex3 r;
   if(A.m != 3 || A.n != 3) throw("Matrix muss 3 Zeilen und 3 Spalten haben");
   r.x = A.data[0] * b.x + A.data[3] * b.y + A.data[6] * b.z;
   r.y = A.data[1] * b.x + A.data[4] * b.y + A.data[7] * b.z;
   r.z = A.data[2] * b.x + A.data[5] * b.y + A.data[8] * b.z;
   return r;
}

const Matrix jm::operator*(Matrix const& A, Matrix const& B)
{
   // The number of columns in the left-hand matrix must match the number of rows in the right-hand
   // matrix
   if(A.n != B.m) throw new
      jm::Exception("Die Matrizen passen nicht zusammen! A: ");   //'+IntToStr(A.m)+'x'+IntToStr(A.n)+' B:'+IntToStr(B.m)+'x'+IntToStr(B.n));

   Matrix R = Matrix(A.m, B.n);

   // Index
   // | 0 3 6 |   | 0 3 6 |
   // | 1 4 7 | * | 1 4 7 |
   // | 2 5 8 |   | 2 5 8 |

   for(Integer i = 0; i < A.m; i++)   // i: Left Rows
   {
      for(Integer j = 0; j < B.n; j++)   //j: RIght columns
      {
         Integer rIndex = i + j * A.m;

         for(Integer k = 0; k < A.n; k++)   // k: Left Cols = Right Cols
         {
            Integer aIndex = i + k * A.m;
            Integer bIndex = k + j * B.m;
            R.data[rIndex] += A.data[aIndex] * B.data[bIndex];
         }
      }
   }

   return R;
}

const Matrix jm::operator+(Matrix const& A, Matrix const& B)
{
   //Die Spaltenanzahl der linken Matrix muss mit der Zeilenanzahl der Rechten Matrix übereinstimmen
   if(A.n != B.m) throw new
      jm::Exception("Die Matrizen passen nicht zusammen! A: ");   //'+IntToStr(A.m)+'x'+IntToStr(A.n)+' B:'+IntToStr(B.m)+'x'+IntToStr(B.n));

   Matrix R = Matrix(A.m, B.n);

   // Index
   // | 0 3 6 |   | 0 3 6 |
   // | 1 4 7 | + | 1 4 7 |
   // | 2 5 8 |   | 2 5 8 |

   for(Integer i = 0; i < A.m; i++)   // i: Zeilen der Linken
   {
      for(Integer j = 0; j < B.n; j++)   //j: Spalten der Rechten
      {
         Integer rIndex = i + j * A.m;
         R.data[rIndex] = A.data[rIndex] + B.data[rIndex];
      }
   }

   return R;
}

const Matrix jm::operator-(Matrix const& A, Matrix const& B)
{
   //Die Spaltenanzahl der linken Matrix muss mit der Zeilenanzahl der Rechten Matrix übereinstimmen
   if(A.n != B.m) throw new
      jm::Exception("Die Matrizen passen nicht zusammen! A: ");   //'+IntToStr(A.m)+'x'+IntToStr(A.n)+' B:'+IntToStr(B.m)+'x'+IntToStr(B.n));

   Matrix R = Matrix(A.m, B.n);

   // Index
   // | 0 3 6 |   | 0 3 6 |
   // | 1 4 7 | - | 1 4 7 |
   // | 2 5 8 |   | 2 5 8 |

   for(Integer i = 0; i < A.m; i++)   // i: Zeilen der Linken
   {
      for(Integer j = 0; j < B.n; j++)   //j: Spalten der Rechten
      {
         Integer  rIndex = i + j * A.m;
         R.data[rIndex] = A.data[rIndex] - B.data[rIndex];
      }
   }

   return R;
}

const Matrix jm::operator*(double const& d, Matrix const& A)
{
   Matrix R = Matrix(A.m, A.n);

   for(Integer i = 0; i < A.m * A.n; i++)
   {
      R.data[i] = d * A.data[i];
   }

   return R;
}

const Matrix jm::operator*(Matrix const& A, double const& d)
{
   return d * A;
}

const Matrix jm::operator/(Matrix const& A, double const& d)
{
   Matrix R = Matrix(A.m, A.n);

   for(Integer i = 0; i < A.m * A.n; i++)
   {
      R.data[i] = A.data[i] / d;
   }

   return R;
}

Matrix Matrix::generate3x3RotationMatrix(double angle, const Vertex3& axis)
{
   //Siehe https://www.opengl.org/sdk/docs/man2/xhtml/glRotate.xml (eher nicht)
   //      https://en.wikipedia.org/wiki/Rotation_matrix
   // Index
   // | 0 3 6 |
   // | 1 4 7 |
   // | 2 5 8 |

   Matrix r = Matrix(3, 3);

   double x = axis.x;
   double y = axis.y;
   double z = axis.z;
   double c = cos(angle);
   double s = sin(angle);

   //1. Zeile
   r.data[0] = c + x * x * (1.0 - c);
   r.data[3] = x * y * (1.0 - c) - z * s;
   r.data[6] = x * z * (1.0 - c) + y * s;

   //2. Zeile
   r.data[1] = y * x * (1.0 - c) + z * s;
   r.data[4] = c + y * y * (1.0 - c);
   r.data[7] = y * z * (1.0 - c) - x * s;

   //3. Zeile
   r.data[2] = z * x * (1.0 - c) - y * s;
   r.data[5] = y * z * (1.0 - c) + x * s;
   r.data[8] = c + z * z * (1.0 - c);

   return r;
}

Matrix Matrix::generate3x3RotationXMatrix(double angle)
{

   // Index
   // | 0 3 6 |
   // | 1 4 7 |
   // | 2 5 8 |

   Matrix r = Matrix(3, 3);

   r.data[0] = 1;
   r.data[4] = cos(angle);
   r.data[8] = cos(angle);

   r.data[7] = -sin(angle);
   r.data[5] = sin(angle);

   return r;
}

Matrix Matrix::generate3x3RotationYMatrix(double angle)
{

   // Index
   // | 0 3 6 |
   // | 1 4 7 |
   // | 2 5 8 |

   Matrix r = Matrix(3, 3);

   r.data[0] = cos(angle);
   r.data[4] = 1;
   r.data[8] = cos(angle);

   r.data[2] = -sin(angle);
   r.data[6] = sin(angle);

   return r;
}

Matrix Matrix::generate3x3RotationZMatrix(double angle)
{

   // Index
   // | 0 3 6 |
   // | 1 4 7 |
   // | 2 5 8 |

   Matrix r = Matrix(3, 3);

   r.data[0] = cos(angle);
   r.data[4] = cos(angle);
   r.data[8] = 1;

   r.data[3] = -sin(angle);
   r.data[1] = sin(angle);

   return r;
}

Matrix Matrix::generate3x3RotationMatrix(const jm::Vertex3& u, const jm::Vertex3& v)
{
    // Normalize both vectors
    jm::Vertex3 u_norm = u.normalized();
    jm::Vertex3 v_norm = v.normalized();

    // Calculate the cross product
    jm::Vertex3 axis = u_norm.crossProduct(v_norm);

    // Calculate the dot product
    double cosTheta = u_norm.DotProduct(v_norm);

    // Calculate the sine of the angle
    double sinTheta = axis.abs();

    // Normalize the axis
    axis.normalize();

    // Construct the rotation matrix using Rodrigues' rotation formula
    jm::Matrix rotationMatrix=jm::Matrix(3,3);
    rotationMatrix.set(0, 0, cosTheta + axis.x * axis.x * (1 - cosTheta));
    rotationMatrix.set(0, 1, axis.x * axis.y * (1 - cosTheta) - axis.z * sinTheta);
    rotationMatrix.set(0, 2, axis.x * axis.z * (1 - cosTheta) + axis.y * sinTheta);

    rotationMatrix.set(1, 0, axis.y * axis.x * (1 - cosTheta) + axis.z * sinTheta);
    rotationMatrix.set(1, 1, cosTheta + axis.y * axis.y * (1 - cosTheta));
    rotationMatrix.set(1, 2, axis.y * axis.z * (1 - cosTheta) - axis.x * sinTheta);

    rotationMatrix.set(2, 0, axis.z * axis.x * (1 - cosTheta) - axis.y * sinTheta);
    rotationMatrix.set(2, 1, axis.z * axis.y * (1 - cosTheta) + axis.x * sinTheta);
    rotationMatrix.set(2, 2, cosTheta + axis.z * axis.z * (1 - cosTheta));

    return rotationMatrix;
}


const Vector jm::operator*(Matrix const& A, Vector const& b)
{
   // Index
   // | 0 3 6 |   | x |
   // | 1 4 7 | * | y |
   // | 2 5 8 |   | z |
   if(A.n != b.m) throw("Matrix must have the same number of columns as vector number of rows");

   Vector ret = Vector(A.m);

   for(Integer r = 0; r < A.m; r++)
   {
      ret.data[r] = 0.0;
      for(Integer c = 0; c < A.n; c++)
      {
         ret.data[r] += b.data[c] * A.get(r, c);
      }
   }

   return ret;
}
