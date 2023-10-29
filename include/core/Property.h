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

namespace jm
{
	/*!
	 \brief Status, to what extent changing the property has an influence on the status of other
	 values of all properties.
	 */
	enum PropertyChangeMode
	{
		kPropertyChangeItself = 0, /*!< Property only changes own value. */
		kPropertyChangeOthers = 1, /*!< Property can have influence on other values. E.g. if you
											     change a point of a line, the property "length" will also
												  changed. */
		kPropertyChangeCount = 2 /*!< Property can change the number of properties. */
	};

	enum PropertyType
	{
		kPropertyTypeString,
		kPropertyTypeInteger,
		kPropertyTypeDouble,
		kPropertyTypeDwgColour,
		kPropertyTypeDwgLayer,
		kPropertyTypeDwgLineType,
		kPropertyTypeBoolean,
		kPropertyTypeValue
	};

	/*!
	 \brief This interface defines the possibility to edit properties of an object via a uniform
	 interface. This is particularly useful for saving time when objects are to be edited in the GUI.
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
			Property(const String &id);

			/*!
			 \brief Constructor with parameters
			 \param id The id of the property
			 \param group The group of the property
			 \param name The name of the property
			 \param hint A hint/help string of the property for the user
			 \param editor Preffered editor widget for this property
			 \param readOnly Status, if the property is read-only
			 \param changeMode Mode of change infulence
			 \param allowEmpty Status, if property can be empty
			 */
			Property(const String &id,
			         const String &group,
			         const String &name,
			         const String &hint,
			         const String &editor,
			         bool readOnly = false,
			         PropertyChangeMode changeMode = kPropertyChangeItself,
			         bool allowEmpty = true);

			/*!
			 \brief Status, if property is read-only.
			 */
			Bool IsReadOnly() const;

			/*!
			 \brief Status, if property can be empty.
			 */
			Bool AllowEmpty() const;

			/*!
			 \brief Status, how the change of one property will effect other properties of the
			 corresponding object.
			 */
			PropertyChangeMode GetChangeMode() const;

			/*!
			 \brief Short call for checking is. Same as: GetId().IsEqual()
			 \param id The unique id of the property.
			 */
			Bool Is(const String &id)const;

			/*!
			 \brief Returns the id of the property
			 */
			const String& GetID() const;

			/*!
			 \brief Returns the name of the property.
			 */
			const String& GetName() const;

			/*!
			 \brief Returns a help string for the property.
			 */
			const String& GetHint() const;

			/*!
			 \brief Returns an identifiert for the suggested edtior of this property.
			 */
			const String& GetEditor() const;

			/*!
			 \brief Returns the group this property can belong to.
			 */
			const String& GetGroup() const;

			/*!
			 \brief Set the name of an icon of this property.
			 \param iconname The name of the icon.
			 */
			void SetIcon(const String &iconname);

			/*!
			 \brief Returns the icon name of this property.
			 */
			const String& GetIcon() const;

			/*!
			 \brief Set the string value of this property.
			 \param value The string value.
			 */
			VxfErrorStatus SetStringValue(const String &value);

			/*!
			 \brief Returns the string value of this property.
			 */
			const String& GetStringValue() const;

			/*!
			 \brief String festlegen
			 */
			//VxfErrorStatus SetDwgColourValue(const dwg::Colour& value);

			/*!
			 \brief Gibt String zurück
			 */
			//dwg::Colour GetDwgColourValue() const;

			/*!
			 \brief Set the Integer value of this Property
			 \param value The Integer value
			 */
			VxfErrorStatus SetIntegerValue(Integer value);

			/*!
			 \brief Returns the Integer Value of this property.
			 */
			Integer GetIntegerValue() const;

			/*!
			 \brief Set the Bool value of this Property
			 \param value The Bool value
			 */
			VxfErrorStatus SetBoolValue(Bool value);

			/*!
			 \brief Returns the Bool Value of this property.
			 */
			Bool GetBoolValue() const;

			/*!
			 \brief Set the Double value of this Property
			 \param value The Bool value
			 */
			VxfErrorStatus SetDoubleValue(Double value);

			/*!
			 \brief Returns the Dool Value of this property.
			 */
			Double GetDoubleValue() const;

			/*!
			 \brief Returns the type of the last value which was set. It is assumed that this is the
			 right property type. Consider that on type (like comboboxes) this type can be wrong and has
			 no meaning in that case.
			 */
			PropertyType GetType() const;

			void SetType(PropertyType type);

			/*!
			 \brief Übernimmt den Wert aus dem anderen Property
			 */
			void SetValue(const Property &other);

			/*!
			 \brief Prüfe, ob Werte gleich sind
			 */
			bool IsValueEquals(const Property &other)const;

			/*!
			 \brief Implementierung des Operators ==
			 */
			DllExport
			friend bool operator==(Property const &v1, Property const &v2);

		private:

			/*!
			 \brief Type of Property
			 */
			PropertyType mType;

			/*!
			 \brief Identifier des Properties
			 */
			String mId;

			/*!
			 \brief Gruppenname der Gruppe, in der die Eigenschaft automatisch am Ende einsortiert wird
			 */
			String mGroup;

			/*!
			 \brief Name der Eigenschaft, wie sie in der Oberfläche angezeigt wird
			 */
			String mName;

			/*!
			 \brief Hinweis
			 */
			String mHint;

			/*!
			 \brief Iconname für bestimmte GUI-Elemente
			 */
			String mIcon;

			/*!
			 \brief Editor, der zur Verwendung genommen werden soll. Dies muss ein registierter Editor im PropertyEditor sein.
			 folgende Standardeditoren gibt es:
			 textfield
			 checkbox
			 combobox
			 */
			String mEditor;

			/*!
			 \brief Status, ob der Wert vom Anwender bearbeitet werden kann, oder nur "informativ" dargestellt wird, weil er z.B. berechnet wurde
			 */
			bool mReadOnly;

			/*!
			 \brief Flag, if the value can be empty, 0 or NULL;
			 */
			bool mAllowEmpty;

			/*!
			 \brief Status, ob eine Veränderung des Wertes Einfluss auf die sichtbare Eigenschaftsstruktur hat, beispielsweise weil ein Auswahlfeld verschiedenen andere Eigenschaften sichtbar oder unsichtbar macht.
			 Dies wird benötigt, um die Sichtbarkeit im Propertyeditor zu steuern.
			 */
			PropertyChangeMode mChangeMode;

			/*!
			 \brief Der Wert des Properties wird normalerweise durch den Anwender in der GUI festgelegt. Also ist der Wert üblicherweise ein String, Bool oder Zahl.
			 Sollte ein anderer Typ vorhanden sein, ist klug zu überlegen, ob die Übergabe nicht als Text passiert, oder ob das hier erweitert werden soll.
			 Es würde aber immer besser ein, einen Text zu parsen. Wie gesagt: Es kommt aus der Oberfläche und nicht von anderen Daten
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
			//dwg::Colour mDwgColourValue;


	};

	/*!
	 \brief Alle Objekte, die diese Schnittstelle ableiten, können über den Einheitlichen PropertyEditor bearbeitet werden.
	 */
	class DllExport EditableObject: public Object
	{

		public:


			EditableObject(): Object()
			{
				mRegenerate = true;
			};

			/*!
			 \brief Legt fest, dass für dieses Objekt im nächsten Durchlauf die visuelle Repräsentation erneuert werden sollte.
			 */
			virtual void Regenerate()
			{
				mRegenerate = true;
			}

			/*!
			 \brief Diese Methode soll von der Regenerationsmethode aufgerufen werden nachdem die visuelle Repräsentation
			 dieses Objektes aktualisiert wurde.
			 */
			virtual void RegenerationDone()
			{
				mRegenerate = false;
			}

			/*!
			 \brief Gibt den Regenerationsstatus zurück.
			 */
			virtual bool ShouldRegenerate() const
			{
				return mRegenerate;
			}

		private:

			/*!
			 \brief Status, ob im nächten Durchlauf die visuelle Repräsentation erneuert werden sollte
			 */
			bool mRegenerate;

	};

}

#endif /* Attribute_h */
