////////////////////////////////////////////////////////////////////////////////////////////////////
// Name:        Vertex2.h
// Library:     VertexFusion Library
// Purpose:     2D-Vector
//
// Author:      Uwe Runtemund (2013-today)
// Modified by:
// Created:     16.01.2013
//
// Copyright:   (c) 2012 Jameo Software, Germany. https://jameo.de
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

#ifndef jm_Vertex2_h
#define jm_Vertex2_h

#include "Types.h"

namespace jm
{
	class Vertex3;

	/*!
	 \brief A two dimensional vector. Owns special functions for 3D space.
	 */
	class DllExport Vertex2
	{
		public:

			/*!
			 \brief X component of vector.
				 \note We need fast acces to this value and other protection measures are not necessary.
				 So we leave it public.
			 */
			double x;

			/*!
			 \brief Y component of vector.
				 \note We need fast acces to this value and other protection measures are not necessary.
				 So we leave it public.
			 */
			double y;


			/*!
			 \brief Konstruktor erzeugt Nullvektor.
			 */
			Vertex2();

			/*!
			 \brief Konstruktor erzeugt beliebigen Vektor
			 \param x X-Komponente des Vektors
			 \param y Y-Komponente des Vektors
			 */
			Vertex2(double x, double y);
		
			Vertex2(const Vertex3 &v3);

			/*!
			 \brief Diese Methode gibt den Betrag des Vektors zurück. Der Betrag entspricht der Länge.
			 */
			double Abs() const;

			/*!
			 \brief Diese Methode normalisiert den Vektor. Ein normalisierter Vektor besitzt die Länge 1.
			 */
			void Normalize();
			Vertex2 Normalized()const;

			/*!
			 \brief Gibt das Kreuzprodukt aus diesem Vektor multipliziert mit einem anderen zurück.
			 */
			double CrossProduct(const Vertex2 &another) const;

			/*!
			 \brief Gibt das Skalarprodukt eines Vektors mit einem anderen zurück
			 */
			double DotProduct(const Vertex2 &another) const;

			/*!
			 \brief Diese Methode berechnet, ob die beiden Vektoren kollinear sind.
			   Also ob beide Vektoren parallel sind.
			 */
			bool IsCollinear(const Vertex2 &another) const;

			/*!
			 \brief Diese Methode berechnet, ob die beiden Vektoren orthogonal sind.
			 Also ob sie senktrecht aufeinander stehen
			 */
			bool IsOrthogonal(const Vertex2 &another) const;

			/*!
			 \brief Gibt den Winkel von einem zum anderen Winkel zurück.
			 \return Winkel im Bogenmaß zwischen 0 und pi (0 - 180°)
			 */
			double AngleTo(const Vertex2 &another) const;

			/*!
			 \brief Diese Methode berechnet, ob dieser Vector "rechts" also im Uhrzeigersinn neben dem anderen Vector liegt
			 */
			bool IsRightTo(const Vertex2 &another) const;

			/*!
			 \brief Diese Methode berechnet, ob dieser Vector "links" also geden den Uhrzeigersinn neben dem anderem Vector liegt
			 */
			bool IsLeftTo(const Vertex2 &another) const;

			/*!
			 \brief Diese Methode gibt wahr zurück, wennd er Vektor definiert ist, also beie Zahlen nicht
			 NAN sind.
			 */
			bool IsValid() const;

			/*!
			 \brief Diese Methode rotiert den Vektor um die Z-Achse mit dem angegebenen Winkel.
			 \param angle Der Rotationswinkel im mathematisch positivem Sinn im Bogenmaß.
			 */
			Vertex2& Rotate(double angle);

			Vertex2 &operator+=(const Vertex2 &another);

			Vertex2 &operator-=(const Vertex2 &another);

			DllExport
			friend std::ostream& operator<< (std::ostream& out, const Vertex2 & vertex);
	};


	/*!
	 \brief Implementierung des Operators +
	 */
	DllExport
	const Vertex2 operator+(const Vertex2 &v1, const Vertex2 &v2);

	/*!
	 \brief Implementierung des Operators -
	 */
	DllExport
	const Vertex2 operator-(const Vertex2 &v1, const Vertex2 &v2);

	/*!
	 \brief Implementierung des Operators *
	 */
	DllExport
	const Vertex2 operator*(const double &d, const Vertex2 &v);


	/*!
	 \brief Implementierung des Operators -=
	 */
	DllExport
	bool operator!=(Vertex2 const &v1, Vertex2 const &v2);

	/*!
	 \brief Diese Methode löst ein lineares Gleichungssystem mit zwei Unbekannten:
	  r.x = x * a.x + y * b.x
	  r.y = x * a.y + y * b.y
	 Das System wird nach x und y augelöst und gelöst.
	 Matrixschreibweise:
		  a   b                 r
		| a.x b.x | * | x | = | r.x |
		| a.y b.y |   | y |   | r.y |
	 */
	DllExport
	Vertex2 SolveLinearSystem(Vertex2 a, Vertex2 b, Vertex2 r);
}

#endif
