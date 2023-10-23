////////////////////////////////////////////////////////////////////////////////////////////////////
// Name:        Extents.cpp
// Library:     vertexfusion
// Purpose:     Implementation of Bounding Box
//
// Author:      Uwe Runtemund (2013-today)
// Modified by:
// Created:     22.10.2012
//
// Copyright:   (c) 2012 Jameo Software, Germany. https://jameo.de
//              (c) 2023 VertexFusion Project
//
// Licence:     LGPL V2.1
//
////////////////////////////////////////////////////////////////////////////////////////////////////

#include "Precompiled.h"

using namespace jm;

Extents::Extents()
{
	mPtMin = Vertex3(1E90, 1E90, 1E90);
	mPtMax = Vertex3(-1E90, -1E90, -1E90);
}

void Extents::Add(const Vertex2& pt)
{
	mPtMin.x = Min(mPtMin.x, pt.x);
	mPtMin.y = Min(mPtMin.y, pt.y);

	mPtMax.x = Max(mPtMax.x, pt.x);
	mPtMax.y = Max(mPtMax.y, pt.y);
}

void Extents::Add(const Vertex3& pt)
{
	mPtMin.x = std::min(mPtMin.x, pt.x);
	mPtMin.y = std::min(mPtMin.y, pt.y);
	mPtMin.z = std::min(mPtMin.z, pt.z);

	mPtMax.x = std::max(mPtMax.x, pt.x);
	mPtMax.y = std::max(mPtMax.y, pt.y);
	mPtMax.z = std::max(mPtMax.z, pt.z);
}

void Extents::Add(const Extents& ext)
{
	if(!ext.IsValid())return;

	Add(ext.mPtMin);
	Add(ext.mPtMax);
}

Vertex3 Extents::GetMinPoint()const
{
	return mPtMin;
}

Vertex3 Extents::GetMaxPoint()const
{
	return mPtMax;
}

bool Extents::IsValid()const
{
	return mPtMin.x < 1E89;
}
