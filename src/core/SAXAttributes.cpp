////////////////////////////////////////////////////////////////////////////////////////////////////
// Name:        SAXAttributes.cpp
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

#include "Precompiled.h"

using namespace jm;

SAXAttributes::SAXAttributes(): Object()
{
   mNames = new std::vector<String>();
   mValues = new std::vector<String>();
}

SAXAttributes::~SAXAttributes()
{
   delete mNames;
   delete mValues;
}

SAXAttributes::SAXAttributes(const SAXAttributes& other)
{
   mNames->clear();
   mValues->clear();

   for(uint32 a = 0; a < other.mNames->size(); a++)
   {
      mNames->push_back(other.mNames->at(a));
      mValues->push_back(other.mValues->at(a));
   }
}

SAXAttributes& SAXAttributes::operator=(const SAXAttributes& other)
{
   if(this == &other) return *this;
   mNames->clear();
   mValues->clear();

   for(uint32 a = 0; a < other.mNames->size(); a++)
   {
      mNames->push_back(other.mNames->at(a));
      mValues->push_back(other.mValues->at(a));
   }

   return *this;

}

void SAXAttributes::AddAttribute(String /*uri*/, String localname, String /*qName*/, String value)
{
   //	std::cout << "Add Attrib: " << localname << " " << value << std::endl;
   mNames->push_back(localname);
   mValues->push_back(value);
}

int32 SAXAttributes::GetIndex(String qName) const
{
   for(uint32 a = 0; a < mNames->size(); a++)
   {
      if(mNames->at(a).equals(qName))return a;
   }

   return -1;
}

int32 SAXAttributes::GetIndex(String /*uri*/, String localName) const
{
   return GetIndex(localName);
}

uint32 SAXAttributes::GetLength() const
{
   return (uint32)mNames->size();
}

String SAXAttributes::GetLocalName(uint32 index) const
{
   return mNames->at(index);
}

String SAXAttributes::GetQName(uint32 index) const
{
   return mNames->at(index);
}

String SAXAttributes::GetType(uint32 /*index*/) const
{
   return "CDATA";
}

String SAXAttributes::GetType(String /*qname*/) const
{
   return "CDATA";
}

String SAXAttributes::GetType(String /*uri*/, String /*localName*/) const
{
   return "CDATA";
}

String SAXAttributes::GetURI(uint32 /*index*/) const
{
   return kEmptyString;
}

String SAXAttributes::GetValue(uint32 index) const
{
   return mValues->at(index);
}

String SAXAttributes::GetValue(const String& qname) const
{
   int32 index = GetIndex(qname);
   if(index > -1)return mValues->at(index);
   return kEmptyString;
}

int32 SAXAttributes::GetIntValue(const String& qname) const
{
   return Integer::valueOf(GetValue(qname)).Int32();
}

float SAXAttributes::GetFloatValue(const String& qname) const
{
   return (float)Double::valueOf(GetValue(qname));
}

bool SAXAttributes::GetBoolValue(const String& qname)const
{
   return GetValue(qname).equalsIgnoreCase("true");
}


bool SAXAttributes::HasValue(const String& qname) const
{
   int32 index = GetIndex(qname);
   if(index > -1)return true;
   return false;
}

String SAXAttributes::GetValue(String uri, String localName) const
{
   int32 index = GetIndex(uri, localName);
   if(index > -1)return mValues->at(index);
   return kEmptyString;
}
