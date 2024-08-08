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

Vertex3 jm::intersectionPointLineAndPlane(const Vertex3& planePosition,
      const Vertex3& normal,
      const Vertex3& linePosition,
      const Vertex3& direction,
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
   // What if the line lies in the plane?
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
      // Starting point implicitly has lambda=0
      // Endpoint implicitly has lambda=1
      // \todo It should be considered whether it is an extra option that the point is set to the end point
      //if( IsLess( lambda , 0 ) )lambda = 0;
      //else if( IsGreater( lambda , 1 ) ) lambda = 1;
      if(isLess(lambda, 0))return Vertex3(NAN, NAN, NAN);
      else if(isGreater(lambda, 1))return Vertex3(NAN, NAN, NAN);
   }

   return linePosition + direction * lambda;
}

Vertex3 jm::closestPointOnPlane(const Vertex3& point,
                                const Vertex3& position,
                                const Vertex3& normal)
{
   // Procedure:
   // 1. The plane is already defined by the normal form (position, normal).
   // -> E: ( x - position ) * normal
   // 2. A straight line is defined that is perpendicular to the plane and passes through P
   // -> g: point + lambda * normal

   return intersectionPointLineAndPlane(position, normal, point, normal, true);
}

Vertex3 jm::closestPointOnLine(const Vertex3& point,
                               const Vertex3& position,
                               const Vertex3& direction)
{
   // Procedure:
   // 1. Define a plane that is perpendicular to the straight line and lies at point p.
   // -> E: ( x - point ) * direction
   // 2. The straight line is already defined by its equation.
   // -> g: position + lanbda * direction

   return intersectionPointLineAndPlane(point, direction, position, direction, true);
}

Vertex3 jm::closestPointOnLine(const Vertex3& position1,
                               const Vertex3& direction1,
                               const Vertex3& position2,
                               const Vertex3& direction2)
{
   // Prerequisites
   // - The straight lines are not parallel and are skewed

   // Procedure:
   // 1. Form the 1st plane in which the two direction vectors span the plane. This means that the
   //    normal vector of the plane is the vertical vector between the two lines
   //    -> normal1 = direction1 X direction2
   // 2. Form the 2nd plane, where the normal vector of the 1st plane and the direction vector of
   //    the 1st straight line span the plane
   //    -> normal2 = position1 X normal1
   //    -> E: ( x - position1) * normal2
   // 3. The intersection of the 2nd straight line with the 2nd auxiliary plane is the perpendicular
   //    base point
   Vertex3 normal1 = direction1.crossProduct(direction2);
   Vertex3 normal2 = direction1.crossProduct(normal1);
   return intersectionPointLineAndPlane(position1, normal2, position2, direction2, true);
}


Vertex3 jm::closestPointOnLine(const Vertex3& point,
                               const Vertex3& lineStart,
                               const Vertex3& lineEnd,
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
   return intersectionPointLineAndPlane(point, direction, lineStart, direction, extend);
}

Vertex3 jm::closestPointOnCircle(const Vertex3& point,
                                 const Vertex3& center,
                                 double radius,
                                 const Vertex3& normal)
{
   if(isEqual(radius, 0.0)) return Vertex3(NAN, NAN, NAN);

   // Procedure:
   // 1. Define A plane in which the circle lies and passes through the point p (point)
   // -> E: ( x - center ) * normal
   // 2. Calculate the perpendicular point of the point on the plane
   // 3. Set up the equation of a straight line with the center of the circle as the position vector
   //    and the direction vector from the radius to the perpendicular point:
   // -> r = g: center + lambda * ( loc - center)
   // 4. Determine lambda for the point on the radius
   // -> lambda = |r| / radius
   // Calculate the intersection.

   Vertex3 loc = closestPointOnPlane(point, center, normal);
   Vertex3 r = loc - center;
   double lambda = r.abs() / radius;
   return center + r * lambda;
}

double jm::distancePointToPlane(const Vertex3& point,
                                const Vertex3& position,
                                const Vertex3& normal)
{
   // Approach:
   // 1. Calculate the perpendicular point on the plane ( = loc)
   // 2. Calculate the direction vector to the point ( = loc - point)
   // 3. The magnitude is the distance
   Vertex3 loc = closestPointOnPlane(point, position, normal);
   loc = loc - point;
   return loc.abs();
}

double jm::distancePointToPoint(const Vertex3& point1,
                                const Vertex3& point2)
{
   Vertex3 v = point2 - point1;
   return v.abs();
}


double jm::distancePointToPoint(const Vertex2& point1,
                                const Vertex2& point2)
{
   Vertex2 v = point2 - point1;
   return v.abs();
}

double jm::distancePointToLine(const Vertex3& point,
                               const Vertex3& position,
                               const Vertex3& direction)
{
   // Approach:
   // 1. Calculate the perpendicular point on the line ( = loc)
   // 2. Calculate the direction vector to the point ( = loc - point)
   // 3. The magnitude is the distance

   Vertex3 loc = closestPointOnLine(point, position, direction);
   loc = loc - point;
   return loc.abs();
}

double jm::distancePointToLine(const Vertex3& point,
                               const Vertex3& lineStart,
                               const Vertex3& lineEnd,
                               bool extend)
{
   // Approach:
   // 1. Calculate the perpendicular point on the line ( = loc)
   // 2. Calculate the direction vector to the point ( = loc - point)
   // 3. The magnitude is the distance

   Vertex3 loc = closestPointOnLine(point, lineStart, lineEnd, extend);
   loc = loc - point;
   return loc.abs();
}

double jm::distancePointToCircle(const Vertex3& point,
                                 const Vertex3& center,
                                 double radius,
                                 const Vertex3& normal)
{
   // Approach:
   // 1. Calculate the perpendicular point on the circle ( = loc)
   // 2. Calculate the direction vector to the point ( = loc - point)
   // 3. The magnitude is the distance
   Vertex3 loc = closestPointOnCircle(point, center, radius, normal);
   loc = loc - point;
   return loc.abs();
}

double jm::distanceLineToLine(const Vertex3& position1,
                              const Vertex3& direction1,
                              const Vertex3& position2,
                              const Vertex3& direction2)
{
   if(direction1.IsCollinear(direction2))
   {
      // Approach when parallel
      // 1. Calculate the difference between both position vectors
      // 2. Calculate the cross product of the first direction vector and the difference
      // 3. Divide by the magnitude of the first direction vector
      Vertex3 cross = direction1.crossProduct(position2 - position1);
      return cross.abs() / direction1.abs();
   }
   else
   {
      // Approach when skew
      // 1. Calculate the perpendicular point on the second line
      // 2. Calculate the perpendicular point on the first line
      // 3. Determine the distance between the two points

      Vertex3 loc2 = closestPointOnLine(position1, direction1, position2, direction2);
      Vertex3 loc1 = closestPointOnLine(position2, direction2, position1, direction1);

      return distancePointToPoint(loc1, loc2);
   }
}


bool jm::isPointOnPlane(const Vertex3& point,
                        const Vertex3& position,
                        const Vertex3& normal,
                        double maxDistance)
{
   double dist = distancePointToPlane(point, position, normal);
   return isLess(dist, maxDistance);
}

bool jm::isPointOnLine(const Vertex3& point,
                       const Vertex3& position,
                       const Vertex3& direction)
{
   double dist = distancePointToLine(point, position, direction);
   return isEqual(dist, 0);
}

bool jm::isPointOnLine(const Vertex3& point,
                       const Vertex3& lineStart,
                       const Vertex3& lineEnd,
                       bool extend)
{
   double dist = distancePointToLine(point, lineStart, lineEnd, extend);
   return isEqual(dist, 0);
}

bool jm::isPointOnCircle(const Vertex3& point,
                         const Vertex3& center,
                         double radius,
                         const Vertex3& normal)
{
   double dist = distancePointToCircle(point, center, radius, normal);
   return isEqual(dist, 0);
}

bool jm::isSamePoint(const Vertex3& point1,
                     const Vertex3& point2)
{
   double dist = distancePointToPoint(point1, point2);
   return isEqual(dist, 0);
}

Vertex2 jm::intersectionPoint(const Vertex2& position1,
                              const Vertex2& direction1,
                              const Vertex2& position2,
                              const Vertex2& direction2)
{
   if(direction1.isCollinear(direction2)) return Vertex2(NAN, NAN);
   else
   {
      Vertex2 x = SolveLinearSystem(direction1, -1 * direction2, position2 - position1);
      return position2 + x.y * direction2;
   }
}

Vertex3 jm::intersectionPoint(const Vertex3& position1,
                              const Vertex3& direction1,
                              const Vertex3& position2,
                              const Vertex3& direction2)
{
   //
   // 1. Calculate the distance between the two lines.
   //
   double dist = distanceLineToLine(position1,
                                    direction1,
                                    position2,
                                    direction2);
   //
   // 2. If the distance is less than or equal to 0, there is an intersection point.
   //
   if(isLessEqual(dist, 0.0))
   {
      //
      // Find the point on the second line that is closest to the first line.
      //
      Vertex3 inter = closestPointOnLine(position1,
                                         direction1,
                                         position2,
                                         direction2);
      //
      // -> This point is the intersection point of the two lines.
      //
      return inter;
   }

   //
   // No intersection point found.
   //
   return Vertex3(NAN, NAN, NAN);
}

bool jm::crosses(const Vertex2& start1,
                 const Vertex2& end1,
                 const Vertex2& start2,
                 const Vertex2& end2)
{
   Vertex2 dir1 = end1 - start1;
   Vertex2 dir2 = end2 - start2;

   if(dir1.isCollinear(dir2)) return false;

   Vertex2 x = SolveLinearSystem(dir1, -1 * dir2, start2 - start1);
   double lambda1 = x.x;
   double lambda2 = x.y;

   if(isLess(lambda1, 0) ||
         isGreater(lambda1, 1) ||
         isLess(lambda2, 0) ||
         isGreater(lambda2, 1))return false;

   return true;
}

Vertex2 jm::extensionPointOnLine(const Vertex2& rayorigin,
                                 const Vertex2& direction,
                                 const Vertex2& start,
                                 const Vertex2& end)
{

   //Direction of the line from the start to the endpoint
   Vertex2 direction2 = end - start;

   double lambda = -1;
   if(direction.isCollinear(direction2)) return Vertex2(NAN, NAN);
   else
   {
      Vertex2 x = SolveLinearSystem(direction, -1 * direction2, start - rayorigin);
      lambda = x.y;
   }


   // Get intersection point
   Vertex2 intersection = start + lambda * direction2;
   if(isNaN(intersection.x) || isNaN(intersection.y)) return intersection;

   // If the intersection point is equal to the starting point, return NAN
   if(isEqual(intersection.x, rayorigin.x) &&
         isEqual(intersection.y, rayorigin.y))
      return Vertex2(NAN, NAN);

   // If lambda is not >= 0 and <= 1, the point is outside the line
   if(isLess(lambda, 0) || isGreater(lambda, 1))return Vertex2(NAN, NAN);

   // Now check if the intersection point lies in the direction of the ray
   direction2 = intersection - rayorigin;

   Vertex2 ndir = direction;
   ndir.normalize();
   Vertex2 ndir2 = direction2;
   ndir2.normalize();

   // If the directions are the same, then the point is in front of the ray
   if(isEqual(ndir.x, ndir2.x) && isEqual(ndir.y, ndir2.y))return intersection;

   // Opposite, so no intersection point
   return Vertex2(NAN, NAN);
}

/*!
 \brief This helper method checks if the point p lies within the start and end angles.
 Start and end angles are in radians.
 */
bool CheckAngle(const Vertex2& point,
                const Vertex2& center,
                double start,
                double end);
bool CheckAngle(const Vertex2& point,
                const Vertex2& center,
                double start,
                double end)
{
   Vertex2 dir = point - center;

   // http://de.wikipedia.org/wiki/Polarkoordinaten#Umrechnung_von_kartesischen_Koordinaten_in_Polarkoordinaten
   double angle = std::atan2(dir.y, dir.x);

   double const DBL_PI = 2 * M_PI;

   // Ensure that the start angle is in the range of 0-2PI
   while(isGreaterEqual(start, DBL_PI))start -= DBL_PI;

   // Ensure that the start angle is greater than start, but not multiple times greater
   while(isGreaterEqual(end, DBL_PI))end -= DBL_PI;
   while(isLessEqual(end, start))end += DBL_PI;

   // Ensure that angle is greater than start
   while(isLess(angle, start))angle += DBL_PI;

   if(isLessEqual(angle, end))return true;

   return false;
}

/*!
 \brief This method is used for interpreting the result of the PQ formula and checking the angles in circles and ellipses.
 */
Vertex2 PQCheck(double p,
                double q,
                const Vertex2& rayorigin,
                const Vertex2& direction,
                const Vertex2& center,
                double start,
                double end);
Vertex2 PQCheck(double p,
                double q,
                const Vertex2& rayorigin,
                const Vertex2& direction,
                const Vertex2& center,
                double start,
                double end)
{
   double p2 = 0.5 * p;
   double rt = p2 * p2 - q;

   // If rt < 0, then the circle is not intersected.
   // If rt is approximately equal to 0, set it to zero to ensure the square root is computed.
   if(isLessEqual(rt, 0.0))
   {
      if(isLess(rt, 0.0)) return Vertex2(NAN, NAN);
      rt = 0;
   }

   double n1 = - p2 - sqrt(rt);
   double n2 = - p2 + sqrt(rt);

   // Both points are behind the beam origin, then there are no points
   if(isLessEqual(n1, 0.0) && isLessEqual(n2, 0.0))return Vertex2(NAN, NAN);

   Vertex2 pt1 = rayorigin + n1 * direction;
   Vertex2 pt2 = rayorigin + n2 * direction;
   bool pt1ok = CheckAngle(pt1, center, start, end);
   bool pt2ok = CheckAngle(pt2, center, start, end);

   // Both points are in front of the beam source
   if(isGreater(n1, 0.0) && isGreater(n2, 0.0))
   {
      if(isLess(n1, n2))
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

   // A point is behind the ray source
   if(isLessEqual(n1, 0.0) && pt2ok)
   {
      return pt2;
   }
   if(isLessEqual(n2, 0.0) && pt1ok)
   {
      return pt1;
   }


   // No solution, for whatever reason...
   return Vertex2(NAN, NAN);
}

Vertex2 jm::extensionPointOnArc(const Vertex2& rayorigin,
                                const Vertex2& direction,
                                const Vertex2& center,
                                double radius,
                                double start,
                                double end)
{
   // Line intersects circle at two points (or is tangent to it)

   //GLS:
   // o.x,o.y : Geradenursprung
   // p.x,p.y : Punkt auf Kreis, der gesucht wird
   // c.x,c.y : Kreismittelpunkt
   // r       : Radius
   // n       : lambda für Richtung (gesucht)
   //
   // Circle equation (p.x - c.x)^2 + (p.y-c.y)^2 = r^2
   // Line equation (vector form) o + n * d = p
   // Substituting and solving the quadratic equation using the quadratic formula leads to:

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

Vertex2 jm::extensionPointOnEllipse(const Vertex2& rayorigin_,
                                    const Vertex2& direction_,
                                    const Vertex2& center_,
                                    const Vertex2& mainAxis,
                                    double minorAxisRatio,
                                    double start,
                                    double end)
{

   // First, the ellipse and the vector must be rotated so that the ellipse lies with the main axis
   // on the x-axis.
   double angle = std::atan2(center_.y, center_.x);

   Vertex2 center = center_;
   center.rotate(-angle);
   Vertex2 direction = direction_;
   direction.rotate(-angle);
   Vertex2 rayorigin = rayorigin_;
   rayorigin.rotate(-angle);

   //Now the ellipse is aligned with the major axis on the X-axis

   //GLS:
   // o.x,o.y : Origin of the line
   // p.x,p.y : Point on the ellipse being sought
   // c.x,c.y : Center of the ellipse
   // a       : Length of the major axis (analogous to radius for a circle)
   // b       : Length of the minor axis
   // n       : lambda for direction (to be found)
   //
   // Ellipse equation (p.x - c.x)^2 / a^2 + (p.y-c.y)^2 / b^2 = 1
   // Line equation (vector form) o + n * d = p
   // Substituting and solving the quadratic equation using the pq-formula leads to:

   double a = mainAxis.abs();
   double b = a * minorAxisRatio;

   double a2 = a * a;
   double b2 = b * b;

   double qx = rayorigin.x - center.x;
   double qy = rayorigin.y - center.y;

   double div = (direction.x * direction.x / a2) + (direction.y * direction.y / b2);

   double p = 2 * ((direction.x * qx / a2) + (direction.y * qy / b2)) / div;
   double q = ((qx * qx / a2) + (qy * qy / b) - 1.0) / div;

   Vertex2 result = PQCheck(p, q, rayorigin, direction, center, start, end);
   if(result.isValid())result.rotate(angle);
   return result;
}

Vertex3 jm::angleBisector(const Vertex3& direction1, const Vertex3& direction2)
{
   return direction1.normalized() + direction2.normalized();
}

Vertex2 jm::angleBisector(const Vertex2& direction1, const Vertex2& direction2)
{
   return direction1.normalized() + direction2.normalized();
}

jm::VxfErrorStatus jm::circleParameterBy3Points(Vertex2& centre, double& radius,
      const Vertex2& p1,
      const Vertex2& p2,
      const Vertex3& p3)
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
   Matrix M11 = Matrix(Vertex3(p1.x, p1.y, 1.0),
                       Vertex3(p2.x, p2.y, 1.0),
                       Vertex3(p3.x, p3.y, 1.0), true);

   Matrix M12 = Matrix(Vertex3(p1.x * p1.x + p1.y * p1.y, p1.y, 1.0),
                       Vertex3(p2.x * p2.x + p2.y * p2.y, p2.y, 1.0),
                       Vertex3(p3.x * p3.x + p3.y * p3.y, p3.y, 1.0), true);

   Matrix M13 = Matrix(Vertex3(p1.x * p1.x + p1.y * p1.y, p1.x, 1.0),
                       Vertex3(p2.x * p2.x + p2.y * p2.y, p2.x, 1.0),
                       Vertex3(p3.x * p3.x + p3.y * p3.y, p3.x, 1.0), true);
   double m11, m12, m13;
   VxfErrorStatus status = M11.det(m11);
   if(status != eOK)return status;
   status = M12.det(m12);
   if(status != eOK)return status;
   status = M13.det(m13);
   if(status != eOK)return status;

   double x = 0.5 * m12 / m11;
   double y = -0.5 * m13 / m11;

   centre.x = x;
   centre.y = y;
   radius = (p1 - centre).abs();

   return eOK;
}
