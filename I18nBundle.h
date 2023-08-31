////////////////////////////////////////////////////////////////////////////////////////////////////
// Name:        I18nBundle.h
// Library:     VertexFusion Library
// Purpose:     Declaration of Translation helper class
//
// Author:      Uwe Runtemund (2013-today)
// Modified by:
// Created:     03.06.2013
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

#ifndef jm_I18nBundle_h
#define jm_I18nBundle_h

#include "Properties.h"

/*!
\brief Quick macro for translation
 */
#define Tr(X) jm::I18nBundle::GetDefault()->Translate(X)

namespace jm
{
	/*!
	 \brief This class provides a central resource to translate an application into the local
	 language for the user.
	 \ingroup core
	 */
	class DllExport I18nBundle: public Properties
	{
		public:

			/*!
			 \brief Konstruktor lädt die Ressourcen aus dem Ressourcenverzeichnis
			 \param language Sprachkürzel "de" für Deutsch, "en" für Englisch usw.
			 */
			I18nBundle(const String &appID,
			           const String &name,
			           const String &language,
			           String subfolder = kEmptyString);

			I18nBundle(const File &file, const String &language);

			String Translate(const String& key) const;

			static I18nBundle* GetDefault();

			static void SetDefault(I18nBundle* bundle);

		private:
			/*!
			 \brief Sprachkürzel
			 */
			String mLanguage;
	};

}

#endif
