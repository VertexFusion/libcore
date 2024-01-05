////////////////////////////////////////////////////////////////////////////////////////////////////
// Name:        Geometry.h
// Library:     Jameo Core Library
// Purpose:     Usefull CAD and geometry functions
//
// Author:      Uwe Runtemund (2012-today)
// Modified by:
// Created:     30.10.2012
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

#ifndef jm_Geometry_h
#define jm_Geometry_h

#include "Vertex2.h"
#include "Vertex3.h"

namespace jm
{
	/*!
	 \brief Diese Methode berechnet den Schnittpunkt einer Geraden mit einer Ebene, wobei die
	 Normalenform benutzt wird.
	 \param planePosition Ortsvektor der Ebene
	 \param normal Normalenvektor der Ebene
	 \param linePosition Ortsvektor der Geraden.
	 \param direction Richtungsvektor der Geraden,
	 \param extend Die Geradengleichung kann ein Liniensegment definieren, wenn man annnimmt, dass
	 linePosition, der Anfangspunkt einer Linie und (linePosittion+direction) der Endpunkt der Linie
	 ist. Wenn extend = true ist, dann wird der Schnittpunkt auf der mathematischen Gerade berechnet,
	 Wenn das falsch ist, wird der Schnittpunkt auf dem Geradenstück nur gewählt. Das heißt, wenn der
	 Punkt außerhalb liegt, wird einer der Endpunkte dann als "Schnittpunkt" angegeben. Dieses
	 "Feature" wird vor allem benötigt, wenn man den kürzesten Abstand zu Liniensegmenten haben
	 möchte. Wenn es keinen Schnittpunkt gibt, wird ein ungültiver Vektor zurückgegeben.
	 */
	DllExport
	Vertex3 IntersectionPointLineAndPlane(const Vertex3 &planePosition,
	                                      const Vertex3 &normal,
	                                      const Vertex3 &linePosition,
	                                      const Vertex3 &direction,
	                                      bool extend);

	/*!
	 \brief Diese Methode berechnet den Punkt auf der Ebene mit dem minimalen Abstand zwischen dem
	 Punkt und der Ebene.
	 \param point Der 3D-Raumpunkt, von dem der Abstand bestimmt werden soll
	 \param position Ortsvektor bzw. beliebiger Punkt auf der Ebene
	 \param normal Normalenvektor, senkrecht auf der Ebene
	 \return Den Punkt auf der Ebene mit dem minimalen (lotrechten) Abstand vom Punkt zur Ebene
	 */
	DllExport
	Vertex3 ClosestPointOnPlane(const Vertex3 &point,
	                            const Vertex3 &position,
	                            const Vertex3 &normal);

	/*!
	 \brief Diese Methode berechnet den Punkt auf der Geraden mit dem minimalen Abstand zwischen
	 dem Punkt und der Geraden. Der Verbindungslinie zwischen point und dem Ergebnis steht senkrecht
	 auf der Linie.
	 \param point  Der 3D-Raumpunkt, von dem der Abstand bestimmt werden soll
	 \param position Ortsvektor bzw. beliebiger Punkt auf der Geraden
	 \param direction Richtungsvektor der Geradem
	 \return Den Punkt auf der Geraden mit dem kürzesten Abstand zwischen Linie und Punkt
	 */
	DllExport
	Vertex3 ClosestPointOnLine(const Vertex3 &point,
	                           const Vertex3 &position,
	                           const Vertex3 &direction);

	/*!
	 \brief Diese Methode berechnet den Punkt auf der 2. Geraden mit dem minimalen Abstand
	 zwischen beiden Geraden. Der Verbindungslinie zwischen point und dem Ergebnis steht senkrecht
	 auf der Linie.
	 \param position1 Ortsvektor bzw. beliebiger Punkt auf der 1. Geraden
	 \param direction1 Richtungsvektor der 1. Geraden
	 \param position2 Ortsvektor bzw. beliebiger Punkt auf der 2. Geraden
	 \param direction2 Richtungsvektor der 2. Geraden
	 \return Den Punkt auf der 2. Geraden mit dem kürzesten Abstand zwischen Linie und Linie
	 */
	DllExport
	Vertex3 ClosestPointOnLine(const Vertex3 &position1,
	                           const Vertex3 &direction1,
	                           const Vertex3 &position2,
	                           const Vertex3 &direction2);

	/*!
	 \brief Diese Methode berechnet den Punkt auf der Geraden mit dem minimalen Abstand zwischen
	 dem Punkt und der Geraden.
	 \param point  Der 3D-Raumpunkt, von dem der Abstand bestimmt werden soll
	 \param lineStart Startpunkt der Linie
	 \param lineEnd Endpunkt der Linie
	 \param extend Status, ob der Schnittpunkt auch über die Linienenden hinaus bestimmt werden soll?
	 Bei "Falsch" wird NAN zurückgegeben
	 \return Den Punkt auf der Geraden mit dem kürzesten Abstand zwischen Linie und Punkt
	 */
	DllExport
	Vertex3 ClosestPointOnLine(const Vertex3 &point,
	                           const Vertex3 &lineStart,
	                           const Vertex3 &lineEnd,
	                           bool extend);

	/*!
	 \brief Diese Methode berechnet minimalen Abstand vom gegebenen Punkt auf den Kreis
	 \param point Der 3D-Raumpunkt, von dem der Abstand bestimmt werden soll
	 \param center Der Mittelpunkt des Kreises
	 \param radius Der Radius des Kreises
	 \param normal Der Normalenvektor. Steht senkrecht auf Kreisebene
	 \return Den Punkt auf dem Kreios mit dem kürzesten Abstand zwischen Linie und Kreis
	 */
	DllExport
	Vertex3 ClosestPointOnCircle(const Vertex3 &point,
	                             const Vertex3 &center,
	                             double radius,
	                             const Vertex3 &normal);

	/*!
	 \brief Diese Methode berechnet den Punkt auf der Geraden mit dem  minimalen Abstand zwischen
	 dem Punkt und der Ebene.
	 \param point Der 3D-Raumpunkt, von dem der Abstand bestimmt werden soll
	 \param position Ortsvektor bzw. beliebiger Punkt auf der Ebene
	 \param normal Normalenvektor, senkrecht auf der Ebene
	 \return Den minimalen (lotrechten) Abstand vom Punkt zur Ebene
	 */
	DllExport
	double DistancePointToPlane(const Vertex3 &point,
	                            const Vertex3 &position,
	                            const Vertex3 &normal);

	/*!
	 \brief Diese Methode berechnet den minimalen Abstand zwischen den beiden Punkten.
	 \param point1 Der erste Punkt.
	 \param point2 Der zweite Punkt
	 \return Den Abstand vom ersten zum zweiten Punkt
	 */
	DllExport
	double DistancePointToPoint(const Vertex3 &point1,
	                            const Vertex3 &point2);

	/*!
	 \brief Diese Methode berechnet den minimalen Abstand zwischen den beiden Punkten.
	 \param point1 Der erste Punkt.
	 \param point2 Der zweite Punkt
	 \return Den Abstand vom ersten zum zweiten Punkt
	 */
	DllExport
	double DistancePointToPoint(const Vertex2 &point1,
	                            const Vertex2 &point2);

	/*!
	 \brief Diese Methode berechnet den minimalen Abstand zwischen dem Punkt und der Geraden.
	 \param point  Der 3D-Raumpunkt, von dem der Abstand bestimmt werden soll
	 \param  position Ortsvektor bzw. beliebiger Punkt auf der Geraden
	 \param direction Richtungsvektor der Geradem
	 \return Den kürzesten Abstand zwischen Linie und Punkt
	 */
	DllExport
	double DistancePointToLine(const Vertex3 &point,
	                           const Vertex3 &position,
	                           const Vertex3 &direction);

	/*!
	 \brief Diese Methode berechnet den minimalen Abstand zwischen dem Punkt und dem
	 Linienelement.
	 \param point  Der 3D-Raumpunkt, von dem der Abstand bestimmt werden soll
	 \param lineStart Startpunkt der Linie
	 \param lineEnd Endpunkt der Linie
	 \param extend Status, ob der Schnittpunkt auch über die Linienenden hinaus bestimmt werden soll?
	 Bei "Falsch" wird ggf. ein Endpunkt der Linie genommen
	 \return Den kürzesten Abstand zwischen Linie und Punkt
	 */
	DllExport
	double DistancePointToLine(const Vertex3 &point,
	                           const Vertex3 &lineStart,
	                           const Vertex3 &lineEnd,
	                           bool extend);

	/*!
	 \brief Diese Methode berechnet minimalen Abstand vom gegebenen Punkt auf den Kreis
	 \param point Der 3D-Raumpunkt, von dem der Abstand bestimmt werden soll
	 \param center Der Mittelpunkt des Kreises
	 \param radius Der Radius des Kreises
	 \param normal Der Normalenvektor. Steht senkrecht auf Kreisebene
	 \return Den kürzesten Abstand zwischen Linie und Kreis
	 */
	DllExport
	double DistancePointToCircle(const Vertex3 &point,
	                             const Vertex3 &center,
	                             double radius,
	                             const Vertex3 &normal);

	/*!
	 \brief Diese Methode berechnet den minimalen Abstand zwischen den Geraden.
	 \param  position1 Ortsvektor bzw. beliebiger Punkt auf der 1. Geraden
	 \param direction1 Richtungsvektor der 1. Geraden
	 \param  position2 Ortsvektor bzw. beliebiger Punkt auf der 2. Geraden
	 \param direction2 Richtungsvektor der 2. Geraden
	 \return Den kürzesten Abstand zwischen den Geraden
	 */
	DllExport
	double DistanceLineToLine(const Vertex3 &position1,
	                          const Vertex3 &direction1,
	                          const Vertex3 &position2,
	                          const Vertex3 &direction2);

	/*!
	 \brief Diese Methode prüft unter Berücksichtigung von resabs, ob der Punkt auf der Ebene
	 liegt.
	 \param point Der 3D-Raumpunkt, von dem der Abstand bestimmt werden soll
	 \param  position Ortsvektor bzw. beliebiger Punkt auf der Ebene
	 \param normal Normalenvektor, senkrecht auf der Ebene
	 \param maxDistance Der max. tolerierte Abstand zur Ebene
	 \return "wahr", wenn der Punkt auf der Ebene liegt
	 */
	DllExport
	bool IsOnPlane(const Vertex3 &point,
	               const Vertex3 &position,
	               const Vertex3 &normal,
	               double maxDistance = 0.0);

	/*!
	 \brief Diese Methode prüft unter Berücksichtigung von resabs, ob der Punkt auf der Geraden
	 liegt.
	 \param point  Der 3D-Raumpunkt, von dem der Abstand bestimmt werden soll
	 \param  position Ortsvektor bzw. beliebiger Punkt auf der Geraden
	 \param direction Richtungsvektor der Geradem
	 \return "wahr", wenn der Punkt auf der Geraden liegt
	 */
	DllExport
	bool IsOnLine(const Vertex3 &point,
	              const Vertex3 &position,
	              const Vertex3 &direction);

	/*!
	 \brief Diese Methode prüft unter Berücksichtigung von resabs, ob der Punkt auf dem
	 Linienelement liegt.
	 \param point  Der 3D-Raumpunkt, von dem der Abstand bestimmt werden soll
	 \param lineStart Startpunkt der Linie
	 \param lineEnd Endpunkt der Linie
	 \param extend Status, ob der Schnittpunkt auch über die Linienenden hinaus bestimmt werden soll?
	 Bei "Falsch" wird ggf. ein Endpunkt der Linie genommen
	 \return "wahr", wenn der Punkt auf dem Linienelement liegt
	 */
	DllExport
	bool IsOnLine(const Vertex3 &point,
	              const Vertex3 &lineStart,
	              const Vertex3 &lineEnd,
	              bool extend);

	/*!
	 \brief Diese Methode prüft unter Berücksichtigung von resabs, ob der Punkt auf dem Kreis
	 liegt.
	 \param point Der 3D-Raumpunkt, von dem der Abstand bestimmt werden soll
	 \param center Der Mittelpunkt des Kreises
	 \param radius Der Radius des Kreises
	 \param normal Der Normalenvektor. Steht senkrecht auf Kreisebene
	 \return "wahr", wenn der Punkt auf dem Kreis liegt
	 */
	DllExport
	bool IsOnCircle(const Vertex3 &point,
	                const Vertex3 &center,
	                double radius,
	                const Vertex3 &normal);

	/*!
	 \brief Diese Methode prüft unter Berücksichtigung von resabs, ob beide Punkte identisch sind.
	 \discussion Die Punkte sind identisch, wenn der Abstand beider kleiner resabs ist.
	 \param point1 Der 1. 3D-Raumpunkt.
	 \param point2 Der 2. 3D-Raumpunkt.
	 \return "wahr", wenn beide Punkte aufeinander liegen
	 */
	DllExport
	bool IsSamePoint(const Vertex3 &point1,
	                 const Vertex3 &point2);

	/*!
	\brief Diese Methode berechnet den zweidimensionalen Schnittpunkt der beiden Geraden,
	 die durch die Anfangspunkte und Richtungsvektoren definiert sind.
	 \param position1 Ortsvektor der ersten Gerade.
	 \param direction1 Richtungsvektor der ersten Geraden.
	 \param position2 Ortsvektor der zweiten Geraden.
	 \param direction2 Richtungsvektor der zweiten Geraden.
	 \return Den Schnittpunkt der beiden Geraden. Im Falle der Kolinearität (parallele Linien) hat
	 der Punkt die Werte NAN
	 */
	DllExport
	Vertex2 IntersectionPoint(const Vertex2 &position1,
	                          const Vertex2 &direction1,
	                          const Vertex2 &position2,
	                          const Vertex2 &direction2);

	/*!
	\brief Diese Methode berechnet den dreidimensionalen Schnittpunkt der beiden Geraden,
	 die durch die Anfangspunkte und Richtungsvektoren definiert sind.
	 \param position1 Ortsvektor der ersten Gerade.
	 \param direction1 Richtungsvektor der ersten Geraden.
	 \param position2 Ortsvektor der zweiten Geraden.
	 \param direction2 Richtungsvektor der zweiten Geraden.
	 \return Den Schnittpunkt der beiden Geraden. Im Falle der Kolinearität (parallele Linien), oder
	 windschiefer Geraten hat der Punkt die Werte NAN
	 */
	DllExport
	Vertex3 IntersectionPoint(const Vertex3 &position1,
	                          const Vertex3 &direction1,
	                          const Vertex3 &position2,
	                          const Vertex3 &direction2);

	/*!
	 \brief Diese Methode prüft, ob sich zwei Linien zwischen Ihren Endpunkten schneiden/kreuzen.
	 Es handelt sich um ein ebenes Problem
	 \param start1 Startpunkt der ersten Gerade.
	 \param end1 Endpunkt der ersten Geraden.
	 \param start2 Startpunkt der zweiten Geraden.
	 \param end2 Endpunkt der zweiten Geraden.
	 \return "wahr", wenn sich die Linien zwischen den Endpunkten schneiden. Andernfalls "falsch".
	 */
	DllExport
	bool Crosses(const Vertex2 &start1,
	             const Vertex2 &end1,
	             const Vertex2 &start2,
	             const Vertex2 &end2);

	/*!
	 \brief Diese Methode prüft, ob ein Strahl (Linie) eine Linie zwischen oder auf Ihren
	 Endpunkten schneidet. Dabei ist entscheidend in welche Richtung der Strahl zeigt. Diese Methode
	 wird verwendet, um Linien zu Dehnen, zu Kürzen, Schraffuren zu zeichnen usw. Daher ist dies eine
	 essentielle Methode für CAD-Arbeiten. Wenn der Strahl die Linie zwischen oder auf den Endpunkten
	 schneidet, wird der Schnittpunkt zurückgegeben.
	 \param rayorigin Die Strahlquelle. Also der Punkt, ab dem geschaut werden soll, ob sich die
	 Linien kreuzen. (Ortsvektor der Geraden)
	 \param direction Der Richtungsvektor, in die der Strahl zeigt.
	 \param start Startpunkt der Linie, mit der verglichen wird.
	 \param end Endpunkt der Linie, mit der verglichen wird.
	 \return Den definierten Vektor, wenn der Schnittpunkt exitiert. Wenn der Schnittpunkt nicht
	 existiert, hat der Vektor NaN als Einträge.
	 */
	DllExport
	Vertex2 ExtensionPointOnLine(const Vertex2 &rayorigin,
	                             const Vertex2 &direction,
	                             const Vertex2 &start,
	                             const Vertex2 &end);

	/*!
	 \brief Diese Methode prüft, ob ein Strahl (Linie) einen Kreisbogen schneidet. Dabei
	 ist entscheidend in welche Richtung der Strahl zeigt. Diese Methode wird verwendet, um Linien zu
	 Dehnen, zu Kürzen, Schraffuren zu zeichnen usw. Daher ist dies eine essentielle Methode für
	 CAD-Arbeiten. Wenn der Strahl den Kreisbogen zwischen oder auf den Endpunkten schneidet, wird
	 der Schnittpunkt zurückgegeben. Es wird der nächste Schnittpunkt zurückgegeben, sollte der
	 Strahl den Kreisbogen zweimal schneiden.
	 \param rayorigin Die Strahlquelle. Also der Punkt, ab dem geschaut werden soll, ob sich die
	 Linien kreuzen. (Ortsvektor der Geraden)
	 \param direction Der Richtungsvektor, in die der Strahl zeigt.
	 \param center Kreismittelpunkt
	 \param start Der Startwinkel des Kreisbogens im Bogenmaß
	 \param end Der Endwinkel des Kreisbogens im Bogenmaß
	 \return Den definierten Vektor, wenn der Schnittpunkt exitiert. Wenn der Schnittpunkt nicht
	 existiert, hat der Vektor NaN als Einträge.
	 */
	DllExport
	Vertex2 ExtensionPointOnArc(const Vertex2 &rayorigin,
	                            const Vertex2 &direction,
	                            const Vertex2 &center,
	                            double radius,
	                            double start,
	                            double end);

	/*!
	 \brief Diese Methode prüft, ob ein Strahl (Linie) einen Ellipsenbogen schneidet. Dabei
	 ist entscheidend in welche Richtung der Strahl zeigt. Diese Methode wird verwendet, um Linien zu
	 Dehnen, zu Kürzen, Schraffuren zu zeichnen usw. Daher ist dies eine essentielle Methode für
	 CAD-Arbeiten. Wenn der Strahl den Ellipsenbogen zwischen oder auf den Endpunkten schneidet, wird
	 der Schnittpunkt zurückgegeben. Es wird der nächste Schnittpunkt zurückgegeben, sollte der
	 Strahl den Ellipsenbogen zweimal schneiden.
	 \param rayorigin Die Strahlquelle. Also der Punkt, ab dem geschaut werden soll, ob sich die
	 Linien kreuzen. (Ortsvektor der Geraden)
	 \param direction Der Richtungsvektor, in die der Strahl zeigt.
	 \param center Ellipsenmittelpunkt
	 \param mainAxis Haupachsenrichtung und Länge der Hauptachse (vom Mittelpunkt aus)
	 \param minorAxisRatio Nebenachsenfaktor
	 \param start Der Startwinkel des Kreisbogens im Bogenmaß
	 \param end Der Endwinkel des Kreisbogens im Bogenmaß
	 \return Den definierten Vektor, wenn der Schnittpunkt exitiert. Wenn der Schnittpunkt nicht
	 existiert, hat der Vektor NaN als Einträge.
	 */
	DllExport
	Vertex2 ExtensionPointOnEllipse(const Vertex2 &rayorigin,
	                                const Vertex2 &direction,
	                                const Vertex2 &center,
	                                const Vertex2 &mainAxis,
	                                double minorAxisRatio,
	                                double start,
	                                double end);

	/*!
	 \brief Diese Methode berechnet die Winkelhalbierende zwischen den beiden Richtungsvektoren um einen gemeinsamen
	 Zentralpunkt. Die Länge der Resultierenden ist nicht norrmiert.
	 */
	DllExport
	Vertex3 AngleBisector(const Vertex3 &direction1,
	                      const Vertex3 &direction2);
	/*!
	 \brief Diese Methode berechnet die Winkelhalbierende zwischen den beiden Richtungsvektoren um einen gemeinsamen
	 Zentralpunkt. Die Länge der Resultierenden ist nicht norrmiert.
	 */
	DllExport
	Vertex2 AngleBisector(const Vertex2 &direction1,
	                      const Vertex2 &direction2);
	
	/*!
	 \brief Calculates the circle parameters centre point and radius given by the 3 points.
	 */
	jm::VxfErrorStatus CircleParameterBy3Points(Vertex2 &centre, double &radius,
															  const Vertex2 &p1,
															  const Vertex2 &p2,
															  const Vertex3 &p3);

}

#endif
