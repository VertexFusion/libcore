////////////////////////////////////////////////////////////////////////////////////////////////////
// Name:        NURBS.cpp
// Library:     jameo
// Purpose:     NURBS
//
// Author:      Uwe Runtemund (2013-today)
// Modified by:
// Created:     26.01.2013
//
// Copyright:   (c) 2013 Jameo Software, Germany. https://jameo.de
//
//              All rights reserved. The methods and techniques described herein are considered
//              trade secrets and/or confidential. Reproduction or distribution, in whole or in
//              part, is forbidden except by express written permission of Jameo.
////////////////////////////////////////////////////////////////////////////////////////////////////

#include "Precompiled.h"

using namespace jm;

Nurbs::Nurbs(): Object()
{
	mDegree = 1;
	mControlpoints = NULL;
	mControlCount = 0;
	mKnots = NULL;
	mKnotCount = 0;
	mWeights = NULL;
	mWeightCount = 0;
}

Nurbs::Nurbs(uint32 degree,
             Vertex3* controlpoints,
             uint32 controlCount,
             double* knots,
             uint32 knotCount,
             double* weights,
             uint32 weightcount): Object()
{
	mDegree = degree;
	if(mDegree < 1)throw new Exception("Degree of NURBS must be greater 0.");

	mControlCount = controlCount;
	mControlpoints = new Vertex3[mControlCount];
	for(uint32 a = 0; a < mControlCount; a++)mControlpoints[a] = controlpoints[a];

	mKnotCount = knotCount;
	mKnots = new double[mKnotCount];
	for(uint32 a = 0; a < mKnotCount; a++)mKnots[a] = knots[a];

	mWeightCount = weightcount;
	mWeights = new double[mWeightCount];
	for(uint32 a = 0; a < mWeightCount; a++)mWeights[a] = weights[a];
}

Nurbs::~Nurbs()
{
	if(mControlpoints != NULL)delete[] mControlpoints;
	if(mKnots != NULL)delete[] mKnots;
	if(mWeights != NULL)delete[] mWeights;
}

double Nurbs::N(uint32 i, uint32 k, double t)
{

	if(k == 0)
	{
		if(mKnots[i] <= t && t < mKnots[i + 1]) return 1.0;
		return 0.0;
	}

	double a = t - mKnots[i];
	double b = mKnots[i + k] - mKnots[i];
	double c = mKnots[i + k + 1] - t;
	double d = mKnots[i + k + 1] - mKnots[i + 1];

	double N1 = 0;
	double N2 = 0;

	if(!IsEqual(b, 0.0))
	{
		N1 = N(i, k - 1, t) * a / b;
	}

	if(!IsEqual(d, 0.0))
	{
		N2 = N(i + 1, k - 1, t) * c / d;
	}
	return N1 + N2;
}

double Nurbs::R(uint32 i, uint32 k, double t)
{
	double a = mWeights[i] * N(i, k, t);
	double b = 0;

	for(uint32 j = 0; j < mControlCount; j++)b += mWeights[j] * N(j, k, t);

	return a / b;
}

Vertex3 Nurbs::GetPoint(double t)
{
	Vertex3 P;

	for(uint32 i = 0; i < mControlCount; i++)P += mControlpoints[i] * R(i, mDegree, t);

	return P;
}

double Nurbs::GetStart()
{
	return 0;
}

double Nurbs::GetEnd()
{
	if(mKnotCount < 1)return 0;
	double m = mControlCount - mDegree + 2;
	if(m < mKnots[mKnotCount - 1])m = mKnots[mKnotCount - 1];
	return m;
}

uint32 Nurbs::GetControlPointCount()
{
	return mControlCount;
}

