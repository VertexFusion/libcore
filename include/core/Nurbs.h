////////////////////////////////////////////////////////////////////////////////////////////////////
// Name:        NURBS.h
// Library:     Jameo Core Library
// Purpose:     NURBS
//
// Author:      Uwe Runtemund (2013-today)
// Modified by:
// Created:     26.01.2013
//
// Copyright:   (c) 2013 Jameo Software, Germany. https://jameo.de
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

#ifndef jm_Nurbs_h
#define jm_Nurbs_h

#include "Types.h"
#include "Vertex3.h"
#include "Object.h"

namespace jm
{

   /*!
    \brief NURBS (nonuniform rational basis splines) are a generalized form of B-Splines.
    They allow for modeling many curves, including projected forms. DXF splines, for example, are based on NURBS.
    This class provides functions and methods to work with NURBS.

    Advantages of NURBS (http://www-lehre.inf.uos.de/~cg/2006/PDF/kap-07.pdf):

    - NURBS are a generalization of B-Splines. When hi = 1 for all i, the NURBS curve reduces to the corresponding B-Spline curve.
    - NURBS are invariant under perspective projection. This means that not all curve points need to be projected, only the control points need to be projected and then connected to form a curve.
    - NURBS are capable of describing circles (unlike non-rational B-Splines).
    */
   class DllExport Nurbs: public Object
   {
      public:

         /*!
          \brief Default constructor for the Nurbs class.
          */
         Nurbs();

         /*!
          \brief Constructor for the Nurbs class.
          \param degree The degree of the polynomial.
          \param controlpoints An array of control points.
          \param controlCount The length of the controlpoints array.
          \param knots An array of knots.
          \param knotCount The length of the knots array.
          \param weights An array of weights.
          \param weightCount The length of the weights array.
          */
         Nurbs(uint32 degree,
               Vertex3* controlpoints,
               uint32 controlCount,
               double* knots,
               uint32 knotCount,
               double* weights,
               uint32 weightCount);

         /*!
          \brief Destructor
          */
         ~Nurbs() override;

         /*!
          \brief Returns a point on the curve at a given parameter value.
          \param t The parameter value on the curve. Should be in the range [0, t_max].
          \return The point on the curve at the given parameter value.
          */
         Vertex3 point(double t);

         /*!
          \brief This method returns the smallest value of t. In this case, it returns 0.
          */
         double start();

         /*!
           \brief This method returns the maximum value of t.
           */
         double end();

         /*!
          \brief Returns the number of control points.
          */
         uint32 controlPointCount();

         /*!
          \brief Returns the knot count
          */
         uint32 knotCount()const;

         /*!
          \brief returns a knot
          */
         double knot(uint32 index)const;

      private:

         /*!
          \brief Degree of the polynomial for the NURBS curve.
          */
         uint32 mDegree;

         /*!
          \brief Control points of curve.
          */
         Vertex3* mControlpoints;

         /*!
          \brief Number of control points.
          */
         uint32 mControlCount;

         //! Knot vector
         double* mKnots;

         //! Knot count.
         uint32 mKnotCount;

         /*!
          \brief The weights of the control points. For B-Splines, all weights are 1.
          */
         double* mWeights;

         /*!
          \brief The number of weights.
          */
         uint32 mWeightCount;

         /*!
          \brief This method returns the value of N_i,k(t).
          \param i The index of the control point.
          \param k The degree of the polynomial for which N is returned. (Not necessarily the degree of the NURBS)
          \param t The parameter value along the curve.
          \return The value of N_i,k(t) at the given parameter value.
          */
         double N(uint32 i, uint32 k, double t);

         /*!
          \brief This method returns the weight of the control points R_i,k(t).
          \param i The index of the control point.
          \param k The degree of the polynomial for which R is returned.
          \param t The parameter value along the curve.
          \return The weight of the control point at the given parameter value.
          */
         double R(uint32 i, uint32 k, double t);
   };

}

#endif
