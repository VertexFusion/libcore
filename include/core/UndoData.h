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
#include "Color.h"
#include "Property.h"
#include "Vertex3.h"

namespace jm
{


   /*!
    \brief This element of a linked list stores the changes made to the file in an Undo Step.

    \details This class should not be derived from Object as it should only be referenced within
    the UndoManager. External references clearly violate the concept and should be avoided!

    \ingroup datamgr
    */
   class DllExport UndoChange
   {
      public:

          /*!
           \brief Pointer to the next UndoChange element in the linked list.
           */
          UndoChange* mNext;

          /*!
           \brief Pointer to the previous UndoChange element in the linked list.
           */
          UndoChange* mPrev;

          /*!
           \brief Pointer to the object in which the change is taking place.
           */
          Object* mObject;

          /*!
           \brief Constructor for UndoChange class.
           \param object Pointer to the object in which the change is taking place.
           */
          explicit UndoChange(Object* object) noexcept;

         /*!
          \brief Destructor
          */
         virtual ~UndoChange() noexcept;

          /*!
           \brief This method performs an undo/redo step by swapping the stored value (here) with the value pointed to by the pointer.
           \note This method also triggers a regenerate() in EditableObjects.
           */
         virtual void swap();

         jm::String objname;
   };

   /*!
    \brief This class encapsulates the step when a bool value is modified.

    \details This class is responsible for managing the undo/redo functionality for bool values.
    It is used to store the changes made to a bool value and perform the undo/redo operation.

    \ingroup undo
    */
   class DllExport UndoChangeBool: public UndoChange
   {
      public:

         UndoChangeBool(Object* object, bool* ptr);

         /*!
          \copydoc UndoChange::swap()
          */
         void swap() override;

      private:

         bool* mPointer;
         bool mValue;

   };

   /*!
    \brief This class encapsulates the step when a int8 value is modified.

    \details This class is responsible for managing the undo/redo functionality for int8 values.
    It is used to store the changes made to an int8 value and perform the undo/redo operation.

    \ingroup undo
    */
   class DllExport UndoChangeInt8: public UndoChange
   {
      public:

         UndoChangeInt8(Object* object, int8* ptr);

         /*!
          \copydoc UndoChange::swap()
          */
         void swap() override;

      private:

         int8* mPointer;
         int8 mValue;

   };

   /*!
    \brief This class encapsulates the step when a uint8 value is modified.

    \details This class is responsible for managing the undo/redo functionality for uint8 values.
    It is used to store the changes made to a uint8 value and perform the undo/redo operation.

    \ingroup undo
    */
   class DllExport UndoChangeUInt8: public UndoChange
   {
      public:

         UndoChangeUInt8(Object* object, uint8* ptr);

         /*!
          \copydoc UndoChange::swap()
          */
         void swap() override;

      private:

         uint8* mPointer;
         uint8 mValue;

   };

   /*!
    \brief This class encapsulates the step when a int16 value is modified.

    \details This class is responsible for managing the undo/redo functionality for int16 values.
    It is used to store the changes made to an int16 value and perform the undo/redo operation.

    \ingroup undo
    */
   class DllExport UndoChangeInt16: public UndoChange
   {
      public:

         UndoChangeInt16(Object* object, int16* ptr);

         /*!
          \copydoc UndoChange::swap()
          */
         void swap() override;

      private:

         int16* mPointer;
         int16 mValue;

   };

   /*!
    \brief This class encapsulates the step when a uint16 value is modified.

    \details This class is responsible for managing the undo/redo functionality for uint16 values.
    It is used to store the changes made to a uint16 value and perform the undo/redo operation.

    \ingroup undo
    */
   class DllExport UndoChangeUInt16: public UndoChange
   {
      public:

         UndoChangeUInt16(Object* object, uint16* ptr);

         /*!
          \copydoc UndoChange::swap()
          */
         void swap() override;

      private:

         uint16* mPointer;
         uint16 mValue;

   };

   /*!
    \brief This class encapsulates the step when a int32 value is modified.

    \details This class is responsible for managing the undo/redo functionality for int32 values.
    It is used to store the changes made to an int32 value and perform the undo/redo operation.

    \ingroup undo
    */
   class DllExport UndoChangeInt32: public UndoChange
   {
      public:

         UndoChangeInt32(Object* object, int32* ptr);

         /*!
          \copydoc UndoChange::swap()
          */
         void swap() override;

      private:

         int32* mPointer;
         int32 mValue;

   };

   /*!
    \brief This class encapsulates the step when a uint32 value is modified.

    \details This class is responsible for managing the undo/redo functionality for uint32 values.
    It is used to store the changes made to a uint32 value and perform the undo/redo operation.

    \ingroup undo
    */
   class DllExport UndoChangeUInt32: public UndoChange
   {
      public:

         UndoChangeUInt32(Object* object, uint32* ptr);

         /*!
          \copydoc UndoChange::swap()
          */
         void swap() override;

      private:

         uint32* mPointer;
         uint32 mValue;

   };

   /*!
    \brief This class encapsulates the step when a int64 value is modified.

    \details This class is responsible for managing the undo/redo functionality for int64 values.
    It is used to store the changes made to an int64 value and perform the undo/redo operation.

    \ingroup undo
    */
   class DllExport UndoChangeInteger : public UndoChange
   {
      public:

         UndoChangeInteger(Object* object, Integer* ptr);

         /*!
          \copydoc UndoChange::swap()
          */
         void swap() override;

      private:

         Integer* mPointer;
         Integer mValue;

   };

   /*!
    \brief This class encapsulates the step when a int64 value is modified.

    \details This class is responsible for managing the undo/redo functionality for int64 values.
    It is used to store the changes made to an int64 value and perform the undo/redo operation.

    \ingroup undo
    */
   class DllExport UndoChangeInt64: public UndoChange
   {
      public:

         UndoChangeInt64(Object* object, int64* ptr);

         /*!
          \copydoc UndoChange::swap()
          */
         void swap() override;

      private:

         int64* mPointer;
         int64 mValue;

   };

   /*!
    \brief This class encapsulates the step when a uint64 value is modified.

    \details This class is responsible for managing the undo/redo functionality for uint64 values.
    It is used to store the changes made to a uint64 value and perform the undo/redo operation.

    \ingroup undo
    */
   class DllExport UndoChangeUInt64: public UndoChange
   {
      public:

         UndoChangeUInt64(Object* object, uint64* ptr);

         /*!
          \copydoc UndoChange::swap()
          */
         void swap() override;

      private:

         uint64* mPointer;
         uint64 mValue;

   };

   /*!
    \brief This class encapsulates the step when a float value is modified.

    \details This class is responsible for managing the undo/redo functionality for float values.
    It is used to store the changes made to a float value and perform the undo/redo operation.

    \ingroup undo
    */
   class DllExport UndoChangeFloat: public UndoChange
   {
      public:

         UndoChangeFloat(Object* object, float* ptr);

         /*!
          \copydoc UndoChange::swap()
          */
         void swap() override;

      private:

         float* mPointer;
         float mValue;

   };

   /*!
    \brief This class encapsulates the step when a double value is modified.

    \details This class is responsible for managing the undo/redo functionality for double values.
    It is used to store the changes made to a double value and perform the undo/redo operation.

    \ingroup undo
    */
   class DllExport UndoChangeDouble: public UndoChange
   {
      public:

         UndoChangeDouble(Object* object, double* ptr);

         /*!
          \copydoc UndoChange::swap()
          */
         void swap() override;

      private:

         double* mPointer;
         double mValue;

   };

   /*!
    \brief This class encapsulates the step when a double value is modified.

    \details This class is responsible for managing the undo/redo functionality for double values.
    It is used to store the changes made to a double value and perform the undo/redo operation.

    \ingroup undo
    */
   class DllExport UndoChangeString: public UndoChange
   {
      public:

         UndoChangeString(Object* object, String* ptr);

         /*!
          \copydoc UndoChange::swap()
          */
         void swap() override;

      private:

         String* mPointer;
         String mValue;

   };

   /*!
    \brief This class encapsulates the step when a Vertex2 value is modified.

    \details This class is responsible for managing the undo/redo functionality for Vertex2 values.
    It is used to store the changes made to a Vertex2 value and perform the undo/redo operation.

    \ingroup undo
    */
   class DllExport UndoChangeVertex2 : public UndoChange
   {
      public:

         UndoChangeVertex2(Object* object, Vertex2* ptr);

         /*!
          \copydoc UndoChange::swap()
          */
         void swap() override;

      private:

         Vertex2* mPointer;
         Vertex2 mValue;

   };

   /*!
    \brief This class encapsulates the step when a Vertex3 value is modified.

    \details This class is responsible for managing the undo/redo functionality for Vertex3 values.
    It is used to store the changes made to a Vertex3 value and perform the undo/redo operation.

    \ingroup undo
    */
   class DllExport UndoChangeVertex3: public UndoChange
   {
      public:

         UndoChangeVertex3(Object* object, Vertex3* ptr);

         /*!
          \copydoc UndoChange::swap()
          */
         void swap() override;

      private:

         Vertex3* mPointer;
         Vertex3 mValue;

   };

   /*!
    \brief This class encapsulates the step when a Date value is modified.

    \details This class is responsible for managing the undo/redo functionality for Date values.
    It is used to store the changes made to a Date value and perform the undo/redo operation.

    \ingroup undo
    */
   class DllExport UndoChangeDate: public UndoChange
   {
      public:

         UndoChangeDate(Object* object, Date* ptr);

         /*!
          \copydoc UndoChange::swap()
          */
         void swap() override;

      private:

         Date* mPointer;
         Date mValue;

   };

   /*!
    \brief This class encapsulates the step when a Color value is modified.

    \details This class is responsible for managing the undo/redo functionality for Color values.
    It is used to store the changes made to a Color value and perform the undo/redo operation.

    \ingroup undo
    */
   class DllExport UndoChangeColour: public UndoChange
   {
      public:

         UndoChangeColour(Object* object, Color* ptr);

         /*!
          \copydoc UndoChange::swap()
          */
         void swap() override;

      private:

         Color* mPointer;
         Color mValue;

   };

   /*!
    \brief This class encapsulates the step when a Property value is modified.

    \details This class is responsible for managing the undo/redo functionality for Property values.
    It is used to store the changes made to a Property value and perform the undo/redo operation.

    \ingroup undo
    */
   class DllExport UndoChangeObjectRef: public UndoChange
   {
      public:

         UndoChangeObjectRef(Object* object, Object** ptr);
         ~UndoChangeObjectRef();

         /*!
          \copydoc UndoChange::swap()
          */
         void swap() override;

      private:

         Object** mPointer;
         Object* mValue;
         // We need to store both values and retain the objects to avoid memory issues
         Object* mValue1;
         Object* mValue2;
         bool mSwapped;

   };

   /*!
    \brief This class encapsulates the step when a Property value is modified.

    \details This class is responsible for managing the undo/redo functionality for Property values.
    It is used to store the changes made to a Property value and perform the undo/redo operation.

    \ingroup undo
    */
   class DllExport UndoChangeBuffer: public UndoChange
   {
      public:

         UndoChangeBuffer(Object* object, uint8** ptr, uint64 length);

         /*!
          \copydoc UndoChange::swap()
          */
         void swap() override;

      private:

         uint8** mPointer;
         uint8* mValue;
         uint64 mLength;
   };

   /*!
    \brief This class encapsulates the step when a Property value is modified.

    \details This class is responsible for managing the undo/redo functionality for Property values.
    It is used to store the changes made to a Property value and perform the undo/redo operation.

    \ingroup undo
    */
   class DllExport UndoRegenerationMarker: public UndoChange
   {
      public:

         explicit UndoRegenerationMarker(EditableObject* object);

         /*!
          \copydoc UndoChange::swap()
          */
         void swap() override;

      private:
   };

   /*!
    \brief This class encapsulates the step when a Property value is modified.

    \details This class is responsible for managing the undo/redo functionality for Property values.
    It is used to store the changes made to a Property value and perform the undo/redo operation.

    \ingroup undo
    */
   class DllExport UndoObjectRelease: public UndoChange
   {
      public:
         UndoObjectRelease(Object* object, bool release);
         virtual ~UndoObjectRelease();

         /*!
          \copydoc UndoChange::swap()
          */
         void swap() override;

      private:
         bool mReleased;
         Object* mObject;
   };

   /*!
    \brief This object stores an editing step made to the file.
    The undo list is a doubly linked list.

    \details Each step in the undo list represents a set of changes made to the file.
    The changes are stored as UndoChange objects, which encapsulate the modifications made to different types of values.

    \ingroup datamgr
    */
   class DllExport UndoStep
   {

      public:

          /*!
           \brief The previous step that was executed.
           When "Undo" is clicked, it will jump to this step.
           This step represents the state of the file before the changes in the current step were applied.
           */
         UndoStep* prev;

          /*!
           \brief The list of changes made to the file.
           Here is the most recent change in this step.
           */
         UndoChange* recent;

          /*!
           \brief The oldest change in the list of file modifications in this step.
           This represents the state of the file before the changes in the current step were applied.
           */
          UndoChange* eldest;

          /*!
           \brief The number of changes made in this step.
           This represents the total count of modifications made to the file in this step.
           */
          uint32 count;

          /*!
           \brief Constructor for the UndoStep class.
           */
         UndoStep();

         /*!
          \brief Destructor
          */
         ~UndoStep();

          /*!
           \brief Adds a change to the step.
           \param change The change to be added.
           \details This function adds a change to the list of modifications made in this step.
           It takes a pointer to an UndoChange object as a parameter and adds it to the list of changes.
           */
         void add(UndoChange* change);

   };

}

#endif
