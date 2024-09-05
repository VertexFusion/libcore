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

#include "Precompiled.hpp"

using namespace jm;

Hashtable::Hashtable(): Object()
{
   mArrLength = 7;
   mData = new HashtableEntry*[mArrLength]; // Array for data
   for(Integer a = 0; a < mArrLength; a++)mData[a] = nullptr;
   mDataLength = 0;
   mLoadfactor = 0.75f;
   mThreshold = Double::round(mArrLength * mLoadfactor);
}

Hashtable::~Hashtable()
{
   clear();
   delete[] mData;
   mDataLength = 0;
   mArrLength = 0;
}

void* Hashtable::put(String key, void* value)
{
   // Make sure that no entry already exists in the hash table.
   Integer hash = key.hashCode();
   Integer index = (hash & 0x7FFFFFFF) % mArrLength;
   for(HashtableEntry* e = mData[index] ; e != nullptr ; e = e->next)
   {
      if((e->hash == hash) && e->key.equals(key))
      {
         void* old = e->value;
         e->value = value;
         return old;
      }
   }

   // Increase table when threshold value is reached.
   if(mDataLength >= mThreshold)
   {
      rehash();
      index = (hash & 0x7FFFFFFF) % mArrLength;
   }

   // Create new entry.
   HashtableEntry* e = mData[index] ;
   HashtableEntry* n = new HashtableEntry();
   n->hash = hash;
   n->key = key;
   n->value = value;
   n->next = e;
   mData[index] = n;
   mDataLength++;
   return nullptr;
}

void* Hashtable::get(const String& key) const
{
   Integer hash = key.constHashCode();

   Integer index = (hash & 0x7FFFFFFF) % mArrLength;
   for(HashtableEntry* e = mData[index] ; e != nullptr ; e = e->next)
   {
      if((e->hash == hash) && e->key.equals(key))
      {
         return e->value;
      }
   }

   return nullptr;
}

void* Hashtable::remove(const String& key)
{
   Integer hash = key.constHashCode();
   Integer index = (hash & 0x7FFFFFFF) % mArrLength;

   HashtableEntry* prev = nullptr;
   HashtableEntry* e = mData[index];
   while(e != nullptr)
   {
      if((e->hash == hash) && e->key.equals(key))
      {
         // Delete element in the linked list
         if(prev != nullptr)
         {
            prev->next = e->next;
         }
         else
         {
            mData[index] = e->next;
         }
         mDataLength--;

         // Return value
         void* oldValue = e->value;
         delete e;
         return oldValue;
      }
      prev = e;
      e = e->next;
   }

   // Nothing found
   return nullptr;
}

void Hashtable::clear()
{
   for(Integer index = 0; index < mArrLength; index++)
   {
      HashtableEntry* e = mData[index];
      while(e != nullptr)
      {
         HashtableEntry* n = e->next;
         delete e;
         e = n;
      }
      mData[index] = nullptr;
   }
   mDataLength = 0;
}

Integer Hashtable::size() const
{
   return mDataLength;
}

void Hashtable::rehash()
{
   int64 oldLength = mArrLength;
   HashtableEntry** oldData = mData;

   int64 newLength = oldLength * 2 + 1;

   HashtableEntry** newData = new HashtableEntry*[newLength];

   for(int64 a = 0; a < newLength; a++)newData[a] = nullptr;

   mArrLength = newLength;
   mThreshold = std::ceil(newLength * mLoadfactor);

   for(int64 a = 0 ; a < oldLength ; a++)
   {
      HashtableEntry* old = oldData[a];

      while(old != nullptr)
      {
         HashtableEntry* next = old->next;

         int64 index = (old->hash & 0x7FFFFFFF) % mArrLength;
         old->next = newData[index];
         newData[index] = old;

         old = next;
      }
   }
   delete[] mData;
   mData = newData;
}

Iterator* Hashtable::keys()
{
   return new HashtableIterator(this, true);
}

Iterator* Hashtable::values()
{
   return new HashtableIterator(this, false);
}


/*
 HashtableIterator
*/

Hashtable::HashtableIterator::HashtableIterator(Hashtable* _table, Bool _retKey): Iterator()
{
   table = _table;
   retKey = _retKey;
   index = 0;
   entry = nullptr;
   last = nullptr;
}

bool Hashtable::HashtableIterator::hasNext()
{
   while(entry == nullptr && index < table->mArrLength)
   {
      entry = table->mData[index++];
   }
   return entry != nullptr;
}

Object* Hashtable::HashtableIterator::next()
{
   while(entry == nullptr && index < table->mArrLength)
   {
      entry = table->mData[index++];
   }

   if(entry != nullptr)
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
   value = nullptr;
   next = nullptr;
}

Hashtable::HashtableEntry::~HashtableEntry()
{
   hash = 0;
   value = nullptr;
   next = nullptr;
}



