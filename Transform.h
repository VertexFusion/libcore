////////////////////////////////////////////////////////////////////////////////////////////////////
// Name:        Transform.h
// Library:     VertexFusion Library
// Purpose:     CAD related utilities for coordinate system transformations 
//
// Author:      Uwe Runtemund (2014-today)
// Modified by:
// Created:     26.01.2014
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

#include "Vertex3.h"
#include "Matrix.h"

#ifndef jm_Transform_h
#define jm_Transform_h

namespace jm
{


	/*!
	 \brief Diese Methode rechnet WCS-Koordinaten in OCS-Koordinaten um
	 */
	Vertex3 WCSToOCS(Vertex3 wcs,
	                     Vertex3 extrusion);

	/*!
	 \brief Diese Methode rechnet OCS-Koordinaten in WCS-Koordinaten um
	 */
	Vertex3 OCSToWCS(const Vertex3& ocs,
	                  const Vertex3& extrusion);

	/*!
	 \brief Diese Methode berechnet die OCS-Transformationsmatrix.
	 Es wird der "Arbitrary Axis Algorithm" aus der DXF-Referenz angewendet.
	 */
	Matrix OCSMatrix(const Vertex3 &extrusion);

	/*!
	 \brief Diese Methode berechnet die WCS-Transformationsmatrix.
	 Es wird der "Arbitrary Axis Algorithm" aud der DXF-Referenz angewendet.
	 */
	Matrix WCSMatrix(const Vertex3 &extrusion);

	/*!
	 \brief Diese Klasse ist eine Abstrahierung der Matrix und erweitert sie um Funktionen
	 */
	struct DllExport Transform : public Matrix
	{

		/*!
		 \brief Konstruktor
		 */
		Transform();

		/*!
		 \brief Konstruktor
		 */
		Transform(const Matrix &m);

		/*!
		 \brief Diese Methode transformiert den Vektor mit der 4x4 Transformationsmatrix.
		 */
		Vertex3 Trans(const Vertex3 &vertex) const;

		/*!
		 \brief Diese Methode transformiert die Zahl mit der 4x4 Transformationsmatrix.
		 (X-Faktor wird genommen...)
		 */
		double Trans(const double &value) const;

		/*!
		 \brief Initialisiert diese Transformation als Verschiebung
		 */
		void InitMoving(const Vertex3 &distance);

		/*!
		 \brief Initialisiert diese Transformation als Skalierung
		 (um Nullpunkt) x,y,z verschiedene Faktoren
		 */
		void InitScaling(const Vertex3 &factors);

		/*!
		 \brief Initialisiert diese Transformation als Skalierung um einen Punkt
		 */
		void InitScaling(const Vertex3 &basePoint, double factor);

		/*!
		 \brief Initialisiert diese Transform als Rotationsmatrix um die Z-Achse
		 \param angle im Bogenmaß
		 */
		void InitRotationZ(double angle);

		/*!
		 \brief Initialisiert diese Transform als Rotationsmatrix
		 \param axisPoint Ortsvektor der Drehachse
		 \param axisDirection normalisierter Richtungsvektor der Drehachse
		 \param angle im Bogenmaß
		 */
		void InitRotation(const Vertex3 &axisPoint,
		                  const Vertex3 &axisDirection,
		                  double angle);
		/*!
		 \brief Initialisiert diese Transform als Reflektionsmatrix
		 \param planePoint Ortsvektor auf der Spiegelebene
		 \param planeNormal Normalenvektor der Spiegelebene
		 */
		void InitMirroring(const Vertex3 &planePoint,
		                   const Vertex3 &planeNormal);

		/*!
		 \brief Initialisiert diese Transform als WCS.Matrix
		 */
		void InitWCS(const Vertex3 &extrusion);

		/*!
		 \brief Initialisiert diese Transformation als Einheitsmatrix
		 */
		void InitIdentity();

	};

}

#endif
