////////////////////////////////////////////////////////////////////////////////////////////////////
// Name:        Array.h
// Library:     Jameo Core Library
// Purpose:     Declaration of dirrefent arrays types
//
// Author:      Uwe Runtemund (2013-today)
// Modified by:
// Created:     30.01.2024
//
// Copyright:   (c) 2024 Jameo Software, Germany. https://jameo.de
//
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

#ifndef jm_ByteArray_h
#define jm_ByteArray_h

#include "Object.h"

namespace jm
{

   /*!
    \brief Represents a byte array and provide convenient methods for accessing the data.
    The Byte array is always \0 terminated.
    */
   class DllExport ByteArray : public Object
   {
      public:

         /*!
          \brief Default Constructor.
         */
         ByteArray();

         /*!
          \brief Create a byte array. If size is < 0, a 0 terminated string is assumed.
          We make a copy of buffer.
          If buffer is NULL a NULL array is created.
          */
         ByteArray(const int8* buffer, int64 size = -1);
         ByteArray(const uint8* buffer, int64 size = -1);

         /*!
          \brief Creates a byte array of size and fills every byte with ch.
         */
         ByteArray(int64 size, uint8 ch);

         ByteArray(const ByteArray& other);

         ByteArray(std::initializer_list<uint8> list);

         virtual ~ByteArray();

         /*!
          \brief Returns the pointer to the data. With the pointer it is possible to modify the
          data. The data is always \0-terminated. The number of bytes can be assumed as Size()+1,
          including the \0-terminator.
          */
         int8* data();

         /*!
          \brief Returns a const pointer to the data.
          \note We use char (instead of int8 here, because char can be signe or unsigned, depending on operating system.)
          */
         const char* constData() const;

         /*!
          \brief Returns the size of the array.
          */
         int64 size() const;

         /*!
          \brief Returns true, if the array is NULL.
          */
         bool isNull() const;

         /*!
          \brief Returns true, if the size of the array is 0.
          */
         bool isEmpty() const;

         /*!
          \brief Sort the bytes in the array in ascending order.
          */
         void sort();

         /*!
          \brief Set every byte in the array to ch.
          */
         void fill(uint8 ch);

         /*!
          \brief Resize the byte array. If the new size is bigger, it will increase the array. If the size is smaller,
          the bytes beyond the new size are excluded, but the array will have the same size.
         \param newSize The new size of the array.
          */
         void resize(int64 newSize);

         uint8 get(int64 index) const;

         void set(int64 index, uint8 item);

         /*!
          \brief Replaces the content of this array with the content of the other array
          */
         void replace(int64 tgtOffset, int64 srcOffset, const ByteArray& buffer, int64 length);

         /*!
          \brief Replaces every byte of oldValue by the newValue.
          */
         void replace(uint8 oldValue, uint8 newValue);

         uint8& operator[](const int64 index) const;

         ByteArray& operator=(const ByteArray& another);

         friend bool operator==(const ByteArray& a1, const ByteArray& a2);

      private:

         //! The size of array. Can be less than the size of mData.
         int64 mArrSize;

         //! The size of the mData array.
         int64  mRawSize;

         //! The array itself.
         uint8* mData;

         void init(const int8* buffer, int64 size);


   };

}
#endif
