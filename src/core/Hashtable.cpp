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

#include "PrecompiledCore.hpp"

using namespace jm;

Hashtable::Hashtable() noexcept: Object(),
   mArrLength(7),
   mDataLength(0),
   mLoadfactor(0.75f),
   mThreshold(5)
{
   mData = new HashtableEntry*[mArrLength]; // Array for data
   for(size_t i = 0; i < mArrLength; i++)
   {
      mData[i] = nullptr;  // Explicitly set each pointer to nullptr
   }
}

Hashtable::~Hashtable() noexcept
{
   clear();
   delete[] mData;
   mDataLength = 0;
   mArrLength = 0;
}

void* Hashtable::put(String key, void* value) noexcept
{
   // Make sure that no entry already exists in the hash table.
   int64 hash = key.hashCode();
   int64 index = (hash & 0x7FFFFFFF) % mArrLength;
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

void* Hashtable::get(const String& key) const noexcept
{
   int64 hash = key.constHashCode();

   int64 index = (hash & 0x7FFFFFFF) % mArrLength;
   for(HashtableEntry* e = mData[index] ; e != nullptr ; e = e->next)
   {
      if((e->hash == hash) && e->key.equals(key))
      {
         return e->value;
      }
   }

   return nullptr;
}

bool Hashtable::containsKey(const String& key) const noexcept
{
   return get(key) != nullptr;
}

void* Hashtable::remove(const String& key) noexcept
{
   int64 hash = key.constHashCode();
   int64 index = (hash & 0x7FFFFFFF) % mArrLength;

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

void Hashtable::clear() noexcept
{
   for(size_t index = 0; index < mArrLength; index++)
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

size_t Hashtable::size() const noexcept
{
   return mDataLength;
}

void Hashtable::rehash() noexcept
{
   size_t oldLength = mArrLength;
   HashtableEntry** oldData = mData;

   size_t newLength = oldLength * 2 + 1;

   HashtableEntry** newData = new HashtableEntry*[newLength];

   for(size_t a = 0; a < newLength; a++)newData[a] = nullptr;

   mArrLength = newLength;
   mThreshold = static_cast<size_t>(std::ceil(static_cast<double>(newLength) * mLoadfactor));

   for(size_t a = 0 ; a < oldLength ; a++)
   {
      HashtableEntry* old = oldData[a];

      while(old != nullptr)
      {
         HashtableEntry* next = old->next;

         size_t index = (old->hash & 0x7FFFFFFF) % mArrLength;
         old->next = newData[index];
         newData[index] = old;

         old = next;
      }
   }
   delete[] mData;
   mData = newData;
}

Iterator* Hashtable::keys() noexcept
{
   return new HashtableIterator(this, true);
}

Iterator* Hashtable::values() noexcept
{
   return new HashtableIterator(this, false);
}


/*
 HashtableIterator
*/

Hashtable::HashtableIterator::HashtableIterator(Hashtable* _table, bool _retKey) noexcept: Iterator(),
   retKey(_retKey),
   table(_table),
   entry(nullptr),
   last(nullptr),
   index(0)
{}

bool Hashtable::HashtableIterator::hasNext() noexcept
{
   while(entry == nullptr && index < table->mArrLength)
   {
      entry = table->mData[index++];
   }
   return entry != nullptr;
}

Object* Hashtable::HashtableIterator::next() noexcept
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
   else return nullptr;
}

/*
 HASHTABLE_ENTRY
 */

Hashtable::HashtableEntry::HashtableEntry() noexcept:
   hash(0),
   key(jm::kEmptyString),
   value(nullptr),
   next(nullptr)
{}

Hashtable::HashtableEntry::~HashtableEntry() noexcept
{
   hash = 0;
   value = nullptr;
   next = nullptr;
}



