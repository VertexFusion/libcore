////////////////////////////////////////////////////////////////////////////////////////////////////
// Name:        Stream.h
// Library:     Jameo Core Library
// Purpose:     Declaration of Stream class
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

#ifndef jm_Stream_h
#define jm_Stream_h

#include "Types.h"
#include "Object.h"
#include "String.h"

namespace jm
{

   /*!
    \brief Mode for opening streams and files.
    */
   enum class FileMode
   {
      kRead,      /*!< Open for reading only. Corresponds to \c rb */
      kWrite,     /*!< Open for writing only. Corresponds to \c wb */
      kReadWrite  /*!< Open for reading and writing. Corresponds to \c rb+ */
   };

   /*!
    \brief The Stream class is an abstraction class for manipulating data streams through a unified interface.
    The stream itself can be a file, a byte array, a network interface, or anything else.
    \details The Stream class provides methods for reading and writing data, as well as managing the stream's state.
    */
   class DllExport Stream: public Object
   {

      public:

         /*!
          \brief Constructor.
          */
         Stream();

         /*!
          \brief Returns the length of the stream.
          \details This method returns the length of the stream in bytes.
          \return The length of the stream.
          */
         virtual int64 size() const = 0;

         /*!
          \brief Opens the stream for read or write operations.
          \param mode The mode to open the stream.
          \details This method opens the stream for read or write operations based on the specified mode.
          \return The status of the operation.
          */
         virtual Status open(FileMode mode) = 0;

         /*!
          \brief Returns whether the file is open or not.
          \details This method returns a boolean value indicating whether the file is currently open or not.
          \return \c true if the file is open, \c false otherwise.
          */
         virtual bool isOpen() = 0;

         /*!
          \brief Closes the stream if it was previously opened and releases any system resources.
          \details This method closes the stream if it was previously opened and releases any system resources associated with it.
          */
         virtual void close() = 0;

         /*!
          \brief Reads a maximum of length bytes into the array.
          \details For large blocks, it is possible that not all bytes are read because
          it is still waiting for data. In this case, only a portion may be returned.
          If you want to ensure that all data is read, you should call readFully().
          \return The actual number of bytes read, or 0 if no bytes were read (EOF).
          */
         virtual int64 read(uint8* buffer, int64 length) = 0;

         /*!
          \brief Reads a maximum of length bytes into the array.
          \details For large blocks, it is possible that not all bytes are read because
          it is still waiting for data. In this case, only a portion may be returned.
          If you want to ensure that all data is read, you should call readFully().
          \param buffer The buffer to read the data from.
           \param length The maximum number of bytes to read.
          \return The actual number of bytes read, or 0 if no bytes were read (EOF).
          */
         virtual int64 readFully(ByteArray& buffer, int64 length) = 0;

         /*!
         \brief Reads a maximum of length bytes into the array.
         \param buffer The buffer to read the data from.
         \return The actual number of bytes read, or 0 if no bytes were read (EOF).
         */
         int64 readFully(ByteArray& buffer);

         /*!
          \brief Moves the file cursor to the desired position, counted from the beginning of the file
          (0-based index).
          \note Not every stream supports this method.
          \details This method moves the file cursor to the specified position, counted from the beginning of the file.
          */
         virtual void seek(int64 position) = 0;

         /*!
          \brief Moves the file cursor to the desired position, counted from the current position.
          \details This method moves the file cursor to the specified position, counted from the current position.
          */
         virtual void move(int64 offset) = 0;

         /*!
          \brief Returns the current cursor position in the file.
          \note Not every stream supports this method.
          \details This method returns the current cursor position in the file.
          \return The current cursor position.
          */
         virtual int64 position() = 0;

         /*!
          \brief Writes a buffer to the output file.
          \details This method writes the contents of the buffer to the output file.
          \param buffer The buffer containing the data to be written.
          \param length The number of bytes to write from the buffer.
          \return The actual number of bytes written.
          */
         virtual int64 write(const uint8* buffer, int64 length) = 0;

         /*!
          \brief Writes a buffer to the output file.
          \details This method writes the contents of the buffer to the output file.
          \param buffer The buffer containing the data to be written.
          \param length The number of bytes to write from the buffer.
          \return The actual number of bytes written.
          */
         inline int64 write(const int8* buffer, int64 length)
         {
            return write((const uint8*)buffer, length);
         };

         /*!
          \brief Writes a string to the output file. The encoding is the default encoding (UTF-8). NOT AS A C-STRING!
          \details This method writes the specified string to the output file using the default encoding, which is UTF-8. The string should not be passed as a C-string.
          */
         int64 write(const String& string);

   };
}
#endif
