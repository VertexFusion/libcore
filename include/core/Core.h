////////////////////////////////////////////////////////////////////////////////////////////////////
// Name:        Core.h
// Library:     Jameo Core Library
// Purpose:     Header for core classes
//
// Author:      Uwe Runtemund (2012-today)
// Modified by:
// Created:     18.10.2012
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

// astyle -A1 -s3 -C -S -N -xg -U -Y -xw -p *

#ifndef jm_Core_h
#define jm_Core_h


#include "Types.h"

#include "Array.h"
#include "Base64.h"
#include "ByteArray.h"
#include "CharArray.h"
#include "Charset.h"
#include "Colour.h"
#include "CRC.h"
#include "Date.h"
#include "Deflater.h"
#include "Diff.h"
#include "DiffBacktrace.h"
#include "DiffDiag.h"
#include "DiffDistance.h"
#include "DiffInfo.h"
#include "Document.h"
#include "Exception.h"
#include "Geometry.h"
#include "I18nBundle.h"
#include "Inflater.h"
#include "Integer.h"
#include "Math.h"
#include "Matrix.h"
#include "MemoryStream.h"
#include "Mutex.h"
#include "Nurbs.h"
#include "PaintingBackend.h"
#include "SAXParser.h"
#include "Serializer.h"
#include "String.h"
#include "StringTokenizer.h"
#include "System.h"
#include "Test.h"
#include "Thread.h"
#include "URI.h"
#include "Vector.h"
#include "Vertex2.h"
#include "Vertex3.h"
#include "XMLWriter.h"
#include "ZipFile.h"


/*! \mainpage Jameo Core Library

Welcome to the Jameo Core Library Documentation.

The Jameo Core Library is a cross-plattform C++ library under the MIT licence, which provide basic
datatypes and concepts often used in our software.

This includes the following basic data types or enhancements:

- Additional basic datatypes: string, date, file, colour, ...
- Basic linear algebra (vectors, matrices) and geometry functions
- \ref datamgr including Undo, Redo and Transactions
- Simple XML in- and out
- Mutex and Threads
- Diff algorithm
- Addition random stuff
- \ref test "Unit tests"

\author  Uwe Runtemund
\copyright 2012-2023 Jameo Software, Germany. https://jameo.de

Legal notes for this website: https://jameo.de/en/about/
*/


/*!
 \defgroup diff Diff

 \brief Collection of classes related to the diff algorithm.
 */

#endif
