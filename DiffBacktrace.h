////////////////////////////////////////////////////////////////////////////////////////////////////
// Name:        DiffBacktrace.h
// Library:     VertexFusion Library
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

	//Vorabdeklaration
	class DiffDistance;
	class DiffDiag;


	/*!
	 \brief DiffBacktrace is used to indicate the "path of change".
	 \ingroup core
	 */
	class DllExport DiffBacktrace
	{
		public:

			/*!
			 \brief Standardkonstruktor
			 */
			DiffBacktrace();

			/*!
			 \brief Copykonstruktor
			 */
			DiffBacktrace(const DiffBacktrace &another);

			/*!
			 \brief Destructor
			 */
			~DiffBacktrace();

			/*!
			 \brief Schreibt das Ergebnis von Diff in den Standardausgabestrom, wenn etwas unterschiedlich ist
			 */
			void Print();

			/*!
			 \brief Diese Methode führt das Backtracing durch, um den Pfad der Veränderungen zu bekommen.
			 \param dd Zeiger auf die Diagonale, aus der das Betrachtete Element stammt.
			 \param i 0-basierter Index auf das Element in der Diagonalen.
			 */
			static DiffBacktrace* Backtrace(DiffDiag* dd, uint32 i);

			/*!
			 \brief Gibt die Diff-Operation zurück.
			 */
			DiffOperation GetOperation();

		private:

			/*!
			 \brief Die Länge des Pfades, der zurückgegangen wird
			 */
			unsigned int size;

			/*!
			 \brief Operation, die in diesem Schritt gemacht wurde
			 */
			DiffOperation operation;

			/*!
			 \brief Zeiger auf das "linke" Objekt, wenn vorhanden
			 */
			Object* obj1;

			/*!
			 \brief Zeiger auf das "rechte" Objekt, wenn vorhanden
			 */
			Object* obj2;

			/*!
			 \brief Zeiger auf das vorangegangene Element in dem Backtrace-Pfad
			 */
			DiffBacktrace* prev;

			/*!
			 \brief Zeiger auf das vorangegangene Element in dem Backtrace-Pfad
			 */
			DiffBacktrace* next;

	};

}


#endif
