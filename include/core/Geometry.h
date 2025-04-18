////////////////////////////////////////////////////////////////////////////////////////////////////
// Name:        Geometry.h
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

#ifndef jm_Geometry_h
#define jm_Geometry_h

#include "Vertex2.h"
#include "Vertex3.h"

namespace jm
{
   /*!
   \brief This method calculates the intersection point of a line and a plane using the normal
   form.
   \param planePosition The position vector of the plane.
   \param normal The normal vector of the plane.
   \param linePosition The position vector of the line.
   \param direction The direction vector of the line.
   \param extend The line equation can define a line segment if we assume that linePosition is the
    starting point of the line and (linePosition+direction) is the end point of the line. If extend
    = true, then the intersection point is calculated on the mathematical line. If false, the
    intersection point is chosen only on the line segment. That means if the point is outside, one
    of the end points is returned as the "intersection point". This "feature" is especially useful
    when you want to find the shortest distance to line segments. If there is no intersection
    point, an invalid vector is returned.
   */
   DllExport
   Vertex3 intersectionPointLineAndPlane(const Vertex3& planePosition,
                                         const Vertex3& normal,
                                         const Vertex3& linePosition,
                                         const Vertex3& direction,
                                         bool extend);

   /*!
    \brief This method calculates the intersection point of 2 circles.
    \param center1 The center point of the first circle.
    \param radius1 The radius of the first circle.
    \param center2 The center point of the second circle.
    \param radius2 The radius of the second circle.
    \param intersection1 The 1st intersection points of the two circles. If the circles do not intersect, the
    points have NaN values.
    \param intersection2 The 1st intersection points of the two circles. If the circles do not intersect, the
    points have NaN values.
    */
   DllExport
   void intersectionPointsOfCircles(const Vertex2& center1,
                                    double radius1,
                                    const Vertex2& center2,
                                    double radius2,
                                    Vertex2& intersection1,
                                    Vertex2& intersection2);

   /*!
    \brief This method calculates the point on the plane that has the minimum distance to the given point.
    \param point The 3D point from which the distance is to be determined.
    \param position Any point on the plane.
    \param normal The normal vector, perpendicular to the plane.
    \return The point on the plane with the minimum distance (perpendicular distance) to the given point.
    */
   DllExport
   Vertex3 closestPointOnPlane(const Vertex3& point,
                               const Vertex3& position,
                               const Vertex3& normal);

   DllExport
   Vertex2 closestPointOnLine(const Vertex2& point,
                              const Vertex2& position,
                              const Vertex2& direction);

   /*!
    \brief This method calculates the point on the line that has the minimum distance to the given point.
    The connecting line between the point and the result is perpendicular to the line.
    \param point The 3D point from which the distance is to be determined.
    \param position The position vector or any point on the line.
    \param direction The direction vector of the line.
    \return The point on the line with the minimum distance to the given point.
    */
   DllExport
   Vertex3 closestPointOnLine(const Vertex3& point,
                              const Vertex3& position,
                              const Vertex3& direction);

   /*!
    \brief This method calculates the point on the second line that has the minimum distance to the first line.
    The connecting line between the point and the result is perpendicular to the line.
    \param position1 The position vector or any point on the first line.
    \param direction1 The direction vector of the first line.
    \param position2 The position vector or any point on the second line.
    \param direction2 The direction vector of the second line.
    \return The point on the second line with the shortest distance between the lines.
    */
   DllExport
   Vertex3 closestPointOnLine(const Vertex3& position1,
                              const Vertex3& direction1,
                              const Vertex3& position2,
                              const Vertex3& direction2);

   /*!
    \brief This method calculates the point on the line that has the minimum distance to the given point.
    \param point The 3D point from which the distance is to be determined.
    \param lineStart The starting point of the line.
    \param lineEnd The end point of the line.
    \param extend If set to "true", the intersection point can be determined even if it lies beyond
    the line segment. If set to "false", NAN is returned if the point is outside the line segment.
    \return The point on the line with the minimum distance to the given point.
    */
   DllExport
   Vertex3 closestPointOnLine(const Vertex3& point,
                              const Vertex3& lineStart,
                              const Vertex3& lineEnd,
                              bool extend);

   /*!
    \brief This method calculates the minimum distance from the given point to the circle.
    \param point The 3D point from which the distance is to be determined.
    \param center The center point of the circle.
    \param radius The radius of the circle.
    \param normal The normal vector of the circle's plane. It is perpendicular to the plane.
    \return The shortest distance between the point and the circle.
    */
   DllExport
   Vertex3 closestPointOnCircle(const Vertex3& point,
                                const Vertex3& center,
                                double radius,
                                const Vertex3& normal);

   /*!
    \brief This method calculates the point on the line that has the minimum distance to the plane.
    \param point The 3D point from which the distance is to be determined.
    \param position Any point on the plane.
    \param normal The normal vector of the plane.
    \return The point on the line with the minimum distance to the plane.
    */
   DllExport
   double distancePointToPlane(const Vertex3& point,
                               const Vertex3& position,
                               const Vertex3& normal);

   /*!
    \brief This method calculates the minimum distance between the two points in 3D space.
    \param point1 The first point.
    \param point2 The second point.
    \return The distance between the first and second point.
    */
   DllExport
   double distancePointToPoint(const Vertex3& point1,
                               const Vertex3& point2);

   /*!
    \brief This method calculates the minimum distance between two points in 3D space.
    \param point1 The first point.
    \param point2 The second point.
    \return The distance between the first and second point.
    */
   DllExport
   double distancePointToPoint(const Vertex2& point1,
                               const Vertex2& point2);

   /*!
    \brief This method calculates the minimum distance between the given point and the line.
    \param point The 3D point from which the distance is to be determined.
    \param position The position vector or any point on the line.
    \param direction The direction vector of the line.
    \return The shortest distance between the line and the point.
    */
   DllExport
   double distancePointToLine(const Vertex3& point,
                              const Vertex3& position,
                              const Vertex3& direction);

   /*!
    \brief This method calculates the minimum distance between a point and a line segment.
    \param point The 3D point from which the distance is to be determined.
    \param lineStart The starting point of the line segment.
    \param lineEnd The end point of the line segment.
    \param extend If set to "true", the intersection point can be determined even if it lies beyond
    the line segment. If set to "false", one of the end points of the line segment is returned as
    the "intersection point" if the point is outside the line segment.
    \return The shortest distance between the line segment and the point.
    */
   DllExport
   double distancePointToLine(const Vertex3& point,
                              const Vertex3& lineStart,
                              const Vertex3& lineEnd,
                              bool extend);

   /*!
    \brief This method calculates the minimum distance from the given point to the circle.
    \param point The 3D point from which the distance is to be determined.
    \param center The center point of the circle.
    \param radius The radius of the circle.
    \param normal The normal vector of the circle's plane. It is perpendicular to the plane.
    \return The shortest distance between the line and the circle.
    */
   DllExport
   double distancePointToCircle(const Vertex3& point,
                                const Vertex3& center,
                                double radius,
                                const Vertex3& normal);

   /*!
    \brief This method calculates the minimum distance between two lines in 3D space.
    \param position1 The position vector or any point on the first line.
    \param direction1 The direction vector of the first line.
    \param position2 The position vector or any point on the second line.
    \param direction2 The direction vector of the second line.
    \return The shortest distance between the two lines.
    */
   DllExport
   double distanceLineToLine(const Vertex3& position1,
                             const Vertex3& direction1,
                             const Vertex3& position2,
                             const Vertex3& direction2);

   /*!
    \brief This method checks if the given point lies on the plane, taking into account the specified tolerance.
    \param point The 3D point for which the distance is to be determined.
    \param position The position vector or any point on the plane.
    \param normal The normal vector, perpendicular to the plane.
    \param maxDistance The maximum tolerated distance to the plane.
    \return "true" if the point lies on the plane, within the specified tolerance, otherwise "false".
    */
   DllExport
   bool isPointOnPlane(const Vertex3& point,
                       const Vertex3& position,
                       const Vertex3& normal,
                       double maxDistance = 0.0);

   /*!
    \brief This method checks whether a given point lies on the line, taking into account a specified tolerance.
    \param point The 3D point for which the distance is to be determined.
    \param position The position vector or any point on the line.
    \param direction The direction vector of the line.
    \return "true" if the point lies on the line, within the specified tolerance, otherwise "false".
    */
   DllExport
   bool isPointOnLine(const Vertex3& point,
                      const Vertex3& position,
                      const Vertex3& direction);

   /*!
    \brief This method checks whether a given point lies on the line segment, taking into account a
    specified tolerance.
    \param point The 3D point for which the distance is to be determined.
    \param lineStart The starting point of the line segment.
    \param lineEnd The end point of the line segment.
    \param extend Flag indicating whether the intersection point should be determined even if it
    lies beyond the line segment ends. If set to "false", NaN will be returned.
    \return "true" if the point lies on the line segment, within the specified tolerance and
    considering the extend flag, otherwise "false".
    */
   DllExport
   bool isPointOnLine(const Vertex3& point,
                      const Vertex3& lineStart,
                      const Vertex3& lineEnd,
                      bool extend);

   /*!
    \brief This method checks if a given point lies on a circle, taking into account a specified tolerance.
    \param point The 3D point for which the distance is to be determined.
    \param center The center point of the circle.
    \param radius The radius of the circle.
    \param normal The normal vector, perpendicular to the plane of the circle.
    \return "true" if the point lies on the circle, within the specified tolerance, otherwise "false".
    */
   DllExport
   bool isPointOnCircle(const Vertex3& point,
                        const Vertex3& center,
                        double radius,
                        const Vertex3& normal);

   /*!
    \brief This method checks if both points are identical, taking into account a specified tolerance.
    \details The points are considered identical if the distance between them is smaller than the tolerance.
    \param point1 The first 3D point.
    \param point2 The second 3D point.
    \return "true" if both points are identical within the specified tolerance, otherwise "false".
    */
   DllExport
   bool isSamePoint(const Vertex3& point1,
                    const Vertex3& point2);

   /*!
    \brief This method calculates the two-dimensional intersection point of two lines defined by
    their starting points and direction vectors.
    \param position1 The starting point of the first line.
    \param direction1 The direction vector of the first line.
    \param position2 The starting point of the second line.
    \param direction2 The direction vector of the second line.
    \return The intersection point of the two lines. If the lines are parallel or collinear, the point
    has NaN values.
    */
   DllExport
   Vertex2 intersectionPoint(const Vertex2& position1,
                             const Vertex2& direction1,
                             const Vertex2& position2,
                             const Vertex2& direction2);

   /*!
    \brief This method calculates the three-dimensional intersection point of two lines defined by
    their starting points and direction vectors.
    \param position1 The starting point of the first line.
    \param direction1 The direction vector of the first line.
    \param position2 The starting point of the second line.
    \param direction2 The direction vector of the second line.
    \return The intersection point of the two lines. If the lines are parallel or skew, the point
    has NaN values.
    */
   DllExport
   Vertex3 intersectionPoint(const Vertex3& position1,
                             const Vertex3& direction1,
                             const Vertex3& position2,
                             const Vertex3& direction2);

   /*!
    \brief This method checks if two lines intersect/cross between their endpoints. It is a planar
    problem.
    \param start1 The start point of the first line.
    \param end1 The end point of the first line.
    \param start2 The start point of the second line.
    \param end2 The end point of the second line.
    \return "true" if the lines intersect between their endpoints, otherwise "false".
    */
   DllExport
   bool crosses(const Vertex2& start1,
                const Vertex2& end1,
                const Vertex2& start2,
                const Vertex2& end2);

   /*!
    \brief This method checks if a ray (line) intersects with a line between or on its endpoints.
    The direction of the ray is crucial.

    This method is used for tasks such as extending lines, trimming lines, drawing hatches, etc.
    Hence, it is an essential method for CAD work. If the ray intersects with the line between or
    on the endpoints, the intersection point is returned.
    \param rayorigin The origin point of the ray. This is the point from which we check if the lines
    intersect. (Position vector of the line)
    \param direction The direction vector in which the ray points.
    \param start The start point of the line to be compared.
    \param end The end point of the line to be compared.
    \return The defined vector if the intersection point exists. If the intersection point does not
    exist, the vector has NaN entries.
    */
   DllExport
   Vertex2 extensionPointOnLine(const Vertex2& rayorigin,
                                const Vertex2& direction,
                                const Vertex2& start,
                                const Vertex2& end);

   /*!
    \brief This method checks if a ray (line) intersects with a circular arc. The direction of
    the ray is crucial.

    This method is used for tasks such as extending lines, trimming lines, drawing hatches, etc.
    Hence, it is an essential method for CAD work. If the ray intersects with the circular arc
    between or on the endpoints, the intersection point is returned. If the ray intersects the
    circular arc twice, the closest intersection point is returned.
    \param rayorigin The origin point of the ray. This is the point from which we check if the lines
    intersect. (Position vector of the line)
    \param direction The direction vector in which the ray points.
    \param center The center point of the circular arc.
    \param start The start angle of the circular arc in radians.
    \param end The end angle of the circular arc in radians.
    \return The defined vector if the intersection point exists. If the intersection point does not
    exist, the vector has NaN entries.
    */
   DllExport
   Vertex2 extensionPointOnArc(const Vertex2& rayorigin,
                               const Vertex2& direction,
                               const Vertex2& center,
                               double radius,
                               double start,
                               double end);

   /*!
   \brief This method checks if a ray (line) intersects with an elliptical arc. The direction of
   the ray is crucial.

   This method is used for tasks such as extending lines, trimming lines, drawing hatches, etc.
   Hence, it is an essential method for CAD work. If the ray intersects with the elliptical arc
   between or on the endpoints, the intersection point is returned. If the ray intersects the
   elliptical arc twice, the closest intersection point is returned.
   \param rayorigin The origin point of the ray. This is the point from which we check if the lines
    intersect. (Position vector of the line)
   \param direction The direction vector in which the ray points.
   \param center The center point of the ellipse.
   \param mainAxis The direction and length of the major axis (from the center).
   \param minorAxisRatio The ratio of the minor axis to the major axis.
   \param start The start angle of the elliptical arc in radians.
   \param end The end angle of the elliptical arc in radians.
   \return The defined vector if the intersection point exists. If the intersection point does not
   exist, the vector has NaN entries.
   */
   DllExport
   Vertex2 extensionPointOnEllipse(const Vertex2& rayorigin,
                                   const Vertex2& direction,
                                   const Vertex2& center,
                                   const Vertex2& mainAxis,
                                   double minorAxisRatio,
                                   double start,
                                   double end);

   /*!
    \brief This method calculates the angle bisector between the two direction vectors around a common
    central point. The length of the resulting vector is not normalized.
    \param direction1 The first direction vector.
    \param direction2 The second direction vector.
    \return The angle bisector vector.
    */
   DllExport
   Vertex3 angleBisector(const Vertex3& direction1,
                         const Vertex3& direction2);
   /*!
   \brief This method calculates the angle bisector between the two direction vectors around a common
   central point. The length of the resulting vector is not normalized.
   \param direction1 The first direction vector.
   \param direction2 The second direction vector.
   \return The angle bisector vector.
   */
   DllExport
   Vertex2 angleBisector(const Vertex2& direction1,
                         const Vertex2& direction2);

   /*!
    \brief Calculates the circle parameters centre point and radius given by the 3 points.
    \param center The calculated center point
    \param radius The calculated radius
    \param p1 First point on the circle
    \param p2 Second point on the circle
    \param p3 Third point on the circle
    */
   DllExport
   jm::Status circleParameterBy3Points(Vertex2& center, double& radius,
                                       const Vertex2& p1,
                                       const Vertex2& p2,
                                       const Vertex2& p3);

   /*!
    \brief Calculates the circle center point by the given 2 tangents and radius of the circle.

    The enclosing quadrant of \c p1 and \c p2 contains \c center. If \c center is on \c p1 or \c p2 the direction vector decides

    \param center The calculated center point
    \param radius The radius of the circle
    \param p1 Point on the first tangent
    \param dir1 Direction of the first tangent
    \param p2 Point on the second tangent
    \param dir2  Direction of the second tangent
    */
   DllExport
   jm::Status circleParameterBy2TangentsRadius(Vertex2& center, double radius,
         const Vertex2& p1, const Vertex2& dir1,
         const Vertex2& p2, const Vertex2& dir2);
}

#endif
