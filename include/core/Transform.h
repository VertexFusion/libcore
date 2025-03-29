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
   Vertex3 wcsToOcs(Vertex3 wcs,
                    Vertex3 extrusion);

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

   /*!
    \brief This class is an abstraction of the Matrix class and extends it with additional functions.
    \details The Transform class represents a transformation matrix used for coordinate system transformations.
             It provides methods for translation, scaling, rotation, mirroring, and initialization of the matrix.
             The matrix can be used to transform 3D points and angles in both World Coordinate System (WCS) and Object Coordinate System (OCS).
    */
   struct DllExport Transform : public Matrix
   {

      /*!
       \brief Default constructor for the Transform class.
       */
      Transform();

      /*!
       \brief Constructor for the Transform class.
       */
      explicit Transform(const Matrix& m);

      /*!
       \brief This method transforms the vertex using the 4x4 transformation matrix.
       \param vertex The input vertex to be transformed.
       \return The transformed vertex.
       */
      Vertex3 trans(const Vertex3& vertex) const;

      /*!
       \brief This method transforms the number using the 4x4 transformation matrix.
       X value is used.
       \param value The input number to be transformed.
       \return The transformed number.
       */
      double trans(double value) const;

      /*!
       \brief Transform a rotation angle about the Z-Axis of LCS as usually needed by arcs or texts.
       \param angle Rotation angle in radians.
       \return The transformed angle.
       */
      double transAngle(double angle) const;

      /*!
       \brief Initializes this transformation as a translation.
       \param distance The distance to translate by.
       */
      void initMoving(const Vertex3& distance);

      /*!
       \brief Initializes this transformation as scaling by different factors along the x, y, and z axes.
       \param factors The scaling factors along the x, y, and z axes.
       */
      void initScaling(const Vertex3& factors);

      /*!
       \brief Initializes this transformation as scaling around a base point.
       \param basePoint The point around which the scaling is performed.
       \param factor The scaling factor.
       */
      void initScaling(const Vertex3& basePoint, double factor);

      /*!
       \brief Initializes this Transform as a rotation matrix around the Z-axis.
       \param angle The rotation angle in radians.
       */
      void initRotationZ(double angle);

      /*!
       \brief Initializes this Transform as a rotation matrix.
       \param axisPoint The origin vector of the rotation axis.
       \param axisDirection The normalized direction vector of the rotation axis.
       \param angle The rotation angle in radians.
       */
      void initRotation(const Vertex3& axisPoint,
                        const Vertex3& axisDirection,
                        double angle);
      /*!
       \brief Initializes this Transform as a mirroring matrix.
       \param planePoint The point on the mirror plane.
       \param planeNormal The normal vector of the mirror plane.
       \details This method initializes the transformation matrix as a mirroring matrix, which reflects points across a mirror plane.
             The mirror plane is defined by a point on the plane (planePoint) and the normal vector of the plane (planeNormal).
             The resulting matrix can be used to mirror 3D points and objects.
       */
      void initMirroring(const Vertex3& planePoint,
                         const Vertex3& planeNormal);

      /*!
       \brief Initializes this Transform as a World Coordinate System (WCS) matrix.
       \param extrusion The extrusion vector used for the transformation.
       \details This method initializes the transformation matrix as a WCS matrix, which represents the coordinate system transformation from Object Coordinate System (OCS) to WCS.
          The extrusion vector is used to define the direction of the Z-axis in the WCS.
          The resulting matrix can be used to transform 3D points and angles from OCS to WCS.
       */
      void initWcs(const Vertex3& extrusion);

      /*!
       \brief Initializes this transformation as an identity matrix.
       \details An identity matrix is a square matrix in which all the elements of the principal diagonal are ones and all other elements are zeros.
             When a vector or point is multiplied by an identity matrix, the result is the same vector or point.
             This method sets the transformation matrix to an identity matrix, effectively resetting any previous transformations applied.
       */
      void initIdentity();

   };

}

#endif
