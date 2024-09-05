////////////////////////////////////////////////////////////////////////////////////////////////////
// Name:        DiffDistance.h
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

#ifndef jm_DiffDistance_h
#define jm_DiffDistance_h

#include <vector>
#include "Object.h"

namespace jm
{

   //Vorabdeklaration
   class DiffBacktrace;
   class DiffDiag;

   /*!
    \brief This class calculates the Levenshtein distance between individual entities.

    For the distance calculation, the only decisive factor is whether the two objects are identical
    or not. The "O(|A|(1+DAB)) Levenshtein distance algorithm with lazy evaluation" is used because
    calculating a fully populated matrix is much too slow for the classical algorithm for large
    files.

    \ingroup diff
    */
   class DllExport DiffDistance
   {
      public:

          /*!
           \brief Number of calculated steps.
           */
         Integer calc;

         /*!
          \brief Constructor
          */
         DiffDistance();

         /*!
          \brief Destructor
          */
         ~DiffDistance();

          /*!
           \brief Clears the internal state to prepare for a new calculation.

           This method clears the internal state of the DiffDistance object in order to prepare for a new calculation.
           */
         void Clear();

         /*!
          \brief Adds an element to the u vector.
          */
         void addU(Object* obj);

         /*!
          \brief Adds an element to the v vector.
          */
         void addV(Object* obj);

          /*!
           \brief This method calculates the Levenshtein distance between the two vectors.
           */
         DiffBacktrace* Solve();

          /*!
           \brief Returns the Levenshtein distance between the two vectors.

           This method calculates the Levenshtein distance between the two vectors of objects.
           The Levenshtein distance is a measure of the difference between two strings or vectors.
           If the distance is 0, it means the objects are identical.

           \return The Levenshtein distance between the two vectors.
           */
         Integer GetDistance() const;

      private:

          /*!
           \brief Calculates the Levenshtein distance between two vectors of objects.

           The Levenshtein distance is a measure of the difference between two strings. In this case,
           it calculates the distance between two vectors of objects. If the distance is 0, it means
           the objects are identical.
           */
         Integer distance;

         /*!
          \brief Calculated diagonal
          */
         DiffDiag* diagonal;

         /*!
          \brief Number of rows.
          */
         Integer m;

         /*!
          \brief Number of columns
          */
         Integer n;

         /*!
          \brief Comparison vector 1
          */
         std::vector<Object*>* u;

         /*!
          \brief Comparison vector 2
          */
         std::vector<Object*>* v;

   };

}

#endif
