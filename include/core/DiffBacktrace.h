////////////////////////////////////////////////////////////////////////////////////////////////////
// Name:        DiffBacktrace.h
// Library:     Jameo Core Library
// Purpose:     Diff Algorithm
//
// Author:      Uwe Runtemund (2013-today)
// Modified by:
// Created:     17.12.2013
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


#ifndef jm_DiffBacktrace_h
#define jm_DiffBacktrace_h

#include "Object.h"
#include "DiffTypes.h"

namespace jm
{

   // Forward declaration
   class DiffDistance;
   class DiffDiag;


   /*!
    \brief DiffBacktrace is used to indicate the "path of change".
    \ingroup diff
    */
   class DllExport DiffBacktrace
   {
      public:

         /*!
          \brief Default constructor
          */
         DiffBacktrace();

         /*!
          \brief Copy constructor
          */
         DiffBacktrace(const DiffBacktrace& another);

         /*!
          \brief Destructor
          */
         ~DiffBacktrace();

         /*!
          \brief Writes the result of Diff to the standard output stream if something is different
          */
         void print();

         /*!
          \brief This method performs the backtracing to obtain the path of changes.
          \param dd Pointer to the diagonal from which the considered element originates.
          \param i 0-based index of the element in the diagonal.
          */
         static DiffBacktrace* backtrace(DiffDiag* dd, int64 i);

         /*!
          \brief Returns the diff operation.
          */
         DiffOperation operation() const;

      private:

         //! The length of the path being backtraced
         int64 mSize;

         //! Operation performed in this step
         DiffOperation mOperation;

         //! Pointer to the "left" object, if available
         Object* mObj1;

         //! Pointer to the "right" object, if available
         Object* mObj2;

         //! Pointer to the previous element in the backtrace path
         DiffBacktrace* mPrev;

         //! Pointer to the next element in the backtrace path
         DiffBacktrace* mNext;

   };

}


#endif
