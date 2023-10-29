////////////////////////////////////////////////////////////////////////////////////////////////////
// Name:        Diff.h
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

#ifndef jm_Diff_h
#define jm_Diff_h

#include "Object.h"
#include "DiffBacktrace.h"
#include "dwg/Dwg.h"

namespace jm
{


	/*!
	 \brief Diff makes the diff function generally available.
	 \ingroup core
	 */
	class DllExport Diff
	{

		public:

			/*!
			 \brief Führt die DIFF-Operation an den übergebenen Dateien aus.
			 \param f1 Die erste (linke) Datei, die zum Vergleich genommen wird.
			 \param f2 Die zweite (rechte) Datei, mit der die erste Datei verglichen wird.
			 \return Gibt die Anzahl der Unterschiede an. Wenn der Rückgabewert 0 ist, dann sind die Dateien identisch.
			 */
			static unsigned int MakeDiff(dwg::Drawing* c1, dwg::Drawing* c2);

			static void HandleEntityU(DiffDistance* dd, dwg::Entity* e);
			static void HandleEntityV(DiffDistance* dd, dwg::Entity* e);

		private:
			/*!
			 \brief Diese Helfermethode löst Entitäten ggf. auf, wenn Sie Unterelemente enhalten
			 */
			static void HandleObjectU(DiffDistance* dd, Object* e);

			/*!
			 \brief Diese Helfermethode löst Entitäten ggf. auf, wenn Sie Unterelemente enhalten
			 */
			static void HandleObjectV(DiffDistance* dd, Object* e);

	};

}

#endif
