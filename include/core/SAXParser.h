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
    \brief Diese Klasse repräsentiert die Attribute, die in dem SAX-Parser verwendet werden
    */
   class DllExport SAXAttributes: public Object
   {

      public:

         /*!
          \brief Konstruktor
          */
         SAXAttributes();

         /*!
          \brief Destructor
          */
         virtual ~SAXAttributes();

         /*!
          \brief Copykonstruktor
          */
         SAXAttributes(const SAXAttributes &other);

         /*!
          \brief Zuweisungsoperator
          */
         SAXAttributes &operator=(const SAXAttributes &another);

         /*!
          \brief Diese Methode braucht der Parser, um die Attributliste mit Inhalt zu füllen
          */
         void AddAttribute(String uri, String localname, String qName, String value);

         /*!
          \brief Sucht nach dem Index eines Attributes
          */
         int32 GetIndex(String qName) const;

         /*!
          \brief Sicht nach dem Index eines Attributes
          */
         int32 GetIndex(String uri, String localName) const;

         /*!
          \brief Gibt die Anzahl der Attribute zurück
          */
         uint32 GetLength() const;

         /*!
          \brief Gibt den LocalName eines Attributes zurück
          */
         String GetLocalName(uint32 index) const;

         /*!
          \brief Gibt den qualifiedName zurück
          */
         String GetQName(uint32 index) const;

         /*!
          \brief Gibt den Attribut-Type zurück
          \discussion The attribute type is one of the strings "CDATA", "ID", "IDREF", "IDREFS", "NMTOKEN", "NMTOKENS", "ENTITY", "ENTITIES", or "NOTATION" (always in upper case).
          */
         String GetType(uint32 index) const;

         /*!
          \brief Gibt den Attribut-Type zurück
          */
         String GetType(String qname) const;

         /*!
          \brief Gibt den Attribut-Type zurück
          */
         String GetType(String uri, String localName) const;

         /*!
          \brief Gibt URI zurück
          */
         String GetURI(uint32 index) const;

         /*!
          \brief Gibt den Wert zurück
          */
         String GetValue(uint32 index) const;

         /*!
          \brief Gibt den Wert zurück
          */
         String GetValue(const String &qname) const;

         int32 GetIntValue(const String &qname)const;
         float GetFloatValue(const String &qname)const;
         bool GetBoolValue(const String &qname)const;

         /*!
          \brief Prüft, ob das Attribut enthalten ist
          */
         bool HasValue(const String &qname) const;

         /*!
          \brief Gibt den Wert zurück
          */
         String GetValue(String uri, String localName) const;

      private:

         std::vector<String>* mNames;
         std::vector<String>* mValues;

   };



   /*!
    \brief Diese Klasse repräsentiert einen XML/HTML-Parser nach dem SAX-Prinzip (Simple API for XML).
    Der Vorteil liegt in der Seriellen Verarbeitung der Tags.
    Diese Abstrakte Vaterklasse muss von den Parsern abgeleitet werden. und einige Methode implementieren.
    */
   class DllExport SAXParser: public Object
   {

      public:

         /*!
          \brief Konstruktor
          */
         SAXParser();

         /*!
          \brief Destructor
          */
         virtual ~SAXParser();

         void Parse(File &file);

         /*!
          \brief Diese Methode parst die übergebene Zeichenkette, welche XML sein soll
          \param xml Der XML-Code
          */
         void Parse(const String &xml);

         /*!
          \brief Diese Methode wird vom Parser aufgerufen, wenn er Buchstaben entdeckt hat.
          */
         virtual void Characters(const String &characters);

         /*!
          \brief Diese Methode wird vom Parser aufgerufen, wenn das Ende des Dokumentes erreicht wurde.
          */
         virtual void EndDocument();

         /*!
          \brief Diese Methode wird vom Parser aufgerufen, wenn das Ende eines Elementes erreicht wurde.
          */
         virtual void EndElement(const String &uri, const String &localName, const String &qName);

         /*!
          \brief End the scope of a prefix-URI mapping.
          */
         virtual void EndPrefixMapping(const String &prefix);

         /*!
          \brief Diese Methode wird vom Parser aufgerufen, wenn ignorierbare Leerzeichen gefunden wurden
          */
         virtual void IgnorableWhiteSpaces(const String &characters);

         /*!
          \brief Receive notification of a processing instruction.
          */
         virtual void ProcessingInstruction(const String &target, const String &data);

         /*!
          \brief Receive notification of a skipped entity.
          */
         virtual void SkippedEntity(const String &name);

         /*!
          \brief Diese Methode wird am Anfang des Dokuemntes aufgerufen
          */
         virtual void StartDocument();

         /*!
          \brief Diese Methode wird beim Beginn eines Elementes aufgerufen.
          */
         virtual void StartElement(const String &uri,
                                   const String &localName,
                                   const String &qName,
                                   const SAXAttributes &attributes);


      private:

         /*!
          \brief Diese Helfermethode parst den Tagstring... Das ist der gesamte Teil zwischen < und >
          */
         void ParseTagString(const String &token);

   };

}


#endif
