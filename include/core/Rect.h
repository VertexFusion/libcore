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

#ifndef jm_Rect_h
#define jm_Rect_h

#include "Size.h"
#include "Point.h"
#include "Vertex2.h"

namespace jm
{

   /*!
    \brief Defines a rectangle.
    */
   struct DllExport Rect
   {
         /*!
          \brief Constructor creates rectangle <0,0,0,0>
          */
         Rect();

         /*!
          \brief Constructor creates rectangle <rx,ry,rwidth,rheight
          \param rx X-Component of the top left corner of the rect.
          \param ry Y-Component of the top left corner of the rect.
          \param rwidth Width of the rectangle (which is parallel to X-Axis)
          \param rheight Height of the rectangle (which is parallel to Y-Axis)
          */
         Rect(double rx, double ry, double rwidth, double rheight);

         Rect(Point origin, Size size);

         Rect(double x, double y, const Size& size);

         //Rect(const Rect &r);

         /*!
          \brief X-Component of top left corner
          */
         double x() const;

         /*!
          \brief Y-Component of top left corner
          */
         double y() const;

         /*!
          \brief Width of the rectangle (along x-axis)
          */
         double width() const;

         /*!
          \brief Height of the rectangle (along y-axis)
          */
         double height() const;

         /*!
          \brief Returns the size of the rectangle.
          */
         Size size() const;

         /*!
          \brief Returns the position of the rectangle, which is the bottom left corner.
          */
         Point origin() const;

         /*!
          \brief Returns the x-coordinate of the left edge of the rectangle.
          */
         double left() const;

         /*!
          \brief Returns the x-coordinate of the right edge of the rectangle.
          */
         double right() const;

         /*!
          \brief Returns the y-coordinate of the top edge of the rectangle.
          */
         double top() const;

         /*!
          \brief Returns the y-coordinate of the bottom edge of the rectangle.
          */
         double bottom() const;

         /*!
          \brief Returns the center point of the rectangle
          */
         Point center() const;

         /*!
          \brief Returns the top-left point
          */
         Point topLeft() const;

         /*!
         \brief Returns the top-right point
         */
         Point topRight() const;

         /*!
          \brief Returns the bottom-left point
          */
         Point bottomLeft() const;

         /*!
          \brief Returns the bottom-left point
          */
         Point bottomRight() const;

         Point topCenter() const;

         Point bottomCenter() const;

         Point leftCenter() const;

         Point rightCenter() const;

         void setX(double x);

         void setY(double y);

         void setWidth(double width);

         void setHeight(double height);

         /*!
          \brief Set the size of the rectangle
          \param sz The new size.
          */
         void setSize(const Size& sz);

         /*!
          \brief Set the size of the rectangle
          \param width The new width of the rectangle.
          \param height The new height of the rectangle.
          */
         void setSize(double width, double height);

         /*!
          \brief Set the position of the rectangle
          \param pt The new position of the bottom left corner.
          */
         void setOrigin(const Point& pt);

         void setOrigin(double x, double y);

         void moveLeft(double delta);

         void moveRight(double delta);

         void moveBottom(double delta);

         /*!
          \brief Set the top edge absolutely (and change size of rectanlge)
          */
         void setTop(double top);

         /*!
          \brief Move the bottom edge absolutely (and change size of rectanlge)
          */
         void setBottom(double bottom);

         /*!
          \brief Move the left edge absolutely (and change size of rectanlge)
          */
         void setLeft(double left);

         /*!
            \brief Move the right edge absolutely (and change size of rectanlge)
          */
         void setRight(double right);

         //
         // Move and Align
         //

         /*!
          \brief Moves the rectangle horizontally
          */
         void moveHorizontal(double deltaX);

         /*!
          \brief Moves the rectangle vertically
          */
         void moveVertical(double deltaY);

         /*!
         \brief Moves the rectangle
         */
         void move(const jm::Point& delta);

         /*!
          \brief The top-left corner of this and the other \c Rect are aligned.
          */
         void alignTopLeft(const Rect& rect);

         /*!
          \brief The bottom-left corner of this and the other \c Rect are aligned.
          */
         void alignBottomLeft(const Rect& rect);

         //
         // Move edges (and resize)
         //

         /*!
          \brief Move the top edge relatively (and resize)
          */
         void shiftTop(double deltaTop);

         /*!
          \brief Move the left edge relatively (and resize)
          */
         void shiftLeft(double deltaLeft);

         /*!
          \brief Move the right edge relatively (and resize)
          */
         void shiftRight(double deltaRight);

         /*!
          \brief Move the bottom edge relatively (and resize)
          */
         void shiftBottom(double deltaBottom);

         //
         // Special Methods
         //

         /*!
          \brief Enlarges this rectangle to a common rectangle with the other.
          */
         void unionWith(const Rect& rect);

         /*!
          \brief Normalized the rectangle.

          Normalizing means, that a rectangle with negative width or height value becomes  positive
          with and height values and the position is corrected in that way, that the outline of the
          rect remains on the same position and size.
          */
         void normalize();

         /*!
          \brief Is the rectangle empty? (Size == 0)
          */
         bool isEmpty() const;

         /*!
          \brief Change this rect to the intersection area of this rectangle with the other rect.
          */
         void intersect(const Rect& other);

         /*!
          \brief Returns the rectangle that is the intersection of both rectangles
          */
         Rect intersection(const Rect& rect) const;

         /*!
          \brief Returns true, if the point <px,py> is within this rectangle. False otherwise.
          \param px X-Component of the point.
          \param py Y-Component of the point.
          */
         bool contains(double px, double py) const;

         /*!
          \brief Returns true, if the point pt is within this rectangle. False otherwise.
          \param pt The point.
          */
         bool contains(const Point& pt) const;

         /*!
          \brief Returns true, if the point pt is within this rectangle. False otherwise.
          \param pt The point.
          */
         bool contains(const Vertex2& pt) const;

         /*!
          \brief Returns true, if the rectangle rect intersects this rectangle. False otherwise.
          \param rect The rectangle
          */
         bool intersects(const Rect& rect) const;

      private:

         Point mOrigin;
         Size mSize;
   };

};

#endif
