////////////////////////////////////////////////////////////////////////////////////////////////////
// Name:        Matrix.h
// Library:     Jameo Core Library
// Purpose:     Matrix Class
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

#ifndef jm_Matrix_h
#define jm_Matrix_h

#include "Types.h"
#include "Vector.h"
#include "Vertex2.h"
#include "Vertex3.h"

namespace jm
{

   /*!
    \brief List of available matrix norms
    */
   enum class MatrixNorm
   {
      kNorm1,//!< Column Sum Norm
      kNormInf//!< Row Sum Norm
   };

   /*!
    \brief An m x n-dimensional matrix.
    \ingroup core
    */
   struct DllExport Matrix
   {
         DllExport
         friend const Matrix operator*(const Matrix& A, const Matrix& B);

         DllExport
         friend const Matrix operator*(const double& d, const Matrix& b);

         DllExport
         friend const Vertex3 operator*(const Matrix& A, const Vertex3& b);

         DllExport
         friend const Matrix operator+(const Matrix& A, const Matrix& B);

         DllExport
         friend const Matrix operator-(const Matrix& A, const Matrix& B);

         DllExport
         friend const Matrix operator/(const Matrix& A, const double& d);

      public:

         /*!
          \brief Number of rows.
          */
         int64 m;

         /*!
          \brief Number of columns.
          */
         int64 n;

         /*!
          \brief This constructor creates a matrix and initializes it with zeros.
          \param rows Number of rows.
          \param cols Number of columns.
          */
         Matrix(int64 rows, int64 cols);

         /*!
          \brief Special constructor for a 3x3 matrix.
          \param c1 The 1st column of the matrix
          \param c2 The 2nd column of the matrix
          \param c3 The 3rd column of the matrix
          \param rowwise if \c true, then the matrix is filled row by row otherwise column by
          column.
          */
         Matrix(const Vertex3& c1,
                const Vertex3& c2,
                const Vertex3& c3,
                bool rowwise);

         /*!
          \brief Default constructor.
          */
         Matrix();

         /*!
          \brief Constructor sets up a matrix 1x1 with the numerical value as entry,
          */
         Matrix(double value);

         /*!
          \brief Copy constructor
          */
         Matrix(const Matrix& other);

         /*!
          \brief Copy constructor
          */
         Matrix(const Matrix* other);

         /*!
          \brief Destructor
          */
         virtual ~Matrix();

         /*!
          \brief Sets the value of a cell.
          \param row The 0-based index of the row.
          \param col The 0-based index of the column.
          \param value The value of the cell.
          */
         void set(int64 row, int64 col, double value);

         /*!
          \brief Adds to the value of a cell the passed value.
          \param row The 0-based index of the row.
          \param col The 0-based index of the column.
          \param value The value to be added to the cell.
          */
         void add(int64 row, int64 col, double value);

         /*!
          \brief Returns the value of a cell.
          \param row The 0-based index of the row.
          \param col The 0-based index of the column.
          */
         double get(int64 row, int64 col) const;

         /*!
          \brief This method fills all elements of the matrix with 0.
          */
         void zeros();

         /*!
          \brief This method transposes the matrix,
          */
         void transpose();

         /*!
          \brief This method inserts the contents of the other matrix into this matrix. Upper left
          element is 0,0
          */
         void insert(const Matrix& A);

         /*!
         \brief This method inserts the contents of the Other matrix into this matrix. Upper left
          element is r,c
         */
         void insert(const Matrix& A, int64 r, int64 c);

         /*!
          \brief This method sets all values on the diagonal elements to the desired value.
          */
         void diag(double value);

         /*!
          \brief Calculates the determinant of a matrix.

          This method is currently limited to a maximum of 4x4 matrices.
          */
         VxfErrorStatus det(double& det) const;

         /*!
          \brief Inverts this matrix.

          This method is currently limited to a maximum of 4x4 matrices.
          */
         VxfErrorStatus inverse();

         /*!
          \brief This method returns the reference to the data array.

          Only needed for efficient access for OpenGL.
          */
         const double* ref() const;

         /*!
          \brief This method calculates the condition of the matrix according to the corresponding
          matrix norm.
          */
         double norm(MatrixNorm norm) const;

         /*!
          \brief Returns the sum of the diagonal elements.
          */
         double trace() const;

         /*!
          \brief Returns the Eigen Values of the matrix.

          Currentrly this is restricted to matrices of maximum 3x3.
          */
         Vector eigen() const;

         /*!
          \brief Prints the content of the matrix on \c std::cout
          */
         void print() const;

         /*!
          \brief This method calculates the number of elements that are not 0.0.
          Currently this is done without EPS.
          */
         uint32 nonZeroElementCount() const;

         /*!
          \brief This static function generates a 3x3 rotation matrix
          \param angle Angle of rotation in radians
          \param axis Rotation axis (must be normalized)
          */
         static Matrix generate3x3RotationMatrix(double angle, const Vertex3& axis);

         /*!
          \brief This static function generates a 3x3 rotation matrix for a rotation around the
          X-axis.
          \param angle Angle of rotation in radians
          */
         static Matrix generate3x3RotationXMatrix(double angle);

         /*!
          \brief This static function generates a 3x3 rotation matrix for a rotation around the
          Y-axis.
          \param angle Angle of rotation in radians
          */
         static Matrix generate3x3RotationYMatrix(double angle);

         /*!
          \brief This static function generates a 3x3 rotation matrix for a rotation around the
          Z-axis.
          \param angle Angle of rotation in radians
          */
         static Matrix generate3x3RotationZMatrix(double angle);

         /*!
          \brief This static function generates a 3x3 rotation matrix for a rotation from vector u to vector v.
          \param u The start vector
          \param v The end vector
          */
         static Matrix generate3x3RotationMatrix(const Vertex3& u, const Vertex3& v);

         Matrix& operator=(const Matrix& A);

      private:

         /*!
          \brief This field stores the data. In analogy to the OpenGL storage convention, the data
          is stored column by column.
          */
         double* data;
   };


   /*!
    \brief Implementation of the operator M * M (matrix multiplication).
    */
   DllExport
   const Matrix operator*(const Matrix& A, const Matrix& B);

   /*!
    \brief Implementation of the operator d * M (scalar multiplication).
    */
   DllExport
   const Matrix operator*(const double& d, const Matrix& b);

   /*!
    \brief Implementation of the operator M * d (scalar multiplication).
    */
   DllExport
   const Matrix operator*(const Matrix& A, const double& d);

   /*!
    \brief Implementation of the operator M * v (matrix multiplication with a vector). The matrix must be square.
    */
   DllExport
   const Vector operator*(const Matrix& A, const Vector& b);

   /*!
    \brief Implementation of the operator M * v (matrix multiplication with a vector). The matrix must be 3x3.
    */
   DllExport
   const Vertex3 operator*(const Matrix& A, const Vertex3& b);

   /*!
    \brief Implementation of the operator M / d (scalar division).
    */
   DllExport
   const Matrix operator/(const Matrix& b, const double& d);

   /*!
    \brief Implementation of the operator M + M (matrix addition).
    */
   DllExport
   const Matrix operator+(const Matrix& A, const Matrix& B);

   /*!
    \brief Implementation of the operator M - M (matrix subtraction).
    */
   DllExport
   const Matrix operator-(const Matrix& A, const Matrix& B);

}
#endif
