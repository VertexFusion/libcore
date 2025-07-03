////////////////////////////////////////////////////////////////////////////////////////////////////
// Name:        ByteArray.cpp
// Library:     Jameo Core Library
// Purpose:     Implementation of ByteArray
//
// Author:      Uwe Runtemund (2013-today)
// Modified by:
// Created:     30.01.2024
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

ByteArray::ByteArray() : Object()
{
   mArrSize = 0;
   mRawSize = 0;
   mData = nullptr;
};

ByteArray::ByteArray(const int8* buffer, size_t size) : Object()
{
   init(buffer, size);
}

ByteArray::ByteArray(const uint8* buffer, size_t size) : Object()
{
   init(reinterpret_cast<const int8*>(buffer), size);
}

void ByteArray::init(const int8* buffer, size_t size)
{
   if(buffer == nullptr)
   {
      mArrSize = 0;
      mRawSize = 0;
      mData = nullptr;
      return;
   }

   if(size == npos)
   {
      mArrSize = 0;
      while(buffer[mArrSize] != 0)
      {
         mArrSize++;
      }
   }
   else mArrSize = size;

   mRawSize = mArrSize + 1;
   mData = new uint8[mRawSize];
   mData[mArrSize] = 0;

   memcpy(mData, buffer, mArrSize);
}


ByteArray::ByteArray(size_t length, uint8 ch) : Object()
{
   mArrSize = length;
   mRawSize = mArrSize + 1;
   mData = new uint8[mRawSize];
   mData[mArrSize] = 0;
   fill(ch);
};

ByteArray::ByteArray(const ByteArray& other) : Object()
{
   mArrSize = other.mArrSize;
   mRawSize = other.mRawSize;
   mData = new uint8[mRawSize];
   for(size_t index = 0; index < mRawSize; index++)
   {
      mData[index] = other.mData[index];
   }
}

ByteArray::ByteArray(std::initializer_list<uint8> list) : Object()
{
   mArrSize = list.size();
   mRawSize = mArrSize + 1;
   mData = new uint8[mRawSize];
   std::initializer_list<uint8>::iterator it;
   size_t cnt = 0;
   for(it = list.begin(); it != list.end(); ++it)
   {
      mData[cnt++] = *it;
   }
   mData[mArrSize] = 0;
}

ByteArray::~ByteArray()
{
   mArrSize = 0;
   mRawSize = 0;
   if(mData != nullptr)delete[] mData;
};

size_t ByteArray::size() const
{
   return mArrSize;
};

bool ByteArray::isNull() const
{
   return mData == nullptr;
}

bool ByteArray::isEmpty() const
{
   return mArrSize == 0;
}

int8* ByteArray::data()
{
   return reinterpret_cast<int8*>(mData);
}

const char* ByteArray::constData() const
{
   return reinterpret_cast<const char*>(mData);
}


void ByteArray::sort()
{
   if(mArrSize < 1)return;

   size_t n = mArrSize;
   do
   {
      size_t newn = 1;
      for(size_t i = 0; i < n - 1; ++i)
      {
         const size_t j = i + 1;
         const uint8 a1 = mData[i];
         const uint8 a2 = mData[j];
         if(a1 > a2)
         {
            //Vertausche
            const uint8 tmp = mData[i];
            mData[i] = mData[j];
            mData[j] = tmp;

            newn = i + 1;
         }
      }
      n = newn;
   }
   while(n > 1);
}

void ByteArray::fill(uint8 ch)
{
   for(size_t index = 0; index < mArrSize; index++)mData[index] = ch;
}


uint8 ByteArray::get(size_t index) const
{
   //if (index >= mLength)
   //	throw new Exception("Array index out of bounds.");
   return mData[index];
};

void ByteArray::set(size_t index, uint8 item)
{
   //if (index >= mLength)
   //	throw new Exception("Array index out of bounds.");
   mData[index] = item;
};

void ByteArray::replace(size_t tgtOffset,
                        size_t srcOffset,
                        const ByteArray& buffer,
                        size_t length)
{
   const size_t range = std::min(length, mArrSize - tgtOffset);

   for(size_t a = 0; a < range; a++)
   {
      mData[a] = buffer.mData[srcOffset + a];
   }
}

void ByteArray::replace(uint8 oldValue, uint8 newValue)
{
   for(size_t index = 0; index < mArrSize; index++)
   {
      if(mData[index] == oldValue)mData[index] = newValue;
   }
}


void ByteArray::resize(size_t newSize)
{
   if(newSize <= mRawSize - 1)
   {
      mArrSize = newSize;
      mData[mArrSize] = 0;
   }
   else
   {
      uint8* tmp = new uint8[newSize + 1];
      for(size_t index = 0; index < mArrSize; index++)
      {
         tmp[index] = mData[index];
      }
      for(size_t index = mArrSize; index < newSize; index++)
      {
         tmp[index] = 0;
      }
      mRawSize = newSize + 1;
      mArrSize = newSize;
      if(mData != nullptr)delete mData;
      mData = tmp;
   }
}

uint8 jm::ByteArray::operator[](size_t index) const
{
   //if (index >= mLength)
   //	throw new Exception("Array index out of bounds.");
   return mData[index];
}

uint8& jm::ByteArray::operator[](size_t index)
{
   //if (index >= mLength)
   //   throw new Exception("Array index out of bounds.");
   return mData[index];
}

ByteArray& jm::ByteArray::operator=(const ByteArray& another)
{
   if(this != &another)
   {
      delete[] mData;

      mArrSize = another.mArrSize;
      mRawSize = another.mRawSize;
      mData = new uint8[mRawSize];
      for(size_t a = 0; a < mRawSize; a++)
      {
         mData[a] = another.mData[a];
      }
   }

   return *this;
}

namespace jm
{
   bool operator==(const ByteArray& a1, const ByteArray& a2)
   {
      if(a1.size() != a2.size())return false;

      for(size_t index = 0; index < a1.size(); index++)
      {
         if(a1[index] != a2[index])return false;
      }

      return true;
   }

}
