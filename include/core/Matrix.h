////////////////////////////////////////////////////////////////////////////////////////////////////
// Name:        Matrix.h
// Library:     VertexFusion Library
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
	enum MatrixNorm
	{
		kMatrixNorm1,//!< Column Sum Norm
		kMatrixNormInf//!< Row Sum Norm
	};

	/*!
	 \brief An m x n-dimensional matrix.
	 \ingroup core
	 */
	struct DllExport Matrix
	{
			DllExport
			friend const Matrix operator*(const Matrix &A, const Matrix &B);

			DllExport
			friend const Matrix operator*(const double &d, const Matrix &b);

			DllExport
			friend const Vertex3 operator*(const Matrix &A, const Vertex3 &b);

			DllExport
			friend const Matrix operator+(const Matrix &A, const Matrix &B);

			DllExport
			friend const Matrix operator-(const Matrix &A, const Matrix &B);

			DllExport
			friend const Matrix operator/(const Matrix &A, const double &d);

		public:

			/*!
			 \brief Number of rows.
			 */
			uint32 m;

			/*!
			 \brief Number of columms.
			 */
			uint32 n;

			/*!
			 \brief This constructor creates a matrix and initializes it with zeros.
			 \param rows Number of rows.
			 \param cols Number of columns.
			 */
			Matrix(uint32 rows, uint32 cols);

			/*!
			 \brief Special constructor for a 3x3 matrix.
			 \param c1 The 1st column of the matrix
			 \param c2 The 2nd column of the matrix
			 \param c3 The 3rd column of the matrix
			 \param rowwise if \c true, then the matrix is filled row by row otherwise column by
			 column.
			 */
			Matrix(const Vertex3 &c1,
					 const Vertex3 &c2,
					 const Vertex3 &c3,
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
			Matrix(const Matrix &other);

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
			void Set(uint32 row, uint32 col, double value);

			/*!
			 \brief Adds to the value of a cell the passed value.
			 \param row The 0-based index of the row.
			 \param col The 0-based index of the column.
			 \param value The value to be added to the cell.
			 */
			void Add(uint32 row, uint32 col, double value);

			/*!
			 \brief Returns the value of a cell.
			 \param row The 0-based index of the row.
			 \param col The 0-based index of the column.
			 */
			double Get(uint32 row, uint32 col) const;

			/*!
			 \brief This method fills all elements of the matrix with 0.
			 */
			void Zeros();

			/*!
			 \brief This method transposes the matrix,
			 */
			void Transpose();

			/*!
			 \brief This method inserts the contents of the other matrix into this matrix. Upper left
			 element is 0,0
			 */
			void Insert(const Matrix &A);

			/*!
			\brief This method inserts the contents of the Other matrix into this matrix. Upper left
			 element is r,c
			*/
			void Insert(const Matrix &A, uint32 r, uint32 c);

			/*!
			 \brief This method sets all values on the diagonal elements to the desired value.
			 */
			void Diag(double value);

			/*!
			 \brief Calculates the determinant of a matrix.
			 
			 This method is currently limited to a maximum of 4x4 matrices.
			 */
			VxfErrorStatus Det(double &det) const;

			/*!
			 \brief Inverts this matrix.
			 
			 This method is currently limited to a maximum of 4x4 matrices.
			 */
			VxfErrorStatus Inverse();

			/*!
			 \brief This method returns the reference to the data array.
			 
			 Only needed for efficient access for OpenGL.
			 */
			const double* GetRef() const;

			/*!
			 \brief This method calculates the condition of the matrix according to the corresponding
			 matrix norm.
			 */
			double Norm(MatrixNorm norm) const;
		
			/*!
			 \brief Returns the sum of the diagonal elements.
			 */
			double Trace() const;
		
			/*!
			 \brief Returns the Eigen Values of the matrix.
			 
			 Currentrly this is restricted to matrices of maximum 3x3.
			 */
			Vector Eigen() const;

			/*!
			 \brief Prints the content of the matrix on \c std::cout
			 */
			void Print() const;

			/*!
			 \brief This method calculates the number of elements that are not 0.0.
			 Currently this is done without EPS.
			 */
			uint32 CountNonZeroElements() const;

			/*!
			 \brief This static function generates a 3x3 rotation matrix
			 \param angle Angle of rotation in radians
			 \param axis Rotation axis (must be normalized)
			 */
			static Matrix Generate3x3RotationMatrix(double angle, const Vertex3 &axis);

			/*!
			 \brief This static function generates a 3x3 rotation matrix for a rotation around the
			 X-axis.
			 \param angle Angle of rotation in radians
			 */
			static Matrix Generate3x3RotationXMatrix(double angle);

			/*!
			 \brief This static function generates a 3x3 rotation matrix for a rotation around the
			 Y-axis.
			 \param angle Angle of rotation in radians
			 */
			static Matrix Generate3x3RotationYMatrix(double angle);

			/*!
			 \brief This static function generates a 3x3 rotation matrix for a rotation around the
			 Z-axis.
			 \param angle Angle of rotation in radians
			 */
			static Matrix Generate3x3RotationZMatrix(double angle);

			Matrix &operator=(const Matrix &A);

		private:

			/*!
			 \brief This field stores the data. In analogy to the OpenGL storage convention, the data
			 is stored column by column.
			 */
			double* data;
	};


	/*!
	 \brief Implementierung des Operators M * M (Matrixmultiplikation)
	 */
	DllExport
	const Matrix operator*(const Matrix &A, const Matrix &B);


	/*!
	 \brief Implementierung des Operators d * M (Skalare multiplikation)
	 */
	DllExport
	const Matrix operator*(const double &d, const Matrix &b);

	/*!
	 \brief Implementierung des Operators M * d (Skalare multiplikation)
	 */
	DllExport
	const Matrix operator*(const Matrix &b, const double &d);

	/*!
	 \brief Implementierung des Operators M * v (Maktrixmultiplikation mit einem Vektor) Die Matrix muss Quadratisch sein...
	 */
	DllExport
	const Vector operator*(const Matrix& A, const Vector& b);

	/*!
	 \brief Implementierung des Operators M * v (Maktrixmultiplikation mit einem Vektor) Die Matrix muss 3x3 sein...
	 */
	DllExport
	const Vertex3 operator*(const Matrix &A, const Vertex3 &b);

	/*!
	 \brief Implementierung des Operators M / d (Skalare Division)
	 */
	DllExport
	const Matrix operator/(const Matrix &b, const double &d);

	/*!
	 \brief Implementierung des Operators M + M
	 */
	DllExport
	const Matrix operator+(const Matrix &A, const Matrix &B);

	/*!
	 \brief Implementierung des Operators M - M
	 */
	DllExport
	const Matrix operator-(const Matrix &A, const Matrix &B);

}
#endif
