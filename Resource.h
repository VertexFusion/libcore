////////////////////////////////////////////////////////////////////////////////////////////////////
//
// This file is part of Nuitk.
//
// Nuitk is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 2.1 of the License, or
// (at your option) any later version.
//
// Nuitk is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with Nuitk. If not, see <http://www.gnu.org/licenses/>.
//
// Copyright (C) 2024 Jameo UG (haftungsbeschraenkt)
// Author: Uwe Runtemund
//
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef NResource_h
#define NResource_h

#include "core/Core.h"
#include "nui/Widget.h"

namespace nui
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
    */
   class Resource:public jm::Stream
   {
      public:

         Resource(const jm::String& path);

         Resource(const Resource& other);

         Resource& operator=(const Resource& other);

         ~Resource();

         bool exists() const;

         int64 size() const override;

         jm::Status open(jm::FileMode mode) override;

         bool isOpen() override;

         void close() override;

         int64 read(uint8* buffer, int64 length) override;

         int64 readFully(jm::ByteArray& buffer, int64 length) override;

         void seek(int64 position) override;

         void move(int64 offset) override;

         int64 position() override;

         int64 write(const uint8* buffer, int64 length) override;

      private:

         //! The backend stream of the resource
         jm::Stream* mStream;
    };

}

#endif
