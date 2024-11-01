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

#ifndef jm_Size_h
#define jm_Size_h

#include "Types.h"
#include "Point.h"

namespace jm
{

  /*!
    \brief Defines a size.
    */
   struct DllExport Size
   {
      //! Constructor creates size <0,0>
      Size();

      //! Constructor creates size <width,height>
      Size(double width, double height);

      Size(const Point &pt);

      //! Returns the width
      double width() const;

      //! Returns the height
      double height() const;

      //! Returns reference to the width
      double& rWidth();

      //! Returns reference to the height
      double& rHeight();

      //Set the with
      void setWidth(double width);

      //Set the height
      void setHeight(double height);

      //! Returns the component-wise minimum of this size and the other size.
      Size cWiseMin(const Size &other) const;

      //! Returns the component-wise maximum of this size and the other size.
      Size cWiseMax(const Size &other) const;

	  bool operator==(const Size &other) const;
	  bool operator!=(const Size &other) const;

      private:

      //! Width
      double mWidth;

      //! Height
      double mHeight;

      DllExport
      friend const Size operator-(const Size& v1, const Size& v2);

      DllExport
	   friend const Size operator*(const double& d, const Size& v);
   };

};

#endif
