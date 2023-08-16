////////////////////////////////////////////////////////////////////////////////////////////////////
// Name:        CharArray.h
// Library:     VertexFusion Library
// Purpose:     Handling arrays of characters
//
// Author:      Uwe Runtemund (2013-today)
// Modified by:
// Created:     18.01.2013
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

#ifndef jm_CharArray_h
#define jm_CharArray_h

#include "Types.h"

namespace jm
{
	/*!
	 \brief This data type represents a Unicode character array. It is deliberately used in 
	 distinction to the character string and serves as a supporting class when encoding and 
	 decoding character strings.
	 \ingroup core
	 */
	struct CharArray
	{
		/*!
		 \brief The length of the array.
		 */
		uint32 length;

		/*!
		 \brief The array itself.
		 */
		uint16* buffer;

		/*!
		 \brief Constructor. Everything remains 0 or NULL.
		 */
		CharArray();

		/*!
		 \brief Constructor create an unitialized array.
		 \param length The length of the array
		 */
		CharArray(uint32 length);

		/*!
		 \brief Copy constructor
		 */
		CharArray(const CharArray &another);

		/*!
		 \brief Destructor
		 */
		virtual ~CharArray();

		CharArray &operator=(const CharArray &another);
	};


}


#endif
