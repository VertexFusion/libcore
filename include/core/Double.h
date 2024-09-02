////////////////////////////////////////////////////////////////////////////////////////////////////
// Name:        Integer.h
// Library:     Jameo Core Library
// Purpose:     Double class
//
// Author:      Uwe Runtemund (2013-today)
// Modified by:
// Created:     06.09.2013
//
// Copyright:   (c) 2013 Jameo Software, Germany. https://jameo.de
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

#ifndef jm_Double_h
#define jm_Double_h


class DllExport Double
{
   public:

    static double valueOf(const jm::String& string);

      /*!
       \brief  This function rounds a number to the nearest integer.
       \return Nearest integer.
       */
      static int64 round(double number);

      /*!
       \brief  This function rounds a number to the desired number of decimal places.
       \note Due to machine precision, the exact value may not always be achieved.
       \param digits Number of decimal places to round to.
       \return Rounded number.
       */
      static double roundFrac(double number, int64 digits);

};



#endif
