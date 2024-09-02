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

Property::Property(const String& id)
{
   mReadOnly = false;
   mId = id;
   mNumberValue.intValue = 0;
   mChangeMode = kPropertyChangeItself;
   mAllowEmpty = true;
   mType = kPropertyTypeString;
}


Property::Property(const String& id,
                   const String& group,
                   const String& name,
                   const String& hint,
                   const String& editor,
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

Bool Property::is(const String& id)const
{
   return mId.equals(id);
}

PropertyType Property::type() const
{
   return mType;
}

void Property::setType(PropertyType type)
{
   mType = type;
}

const String& Property::id() const
{
   return mId;
}

const String& Property::name() const
{
   return mName;
}

const String& Property::hint() const
{
   return mHint;
}

const String& Property::editor() const
{
   return mEditor;
}

const String& Property::group() const
{
   return mGroup;
}

void Property::setIcon(const String& iconname)
{
   mIcon = iconname;
}

const  String& Property::icon() const
{
   return mIcon;
}

Bool Property::isReadOnly() const
{
   return mReadOnly;
}

Bool Property::allowEmpty() const
{
   return mAllowEmpty;
}

PropertyChangeMode Property::changeMode() const
{
   return mChangeMode;
}

VxfErrorStatus Property::setStringValue(const String& value)
{
   mTextValue = value;
   mType = kPropertyTypeString;
   return eOK;
}

VxfErrorStatus Property::setUnitValue(double value, const String& unit)
{
   mTextValue = unit;
   mNumberValue.doubleValue = value;
   mType = kPropertyTypeValue;
   return eOK;
}

const String& Property::stringValue() const
{
   return mTextValue;
}

VxfErrorStatus Property::setIntegerValue(Integer value)
{
   mNumberValue.intValue = value;
   mType = kPropertyTypeInteger;
   return eOK;
}
/*
VxfErrorStatus Property::SetDwgColourValue(const dwg::Color& value)
{
	mDwgColourValue = value;
	mType = kPropertyTypeDwgColour;
	return eOK;
}

dwg::Color Property::GetDwgColourValue() const
{
	return mDwgColourValue;
}*/

Integer Property::integerValue() const
{
   return mNumberValue.intValue;
}

VxfErrorStatus Property::setDoubleValue(double value)
{
   mNumberValue.doubleValue = value;
   mType = kPropertyTypeDouble;
   return eOK;
}

double Property::doubleValue() const
{
   return mNumberValue.doubleValue;
}

VxfErrorStatus Property::setBoolValue(Bool value)
{
   mNumberValue.boolValue = value;
   mType = kPropertyTypeBoolean;
   return eOK;
}

Bool Property::boolValue() const
{
   return mNumberValue.boolValue;
}

void Property::setValue(const Property& other)
{
   mTextValue = other.mTextValue;
   mNumberValue = other.mNumberValue;
   mType = other.mType;
}

bool Property::isValueEquals(const Property& other)const
{
   if(mTextValue.equals(other.mTextValue) == false)return false;
   if(mNumberValue.intValue != other.mNumberValue.intValue)return false;
   return true;
}

bool jm::operator==(Property const& v1, Property const& v2)
{
   // Actually we do not check mType, because if values are equal, but type different
   // (like for compoboxes), they are supposed to be equal anyway.

   if(v1.mId.equals(v2.mId) == false)return false;
   if(v1.mEditor.equals(v2.mEditor) == false)return false;

   if(v1.type() == kPropertyTypeValue)
   {
      return v1.stringValue() == v2.stringValue() &&
             jm::isEqual(v1.doubleValue(), v2.doubleValue());
   }

   String editor = v1.mEditor;
   if(editor.equals("textfield"))
   {
      return v1.stringValue().equals(v2.stringValue());
   }
   else if(editor.equals("number"))
   {
      return v1.integerValue() == v2.integerValue();
   }
   else if(editor.equals("checkbox"))
   {
      return v1.boolValue() == v2.boolValue();
   }
   else if(editor.equals("file"))
   {
      return v1.stringValue().equals(v2.stringValue());
   }
   else if(editor.equals("combobox"))
   {
      return v1.integerValue() == v2.integerValue();
   }
   else if(editor.equals("value"))
   {
      return v1.stringValue().equals(v2.stringValue()) && jm::isEqual(v1.doubleValue(),
             v2.doubleValue());
   }
   else if(editor.equals("dwgcolour"))
   {
      return v1.integerValue() == v2.integerValue();
   }
   else if(editor.equals("dwglayer"))
   {
      return v1.stringValue().equals(v2.stringValue());
   }
   System::log(Tr("Property not comparable"), kLogDebug);
   return false;
}
