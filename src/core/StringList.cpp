////////////////////////////////////////////////////////////////////////////////////////////////////
// Name:        String.cpp
// Library:     Jameo Core Library
// Purpose:     Implementation of String class
//
// Author:      Uwe Runtemund (2014-today)
// Modified by:
// Created:     08.10.2012
//
// Copyright:   (c) 2012 Jameo Software, Germany. https://jameo.de
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


StringList::StringList(): Object()
{
   mData = new String[8];
   mLength = 8;
   mSize = 0;
}

StringList::StringList(size_t size)
{
   mData = new String[size];
   mLength = size;
   mSize = size;
}


StringList::StringList(const jm::String& string): Object()
{
   mData = new String[8];
   mLength = 8;
   mSize = 0;
   append(string);
};

StringList::StringList(const StringList& other): Object()
{
   mSize = other.mSize;
   mLength = other.mLength;
   mData = new String[mLength];
   for(size_t a = 0; a < mSize; a++)
   {
      mData[a] = other.mData[a];
   }
}

StringList::~StringList()
{
   mLength = 0;
   mSize = 0;
   if(mData != nullptr)delete[] mData;
}

void StringList::reserve(size_t size)
{
   checkSize(size);
}

void StringList::append(const jm::String& string)
{
   checkSize(1);
   mData[mSize++] = string;
}

void StringList::remove(const jm::String& string)
{
   for(size_t index = 0; index < mSize; index++)
   {
      if(mData[index] == string)
      {
         for(size_t index2 = index + 1; index2 < mSize; index2++)
         {
            mData[index2 - 1] = mData[index2];
         }
         mSize--;
         index--;
      }
   }
}

size_t StringList::size() const
{
   return mSize;
}

void StringList::sort()
{
   if(mSize < 1)return;

   size_t n = mSize;
   do
   {
      size_t newn = 1;
      for(size_t i = 0; i < n - 1; ++i)
      {
         size_t j = i + 1;
         const String* a1 = &mData[i];
         const String* a2 = &mData[j];
         if(a1->compareTo(*a2) > 0)
         {
            // Swap
            String tmp = mData[i];
            mData[i] = mData[j];
            mData[j] = tmp;

            newn = i + 1;
         }
      }
      n = newn;
   }
   while(n > 1);
}

jm::String StringList::join(Char divider) const
{
   size_t stringSize = mSize - 1;
   for(size_t index = 0; index < mSize; index++)stringSize += mData[index].size();

   jm::String result;
   result.checkCapacity(stringSize);

   for(size_t index = 0; index < mSize; index++)
   {
      if(index > 0)result << divider;
      result << mData[index];
   }

   return result;
}

const String& StringList::get(size_t index) const
{
   if(index >= mSize)
      throw Exception(jm::String("Array index %1 out of bounds.").arg(index));
   return mData[index];
}

void StringList::set(size_t index, const String& item)
{
   if(index >= mSize)
      throw Exception(jm::String("Array index %1 out of bounds.").arg(index));
   mData[index] = item;
}

void StringList::clear()
{
   mSize = 0;
}

bool StringList::contains(const String& str) const
{
   for(size_t index = 0; index < mSize; index++)
   {
      if(mData[index] == str)return true;
   }
   return false;
}


void StringList::checkSize(size_t size)
{
   if(mSize + size < mLength)return;
   while(mLength < mSize + size)mLength += 8;
   String* tmp = new String[mLength];
   for(size_t index = 0; index < mSize; index++)tmp[index] = mData[index];
   delete[] mData;
   mData = tmp;
}

String& jm::StringList::operator[](const size_t index) const
{
   if(index >= mSize)
      throw Exception(jm::String("Array index %1 out of bounds.").arg(index));
   return mData[index];
}

StringList& jm::StringList::operator=(const StringList& another)
{
   if(this != &another)
   {
      delete[] mData;

      mLength = another.mLength;
      mSize = another.mSize;
      mData = new String[mLength];
      for(size_t a = 0; a < mSize; a++)
      {
         mData[a] = another.mData[a];
      }
   }

   return *this;
}

StringList& jm::operator<< (StringList& out, const String& str)
{
   out.append(str);
   return out;
}

String* StringList::begin()
{
   return &mData[0];
}

String* StringList::end()
{
   // Note: end() returns a pointer to the "element" after the last element.
   // This is the standard behavior for STL containers.
   // It allows for range-based for loops to work correctly.
   // This element is not always initialized or valid, but it is used to indicate the end of the
   // container.
   return &mData[mSize];
}
