////////////////////////////////////////////////////////////////////////////////////////////////////
// Name:        LinkedList.cpp
// Library:     Jameo Core Library
// Purpose:     LinkedList with Undo-Management
//
// Author:      Uwe Runtemund (2016-today)
// Modified by:
// Created:     26.11.2016
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

#include "Precompiled.hpp"

using namespace jm;

LListElement::LListElement(): Object()
{
   next = nullptr;
   prev = nullptr;
   data = nullptr;
}

LinkedList::LinkedList(Object* owner): Object()
{
   listStart = nullptr;
   listEnd = nullptr;
   current = nullptr;
   count = 0;
   mOwner = owner;
   if(mOwner == nullptr)
   {
      System::log("Owner of LinkedList must not be nullptr!", kLogWarning);
   }
}

LinkedList::~LinkedList()
{
   clear(nullptr);
}

bool LinkedList::hasNext()
{
   return current != nullptr;
}

LListElement* LinkedList::nextElement()
{
   LListElement* ret = current;
   current = current->next;
   return ret;
}

Object* LinkedList::next()
{
   Object* ret = current->data;
   current = current->next;
   return ret;
}

Object* LinkedList::first() const
{
   if(count == 0)return nullptr;
   return listStart->data;
}

Object* LinkedList::last() const
{
   if(count == 0)return nullptr;
   return listEnd->data;
}

void LinkedList::rewind()
{
   current = listStart;
}

void LinkedList::clear(UndoManager* um)
{
   if(um != nullptr)
   {
      while(listStart != nullptr)
      {
         LListElement* victim = listStart;
         remove(victim, um); //Here undo magic is done
      }
   }
   else
   {
      rewind();
      while(hasNext())nextElement()->release();
   }

   listStart = nullptr;
   listEnd = nullptr;
   current = nullptr;
   count = 0;
}

void LinkedList::add(Object* data, UndoManager* um)
{
   LListElement* item = new LListElement();
   if(um != nullptr)um->registerChange(item, reinterpret_cast<Object * *>(&(item->data)));
   item->data = data;
   add(item, um);
}

void LinkedList::add(LListElement* item, UndoManager* um)
{
   if(um != nullptr)
   {
      um->registerChange(item, reinterpret_cast<Object**>(& (item->prev)));
      if(listEnd != nullptr)um->registerChange(listEnd, reinterpret_cast<Object * *>(& (listEnd->next)));
      if(listStart == nullptr)um->registerChange(this, reinterpret_cast<Object * *>(&listStart));
      um->registerChange(this, reinterpret_cast<Object**>(&listEnd));
      um->registerChange(this, &count);
   }

   item->prev = listEnd;

   if(listEnd != nullptr)
   {
      listEnd->next = item;
      item->prev = listEnd;
   }

   listEnd = item;

   if(listStart == nullptr)
   {
      listStart = item;
   }
   count++;
}

void LinkedList::addBefore(Object* addBeforeThis, Object* itemToAdd, UndoManager* um)
{
   LListElement* before = nullptr;

   rewind();
   while(hasNext())
   {
      LListElement* elem = nextElement();
      if(elem->data == addBeforeThis)
      {
         before = elem;
         break;
      }
   }

   if(before != nullptr)
   {
      LListElement* item = new LListElement();
      if(um != nullptr)um->registerChange(item, (Object* *) & (item->data));
      item->data = itemToAdd;

      addBefore(before, item, um);
   }
}

void LinkedList::addBefore(LListElement* addBeforeThis, LListElement* itemToAdd, UndoManager* um)
{
   LListElement* addAfterThis = addBeforeThis->prev;

   if(um != nullptr)
   {
      um->registerChange(itemToAdd, (Object**) & (itemToAdd->prev));
      um->registerChange(itemToAdd, (Object**) & (itemToAdd->next));
      if(listStart == addBeforeThis)um->registerChange(this, (Object* *)&listStart);
      um->registerChange(addBeforeThis, (Object**) & (addBeforeThis->prev));
      if(addBeforeThis->prev != nullptr)um->registerChange(addBeforeThis,
               (Object* *) & (addAfterThis->next));
      um->registerChange(this, &count);
   }

   //Listenanfang anpassen
   if(listStart == addBeforeThis)listStart = itemToAdd;

   //ItemToAdd anpassen
   itemToAdd->prev = addAfterThis;
   itemToAdd->next = addBeforeThis;

   //Vorgänger anpassen
   if(addAfterThis != nullptr)addAfterThis->next = itemToAdd;

   //Nachfolger anpassen
   addBeforeThis->prev = itemToAdd;

   //Zähler anpassen
   count++;
}


VxfErrorStatus LinkedList::remove(LListElement* element, UndoManager* um)
{
   LListElement* prev = element->prev;
   LListElement* next = element->next;

   if(um != nullptr)
   {
      if(prev != nullptr)um->registerChange(prev, (Object* *) & (prev->next));
      if(next != nullptr)um->registerChange(next, (Object* *) & (next->prev));
      if(listStart == element)um->registerChange(this, (Object* *) &listStart);
      if(listEnd == element)um->registerChange(this, (Object* *) &listEnd);
      um->registerChange(element, reinterpret_cast<Object**>(&element->prev));
      um->registerChange(element, (Object**) & (element->next));
      um->registerChange(this, &count);
      um->registerRelease(element);
   }

   if(prev != nullptr)prev->next = next;
   if(next != nullptr)next->prev = prev;

   if(listStart == element)
   {
      if(listStart->next != nullptr)listStart = listStart->next;
      else listStart = nullptr;
   }

   if(listEnd == element)
   {
      if(listEnd->prev != nullptr)listEnd = listEnd->prev;
      else listEnd = nullptr;
   }

   element->prev = nullptr;
   element->next = nullptr;
   element->release();
   count--;

   return eOK;
}


VxfErrorStatus LinkedList::remove(const Object* data, UndoManager* um)
{
   rewind();
   while(hasNext())
   {
      LListElement* elem = nextElement();
      if(elem->data == data)
      {
         return remove(elem, um);
      }
   }

   return eNotFound;
}

uint32 LinkedList::size() const
{
   return count;
}

void LinkedList::swapData(Object* data1, Object* data2, UndoManager* um)
{
   LListElement* elem1 = nullptr;
   LListElement* elem2 = nullptr;

   rewind();
   while(hasNext())
   {
      LListElement* elem = nextElement();
      if(elem->data == data1)elem1 = elem;
      if(elem->data == data2)elem2 = elem;
      if(elem1 != nullptr && elem2 != nullptr)break;
   }

   if(elem1 != nullptr && elem2 != nullptr)
   {
      if(um != nullptr)
      {
         um->registerChange(elem1, (Object**) & (elem1->data));
         um->registerChange(elem2, (Object**) & (elem2->data));
         elem1->data = data2;
         elem2->data = data1;
      }
   }
}

LinkedListIterator LinkedList::iterator() const
{
   return LinkedListIterator(this);
}

LinkedListIterator::LinkedListIterator(const LinkedList* list)
{
   if(list == nullptr)
   {
      listStart = nullptr;
      listEnd = nullptr;
      current = nullptr;
      count = 0;
      return;
   }
   listStart = list->listStart;
   listEnd = list->listEnd;
   current = listStart;
   count = list->count;
}

LinkedListIterator::LinkedListIterator(const LinkedListIterator& other)
{
   listStart = other.listStart;
   listEnd = other.listEnd;
   current = other.current;
   count = other.count;
}


bool LinkedListIterator::hasNext()
{
   return current != nullptr;
}

Object* LinkedListIterator::next()
{
   Object* ret = current->data;
   current = current->next;
   return ret;
}

Object* LinkedListIterator::seek() const
{
   return current->data;
}

LinkedListIterator::~LinkedListIterator()
{

}

namespace jm
{
   LinkedListIterator& LinkedListIterator::operator=(const LinkedListIterator& other)
   {
      if(this != &other)
      {
         listStart = other.listStart;
         listEnd = other.listEnd;
         current = other.current;
         count = other.count;
      }

      return *this;
   }
}
