////////////////////////////////////////////////////////////////////////////////////////////////////
// Name:        Iterator.h
// Library:     Jameo Core Library
// Purpose:     Itrator Interface
//
// Author:      Uwe Runtemund (2013-today)
// Modified by:
// Created:     29.01.2013
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

#ifndef jm_Iterator_h
#define jm_Iterator_h

#include "Types.h"

namespace jm
{
   class Object;

   /*!
    \brief The abstract class Iterator is used to provide an interface with which one can
    conveniently iterate through a list or array. It depends on the implementation which data is
    obtained.

    \note With initialisation of the list, the pointer to the elements precedes the first element,
    so that the first call to next() actually returns the first element.
    \ingroup core
    */
   class DllExport Iterator
   {

      public:
          /*!
           \brief This method checks if the list contains another element.
           \return "true" if there is at least one more element in the list, otherwise "false".
           */
         virtual bool hasNext() noexcept = 0;

          /*!
           \brief This method iterates to the next element in the list and returns it.
           \return A pointer to the next element in the list. Returns nullptr, if end if list reached
           */
         virtual Object* next() noexcept = 0;

         virtual ~Iterator() noexcept;
   };


}
#endif
