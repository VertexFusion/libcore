////////////////////////////////////////////////////////////////////////////////////////////////////
// Name:        Geometry.cpp
// Library:     Jameo Core Library
// Purpose:     Useful CAD and geometry functions
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


#include "Precompiled.h"

using namespace jm;

Vertex3 jm::IntersectionPointLineAndPlane(const Vertex3 &planePosition,
      const Vertex3 &normal,
      const Vertex3 &linePosition,
      const Vertex3 &direction,
      bool extend)
{
	if(normal.IsNull())
	{
		return Vertex3(NAN, NAN, NAN);
	}
	if(direction.IsNull())
	{
		return Vertex3(NAN, NAN, NAN);
	}

	// Why was that here? Must the plane normal vector not be perpendicular to the direction vector?
	// stehen? What if the line lies in the plane?
	if(normal.IsOrthogonal(direction))
	{
		return Vertex3(NAN, NAN, NAN);
	}

	double lambda = (normal.x * (planePosition.x - linePosition.x)
	                 + normal.y * (planePosition.y - linePosition.y)
	                 + normal.z * (planePosition.z - linePosition.z))
	                / (direction.x * normal.x + direction.y * normal.y + direction.z * normal.z);


	if(!extend)
	{
		//Startpunkt hat implizit lambda=0
		//Endpunkt hat implizit lambda=1
		//\todo Es sollte überlegt werden, ob es eine Extraoption ist, dass der Punkt auf den Endpunkt gesetzt wird
		//if( IsLess( lambda , 0 ) )lambda = 0;
		//else if( IsGreater( lambda , 1 ) ) lambda = 1;
		if(IsLess(lambda, 0))return Vertex3(NAN, NAN, NAN);
		else if(IsGreater(lambda, 1))return Vertex3(NAN, NAN, NAN);
	}

	return linePosition + direction * lambda;
}

Vertex3 jm::ClosestPointOnPlane(const Vertex3 &point,
                                const Vertex3 &position,
                                const Vertex3 &normal)
{
	//Vorgehen:
	// 1. Die Ebene ist bereits durch die Normalenform (position, normal) definiert.
	// -> E: ( x - position ) * normal
	// 2. Es wird eine Gerade definiert, die Senkrecht auf der Ebene steht und durch P geht
	// -> g: point + lambda * normal

	return IntersectionPointLineAndPlane(position, normal, point, normal, true);
}

Vertex3 jm::ClosestPointOnLine(const Vertex3 &point,
                               const Vertex3 &position,
                               const Vertex3 &direction)
{
	//Vorgehen
	// 1. Definiere eine Ebene, die senkrecht auf der Gerraden steht und im Punkt p liegt.
	// -> E: ( x - point ) * direction
	// 2. Die Gerade ist bereits durch Ihre Geradengleichung definiert.
	// -> g: position + lanbda * direction

	return IntersectionPointLineAndPlane(point, direction, position, direction, true);
}

Vertex3 jm::ClosestPointOnLine(const Vertex3 &position1,
                               const Vertex3 &direction1,
                               const Vertex3 &position2,
                               const Vertex3 &direction2)
{
	//Voraussetungen
	// - Die Geraden sind nicht parallel und windschief

	//Vorgehen
	// 1. Bilde 1. Ebene, bei der die beiden Richtungsvektoren die Ebene aufspannen. Dadurch ist der
	//    Normalenvektor der Ebene, der senkrechte Vektor zwischen beiden Linien
	//    -> normal1 = direction1 X direction2
	// 2. Bilde 2. Ebene, wobei der Normalenvektor der 1. Ebene und der Richtungsvektor der 1.
	//    Geraden die Ebene Aufspannen
	//    -> normal2 = position1 X normal1
	//    -> E: ( x - position1) * normal2
	// 3. Der Schnittpunkt der 2. Geraden mit der 2. Hilfsebene ist der Lotfußpunkt
	Vertex3 normal1 = direction1.CrossProduct(direction2);
	Vertex3 normal2 = direction1.CrossProduct(normal1);
	return IntersectionPointLineAndPlane(position1, normal2, position2, direction2, true);
}


Vertex3 jm::ClosestPointOnLine(const Vertex3 &point,
                               const Vertex3 &lineStart,
                               const Vertex3 &lineEnd,
                               bool extend)
{
	// Vorgehen
	// 1. Definiere eine Geradengleichung für die Linie:
	// 1a. Dazu definiere einen Richtungsvektor:
	//	direction = lineEnd - lineStart.
	// -> g: lineStart + lambda * direction
	// 2. Definiere eine Ebene, die Senkrecht auf der Geraden steht und im Punkt p liegt
	// -> E: ( x - point ) * direction

	Vertex3 direction = lineEnd - lineStart;
	return IntersectionPointLineAndPlane(point, direction, lineStart, direction, extend);
}

Vertex3 jm::ClosestPointOnCircle(const Vertex3 &point,
                                 const Vertex3 &center,
                                 double radius,
                                 const Vertex3 &normal)
{
	if(IsEqual(radius, 0.0)) return Vertex3(NAN, NAN, NAN); // throw new vxf::Exception("Radius of a circle is zero!");

	// Vorgehen:
	// 1. Definiere Eine Ebene, in der der Kreis liegt und durch den Punkt p (point) geht
	// -> E: ( x - center ) * normal
	// 2. Berechne den Lotpunkt des Punktes auf der Ebene
	// 3. Stelle Geradengleichung auf mit Kreismittelpunkt als Ortsvektor und den Richtungsvektor vom
	//    Radius zum Lotpunkt:
	// -> r = g: center + lambda * ( loc - center)
	// 4. Bestimme Lambda für den Punkt auf dem Radius
	// -> lambda = |r| / radius
	// Rechne Schnittpunkt aus.

	Vertex3 loc = ClosestPointOnPlane(point, center, normal);
	Vertex3 r = loc - center;
	double lambda = r.Abs() / radius;
	return center + r * lambda;
}

double jm::DistancePointToPlane(const Vertex3 &point,
                                const Vertex3 &position,
                                const Vertex3 &normal)
{
	//Vorgehen:
	// 1. Berechne Lotpunkt auf der Ebene ( = loc)
	// 2. Berechne Richtungsvektor zum Punt ( = loc - point)
	// 3. Betrag ist Abstand

	Vertex3 loc = ClosestPointOnPlane(point, position, normal);
	loc = loc - point;
	return loc.Abs();
}

double jm::DistancePointToPoint(const Vertex3 &point1,
                                const Vertex3 &point2)
{
	Vertex3 v = point2 - point1;
	return v.Abs();
}


double jm::DistancePointToPoint(const Vertex2 &point1,
                                const Vertex2 &point2)
{
	Vertex2 v = point2 - point1;
	return v.Abs();
}

double jm::DistancePointToLine(const Vertex3 &point,
                               const Vertex3 &position,
                               const Vertex3 &direction)
{
	//Vorgehen:
	// 1. Berechne Lotpunkt auf der Geraden ( = loc)
	// 2. Berechne Richtungsvektor zum Punt ( = loc - point)
	// 3. Betrag ist Abstand

	Vertex3 loc = ClosestPointOnLine(point, position, direction);
	loc = loc - point;
	return loc.Abs();
}

double jm::DistancePointToLine(const Vertex3 &point,
                               const Vertex3 &lineStart,
                               const Vertex3 &lineEnd,
                               bool extend)
{
	//Vorgehen:
	// 1. Berechne Lotpunkt auf der Geraden ( = loc)
	// 2. Berechne Richtungsvektor zum Punt ( = loc - point)
	// 3. Betrag ist Abstand

	Vertex3 loc = ClosestPointOnLine(point, lineStart, lineEnd, extend);
	loc = loc - point;
	return loc.Abs();
}

double jm::DistancePointToCircle(const Vertex3 &point,
                                 const Vertex3 &center,
                                 double radius,
                                 const Vertex3 &normal)
{
	//Vorgehen:
	// 1. Berechne Lotpunkt auf dem Kreis ( = loc)
	// 2. Berechne Richtungsvektor zum Punt ( = loc - point)
	// 3. Betrag ist Abstand

	Vertex3 loc = ClosestPointOnCircle(point, center, radius, normal);
	loc = loc - point;
	return loc.Abs();
}

double jm::DistanceLineToLine(const Vertex3 &position1,
                              const Vertex3 &direction1,
                              const Vertex3 &position2,
                              const Vertex3 &direction2)
{
	if(direction1.IsCollinear(direction2))
	{
		//Vorgehen, wenn parallel
		// 1. Bestimme die Differenz aus beiden Ortsvektoren
		// 2. Bestimme Kreuzprodukt aus 1. Richtungsvektor und Differenz
		// 3. Teile durch Betrag des 1. Richtungsvektor
		Vertex3 cross = direction1.CrossProduct(position2 - position1);
		return cross.Abs() / direction1.Abs();
	}
	else
	{
		//Vorgehen, wenn windschief
		// 1. Berechne Lotpunkt auf der 2. Geraden
		// 2. Berechne Lotpunkt auf der 1. Geraden
		// 3. Bestimme Abstand der beiden Punkte

		Vertex3 loc2 = ClosestPointOnLine(position1, direction1, position2, direction2);
		Vertex3 loc1 = ClosestPointOnLine(position2, direction2, position1, direction1);

		return DistancePointToPoint(loc1, loc2);
	}
}


bool jm::IsOnPlane(const Vertex3 &point,
                   const Vertex3 &position,
                   const Vertex3 &normal,
                   double maxDistance)
{
	double dist = DistancePointToPlane(point, position, normal);
	return IsLess(dist, maxDistance);
}

bool jm::IsOnLine(const Vertex3 &point,
                  const Vertex3 &position,
                  const Vertex3 &direction)
{
	double dist = DistancePointToLine(point, position, direction);
	return IsEqual(dist, 0);
}

bool jm::IsOnLine(const Vertex3 &point,
                  const Vertex3 &lineStart,
                  const Vertex3 &lineEnd,
                  bool extend)
{
	double dist = DistancePointToLine(point, lineStart, lineEnd, extend);
	return IsEqual(dist, 0);
}

bool jm::IsOnCircle(const Vertex3 &point,
                    const Vertex3 &center,
                    double radius,
                    const Vertex3 &normal)
{
	double dist = DistancePointToCircle(point, center, radius, normal);
	return IsEqual(dist, 0);
}

bool jm::IsSamePoint(const Vertex3 &point1,
                     const Vertex3 &point2)
{
	double dist = DistancePointToPoint(point1, point2);
	return IsEqual(dist, 0);
}

Vertex2 jm::IntersectionPoint(const Vertex2 &position1,
                              const Vertex2 &direction1,
                              const Vertex2 &position2,
                              const Vertex2 &direction2)
{
	if(direction1.IsCollinear(direction2)) return Vertex2(NAN, NAN);
	else
	{
		Vertex2 x = SolveLinearSystem(direction1, -1 * direction2, position2 - position1);
		return position2 + x.y * direction2;
	}
}

Vertex3 jm::IntersectionPoint(const Vertex3 &position1,
                              const Vertex3 &direction1,
                              const Vertex3 &position2,
                              const Vertex3 &direction2)
{
	//
	// 1. Ermittle Abstand der Geraden.
	//
	double dist = DistanceLineToLine(position1,
	                                 direction1,
	                                 position2,
	                                 direction2);

	//
	// 2. Ein Schnittpunkt ist vorhanden, wenn der Abstand 0 ist.
	//
	if(IsLessEqual(dist, 0.0))
	{
		//
		// Welcher Punkt auf der 2. Geraden hat den kürzesten Abstand zur 1. Geraden ?
		//
		Vertex3 inter = ClosestPointOnLine(position1,
		                                   direction1,
		                                   position2,
		                                   direction2);

		//
		// -> Genau dieser Punkt ist der Schnittpunkt der beiden Geraden.
		//
		return inter;
	}

	//
	// Kein Schnittpunkt vorhanden
	//
	return Vertex3(NAN, NAN, NAN);
}

bool jm::Crosses(const Vertex2 &start1,
                 const Vertex2 &end1,
                 const Vertex2 &start2,
                 const Vertex2 &end2)
{
	Vertex2 dir1 = end1 - start1;
	Vertex2 dir2 = end2 - start2;

	if(dir1.IsCollinear(dir2)) return false;

	Vertex2 x = SolveLinearSystem(dir1, -1 * dir2, start2 - start1);
	double lambda1 = x.x;
	double lambda2 = x.y;

	/*	Vertex2 intersection = IntersectionPoint( start1, dir1, start2, dir2 );

		if( IsNaN( intersection.x ) || IsNaN( intersection.y ) ) return false;

		//Bestimme die Lambdas vom Start zum Endpunkt
		Vertex2 dist1 = intersection - start1;
		Vertex2 dist2 = intersection - start2;

		double lambda1 = dist1.Abs() / dir1.Abs();
		double lambda2 = dist2.Abs() / dir2.Abs();*/

	if(IsLess(lambda1, 0) ||
	      IsGreater(lambda1, 1) ||
	      IsLess(lambda2, 0) ||
	      IsGreater(lambda2, 1))return false;

	return true;
}

Vertex2 jm::ExtensionPointOnLine(const Vertex2 &rayorigin,
                                 const Vertex2 &direction,
                                 const Vertex2 &start,
                                 const Vertex2 &end)
{
	//Richtung der Linie vom Start zum Endpunkt
	Vertex2 direction2 = end - start;

	double lambda = -1;
	if(direction.IsCollinear(direction2)) return Vertex2(NAN, NAN);
	else
	{
		Vertex2 x = SolveLinearSystem(direction, -1 * direction2, start - rayorigin);
		lambda = x.y;
	}


	//Bekomme Schnittpunkt
	Vertex2 intersection = start + lambda * direction2;
	if(IsNaN(intersection.x) || IsNaN(intersection.y)) return intersection;

	//Wenn Schnittpunkt == Startpunkt ist, dann gibt auf NAN zurück
	if(IsEqual(intersection.x, rayorigin.x) &&
	      IsEqual(intersection.y, rayorigin.y))
		return Vertex2(NAN, NAN);

	//Wenn lambda nicht >= 0 und <=1 ist der Punkt außerhalb der Linie
	if(IsLess(lambda, 0) || IsGreater(lambda, 1))return Vertex2(NAN, NAN);

	//Prüfe nun, ob der Schnittpunkt in Richtung des Strahls liegt
	direction2 = intersection - rayorigin;

	Vertex2 ndir = direction;
	ndir.Normalize();
	Vertex2 ndir2 = direction2;
	ndir2.Normalize();

	//Wenn gleichgerichtet, dann ist der Punkt vor dem Strahl
	if(IsEqual(ndir.x, ndir2.x) && IsEqual(ndir.y, ndir2.y))return intersection;

	//Entgegengesetzt, also kein Schnittpunkt
	return Vertex2(NAN, NAN);
}

/*!
 \brief Diese Helfermethode prüft, ob der punkt p innerhalb des Start und Endwinkels liegt
 Start und Endwinkel im Bogenmaß
 */
bool CheckAngle(const Vertex2 &point,
                const Vertex2 &center,
                double start,
                double end);
bool CheckAngle(const Vertex2 &point,
                const Vertex2 &center,
                double start,
                double end)
{
	Vertex2 dir = point - center;

	// http://de.wikipedia.org/wiki/Polarkoordinaten#Umrechnung_von_kartesischen_Koordinaten_in_Polarkoordinaten
	double angle = std::atan2(dir.y, dir.x);

	double const DBL_PI = 2 * M_PI;

	//Sorge dafür, dass Startwinkel im Bereich 0-2PI ist;
	while(IsGreaterEqual(start, DBL_PI))start -= DBL_PI;

	//Sroge dafür, dass er Startwinkel größer start ist, aber nicht um ein vielfaches größer
	while(IsGreaterEqual(end, DBL_PI))end -= DBL_PI;
	while(IsLessEqual(end, start))end += DBL_PI;

	//Sorge dafür, dass angle > start ist
	while(IsLess(angle, start))angle += DBL_PI;

	if(IsLessEqual(angle, end))return true;

	return false;
}

/*!
 \brief Diese Methode wird bei Kreisen und Ellipsen dazu verwendet, das Ergebnis der PQ-Formel zu
 interpretieren und gleichzeitig die Winkel zu Prüfen.
 */
Vertex2 PQCheck(double p,
                double q,
                const Vertex2 &rayorigin,
                const Vertex2 &direction,
                const Vertex2 &center,
                double start,
                double end);
Vertex2 PQCheck(double p,
                double q,
                const Vertex2 &rayorigin,
                const Vertex2 &direction,
                const Vertex2 &center,
                double start,
                double end)
{
	double p2 = 0.5 * p;
	double rt = p2 * p2 - q;

	//Wenn rt < 0 ist, dann wird der Kreis nicht geschnitten.
	//Wenn rt ~ 0 ist, setze es auf Null, damit die Wurzel auch berechnet wird.
	if(IsLessEqual(rt, 0.0))
	{
		if(IsLess(rt, 0.0)) return Vertex2(NAN, NAN);
		rt = 0;
	}

	double n1 = - p2 - sqrt(rt);
	double n2 = - p2 + sqrt(rt);

	//Beide Punkte liegen hinter der Strahlquelle, dann gibts keine Punkte
	if(IsLessEqual(n1, 0.0) && IsLessEqual(n2, 0.0))return Vertex2(NAN, NAN);

	Vertex2 pt1 = rayorigin + n1 * direction;
	Vertex2 pt2 = rayorigin + n2 * direction;
	bool pt1ok = CheckAngle(pt1, center, start, end);
	bool pt2ok = CheckAngle(pt2, center, start, end);

	//Beide Punkte liegen vor der Strahlquelle
	if(IsGreater(n1, 0.0) && IsGreater(n2, 0.0))
	{
		if(IsLess(n1, n2))
		{
			if(pt1ok)return pt1;
			if(pt2ok)return pt2;
		}
		else
		{
			if(pt2ok)return pt2;
			if(pt1ok)return pt1;
		}
		return Vertex2(NAN, NAN);
	}

	//Ein Punkt liegt hinter der Strahlquelle
	if(IsLessEqual(n1, 0.0) && pt2ok)
	{
		return pt2;
	}
	if(IsLessEqual(n2, 0.0) && pt1ok)
	{
		return pt1;
	}


	// Keine Lösung, aus welchen Grund auch immer...
	return Vertex2(NAN, NAN);
}

Vertex2 jm::ExtensionPointOnArc(const Vertex2 &rayorigin,
                                const Vertex2 &direction,
                                const Vertex2 &center,
                                double radius,
                                double start,
                                double end)
{
	//Linie schneidet Kreis in zwei Punkten (oder tangiert ihn)

	//GLS:
	// o.x,o.y : Geradenursprung
	// p.x,p.y : Punkt auf Kreis, der gesucht wird
	// c.x,c.y : Kreismittelpunkt
	// r       : Radius
	// n       : lambda für Richtung (gesucht)
	//
	// Kreisgleichung (p.x - c.x)^2 + (p.y-c.y)^2 = r^2
	// Geradengleichung (vektoriell) o + n * d = p
	// Einsetzen und quadratische Gleichung mit pq-Formel lösen führt zu:

	double dx2 = direction.x * direction.x;
	double dy2 = direction.y * direction.y;
	double rd2 = radius * radius;
	double rx2 = rayorigin.x * rayorigin.x;
	double ry2 = rayorigin.y * rayorigin.y;
	double cx2 = center.x * center.x;
	double cy2 = center.y * center.y;

	double a = dx2 + dy2;

	double b = 2 *
	           (direction.x * rayorigin.x
	            - center.x * direction.x
	            + direction.y * rayorigin.y
	            - center.y * direction.y);

	double c = rd2 - rx2 - ry2 - cx2 - cy2
	           +  2 * rayorigin.x * center.x + 2 * rayorigin.y * center.y;

	double p = b / a;
	double q = -c / a;

	return PQCheck(p, q, rayorigin, direction, center, start, end);
}

Vertex2 jm::ExtensionPointOnEllipse(const Vertex2 &rayorigin_,
                                    const Vertex2 &direction_,
                                    const Vertex2 &center_,
                                    const Vertex2 &mainAxis,
                                    double minorAxisRatio,
                                    double start,
                                    double end)
{

	// Zunächst muss die Ellipse und der Vektor so rotiert werden, dass die Ellipse mit der
	// Hauptachse auf der X-Achse liegt.
	double angle = std::atan2(center_.y, center_.x);

	Vertex2 center = center_;
	center.Rotate(-angle);
	Vertex2 direction = direction_;
	direction.Rotate(-angle);
	Vertex2 rayorigin = rayorigin_;
	rayorigin.Rotate(-angle);

	//Nun liegt die Ellipse mit der Hauptachse auf der X-Achse

	//GLS:
	// o.x,o.y : Geradenursprung
	// p.x,p.y : Punkt auf Ellipse, der gesucht wird
	// c.x,c.y : Ellipsenmittelpunkt
	// a       : Länge der Hauptachse (analogon Radius beim Kreis)
	// b       : Länge der Nebenachse
	// n       : lambda für Richtung (gesucht)
	//
	// Ellipsengleichung (p.x - c.x)^2 / a^2 + (p.y-c.y)^2 / b^2 = 1
	// Geradengleichung (vektoriell) o + n * d = p
	// Einsetzen und quadratische Gleichung mit pq-Formel lösen führt zu:

	double a = mainAxis.Abs();
	double b = a * minorAxisRatio;

	double a2 = a * a;
	double b2 = b * b;

	double qx = rayorigin.x - center.x;
	double qy = rayorigin.y - center.y;

	double div = (direction.x * direction.x / a2) + (direction.y * direction.y / b2);

	double p = 2 * ((direction.x * qx / a2) + (direction.y * qy / b2)) / div;
	double q = ((qx * qx / a2) + (qy * qy / b) - 1.0) / div;

	Vertex2 result = PQCheck(p, q, rayorigin, direction, center, start, end);
	if(result.IsValid())result.Rotate(angle);
	return result;
}

Vertex3 jm::AngleBisector(const Vertex3 &direction1, const Vertex3 &direction2)
{
	return direction1.Normalized() + direction2.Normalized();
}

Vertex2 jm::AngleBisector(const Vertex2 &direction1, const Vertex2 &direction2)
{
	return direction1.Normalized() + direction2.Normalized();
}

jm::VxfErrorStatus jm::CircleParameterBy3Points(Vertex2 &centre, double &radius,
														  const Vertex2 &p1,
														  const Vertex2 &p2,
														  const Vertex3 &p3)
{
	// Algorithm:
	// Given: 3 points <x1,y1>, <x2,y2>, <x3,y3>
	// Searched: Centre point <x,y>
	//
	//        | x^2+y^2   x  y   1 |
	// Solve: | x1^2+y1^2 x1 y1  1 |
	//     A= | x2^2+y2^2 x2 y2  1 | = 0
	//        | x3^2+y3^2 x3 y3  1 |
	//
	// e.g.: x = 0,5 * M12 / M11
	//       y = 0,5 * M13 / M11

	// Calculate M12 (Minor of A), minor M12 is det of A without row 1 and col 2
	Matrix M11 = Matrix(Vertex3(p1.x,p1.y,1.0),
							  Vertex3(p2.x,p2.y,1.0),
							  Vertex3(p3.x,p3.y,1.0),true);

	Matrix M12 = Matrix(Vertex3(p1.x*p1.x+p1.y*p1.y,p1.y,1.0),
							  Vertex3(p2.x*p2.x+p2.y*p2.y,p2.y,1.0),
							  Vertex3(p3.x*p3.x+p3.y*p3.y,p3.y,1.0),true);

	Matrix M13 = Matrix(Vertex3(p1.x*p1.x+p1.y*p1.y,p1.x,1.0),
							  Vertex3(p2.x*p2.x+p2.y*p2.y,p2.x,1.0),
							  Vertex3(p3.x*p3.x+p3.y*p3.y,p3.x,1.0),true);
	double m11,m12,m13;
	VxfErrorStatus status = M11.Det(m11);
	if(status!=eOK)return status;
	status = M12.Det(m12);
	if(status!=eOK)return status;
	status = M13.Det(m13);
	if(status!=eOK)return status;
	
	double x = 0.5*m12/m11;
	double y = -0.5*m13/m11;
	
	centre.x=x;
	centre.y=y;
	radius=(p1-centre).Abs();
	
	return eOK;
}
