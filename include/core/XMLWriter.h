////////////////////////////////////////////////////////////////////////////////////////////////////
// Name:        XMLWriter.h
// Library:     Jameo Core Library
// Purpose:     Write XML-Files
//
// Author:      Uwe Runtemund (2020-today)
// Modified by:
// Created:     27.12.2020
//
// Copyright:   (c) 2020 Jameo Software, Germany. https://jameo.de
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

#ifndef jm_XMLWriter_h
#define jm_XMLWriter_h

#include "String.h"
#include "Stack.h"

namespace jm
{

   /*!
    \brief This class provides methods to write XML data.
    \details The XMLWriter class allows you to write XML files by providing various methods to handle different aspects of XML writing.
    */

   class DllExport XMLWriter: public Object
   {
      public:

          /*!
           \brief Constructor.
           \param output The \c Stream where the XML data should be written.
           */
         explicit XMLWriter(Stream* output);

         /*!
          \brief Destructor.
          */
         ~XMLWriter() override;

          /*!
           \brief This method must be called at the beginning. It opens the stream if it hasn't been opened yet.
           \return true if everything is fine.
           */
          bool startDocument();

          /*!
           \brief This method must be called at the end. It closes the stream.
           \return true if the stream is successfully closed.
           */
         bool endDocument();

          /*!
           \brief Increase indentation level.
           \details In XML, whitespaces are sometimes significant. The significance of whitespaces depends on the document. This method performs an indentation and increases the indentation level.
           */
         void startIndent();

          /*!
           \brief Decrease indentation level.
           \details In XML, whitespaces are sometimes significant. The significance of whitespaces depends on the document. This method performs an indentation and decreases the indentation level.
           \note This method is used to decrease the indentation level in XML writing. It is important to maintain proper indentation for readability and to follow XML formatting conventions.
           */
         void endIndent();

           /*!
            \brief This method opens a new XML element.
            \details This method is used to open a new XML element in the XMLWriter class. It should be called before writing any content to the element.
            \param name The name of the XML element to be opened.
            */
         void startElement(const String& name);

          /*!
           \brief This method writes an XML attribute to the open start element.
           \param name The name of the attribute.
           \param content The content of the attribute.
           \warning This method must be called before writing any content to an element.
           */
         void writeAttribute(const String& name, const String& content);

          /*!
           \brief This method writes an XML attribute to the currently open start element.
           \details This method should be called before writing any content to the element.
           \param name The name of the attribute.
           \param content The content of the attribute.
           \warning This method must be called before writing any content to an element.
           */
         void writeAttribute(const String& name, int32 content);

          /*!
           \brief This method writes an XML attribute to the currently open start element.
           \details This method should be called before writing any content to the element.
           \param name The name of the attribute.
           \param content The content of the attribute.
           \warning This method must be called before writing any content to an element.
           */
         void writeAttribute(const String& name, uint32 content);

          /*!
           \brief This method writes an XML attribute to the currently open start element.
           \details This method should be called before writing any content to the element.
           \param name The name of the attribute.
           \param content The content of the attribute.
           \warning This method must be called before writing any content to an element.
           */
         void writeAttribute(const String& name, int64 content);

          /*!
           \brief This method writes an XML attribute to the currently open start element.
           \details This method should be called before writing any content to the element.
           \param name The name of the attribute.
           \param content The content of the attribute.
           \warning This method must be called before writing any content to an element.
           */
         void writeAttribute(const String& name, uint64 content);

          /*!
           \brief This method writes an XML attribute to the currently open start element.
           \details This method should be called before writing any content to the element.
           \param name The name of the attribute.
           \param content The content of the attribute.
           \warning This method must be called before writing any content to an element.
           \note The content of the attribute should be a string.
           */
         void writeAttribute(const String& name, float content);

          /*!
           \brief This method writes an XML attribute to the currently open start element.
           \details This method should be called before writing any content to the element.
           \param name The name of the attribute.
           \param content The content of the attribute.
           \warning This method must be called before writing any content to an element.
           \note The content of the attribute should be a string.
           */
         void writeAttribute(const String& name, double content);

          /*!
           \brief This method closes the currently open XML element. If the element has no content, a <.../> element is written.
           */
         void endElement();

          /*!
           \brief This method writes CDATA to the currently open start element.
           \details CDATA is used to escape blocks of text that contain characters which would otherwise be recognized as markup. This method should be called before writing any content to the element.
           \param cdata The CDATA to be written.
           \param xmlencode If true (default), certain characters (e.g. & -> &amp;) will be XML-encoded.
           */
         void writeCData(const String& cdata, bool xmlencode = true);

          /*!
           \brief This method writes data and encodes it using the BASE64 algorithm.
           \param data The unencoded data to be written.
           \param length The length of the data.
           */
         void WriteBase64(uint8* data, int64 length);


      private:

         Stream* mOutput;

         int32 mIndent;

         bool mLastIndent;

         struct ElementInfo
         {
            String name;
            bool indent;
            bool hasContent;
            bool hasCharacters;

            ElementInfo()
            {
               indent = false;
               hasContent = false;
               hasCharacters = false;
            }

         };

         Stack<ElementInfo>* mOpenElements;

         String Encode(const String& input);

         void WriteIndent();
   };

}

#endif /* XMLWriter_h */
