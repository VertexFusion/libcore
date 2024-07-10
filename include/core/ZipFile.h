////////////////////////////////////////////////////////////////////////////////////////////////////
// Name:        ZipFile.h
// Library:     Jameo Core Library
// Purpose:     Read & Write ZIP-Files
//
// Author:      Uwe Runtemund (2017-today)
// Modified by:
// Created:     13.08.2017
//
// Copyright:   (c) 2017 Jameo Software, Germany. https://jameo.de
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

#ifndef jm_ZipFile_h
#define jm_ZipFile_h

#include "File.h"
#include "LinkedList.h"

namespace jm
{

   class DllExport ZipEntry: public Object
   {
      public:

         /*!
          \brief Constructor
          */
         ZipEntry(const String &name);

         /*!
          \brief Returns the name of the entry.
          */
         String name()const;

         /*!
          \brief set the size of the uncompressed entry.
          */
         void setUncompressedSize(uint32 size);

         /*!
          \brief Returns the size of the uncompressed entry.
          */
         uint32 uncompressedSize()const;

         /*!
          \brief Returns true, if the entry is a directory. An entry is recognized as
          a directory, if the last character of the name is '/'.
          */
         bool isDirectory()const;

      private:

         String mName;
         String mExtra;
         String mComment;
         uint32 mUncompressedSize;
         uint32 mCompressedSize;
         uint32 mHeaderOffset;
         uint32 mCRC;
         uint32 mDataOffset; // 0-based offset in file

         friend class ZipFile;
         friend class ZipOutputFile;
   };

   /*!
    \brief Diese Klasse repräsentiert eine ZIP-Datei zum Einlesen der Zip-Daten.
    */
   class DllExport ZipFile: public Object
   {

      public:

         /*!
          \brief Konstruktor
          */
         ZipFile(File* file);

         /*!
          \brief Öffnet die Datei zum Lesen
          */
         void open();

         /*!
          \brief Schließt die Datei
          */
         void close();

         /*!
          \brief Gibt den Kommentar der ZIP-Datei zurück, oder leeren String, wenn kein Kommentar
          existiert.
          */
         String comment();

         /*!
          \brief Gibt den Zip-Eintrag zurück, wenn er existiert, oder NULL, wenn er nicht
          existiert.
          */
         ZipEntry* entry(const String &name);

         /*!
          \brief Gibt einen Iterator über die Zipeinträge zurück
          */
         LinkedListIterator entryIterator();

         /*!
          \brief Gibt die Anzahl der Zipeinträge zurück.
          */
         uint32 entryCount() const;

         /*!
          \brief Gibt den Stream mit den unkomprimierten Daten des Eintrages zurück. Der Aufrufer
          dieser Methode übernimmt den Stream und muss ihn selbst aufräumen. Der Stream ist nur
          geeignet die Daten einer ZIP-Datei zu lesen. In den Stream kann nicht geschrieben werden.
          */
         Stream* stream(const ZipEntry* entry);

      private:

         /*!
          \brief Die Datei.
          */
         File* mFile;

         /*!
          \brief Die Einträge
          */
         LinkedList mEntries;

   };


   /*!
   \brief Diese Klasse repräsentiert eine ZIP-Datei zum Schreiben der Zip-Daten.
   */
   class DllExport ZipOutputFile: public Object
   {

      public:

         /*!
         \brief Konstruktor
         */
         ZipOutputFile(File* file);

         /*!
         \brief Öffnet die Datei zum Schreiben
         */
         void open();

         /*!
         \brief Schließt die Datei
         */
         void close();

         /*!
         \brief Schließt den aktuellen Eintrag und bereitet die Datei auf das Schreiben des nächsten
         Eintrages vor
         */
         void closeEntry();

         /*!
         \brief Beginnt mit dem Schreiben eines neuen ZIP-Eintrags. Der Stream wartet nun an
         korrekter Position auf Daten
         */
         void putNextEntry(ZipEntry* entry);

         /*!
         \brief Gibt den Stream für das Schreiben der Daten zurück.
         */
         void write(uint8* data, Integer offset, Integer length);

         /*!
         \brief Schreibt den Inhalt der Datei in den Stream
         */
         void writeAndClose(File* file);


      private:

         /*!
         \brief Die ZIP-Datei.
         */
         File* mFile;

         /*!
         \brief Temporäre Datei für UNkomprimierte Daten
         */
         File* mTemp;

         /*!
          \brief Die Einträge
          */
         LinkedList mEntries;

   };

}


#endif
