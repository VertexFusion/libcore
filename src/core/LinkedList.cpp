//
//  LinkedList.cpp
//  jameo
//
//  Created by Uwe Runtemund on 26.11.16.
//  Copyright © 2016 Jameo Software. All rights reserved.
//

#include "Precompiled.h"

using namespace jm;

LListElement::LListElement(): Object()
{
	next = NULL;
	prev = NULL;
	data = NULL;
}

LinkedList::LinkedList(Object* owner): Object()
{
	listStart = NULL;
	listEnd = NULL;
	current = NULL;
	count = 0;
	mOwner = owner;
	if(mOwner == NULL)
	{
		System::Log("Owner of LinkedList must not be NULL!",kLogWarning);
	}
}

LinkedList::~LinkedList()
{
	Clear(NULL);
}

bool LinkedList::HasNext()
{
	return current != NULL;
}

LListElement* LinkedList::NextElement()
{
	LListElement* ret = current;
	current = current->next;
	return ret;
}

Object* LinkedList::Next()
{
	Object* ret = current->data;
	current = current->next;
	return ret;
}

Object* LinkedList::First()
{
	if(count == 0)return NULL;
	return listStart->data;
}

Object* LinkedList::Last()
{
	if(count == 0)return NULL;
	return listEnd->data;
}

void LinkedList::Rewind()
{
	current = listStart;
}

void LinkedList::Clear(UndoManager* um)
{
	if(um != NULL)
	{
		while(listStart!=NULL)
		{
			LListElement* victim=listStart;
			Remove(victim,um);
		}
//		um->RegisterChange(mOwner, (Object**) &listEnd);
//		um->RegisterChange(mOwner, (Object**) &listStart);
//		um->RegisterChange(mOwner, &count);
	}
	else
	{
		Rewind();
		while(HasNext())delete NextElement();
	}

	listStart = NULL;
	listEnd = NULL;
	current = NULL;
	count = 0;
}

LListElement* LinkedList::Add(Object* data, UndoManager* um)
{
	LListElement* item = new LListElement();
	if(um != NULL)um->RegisterChange(mOwner, reinterpret_cast<Object**>(&(item->data)));
	item->data = data;
	Add(item, um);
	return item;
}

void LinkedList::Add(LListElement* item, UndoManager* um)
{
	if(um != NULL)
	{
		um->RegisterChange(mOwner, reinterpret_cast<Object**>(& (item->prev)));
		if(listEnd != NULL)um->RegisterChange(mOwner, reinterpret_cast<Object**>(& (listEnd->next)));
		if(listStart == NULL)um->RegisterChange(mOwner, reinterpret_cast<int64*>(&listStart));
		um->RegisterChange(mOwner, reinterpret_cast<int64*>(&listEnd));
		um->RegisterChange(mOwner, &count);
	}

	item->prev = listEnd;

	if(listEnd != NULL)
	{
		listEnd->next = item;
		item->prev = listEnd;
	}

	listEnd = item;

	if(listStart == NULL)
	{
		listStart = item;
	}
	count++;
}

void LinkedList::AddBefore(Object* addBeforeThis, Object* itemToAdd, UndoManager* um)
{
	LListElement* before = NULL;

	Rewind();
	while(HasNext())
	{
		LListElement* elem = NextElement();
		if(elem->data == addBeforeThis)
		{
			before = elem;
			break;
		}
	}

	if(before != NULL)
	{
		LListElement* item = new LListElement();
		if(um != NULL)um->RegisterChange(mOwner, (Object**) & (item->data));
		item->data = itemToAdd;

		AddBefore(before, item, um);
	}
}

void LinkedList::AddBefore(LListElement* addBeforeThis, LListElement* itemToAdd, UndoManager* um)
{
	if(um != NULL)
	{
		um->RegisterChange(mOwner, (Object**)& (itemToAdd->prev));
		um->RegisterChange(mOwner, (Object**)& (itemToAdd->next));
		if(listStart == addBeforeThis)um->RegisterChange(mOwner, (Object**)&listStart);
		um->RegisterChange(mOwner, (Object**)& (addBeforeThis->prev));
		if(addBeforeThis->prev != NULL)um->RegisterChange(mOwner, (Object**)& (addBeforeThis->prev->next));
		um->RegisterChange(mOwner, &count);
	}

	//Listenanfang anpassen
	if(listStart == addBeforeThis)listStart = itemToAdd;

	LListElement* addAfterThis = addBeforeThis->prev;

	//ItemToAdd anpassen
	itemToAdd->prev = addAfterThis;
	itemToAdd->next = addBeforeThis;

	//Vorgänger anpassen
	if(addAfterThis != NULL)addAfterThis->next = itemToAdd;

	//Nachfolger anpassen
	addBeforeThis->prev = itemToAdd;

	//Zähler anpassen
	count++;
}


void LinkedList::Remove(LListElement* element, UndoManager* um)
{
	LListElement* prev = element->prev;
	LListElement* next = element->next;

	if(um != NULL)
	{
		if(prev != NULL)um->RegisterChange(mOwner, (Object**) & (prev->next));
		if(next != NULL)um->RegisterChange(mOwner, (Object**) & (next->prev));
		if(listStart == element)um->RegisterChange(mOwner, (Object**) &listStart);
		if(listEnd == element)um->RegisterChange(mOwner, (Object**) &listEnd);
		um->RegisterChange(mOwner, reinterpret_cast<Object**>(&element->prev));
		um->RegisterChange(mOwner, (Object**) & (element->next));
		um->RegisterChange(mOwner, &count);
		um->RegisterRelease(element);
	}

	if(prev != NULL)prev->next = next;
	if(next != NULL)next->prev = prev;

	if(listStart == element)
	{
		if(listStart->next != NULL)listStart = listStart->next;
		else listStart = NULL;
	}

	if(listEnd == element)
	{
		if(listEnd->prev != NULL)listEnd = listEnd->prev;
		else listEnd = NULL;
	}

	element->prev = NULL;
	element->next = NULL;
	element->Release();
	count--;
}


void LinkedList::Remove(const Object* data, UndoManager* um)
{
	Rewind();
	while(HasNext())
	{
		LListElement* elem = NextElement();
		if(elem->data == data)
		{
			Remove(elem, um);
		}
	}
}

uint32 LinkedList::Length() const
{
	return count;
}

void LinkedList::SwapData(Object* data1, Object* data2, UndoManager* um)
{
	LListElement* elem1 = NULL;
	LListElement* elem2 = NULL;

	Rewind();
	while(HasNext())
	{
		LListElement* elem = NextElement();
		if(elem->data == data1)elem1 = elem;
		if(elem->data == data2)elem2 = elem;
		if(elem1 != NULL && elem2 != NULL)break;
	}

	if(elem1 != NULL && elem2 != NULL)
	{
		if(um != NULL)
		{
			if(um != NULL)um->RegisterChange(mOwner, (Object**) & (elem1->data));
			if(um != NULL)um->RegisterChange(mOwner, (Object**) & (elem2->data));
			elem1->data = data2;
			elem2->data = data1;
		}
	}
}

LinkedListIterator LinkedList::GetIterator() const
{
	return LinkedListIterator(this);
}

LinkedListIterator::LinkedListIterator(const LinkedList* list)
{
	if(list == NULL)
	{
		listStart = NULL;
		listEnd = NULL;
		current = NULL;
		count = 0;
		return;
	}
	listStart = list->listStart;
	listEnd = list->listEnd;
	current = listStart;
	count = list->count;
}

LinkedListIterator::LinkedListIterator(const LinkedListIterator &other)
{
	listStart = other.listStart;
	listEnd = other.listEnd;
	current = other.current;
	count = other.count;
}


bool LinkedListIterator::HasNext()
{
	return current != NULL;
}

Object* LinkedListIterator::Next()
{
	Object* ret = current->data;
	current = current->next;
	return ret;
}

Object* LinkedListIterator::Seek()
{
	return current->data;
}

LinkedListIterator::~LinkedListIterator()
{

}

namespace jm
{
	LinkedListIterator& LinkedListIterator::operator=(const LinkedListIterator &other)
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
