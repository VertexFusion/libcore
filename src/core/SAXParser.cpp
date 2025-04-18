////////////////////////////////////////////////////////////////////////////////////////////////////
// Name:        SAXParser.cpp
// Library:     Jameo Core Library
// Purpose:     SAX parser
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

#include "PrecompiledCore.hpp"

using namespace jm;

SAXParser::SAXParser(): Object()
{

}

SAXParser::~SAXParser()
{

}

void SAXParser::parse(File& file)
{
   if(!file.exists())return;
   if(!file.canRead())return;
   int64 length = file.size();
   ByteArray buffer = ByteArray(length, 0);
   file.open(jm::FileMode::kRead);
   file.Stream::readFully(buffer);
   file.close();
   jm::String content = jm::String(buffer);
   parse(content);
}

void SAXParser::parse(const String& xml)
{
   String token;

   // Make sure that the token is large enough and does not have to be constantly enlarged for
   // binary data.
   token.checkCapacity(xml.size());

   startDocument();

   int64 length = xml.size(); // Length of XML-Code
   int64 pos = 0; // Position of pointer

   bool inTag = false;   // Status, if tag is open
   bool inValue = false; // Status, if value is open
   Char opener = '\"'; // Character for begin and end of tag. ' or "
   Char c;

   while(pos < length)
   {
      c = xml.charAt(pos);

      if(c == '<' && inTag == false && inValue == false) // Found beginning of a tag.
      {
         inTag = true;
         // Outputs characters: TODO: IgnorableWhitespaces muss hier noch berücksichtigt werden.
         if(token.size() > 0)
         {
            String beginWhitespaces;
            String endWhiteSpaces;

            // Cut whitespaces at the beginning
            int64 sub = 0;
            while(sub < token.size() && token.charAt(sub).isWhitespace())
            {
               beginWhitespaces.append(token.charAt(sub));
               sub++;
            }
            if(beginWhitespaces.size() > 0)
            {
               // Direct assignment would change the length of tokens. Hence this detour
               const String tmp = token.substring(beginWhitespaces.size());
               token.zero();
               token.append(tmp);
            }

            // Cut off whitespaces at the end
            sub = token.size() - 1;
            while(sub >= 0 && sub < token.size() && token.charAt(sub).isWhitespace())
            {
               endWhiteSpaces.insert(0, token.charAt(sub));
               sub--;
            }
            if(endWhiteSpaces.size() > 0)
            {
               // Direct assignment would change the length of tokens. Hence this detour
               const String tmp = token.substring(0, token.size() - endWhiteSpaces.size());
               token.zero();
               token.append(tmp);
            }

            if(beginWhitespaces.size() > 0)
            {
               token.insert(0, beginWhitespaces.charAt(beginWhitespaces.size() - 1));
               beginWhitespaces.deleteCharAt(beginWhitespaces.size() - 1);
            }

            if(endWhiteSpaces.size() > 0)
            {
               token.append(endWhiteSpaces.charAt(0));
               endWhiteSpaces.deleteCharAt(0);
            }

            // Call parsing methods
            if(beginWhitespaces.size() > 0)ignorableWhiteSpaces(beginWhitespaces);
            if(token.size() > 0)characters(token);
            if(endWhiteSpaces.size() > 0)ignorableWhiteSpaces(endWhiteSpaces);
         }

         token.zero();
      }
      else if(c == '&' && inTag == false)
      {
         String escape;
         do
         {
            pos++;
            c = xml.charAt(pos);
            escape.append(c);
         }
         while(c != ';' && pos < length - 1);

         if(escape.equals("lt;"))token.append('<');
         else if(escape.equals("gt;"))token.append('>');
         else if(escape.equals("amp;"))token.append('&');
         else if(escape.equals("quot;"))token.append('"');
         else if(escape.equals("le;"))token.append(0x2264); //≤
         else if(escape.equals("ge;"))token.append(0x2265); //≥
         else if(escape.equals("leq;"))token.append(0x2264); //≤
         else if(escape.equals("geq;"))token.append(0x2265); //≥
      }
      else if(c == '>' && inTag == true && inValue == false)
      {
         parseTagString(token);
         token.zero();
         inTag = false;
      }
      else if((c == '\"' || c == '\'') && inTag == true)
      {
         if(inValue == false)
         {
            inValue = true;
            opener = c;
         }
         else if(inValue == true && opener == c)
         {
            inValue = false;
         }
         token.append(c);
      }
      else token.append(c);


      pos++;
   }

   endDocument();
}

void SAXParser::parseTagString(const String& xmlline)
{
   String line = xmlline;

   line.append(' ');// Whitespace at the end makes parsing easier because code is saved.

   int64 pos = 0; //Position of pointer
   int64 length = line.size(); // Length
   bool inValue = false; // Status, if in value
   Char c;
   Char opener = 0;
   int64 tagType = 0; //0: Open, 1: Close 2: Open/Close
   int64 step = 0; // 0:Tagname, 1: Attribute name, 2: Attribute value

   // Check for '/' at the end
   pos = line.size() - 1;
   while(line.charAt(pos).isWhitespace())pos--;
   if(line.charAt(pos) == '/')
   {
      tagType = 2;
   }


   // Skip whitespaces at beginning
   pos = 0;
   while(line.charAt(pos).isWhitespace())pos++;

   // Check for '/' at beginning.
   if(line.charAt(pos) == '/')
   {
      tagType = 1;
      pos++;
   }


   String token;// Current token
   String tname;// Name of tag
   String aname;// Name of attribute
   String avalue;// Value of attribute

   SAXAttributes attribs;

   while(pos < length)
   {
      c = line.charAt(pos);

      if(c == '\"' || c == '\'')
      {
         if(inValue == false)
         {
            inValue = true;
            opener = c;
         }
         else if(opener == c)// inValue is always "true" here
         {
            inValue = false;

            if(step == 2)
            {
               avalue = token;
               step--;
               attribs.addAttribute(jm::kEmptyString, aname, aname, avalue);
               token.clear();
            }
         }
         else token.append(c);
      }
      else if(c == '&' && inValue == true)
      {
         String escape;
         do
         {
            pos++;
            c = line.charAt(pos);
            escape.append(c);
         }
         while(c != ';' && pos < length - 1);

         if(escape.equals("lt;"))token.append('<');
         else if(escape.equals("gt;"))token.append('>');
         else if(escape.equals("amp;"))token.append('&');
         else if(escape.equals("quot;"))token.append('"');
      }
      else if((c.isWhitespace() || c == '=' || c == '/') && !inValue)
      {
         // Process Token
         if(token.size() > 0)
         {
            if(step == 0)
            {
               tname = token;
               step++;
            }
            else if(step == 1)
            {
               aname = token;
               step++;
            }
            token.clear();
         }
      }
      else token.append(c);

      pos++;
   }

   // VProcess in the parser
   const String qualifiedName = tname;
   const String localName = qualifiedName.substring(qualifiedName.lastIndexOf(':') + 1);
   switch(tagType)
   {
      case 0:
         startElement(jm::kEmptyString, localName, qualifiedName, attribs);
         break;

      case 1:
         endElement(jm::kEmptyString, localName, qualifiedName);
         break;

      case 2:
         startElement(jm::kEmptyString, localName, qualifiedName, attribs);
         endElement(jm::kEmptyString, localName, qualifiedName);
         break;

   }

}

void SAXParser::characters(const String& /*characters*/)
{
   // Dummy method
   //	std::cout << "SAX: Characters: " << std::endl;
}

void SAXParser::endDocument()
{
   // Dummy method
   //	std::cout << "SAX: endDocument" << std::endl;
}

void SAXParser::endElement(const String& /*uri*/,
                           const String& /*localName*/,
                           const String& /*qName*/)
{
   // Dummy method
   //	std::cout << "SAX: endElement " << localName << std::endl;
}

void SAXParser::endPrefixMapping(const String& /*prefix*/)
{
   // Dummy method
   //	std::cout << "SAX: EndPrefixMapping" << std::endl;
}

void SAXParser::ignorableWhiteSpaces(const String& /*characters*/)
{
   // Dummy method
   //	std::cout << "SAX: IgnorableWhitespaces" <<std::endl;
}

void SAXParser::processingInstruction(const String& /*target*/,
                                      const String& /*data*/)
{
   // Dummy method
   //	std::cout << "SAX: ProcessingInstruxtion" << std::endl;
}

void SAXParser::skippedEntity(const String& /*name*/)
{
   // Dummy method
   //	std::cout << "SAX: SkippedEntity" << std::endl;
}

void SAXParser::startDocument()
{
   // Dummy method
   //	std::cout << "SAX: startDocument" << std::endl;
}

void SAXParser::startElement(const String& /*uri*/,
                             const String& /*localName*/,
                             const String& /*qName*/,
                             const SAXAttributes& /*attributes*/)
{
   // Dummy method
   //	std::cout << "SAX: startElement " << localName  << " " << attributes.GetLength() << std::endl;
}
