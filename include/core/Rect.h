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
      //! Constructor creates rectangle <0,0,0,0>
      Rect();

      //! Constructor creates rectangle <rx,ry,rwidth,rheight
      //! \param rx X-Component of the top left corner of the rect.
      //! \param ry Y-Component of the top left corner of the rect.
      //! \param rwidth Width of the rectangle (which is parallel to X-Axis)
      //! \param rheight Height of the rectangle (which is parallel to Y-Axis)
      Rect(double rx, double ry, double rwidth, double rheight);

      Rect(Point origin, Size size);

      Rect(double x, double y, const Size &size);

      //Rect(const Rect &r);

      //! X-Component of top left corner
      double x() const;

      //! Y-Component of top left corner
      double y() const;

      //! Width of the rectangle (along x-axis)
      double width() const;

      //! Height of the rectangle (along y-axis)
      double height() const;

      //! Returns the size of the rectangle.
      Size size() const;

      //! Returns the position of the rectangle, which is the bottom left corner.
      Point origin() const;

      /*!
       /brief Returns the x-coordinate of the left edge of the rectangle.
       */
      double left() const;

      /*!
       /brief Returns the x-coordinate of the right edge of the rectangle.
       */
      double right() const;

      /*!
       /brief Returns the y-coordinate of the top edge of the rectangle.
       */
      double top() const;

      /*!
       /brief Returns the y-coordinate of the bottom edge of the rectangle.
       */
      double bottom() const;

      /*! \brief Gibt den Mittelpunkt des Rechtecks zurück */
      Point center() const;

      /*! \brief Gibt den oberen linken Punnkt zurück */
      Point topLeft() const;

      /*! \brief Gibt den oberen rechten Punnkt zurück */
      Point topRight() const;

      /*! \brief Gibt den unteren linken Punnkt zurück */
      Point bottomLeft() const;

      /*! \brief Gibt den unteren rechten Punnkt zurück */
      Point bottomRight() const;

      Point topCenter() const;

      Point bottomCenter() const;

      Point leftCenter() const;

      Point rightCenter() const;

      void setX(double x);

      void setY(double y);

      void setWidth(double width);

      void setHeight(double height);

      //! Set the size of the rectangle
      //! \param sz The new size.
      void setSize(const Size &sz);

      //! Set the size of the rectangle
      //! \param width The new width of the rectangle.
      //! \param height The new height of the rectangle.
      void setSize(double width, double height);

      //! Set the position of the rectangle
      //! \param pt The new position of the bottom left corner.
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
      // Verschieben und Ausrichten
      //

      /*! \brief Verschiebt das Rechteck horizontal */
      void moveHorizontal(double deltaX);

      /*! \brief Verschiebt das Rechteck vertikal */
      void moveVertical(double deltaY);

      /*! \brief Verschiebt das Rechteck */
      void move(const jm::Point &delta);

      /*! \brief Die linke obere Ecke dieses und des anderen \c Rects werden übereinander gelegt. */
      void alignTopLeft(const Rect &rect);

      /*! \brief Die linke untere Ecke dieses und des anderen \c Rects werden übereinander gelegt. */
      void alignBottomLeft(const Rect &rect);

      //
      // Kanten verschieben ( Und Größe ändern)
      //

      /*! \brief Obere Kante relativ verschieben (und Größe ändern) */
      void shiftTop(double deltaTop);

      /*! \brief Linke Kante relativ verschieben (und Größe ändern) */
      void shiftLeft(double deltaLeft);

      /*! \brief Rechte Kante relativ verschieben (und Größe ändern) */
      void shiftRight(double deltaRight);

      /*! \brief Untere Kante relativ verschieben (und Größe ändern) */
      void shiftBottom(double deltaBottom);

      //
      // Besondere Methoden
      //

      /*! \brief Vergrößert dieses Rechteck auf ein Gemeinsames Rechteck mit dem anderen.  */
      void unionWith(const Rect &rect);

      //! Normalizing means, that a rectangle with negative width or height value becomes  positive
      //! with and height values and the position is corrected in that way, that the outline of the
      //! rect remains on the same position and size.
      void normalize();

		/*! \brief Ist das Rechteck leer? (Größe =0) */
		bool isEmpty() const;

      /*!
       \brief Change this rect to the intersection area of this rectangle with the other rect.
       */
      void intersect(const Rect& other);

		/*! \brief Gibt das Rechteck zurück, welches die Schnittmenge auf beiden Rechtecken bildet */
		Rect intersection(const Rect &rect) const;

      //! Returns true, if the point <px,py> is within this rectangle. False otherwise.
      //! \param px X-Component of the point.
      //! \param py Y-Component of the point.
      bool contains(double px, double py) const
      {
         return (px >= mOrigin.x() &&
                 px <= mOrigin.x() + mSize.width() &&
                 py >= mOrigin.y() &&
                 py <= mOrigin.y() + mSize.height());
      }

      //! Returns true, if the point pt is within this rectangle. False otherwise.
      //! \param pt The point.
      bool contains(const Point &pt) const
      {
         return contains(pt.x(), pt.y());
      }

      //! Returns true, if the point pt is within this rectangle. False otherwise.
      //! \param pt The point.
      bool contains(const Vertex2 &pt) const
      {
         return contains(pt.x,pt.y);
      }

      //! Returns true, if the rectangle rect intersects this rectangle. False otherwise.
      //! \param rect The rectangle
      inline bool intersects(const Rect &rect) const
      {
         return (mOrigin.x()        <= rect.x() + rect.mSize.width() &&
                 mOrigin.x() + mSize.width()  >= rect.x() &&
                 mOrigin.y()        <= rect.y() + rect.mSize.height() &&
                 mOrigin.y() + mSize.height() >= rect.y());
      }

      private:

        Point mOrigin;
        Size mSize;
   };

};

#endif
