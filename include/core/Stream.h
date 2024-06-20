////////////////////////////////////////////////////////////////////////////////////////////////////
// Name:        Stream.h
// Library:     Jameo Core Library
// Purpose:     Declaration of Stream class
//
// Author:      Uwe Runtemund (2015-today)
// Modified by:
// Created:     18.08.2015
//
// Copyright:   (c) 2015 Jameo Software, Germany. https://jameo.de
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

#ifndef jm_Stream_h
#define jm_Stream_h

#include "Types.h"
#include "Object.h"
#include "String.h"

namespace jm
{

   /*!
    \brief Mode for opening streams and files.
    */
   enum FileMode
   {
      kFmRead,      /*!< Open for reading only. Corresponds to \c rb */
      kFmWrite,     /*!< Open for writing only. Corresponds to \c wb */
      kFmReadWrite  /*!< Open for reading and writing. Corresponds to \c rb+ */
   };

   /*!
    \brief Die Stream-Klasse ist eine Abstraktionsklasse, um Datenströme über eine einheitliche
    Schnittstelle bearbeiten zu können. Der Stream selbst kann dabei eine Datei, ein Byte-Array,
    eine Neztwerkschnittstelle, oder irgendetwas anderes sein.
    */
   class DllExport Stream: public Object
   {

      public:

         /*!
          \brief Konstruktor
          */
         Stream();

         /*!
          \brief Gibt die Länge des Streams zurück
          */
         virtual Integer size() const = 0;

         /*!
          \brief Öffnet den Stream um Lese- oder Schreiboperationen an ihm vorzunehmen.
          \param mode Der Modus zum öffnen.
          */
         virtual VxfErrorStatus open(FileMode mode) = 0;

         /*!
          \brief Status, ob die Datei geöffnet ist
          */
         virtual bool isOpen() = 0;

         /*!
          \brief Schließt den Stream, wenn sie vorher geöffnet war. Unf gibt ggf. Systemressourcen
          frei.
          */
         virtual void close() = 0;

         /*!
          \brief Liest maximal length bytes in das Array.
          \details Bei Großen Blocken kann es sein, dass nicht alle Bytes eingelesen werden, weil
          noch auf Daten gewartet werden. In diesem Fall kann es sein, dass nur ein Teil
          zurückgegeben wird. Will man in jedem Fall alle Daten haben, muss man readFully()
          aufrufen.
          \return Die tatsächlich eingelesene Menge an Bytes, oder 0 wenn keine Bytes gelesen wurden
          (EOF).
          */
         virtual Integer read(uint8* buffer, Integer length) = 0;

         /*!
          \brief Liest maximal length bytes in das Array
          \return Die tatsächlich eingelesene Menge an Bytes, oder 0 wenn keine Bytes gelesen wurden
          (EOF).
          */
         virtual Integer readFully(ByteArray &buffer, Integer length) = 0;
         Integer readFully(ByteArray &buffer)
         {
            return readFully(buffer, buffer.size());
         };

         /*!
          \brief Bewegt den Dateicursor an die gewünschte Stelle, gezählt vom Dateianfang
          (0-basierter Index).
          \note Nicht jeder Stream unterstützt diese Methode.
          */
         virtual void seek(Integer position) = 0;

         /*!
          \brief Bewegt den Dateicursor an die gewünschte Stelle, gezählt von der aktuellen Position
          */
         virtual void move(Integer offset) = 0;

         /*!
          \brief Diese Methode gibt die aktuelle Cursorposition in der Datei zurück
          Nicht jeder Stream unterstützt diese Methode.
          */
         virtual Integer position() = 0;

         /*!
          \brief Schreibt einen Buffer in die Ausgabedatei
          */
         virtual Integer write(const uint8* buffer, Integer length) = 0;
         inline Integer write(const int8* buffer, Integer length)
         {
            return write((const uint8*)buffer, length);
         };

         /*!
          \brief Schreibt einen String in die Ausgabedatei. Kodierung ist die Standardkodierung
          (also UTF-8).
          NICHT ALS C_STRING
          */
         Integer write(const String &string);

   };
}
#endif
