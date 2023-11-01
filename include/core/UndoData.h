////////////////////////////////////////////////////////////////////////////////////////////////////
// Name:        UndoData.h
// Library:     Jameo Core Library
// Purpose:     Undo/Redo Management
//
// Author:      Uwe Runtemund (2014-today)
// Modified by:
// Created:     11.02.2014
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

#ifndef jm_UndoData_h
#define jm_UndoData_h

#include "String.h"
#include "Date.h"
#include "Colour.h"
#include "Property.h"
#include "Vertex3.h"

namespace jm
{


	/*!
	 \brief Dieses Element einer Verketteten liste speichert in einem Undo-Step die Veränderungden
	 an der Datei.
	 \discussion Diese Klasse soll nicht von Object abgeleitet werden, das sie nur innerhalb des
	 Undomanager referenziert werden soll. Externe Referenzierungen verstoßen eindeutig gegen das
	 Konzept und sind zu unterlassen!

	 \ingroup datamgr
	 */
	class DllExport UndoChange
	{
		public:

			/*!
			 \brief Das nächste Element in der Liste
			 */
			UndoChange* mNext;

			/*!
			 \brief Das nächste Element in der Liste
			 */
			UndoChange* mPrev;

			/*!
			 \brief Das Objekt, in dem die Änderung stattfindet
			 */
			Object* mObject;

			/*!
			 \brief Konstruktir
			 */
			UndoChange(Object* object);

			/*!
			 \brief Destructor
			 */
			virtual ~UndoChange();

			/*!
			 \brief Diese Methode macht einen Rückgängig-Schritt und wandelt es in einen Redo-Schritt
			 oder umgekehrt.
			 \discussion Es werden der gespeicherte Wert (hier) mit dem gespeicherten Wert auf dem der
			 Pointer zeigt vertauscht. Außerdem wird ein Regenerate() in EditableObjects ausgelöst.
			 */
			virtual void Swap();

	};

	/*!
	 \brief Diese Klasse kapselt den Schritt, wenn ein bool-Wert verändert werden soll.
	 */
	class DllExport UndoChangeBool: public UndoChange
	{
		public:

			UndoChangeBool(Object* object, bool *ptr);
			void Swap();

		private:

			bool* mPointer;
			bool mValue;

	};

	/*!
	 \brief Diese Klasse kapselt den Schritt, wenn ein int8-Wert verändert werden soll.
	 */
	class DllExport UndoChangeInt8: public UndoChange
	{
		public:

			UndoChangeInt8(Object* object, int8 *ptr);
			void Swap();

		private:

			int8* mPointer;
			int8 mValue;

	};

	class DllExport UndoChangeUInt8: public UndoChange
	{
		public:

			UndoChangeUInt8(Object* object, uint8 *ptr);
			void Swap();

		private:

			uint8* mPointer;
			uint8 mValue;

	};

	class DllExport UndoChangeInt16: public UndoChange
	{
		public:

			UndoChangeInt16(Object* object, int16 *ptr);
			void Swap();

		private:

			int16* mPointer;
			int16 mValue;

	};

	class DllExport UndoChangeUInt16: public UndoChange
	{
		public:

			UndoChangeUInt16(Object* object, uint16 *ptr);
			void Swap();

		private:

			uint16* mPointer;
			uint16 mValue;

	};

	class DllExport UndoChangeInt32: public UndoChange
	{
		public:

			UndoChangeInt32(Object* object, int32 *ptr);
			void Swap();

		private:

			int32* mPointer;
			int32 mValue;

	};

	class DllExport UndoChangeUInt32: public UndoChange
	{
		public:

			UndoChangeUInt32(Object* object, uint32 *ptr);
			void Swap();

		private:

			uint32* mPointer;
			uint32 mValue;

	};

	class DllExport UndoChangeInteger : public UndoChange
	{
	public:

		UndoChangeInteger(Object* object, Integer* ptr);
		void Swap();

	private:

		Integer* mPointer;
		Integer mValue;

	};

	class DllExport UndoChangeInt64: public UndoChange
	{
		public:

			UndoChangeInt64(Object* object, int64 *ptr);
			void Swap();

		private:

			int64* mPointer;
			int64 mValue;

	};

	class DllExport UndoChangeUInt64: public UndoChange
	{
		public:

			UndoChangeUInt64(Object* object, uint64 *ptr);
			void Swap();

		private:

			uint64* mPointer;
			uint64 mValue;

	};

	class DllExport UndoChangeFloat: public UndoChange
	{
		public:

			UndoChangeFloat(Object* object, float *ptr);
			void Swap();

		private:

			float* mPointer;
			float mValue;

	};

	class DllExport UndoChangeDouble: public UndoChange
	{
		public:

			UndoChangeDouble(Object* object, double *ptr);
			void Swap();

		private:

			double* mPointer;
			double mValue;

	};

	class DllExport UndoChangeString: public UndoChange
	{
		public:

			UndoChangeString(Object* object, String *ptr);
			void Swap();

		private:

			String* mPointer;
			String mValue;

	};

	class DllExport UndoChangeVertex2 : public UndoChange
	{
		public:

			UndoChangeVertex2(Object* object, Vertex2* ptr);
			void Swap();

		private:

			Vertex2* mPointer;
			Vertex2 mValue;

	};

	class DllExport UndoChangeVertex3: public UndoChange
	{
		public:

			UndoChangeVertex3(Object* object, Vertex3 *ptr);
			void Swap();

		private:

			Vertex3* mPointer;
			Vertex3 mValue;

	};

	class DllExport UndoChangeDate: public UndoChange
	{
		public:

			UndoChangeDate(Object* object, Date *ptr);
			void Swap();

		private:

			Date* mPointer;
			Date mValue;

	};

	class DllExport UndoChangeColour: public UndoChange
	{
		public:

			UndoChangeColour(Object* object, Colour *ptr);
			void Swap();

		private:

			Colour* mPointer;
			Colour mValue;

	};

	class DllExport UndoChangeObjectRef: public UndoChange
	{
		public:

			UndoChangeObjectRef(Object* object, Object **ptr);
			~UndoChangeObjectRef();
			void Swap();

		private:

			Object** mPointer;
			Object* mValue;

	};

	class DllExport UndoChangeBuffer: public UndoChange
	{
		public:

			UndoChangeBuffer(Object* object, uint8 **ptr, uint64 length);
			void Swap();

		private:

			uint8** mPointer;
			uint8* mValue;
			uint64 mLength;
	};

	class DllExport UndoRegenerationMarker: public UndoChange
	{
		public:

			UndoRegenerationMarker(EditableObject* object);
			void Swap();

		private:

			Colour* mPointer;

	};

	class DllExport UndoObjectRelease: public UndoChange
	{
		public:
			UndoObjectRelease(Object* object, bool release);
			virtual ~UndoObjectRelease();
			void Swap();
        private:
            bool mReleased;
            Object* mObject;
	};

	/*!
	 \brief Dieses Objekt speichert einen Bearbeitungsschritt an der Datei.
	 Die Undoliste ist eine doppelt verkettete Liste.

	 \ingroup datamgr
	 */
	class DllExport UndoStep
	{

		public:

			/*!
			 \brief Der vorherige Schritt, der ausgeführt wurde.
			 Wenn auf "Rückgängig" geklickt wird, wird auf diesen Schritt gesprungen
			 */
			UndoStep* prev;

			/*!
			 \brief Die Liste mit den Änderungen an der Datei.
			 Hier die letzte Änderung in diesem Schritt
			 */
			UndoChange* recent;

			/*!
			 \brief Die Liste mit den Änderungen an der Datei.
			 Hier die älteste Änderung in diesem Schritt
			 */
			UndoChange* eldest;

			/*!
			 \brief Die Anzahl der Änderungen
			 */
			uint32 count;

			/*!
			 \brief Konstruktor
			 */
			UndoStep();

			/*!
			 \brief Destructor
			 */
			~UndoStep();

			/*!
			 \brief Fügt eine Änderung hinzu.
			 \param change Die Änderung, die hinzugefügt wird.
			 */
			void AddChange(UndoChange* change);

	};

}

#endif
