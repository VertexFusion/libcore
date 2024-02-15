////////////////////////////////////////////////////////////////////////////////////////////////////
// Name:        Property.cpp
// Library:     Jameo Core Library
// Purpose:     Property
//
// Author:      Uwe Runtemund (2016-today)
// Modified by:
// Created:     24.06.2016
//
// Copyright:   (c) 2016 Jameo Software, Germany. https://jameo.de
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

Property::Property()
{
	mReadOnly = false;
	mNumberValue.intValue = 0;
	mChangeMode = kPropertyChangeItself;
	mAllowEmpty = true;
	mType = kPropertyTypeString;
}

Property::Property(const String &id)
{
	mReadOnly = false;
	mId = id;
	mNumberValue.intValue = 0;
	mChangeMode = kPropertyChangeItself;
	mAllowEmpty = true;
	mType = kPropertyTypeString;
}


Property::Property(const String &id,
                   const String &group,
                   const String &name,
                   const String &hint,
                   const String &editor,
                   bool readOnly,
                   PropertyChangeMode changeMode,
                   bool allowEmpty)
{
	mId = id;
	mGroup = group;
	mName = name;
	mHint = hint;
	mEditor = editor;
	mReadOnly = readOnly;
	mChangeMode = changeMode;
	mNumberValue.intValue = 0;
	mAllowEmpty = allowEmpty;
	mType = kPropertyTypeString;
}

Bool Property::Is(const String &id)const
{
	return mId.Equals(id);
}

PropertyType Property::GetType() const
{
	return mType;
}

void Property::SetType(PropertyType type)
{
	mType = type;
}

const String& Property::GetID() const
{
	return mId;
}

const String& Property::GetName() const
{
	return mName;
}

const String& Property::GetHint() const
{
	return mHint;
}

const String& Property::GetEditor() const
{
	return mEditor;
}

const String& Property::GetGroup() const
{
	return mGroup;
}

void Property::SetIcon(const String &iconname)
{
	mIcon = iconname;
}

const  String& Property::GetIcon() const
{
	return mIcon;
}

Bool Property::IsReadOnly() const
{
	return mReadOnly;
}

Bool Property::AllowEmpty() const
{
	return mAllowEmpty;
}

PropertyChangeMode Property::GetChangeMode() const
{
	return mChangeMode;
}

VxfErrorStatus Property::SetStringValue(const String &value)
{
	mTextValue = value;
	mType = kPropertyTypeString;
	return eOK;
}

VxfErrorStatus Property::SetUnitValue(double value,const String &unit)
{
	mTextValue=unit;
	mNumberValue.doubleValue=value;
	mType=kPropertyTypeValue;
	return eOK;
}


const String& Property::GetStringValue() const
{
	return mTextValue;
}

VxfErrorStatus Property::SetIntegerValue(Integer value)
{
	mNumberValue.intValue = value;
	mType = kPropertyTypeInteger;
	return eOK;
}
/*
VxfErrorStatus Property::SetDwgColourValue(const dwg::Colour& value)
{
	mDwgColourValue = value;
	mType = kPropertyTypeDwgColour;
	return eOK;
}

dwg::Colour Property::GetDwgColourValue() const
{
	return mDwgColourValue;
}*/

Integer Property::GetIntegerValue() const
{
	return mNumberValue.intValue;
}

VxfErrorStatus Property::SetDoubleValue(Double value)
{
	mNumberValue.doubleValue = value;
	mType = kPropertyTypeDouble;
	return eOK;
}

Double Property::GetDoubleValue() const
{
	return mNumberValue.doubleValue;
}

VxfErrorStatus Property::SetBoolValue(Bool value)
{
	mNumberValue.boolValue = value;
	mType = kPropertyTypeBoolean;
	return eOK;
}

Bool Property::GetBoolValue() const
{
	return mNumberValue.boolValue;
}

void Property::SetValue(const Property &other)
{
	mTextValue = other.mTextValue;
	mNumberValue = other.mNumberValue;
	mType = other.mType;
}

bool Property::IsValueEquals(const Property &other)const
{
	if(mTextValue.Equals(other.mTextValue) == false)return false;
	if(mNumberValue.intValue != other.mNumberValue.intValue)return false;
	return true;
}

bool jm::operator==(Property const &v1, Property const &v2)
{
	// Actually we do not check mType, because if values are equal, but type different
	// (like for compoboxes), they are supposed to be equal anyway.

	if(v1.mId.Equals(v2.mId) == false)return false;
	if(v1.mEditor.Equals(v2.mEditor) == false)return false;

	String editor = v1.mEditor;
	if(editor.Equals("textfield"))
	{
		return v1.GetStringValue().Equals(v2.GetStringValue());
	}
	else if(editor.Equals("number"))
	{
		return v1.GetIntegerValue() == v2.GetIntegerValue();
	}
	else if(editor.Equals("checkbox"))
	{
		return v1.GetBoolValue() == v2.GetBoolValue();
	}
	else if(editor.Equals("file"))
	{
		return v1.GetStringValue().Equals(v2.GetStringValue());
	}
	else if(editor.Equals("combobox"))
	{
		return v1.GetIntegerValue() == v2.GetIntegerValue();
	}
	else if(editor.Equals("value"))
	{
		return v1.GetStringValue().Equals(v2.GetStringValue()) && jm::IsEqual(v1.GetDoubleValue(),
																									 v2.GetDoubleValue());
	}
	else if (editor.Equals("dwgcolour"))
	{
		return v1.GetIntegerValue() == v2.GetIntegerValue();
	}
	System::Log(Tr("Property not comparable"),kLogDebug);
	return false;
}
