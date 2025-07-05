////////////////////////////////////////////////////////////////////////////////////////////////////
// Name:        Integer.h
// Library:     Jameo Core Library
// Purpose:     Integer class
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

#ifndef jm_Integer_h
#define jm_Integer_h

#include "String.h"

namespace jm
{

   /*!
    \brief This class collect static methods to manipulate integer values
    \ingroup core
    */
   class DllExport Integer
   {
      public:

         /*!
          \brief Returns the number of digits, this number has.
          \return return 1 for a number between 0 and 9, 2 for a number between 10 and 99 and so on...
          If the number is negative, the sign is also counted.
          */
         static uint8 digits(int64 number);

         /*!
          \brief Method converts a hexadecimal string value into an integer number.
          \param str A character string that represents a hexadecimal coded number. E.g. "FF" for 255.
          \return Returns the desired number as an integer value.
          */
         static int64 fromHex(const jm::String& str);

         /*!
          \brief Method converts a hexadecimal string value into an integer number.
          \param str A character string that represents a hexadecimal coded number. E.g. "FF" for 255.
          \param begin start index of hex string
          \param size Size of hex string
          \return Returns the desired number as an integer value.
          */
         static int64 fromHex(const jm::String& str, size_t begin, size_t size);

         /*!
          \brief Converts an integer number to a hexadecimal string value.
          \return Returns the desired number as a string, which is a hexadecimal representation.
          For example, "FF" for 255.
          */
         static jm::String toHexString(int64 number);

         /*!
          \brief Converts an integer number to a string representation of a Roman numeral.
          \return The desired number as a string with the value of a Roman numeral.
          */
         static jm::String toRomanString(int64 number);

         /*!
          \brief Converts an integer number to a string representation of a capital letter.
          \return The desired number as a string with the value of a capital letter.
          */
         static jm::String toLatinAlphabetString(int64 number);

   };

}

#endif
