//
//  Property.cpp
//  jameo
//
//  Created by Uwe Runtemund on 24.06.16.
//  Copyright © 2016 Jameo Software. All rights reserved.
//

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

bool Property::Is(const String &id)const
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

bool Property::IsReadOnly() const
{
	return mReadOnly;
}

bool Property::AllowEmpty() const
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

String Property::GetStringValue() const
{
	return mTextValue;
}

VxfErrorStatus Property::SetIntegerValue(int64 value)
{
	mNumberValue.intValue = value;
	mType = kPropertyTypeInteger;
	return eOK;
}

VxfErrorStatus Property::SetDwgColourValue(const dwg::Colour& value)
{
	mDwgColourValue = value;
	mType = kPropertyTypeDwgColour;
	return eOK;
}

dwg::Colour Property::GetDwgColourValue() const
{
	return mDwgColourValue;
}

int64 Property::GetIntegerValue() const
{
	return mNumberValue.intValue;
}

VxfErrorStatus Property::SetDoubleValue(double value)
{
	mNumberValue.doubleValue = value;
	mType = kPropertyTypeDouble;
	return eOK;
}

double Property::GetDoubleValue() const
{
	return mNumberValue.doubleValue;
}

VxfErrorStatus Property::SetBoolValue(bool value)
{
	mNumberValue.boolValue = value;
	mType = kPropertyTypeBoolean;
	return eOK;
}

bool Property::GetBoolValue() const
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
	// Actially we do not check mType, because if  values are equal, but type different
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
		//vvalue = WxStr2Jm(property->GetValue().GetString());
		//if (vvalue.GetUnit().IsEmpty())vvalue.SetUnit(physics::Unit::Eval(WxStr2Jm(property->GetAttribute(wxPG_ATTR_UNITS))));
		return v1.GetStringValue().Equals(v2.GetStringValue());
	}
	else if(editor.Equals("dwgcolour"))
	{
		return v1.mDwgColourValue == v2.mDwgColourValue;
	}
	std::cout << "Property not comparable" << std::endl;
	return false;
}
