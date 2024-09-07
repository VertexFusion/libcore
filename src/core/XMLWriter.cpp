////////////////////////////////////////////////////////////////////////////////////////////////////
// Name:        XMLWriter.cpp
// Library:     Jameo Core Library
// Purpose:     Writer for XML Files
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

#include "Precompiled.hpp"

using namespace jm;

XMLWriter::XMLWriter(jm::Stream* output)
{
   mOutput = output;

   mOpenElements = new Stack<ElementInfo>();
}

XMLWriter::~XMLWriter()
{
   delete mOpenElements;
}

bool XMLWriter::StartDocument()
{
   mIndent = 0;
   mLastIndent = false;
   if(mOutput->isOpen() == false)mOutput->open(kFmWrite);

   mOutput->write("<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n");
   return true;
}

bool XMLWriter::EndDocument()
{
   mOutput->close();
   return true;
}

void XMLWriter::StartIndent()
{
   if(mOpenElements->Size() > 0 && mOpenElements->Top().hasContent == false)
   {
      mOpenElements->TopRef()->hasContent = true;
      mOutput->write(">");
   }
   mIndent += 3;
   mLastIndent = true;
}

void XMLWriter::EndIndent()
{
   if(mOpenElements->Size() > 0 && mOpenElements->Top().hasContent == false)
   {
      mOpenElements->TopRef()->hasContent = true;
      mOutput->write(">");
   }
   mLastIndent = false;
   mIndent -= 3;
}

void XMLWriter::StartElement(const jm::String& name)
{

   if(mOpenElements->Size() > 0 && mOpenElements->Top().hasContent == false)
   {
      mOpenElements->TopRef()->hasContent = true;
      mOutput->write(">");
   }

   if(mLastIndent)
   {
      WriteIndent();
   }


   mOutput->write("<");
   mOutput->write(name);

   ElementInfo info;
   info.name = name;
   info.indent = mLastIndent;
   mOpenElements->Push(info);
   mLastIndent = false;
}

void XMLWriter::EndElement()
{
   if(mOpenElements->Top().hasContent == false)
   {
      mOutput->write("/>");
   }
   else
   {
      if(mOpenElements->Top().indent && mOpenElements->Top().hasCharacters == false)
      {
         WriteIndent();
      }

      mOutput->write("</");
      mOutput->write(mOpenElements->Top().name);
      mOutput->write(">");
   }

   mOpenElements->Pop();
   mLastIndent = false;
}

void XMLWriter::WriteCDATA(const jm::String& cdata, bool xmlencode)
{
   if(mOpenElements->Size() > 0 && mOpenElements->Top().hasContent == false)
   {
      mOpenElements->TopRef()->hasContent = true;
      mOutput->write(">");
   }

   if(mOpenElements->Size() > 0 && mOpenElements->Top().hasCharacters == false)
   {
      mOpenElements->TopRef()->hasCharacters = true;
   }

   //XML-Codieren
   if(xmlencode)
   {
      jm::String encoded = Encode(cdata);


      mOutput->write(encoded);
   }
   else
   {
      mOutput->write(cdata);
   }
   mLastIndent = false;
}

jm::String XMLWriter::Encode(const jm::String& input)
{
   jm::String encoded;
   jm::StringTokenizer st = jm::StringTokenizer(input, "&<>\"'", true);

   while(st.hasNext())
   {
      jm::String token = st.next();

      if(token.equals("&"))encoded.append("&amp;");
      else if(token.equals("<"))encoded.append("&lt;");
      else if(token.equals(">"))encoded.append("&gt;");
      else if(token.equals("\""))encoded.append("&quot;");
      else if(token.equals("'"))encoded.append("&apos;");
      else encoded.append(token);
   }
   return encoded;
}

void XMLWriter::WriteBase64(uint8* data, Integer length)
{
   if(mOpenElements->Size() > 0 && mOpenElements->Top().hasContent == false)
   {
      mOpenElements->TopRef()->hasContent = true;
      mOpenElements->TopRef()->hasCharacters = true;
      mOutput->write(">");
   }


   uint8* encoded = jm::Base64::encode(data, length);
   mOutput->write(encoded, length);
   delete[] encoded;
   mLastIndent = false;
}


void XMLWriter::WriteAttribute(const jm::String& name, const jm::String& content)
{
   if(mOpenElements->Size() == 0 || mOpenElements->Top().hasContent == true)
   {
      return;
   }

   mOutput->write(" ");
   mOutput->write(name);
   mOutput->write("=\"");
   mOutput->write(Encode(content));
   mOutput->write("\"");
   mLastIndent = false;
}

void XMLWriter::WriteAttribute(const jm::String& name, int32 content)
{
   WriteAttribute(name, jm::String::valueOf(content));
}

void XMLWriter::WriteAttribute(const jm::String& name, uint32 content)
{
   WriteAttribute(name, jm::String::valueOf(content));
}

void XMLWriter::WriteAttribute(const jm::String& name, int64 content)
{
   WriteAttribute(name, jm::String::valueOf(content));
}

void XMLWriter::WriteAttribute(const jm::String& name, uint64 content)
{
   WriteAttribute(name, jm::String::valueOf(content));
}
void XMLWriter::WriteAttribute(const jm::String& name, float content)
{
   WriteAttribute(name, jm::String::valueOf(content));
}

void XMLWriter::WriteAttribute(const jm::String& name, double content)
{
   WriteAttribute(name, jm::String::valueOf(content));
}

void XMLWriter::WriteIndent()
{
   jm::String str;
   str << '\n';
   for(int32 a = 0; a < mIndent; a++)str.append(' ');
   if(str.size() == 0)return;
   mOutput->write(str);
}
