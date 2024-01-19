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

#include "Precompiled.h"

using namespace jm;

Transform::Transform(): jm::Matrix(4, 4)
{

}

Transform::Transform(const jm::Matrix &m): jm::Matrix(m)
{
	if(m.m != m.n && m.m != 4)throw new jm::Exception("Matrix must be 4");
}


jm::Vertex3 Transform::Trans(const jm::Vertex3 &vertex) const
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

double Transform::Trans(const double &value) const
{
	//!\todo  Gibt es eine bessere Lösung?
	jm::Vertex3 p1 = Trans(jm::Vertex3(0, 0, 0));
	jm::Vertex3 p2 = Trans(jm::Vertex3(value, 0, 0));
	return (p2 - p1).Abs();
}

Double Transform::TransAngle(const Double& angle) const
{
	jm::Vertex3 center = jm::Vertex3(0,0,0);
	jm::Vertex3 x = jm::Vertex3(1.0, 0, 0);
	jm::Vertex3 direction = x;
	direction.RotateZ(angle);

	// Change angles
	// TODO: NOT SHURE IF THIS IS COMPLIANT IF ROTATION IS NOT PARALLEL TO Z AXIS
	direction = Trans(direction);
	center = Trans(center);

	direction -= center;

	Double newrotation = direction.AngleTo(x);

	return newrotation;
}

void Transform::InitMoving(const jm::Vertex3 &distance)
{
	//Transformationsmatrix:
	// | 1 0 0 x |
	// | 0 1 0 y |
	// | 0 0 1 z |
	// | 0 0 0 1 |
	Zeros();
	Diag(1.0f);
	Set(0, 3, distance.x);
	Set(1, 3, distance.y);
	Set(2, 3, distance.z);
}

void Transform::InitScaling(const jm::Vertex3 &factors)
{
	Zeros();
	Set(0, 0, factors.x);
	Set(1, 1, factors.y);
	Set(2, 2, factors.z);
	Set(3, 3, 1.0);
}

void Transform::InitScaling(const jm::Vertex3 &basePoint, double factor)
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

	Zeros();
	Set(0, 0, factor);
	Set(1, 1, factor);
	Set(2, 2, factor);

	Set(0, 3, basePoint.x - factor * basePoint.x);
	Set(1, 3, basePoint.y - factor * basePoint.y);
	Set(2, 3, basePoint.z - factor * basePoint.z);
	Set(3, 3, 1.0);
}

void Transform::InitRotationZ(double angle)
{
	Matrix mx = Matrix::Generate3x3RotationZMatrix(angle);
	Zeros();
	Set(0, 0, mx.Get(0, 0));
	Set(1, 0, mx.Get(1, 0));
	Set(2, 0, mx.Get(2, 0));
	Set(0, 1, mx.Get(0, 1));
	Set(1, 1, mx.Get(1, 1));
	Set(2, 1, mx.Get(2, 1));
	Set(0, 2, mx.Get(0, 2));
	Set(1, 2, mx.Get(1, 2));
	Set(2, 2, mx.Get(2, 2));
	Set(3, 3, 1.0);
}

void Transform::InitRotation(const jm::Vertex3 &axisPoint,
                             const jm::Vertex3 &axisDirection,
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

	Matrix mx = Matrix::Generate3x3RotationMatrix(angle, axisDirection);
	Zeros();
	Set(0, 0, mx.Get(0, 0));
	Set(1, 0, mx.Get(1, 0));
	Set(2, 0, mx.Get(2, 0));
	Set(0, 1, mx.Get(0, 1));
	Set(1, 1, mx.Get(1, 1));
	Set(2, 1, mx.Get(2, 1));
	Set(0, 2, mx.Get(0, 2));
	Set(1, 2, mx.Get(1, 2));
	Set(2, 2, mx.Get(2, 2));
	Set(0, 3, x - x * mx.Get(0, 0) - y * mx.Get(0, 1) - z * mx.Get(0, 2));
	Set(1, 3, y - x * mx.Get(1, 0) - y * mx.Get(1, 1) - z * mx.Get(1, 2));
	Set(2, 3, z - x * mx.Get(2, 0) - y * mx.Get(2, 1) - z * mx.Get(2, 2));
	Set(3, 3, 1.0);

}

void Transform::InitMirroring(const jm::Vertex3 &planePoint,
                              const jm::Vertex3 &planeNormal)
{
	//Transformationsmatrix:

	//1. Verschiebe Basepunkt auf Nullpunkt
	//2. Spiegle
	//3. Verschiebe Basepunkt zurück
	// Zur Erinnerung: Matrizen von rechts nach links multiplizieren...
	// => M3_trans * M2_scale * M1_trans

	// Koordinatenform der Ebene
	// a*x + b*y + c*z = d

	// Normalenform der Ebene
	// (x - p) * n = 0 (p: Ortsvektor der Ebene, n: Normalenvektor der Ebene, x:Beliebiger Wekter
	//
	// a = n1, b=n2, c=n3, d=p1*n1+p2*n2+p3*n3

	//Für eine Ebene mit d=0 ist die Spiegelmatrix wie folgt definiert:
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

	Zeros();
	Set(0, 0, 1.0 - 2.0 * a * a);
	Set(1, 0, -2.0 * a * b);
	Set(2, 0, -2.0 * a * c);
	Set(0, 1, -2.0 * b * a);
	Set(1, 1, 1.0 - 2.0 * b * b);
	Set(2, 1, -2.0 * b * c);
	Set(0, 2, -2.0 * a * c);
	Set(1, 2, -2.0 * b * c);
	Set(2, 2, 1.0 - 2.0 * c * c);
	Set(0, 3, -2.0 * a * d);
	Set(1, 3, -2.0 * b * d);
	Set(2, 3, -2.0 * c * d);
	Set(3, 3, 1.0);
}


void Transform::InitWCS(const jm::Vertex3 &extrusion)
{
	Matrix mx = WCSMatrix(extrusion);
	Zeros();
	Set(0, 0, mx.Get(0, 0));
	Set(1, 0, mx.Get(1, 0));
	Set(2, 0, mx.Get(2, 0));
	Set(0, 1, mx.Get(0, 1));
	Set(1, 1, mx.Get(1, 1));
	Set(2, 1, mx.Get(2, 1));
	Set(0, 2, mx.Get(0, 2));
	Set(1, 2, mx.Get(1, 2));
	Set(2, 2, mx.Get(2, 2));
	Set(3, 3, 1.0);
}

void Transform::InitIdentity()
{
	Zeros();
	Diag(1.0f);
}


Matrix jm::OCSMatrix(const jm::Vertex3& extrusion)
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
	if(std::abs(extrusion.x) < b && std::abs(extrusion.y) < b) ox = wy.CrossProduct(extrusion);
	else ox = wz.CrossProduct(extrusion);
	ox.Normalize();
	oy = extrusion.CrossProduct(ox);
	oy.Normalize();

	jm::Matrix ocs = jm::Matrix(ox, oy, oz, true);
	return ocs;
}

Matrix jm::WCSMatrix(const jm::Vertex3 &extrusion)
{
	//WCS = OCS^-1
	jm::Matrix WCS = OCSMatrix(extrusion);
	WCS.Inverse();
	return WCS;
}


Vertex3 jm::WCSToOCS(jm::Vertex3 wcs,
                     jm::Vertex3 extrusion)
{
	/*	Matrix in = Matrix( 1, 3 );
	 in.Set( 0, 0, wcs.x );
	 in.Set( 0, 1, wcs.y );
	 in.Set( 0, 2, wcs.z );*/

	jm::Matrix OCS = OCSMatrix(extrusion);

	//	Matrix out = in * OCS;
	jm::Vertex3 out = OCS * wcs;
	return out;
	//	Vertex3 ocs = Vertex3( out.Get( 0, 0 ), out.Get( 0, 1 ), out.Get( 0, 2 ) );
	//	return ocs;
}

Vertex3 jm::OCSToWCS(const jm::Vertex3& ocs, const jm::Vertex3& extrusion)
{
	/*	Matrix in = Matrix( 1, 3 );
	 in.Set( 0, 0, ocs.x );
	 in.Set( 0, 1, ocs.y );
	 in.Set( 0, 2, ocs.z );*/

	jm::Matrix WCS = WCSMatrix(extrusion);

	//	Matrix out = in * WCS;
	jm::Vertex3 out = WCS * ocs;
	return out;

	//	Vertex3 wcs = Vertex3( out.Get( 0, 0 ), out.Get( 0, 1 ), out.Get( 0, 2 ) );

	//	return wcs;
}
