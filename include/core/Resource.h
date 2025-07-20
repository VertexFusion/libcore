////////////////////////////////////////////////////////////////////////////////////////////////////
// Name:        Resource.h
// Library:     Jameo Core Library
// Purpose:     Declaration of Object class
//
// Author:      Uwe Runtemund (2014-today)
// Modified by:
// Created:     01.01.2025
//
// Copyright:   (c) 2025 Jameo Software, Germany. https://jameo.de
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


#ifndef sd_Resource_h
#define sd_Resource_h

#include "Stream.h"

namespace jm
{

   /*!
    \brief This class represents a resource, which comes with the app.

    Resources are files, that are packed with an application. Like images, fonts and other stuff to
    make the application work. On most systems, these are "plain" files in a defined resource
    directory. On Android for example, these are files packed into to apk of the app. So simple file
    access is not possible.

    To handle all resources whether it is a file or a packed resource, we provide this unified
    interface.

    \note On Android, resource names must not contain a point (.), and must be lowercase. In Android
    resources are located without its ending. So in the same path do not have resources with same
    name, but different endings.
    
   \ingroup app
    */
   class DllExport Resource: public jm::Stream
   {
      public:

         explicit Resource(const jm::String& path);

         Resource(const Resource& other);

         Resource& operator=(const Resource& other);

         ~Resource() override;

         bool exists() const;

         size_t size() const override;

         jm::Status open(jm::FileMode mode) override;

         bool isOpen() override;

         bool canRead() const override;

         void close() override;

         size_t read(uint8* buffer, size_t length) override;

         size_t readFully(jm::ByteArray& buffer, size_t length) override;

         void seek(size_t position) override;

         void move(ssize_t offset) override;

         size_t position() override;

         size_t write(const uint8* buffer, size_t length) override;

      private:

         //! The backend stream of the resource
         jm::Stream* mStream;
   };

   //
   // Resource API (only on Android necessary)
   //
   jm::ByteArray osResourceRead(const jm::String& path);

}

#endif
