////////////////////////////////////////////////////////////////////////////////////////////////////
// Name:        LinkedList.h
// Library:     Jameo Core Library
// Purpose:     Helper classes variable List
//
// Author:      Uwe Runtemund (2013-today)
// Modified by:
// Created:     24.08.2013
//
// Copyright:   (c) 2013 Jameo Software, Germany. https://jameo.de
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

#ifndef jm_LinkedList_h
#define jm_LinkedList_h

#include "Object.h"
#include "UndoManager.h"
#include "Iterator.h"

namespace jm
{
   class LinkedList;

   class LListElement : public Object
   {

      public:
         LListElement* next;
         LListElement* prev;
         Object* data;

         LListElement();

         jm::String displayName() const override
         {
            return "jm::LListElement";
         };

   };

   class DllExport LinkedListIterator : public Iterator
   {

      public:

         LinkedListIterator(const LinkedList* list);

         LinkedListIterator(const LinkedListIterator& other);

         bool hasNext();

         Object* next();

         // Return the next object without moving the iterator
         Object* seek() const;

         ~LinkedListIterator();

         LinkedListIterator& operator=(const LinkedListIterator& other);

      private:

         LListElement* listStart;
         LListElement* listEnd;
         LListElement* current;

         uint32 count;

   };

   /*!
    \brief This class provides a linked list including undo management.
    \ingroup core
    */
   class DllExport LinkedList: public Object
   {
      public:

          /*!
           \brief Constructor for the LinkedList. Initializes all variables.
           \param owner The owner of the list. Ideally an Editable object. This object may receive
           regenerate events during undo steps.
           */
         LinkedList(Object* owner);

          /*!
           \brief Destructor for the linked list. This function deletes all variables.
           \warning If you are using the LinkedList together with UndoManager, you must call
           LinkedList::clear() with the UndoManager object to gracefully erase the objects.
           Alternatively, you can call UndoManager::clearStacks() to achieve the same effect.
           Otherwise, memory errors may occur.
           */
         ~LinkedList();

          /*!
           \brief This method returns true if there is a next element in the list
           */
         bool hasNext();

          /*!
           \brief Iterates to the next element in the list and returns the current one.
           The next element can be NULL, but then hasNext() will return false.
           */
         Object* next();

         /*!
          \brief Returns the first element of the list.
          */
         Object* first() const;

         /*!
          \brief Returns the last element of the list.
          */
         Object* last() const;

         void rewind();

         void clear(UndoManager* um);

         void add(Object* data, UndoManager* um);

         void addBefore(Object* addBeforeThis, Object* itemToAdd, UndoManager* um);

         /*!
          \brief removes the element from the list.
          \return eOK on success. eNotFound, if entry is not in the list.
          */
         VxfErrorStatus remove(const Object* data, UndoManager* um);

         void swapData(Object* data1, Object* data2, UndoManager* um);

         /*!
          \brief Returns the number of entries in this list.
          */
         uint32 size() const;

         LinkedListIterator iterator() const;

         jm::String displayName() const override
         {
            return "jm::LinkedList";
         };

      private:

         LListElement* listStart;
         LListElement* listEnd;
         LListElement* current;

         uint32 count;

         Object* mOwner;

         friend class LinkedListIterator;

          /*!
            \brief Iterates to the next element in the list and returns the current one.
            The next element can be NULL, but then hasNext() will return false.
            */
         LListElement* nextElement();

         void add(LListElement* item, UndoManager* um);

         void addBefore(LListElement* addBeforeThis, LListElement* itemToAdd, UndoManager* um);

         VxfErrorStatus remove(LListElement* element, UndoManager* um);

   };



}

#endif
