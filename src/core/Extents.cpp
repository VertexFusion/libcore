////////////////////////////////////////////////////////////////////////////////////////////////////
// Name:        Extents.cpp
// Library:     Jameo Core Library
// Purpose:     Implementation of Bounding Box
//
// Author:      Uwe Runtemund (2013-today)
// Modified by:
// Created:     22.10.2012
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
