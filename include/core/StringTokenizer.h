////////////////////////////////////////////////////////////////////////////////////////////////////
// Name:        StringTokenizer.h
// Library:     Jameo Core Library
// Purpose:     String tokenizer
//
// Author:      Uwe Runtemund (2013-today)
// Modified by:
// Created:     02.02.2013
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

#ifndef jm_StringTokenizer_h
#define jm_StringTokenizer_h

#include "String.h"

namespace jm
{

   /*!
    \brief The StringTokenizer class is used to tokenize a string based on specified delimiters.
    It splits the string into individual pieces.
    */
   class DllExport StringTokenizer: public Object
   {
      public:

         /*!
         \brief Constructor
         \param str The string to be analyzed.
         \param delimiter The delimiters used to split the string. Each character is considered as a delimiter.
         \param retDelim Status indicating whether the delimiters should be treated as separate tokens and returned or not.
         */
         StringTokenizer(const String& str, const String& delimiter, bool retDelim);

         /*!
          \brief Returns whether there are more tokens in the string.
          */
         bool hasNext();

         /*!
          \brief Returns the next token.
          \throw Exception if no token is available.
          */
         String next();

      private:

         //! The string to be analyzed.
         String mStr;

         //! The delimiters used to split the string.
         String mDelimiters;

         //! The current pointer position.
         size_t mPosition;

         //! The pointer position of the first character of the next token.
         size_t mNewStart;

         //! Status indicating whether the delimiters should be treated as separate tokens and returned or not.
         bool mRetDelim;

         /*!
          \brief This method checks if the character at a position is a delimiter
          \param index The 0-based index of the character in the string to be examined.
          \return "True" if the character at position index is a defined delimiter. Otherwise, "false".
          */
         bool isDelimiter(size_t index) const;

         /*!
          \brief This method searches for the end of a token starting from a desired position,
          i.e., it finds the index of the first delimiter character.
          \param startPos The position to start searching from.
          \return The index in the string str where the end of the token was found, or the length of
          the token if no delimiter is found anymore.
          */
         size_t findTokenEnd(size_t startPos) const;

         /*!
          \brief This method searches for the end of the delimiter starting from a specific position. If
          retDelim is "false", it returns the position of the first non-delimiter character starting from the
          given position. If retDelim is "true", it returns the startPosition.
          \param startPos The position to be searched.
          \return The index in the string str where the end of the delimiter was found.
         */
         size_t findDelimiterEnd(size_t startPos) const;
   };


}


#endif
