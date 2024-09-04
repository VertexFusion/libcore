////////////////////////////////////////////////////////////////////////////////////////////////////
// Name:        Hashtable.h
// Library:     Jameo Core Library
// Purpose:     Hashtable
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

#ifndef jm_Hashtable_h
#define jm_Hashtable_h

#include "String.h"
#include "Iterator.h"

namespace jm
{


   /*!
    \brief A hash table is an instrument used to sort data. A string serves as the access key, whose
    hash value ensures fast access. This class provides all the necessary methods to be able to work
    comfortably with a hash table.
    \ingroup core
    */
   class DllExport Hashtable: public Object
   {

      public:

          /*!
           \brief Default constructor for the Hashtable class.
           */
         Hashtable();

          /*!
           \brief Destructor for the Hashtable class.
           */
         ~Hashtable();


          /*!
           \brief This method inserts a new element into the hash table.
           \param key The key to which the object will be associated.
           \param value The pointer to the object to be inserted.
           \return If an old object is replaced, it is returned.
           */
         void* put(String key, void* value);

          /*!
           \brief This method returns the object associated with the specified key.
           \param key The key to which the object is associated.
           \return A pointer to the object associated with the key, or nullptr if the object is not
           present in the hashtable.
           */
         void* get(const String& key) const;

          /*!
           \brief This method removes the object associated with the specified key.
           \param key The key to which the object is associated.
           \return A pointer to the object that was removed, or nullptr if the object was not found.
           */
         void* remove(const String& key);

         /*!
          \brief Returns the number of entries in this hash table.
          */
         Integer size() const;

          /*!
           \brief This method returns true if the hashtable is empty.
           \return true if the hashtable is empty, false otherwise.
           */
         bool isEmpty() const;

          /*!
           \brief This method returns true if an object is associated with the specified key.
           \param key The key for which the object is being checked.
           \return true if an object is associated with the key, false otherwise.
           */
         bool containsKey(const String& key) const;

          /*!
           \brief This method returns true if the hashtable contains an object associated with the specified value.
           \param value The value to search for.
           \return true if an object is associated with the value, false otherwise.
           */
         bool containsValue(void* value) const;

          /*!
           \brief This method returns an object of the "Iterator" class that iterates through
           the keys of this table.
           \return An Iterator object that iterates through the keys of this table.
           */
         Iterator* keys();

          /*!
           \brief This method returns an object of the "Iterator" class that iterates through
           the values of this table.
           \return An Iterator object that iterates through the values of this table.
           */
         Iterator* values();

          /*!
           \brief This method removes all elements from the Hashtable.
           */
         void clear();

      protected:

          /*!
           \brief This method increases the capacity of the Hashtable.
           */
         void rehash();

      private:

          /*!
           \brief This private typedef simplifies the sorting of data into the data array.
           It is a linked list for performance reasons.
           */
         struct HashtableEntry
         {
            //! The hash value of the entry.
            Integer hash;

            //! The key associated with the entry.
            String key;

            //! The value associated with the entry.
            void* value;

            //! Pointer to the next entry in the linked list.
            HashtableEntry* next;
            HashtableEntry();
            ~HashtableEntry();
         };

          //! \brief This field stores the data of the Hashtable.
         HashtableEntry** mData;

          //! \brief This variable stores the actual length of the storage array.
         int64 mArrLength;

          //! \brief This variable stores the number of entries in the hashtable.
         int64 mDataLength;

          //! \brief This threshold defines the number of entries at which the storage array for 
          //! the data should be resized. It is the absolute number of entries at which a storage
          //! reorganization is performed.
         int64 mThreshold;

          //! This variable stores the load factor threshold at which the Hashtable should be rehashed.
          //! A value of 0 means 0%, while a value of 1 means 100%.
         double mLoadfactor;

          /*!
           \brief This subclass implements an iterator that allows iterating through the hashtable.
           */
         class HashtableIterator: public Iterator
         {
            public:

               /*!
                \brief Constructor for the HashtableIterator class.
                \param table A pointer to the Hashtable object being iterated.
                \patam retKey A boolean value indicating whether the iterator should return keys or values.
                */
               HashtableIterator(Hashtable* table, Bool retKey);

               /*!
                \copydoc Iterator::hasNext()
                */
               bool hasNext() override;
               
               /*!
                \copydoc Iterator::next()
                */
               Object* next() override;

            private:
               //! retKey A boolean value indicating whether the iterator should return keys or values.
               Bool retKey;
              
               //!param table A pointer to the Hashtable object being iterated.
               Hashtable* table;
               HashtableEntry* entry;
               HashtableEntry* last;
               int64 index;
         };

   };

}


#endif
