////////////////////////////////////////////////////////////////////////////////////////////////////
// Name:        Resource.cpp
// Library:     Jameo Core Library
// Purpose:     Resource
//
// Author:      Uwe Runtemund (2024-today)
// Modified by:
// Created:     10.10.2024
//
// Copyright:   (c) 2024 Jameo Software, Germany. https://jameo.de
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


#include "PrecompiledCore.hpp"

using namespace jm;

Resource::Resource(const String& path)
{
#ifdef JM_ANDROID
   jm::ByteArray array = jm::osResourceRead(path);
   if(array.size() <= 0)
   {
      mStream = nullptr;
      return;
   }
   uint8* buffer = new uint8[array.size()];
   memcpy(buffer, array.constData(), array.size());
   mStream = new jm::MemoryStream(buffer, array.size(), true);
#else
   mStream = new jm::File(jm::ResourceDir(jm::System::bundleId()), path);
#endif
}

Resource::Resource(const Resource& other)
{
   mStream = other.mStream;
   if(mStream != nullptr)mStream->retain();
}

Resource& Resource::operator=(const Resource& other)
{
   if(this != &other)
   {
      mStream = other.mStream;
      if(mStream != nullptr)mStream->retain();
   }

   return *this;
}

Resource::~Resource()
{
   if(mStream != nullptr)
   {
      mStream->release();
      mStream = nullptr;
   }
}

int64 Resource::size() const
{
   if(mStream == nullptr)return -1;
   return mStream->size();
}

jm::Status Resource::open(jm::FileMode mode)
{
   return mStream->open(mode);
}

bool Resource::isOpen()
{
   return mStream->isOpen();
}

bool Resource::canRead() const
{
   return mStream->canRead();
}

void Resource::close()
{
   mStream->close();
}

int64 Resource::read(uint8* buffer, int64 length)
{
   return mStream->read(buffer, length);
}

int64 Resource::readFully(jm::ByteArray& buffer, int64 length)
{
   return mStream->readFully(buffer, length);
}

void Resource::seek(int64 position)
{
   mStream->seek(position);
}

void Resource::move(int64 offset)
{
   mStream->move(offset);
}

int64 Resource::position()
{
   return mStream->position();
}

int64 Resource::write(const uint8* buffer, int64 length)
{
   return mStream->write(buffer, length);
}

bool Resource::exists() const
{
   if(mStream != nullptr)
   {
      jm::File* file = dynamic_cast<jm::File*>(mStream);
      if(file != nullptr)return file->exists();
      else return true;
   }
   return false;
}
