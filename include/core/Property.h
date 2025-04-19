////////////////////////////////////////////////////////////////////////////////////////////////////
// Name:        Property.h
// Library:     Jameo Core Library
// Purpose:     Object for property handling in applications
//
// Author:      Uwe Runtemund (2016-today)
// Modified by:
// Created:     05.06.2016
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

#ifndef jm_Property_h
#define jm_Property_h

#include <vector>

#include "Types.h"
#include "String.h"
#include "Integer.h"
#include "Vertex3.h"

namespace jm
{
   class Document;

   /*!
    \brief Status, to what extent changing the property has an influence on the status of other
    values of all properties.
    */
   enum class PropertyChangeMode
   {
      kItself = 0, /*!< Property only changes own value. */
      kOthers = 1, /*!< Property can have influence on other values. E.g. if you
											     change a point of a line, the property "length" will also
												  changed. */
      kCount = 2 /*!< Property can change the number of properties. */
   };

   enum class PropertyType
   {
      kString,
      kInteger,
      kDouble,
      kDwgColour,
      kDwgLayer,
      kDwgLineType,
      kBoolean,
      kValue
   };

   struct DllExport Variant
   {
      Variant();

      Variant(const Variant& another);

      Variant& operator=(const Variant& another);

      explicit Variant(int64 number);

      explicit Variant(double number);

      explicit Variant(const jm::String& string);

      int64 toInt64() const;

      int32 toInt32() const;

      double toDouble() const;

      const String& toString() const;

      /*!
       \brief Type of Property
       */
      PropertyType mType;

      /*!
       \brief The value of the property is usually set by the user in the GUI. Therefore, the value is typically a string, boolean, or number.
       If there is another type of value, it is wise to consider whether the transfer should be done as a text or if it should be extended here.
       However, it is always better to parse it as a text. As mentioned, it comes from the interface and not from other data.
       */
      union
      {
         bool boolValue;
         uint64 uintValue;
         int64 intValue;
         float floatValue;
         double doubleValue;
      } mNumberValue;

      String mTextValue;
   };

   /*!
    \brief This interface defines the possibility to edit properties of an object via a uniform
    interface. This is particularly useful for saving time when objects are to be edited in the GUI.

    \ingroup datamgr
    */
   struct DllExport Property
   {
      public:

         /*!
          \brief Default constructor
          */
         Property();

         /*!
          \brief Constructor with the property id
          */
         explicit Property(const String& id);

         /*!
          \brief Constructor with parameters
          \param id The id of the property
          \param group The group of the property
          \param name The name of the property
          \param hint A hint/help string of the property for the user
          \param editor Preferred editor widget for this property
          \param readOnly Status, if the property is read-only
          \param changeMode Mode of change infulence
          \param allowEmpty Status, if property can be empty
          */
         Property(const String& id,
                  const String& group,
                  const String& name,
                  const String& hint,
                  const String& editor,
                  bool readOnly = false,
                  PropertyChangeMode changeMode = PropertyChangeMode::kItself,
                  bool allowEmpty = true);

         /*!
          \brief Status, if property is read-only.
          */
         bool isReadOnly() const;

         /*!
          \brief Status, if property can be empty.
          */
         bool allowEmpty() const;

         /*!
          \brief Status, how the change of one property will effect other properties of the
          corresponding object.
          */
         PropertyChangeMode changeMode() const;

         /*!
          \brief Short call for checking is. Same as: GetId().IsEqual()
          \param id The unique id of the property.
          */
         bool is(const String& id)const;

         /*!
          \brief Returns the id of the property
          */
         const String& id() const;

         /*!
          \brief Returns the name of the property.
          */
         const String& name() const;

         /*!
          \brief Returns a help string for the property.
          */
         const String& hint() const;

         /*!
          \brief Returns an identifiert for the suggested edtior of this property.
          */
         const String& editor() const;

         /*!
          \brief Returns the group this property can belong to.
          */
         const String& group() const;

         /*!
          \brief Set the name of an icon of this property.
          \param iconname The name of the icon.
          */
         void setIcon(const String& iconname);

         /*!
          \brief Returns the icon name of this property.
          */
         const String& icon() const;

         /*!
          \brief Set the string value of this property.
          \param value The string value.
          */
         Status setStringValue(const String& value);

         /*!
          \brief Set unit value.
          \param value The number.
          \param unit The unit.
          */
         Status setUnitValue(double value, const String& unit);

         /*!
          \brief Returns the string value of this property.
          */
         const String& stringValue() const;

         /*!
          \brief Set the Integer value of this Property
          \param value The Integer value
          */
         Status setIntegerValue(int64 value);

         /*!
          \brief Returns the Integer Value of this property.
          */
         int64 integerValue() const;

         /*!
          \brief Set the Bool value of this Property
          \param value The Bool value
          */
         Status setBoolValue(bool value);

         /*!
          \brief Returns the Bool Value of this property.
          */
         bool boolValue() const;

         /*!
          \brief Set the Double value of this Property
          \param value The Bool value
          */
         Status setDoubleValue(double value);

         /*!
          \brief Returns the Dool Value of this property.
          */
         double doubleValue() const;

         /*!
          \brief Returns the type of the last value which was set. It is assumed that this is the
          right property type. Consider that on type (like comboboxes) this type can be wrong and has
          no meaning in that case.
          */
         PropertyType type() const;

         void setType(PropertyType type);

         /*!
          \brief Übernimmt den Wert aus dem anderen Property
          */
         void setValue(const Property& other);

         /*!
          \brief Prüfe, ob Werte gleich sind
          */
         bool isValueEquals(const Property& other)const;

         /*!
          \brief Implementierung des Operators ==
          */
         DllExport
         friend bool operator==(Property const& v1, Property const& v2);

      private:

         /*!
          \brief Type of Property
          */
         PropertyType mType;

         /*!
          \brief Identifier of the property.
          */
         String mId;

         /*!
          \brief Name of the group where the property will be automatically sorted at the end
          */
         String mGroup;

         /*!
          \brief Name of the property as displayed in the user interface.
          */
         String mName;

         /*!
          \brief Hint
          */
         String mHint;

         /*!
          \brief Icon name for specific GUI elements.
          */
         String mIcon;

         /*!
          \brief Editor that should be used. This must be a registered editor in the PropertyEditor.
          The following standard editors are available:
          - textfield
          - checkbox
          - combobox
          */
         String mEditor;

         /*!
          \brief Indicates whether the value can be edited by the user or is only displayed as "informative" because it is calculated, for example.
          */
         bool mReadOnly;

         /*!
          \brief Flag, if the value can be empty, 0 or NULL;
          */
         bool mAllowEmpty;

         /*!
          \brief Indicates whether a change in the value has an impact on the visible property structure, for example, because a dropdown field makes different properties visible or invisible.
          This is needed to control visibility in the Property Editor.
          */
         PropertyChangeMode mChangeMode;

         /*!
          \brief The value of the property is typically set by the user in the GUI. Therefore, the value is usually a string, boolean, or number.
          If a different type is present, it is wise to consider whether the transfer should be done as text or if it should be extended here.
          However, it is always better to parse it as text. As mentioned, it comes from the interface and not from other data.
          */
         union
         {
            bool boolValue;
            uint64 uintValue;
            int64 intValue;
            float floatValue;
            double doubleValue;
         } mNumberValue;

         String mTextValue;
         //dwg::Color mDwgColourValue;


   };

   /*!
    \brief Objects of this class have additional functions for comfortable user interaction. For
    example the undo- management is more easy usable, also the connection to the user interface can
    be done more automatic.

    \ingroup datamgr
    */
   class DllExport EditableObject: public Object
   {

      public:

         /*!
          \brief Default constructor
          \param doc The document, this object belongs to
          */
         explicit EditableObject(Document* doc);

         /*!
          \brief Determines that the visual representation should be renewed for this object in the
          next run.
          */
         virtual void regenerate();

         /*!
          \brief This method should be called by the regeneration method after the visual
          representation of this object has been updated.
          */
         virtual void regenerationDone();

         /*!
          \brief Returns the regeneration status
          */
         virtual bool shouldRegenerate() const;

         Document* document() const;

         /*!
          \brief The method set the \p value to the member the \p pointer references.

          The pointer must point to an member which is part of this or derived object. Here also the
          Undo-Manager is called for registering the change.

          \param pointer The pointer to the String member.
          \param value The new value for the member.
          */
         virtual Status setMember(String* pointer, const String& value);

         /*!
          \brief The method set the \p value to the member the \p pointer references.

          The pointer must point to an member which is part of this or derived object. Here also the
          Undo-Manager is called for registering the change.

          With the range values, a specified range for the input can be defined.
          For example, if you set \p rangeMin to 0, this method only accept positive numbers.

          \param pointer The pointer to the Integer member.
          \param value The new value for the member.
          \param rangeMin Minimum valid value. Default is INT64_MIN
          \param rangeMax Maximum valid value. Default is INT64_MAX
          */
         virtual Status setMember(int64* pointer,
                                  int64 value,
                                  int64 rangeMin = INT64_MIN,
                                  int64 rangeMax = INT64_MAX);

         /*!
          \brief The method set the \p value to the member the \p pointer references.

          The pointer must point to an member which is part of this or derived object. Here also the
          Undo-Manager is called for registering the change.

          \param pointer The pointer to the Double member.
          \param value The new value for the member.
          \return eInvalidInput if value is \c NaN, eNotChanged if value is equal to current value
          and eOK if set successfully.
          */
         virtual Status setMember(double* pointer, double value);

         virtual Status setMember(bool* pointer, bool value);

         virtual Status setMember(uint8* pointer, uint8 value);

         virtual Status setMember(int16* pointer, int16 value);

         virtual Status setMember(Vertex3* pointer, const Vertex3& value);

         /*!
          \brief Begins an editing transaction;
          */
         Status openTransaction();

         /*!
          \brief Closes an transaction;

          */
         Status closeTransaction();

      private:

         //! \brief The document this object belongs to
         Document* mDocument;

         //! \brief Status if the visual representation of this object should be regenerated.
         bool mRegenerate;
   };

}

#endif /* Attribute_h */
