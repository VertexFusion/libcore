////////////////////////////////////////////////////////////////////////////////////////////////////
// Name:        CRC.h
// Library:     Jameo Core Library
// Purpose:     CRC
//
// Author:      Uwe Runtemund (2013-today)
// Modified by:
// Created:     19.11.2013
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

#ifndef jm_CRC_h
#define jm_CRC_h

namespace jm
{
   /*!
    \brief DWG files use many CRC (cyclic redundancy check) checksum algorithms to verify the
    integrity of the file. This method provides the appropriate methods to calculate and check the
    checksums.
    \ingroup core
    */
   class DllExport CRC
   {
      public:

         /*!
          \brief Calculate checksum.
          \param initial Start value for CRC calculation
          \param buffer Pointer to the first byte in the buffer to check.
          \param length Length to check
          */
         static uint16 crc8(uint16 initial, uint8* buffer, uint32 length);
   };


}


#endif
