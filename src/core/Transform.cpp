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

#include "PrecompiledCore.hpp"

using namespace jm;

Matrix jm::ocsMatrix(const jm::Vertex3& extrusion)
{
   // Coordinate system axes of WCS
   jm::Vertex3 wy = jm::Vertex3(0.0, 1.0, 0.0);
   jm::Vertex3 wz = jm::Vertex3(0.0, 0.0, 1.0);

   // Coordinate system axes of OCS
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
   jm::Matrix OCS = ocsMatrix(extrusion);

   //	Matrix out = in * OCS;
   jm::Vertex3 out = OCS * wcs;
   return out;
}

Vertex3 jm::ocsToWcs(const jm::Vertex3& ocs, const jm::Vertex3& extrusion)
{
   jm::Matrix WCS = wcsMatrix(extrusion);

   //	Matrix out = in * WCS;
   jm::Vertex3 out = WCS * ocs;
   return out;
}
