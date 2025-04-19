////////////////////////////////////////////////////////////////////////////////////////////////////
// Name:        Rect.cpp
// Library:     Jameo Core Library
// Purpose:     Point
//
// Author:      Uwe Runtemund (2024-today)
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

#include "PrecompiledCore.hpp"

jm::Rect::Rect()
{
   mOrigin = Point();
   mSize = Size();
}

jm::Rect::Rect(double rx, double ry, double rwidth, double rheight)
{
   mOrigin = Point(rx, ry);
   mSize = Size(rwidth, rheight);
}

jm::Rect::Rect(Point origin, Size size)
{
   mOrigin = origin;
   mSize = size;
}

jm::Rect::Rect(double rx, double ry, const Size& size)
{
   mOrigin = Point(rx, ry);
   mSize = size;
}

double jm::Rect::x() const
{
   return mOrigin.x();
}

double jm::Rect::y() const
{
   return mOrigin.y();
}

double jm::Rect::height() const
{
   return mSize.height();
}

double jm::Rect::width() const
{
   return mSize.width();
}

jm::Size jm::Rect::size() const
{
   return mSize;
}

jm::Point jm::Rect::origin() const
{
   return mOrigin;
}

double jm::Rect::left() const
{
   return mOrigin.x();
}

double jm::Rect::right() const
{
   return mOrigin.x() + mSize.width();
}

double jm::Rect::top() const
{
   return mOrigin.y();
}

double jm::Rect::bottom() const
{
   return mOrigin.y() + mSize.height();
}

jm::Point jm::Rect::center() const
{
   return jm::Point(mOrigin.x() + 0.5 * mSize.width(),
                    mOrigin.y() + 0.5 * mSize.height());
}

jm::Point jm::Rect::topLeft() const
{
   return mOrigin;
}

jm::Point jm::Rect::topRight() const
{
   return jm::Point(mOrigin.x() + mSize.width(),
                    mOrigin.y());
}

jm::Point jm::Rect::bottomLeft() const
{
   return jm::Point(mOrigin.x(),
                    mOrigin.y() + mSize.height());
}

jm::Point jm::Rect::bottomRight() const
{
   return jm::Point(mOrigin.x() + mSize.width(),
                    mOrigin.y() + mSize.height());
}

jm::Point jm::Rect::topCenter() const
{
   return jm::Point(mOrigin.x() + 0.5 * mSize.width(),
                    top());
}

jm::Point jm::Rect::bottomCenter() const
{
   return jm::Point(mOrigin.x() + 0.5 * mSize.width(),
                    bottom());
}

jm::Point jm::Rect::leftCenter() const
{
   return jm::Point(left(),
                    mOrigin.y() + 0.5 * mSize.height());
}

jm::Point jm::Rect::rightCenter() const
{
   return jm::Point(right(),
                    mOrigin.y() + 0.5 * mSize.height());
}

void jm::Rect::intersect(const jm::Rect& other)
{
   setLeft(std::max(left(), other.left()));
   setTop(std::max(top(), other.top()));
   mSize.setWidth(std::min(right(), other.right()) - mOrigin.x());
   mSize.setHeight(std::min(bottom(), other.bottom()) - mOrigin.y());
}

void jm::Rect::setX(double x)
{
   mOrigin.setX(x);
}

void jm::Rect::setY(double y)
{
   mOrigin.setY(y);
}

void jm::Rect::setWidth(double width)
{
   mSize.setWidth(width);
}

void jm::Rect::setHeight(double height)
{
   mSize.setHeight(height);
}

void jm::Rect::setSize(const Size& sz)
{
   mSize = sz;
}

void jm::Rect::setSize(double width, double height)
{
   mSize = Size(width, height);
}

void jm::Rect::setOrigin(const Point& pt)
{
   mOrigin = pt;
}

void jm::Rect::setOrigin(double x, double y)
{
   mOrigin = Point(x, y);
}

//
// Verschieben und Ausrichten
//


void jm::Rect::moveHorizontal(double x)
{
   mOrigin.rX() += x;
}

void jm::Rect::moveVertical(double y)
{
   mOrigin.rY() += y;
}

void jm::Rect::move(const jm::Point& delta)
{
   mOrigin += delta;
}

void jm::Rect::alignTopLeft(const jm::Rect& rect)
{
   mOrigin = rect.mOrigin;
}

void jm::Rect::alignBottomLeft(const jm::Rect& rect)
{
   mOrigin = jm::Point(rect.left(), rect.bottom() - height());
}

//
// Kanten Verschiebenn
//

void jm::Rect::shiftTop(double deltaTop)
{
   mOrigin.rY() += deltaTop;
   mSize.rHeight() -= deltaTop;
}

void jm::Rect::shiftLeft(double deltaLeft)
{
   mOrigin.rX() += deltaLeft;
   mSize.rWidth() -= deltaLeft;
}

void jm::Rect::shiftRight(double deltaRight)
{
   mSize.rWidth() += deltaRight;
}

void jm::Rect::shiftBottom(double deltaBottom)
{
   mSize.rHeight() += deltaBottom;
}

void jm::Rect::moveLeft(double delta)
{
   //TODO: DEPRECATED
   mOrigin.rX() += delta;
   mSize.rWidth() -= delta;
}

void jm::Rect::moveRight(double delta)
{
   //TODO: DEPRECATED
   mSize.rWidth() += delta;
}

void jm::Rect::moveBottom(double delta)
{
   //TODO: DEPRECATED
   mSize.rHeight() += delta;
}


//
// Kanten verschieben ( Und Größe ändern)
//

void jm::Rect::setTop(double dtop)
{
   shiftTop(dtop - top());
}

void jm::Rect::setLeft(double dleft)
{
   shiftLeft(dleft - left());
}

void jm::Rect::setRight(double dright)
{
   shiftRight(dright - right());
}

void jm::Rect::setBottom(double dbottom)
{
   shiftBottom(dbottom - bottom());
}

void jm::Rect::normalize()
{
   if(mSize.width() < 0)
   {
      mOrigin.rX() += mSize.width();
      mSize.setWidth(-mSize.width());
   }
   if(mSize.height() < 0)
   {
      mOrigin.rY() += mSize.height();
      mSize.setHeight(-mSize.height());
   }
}

bool jm::Rect::contains(double px, double py) const
{
   return (px >= mOrigin.x() &&
           px <= mOrigin.x() + mSize.width() &&
           py >= mOrigin.y() &&
           py <= mOrigin.y() + mSize.height());
}

/*!
 \brief Returns true, if the point pt is within this rectangle. False otherwise.
 \param pt The point.
 */
bool jm::Rect::contains(const Point& pt) const
{
   return contains(pt.x(), pt.y());
}

/*!
 \brief Returns true, if the point pt is within this rectangle. False otherwise.
 \param pt The point.
 */
bool jm::Rect::contains(const Vertex2& pt) const
{
   return contains(pt.x, pt.y);
}

/*!
 \brief Returns true, if the rectangle rect intersects this rectangle. False otherwise.
 \param rect The rectangle
 */
bool jm::Rect::intersects(const Rect& rect) const
{
   return (mOrigin.x()        <= rect.x() + rect.mSize.width() &&
           mOrigin.x() + mSize.width()  >= rect.x() &&
           mOrigin.y()        <= rect.y() + rect.mSize.height() &&
           mOrigin.y() + mSize.height() >= rect.y());
}


//
// Special Methods
//

void jm::Rect::unionWith(const jm::Rect& rect)
{
   if(left() > rect.left())setLeft(rect.left());
   if(top() > rect.top())setTop(rect.top());
   if(right() < rect.right())setRight(rect.right());
   if(bottom() < rect.bottom())setBottom(rect.bottom());
}

bool jm::Rect::isEmpty() const
{
   return jm::isEqual(mSize.width(), 0.0) || jm::isEqual(mSize.height(), 0.0);
}
jm::Rect jm::Rect::intersection(const jm::Rect& rect) const
{
   Rect intersection;

   if(intersects(rect))
   {
      double dleft = std::max(left(), rect.left());
      double dtop  = std::max(top(), rect.top());
      double dright = std::min(right(), rect.right());
      double dbottom = std::min(bottom(), rect.bottom());

      intersection.setOrigin(dleft, dtop);
      intersection.setSize(dright - dleft, dbottom - dtop);
   }

   return intersection;
}
