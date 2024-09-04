////////////////////////////////////////////////////////////////////////////////////////////////////
// Name:        SAXParser.h
// Library:     Jameo Core Library
// Purpose:     XML Parsing tool
//
// Author:      Uwe Runtemund (2014-today)
// Modified by:
// Created:     04.03.2014
//
// Copyright:   (c) 2014 Jameo Software, Germany. https://jameo.de
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

#ifndef jm_SAXParser_h
#define jm_SAXParser_h

#include <vector>

#include "String.h"


namespace jm
{
   /*!
    \brief This class represents the attributes used in the SAX parser.
    */
   class DllExport SAXAttributes: public Object
   {

      public:

         /*!
          \brief Constructor
          */
         SAXAttributes();

         /*!
          \brief Destructor
          */
         virtual ~SAXAttributes();

         /*!
          \brief Copy constructor
          */
         SAXAttributes(const SAXAttributes& other);

         /*!
          \brief assigning operator
          */
         SAXAttributes& operator=(const SAXAttributes& another);

         /*!
          \brief This method is needed by the parser to fill the list with content.
          */
         void addAttribute(String uri, String localname, String qName, String value);

          /*!
           \brief This method searches for the index of an attribute.
           \param qName The qualified name of the attribute.
           \return The index of the attribute, or -1 if not found.
           */
         int32 indexOf(String qName) const;

          /*!
           \brief This method searches for the index of an attribute.
           \param localName The local name of the attribute.
           \return The index of the attribute, or -1 if not found.
           */
         int32 indexOf(String uri, String localName) const;

          /*!
           \brief Returns the number of attributes.
           */
         uint32 count() const;

          /*!
           \brief Returns the local name of an attribute.
           \param index The 0-based index of the attribute.
           \return The local name of the attribute.
           */
         String localName(uint32 index) const;

          /*!
           \brief Returns the qualified name.
           \return The qualified name of the attribute.
           */
         String qualifiedName(uint32 index) const;

          /*!
           \brief Returns the attribute type.
           \details The attribute type is one of the following strings: "CDATA", "ID", "IDREF", "IDREFS", "NMTOKEN", "NMTOKENS", "ENTITY", "ENTITIES", or "NOTATION" (always in upper case).
           \return The attribute type.
           */
         String type(uint32 index) const;

          /*!
           \brief Returns the attribute type.
           \details The attribute type is one of the following strings: "CDATA", "ID", "IDREF", "IDREFS", "NMTOKEN", "NMTOKENS", "ENTITY", "ENTITIES", or "NOTATION" (always in upper case).
           \return The attribute type.
           */
         String type(String qname) const;

          /*!
           \brief Returns the attribute type.
           \details The attribute type is one of the following strings: "CDATA", "ID", "IDREF", "IDREFS", "NMTOKEN", "NMTOKENS", "ENTITY", "ENTITIES", or "NOTATION" (always in upper case).
           \param uri The URI of the attribute.
           \param localName The local name of the attribute.
           \return The attribute type.
           */
         String type(String uri, String localName) const;

          /*!
           \brief Returns the URI.
           \return The URI of the attribute.
           */
         String uri(uint32 index) const;

          /*!
           \brief Returns the value of the attribute.
           \param index The 0-based index of the attribute.
           \return The value of the attribute.
           */
         String value(uint32 index) const;

          /*!
           \brief Returns the value.
           \param qname The qualified name of the attribute.

           \return The value.
           */
         String value(const String& qname) const;

         /*!
          \brief Returns the value as an integer.
          \param qname The qualified name of the attribute.
          */
         int32 valueAsInt(const String& qname)const;

         /*!
          \brief Returns the value as a float.
          \param qname The qualified name of the attribute.
          */
         float valueAsFloat(const String& qname)const;

         /*!
          \brief Returns the value as a double.
          \param qname The qualified name of the attribute.
          */
         double valueAsDouble(const String& qname)const;

         /*!
          \brief Returns the value as a boolean.
          \param qname The qualified name of the attribute.
          */
         bool valueAsBool(const String& qname)const;

         /*!
          \brief Checks if the attribute is contained
          \param qname The qualified name of the attribute.
          */
         bool hasValue(const String& qname) const;

         /*!
          \brief Returns the value.
          \param uri The URI of the attribute.
          \param localName The local name of the attribute.
          */
         String value(String uri, String localName) const;

      private:

         std::vector<String>* mNames;
         std::vector<String>* mValues;

   };



   /*!
    \brief This class represents an XML/HTML parser based on the SAX (Simple API for XML) principle.
    The advantage lies in the serial processing of tags.
    This abstract base class must be derived by the parsers and implement some methods.
    */
   class DllExport SAXParser: public Object
   {

      public:

          /*!
           \brief Constructor
           */
         SAXParser();

         /*!
          \brief Destructor
          */
         virtual ~SAXParser();

         /*!
          \brief This method parses the given file.
          \param file The file to parse.
          */
         void parse(File& file);

          /*!
           \brief This method parses the given string, which should be XML code.
           \param xml The XML code to parse.
           */
         void parse(const String& xml);

          /*!
           \brief This method is called by the parser when it encounters letters.
           \param characters The characters.
           */
         virtual void characters(const String& characters);

          /*!
           \brief This method is called by the parser when the end of the document is reached.
           */
         virtual void endDocument();

         /*!
         \brief This method is called by the parser when the end of an element is reached.
         \param uri The URI of the element.
         \param localName The local name of the element.
         \param qName The qualified name of the element.
         */
         virtual void endElement(const String& uri, const String& localName, const String& qName);

         /*!
          \brief End the scope of a prefix-URI mapping.
          \param prefix The prefix that was being mapped.
          */
         virtual void endPrefixMapping(const String& prefix);

          /*!
         \brief This method is called by the parser when ignorable white spaces are encountered. 
         \param characters The characters.
           */
         virtual void ignorableWhiteSpaces(const String& characters);

         /*!
          \brief Receive notification of a processing instruction.
          */
         virtual void processingInstruction(const String& target, const String& data);

         /*!
          \brief Receive notification of a skipped entity.
          */
         virtual void skippedEntity(const String& name);

          /*!
           \brief This method is called at the beginning of the document.
           */
         virtual void startDocument();

          /*!
         \brief This method is called at the beginning of an element.
         \param uri The URI of the element.
         \param localName The local name of the element.
         \param qName The qualified name of the element.
         \param attributes The attributes of the element.
           */
         virtual void startElement(const String& uri,
                                   const String& localName,
                                   const String& qName,
                                   const SAXAttributes& attributes);


      private:

          /*!
           \brief This helper method parses the tag string... This is the entire part between < and >
           */
         void parseTagString(const String& token);

   };

}


#endif
