//
//  SAXAttributes.cpp
//  crawler
//
//  Created by Uwe Runtemund on 04.03.14.
//  Copyright (c) 2014 Jameo Software. All rights reserved.
//

#include "Precompiled.h"

using namespace jm;

SAXAttributes::SAXAttributes(): Object()
{

}

SAXAttributes::~SAXAttributes()
{

}

SAXAttributes::SAXAttributes(const SAXAttributes &other)
{
	mNames.clear();
	mValues.clear();

	for(uint32 a = 0; a < other.mNames.size(); a++)
	{
		this->mNames.push_back(other.mNames[a]);
		this->mValues.push_back(other.mValues[a]);
	}
}

SAXAttributes &SAXAttributes::operator=(const SAXAttributes &other)
{
	if(this == &other) return *this;
	this->mNames.clear();
	this->mValues.clear();

	for(uint32 a = 0; a < other.mNames.size(); a++)
	{
		this->mNames.push_back(other.mNames[a]);
		this->mValues.push_back(other.mValues[a]);
	}

	return *this;

}

void SAXAttributes::AddAttribute(String uri, String localname, String qName, String value)
{
	//	std::cout << "Add Attrib: " << localname << " " << value << std::endl;
	mNames.push_back(localname);
	mValues.push_back(value);
}

int32 SAXAttributes::GetIndex(String qName) const
{
	for(uint32 a = 0; a < mNames.size(); a++)
	{
		if(mNames[a].Equals(qName))return a;
	}

	return -1;
}

int32 SAXAttributes::GetIndex(String uri, String localName) const
{
	return GetIndex(localName);
}

uint32 SAXAttributes::GetLength() const
{
	return (uint32)mNames.size();
}

String SAXAttributes::GetLocalName(uint32 index) const
{
	return mNames[index];
}

String SAXAttributes::GetQName(uint32 index) const
{
	return mNames[index];
}

String SAXAttributes::GetType(uint32 index) const
{
	return "CDATA";
}

String SAXAttributes::GetType(String qname) const
{
	return "CDATA";
}

String SAXAttributes::GetType(String uri, String localName) const
{
	return "CDATA";
}

String SAXAttributes::GetURI(uint32 index) const
{
	return kEmptyString;
}

String SAXAttributes::GetValue(uint32 index) const
{
	return mValues[index];
}

String SAXAttributes::GetValue(const String &qname) const
{
	int32 index = GetIndex(qname);
	if(index > -1)return mValues[index];
	return kEmptyString;
}

int32 SAXAttributes::GetIntValue(const String &qname) const
{
	return (int32) Integer::ValueOf(GetValue(qname));
}

float SAXAttributes::GetFloatValue(const String &qname) const
{
	return (float) StrToDouble(GetValue(qname));
}

bool SAXAttributes::GetBoolValue(const String &qname)const
{
	return GetValue(qname).EqualsIgnoreCase("true");
}


bool SAXAttributes::HasValue(const String &qname) const
{
	int32 index = GetIndex(qname);
	if(index > -1)return true;
	return false;
}

String SAXAttributes::GetValue(String uri, String localName) const
{
	int32 index = GetIndex(uri, localName);
	if(index > -1)return mValues[index];
	return kEmptyString;
}
