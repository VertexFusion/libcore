////////////////////////////////////////////////////////////////////////////////////////////////////
// Name:        MeoryStream.h
// Library:     Jameo Core Library
// Purpose:     Helper classes for our stream object
//
// Author:      Uwe Runtemund (2015-today)
// Modified by:
// Created:     18.08.2015
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

#ifndef jm_MemoryStream_h
#define jm_MemoryStream_h

#include "Stream.h"

namespace jm
{

   /*!
   \brief The MemoryStream class represents a byte stream access to a byte array.
   */
   class DllExport MemoryStream : public Stream
   {

      public:

         /*!
          \brief Constructor.
          \param array The byte array on which the stream operations will be applied.
          \param length The length of the byte array.
          */
         MemoryStream(uint8* array, int64 length, bool takeOwnership = false);

         /*!
          \brief Destructor
          */
         ~MemoryStream() override;

         Status open(FileMode mode) override;

         bool isOpen() override;

         bool canRead() const override;

         void close() override;

         int64 read(uint8* buffer, int64 length) override;

         int64 readFully(ByteArray& buffer, int64 length) override;

         void seek(int64 position) override;

         void move(int64 offset) override;

         int64 position() override;

         int64 write(const uint8* buffer, int64 length) override;

         int64 size() const override;

         /*!
          \brief Returns the buffer of the MemoryStream.
          \return A pointer to the byte array buffer.
          */
         uint8* buffer();

         /*!
          \brief Returns the written length of the buffer.
          */
         int64 writtenLength() const;

      private:

         //! The byte array that serves as the source or destination.
         uint8* mStream;

         //! Status if this object is stream owner
         bool mStreamOwner;

         //! The length of the byte array.
         int64 mStreamlength;

         //! The current pointer position in the array.
         int64 mPosition;

         //! Written length of the stream
         int64 mWritelength;

   };




}
#endif
