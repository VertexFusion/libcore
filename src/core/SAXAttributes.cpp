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

#include "PrecompiledCore.hpp"

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

   for(size_t a = 0; a < other.mNames->size(); a++)
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

   for(size_t a = 0; a < other.mNames->size(); a++)
   {
      mNames->push_back(other.mNames->at(a));
      mValues->push_back(other.mValues->at(a));
   }

   return *this;

}

void SAXAttributes::addAttribute(const String& /*uri*/,
                                 const String& localname,
                                 const String& /*qName*/,
                                 const String& value)
{
   //	std::cout << "Add Attrib: " << localname << " " << value << std::endl;
   mNames->push_back(localname);
   mValues->push_back(value);
}

size_t SAXAttributes::indexOf(const String& qName) const
{
   for(size_t a = 0; a < mNames->size(); a++)
   {
      if(mNames->at(a).equals(qName))return a;
   }

   return npos;
}

size_t SAXAttributes::indexOf(const String& /*uri*/,
                              const String& localName) const
{
   return indexOf(localName);
}

size_t SAXAttributes::count() const
{
   return mNames->size();
}

String SAXAttributes::localName(size_t index) const
{
   return mNames->at(index);
}

String SAXAttributes::qualifiedName(size_t index) const
{
   return mNames->at(index);
}

String SAXAttributes::type(size_t /*index*/) const
{
   return "CDATA";
}

String SAXAttributes::type(const String& /*qname*/) const
{
   return "CDATA";
}

String SAXAttributes::type(const String& /*uri*/,
                           const String& /*localName*/) const
{
   return "CDATA";
}

String SAXAttributes::uri(size_t /*index*/) const
{
   return kEmptyString;
}

String SAXAttributes::value(size_t index) const
{
   return mValues->at(index);
}

String SAXAttributes::value(const String& qname) const
{
   size_t index = indexOf(qname);
   if(index != npos)return mValues->at(index);
   return kEmptyString;
}

int64 SAXAttributes::valueAsInt(const String& qname) const
{
   return value(qname).toInt();
}

float SAXAttributes::valueAsFloat(const String& qname) const
{
   return (float)value(qname).toDouble();
}

double SAXAttributes::valueAsDouble(const String& qname) const
{
   return value(qname).toDouble();
}

bool SAXAttributes::valueAsBool(const String& qname)const
{
   return value(qname).equalsIgnoreCase("true");
}


bool SAXAttributes::hasValue(const String& qname) const
{
   int32 index = indexOf(qname);
   if(index > -1)return true;
   return false;
}

String SAXAttributes::value(const String& uri,const String& localName) const
{
   size_t index = indexOf(uri, localName);
   if(index != npos)return mValues->at(index);
   return kEmptyString;
}
