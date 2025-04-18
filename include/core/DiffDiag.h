////////////////////////////////////////////////////////////////////////////////////////////////////
// Name:        DiffDiag.h
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


#ifndef jm_DiffDiag_h
#define jm_DiffDiag_h

#include <vector>
#include "Object.h"
#include "DiffTypes.h"

namespace jm
{

   class DiffDistance;

   /*!
    \brief This class represents a diagonal in the diff algorithm.
    \ingroup diff
    */
   class DllExport DiffDiag
   {

      public:

         DiffDiag(DiffDistance* dist,
                  std::vector<Object*>* u,
                  std::vector<Object*>* v,
                  int64 offset);

         ~DiffDiag();

         DiffDiag* above();
         DiffDiag* below();

         int64 upperEntry(int64 i);
         int64 leftEntry(int64 i);

         int64 entry(int64 j);

         Object* objectU(int64 i);
         Object* objectV(int64 i);

         int64 offset();


      private:

         /*!
          \brief This variable stores the offset of the diagonal.
          Diagonals start at u[0], v[abs(offset)].
          Diagonals below the middle have negative offsets.
          */
         int64 mOffset;

         /*!
          \brief Pointer to the first vector for comparison.
          */
         std::vector<Object*>* mU;

         /*!
          \brief Pointer to the second vector for comparison.
          */
         std::vector<Object*>* mV;

         /*!
          \brief Linked List
          */
         DiffDiag* mBelow;
         DiffDiag* mAbove;

         /*!
          \brief This vector stores the elements of the diagonal.
          */
         std::vector<int64>* mElements;

         /*!
          \brief Pointer to DiffDistance object to determine the number of calculated values.
          */
         DiffDistance* mDistance;

   };

}

#endif
