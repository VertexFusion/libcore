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
         friend Matrix operator*(const Matrix& A, const Matrix& B);

         DllExport
         friend Matrix operator*(const double& d, const Matrix& b);

         DllExport
         friend Vertex3 operator*(const Matrix& A, const Vertex3& b);

         DllExport
         friend Matrix operator+(const Matrix& A, const Matrix& B);

         DllExport
         friend Matrix operator-(const Matrix& A, const Matrix& B);

         DllExport
         friend Matrix operator/(const Matrix& A, const double& d);

      public:

         /*!
          \brief This constructor creates a matrix and initializes it with zeros.
          \param rows Number of rows.
          \param cols Number of columns.
          */
         Matrix(size_t rows, size_t cols);

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
         Matrix() = default;

         /*!
          \brief Constructor sets up a matrix 1x1 with the numerical value as entry,
          */
         explicit Matrix(double value);

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
         void set(size_t row, size_t col, double value);

         /*!
          \brief Adds to the value of a cell the passed value.
          \param row The 0-based index of the row.
          \param col The 0-based index of the column.
          \param value The value to be added to the cell.
          */
         void add(size_t row, size_t col, double value);

         /*!
          \brief Returns the value of a cell.
          \param row The 0-based index of the row.
          \param col The 0-based index of the column.
          */
         double get(size_t row, size_t col) const;

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
         void insert(const Matrix& A, size_t r, size_t c);

         /*!
          \brief This method sets all values on the diagonal elements to the desired value.
          */
         void diag(double value);

         /*!
          \brief Calculates the determinant of a matrix.

          This method is currently limited to a maximum of 4x4 matrices.
          */
         Status det(double& det) const;

         /*!
          \brief Inverts this matrix.

          This method is currently limited to a maximum of 4x4 matrices.
          */
         Status inverse();

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
         size_t nonZeroElementCount() const;

         /*!
          \brief Initializes this transformation as an identity matrix.
          \details An identity matrix is a square matrix in which all the elements of the principal
          diagonal are ones and all other elements are zeros. When a vector or point is multiplied
          by an identity matrix, the result is the same vector or point. This method sets the
          transformation matrix to an identity matrix, effectively resetting any previous
          transformations applied.
          */
         void initIdentity();

         /*!
          \brief Initializes this matrix as a World Coordinate System (WCS) matrix.
          \note The matrix must be 4x4
          \param extrusion The extrusion vector used for the transformation.
          \details This method initializes the transformation matrix as a WCS matrix, which
          represents the coordinate system transformation from Object Coordinate System (OCS) to
          WCS. The extrusion vector is used to define the direction of the Z-axis in the WCS.
          The resulting matrix can be used to transform 3D points and angles from OCS to WCS.
          */
         void initWcs(const Vertex3& extrusion);

         /*!
          \brief Initializes this matrix as a mirroring matrix.
          \param planePoint The point on the mirror plane.
          \param planeNormal The normal vector of the mirror plane.
          \details This method initializes the transformation matrix as a mirroring matrix, which
          reflects points across a mirror plane. The mirror plane is defined by a point on the
          plane (planePoint) and the normal vector of the plane (planeNormal).
          The resulting matrix can be used to mirror 3D points and objects.
          */
         void initMirroring(const Vertex3& planePoint, const Vertex3& planeNormal);

         /*!
          \brief Initializes this matrix as a translation matrix.
          \param distance The distance to translate by.
          */
         void initMoving(const Vertex3& distance);

         /*!
          \brief Initializes this transformation as scaling by different factors along the x, y,
          and z axes.
          \param factors The scaling factors along the x, y, and z axes.
          */
         void initScaling(const Vertex3& factors);

         /*!
          \brief Initializes this transformation as scaling around a base point.
          \param basePoint The point around which the scaling is performed.
          \param factor The scaling factor.
          */
         void initScaling(const Vertex3& basePoint, double factor);

         /*!
          \brief Initializes this Transform as a rotation matrix around the Z-axis.
          \param angle The rotation angle in radians.
          */
         void initRotationZ(double angle);

         /*!
          \brief Initializes this Transform as a rotation matrix.
          \param axisPoint The origin vector of the rotation axis.
          \param axisDirection The normalized direction vector of the rotation axis.
          \param angle The rotation angle in radians.
          */
         void initRotation(const Vertex3& axisPoint,
                           const Vertex3& axisDirection,
                           double angle);

         /*!
          \brief Initialize this matrix as a "look-at" matrix.
          \param camera The camera position
          \param center The "target" center of the view
          \param up The up vector (needed for rotation)
          */
         void initLookAt(const jm::Vertex3& camera,
                         const jm::Vertex3& center,
                         const jm::Vertex3& up);

         /*!
          \brief This method transforms the vertex using the 4x4 transformation matrix.
          \param vertex The input vertex to be transformed.
          \return The transformed vertex.
          */
         Vertex3 trans(const Vertex3& vertex) const;

         /*!
          \brief This method transforms the number using the 4x4 transformation matrix.
          X value is used.
          \param value The input number to be transformed.
          \return The transformed number.
          */
         double trans(double value) const;

         /*!
          \brief Transform a rotation angle about the Z-Axis of LCS as usually needed by arcs or
          texts.
          \param angle Rotation angle in radians.
          \return The transformed angle.
          */
         double transAngle(double angle) const;

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

         /*!
          \brief This method returns the number of rows.
          */
         size_t rows() const;

         /*!
          \brief This method returns the number of columns.
          */
         size_t cols() const;

      private:

         /*!
          \brief Number of rows.
          */
         size_t m = 0;

         /*!
          \brief Number of columns.
          */
         size_t n = 0;

         /*!
          \brief This field stores the data. In analogy to the OpenGL storage convention, the data
          is stored column by column.
          */
         double* data = nullptr;

         void init(size_t rows, size_t cols);
   };


   /*!
    \brief Implementation of the operator M * M (matrix multiplication).
    */
   DllExport
   Matrix operator*(const Matrix& A, const Matrix& B);

   /*!
    \brief Implementation of the operator d * M (scalar multiplication).
    */
   DllExport
   Matrix operator*(const double& d, const Matrix& b);

   /*!
    \brief Implementation of the operator M * d (scalar multiplication).
    */
   DllExport
   Matrix operator*(const Matrix& A, const double& d);

   /*!
    \brief Implementation of the operator M * v (matrix multiplication with a vector). The matrix must be square.
    */
   DllExport
   Vector operator*(const Matrix& A, const Vector& b);

   /*!
    \brief Implementation of the operator M * v (matrix multiplication with a vector). The matrix must be 3x3.
    */
   DllExport
   Vertex3 operator*(const Matrix& A, const Vertex3& b);

   /*!
    \brief Implementation of the operator M / d (scalar division).
    */
   DllExport
   Matrix operator/(const Matrix& b, const double& d);

   /*!
    \brief Implementation of the operator M + M (matrix addition).
    */
   DllExport
   Matrix operator+(const Matrix& A, const Matrix& B);

   /*!
    \brief Implementation of the operator M - M (matrix subtraction).
    */
   DllExport
   Matrix operator-(const Matrix& A, const Matrix& B);

}
#endif
