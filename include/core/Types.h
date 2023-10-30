////////////////////////////////////////////////////////////////////////////////////////////////////
// Name:        Types.h
// Library:     Jameo Core Library
// Purpose:     Common Type Definitions
//
// Author:      Uwe Runtemund (2012-today)
// Modified by:
// Created:     09.11.2012
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

#include <iostream>
#include <limits>

#ifndef jm_Types_h
#define jm_Types_h

//! ASCII Constants for different operations
#define kTxtClearScreen "\033[2J\033[H" // CLEAR SCREEN AND CURSOR TO HOME

//! ASCII Constants for colors in the console stream.
#define kTxtReset "\033[0m"
#define kTxtBold "\033[1m"
#define kTxtRed "\033[31m"
#define kTxtGreen "\033[32m"
#define kTxtYellow "\033[33m"
#define kTxtBlue "\033[34m"
#define kTxtMagenta "\033[35m"
#define kTxtCyan "\033[36m"

#define kTxtBrightMagenta "\033[95m"


#ifndef M_2PI
#define M_2PI    2.0*3.14159265358979323846264338328 /*!<  Defines a value for "2 x pi" */
#endif

#ifndef M_1_5_PI
#define M_1_5_PI    1.5*3.14159265358979323846264338328
#endif

#ifndef M_PI
#define M_PI    3.14159265358979323846264338328
#endif

#ifndef M_PI_2
#define M_PI_2    1.57079632679489661923132169164
#endif

#ifndef M_PI_4
#define M_PI_4    0.785398163397448309616
#endif

#ifndef UINT8_MAX
#define UINT8_MAX 255
#endif

#ifndef UINT16_MAX
#define UINT16_MAX 65535
#endif

#ifndef UINT32_MAX
#define UINT32_MAX 4294967295U
#endif

#ifndef UINT64_MAX
#define UINT64_MAX 18446744073709551615ULL
#endif


#ifndef NULL
#define NULL 0
#endif

#ifndef NAN
static const unsigned long __jmnan[2] = {0xffffffff, 0x7fffffff};
#define NAN (*(const double *) __jmnan)
#endif

// Note: This value is not valid for double.
#ifndef POSITIVE_INFINITY
static const unsigned long __pinf[2] = {0x7ff00000, 0x00000000};
#define POSITIVE_INFINITY (*(const double *) __pinf)
#endif

// Note: This value is not valid for double.
#ifndef NEGATIVE_INFINITY
static const unsigned long __ninf[2] = {0xfff00000, 0x00000000};
#define NEGATIVE_INFINITY (*(const double *) __ninf)
#endif

typedef char                int8;
typedef unsigned char       uint8;
typedef short               int16;
typedef unsigned short      uint16;
typedef int                 int32;
typedef unsigned int        uint32;

#ifndef indeterminate
#define indeterminate -1
#endif

#ifndef BoolFalse
#define BoolFalse 0
#endif

#ifndef BoolTrue
#define BoolTrue 1
#endif

#ifdef __APPLE__

#define DllExport
typedef __int64_t           int64;
typedef __uint64_t          uint64;
typedef long                slong;
typedef unsigned long       ulong;
#define WITHULONG

#elif defined __linux__

#define DllExport
typedef __int64_t           int64;
typedef __uint64_t          uint64;

#elif defined _WIN32

#define DllExport   __declspec( dllexport )
typedef __int64           int64;
typedef unsigned __int64  uint64;
typedef long                slong;
typedef unsigned long       ulong;
#define WITHULONG

#endif


namespace jm
{
	/*!
	\brief This enumeration list all errors posted by this library.
	\note Do no use numbers of this enum for storing persistent data. Numbers are changing.
	*/
	enum VxfErrorStatus
	{
		// for usage as boolean replacement
		eNo = 0,       /*!< Same meansing as a bool \c false */
		eOK = 1,       /*!< All ok. Operation finished as excepted. */
		eYes = 1,      /*!< Same meaning as a bool "true" (same as eOK) */

		// General Errors
		eError,					/*!< Operation not done. Unspecified error occured. */
		eNotAllowed,			/*! < Operation not allowed. */
		eNotImplemented,		/*!< Operation not done. Not implemented. */
		eNullPointer,			/*!< Operation not done. Null pointer found. */
		eIndexOutOfBounds,	/*!< Operation not done. Array overflow underflow and similar */

		// DWG related
		eNullHandle,			/*!< Operation not done. Null handle found. */
		eDuplicatHandle,		/*!< Operation not done. Duplicate handle found. */
		eOwnerMismatch,		/*!< Operation not done. Owner of object points to invalid owner. */

		eDuplicateKey,			/*!< Operation not done. Duplicate key found. E.g. becaue you try to
									     name a new DwgLayer with a name, a layer already exists. */
		eInvalidKey,			/*!< Operation not done. Key has invalid value. E.g. because you try to
										  use a group code in a DwgXRecord for a specific datatype, but the
										  code is mapped to another data type, or you try to name a colour
										  although the colour name is not defined in a colour book. */
		eInvalidInput,			/*!< Operation not done. Input is invalid. */
		eNotFound,				/*!< Operation not done. The entry you are looking for was not found. */
		eNotChanged,			/*!< Operation not done. Value not changed. Often not really an error,
										  but a notice. */

		eOnLockedLayer,		/*!< Operation not done. The entity is on a locked layer. */
		eUndefinedBlock,		/*!< Operation not done. The requested block is undefined. */
		eUndefinedLineType,	/*!< Operation not done. The requested DwgLineType is undefined. */
		eUndefinedLayer,		/*!< Operation not done. The requested DwgLayer is undefined. */
		eWrongObjectType,		/*!< Operation not done. The provided object has not the expected object
									     type. */

		// Structure related
		eNoElementsForTransformationProvided,
		eTargetNodeForCopyOperationNotFound,
		eTargetBeamForCopyOperationNotFound,
		eInvalidVectorInput,
		eInvalidAngleInput,
		eInvalidFactorInput

	};


	/*!
	\brief This class is intended to be used for comparisons.
	*/
	template <class T>
	class Comparable
	{
		public:

			Comparable() {};

			virtual ~Comparable() {};

			virtual int32 CompareTo(const T &other) const = 0;
	};

}

#endif

