////////////////////////////////////////////////////////////////////////////////////////////////////
// Name:        Array.h
// Library:     Jameo Core Library
// Purpose:     Declaration of different arrays types
//
// Author:      Uwe Runtemund (2013-today)
// Modified by:
// Created:     09.06.2012
//
// Copyright:   (c) 2012 Jameo Software, Germany. https://jameo.de
//
//
// Licence:     The MIT License
//              Permission is hereby granted, free of charge, to any person obtaining a copy of this
//              software and associated documentation files (the "Software"), to deal in the
//              Software without restriction, including without limitation the rights to use, copy,
//              modify, merge, publish, distribute, sub-license, and/or sell copies of the Software,
//              and to permit persons to whom the Software is furnished to do so, subject to the
//              following conditions:
//
//              The above copyright notice and this permission notice shall be included in all
//              copies or substantial portions of the Software.
//
//              THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
//              INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
//              PARTICULAR PURPOSE AND NON-INFRINGEMENT.IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
//              HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF
//              CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE
//              OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
//
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef jm_Array_h
#define jm_Array_h

#include "Types.h"
#include "String.h"
#include "Exception.h"

namespace jm
{
   /*!
    \brief The array class serves as a template for handling arrays as easily as variables.
     At the same time, array size control takes place.
     \ingroup core
    */
   template <class T>
   class Array: public Object
   {
      public:

         Array(): Object(),
            mSize(0)
         {
            mData = new T[0];
         };

         explicit Array(size_t size): Object(),
            mSize(size)
         {
            mSize = size;
            mData = new T[size];
         };

         Array(const Array& other): Object()
         {
            mSize = other.mSize;
            mData = new T[mSize];
            for(size_t a = 0; a < mSize; a++)
            {
               mData[a] = other.mData[a];
            }
         }

         ~Array() override
         {
            mSize = 0;
            if(mData != nullptr)delete[] mData;
         };

         inline size_t size() const
         {
            return mSize;
         };

         inline void sort()
         {
            if(mSize < 1)return;
            if(dynamic_cast<Comparable<T>*>(&mData[0]) == nullptr)return;

            size_t n = mSize;
            do
            {
               size_t newn = 1;
               for(size_t i = 0; i < n - 1; ++i)
               {
                  size_t j = i + 1;
                  Comparable<T>* a1 = static_cast<Comparable<T>*>(&mData[i]);
                  Comparable<T>* a2 = static_cast<Comparable<T>*>(&mData[j]);
                  if(a1->compareTo(*static_cast<T*>(a2)) > 0)
                  {
                     //Vertausche
                     T tmp = mData[i];
                     mData[i] = mData[j];
                     mData[j] = tmp;

                     newn = i + 1;
                  }
               }
               n = newn;
            }
            while(n > 1);
         }

         inline T get(size_t index) const
         {
            if(index >= mSize)
               throw Exception("Array index out of bounds.");
            return mData[index];
         };

         inline void set(size_t index, T item)
         {
            if(index >= mSize)
               throw Exception("Array index out of bounds.");
            mData[index] = item;
         };

         inline T& operator[](const size_t index) const
         {
            if(index >= mSize)
               throw Exception("Array index out of bounds.");
            return mData[index];
         }

         Array& operator=(const Array& another)
         {
            if(this != &another)
            {
               delete[] mData;

               mSize = another.mSize;
               mData = new T[mSize];
               for(size_t a = 0; a < mSize; a++)
               {
                  mData[a] = another.mData[a];
               }
            }

            return *this;
         }

      private:

         /*!
          The length of the array.
          */
         size_t mSize;

         /*!
          \brief The data array itself.
          */
         T* mData;

   };


   /*!
   Specialization for pointer arrays.
   */
   template <class T>
   class Array<T*> : public Object
   {
      public:

         Array() : Object(),
            mLength(0)
         {
            mData = new T*[0];
         };

         explicit Array(size_t length) : Object(),
            mLength(length)
         {
            mData = new T*[length];
         };

         Array(const Array& other) : Object(),
            mLength(other.mLength)
         {
            mData = new T*[mLength];
            for(size_t a = 0; a < mLength; a++)
            {
               mData[a] = other.mData[a];
            }
         }

         ~Array() override
         {
            mLength = 0;
            if(mData != nullptr)delete[] mData;
         };

         inline size_t size() const
         {
            return mLength;
         };

         inline void sort()
         {
            if(mLength < 1)return;
            if(mData[0] == nullptr)return;

            size_t n = mLength;
            do
            {
               size_t newn = 1;
               for(size_t i = 0; i < n - 1; ++i)
               {
                  size_t j = i + 1;
                  const Comparable<T>* a1 = static_cast<Comparable<T>*>(mData[i]);
                  const T& a2 = *mData[j];
                  if(a1->compareTo(a2) > 0)
                  {
                     // Swap
                     T* tmp = mData[i];
                     mData[i] = mData[j];
                     mData[j] = tmp;

                     newn = i + 1;
                  }
               }
               n = newn;
            }
            while(n > 1);
         }

         inline T* get(size_t index) const
         {
            if(index >= mLength)
               throw Exception("Array index out of bounds.");
            return mData[index];
         };

         inline void set(size_t index, T* item)
         {
            if(index >= mLength)
               throw Exception("Array index out of bounds.");
            mData[index] = item;
         };

         inline T*& operator[](const size_t index) const
         {
            if(index >= mLength)
               throw Exception("Array index out of bounds.");
            return mData[index];
         }


         Array& operator=(const Array& another)
         {
            if(this != &another)
            {
               delete[] mData;

               mLength = another.mLength;
               mData = new T*[mLength];
               for(size_t a = 0; a < mLength; a++)
               {
                  mData[a] = another.mData[a];
               }
            }

            return *this;
         }

      private:

         //! The length of the array.
         size_t mLength;

         //! The data of the array.
         T** mData;

   };


   /*!
    FloatArray
    */
   class FloatArray: public Object
   {
      public:

         FloatArray(): Object()
         {
            mLength = 0;
            mData = new float[0];
         };

         explicit FloatArray(size_t length): Object()
         {
            mLength = length;
            mData = new float[length];
         };

         FloatArray(const FloatArray& other): Object()
         {
            mLength = other.mLength;
            mData = new float[mLength];
            for(size_t a = 0; a < mLength; a++)
            {
               mData[a] = other.mData[a];
            }
         }

         FloatArray(std::initializer_list<float> list): Object()
         {
            mLength = list.size();
            mData = new float[mLength];
            size_t cnt = 0;
            for(std::initializer_list<float>::iterator it = list.begin();
                  it != list.end();
                  ++it)
            {
               mData[cnt++] = *it;
            }
         }

         ~FloatArray() override
         {
            mLength = 0;
            if(mData != nullptr)delete[] mData;
         };

         inline size_t Length() const
         {
            return mLength;
         };

         inline void Sort()
         {
            if(mLength < 1)return;

            size_t n = mLength;
            do
            {
               size_t newn = 1;
               for(size_t i = 0; i < n - 1; ++i)
               {
                  size_t j = i + 1;
                  float a1 = mData[i];
                  float a2 = mData[j];
                  if(a1 > a2)
                  {
                     // Swap
                     float tmp = mData[i];
                     mData[i] = mData[j];
                     mData[j] = tmp;

                     newn = i + 1;
                  }
               }
               n = newn;
            }
            while(n > 1);
         }

         inline float Get(size_t index) const
         {
            //if(index >= mLength)
            //	throw new Exception("Array index out of bounds.");
            return mData[index];
         };

         inline void Set(size_t index, float item)
         {
            //if(index >= mLength)
            //	throw new Exception("Array index out of bounds.");
            mData[index] = item;
         };

         inline float& operator[](const size_t index) const
         {
            //if(index >= mLength)
            //	throw new Exception("Array index out of bounds.");
            return mData[index];
         }

         FloatArray& operator=(const FloatArray& another)
         {
            if(this != &another)
            {
               delete[] mData;

               mLength = another.mLength;
               mData = new float[mLength];
               for(size_t a = 0; a < mLength; a++)
               {
                  mData[a] = another.mData[a];
               }
            }

            return *this;
         }

      private:

         //! The length of the array
         size_t mLength;

         //! The data of the array
         float* mData;

   };
}

#endif
