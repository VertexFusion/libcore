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

#include "Precompiled.h"

using namespace jm;

ByteArray::ByteArray() : Object()
{
   mArrSize = 0;
   mRawSize = 0;
   mData = NULL;
};

ByteArray::ByteArray(const int8* buffer, Integer size) : Object()
{
   Init(buffer,size);
}

ByteArray::ByteArray(const uint8* buffer, Integer size) : Object()
{
   Init((const int8*)buffer,size);
}

void ByteArray::Init(const int8* buffer, Integer size)
{
   if(buffer == NULL)
   {
      mArrSize = 0;
      mRawSize = 0;
      mData = NULL;
      return;
   }

   if(size < 0)
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


ByteArray::ByteArray(Integer length, uint8 ch) : Object()
{
   mArrSize = length;
   mRawSize = mArrSize + 1;
   mData = new uint8[mRawSize];
   mData[mArrSize] = 0;
   Fill(ch);
};

ByteArray::ByteArray(const ByteArray& other) : Object()
{
   mArrSize = other.mArrSize;
   mRawSize = other.mRawSize;
   mData = new uint8[mRawSize];
   for(Integer index = 0; index < mRawSize; index++)
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
   Integer cnt = 0;
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
   if(mData != NULL)delete[] mData;
};

Integer ByteArray::Size() const
{
   return mArrSize;
};

bool ByteArray::IsNull() const
{
   return mData == NULL;
}

bool ByteArray::IsEmpty() const
{
   return mArrSize == 0;
}

int8* ByteArray::Data()
{
   return reinterpret_cast<int8*>(mData);
}

const char* ByteArray::ConstData() const
{
   return reinterpret_cast<const char*>(mData);
}


void ByteArray::Sort()
{
   if(mArrSize < 1)return;

   Integer n = mArrSize;
   do
   {
      Integer newn = 1;
      for(Integer i = 0; i < n - 1; ++i)
      {
         Integer j = i + 1;
         uint8 a1 = mData[i];
         uint8 a2 = mData[j];
         if(a1 > a2)
         {
            //Vertausche
            uint8 tmp = mData[i];
            mData[i] = mData[j];
            mData[j] = tmp;

            newn = i + 1;
         }
      }
      n = newn;
   }
   while(n > 1);
}

void ByteArray::Fill(uint8 ch)
{
   for(Integer index = 0; index < mArrSize; index++)mData[index] = ch;
}


uint8 ByteArray::Get(Integer index) const
{
   //if (index >= mLength)
   //	throw new Exception("Array index out of bounds.");
   return mData[index];
};

void ByteArray::Set(Integer index, uint8 item)
{
   //if (index >= mLength)
   //	throw new Exception("Array index out of bounds.");
   mData[index] = item;
};

void ByteArray::Replace(Integer tgtOffset,Integer srcOffset,const ByteArray &buffer, Integer length)
{
   Integer range=Min(length, mArrSize-tgtOffset);

   for(Integer a=0;a<range;a++)
   {
      mData[a] = buffer.mData[srcOffset+a];
   }
}

void ByteArray::Resize(Integer newSize)
{
   if(newSize<=mRawSize-1)
   {
      mArrSize=newSize;
      mData[mArrSize]=0;
   }
   else
   {
      uint8* tmp = new uint8[newSize+1];
      for(Integer index=0;index<mArrSize;index++)
      {
         tmp[index] = mData[index];
      }
      for(Integer index=mArrSize;index<newSize;index++)
      {
         tmp[index] = 0;
      }
      mRawSize=newSize+1;
      mArrSize=newSize;
   }
}

uint8& jm::ByteArray::operator[](const Integer index) const
{
   //if (index >= mLength)
   //	throw new Exception("Array index out of bounds.");
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
      for(Integer a = 0; a < mRawSize; a++)
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
      if(a1.Size() != a2.Size())return false;

      for(Integer index = 0; index < a1.Size(); index++)
      {
         if(a1[index] != a2[index])return false;
      }

      return true;
   }

}
