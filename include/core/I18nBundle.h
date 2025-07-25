////////////////////////////////////////////////////////////////////////////////////////////////////
// Name:        I18nBundle.h
// Library:     Jameo Core Library
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

#include "Preferences.h"
#include "Resource.h"

/*!
\brief Quick macro for translation
\deprecated please use jtr
 */
#define Tr(X) jm::I18nBundle::getDefault()->translate(X)

#define jtr(X) jm::I18nBundle::getDefault()->translate(X)

namespace jm
{
   /*!
    \brief This class provides a central resource to translate an application into the local
    language for the user.
    \ingroup app
    */
   class DllExport I18nBundle: public Preferences
   {
      public:

         /*!
          \brief Constructor
          \param language Language String in form: "de-DE"
          */
         explicit I18nBundle(const String& language);

         /*!
         	\brief This method reads a *.mo file and adds the content to this bundle.
         	\param stream The mo resource (file, resource etc.).
         	*/
         void appendMo(Stream* stream);

         String translate(const String& key) const;

         /*!
          \brief returns the application default translation
          */
         static I18nBundle* getDefault();

         /*!
          \brief This method is called on start-up from jm::System to initialise the default
          language. The developer usually do not need to call this.
          */
         static void initDefault();

         /*!
            \brief This method is called on shutdown from jm::System to free the default language.
          */
         static void quitDefault();

         /*!
          \brief Try to examine the language file for given bundle-id
          */
         static jm::Resource transFileByBundleId(const String& filename,
                                                 const String& language);

      private:

         //! Language
         String mLanguage;
   };

}

#endif
