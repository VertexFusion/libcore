////////////////////////////////////////////////////////////////////////////////////////////////////
// Name:        Transform.h
// Library:     Jameo Core Library
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
    \brief This method converts World Coordinate System (WCS) coordinates to Object Coordinate System (OCS) coordinates.
    \param wcs The input WCS coordinates.
    \param extrusion The extrusion vector used for the transformation.
    \return The corresponding OCS coordinates.
    */
   DllExport
   Vertex3 wcsToOcs(const Vertex3& wcs,
                    const Vertex3& extrusion);

   /*!
    \brief This method converts Object Coordinate System (OCS) coordinates to World Coordinate System (WCS) coordinates.
    \param ocs The input OCS coordinates.
    \param extrusion The extrusion vector used for the transformation.
    \return The corresponding WCS coordinates.
    */
   DllExport
   Vertex3 ocsToWcs(const Vertex3& ocs,
                    const Vertex3& extrusion);

   /*!
    \brief This method calculates the OCS transformation matrix using the "Arbitrary Axis Algorithm" from the DXF reference.
    \param extrusion The extrusion vector used for the transformation.
    */
   DllExport
   Matrix ocsMatrix(const Vertex3& extrusion);

   /*!
    \brief This method calculates the WCS transformation matrix using the "Arbitrary Axis Algorithm" from the DXF reference.
    \param extrusion The extrusion vector used for the transformation.
    \return The WCS transformation matrix.
    */
   DllExport
   Matrix wcsMatrix(const Vertex3& extrusion);

}

#endif
