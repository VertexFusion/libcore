////////////////////////////////////////////////////////////////////////////////////////////////////
// Name:        File.h
// Library:     Jameo Core Library
// Purpose:     File
//
// Author:      Uwe Runtemund (2013-today)
// Modified by:
// Created:     12.05.2013
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

#ifndef jm_File_h
#define jm_File_h

#include "String.h"
#include "Array.h"
#include "ByteArray.h"
#include "Object.h"
#include "Stream.h"
#include "Date.h"

namespace jm
{

   /*!
    \brief This field stores the directory separator character based on the operating system.
    */
   #ifdef __APPLE__//macOS, iOS
   const Char DIR_SEP = Char('/');
   #elif defined __linux__ //Linux
   const Char DIR_SEP = Char('/');
   #elif defined _WIN32//Windows
   const Char DIR_SEP = Char('\\');
   #endif

   /*!
    \brief  This class is a representation of file or directory paths. In addition, data can be read
    from and written to the hard disk.
    \ingroup core
    */
   class DllExport File: public Stream, public Comparable<File>
   {
      public:

         /*!
          \brief Default constructor. The file has no name.
          */
         File();

         /*!
          \brief Constructor
          \param pathname Path to the file.
          */
         File(const String& pathname);

         /*!
          \brief Constructor
          \param parent Path of parent file.
          \param child Path of child file.
          */
         File(String parent,
              String child);

         /*!
          \brief Constructor
          \param parent File object of parent file
          \param child Path of child file
          */
         File(const File& parent,
              String child);

         /*!
          \brief Copy constructor
          */
         File(const File& other);

         /*!
          \brief Destructor
          */
         ~File();

         /*!
          \brief checks if the file is null (has no path).
          */
         bool isNull()const;


         /*!
          \brief Checks if the file can be executed.
          */
         bool canExecute() const;

         /*!
          \brief Checks if the file can be read.
          */
         bool canRead() const;

         /*!
          \brief Checks if the file can be written.
          */
         bool canWrite() const;

         /*!
          \brief Creates a new file, but only, if the file not exist. If the file exists,
         nothing happens.
          \return true, if a new file was created. false otherwise.
          */
         bool createNewFile();

         /*!
          \brief Create a new directory.
          \return true, if a new directory was created. false otherwise.
          */
         bool makeDirectory();

         /*!
          \brief Checks if the file exists.
          */
         bool exists() const;

          /*!
           \brief This method deletes the file permanently. If it is a directory, it will only be deleted if it is empty.
           \return true if the file was successfully deleted, false otherwise.
           */
         bool Delete();

          /*!
           \brief Moves the file to the system trash.
           */
         bool moveToTrash();

          /*!
           \brief Renames the file to a new name.
           \param newPath The new path and name for the file.
           */
         bool renameTo(const String& newPath);

          /*!
           \brief Returns the name of the file. This is the pure name without any path information.
           \return The name of the file.
           */
         String name() const;

          /*!
           \brief Returns the directory path of the file, excluding the file name itself.
           It corresponds to the directory in which this file is located.
           \return The directory path of the file.
           */
         String parent() const;

          /*!
           \brief Returns the absolute path of the file from the root of the file system.
           \return The absolute path of the file.
           */
         const String& absolutePath() const;

          /*!
           \brief Returns the full path of this file. The path can be relative or absolute.
           \return The full path of the file.
           */
         String path() const;

          /*!
           \brief This method returns the file extension of the file. If the file does not have
           an extension, the return value is an empty string. An extension is indicated by a dot.
           For ".tar.gz", only "gz" is returned.
           \return The file extension.
           */
         String extension() const;

          /*!
           \brief Checks if this file is an absolute path.
           \return true if the file is an absolute path, false otherwise.
           */
         bool isAbsolute() const;

          /*!
           \brief Checks if this file is a directory.
           \return true if the file is a directory, false otherwise.
           */
         bool isDirectory() const;

          /*!
           \brief Checks if this file is a regular file.
           \return true if the file is a regular file, false otherwise.
           */
         bool isFile() const;

          /*!
           \brief Checks if this file is a symbolic link.
           \return true if the file is a symbolic link, false otherwise.
           */
         bool isLink() const;

          /*!
           \brief Checks if this file is a named pipe (FIFO).
           \return true if the file is a named pipe, false otherwise.
           */
         bool isPipe() const;

          /*!
           \brief Checks if this file is hidden.
           \return true if the file is hidden, false otherwise.
           */
         bool isHidden() const;

          /*!
           \brief Retrieves a list of all files in the directory.
           \return A dynamically allocated array of File objects representing the files in the directory. The caller is responsible for deleting the array.
           */
         Array<File>* listFiles()const;

          /*!
           \brief Returns the size of the file in bytes.
           \return The size of the file in bytes.
           */
         int64 size() const override;

          /*!
           \brief Returns the date of the last modification.
           \return The date of the last modification.
           */
         Date lastModified() const;

          /*!
           \brief Opens the file for read or write operations.
           \param mode The mode for opening the file.
           */
         VxfErrorStatus open(FileMode mode) override;

          /*!
           \brief Checks if the file is open.
           \return true if the file is open, false otherwise.
           */
         bool isOpen() override;

          /*!
           \brief Closes the file if it was previously opened.
           */
         void close() override;

          /*!
           \brief Reads a maximum of length bytes into the array.
           \discussion For large blocks, it is possible that not all bytes are read because
           it is still waiting for data. In this case, only a portion may be returned.
           If you want to ensure that all data is read, you should call "readFully".
           \param buffer The buffer to read the data into.
           \param length The maximum number of bytes to read.
           \return The actual number of bytes read, or 0 if no bytes were read (EOF).
           */
         int64 read(unsigned char* buffer,
                      int64 length) override;

          /*!
           \brief Reads a maximum of length bytes into the array.
           \param buffer The buffer to read the data into.
           \param length The maximum number of bytes to read.
           \return The actual number of bytes read, or 0 if no bytes were read (EOF).
           */
         int64 readFully(ByteArray& buffer, int64 length) override;



          /*!
           \brief Moves the file cursor to the desired position, counted from the beginning of the file.
           \param position The desired position to move the file cursor to (0-based index).
           */
         void seek(int64 position) override;

          /*!
           \brief Moves the file cursor to the desired position, relative to the current position.
           \param offset The offset to move the file cursor by.
           */
         void move(int64 offset) override;

          /*!
           \brief Returns the current cursor position in the file.
           \return The current cursor position.
           */
         int64 position() override;

          /*!
           \brief Writes a buffer to the output file.
           \param buffer The buffer containing the data to be written.
           \param length The number of bytes to write from the buffer.
           \return The number of bytes actually written, or 0 if an error occurred.
           */
         int64 write(const uint8* buffer, int64 length) override;

          /*!
           \brief Compares the absolute file path with another file's absolute path.
           \param other The file to compare with.
           \return An integer value indicating the result of the comparison:
                 - 0 if the file paths are equal.
                 - a negative value if this file path is lexicographically less than the other file path.
                 - a positive value if this file path is lexicographically greater than the other file path.
           */
         int32 compareTo(const File& other) const override;

         /*!
          \brief Returns the tags of the file.

          In mac os these tags are presented by the Finder.
          */
         StringList getTags()const;

         /*!
          \brief Adds a tag to the file. If the tag already exists, nothing happens.
          */
         VxfErrorStatus addTag(const String& tag);

         /*!
          \brief Remove a tag from the file. If the tag not exists, nothing happens.
          */
         VxfErrorStatus removeTag(const String& tag);

         //Operatore
         File& operator=(const File& another);

      private:

         //! The pathname of the file. It is normalized, meaning it uses the directory separators and does not contain duplicates, etc.
         String mPathname;

         //! The C-String representation of the pathname. It is created and held when needed.
         ByteArray mCstr;

          //! Filehandle in operating system
         FILE* mHandle;

          /*!
           \brief This method normalizes the pathname.
           \details On Unix, a normalized pathname does not contain duplicate slashes
           and does not end with a slash.
           \param pathname The pathname to be normalized.
           \return The normalized pathname.
           */
         String normalize(const String& pathname);

          /*!
           \brief This method combines the parent name with the child name.
           Note: Both parent and child paths must be normalized.
           \param parent The pathname of the parent file.
           \param child The pathname of the child file.
           \return The combined pathname of the parent and child files.
           */
         String resolve(String parent,
                        String child);

          /*!
           \brief This helper method sets the C-string used to resolve the filename in the operating system.
           */
         void setCString();

         //! Helper for storing tag list
         VxfErrorStatus setTags(const jm::StringList& tags);

   };

   /*!
    \brief This method returns the path of the executing application. It consists of
    the directory name and the application name.
    \return The path of the executing application.
    */
   extern DllExport
   String ExecPath();

   /*!
    \brief This method returns the directory where the application is being executed.
    \return The directory where the application is being executed.
    */
   extern DllExport
   String ExecDir();

   /*!
      \brief This method returns the name of the current application.
    */
   extern DllExport
   String ExecName();

   /*!
    \brief This method returns the directory where the current application should search for resources.
    \param bundleId The identifier of the application bundle (same as Bundle-Id for macOS).
    \return The directory where the application should search for resources.
    */
   extern DllExport
   File ResourceDir(const String& bundleId);

   /*!
    \brief This method returns the directory where the current application stores its settings.
    \return The directory where the application's settings are stored.
    */
   extern DllExport
   File PropertyDir();

   /*!
    \brief This method returns the user directory.
    */
   extern DllExport
   File UserDir();

   /*!
    \brief This method returns the current directory.
    */
   extern DllExport
   File currentDir();

}


#endif
