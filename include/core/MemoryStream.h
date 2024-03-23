////////////////////////////////////////////////////////////////////////////////////////////////////
// Name:        MeoryStream.h
// Library:     Jameo Core Library
// Purpose:     Helper classes for our stream object
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

#ifndef jm_MemoryStream_h
#define jm_MemoryStream_h

#include "Stream.h"

namespace jm
{

   /*!
   \brief The MemoryStream class represents a byte stream access to a byte array.
   */
   class DllExport MemoryStream : public Stream
   {

      public:

         /*!
          */
         Integer mWritelength;


         /*!
          \brief Konstruktor.
          \param array Das Byte-Array auf dem die Streamoperationen angewendet werden sollen.
          \param length Die Länge des Byte-Arrays
          */
         MemoryStream(uint8* array, Integer length);

         /*!
         \brief Öffnet den Stream um Lese- oder Schreiboperationen an ihm vorzunehmen.
         \param mode Der Modus zum öffnen.
         */
         void Open(FileMode mode) override;

         /*!
          \brief Status, ob die Datei geöffnet ist
          */
         bool IsOpen() override;

         /*!
         \brief Schließt den Stream, wenn sie vorher geöffnet war. Unf gibt ggf. Systemressourcen frei.
         */
         void Close() override;

         /*!
         \brief Liest maximal length bytes in das Array
         \return Die tatsächlich eingelesene Menge an Bytes, oder 0 wenn keine Bytes gelesen wurden (EOF)
         */
         Integer Read(uint8* buffer, Integer length) override;

         /*!
         \brief Liest maximal length bytes in das Array
         \return Die tatsächlich eingelesene Menge an Bytes, oder 0 wenn keine Bytes gelesen wurden (EOF)
         */
         Integer ReadFully(ByteArray& buffer, Integer length) override;

         /*!
         \brief Bewegt den Dateicursor an die gewünschte Stelle, gezählt vom Dateianfang (0-basierter Index)
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
          \brief Gibt die Länge des Streams zurück
          */
         Integer Length() const override;

         /*!
          \brief Gibt den Puffer zurück
          */
         uint8* GetBuffer();

      private:

         /*!
          \brief Das Byte-Array, welches als Quelle oder Ziel dient.
          */
         uint8* mStream;

         /*!
          \brief Die Länge des Arrays.
          */
         Integer mStreamlength;

         /*!
          \brief Die aktuelle Zeigerposition in dem Array.
          */
         Integer mPosition;

   };




}
#endif
