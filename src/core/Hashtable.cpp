////////////////////////////////////////////////////////////////////////////////////////////////////
// Name:        Hashtable.cpp
// Library:     Jameo Core Library
// Purpose:     Implementation of a hashtable
//
// Author:      Uwe Runtemund (2013-today)
// Modified by:
// Created:     24.01.2013
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

#include "Precompiled.h"

using namespace jm;

Hashtable::Hashtable(): Object()
{
	mArrLength = 7;
	mData = new HashtableEntry*[mArrLength];//Array mit den Daten
	for(Integer a = 0; a < mArrLength; a++)mData[a] = NULL;
	mDataLength = 0;
	mLoadfactor = 0.75f;
	mThreshold = (mArrLength * mLoadfactor).Round();
}

Hashtable::~Hashtable()
{
	Clear();
	delete[] mData;
	mDataLength = 0;
	mArrLength = 0;
}

void* Hashtable::Put(String key, void* value)
{
	// Stelle sicher, dass kein Eintrag bereits in der Hashtabelle vorhanden ist.
	Integer hash = key.HashCode();
	Integer index = (hash & 0x7FFFFFFF) % mArrLength;
	for(HashtableEntry* e = mData[index] ; e != NULL ; e = e->next)
	{
		if((e->hash == hash) && e->key.Equals(key))
		{
			void* old = e->value;
			e->value = value;
			return old;
		}
	}

	//Tabelle verößern, wenn Schwellwert erreicht wird.
	if(mDataLength >= mThreshold)
	{
		Rehash();
		index = (hash & 0x7FFFFFFF) % mArrLength;
	}

	// Neuen Eintrag anlegen.
	HashtableEntry* e = mData[index] ;
	HashtableEntry* n = new HashtableEntry();
	n->hash = hash;
	n->key = key;
	n->value = value;
	n->next = e;
	mData[index] = n;
	mDataLength++;
	return NULL;
}

void* Hashtable::Get(String key) const
{
	Integer hash = key.HashCode();

	Integer index = (hash & 0x7FFFFFFF) % mArrLength;
	for(HashtableEntry* e = mData[index] ; e != NULL ; e = e->next)
	{
		if((e->hash == hash) && e->key.Equals(key))
		{
			return e->value;
		}
	}

	return NULL;
}

void* Hashtable::Remove(String key)
{
	Integer hash = key.HashCode();
	Integer index = (hash & 0x7FFFFFFF) % mArrLength;

	HashtableEntry* prev = NULL;
	HashtableEntry* e = mData[index];
	while(e != NULL)
	{
		if((e->hash == hash) && e->key.Equals(key))
		{
			//Lösche Element in der Verkettenliste
			if(prev != NULL)
			{
				prev->next = e->next;
			}
			else
			{
				mData[index] = e->next;
			}
			mDataLength--;

			//Wert zurückgeben
			void* oldValue = e->value;
			delete e;
			return oldValue;
		}
		prev = e;
		e = e->next;
	}

	//Nichts gefunden
	return NULL;
}

void Hashtable::Clear()
{
	for(Integer index = 0; index < mArrLength; index++)
	{
		HashtableEntry* e = mData[index];
		while(e != NULL)
		{
			HashtableEntry* n = e->next;
			delete e;
			e = n;
		}
		mData[index] = NULL;
	}
	mDataLength = 0;
}

Integer Hashtable::Size() const
{
	return mDataLength;
}

void Hashtable::Rehash()
{
	Integer oldLength = mArrLength;
	HashtableEntry** oldData = mData;

	Integer newLength = oldLength * 2 + 1;

	HashtableEntry** newData = new HashtableEntry*[newLength];

	for(Integer a = 0; a < newLength; a++)newData[a] = NULL;

	mArrLength = newLength;
	mThreshold = (newLength * mLoadfactor).Ceil();

	for(Integer a = 0 ; a < oldLength ; a++)
	{
		HashtableEntry* old = oldData[a];

		while(old != NULL)
		{
			HashtableEntry* next = old->next;

			Integer index = (old->hash & 0x7FFFFFFF) % mArrLength;
			old->next = newData[index];
			newData[index] = old;

			old = next;
		}
	}
	delete[] mData;
	mData = newData;
}

Iterator* Hashtable::Keys()
{
	return new HashtableIterator(this, true);
}

Iterator* Hashtable::Values()
{
	return new HashtableIterator(this, false);
}


/*
 HASHTABLITERATOR
*/

Hashtable::HashtableIterator::HashtableIterator(Hashtable* _table, Bool _retKey): Iterator()
{
	table = _table;
	retKey = _retKey;
	index = 0;
	entry = NULL;
	last = NULL;
}

bool Hashtable::HashtableIterator::HasNext()
{
	while(entry == NULL && index < table->mArrLength)
	{
		entry = table->mData[index++];
	}
	return entry != NULL;
}

Object* Hashtable::HashtableIterator::Next()
{
	while(entry == NULL && index < table->mArrLength)
	{
		entry = table->mData[index++];
	}

	if(entry != NULL)
	{
		last = entry;
		entry = entry->next;
		return reinterpret_cast<Object*>((retKey) ? & (last->key) : last->value);
	}
	else throw new Exception("No such element in hashtable iterator.");

}

/*
 HASHTABLE_ENTRY
 */

Hashtable::HashtableEntry::HashtableEntry()
{
	hash = 0;
	value = NULL;
	next = NULL;
}

Hashtable::HashtableEntry::~HashtableEntry()
{
	hash = 0;
	value = NULL;
	next = NULL;
}



