////////////////////////////////////////////////////////////////////////////////////////////////////
// Name:        Vertex3.h
// Library:     Jameo Core Library
// Purpose:     3D-Vector
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

#ifndef jm_Vertex3_h
#define jm_Vertex3_h

#include "Types.h"
#include "Vertex2.h"

namespace jm
{

   /*!
    \brief A three dimensional vector. Owns special functions for 3D space.
    */
   class DllExport Vertex3
   {
      public:

         /*!
          \brief X component of vector.
          \note We need fast acces to this value and other protection measures are not necessary.
          So we leave it public.
          */
         double x;

         /*!
          \brief Y component of vector.
          \note We need fast acces to this value and other protection measures are not necessary.
          So we leave it public.
          */
         double y;

         /*!
          \brief Z component of vector.
          \note We need fast acces to this value and other protection measures are not necessary.
          So we leave it public.
          */
         double z;

         /*!
          \brief Constructor for arbitrary vector.
          \param x X component of vector
          \param y Y component of vector
          \param z Z component of vector
          */
         Vertex3(double x = 0, double y = 0, double z = 0);

         /*!
          \brief Constructor for arbitrary vector.
          \param xy 2D Vector with x and y component.
          \param z Z component of vector
          */
         Vertex3(const Vertex2 xy, double z = 0);

         /*!
          \brief Copy constructor
          \param another The other vector
          */
         Vertex3(const Vertex3& another);

         /*!
         \brief Calculates the cross-product of this vector with the other.
         \param another The other vector.
         \return The result of "this x another".
         */
         Vertex3 crossProduct(const Vertex3& another) const;

         /*!
          \brief Gibt das Skalarprodukt eines Vektors mit einem anderen zurück.
          - Wenn das Skalarprodukt 0 ist, dann stehen zwei Vektoren senkrecht aufeinander.
          - Wenn das Skalarporduct > 0 ist, dann ist der eingeschlossene Winkel spitz
          - Wenn das Skalarporduct < 0 ist, dann ist der eingeschlossene Winkel stumpf
          - Bei normierten Vektoren entspricht das Skalarprodukt der Projektion eines Vektoren auf
            den anderen.
          \param another The other vector.
          \return The result of "this * other".
          */
         double DotProduct(const Vertex3& another) const;

         /*!
          \brief Diese Methode berechnet, ob die beiden Vektoren kollinear sind.
            Also ob beide Vektoren parallel sind.
          */
         bool IsCollinear(const Vertex3& another) const;

         /*!
          \brief Diese Methode berechnet, ob die beiden Vektoren orthogonal sind.
          Also ob sie senktrecht aufeinander stehen
          */
         bool IsOrthogonal(const Vertex3& another) const;

         /*!
          \brief Diese Methode prüft, ob der Vektor der Nullvektor ist (unter Berücksichtigung von
          RESABS)
          */
         bool IsNull() const;

         /*!
          \brief Diese Methode prüft, ob der Vektor einen "NaN"-Eintrag hat. Wenn alle Einträge
          definiert sind, wird wahr zurückgegeben.
          */
         bool IsValid() const;

         /*!
          \brief Returns the angle between this vector and another vector.
          \param another The vector we want to know the angle to.
          \return Angle in radians.
          */
         double angleTo(const Vertex3& another) const;

         /*!
          \brief This method returns the absolute value of the vector. The absolute value is equal to the length.
          */
         double abs() const;

         /*!
          \brief Diese Methode rotiert den Vektor um die X-Achse um den angegebenen Winkel.
          \param angle Der Rotationswinkel. Der Winkel wird im Bogenmaß angegeben
          */
         void RotateX(double angle);

         /*!
          \brief Diese Methode rotiert den Vektor um die Y-Achse um den angegebenen Winkel.
          \param angle Der Rotationswinkel. Der Winkel wird im Bogenmaß angegeben
          */
         void RotateY(double angle);

         /*!
          \brief Diese Methode rotiert den Vektor um die Z-Achse um den angegebenen Winkel.
          \param angle Der Rotationswinkel. Der Winkel wird im Bogenmaß angegeben
          */
         void RotateZ(double angle);

         /*!
          \brief Diese Methode rotiert den Vektor um die gegebene um den angegebenen Winkel.
          \param angle Der Rotationswinkel. Der Winkel wird im Bogenmaß angegeben
          \param axis Die Rotationsachse
          */
         void Rotate(double angle, const Vertex3& axis);

         /*!
          \brief  This method normalises the vector. A normalised vector has a length of 1 and the
          reference to this vector is returned.
          \note If this vector has the length (nearly) 0, it is returned unchanged.
          */
         Vertex3& normalize();

         /*!
          \brief This method returns a normalised vector. A normalised vector has a length of 1.
          This vector is not changed in the process.
          \note If this vector has the length (nearly) 0, it is returned unchanged.
         */
         Vertex3 normalized() const;

         /*!
          \brief This method multiplies this vector line by line with the other vector.
          \return Returns the result of the calculation. This vector remains unchanged.
          */
         Vertex3 scale(const Vertex3& another) const;

         /*!
          \brief This method returns the largest component of x,y,z from this vector.
          */
         double biggest() const;

         /*!
          \brief Implementation of the operator +=
          */
         Vertex3& operator+=(const Vertex3& v);

         /*!
          \brief Implementation of the operator -=
          */
         Vertex3& operator-=(const Vertex3& v);

         /*!
          \brief Implementation of the operator *
          */
         Vertex3 operator*(double b) const;

         /*!
          \brief Implementation of the operator /
          */
         Vertex3 operator/(double b) const;

         /*!
          \brief Implementation of the operator +
          */
         Vertex3 operator+(const Vertex3& v1) const;

         /*!
          \brief Implementation of the operator -
          */
         Vertex3 operator-(const Vertex3& v1) const;

         /*!
         \brief Implementation of the operator ==
         */
         DllExport
         friend const Vertex3 operator*(const double& d, const Vertex3& b);

         /*!
         \brief Implementation of the operator ==
         */
         DllExport
         friend std::ostream& operator<< (std::ostream& out, const Vertex3& vertex);

         /*!
         \brief Implementation of the operator ==
         */
         DllExport
         friend String& operator<< (String& out, const Vertex3& vertex);

         Vertex3& operator=(const Vertex3& another);

   };

   /*!
    \brief This method checks whether the three vectors are linearly independent.
    The vectors are linearly independent if the determinant of a 3x3 matrix in which the 3
    vectors are the columns, is not equal to 0.
    \return true if the vectors are linearly independent.
    */
   DllExport
   bool isLinearIndependent(const Vertex3& v1, const Vertex3& v2, const Vertex3& v3);


   /*!
    \brief Implementation of the operator ==
    */
   DllExport
   bool operator==(Vertex3 const& v1, Vertex3 const& v2);

   /*!
    \brief Implementation of the operator !=
    */
   DllExport
   bool operator!=(Vertex3 const& v1, Vertex3 const& v2);


   /*!
    \brief A class to calculate the bounding box of points
    */
   class DllExport Extents
   {
      public:

         /*!
          \brief Constructor.
          */
         Extents();

         /*!
          \brief Expand the box to also enclose the point pt.
          */
         void add(const Vertex2& pt);

         /*!
         	\brief Expand the box to also enclose the point pt.
         	*/
         void add(const Vertex3& pt);

         /*!
          \brief Expand the box to also enclode the box ext.
          If the other box is invalid (no point was added), then it will be ignored.
          */
         void add(const Extents& ext);

         const Vertex3& minPoint()const;
         const Vertex3& maxPoint()const;

         Vertex3 delta()const;

         /*!
          \brief Returns true, if the Extent has collected at minimum 1 point.
          */
         bool isValid()const;

      private:

         Vertex3 mPtMin;

         Vertex3 mPtMax;
   };

}

#endif
