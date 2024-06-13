////////////////////////////////////////////////////////////////////////////////////////////////////
// Name:        CharArray.h
// Library:     Jameo Core Library
// Purpose:     Handling arrays of characters
//
// Author:      Uwe Runtemund (2013-today)
// Modified by:
// Created:     18.01.2013
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

#ifndef jm_CharArray_h
#define jm_CharArray_h

#include "Types.h"
#include "Integer.h"

namespace jm
{
   /*!
    \brief This datatype presents a 16 bit unicode character.
    */
   class DllExport Char
   {
      public:

      Char(){mChar=0;};

     /* explicit */ Char(uint16 character){mChar=character;};

      uint16 Unicode() const {return mChar;};

      //! \brief Returns the character as lower case (if possible).
      Char ToLowerCase() const;

      //! \brief Returns the character as upper case (if possible).
      Char ToUpperCase() const;

      //! \brief Returns true, if the character is a white space
      bool IsWhitespace() const;

      //! \brief Returns true, if the character is a digit (0-9)
      bool IsDigit() const;

      //! \brief Returns true, if the character is a letter
      bool IsLetter() const;

      //! \brief Returns true, if the character is upper case
      bool IsUpperCase() const;

      //! \brief Returns true, if the character is lower case
      bool IsLowerCase() const;

      //! \brief Returns the digit value (0-9) or -1 if the character is no digit
      int32 DigitValue()const;

      /*!
       \brief Implementation of ==
       */
      DllExport
      friend bool operator==(Char ch1, Char ch2){ return ch1.mChar==ch2.mChar;};

      /*!
       \brief Implementation of !=
       */
      DllExport
      friend bool operator!=(Char ch1, Char ch2){ return ch1.mChar!=ch2.mChar;};

      /*!
       \brief Implementation of <
       */
      DllExport
      friend bool operator<(Char ch1, Char ch2){ return ch1.mChar<ch2.mChar;};

      /*!
       \brief Implementation of <=
       */
      DllExport
      friend bool operator<=(Char ch1, Char ch2){ return ch1.mChar<=ch2.mChar;};

      /*!
       \brief Implementation of >
       */
      DllExport
      friend bool operator>(Char ch1, Char ch2){ return ch1.mChar>ch2.mChar;};

      /*!
       \brief Implementation of >=
       */
      DllExport
      friend bool operator>=(Char ch1, Char ch2){ return ch1.mChar>=ch2.mChar;};

      private:

      //! The character
      uint16 mChar;
   };

   /*!
    \brief This data type represents a Unicode character array. It is deliberately used in
    distinction to the character string and serves as a supporting class when encoding and
    decoding character strings.
    \ingroup core
    */
   struct CharArray
   {
      /*!
       \brief The length of the array.
       */
      Integer length;

      /*!
       \brief The array itself.
       */
      Char* buffer;

      /*!
       \brief Constructor. Everything remains 0 or NULL.
       */
      CharArray();

      /*!
       \brief Constructor create an uninitialized array.
       \param length The length of the array
       */
      CharArray(Integer length);

      /*!
       \brief Copy constructor
       */
      CharArray(const CharArray &another);

      /*!
       \brief Destructor
       */
      virtual ~CharArray();

      CharArray &operator=(const CharArray &another);
   };


}


#endif
