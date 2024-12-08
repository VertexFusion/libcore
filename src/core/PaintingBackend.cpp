////////////////////////////////////////////////////////////////////////////////////////////////////
// Name:        PaintingBackend.cpp
// Library:     jameo
// Purpose:     Drawing Interface for draw CAD drawings to different targets (Backends)
//
// Author:      Uwe Runtemund (2012-today)
// Modified by:
// Created:     21.07.2017
//
// Copyright:   (c) 2017 Jameo Software, Germany. https://jameo.de
//
//              All rights reserved. The methods and techniques described herein are considered
//              trade secrets and/or confidential. Reproduction or distribution, in whole or in
//              part, is forbidden except by express written permission of Jameo.
////////////////////////////////////////////////////////////////////////////////////////////////////

#include "PrecompiledCore.hpp"

using namespace jm;

PaintingBackend::PaintingBackend(): Object()
{
   mTransformstack = new std::vector<Transform>();
   mBuffer = new std::vector<BufferElement>();
}

PaintingBackend::~PaintingBackend()
{
   delete mTransformstack;
   delete mBuffer;
}
