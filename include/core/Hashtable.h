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
          \brief Standardkonstruktor für die Hashtabelle
          */
         Hashtable();

         /*!
          \brief Standarddestruktor für die Hashtabelle
          */
         ~Hashtable();


         /*!
          \brief Diese Methode fügt ein neues Element in die Hashtabelle ein.
          \param key Der Schlüssel, zu dem das Objekt zugeordnet wird
          \param value Der Pointer auf das Objekt, welches hier eingeordnet werden soll.
          \return Wenn ein altes Objekt dadurch ersetzt wird, wird dieses zurückgegeben.
          */
         void* Put(String key, void* value);

         /*!
          \brief Diese Methode gibt das Objekt zurück, welches zu dem gesuchten Key zugeordnet
          ist.
          \param key Der Schlüssel, zu dem das Objekt zugeordnet wird
          \return Den Pointer auf das Objekt, welches gesucht wird, oder NULL, wenn das Objekt nicht
          in der Hashtabelle vorhanden ist.
          */
         void* Get(const String &key) const;

         /*!
          \brief Diese Methode entfernt das Objekt, welches zu dem gesuchten Key zugeordnet ist.
          \param key Der Schlüssel, zu dem das Objekt zugeordnet wird
          \return Den Pointer auf das Objekt, welches entfernt wurde.
          */
         void* Remove(String key);

         /*!
          \brief Returns the number of entries in this hash table.
          */
         Integer Size() const;

         /*!
          \brief Diese Methode gibt "wahr" zurück, wenn die Hashtabelle leer ist.
          */
         bool IsEmpty() const;

         /*!
          \brief Diese Methode gibt "wahr" zurück, wenn zu dem Schlüssel ein Objekt zugeordnet
          ist.
          \param key Der Schlüssel, zu dem das Objekt zugeordnet wird
          */
         bool ContainsKey(const String &key) const;

         /*!
          \brief Diese Methode gibt "wahr" zurück, wenn zu dem Schlüssel ein Objekt zugeordnet
          ist.
          \param value Dert Wert,nach dem gesucht wird
          */
         bool ContainsValue(void* value) const;

         /*!
          \brief Diese Methode gibt ein Objekt der Klasse "Iterator" zurück, welches sich durch
          die Schlüssel dieser Tabelle iteriert.
          */
         Iterator* Keys();

         /*!
          \brief Diese Methode gibt ein Objekt der Klasse "Iterator" zurück, welches sich durch
         die Werte dieser Tabelle iteriert.
          */
         Iterator* Values();

         /*!
          \brief Diese Methode entfernt alle Elemente aus der Hashtable
          */
         void Clear();

      protected:

         /*!
         \brief Diese Methode erhöhte die Kapazität der Hashtabelle
         */
         void Rehash();

      private:

         /*!
          \brief Diese pricate Typendeklaration erleichtert das Einsortierend der Daten in das
          Datenarray. Es handelt sich aus Geschwindigkeitsgründen um eine Verkettete Liste
          */
         struct HashtableEntry
         {
            Integer hash;
            String key;
            void* value;
            HashtableEntry* next;//Verkettete liste :-)
            HashtableEntry();//Konstruktor
            ~HashtableEntry();//Destruktor
         };

         /*!
          \brief Diese Feld speichert die Daten der Hashtabelle
          */
         HashtableEntry** mData;

         /*!
          \brief Diese Variable speichert die tatsächliche Länge des Speicherarrays.
          */
         Integer mArrLength;

         /*!
          \brief Diese Variable speichert die Anzahl der Einträge in der Hashtabelle.
          */
         Integer mDataLength;

         /*!
          \brief Dieser Schwellwert definiert, ab welchen "Füllstand" das Speicherarray für die
          Daten vergrößert werden soll. Es ist die absolute Zahl an Einträgen, ab der eine
          Speicherneusortierung vorgenommen wird.
          */
         Integer mThreshold;

         /*!
          \brief Diese Variable speichert den prozentualen Schwellwert, ab dem neu sortiert wird.
          0 bedeutet 0%, 1 bedeutet 100%
          */
         Double mLoadfactor;

         /*!
          \brief Diese Unterklasse implementiert einen Iterator, mit dem durch die Hashtabelle
          iteriert werden kann.
          */
         class HashtableIterator: public Iterator
         {
            private:
               Bool retKey;
               Hashtable* table;
               HashtableEntry* entry;
               HashtableEntry* last;
               Integer index;
            public:
               HashtableIterator(Hashtable* table, Bool retKey);
               bool HasNext();
               Object* Next();
         };

   };

}


#endif
