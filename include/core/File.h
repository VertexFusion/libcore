////////////////////////////////////////////////////////////////////////////////////////////////////
// Name:        File.h
// Library:     Jameo Core Library
// Purpose:     File
//
// Author:      Uwe Runtemund (2013-today)
// Modified by:
// Created:     12.05.2013
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

#ifndef jm_File_h
#define jm_File_h

#include "String.h"
#include "Array.h"
#include "ByteArray.h"
#include "Object.h"
#include "Stream.h"
#include "Date.h"

namespace jm
{

   /*!
    \brief Dieses Feld speichert je nach Betriebssystem das Trennzeichen für Verzeichnisse
    */
   #ifdef __APPLE__//macOS, iOS
   const Char DIR_SEP = Char('/');
   #elif defined __linux__ //Linux
   const Char DIR_SEP = Char('/');
   #elif defined _WIN32//Windows
   const Char DIR_SEP = Char('\\');
   #endif

   /*!
    \brief  This class is a representation of file or directory paths. In addition, data can be read
    from and written to the hard disk.
    \ingroup core
    */
   class DllExport File: public Stream, public Comparable<File>
   {
      public:

         /*!
          \brief Standardkonstruktor erzeugt Namenlose Datei
          */
         File();

         /*!
          \brief Konstruktor
          \param pathname Der Pfadname der Datei.
          */
         File(const String &pathname);

         /*!
          \brief Konstruktor
          \param parent Der Pfadname der "Vaterdatei".
          \param child Der Pfadname der "Kinddatei"
          */
         File(String parent,
              String child);

         /*!
          \brief Konstruktor
          \param parent Das ShxFile-Objekt der "Vaterdatei".
          \param child Der Pfadname der "Kinddatei"
          */
         File(const File &parent,
              String child);

         /*!
          \brief Kopierkonstrutor
          */
         File(const File &other);

         /*!
          \brief Destructor
          */
         ~File();


         /*!
          \brief Diese Methode prüft, ob die Datei ausführbar ist.
          */
         bool CanExecute() const;

         /*!
          \brief Diese Methode prüft, ob die Datei lesbar ist.
          */
         bool CanRead() const;

         /*!
          \brief Diese Methode prüft, ob die Datei beschreibar ist.
          */
         bool CanWrite() const;

         /*!
          \brief Diese Methode erzeugt eine neue leere Datei, aber nur wenn die Datei nicht
          existiert.
          \return Gibt wahr zurück, wenn eine neue Datei angelegt wurde.
          */
         bool CreateNewFile();

         /*!
          \brief Diese Methode erzeugt ein Verzeichnis mit diesem Dateinamen.
          \return gibt wahr zurück, wenn das Verzeichnis angelegt wurde,
          */
         bool MakeDirectory();

         /*!
          \brief Diese Methode prüft, ob die Datei existiert
          */
         bool Exists() const;

         /*!
          \brief Diese Methode löscht die Datei (endgültig). Ein Verzeichnis nur, wenn es leer
          ist.
          */
         bool Delete();

         /*!
          \brief Diese Methode verschiebt die Datei in den System-Papierkorb.
          */
         bool MoveToTrash();

         /*!
          \brief Benennt die Datei um
          */
         bool RenameTo(const String &newPath);

         /*!
          \brief Gibt den Namen der Datei zurück. Dies ist der reine Name ohne Pfadangabe usw.
          */
         String GetName() const;

         /*!
          \brief Gibt den Pfadnamen zu der Datei an, Also ohne den Dateinamen selbst.
          Es entspricht dem Verzeichnis, in dem diese Datei liegt.
          */
         String GetParent() const;

         /*!
          \brief Gibt den absoluten Dateinamen von der Wurzel des Dateisystems an zurück
          */
         const String& GetAbsolutePath() const;

         /*!
          \brief Gibt den vollständigen Pfad dieser Datei an. Dieser kann relativ sein, wenn er
          relativ ist,
          oder auch absolut, wenn er absolut ist.
          */
         String GetPath() const;

         /*!
          \brief Diese Methode gibt die Dateiendund der Datei zurück. Wenn die Datei keine
          Dateiendung besitzt, dann ist der Rückgabewert ein leerer String. Eine Dateiendung ist
          duch einen Punkt gekennzeichnet. Für ".tar.gz" wird nur "gz" zurückgegeben.
          */
         String GetExtension() const;

         /*!
          \brief Diese Methode prüft, ob diese Datei absolut ist
          */
         bool IsAbsolute() const;

         /*!
          \brief Diese Methode prüft, ob diese Datei ein Verzeichnis ist
          */
         bool IsDirectory() const;

         /*!
          \brief Diese Methode prüft, ob diese Datei eine gewöhnliche Datei ist
          */
         bool IsFile() const;

         /*!
          \brief Diese Methode prüft, ob diese Datei eine Verknüpfung ist
          */
         bool IsLink() const;

         /*!
          \brief Diese Methode prüft, ob diese Datei eine FIFO ist.
          */
         bool IsPipe() const;

         /*!
          \brief Diese Methode prüft, ob diese Datei versteckt ist
          */
         bool IsHidden() const;

         /*!
          \brief Methode macht eine Liste mit Allen Dateien im dem Verzeichnis.
          */
         Array<File>* ListFiles()const;

         /*!
          \brief Gibt die Größe der Datei in Bytes zurück
          */
         Integer Length() const override;

         /*!
          \brief Gibt das Datum der letzten Änderung zurück
          */
         Date LastModified() const;

         /*!
          \brief Öffnet die Datei um Lese- oder Schreiboperationen an ihr vorzunehmen
          \param mode Der Modus zum öffnen.
          */
         void Open(FileMode mode) override;

         /*!
          \brief Status, ob die Datei geöffnet ist
          */
         bool IsOpen() override;

         /*!
          \brief Schließt die Datei, wenn sie vorher geöffnet war
          */
         void Close() override;

         /*!
          \brief Liest maximal length bytes in das Array
          \discussion Bei Großen Blocken kann es sein, dass nicht alle Bytes eingelesen werden, weil
          noch auf Daten gewartet werden. In diesem Fall kann es sein, dass nur ein Teil
          zurückgegeben wird. Will man in jedem Fall alle Daten haben, muss man "ReadFully"
          aufrufen.
          \return Die tatsächlich eingelesene Menge an Bytes, oder 0 wenn keine Bytes gelesen wurden
          (EOF)
          */
         Integer Read(unsigned char* buffer,
                      Integer length) override;

         /*!
          \brief Liest maximal length bytes in das Array
          \return Die tatsächlich eingelesene Menge an Bytes, oder 0 wenn keine Bytes gelesen wurden
          (EOF)
          */
         Integer ReadFully(ByteArray& buffer, Integer length) override;



         /*!
          \brief Bewegt den Dateicursor an die gewünschte Stelle, gezählt vom Dateianfang
          (0-basierter Index)
          */
         void Seek(Integer position) override;

         /*!
          \brief Bewegt den Dateicursor an die gewünschte Stelle, gezählt von der aktuellen Position
          */
         void Move(Integer offset) override;

         /*!
          \brief Diese Methode gibt die aktuelle Cursorposition in der Datei zurück
          */
         Integer GetPosition() override;

         /*!
          \brief Schreibt einen Buffer in die Ausgabedatei
          */
         Integer Write(uint8* buffer, Integer length) override;

         /*!
          \brief Vergleichsmethode vergleicht den absoluten Dateipfad miteinander
          */
         int32 CompareTo(const File &other) const override;

         /*!
          \brief Returns the tags of the file.

          In mac os these tags are presented by the Finder.
          */
         Array<String> GetTags()const;

         /*!
          \brief Adds a tag to the file. If the tag already exists, nothing happens.
          */
         VxfErrorStatus AddTag(const String &tag);

         /*!
          \brief Remove a tag from the file. If the tag not exists, nothing happens.
          */
         VxfErrorStatus RemoveTag(const String &tag);

         //Operatore
         File &operator=(const File &another);

      private:
         /*!
          \brief Der Pfadname der Datei. Er ist normalisiert, das heißt er benutzt die auf dem
          System verwendeten Verzeichnisseparatoren und keine Duplikate usw.
          */
         String mPathname;

         /*!
          \brief Die C-String Repräsentation des Pfadnamen. Wird bei Bedarf angelegt und gehalten
          */
         ByteArray mCstr;

         /*!
          \brief Filehandle im Betriebssystem
          */
         FILE* mHandle;

         /*!
          \brief Diese Methode normalisiert den Pfadnamen.
          \discussion Unter Unix enthält ein normalisierter Pfadname keine doppelten Schrägstriche
          und endet nicht mit einem Schrägstrich.
          */
         String Normalize(const String &pathnames);

         /*!
          \brief Diese Methode kombiniert den Vaternamen mit dem Childnamen
          Achtung: parent und child müssen normalisiert sein.
          \param parent Der Pfadname der "Vaterdatei".
          \param child Der Pfadname der "Kinddatei"
          */
         String Resolve(String parent,
                        String child);

         /*!
          \brief Diese Helfermethode setzt den C-String, mit dem dann im Betriebssystem der
          Dateiname aufgelöst wird
          */
         void SetCString();
   };



   /*!
    \brief Diese Methode gibt den Pfad der ausführenden Anwendung zurück. Er besteht aus
    Verzeichnisname und Anwendungsname
    */
   extern DllExport
   String ExecPath();

   /*!
    \brief Diese Methode gibt das Verzeichnis zurück, in dem die Anwendung ausgeführt wird
    */
   extern DllExport
   String ExecDir();

   /*!
    \brief Diese Methode gibt das Verzeichnis zurück, in dem die Anwendung ausgeführt wird
    */
   extern DllExport
   String ExecName();

   /*!
    Diese Methode gibt das Verzeichnis zurück, in dem die aktuelle Anwendung nach Ressourcen suchen
    soll
    */
   extern DllExport
   File ResourceDir(const String &bundleId);   //Unter MAC mit Bundle-ID...

   /*!
    Diese Methode gibt das Verzeichnis zurück, in dem ide aktuelle Anwendung ihre Einstellungen
    speichern.
    */
   extern DllExport
   File PropertyDir();

   /*!
    Diese Methode gibt das Benutzer-Verzeichnis zurück.
    */
   extern DllExport
   File UserDir();

}


#endif
