////////////////////////////////////////////////////////////////////////////////////////////////////
// Name:        Vertex2.h
// Library:     Jameo Core Library
// Purpose:     2D-Vector
//
// Author:      Uwe Runtemund (2013-today)
// Modified by:
// Created:     16.01.2013
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

#ifndef jm_Vertex2_h
#define jm_Vertex2_h

#include "Types.h"

namespace jm
{
   class Vertex3;

   /*!
    \brief A two dimensional vector. Owns special functions for 2d space.
    */
   class DllExport Vertex2
   {
      public:

         /*!
          \brief X component of vector.
          \note We need fast access to this value and other protection measures are not necessary.
          So we leave it public.
          */
         double x=0.0;

         /*!
          \brief Y component of vector.
        	 \note We need fast access to this value and other protection measures are not necessary.
        	 So we leave it public.
          */
         double y=0.0;


         /*!
          \brief Constructor creates null vector.
          */
         Vertex2();

         /*!
          \brief Constructor creates arbitrary vector
          \param x X-component of the vector
          \param y y-component of the vector
          */
         Vertex2(double x, double y);

         Vertex2(const Vertex3& v3);

         /*!
          \brief This method returns the absolute value of the vector. The absolute value is equal to the length.
          */
         double abs() const;

         /*!
          \brief This method normalizes the vector. A normalized vector has the length 1.
          \note If this vector has the length (nearly) 0, it is returned unchanged.
          */
         Vertex2& normalize();

         /*!
          \brief This method returns a normalized vector with the length 1.
          \note If this vector has the length (nearly) 0, it is returned unchanged.
          */
         Vertex2 normalized()const;

         /*!
          \brief Returns the cross product of this vector multiplied by another.
          \param another the other vector.
          \return Returns the result of: this × another
          */
         double crossProduct(const Vertex2& another) const;

         /*!
          \brief Returns the scalar product of this vector with another
          \param another the other vector.
          \return Returns the result of: this dot another
          */
         double dotProduct(const Vertex2& another) const;

         /*!
          \brief This method calculates whether the two vectors are collinear.
          In other words, whether both vectors are parallel.
          */
         bool isCollinear(const Vertex2& another) const;

         /*!
          \brief This method calculates whether the two vectors are orthogonal.
          In other words, whether they are perpendicular to each other.
          */
         bool isOrthogonal(const Vertex2& another) const;

         /*!
          \brief Returns the signed angle between this vector and another vector.
          \note This method uses as positive direction the clockwise direction with right
          x-axis as 0° like in SVG.
          \param another The vector we want to know the angle to.
          \return Angle in radians.
          */
         double angleTo(const Vertex2& another) const;

         /*!
          \brief This method calculates whether this vector is "to the right", i.e. clockwise next to the other vector.
          */
         bool isRightTo(const Vertex2& another) const;

         /*!
          \brief This method calculates whether this vector is "left", i.e. counterclockwise, next to the other vector
          */
         bool isLeftTo(const Vertex2& another) const;

         /*!
          \brief This method returns true if the vector is defined, i.e. if the numbers are not
          NAN "Not-a-number".
          */
         bool isValid() const;

         /*!
          \brief This method rotates the vector around the Z-axis with the specified angle.
          \param angle The angle of rotation in the mathematical positive sense in radians.
          */
         Vertex2& rotate(double angle);

         /*!
          \brief This method multiplies this vector line by line with the other vector.
          \return Returns the result of the calculation. This vector remains unchanged.
          */
         Vertex2 scale(const Vertex2& another) const;

         Vertex2& operator+=(const Vertex2& another);

         Vertex2& operator-=(const Vertex2& another);

         /*!
          \brief Implementation of the operator *
          */
         Vertex2 operator*(double b) const;

         /*!
          \brief Implementation of the operator /
          */
         Vertex2 operator/(double b) const;

         DllExport
         friend std::ostream& operator<< (std::ostream& out, const Vertex2& vertex);
   };


   /*!
    \brief Implementation of the operator +
    */
   DllExport
   const Vertex2 operator+(const Vertex2& v1, const Vertex2& v2);

   /*!
    \brief Implementation of the operator -
    */
   DllExport
   const Vertex2 operator-(const Vertex2& v1, const Vertex2& v2);

   /*!
    \brief Implementation of the operator *
    */
   DllExport
   const Vertex2 operator*(const double& d, const Vertex2& v);

   /*!
    \brief Implementation of the operator *
    */
   DllExport
   const Vertex2 operator*(const Integer& i, const Vertex2& v);

   /*!
    \brief Implementation of the operator -=
    */
   DllExport
   bool operator!=(Vertex2 const& v1, Vertex2 const& v2);

   /*!
    \brief This method solves a linear system of equations with two unknowns:
     r.x = x * a.x + y * b.x
     r.y = x * a.y + y * b.y
     The system is solved for x and y.
     Matrix notation:
   	  a   b                 r
   	| a.x b.x | * | x | = | r.x |
   	| a.y b.y |   | y |   | r.y |
    */
   DllExport
   Vertex2 SolveLinearSystem(Vertex2 a, Vertex2 b, Vertex2 r);
}

#endif
