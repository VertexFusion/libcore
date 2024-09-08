////////////////////////////////////////////////////////////////////////////////////////////////////
// Name:        Transform.cpp
// Library:     jameo
// Purpose:     CAD related utilities for coordinate system transformations
//
// Author:      Uwe Runtemund (2014-today)
// Modified by:
// Created:     24.08.2014
//
// Copyright:   (c) 2014 Jameo Software, Germany. https://jameo.de
//
//              All rights reserved. The methods and techniques described herein are considered
//              trade secrets and/or confidential. Reproduction or distribution, in whole or in
//              part, is forbidden except by express written permission of Jameo.
////////////////////////////////////////////////////////////////////////////////////////////////////

#include "Precompiled.hpp"

using namespace jm;

Transform::Transform(): jm::Matrix(4, 4)
{

}

Transform::Transform(const jm::Matrix& m): jm::Matrix(m)
{
   if(m.m != m.n && m.m != 4)throw jm::Exception("Matrix must be 4");
}


jm::Vertex3 Transform::trans(const jm::Vertex3& vertex) const
{
   jm::Vector input = jm::Vector(4);
   input.data[0] = vertex.x;
   input.data[1] = vertex.y;
   input.data[2] = vertex.z;
   input.data[3] = 1.0;

   jm::Matrix mx = jm::Matrix(this);
   jm::Vector output =  mx * input;

   return jm::Vertex3(output.data[0], output.data[1], output.data[2]);
}

double Transform::trans(double value) const
{
   //!\todo  Gibt es eine bessere Lösung?
   jm::Vertex3 p1 = trans(jm::Vertex3(0, 0, 0));
   jm::Vertex3 p2 = trans(jm::Vertex3(value, 0, 0));
   return (p2 - p1).abs();
}

double Transform::transAngle(double angle) const
{
   jm::Vertex3 center = jm::Vertex3(0, 0, 0);
   jm::Vertex3 x = jm::Vertex3(1.0, 0, 0);
   jm::Vertex3 direction = x;
   direction.rotateZ(angle);

   // Change angles
   // TODO: NOT SURE IF THIS IS COMPLIANT IF ROTATION IS NOT PARALLEL TO Z AXIS
   direction = trans(direction);
   center = trans(center);

   direction -= center;

   double newrotation = direction.angleTo(x);

   return newrotation;
}

void Transform::initMoving(const jm::Vertex3& distance)
{
   //Transformationsmatrix:
   // | 1 0 0 x |
   // | 0 1 0 y |
   // | 0 0 1 z |
   // | 0 0 0 1 |
   zeros();
   diag(1.0f);
   set(0, 3, distance.x);
   set(1, 3, distance.y);
   set(2, 3, distance.z);
}

void Transform::initScaling(const jm::Vertex3& factors)
{
   zeros();
   set(0, 0, factors.x);
   set(1, 1, factors.y);
   set(2, 2, factors.z);
   set(3, 3, 1.0);
}

void Transform::initScaling(const jm::Vertex3& basePoint, double factor)
{
   //Transformationsmatrix:

   //1. Verschiebe Basepunkt auf Nullpunkt
   //2. Skaliere
   //3. Verschiebe Basepunkt zurück
   // Zur Erinnerung: Matrizen von rechts nach links multiplizieren...
   // => M3_trans * M2_scale * M1_trans

   // | 1 0 0 x |   | f 0 0 0 |   | 1 0 0 -x |   | f 0 0 x-f*x |
   // | 0 1 0 y | * | 0 f 0 0 | * | 0 1 0 -y |   | 0 f 0 y-f*y |
   // | 0 0 1 z |   | 0 0 f 0 |   | 0 0 1 -z | = | 0 0 f z-f*z |
   // | 0 0 0 1 |   | 0 0 0 1 |   | 0 0 0  1 |   | 0 0 0     1 |

   zeros();
   set(0, 0, factor);
   set(1, 1, factor);
   set(2, 2, factor);

   set(0, 3, basePoint.x - factor * basePoint.x);
   set(1, 3, basePoint.y - factor * basePoint.y);
   set(2, 3, basePoint.z - factor * basePoint.z);
   set(3, 3, 1.0);
}

void Transform::initRotationZ(double angle)
{
   Matrix mx = Matrix::generate3x3RotationZMatrix(angle);
   zeros();
   set(0, 0, mx.get(0, 0));
   set(1, 0, mx.get(1, 0));
   set(2, 0, mx.get(2, 0));
   set(0, 1, mx.get(0, 1));
   set(1, 1, mx.get(1, 1));
   set(2, 1, mx.get(2, 1));
   set(0, 2, mx.get(0, 2));
   set(1, 2, mx.get(1, 2));
   set(2, 2, mx.get(2, 2));
   set(3, 3, 1.0);
}

void Transform::initRotation(const jm::Vertex3& axisPoint,
                             const jm::Vertex3& axisDirection,
                             double angle)
{
   //Transformationsmatrix:

   //1. Verschiebe Basepunkt auf Nullpunkt
   //2. Rotiere
   //3. Verschiebe Basepunkt zurück
   // Zur Erinnerung: Matrizen von rechts nach links multiplizieren...
   // => M3_trans * M2_scale * M1_trans

   // | 1 0 0 x |   | r1 r2 r3 0 |   | 1 0 0 -x |   | r1 r2 r3 x-x*r1-y*r2-z*r3 |
   // | 0 1 0 y | * | r4 r5 r6 0 | * | 0 1 0 -y |   | r3 r4 r6 y-x*r4-y*r5-z*r6 |
   // | 0 0 1 z |   | r7 r8 r9 0 |   | 0 0 1 -z | = | r7 r8 r9 z-x*r7-y*r8-z*r9 |
   // | 0 0 0 1 |   |  0  0  0 1 |   | 0 0 0  1 |   |  0  0  0     1            |

   double x = axisPoint.x;
   double y = axisPoint.y;
   double z = axisPoint.z;

   Matrix mx = Matrix::generate3x3RotationMatrix(angle, axisDirection);
   zeros();
   set(0, 0, mx.get(0, 0));
   set(1, 0, mx.get(1, 0));
   set(2, 0, mx.get(2, 0));
   set(0, 1, mx.get(0, 1));
   set(1, 1, mx.get(1, 1));
   set(2, 1, mx.get(2, 1));
   set(0, 2, mx.get(0, 2));
   set(1, 2, mx.get(1, 2));
   set(2, 2, mx.get(2, 2));
   set(0, 3, x - x * mx.get(0, 0) - y * mx.get(0, 1) - z * mx.get(0, 2));
   set(1, 3, y - x * mx.get(1, 0) - y * mx.get(1, 1) - z * mx.get(1, 2));
   set(2, 3, z - x * mx.get(2, 0) - y * mx.get(2, 1) - z * mx.get(2, 2));
   set(3, 3, 1.0);

}

void Transform::initMirroring(const jm::Vertex3& planePoint,
                              const jm::Vertex3& planeNormal)
{
   //Transformationsmatrix:

   //1. Verschiebe Basepunkt auf Nullpunkt
   //2. Spiegle
   //3. Verschiebe Basepunkt zurück
   // Zur Erinnerung: Matrizen von rechts nach links multiplizieren...
   // => M3_trans * M2_scale * M1_trans

   // Koordinatenform der Ebene
   // a*x + b*y + c*z = d

   // Normal form of the plane
   // (x - p) * n = 0
   // p: Location vector of the plane, n: Normal vector of the plane, x:Arbitrary vector
   //
   // a = n1, b=n2, c=n3, d=p1*n1+p2*n2+p3*n3

   // For a plane with d=0, the mirror matrix is defined as follows:
   //
   //     | 1-2a^2  -2ab   -2ac  |
   // A = | -2ab   1-2b^2  -2bc  |
   //     | -2ac    -2bc  1-2c^2 |
   //

   //Siehe auch https://en.wikipedia.org/wiki/Transformation_matrix

   double a = planeNormal.x;
   double b = planeNormal.y;
   double c = planeNormal.z;
   double d = - planePoint.x * planeNormal.x
              - planePoint.y * planeNormal.y
              - planePoint.z * planeNormal.z;

   zeros();
   set(0, 0, 1.0 - 2.0 * a * a);
   set(1, 0, -2.0 * a * b);
   set(2, 0, -2.0 * a * c);
   set(0, 1, -2.0 * b * a);
   set(1, 1, 1.0 - 2.0 * b * b);
   set(2, 1, -2.0 * b * c);
   set(0, 2, -2.0 * a * c);
   set(1, 2, -2.0 * b * c);
   set(2, 2, 1.0 - 2.0 * c * c);
   set(0, 3, -2.0 * a * d);
   set(1, 3, -2.0 * b * d);
   set(2, 3, -2.0 * c * d);
   set(3, 3, 1.0);
}


void Transform::initWcs(const jm::Vertex3& extrusion)
{
   Matrix mx = wcsMatrix(extrusion);
   zeros();
   set(0, 0, mx.get(0, 0));
   set(1, 0, mx.get(1, 0));
   set(2, 0, mx.get(2, 0));
   set(0, 1, mx.get(0, 1));
   set(1, 1, mx.get(1, 1));
   set(2, 1, mx.get(2, 1));
   set(0, 2, mx.get(0, 2));
   set(1, 2, mx.get(1, 2));
   set(2, 2, mx.get(2, 2));
   set(3, 3, 1.0);
}

void Transform::initIdentity()
{
   zeros();
   diag(1.0f);
}


Matrix jm::ocsMatrix(const jm::Vertex3& extrusion)
{
   //Koordinatenachsen des WCS
   jm::Vertex3 wy = jm::Vertex3(0.0, 1.0, 0.0);
   jm::Vertex3 wz = jm::Vertex3(0.0, 0.0, 1.0);

   //Koordinatenachsen des OCS
   jm::Vertex3 ox;
   jm::Vertex3 oy;
   jm::Vertex3 oz = extrusion;

   //Arbitrary Axis algorithm
   double b = 1.0 / 64.0;
   if(std::abs(extrusion.x) < b && std::abs(extrusion.y) < b) ox = wy.crossProduct(extrusion);
   else ox = wz.crossProduct(extrusion);
   ox.normalize();
   oy = extrusion.crossProduct(ox);
   oy.normalize();

   jm::Matrix ocs = jm::Matrix(ox, oy, oz, true);
   return ocs;
}

Matrix jm::wcsMatrix(const jm::Vertex3& extrusion)
{
   //WCS = OCS^-1
   jm::Matrix WCS = ocsMatrix(extrusion);
   WCS.inverse();
   return WCS;
}


Vertex3 jm::wcsToOcs(jm::Vertex3 wcs,
                     jm::Vertex3 extrusion)
{
   /*	Matrix in = Matrix( 1, 3 );
    in.Set( 0, 0, wcs.x );
    in.Set( 0, 1, wcs.y );
    in.Set( 0, 2, wcs.z );*/

   jm::Matrix OCS = ocsMatrix(extrusion);

   //	Matrix out = in * OCS;
   jm::Vertex3 out = OCS * wcs;
   return out;
   //	Vertex3 ocs = Vertex3( out.Get( 0, 0 ), out.Get( 0, 1 ), out.Get( 0, 2 ) );
   //	return ocs;
}

Vertex3 jm::ocsToWcs(const jm::Vertex3& ocs, const jm::Vertex3& extrusion)
{
   /*	Matrix in = Matrix( 1, 3 );
    in.Set( 0, 0, ocs.x );
    in.Set( 0, 1, ocs.y );
    in.Set( 0, 2, ocs.z );*/

   jm::Matrix WCS = wcsMatrix(extrusion);

   //	Matrix out = in * WCS;
   jm::Vertex3 out = WCS * ocs;
   return out;

   //	Vertex3 wcs = Vertex3( out.Get( 0, 0 ), out.Get( 0, 1 ), out.Get( 0, 2 ) );

   //	return wcs;
}
