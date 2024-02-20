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
          \brief Konstruktor
          */
         ZipEntry(const String &name);

         /*!
          \brief Gibt den Namen des Eintrages zurück
          */
         String GetName()const;

         /*!
          \brief Legt die Größe des unkomprimierten Eintrages fest
          */
         void SetUncompressedSize(uint32 size);

         /*!
          \brief Gibt die Größe des unkomprimierten Eintrages zurück
          */
         uint32 GetUncompressedSize()const;

         /*!
          \brief Gibt den Status zurück, ob der Eintrag ein Verzeichnis ist. Ein Verzeichnis
          ist dadurch definiert, dass das letzte Zeichen im Namen ein "/" ist.
          */
         bool IsDirectory()const;

      private:

         /*! \brief Der Name */
         String mName;

         /*! \brief Extrafeld */
         String mExtra;

         /*! \brief Kommentar */
         String mComment;

         /*! \brief Die unkomprimierte Größe */
         uint32 mUncompressedSize;

         /*! \brief Die komprimierte Größe */
         uint32 mCompressedSize;

         /*! \brief Offset des Local Headers */
         uint32 mHeaderOffset;

         /*! \brief Prüfsumme */
         uint32 mCRC;

         /*! \brieg 0-basierter Offset in Datei */
         uint32 mDataOffset;

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
         void Open();

         /*!
          \brief Schließt die Datei
          */
         void Close();

         /*!
          \brief Gibt den Kommentar der ZIP-Datei zurück, oder leeren String, wenn kein Kommentar
          existiert.
          */
         String GetComment();

         /*!
          \brief Gibt den Zip-Eintrag zurück, wenn er existiert, oder NULL, wenn er nicht
          existiert.
          */
         ZipEntry* GetEntry(const String &name);

         /*!
          \brief Gibt einen Iterator über die Zipeinträge zurück
          */
         LinkedListIterator GetEntryIterator();

         /*!
          \brief Gibt die Anzahl der Zipeinträge zurück.
          */
         uint32 GetEntryCount() const;

         /*!
          \brief Gibt den Stream mit den unkomprimierten Daten des Eintrages zurück. Der Aufrufer
          dieser Methode übernimmt den Stream und muss ihn selbst aufräumen. Der Stream ist nur
          geeignet die Daten einer ZIP-Datei zu lesen. In den Stream kann nicht geschrieben werden.
          */
         Stream* GetStream(const ZipEntry* entry);

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
         void Open();

         /*!
         \brief Schließt die Datei
         */
         void Close();

         /*!
         \brief Schließt den aktuellen Eintrag und bereitet die Datei auf das Schreiben des nächsten
         Eintrages vor
         */
         void CloseEntry();

         /*!
         \brief Beginnt mit dem Schreiben eines neuen ZIP-Eintrags. Der Stream wartet nun an
         korrekter Position auf Daten
         */
         void PutNextEntry(ZipEntry* entry);

         /*!
         \brief Gibt den Stream für das Schreiben der Daten zurück.
         */
         void Write(uint8* data, Integer offset, Integer length);

         /*!
         \brief Schreibt den Inhalt der Datei in den Stream
         */
         void WriteAndClose(File* file);


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
