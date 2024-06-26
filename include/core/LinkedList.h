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

         LinkedListIterator(const LinkedListIterator &other);

         bool hasNext();

         Object* next();

         Object* Seek();//Gibt das nächste Objekt zurück, ohne den Iterator zu bewegenn

         ~LinkedListIterator();

         LinkedListIterator &operator=(const LinkedListIterator &other);

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
          \brief Konstruktor für die Verkettete Liste. Hier werden alle Variablen initialisiert.
          \param owner Der Besitzer der Liste. Bestenfalls ein Editable-Objekt. Dieses erhält
          ggf. regenerate-Events bei Undo-Schritten.
          */
         LinkedList(Object* owner);

         /*!
          \brief Destructor für die verkettete Liste. Hier werden alle Variabeln gelöscht
          \warning If you use the LinkedList together with UndoManager, you must call
          LinkedList::clear() with the UndoManager object to erase the objects gracefully.
          Alternatively you can call UndoManager::clearStacks() to get the same effect.
          Otherwise memory errors occur.
          */
         ~LinkedList();

         /*!
          \brief Diese Methode gibt wahr zurück, wenn ein nächstes Element in der Liste vorhanden ist
          */
         bool hasNext();
         /*!
          \brief Iteriert die Liste zu nächsten Element und gibt das aktuelle zurück.
          Das nächste Element kann NULL sein, aber dann wird hasNext() falsch zurückgeben.
          */
         Object* next();

         /*!
          \brief Gibt das erste Element der Liste zurück
          */
         Object* first() const;

         /*!
          \brief Gibt das letzte Element der Liste zurück
          */
         Object* last() const;

         void rewind();

         void clear(UndoManager* um);

         void add(Object* data, UndoManager* um);

         void addBefore(Object* addBeforeThis, Object* itemToAdd, UndoManager* um);

         void remove(const Object* data, UndoManager* um);

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
         	\brief Iteriert die Liste zu nächsten Element und gibt das aktuelle zurück.
         	Das nächste Element kann NULL sein, aber dann wird hasNext() falsch zurückgeben.
         	*/
         LListElement* nextElement();

         void add(LListElement* item, UndoManager* um);

         void addBefore(LListElement* addBeforeThis, LListElement* itemToAdd, UndoManager* um);

         void remove(LListElement* element, UndoManager* um);

   };



}

#endif
