////////////////////////////////////////////////////////////////////////////////////////////////////
// Name:        Base64.h
// Library:     Jameo Core Library
// Purpose:     Base64 Encoding/Decoding
//
// Author:      Uwe Runtemund (2020-today)
// Modified by:
// Created:     28.12.2020
//
// Copyright:   (c) 2020 Jameo Software, Germany. https://jameo.de
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
#ifndef jm_Base64_h
#define jm_Base64_h

#include "String.h"

namespace jm
{

   /*!
    \brief Implementation of the BASE64 algorithm.
    \ingroup core
    */
   class DllExport Base64
   {
      public:

         /*!
          \brief Encodes the data stream with the BASE64 algorithm.
          \param data The data to be encoded.
          \param length The length of the input buffer. After exiting the method, the length of the
          output buffer is returned here.
          \return The output buffer. The caller of the method takes over the array and has to clean
          it up by himself.
          */
         static uint8* encode(const uint8* data, Integer& length);

         /*!
          \brief Decodes the data stream with the BASE64 algorithm.
          \param data The data to be decoded.
          \param length The length of the input buffer. After exiting the method, the length of the
          output buffer is returned here.
          \return The output buffer. The caller of the method takes over the array and has to clean
          it up by himself.
          */
         static uint8* decode(const uint8* data, uint32& length);

   };

}

#endif
