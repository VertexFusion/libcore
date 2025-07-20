////////////////////////////////////////////////////////////////////////////////////////////////////
// Name:        Diff.h
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

#ifndef jm_Diff_h
#define jm_Diff_h

#include "Object.h"
#include "DiffBacktrace.h"

/*!
 \defgroup diff Diff

 \brief A collection of classes related to the diff algorithm.
 */

namespace jm
{


   /*!
    \brief Diff makes the diff function generally available.
    \ingroup diff
    */
   class DllExport Diff
   {

      public:

         /*!
          \brief Executes the DIFF operation on the given files.
          \param f1 The first (left-hand side) file that is used for comparison.
          \param f2 The second (right-hand side) file with which the first file is compared.
          \return States the number of differences. Return value 0 means that the files are identical.
          */
         /*static unsigned int MakeDiff(dwg::Drawing* c1, dwg::Drawing* c2);

         static void HandleEntityU(DiffDistance* dd, dwg::Entity* e);
         static void HandleEntityV(DiffDistance* dd, dwg::Entity* e);
         */
      private:
         /*!
          \brief This helping method resolves, where necessary, entities if they contain subelements
          */
         static void HandleObjectU(DiffDistance* dd, Object* e);

         /*!
          \brief This helping method resolves, where necessary, entities if they contain subelements
          */
         static void HandleObjectV(DiffDistance* dd, Object* e);

   };

}

#endif
