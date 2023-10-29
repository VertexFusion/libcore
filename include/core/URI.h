////////////////////////////////////////////////////////////////////////////////////////////////////
// Name:        URI.h
// Library:     VertexFusion Library
// Purpose:     URI
//
// Author:      Uwe Runtemund (2016-today)
// Modified by:
// Created:     01.04.2016
//
// Copyright:   (c) 2016 Jameo Software, Germany. https://jameo.de
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

#ifndef jm_URL_h
#define jm_URL_h

#include "String.h"

namespace jm
{

	/*!
	 \brief Repräsentation einer URI (Uniform Resource Identifier).
	 Eine URI hat folgenden Aufbau:

	                     hierarchical part
	         ┌───────────────────┴─────────────────────┐
								authority               path
	         ┌───────────────┴───────────────┐┌───┴────┐
	   abc://username:password@example.com:123/path/data?key=value#fragid1
	   └┬┘   └───────┬───────┘ └────┬────┘ └┬┘           └───┬───┘ └──┬──┘
	 scheme  user information     host     port            query   fragment

	   urn:example:mammal:monotreme:echidna
		└┬┘ └──────────────┬───────────────┘
	 scheme              path

	 */
	class URI : public Object
	{

		private:

			/*!
			 \brief Die URI in ihrer vollständigen Darstellung
			 */
			String mUri;

		public:

			URI(const String &uri);

			/*URI(const String& scheme,
			    const String &userInformation,
			    const String &host,
			    const int port,
			    const String &path,
			    const String &query,
			    const String &fragment);*/


	};

}

#endif /* URL_h */
