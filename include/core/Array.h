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
#include "Integer.h"
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

         Array(): Object()
         {
            mLength = 0;
            mData = new T[0];
         };

         Array(Integer length): Object()
         {
            mLength = length;
            mData = new T[length];
         };

         Array(const Array &other): Object()
         {
            mLength = other.mLength;
            mData = new T[mLength];
            for(Integer a = 0; a < mLength; a++)
            {
               mData[a] = other.mData[a];
            }
         }

         virtual ~Array()
         {
            mLength = 0;
            if(mData != NULL)delete[] mData;
         };

         inline Integer Length() const
         {
            return mLength;
         };

         inline void Sort()
         {
            if(mLength < 1)return;
            if(dynamic_cast<Comparable<T>*>(&mData[0]) == NULL)return;

            Integer n = mLength;
            do
            {
               Integer newn = 1;
               for(Integer i = 0; i < n - 1; ++i)
               {
                  Integer j = i + 1;
                  Comparable<T>* a1 = static_cast<Comparable<T>*>(&mData[i]);
                  Comparable<T>* a2 = static_cast<Comparable<T>*>(&mData[j]);
                  if(a1->compareTo(*(T *)a2) > 0)
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

         inline T Get(Integer index) const
         {
            if(index < 0 || index >= mLength)
               throw new Exception("Array index out of bounds.");
            return mData[index];
         };

         inline void Set(Integer index, T item)
         {
            if(index < 0 || index >= mLength)
               throw new Exception("Array index out of bounds.");
            mData[index] = item;
         };

         inline T &operator[](const Integer index) const
         {
            if(index < 0 || index >= mLength)
               throw new Exception("Array index out of bounds.");
            return mData[index];
         }

         Array& operator=(const Array &another)
         {
            if(this != &another)
            {
               delete[] mData;

               mLength = another.mLength;
               mData = new T[mLength];
               for(Integer a = 0; a < mLength; a++)
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
         Integer mLength;

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

         Array() : Object()
         {
            mLength = 0;
            mData = new T*[0];
         };

         Array(uint32 length) : Object()
         {
            mLength = length;
            mData = new T*[length];
         };

         Array(const Array& other) : Object()
         {
            mLength = other.mLength;
            mData = new T*[mLength];
            for(uint32 a = 0; a < mLength; a++)
            {
               mData[a] = other.mData[a];
            }
         }

         virtual ~Array()
         {
            mLength = 0;
            if(mData != NULL)delete[] mData;
         };

         inline uint32 Length() const
         {
            return mLength;
         };

         inline void Sort()
         {
            if(mLength < 1)return;
            if(mData[0] == NULL)return;

            uint32 n = mLength;
            do
            {
               uint32 newn = 1;
               for(uint32 i = 0; i < n - 1; ++i)
               {
                  uint32 j = i + 1;
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

         inline T* Get(uint32 index) const
         {
            if(index >= mLength)
               throw new Exception("Array index out of bounds.");
            return mData[index];
         };

         inline void Set(uint32 index, T* item)
         {
            if(index >= mLength)
               throw new Exception("Array index out of bounds.");
            mData[index] = item;
         };

         inline T*& operator[](const uint32 index) const
         {
            if(index >= mLength)
               throw new Exception("Array index out of bounds.");
            return mData[index];
         }


         Array& operator=(const Array& another)
         {
            if(this != &another)
            {
               delete[] mData;

               mLength = another.mLength;
               mData = new T[mLength];
               for(uint32 a = 0; a < mLength; a++)
               {
                  mData[a] = another.mData[a];
               }
            }

            return *this;
         }

      private:

         //! The length of the array.
         uint32 mLength;

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

         FloatArray(uint32 length): Object()
         {
            mLength = length;
            mData = new float[length];
         };

         FloatArray(const FloatArray &other): Object()
         {
            mLength = other.mLength;
            mData = new float[mLength];
            for(uint32 a = 0; a < mLength; a++)
            {
               mData[a] = other.mData[a];
            }
         }

         FloatArray(std::initializer_list<float> list): Object()
         {
            mLength = (uint32)list.size();
            mData = new float[mLength];
            std::initializer_list<float>::iterator it;
            uint32 cnt = 0;
            for(it = list.begin(); it != list.end(); ++it)
            {
               mData[cnt++] = *it;
            }
         }

         virtual ~FloatArray()
         {
            mLength = 0;
            if(mData != NULL)delete[] mData;
         };

         inline uint32 Length() const
         {
            return mLength;
         };

         inline void Sort()
         {
            if(mLength < 1)return;

            uint32 n = mLength;
            do
            {
               uint32 newn = 1;
               for(uint32 i = 0; i < n - 1; ++i)
               {
                  uint32 j = i + 1;
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

         inline float Get(uint32 index) const
         {
            //if(index >= mLength)
            //	throw new Exception("Array index out of bounds.");
            return mData[index];
         };

         inline void Set(uint32 index, float item)
         {
            //if(index >= mLength)
            //	throw new Exception("Array index out of bounds.");
            mData[index] = item;
         };

         inline float &operator[](const uint32 index) const
         {
            //if(index >= mLength)
            //	throw new Exception("Array index out of bounds.");
            return mData[index];
         }

         FloatArray& operator=(const FloatArray &another)
         {
            if(this != &another)
            {
               delete[] mData;

               mLength = another.mLength;
               mData = new float[mLength];
               for(uint32 a = 0; a < mLength; a++)
               {
                  mData[a] = another.mData[a];
               }
            }

            return *this;
         }

      private:

         //! The length of the array
         uint32 mLength;

         //! The data of the array
         float* mData;

   };

	/*!
	 \class StringList
	 \author Uwe Runtemund
	 \brief This is a list of strings. It provides useful methods for manipulating string lists.
	 */
   class DllExport StringList:public Object
   {

   public:

      StringList():Object()
      { 
         mData=new String[8];
         mLength=8;
         mSize=0;
      };

      void append(const jm::String &string)
      {
         checkSize(1);
         mData[mSize++]=string;
      }

      DllExport
      friend StringList& operator<< (StringList &out, const String& str)
      {
         out.append(str);
         return out;
      }

      StringList(const StringList &other): Object()
      {
         mSize=other.mSize;
         mLength = other.mLength;
         mData = new String[mLength];
         for(Integer a = 0; a < mSize; a++)
         {
            mData[a] = other.mData[a];
         }
      }

      virtual ~StringList()
      {
         mLength = 0;
         mSize=0;
         if(mData != NULL)delete[] mData;
      };

      inline Integer size() const
      {
         return mSize;
      };

      inline void sort()
      {
         if(mLength < 1)return;

         Integer n = mLength;
         do
         {
            Integer newn = 1;
            for(Integer i = 0; i < n - 1; ++i)
            {
               Integer j = i + 1;
               String* a1 = &mData[i];
               String* a2 = &mData[j];
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

      inline String get(Integer index) const
      {
         if(index < 0 || index >= mSize)
            throw new Exception("Array index out of bounds.");
         return mData[index];
      };

      inline void set(Integer index, String item)
      {
         if(index < 0 || index >= mSize)
            throw new Exception("Array index out of bounds.");
         mData[index] = item;
      };

      inline String &operator[](const Integer index) const
      {
         if(index < 0 || index >= mSize)
            throw new Exception("Array index out of bounds.");
         return mData[index];
      }

      StringList& operator=(const StringList &another)
      {
         if(this != &another)
         {
            delete[] mData;

            mLength = another.mLength;
            mSize=another.mSize;
            mData = new String[mLength];
            for(Integer a = 0; a < mSize; a++)
            {
               mData[a] = another.mData[a];
            }
         }

         return *this;
      }

      void clear()
      {
         mSize=0;
      }

   private:

      //! The length of the array.
      Integer mLength;

      //! The data size (can be less then length
      Integer mSize;

      //! The data array itself.
      String* mData;

      void checkSize(Integer size)
      {
         if(mSize+size<mLength)return;
         while(mLength<mSize+size)mLength+=8;
         String* tmp = new String[mLength];
         for(Integer index=0;index<mSize;index++)tmp[index]=mData[index];
         delete[] mData;
         mData=tmp;
      }
   };
}

#endif
