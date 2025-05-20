////////////////////////////////////////////////////////////////////////////////////////////////////
// Name:        Deflater.h
// Library:     Jameo Core Library
// Purpose:     Deflate Algorithm
//
// Author:      Uwe Runtemund (2015-today)
// Modified by:
// Created:     15.09.2013
//
// Copyright:   (c) 2015 Jameo Software, Germany. https://jameo.de
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

#ifndef jm_Deflater_h
#define jm_Deflater_h

#include "Types.h"
#include "Object.h"

namespace jm
{

   /*!
    \brief Compression class for DEFLATE-compressed data.
    The basis is RFC 1950 and RFC 1951.
    As of 2017-01-14, the own implementation was exchanged in favour of zlib.
    \ingroup core
    */
   class DllExport Deflater: public Object
   {

      public:

         /*!
          \brief Constructor
          */
         Deflater();

         /*!
          \brief Constructor
          \param wrap Status, whether zlib header and CRC are omitted
          */
         //Deflater( bool wrap );

         /*!
          \brief Destructor
          */
         ~Deflater() override = default;

         /*!
          \brief Gives this class a block of bytes to compress.
          \param buffer Uncompressed data
          \param length Data length
          */
         void setInput(uint8* buffer,
                       int64 length);

         /*!
          \brief This method compresses the data in the buffer
          \discussion Both parameters are output values and are initialised by this method.
          The caller must clean up the array himself afterwards.
          \param buffer The buffer into which the data is to be written.
          \param length Buffer length
          */
         void deflate(uint8*& buffer,
                      int64& length);

         /*!
          \brief Resets the compressor so that a new object can be compressed
          */
         void reset();

         /*!
          \brief Returns the total number of bytes of the uncompressed input
          */
         int64 totalInSize();

         /*!
          \brief Returns the total number of bytes of the compressed output
          */
         int64 totalOutSize();

      private:

         //Current block
         uint8* mUncompBytes;
         int64 mUncompLength;
         int64 mUncompIndex;

         //Count variables for processed bytes
         int64 mTotalIn;
         int64 mTotalOut;

   };

}

#endif
