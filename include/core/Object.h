////////////////////////////////////////////////////////////////////////////////////////////////////
// Name:        Object.h
// Library:     Jameo Core Library
// Purpose:     Declaration of Object class
//
// Author:      Uwe Runtemund (2014-today)
// Modified by:
// Created:     20.04.2014
//
// Copyright:   (c) 2014 Jameo Software, Germany. https://jameo.de
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

#ifndef jm_Object_h
#define jm_Object_h

#include "Types.h"
#include "DiffTypes.h"

namespace jm
{
   class AutoreleasePool;
   class String;

   /*!
    \brief Most objects are derived from this class. This makes it possible to simplify the API, as
    object pointers can passed and not just void*.
    */
   class DllExport Object
   {

      public:

         /*!
          \brief Constructor.
          */
         Object() noexcept;

         /*!
          \brief Destructor.
          */
         virtual ~Object() noexcept;

         /*!
          \brief Decreases the reference counter and releases the object immediately when the
          reference counter becomes 0.
          */
         void release() noexcept;

         /*!
          \brief Increases the reference counter of this object by 1.
          \note An object is automatically released when the reference counter becomes 0.
          \return Reference to this object.
          */
         Object* retain() noexcept;

         /*!
          \brief Same function as release(), but releases the object with a delay if the reference
          counter is 0. AutoreleasePool::drain() must be called in the to release the object.
          \return Reference to this object.
          */
         Object* autorelease() noexcept;

         /*!
          \brief Returns the value of the reference counter.
          */
         int32 referenceCount() const noexcept;

         /*!
          \brief Comparison of objects.
          \param other The object to compare with.
          */
         virtual bool equals(const Object* other) const;

         /*!
          \brief Returns the display name of the object intended to present to a user.

          This method should be implemented by objects that want to present the name of the object
          to the user of an application. For example the diff-algorithm uses this or also the dwg
          objects.
          */
         virtual String displayName() const;

         /*!
          \brief Output method for outputting the diff results for the diff algorithm.
          \param operation The calculated diff operation.
          \param other The object to compare with.
          */
         virtual void printDiffInfo(DiffOperation operation, Object* other) const;

         // Methods for flagging the object
         void setHighBit(bool status) noexcept;
         bool highBit()const noexcept;

      private:

         /*!
          \brief Reference counter for reference counting.

          \note the highest bit is a modified flag for undo management
          */
         int32 mRefCount;

         /*!
          \brief The auto release pool for this object.
          */
         AutoreleasePool* mPool;

   };
}

#endif
