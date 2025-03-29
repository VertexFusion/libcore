////////////////////////////////////////////////////////////////////////////////////////////////////
// Name:        ZipFile.h
// Library:     Jameo Core Library
// Purpose:     Read & Write ZIP-Files
//
// Author:      Uwe Runtemund (2017-today)
// Modified by:
// Created:     13.08.2017
//
// Copyright:   (c) 2017 Jameo Software, Germany. https://jameo.de
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

#ifndef jm_ZipFile_h
#define jm_ZipFile_h

#include "File.h"
#include "LinkedList.h"

namespace jm
{

   /*!
   \brief Entry for a ZIP file.
   */
   class DllExport ZipEntry: public Object
   {
      public:

          /*!
           \brief Constructor for the ZipEntry class.
           \param name The name of the entry.
           */
         explicit ZipEntry(const String& name);

         /*!
          \brief Returns the name of the entry.
          */
         String name()const;

          /*!
           \brief Set the size of the uncompressed entry.
           \param size The size of the uncompressed entry in bytes.
           */
         void setUncompressedSize(uint32 size);

         /*!
          \brief Returns the size of the uncompressed entry.
          */
         uint32 uncompressedSize()const;

         /*!
          \brief Returns true, if the entry is a directory. An entry is recognized as
          a directory, if the last character of the name is '/'.
          */
         bool isDirectory()const;

      private:

         String mName;
         String mExtra;
         String mComment;
         uint32 mUncompressedSize;
         uint32 mCompressedSize;
         uint32 mHeaderOffset;
         uint32 mCRC;
         uint32 mDataOffset; // 0-based offset in file

         friend class ZipFile;
         friend class ZipOutputFile;
   };

   /*!
    \brief This class represents a ZIP file for reading ZIP data.
    */
   class DllExport ZipFile: public Object
   {

      public:

           /*!
            \brief Constructor for ZipFile class.
            \param file A pointer to the Stream object representing the ZIP file.
            */
          explicit ZipFile(Stream* file);

         /*!
          \brief Destructor
          */
         ~ZipFile() override;

          /*!
           \brief Opens the file for reading.
           */
         void open();

          /*!
           \brief Closes the file.
           */
          void close();

          /*!
           \brief Returns the comment of the ZIP file, or an empty string if no comment exists.
           \return The comment of the ZIP file.
           */
         String comment();

          /*!
           \brief Returns the ZipEntry object if it exists, or nullptr if it does not exist.
           \note ZipFile is owner of ZipEntry. If you want to get ownership, you must call \c retain()
           \param name The name of the ZipEntry to retrieve.
           \return A pointer to the ZipEntry object if it exists, or nullptr otherwise.
           */
         ZipEntry* entry(const String& name);

          /*!
           \brief Returns an iterator over the Zip entries.
           \return An iterator over the Zip entries.
           */
         LinkedListIterator entryIterator();

          /*!
           \brief Returns the number of Zip entries in the ZipFile.
           \return The number of Zip entries.
           */
         uint32 entryCount() const;

          /*!
           \brief Returns the stream containing the uncompressed data of the entry. The caller
           of this method takes ownership of the stream and is responsible for cleaning it up.
           The stream is read-only and can only be used to read the data from a ZIP file.
           Writing to the stream is not supported.
           \param entry The ZipEntry object for which the stream is requested.
           \return A pointer to the Stream object containing the uncompressed data, or nullptr if the entry does not exist.
           */
         Stream* stream(const ZipEntry* entry);

      private:

          //! The file.
          Stream* mFile;

          //! The entries
         LinkedList mEntries;

   };


   /*!
   \brief This class represents a ZIP file for writing ZIP data.
   */
   class DllExport ZipOutputFile: public Object
   {

      public:

          /*!
          \brief Constructor for the ZipOutputFile class.
          \param file A pointer to the File object representing the ZIP file.
          */
          explicit ZipOutputFile(File* file);

          /*!
          \brief Opens the file for writing.
          */
         void open();

          /*!
          \brief Closes the file and releases any resources associated with it.
          */
         void close();

          /*!
          \brief Closes the current entry and prepares the file for writing the next entry.
          This method should be called after writing the data for the current entry is complete.
          */
          void closeEntry();

          /*!
          \brief Begins writing a new ZIP entry. The stream is now positioned correctly to receive data.
          \param entry The ZipEntry object representing the new entry to be written.
          */
          void putNextEntry(ZipEntry* entry);

          /*!
          \brief Writes the specified data to the stream.
          \param data A pointer to the data to be written.
          \param offset The offset in the data buffer where writing should start.
          \param length The number of bytes to write.
          */
          void write(uint8* data, int64 offset, int64 length);

          /*!
          \brief Writes the content of the file to the stream and closes the file.
          \param file A pointer to the File object representing the file to be written.
          */
          void writeAndClose(File* file);


      private:

          //! The ZIP file.
          File* mFile;

          //! Temporary file for uncompressed data
          File* mTemp;

          //! The entries
          LinkedList mEntries;

   };

}


#endif
