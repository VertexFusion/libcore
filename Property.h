////////////////////////////////////////////////////////////////////////////////////////////////////
// Name:        Property.h
// Library:     VertexFusion Library
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
#include "dwg/DwgTypes.h"
#include "dwg/DwgColour.h"

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

			Property();

			Property(const String &id);

			/*!
			 \brief Konstruktor
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
			 \brief Status, ob die Eigenschaft veränderlich ist oder nicht
			 */
			bool IsReadOnly() const;

			/*!
			 \brief Status, ob der Wert leer sein darf
			 */
			bool AllowEmpty() const;

			/*!
			 \brief Status, wie eine Änderung der Eigenschaft sicht auf den Wert oder andere
			 Werte ausübt.
			 */
			PropertyChangeMode GetChangeMode() const;

			/*!
			 \brief Status, ob die Eigenschaft auch die Werte anderer Felder beeinflussen kann
			 */
			bool IsChangingOtherValues() const;
		
			/*!
			 \brief Verkürzte Methode, um die ID zu überprüfen. Statt "GetId().IsEqual()"
			 */
			bool Is(const String &id)const;

			/*!
			 \brief Gibt die ID zurück
			 */
			const String& GetID() const;

			/*!
			 \brief Gibt den Namen zurück
			 */
			const String& GetName() const;

			/*!
			 \brief Gibt den Namen zurück
			 */
			const String& GetHint() const;

			/*!
			 \brief Gibt den Editor zurück
			 */
			const String& GetEditor() const;

			/*!
			 \brief Gibt die Gruppe zurück
			 */
			const String& GetGroup() const;

			/*!
			 \brief String festlegen
			 */
			void SetIcon(const String &iconname);

			/*!
			 \brief Gibt den Namen zurück
			 */
			const String& GetIcon() const;

			/*!
			 \brief String festlegen
			 */
			VxfErrorStatus SetStringValue(const String &value);

			/*!
			 \brief Gibt String zurück
			 */
			String GetStringValue() const;

			/*!
			 \brief String festlegen
			 */
			VxfErrorStatus SetDwgColourValue(const DwgColour& value);

			/*!
			 \brief Gibt String zurück
			 */
			DwgColour GetDwgColourValue() const;

			/*!
			 \brief Legt Integer fest
			 */
			VxfErrorStatus SetIntegerValue(int64 value);

			/*!
			 \brief Gibt integer zurück
			 */
			int64 GetIntegerValue() const;

			/*!
			 \brief Legt Integer fest
			 */
			VxfErrorStatus SetBoolValue(bool value);

			/*!
			 \brief Gibt integer zurück
			 */
			bool GetBoolValue() const;

			/*!
			 \brief Legt Double fest
			 */
			VxfErrorStatus SetDoubleValue(double value);

			/*!
			 \brief Gibt Double zurück
			 */
			double GetDoubleValue() const;

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
			DwgColour mDwgColourValue;


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
