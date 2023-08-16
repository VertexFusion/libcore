//
//  Hashtable.cpp
//  jameo
//
//  Created by Uwe Runtemund on 24.01.13.
//  Copyright (c) 2013 Jameo Software. All rights reserved.
//

#include "Precompiled.h"

using namespace jm;

Hashtable::Hashtable(): Object()
{
	mArrLength = 7;
	mData = new HashtableEntry*[mArrLength];//Array mit den Daten
	for(uint32 a = 0; a < mArrLength; a++)mData[a] = NULL;
	mDataLength = 0;
	mLoadfactor = 0.75f;
	mThreshold = (uint32)(mArrLength * mLoadfactor);
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
	int32 hash = key.HashCode();
	uint32 index = (hash & 0x7FFFFFFF) % mArrLength;
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
	int32 hash = key.HashCode();

	uint32 index = (hash & 0x7FFFFFFF) % mArrLength;
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
	int32 hash = key.HashCode();
	uint32 index = (hash & 0x7FFFFFFF) % mArrLength;

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
	for(uint32 index = 0; index < mArrLength; index++)
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

uint32 Hashtable::Size() const
{
	return mDataLength;
}

void Hashtable::Rehash()
{
	uint32 oldLength = mArrLength;
	HashtableEntry** oldData = mData;

	uint32 newLength = oldLength * 2 + 1;

	HashtableEntry** newData = new HashtableEntry*[newLength];

	for(uint32 a = 0; a < newLength; a++)newData[a] = NULL;

	mArrLength = newLength;
	mThreshold = (uint32) std::ceil(newLength * mLoadfactor);

	for(uint32 a = 0 ; a < oldLength ; a++)
	{
		HashtableEntry* old = oldData[a];

		while(old != NULL)
		{
			HashtableEntry* next = old->next;

			uint32 index = (old->hash & 0x7FFFFFFF) % mArrLength;
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

Hashtable::HashtableIterator::HashtableIterator(Hashtable* _table, bool _retKey): Iterator()
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



