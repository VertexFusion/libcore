////////////////////////////////////////////////////////////////////////////////////////////////////
// Name:        Vertex2.h
// Library:     Jameo Core Library
// Purpose:     Vector
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

#ifndef jm_Vector_h
#define jm_Vector_h

#include "Types.h"

namespace jm
{

   /*!
    \brief An n-dimensional vector.
    \ingroup core
    */
   struct DllExport Vector
   {
      /*!
       \brief This variable stores the number of rows in the vector.
       */
      Integer m;

      /*!
       \brief This field stores the data of the vector. The length must always be m.
       */
      double* data;

      /*!
       \brief Constructor creates empty vector (m=0)
       */
      Vector();

      /*!
       \brief Copy constructor
       */
      Vector(const Vector &another);

      /*!
       \brief Constructor creates an n-dimensional vector.
       \param rows Number of rows (dimensions) in the vector.
       */
      Vector(Integer rows);

      /*!
       \brief Destructor
       */
      ~Vector();

      /*!
       \brief This method returns the absolute value of the vector.
       */
      double Abs() const;

      /*!
       \brief This method normalises the vector. The length of the vector is set to 1. The direction
       remains the same.
       */
      void Normalize();

      /*!
       \brief This method zeroes all entries of the vector.
       */
      void Zeros();

      /*!
       \brief This method sets all entries of the vector to 1.0.
       */
      void Ones();

      /*!
       \brief Returns the scalar product of one vector with another.

       <ul><li>If the scalar product is 0, then two vectors are perpendicular to each other.</li>
       <li>If the scalar conduct > 0, then the included angle is acute.</li>
       <li>If the scalar conduct < 0, then the included angle is obtuse.</li>
       <li>For normalised vectors, the scalar product corresponds to the projection of one vector
       onto the other.</li>
       </ul>
       \param another The vector with which the scalar product "this × other" is formed.
       */
      double DotProduct(const Vector &another) const;

      Vector& operator=(const Vector &another);

      DllExport
      friend std::ostream &operator<< (std::ostream &out, const Vector &str);

   };

   /*!
    \brief Implementation of the operator +
    */
   DllExport
   const Vector operator+(const Vector &v1, const Vector &v2);

   /*!
    \brief Implementation of the operator -
    */
   DllExport
   const Vector operator-(const Vector &v1, const Vector &v2);

   /*!
    \brief Implementation of the operator *
    */
   DllExport
   const Vector operator*(const double &d, const Vector &v);

}

#endif
