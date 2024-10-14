////////////////////////////////////////////////////////////////////////////////////////////////////
// Name:        Size.h
// Library:     Jameo Core Library
// Purpose:     Declaration of Object class
//
// Author:      Uwe Runtemund (2014-today)
// Modified by:
// Created:     10.10.2024
//
// Copyright:   (c) 2024 Jameo Software, Germany. https://jameo.de
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

#ifndef jm_Point_h
#define jm_Point_h

#include "Types.h"

namespace jm
{

   /*!
    \brief Defines a point. This point is used for 2D-Coordinates. 

    In opposite to Vertex2 this class has no vector operations. It is only used for 2D-Coordinates.
    Typically used in combination with Rect.
    */
   class DllExport Point
   {
      public:
         /*! 
         \brief Constructor. Creates point <0,0>.
         */
         Point();

         /*! 
         \brief Constructor. Creates point <x,y>.
         \param x X-Component of the point.
         \param y Y-Component of the point.
         */
         Point(double x, double y);

         Point(const Vertex2 &v){mX=v.x;mY=v.y;};

         /*! 
         \brief Returns the x-component of the point.
         */
         double x() const;

         /*!
         \brief Returns the y-component of the point.
         */
         double y() const;

         //! Returns reference to the x-component
         double& rX();

         //! Returns reference to the y-component
         double& rY();

         //Set the Y-component
         void setX(double x);

         //Set the x-component
         void setY(double y);

         /*!
         \brief Returns the component-wise minimum of this point and the other point.
         \param other The other point.
         */
         Point cWiseMin(const Point &other) const;

         /*!
         \brief Returns the component-wise maximum of this point and the other point.
         \param other The other point.
         */
         Point cWiseMax(const Point &other) const;

         inline jm::Vertex2 toVertex2() const
         {
            return jm::Vertex2(mX, mY);
         };


         Point &operator+=(const Point &another);

         Point &operator-=(const Point &another);

         DllExport
         friend const Point operator+(const Point& v1, const Point& v2);

         DllExport
         friend const Point operator-(const Point& v1, const Point& v2);

         DllExport
         friend const Point operator*(const double &d, const Point &v2);

      private:

         //! X-Position
         double mX;

         //! Y-Position
         double mY;
   };

};

#endif
