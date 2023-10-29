////////////////////////////////////////////////////////////////////////////////////////////////////
// Name:        NURBS.h
// Library:     Jameo Core Library
// Purpose:     NURBS
//
// Author:      Uwe Runtemund (2013-today)
// Modified by:
// Created:     26.01.2013
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

#ifndef jm_Nurbs_h
#define jm_Nurbs_h

#include "Types.h"
#include "Vertex3.h"
#include "Object.h"

namespace jm
{

	/*!
	 \brief NURBS (nonuniform rational basis splines) sind eine verallgemeinerte Form der B-Splines.
	 Mit ihnen ist es möglich viele Kurven auch in projezierter Form zu modellieren. Die DXF-Splines
	 z.B. basieren auf diesen NURBS. Diese Klasse stellt Funktionen und Methoden zur Verfügung, um
	 mit NURBS arbeiten zu können.
	 Vorteile von NURBS (http://www-lehre.inf.uos.de/~cg/2006/PDF/kap-07.pdf)

	 - NURBS sind eine Verallgemeinerung der B-Splines. Für hi = 1 ∀i reduziert sich die NURBS-Kurve
	   zur entsprechenden B-Spline-Kurve.
	 - NURBS sind invariant bzgl. perspektivischer Projektion. Dies bedeutet, dass zur Projektion
	   einer Kurve nicht alle Kurvenpunkte projeziert werden müssen, sondern es reicht, die
		Stützpunkte zu projezieren und dann zu einer Kurve zu verbinden.
	 - NURBS sind (im Gegensatz zu nicht-rationalen B-Splines) in der Lage, Kreise zu beschreiben.
	 */
	class DllExport Nurbs: public Object
	{
		public:
			/*!
			 \brief Standardkonstruktor
			 */
			Nurbs();

			/*!
			 \brief Konstruktor
			 \param degree Grad des Polynoms
			 \param controlpoints Feld mit den Kontrollpunkten
			 \param controlCount Länge des Feldes controlpoints
			 \param knots Feld mit den Knoten
			 \param knotCount Länge des Feldes knots
			 \param weights Feld mit den Gewichtungen
			 \param weightCount Länge des Feldes weights
			 */
			Nurbs(uint32 degree,
			      Vertex3* controlpoints,
			      uint32 controlCount,
			      double* knots,
			      uint32 knotCount,
			      double* weights,
			      uint32 weightCount);

			/*!
			 \brief Destructor
			 */
			~Nurbs();

			/*!
			 \brief Gibt einen beliebigen Punkt auf der Kurve zurück.
			 \param t Die Laufvariable auf der Kurve. Im Intervall zwischen 0 und t_max
			 */
			Vertex3 GetPoint(double t);

			/*!
			 \brief Diese Methode gibt den kleinen Wert von t zurück. Also 0
			 */
			double GetStart();

			/*!
			 \brief Diese Methode gibt den größten Wert von t zurück.
			  // Warum mal so und mal so???
			  // - n−k+2
			  // - max von knot
			 */
			double GetEnd();

			/*!
			 \brief Gibt die Anzahl der Kontrollpunkte zurück
			 */
			uint32 GetControlPointCount();

		private:

			/*!
			 \brief Grad des Polynoms der NURBS
			 */
			uint32 mDegree;

			/*!
			 \brief Kontrollpunkte der Kurve
			 */
			Vertex3* mControlpoints;

			/*!
			 \brief Anzahl der Kontrollpunkte
			 */
			uint32 mControlCount;

			/*!
			 \brief Der Knotenvektor
			 */
			double* mKnots;

			/*!
			 \brief Anzahl der Knoten
			 */
			uint32 mKnotCount;

			/*!
			 \brief Die Gewichtungen. Für B-Splines sind alle 1.
			 */
			double* mWeights;

			/*!
			 \brief Anzahl der Gewichtungen
			 */
			uint32 mWeightCount;

			/*!
			 \brief Diese Methode gibt den Wert N_i,k(t) zurück
			 \param i Die Laufvariable in den Vektoren
			 \param k Der Grad des Polynoms, für den N zurückgegeben werden soll. (Ist nicht
			          zwangsläufig der Grad der NURBS)
			 \param t Die Laufvariable über die Kurve
			 */
			double N(uint32 i, uint32 k, double t);

			/*!
			 \brief Diese Methode gibt die Gewichtung der Kontrollpunkte R_i,k(t) zurück
			 \param i Die Laufvariable in den Vektoren
			 \param k Der Grad des Polynoms, für den R zurückgegeben werden soll.
			 \param t Die Laufvariable über die Kurve
			 */
			double R(uint32 i, uint32 k, double t);
	};

}

#endif
