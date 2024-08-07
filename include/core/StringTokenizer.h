////////////////////////////////////////////////////////////////////////////////////////////////////
// Name:        StringTokenizer.h
// Library:     Jameo Core Library
// Purpose:     String tokenizer
//
// Author:      Uwe Runtemund (2013-today)
// Modified by:
// Created:     02.02.2013
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

#ifndef jm_StringTokenizer_h
#define jm_StringTokenizer_h

#include "String.h"

namespace jm
{

   /*!
    \brief Der Strintokenizer ist eine Klasse, die dazu dient, eine Zeichenkette an bestimmten
    Trennzeichen zu trennen und in einzelne Stücke zu zerlegen.
    */
   class DllExport StringTokenizer: public Object
   {
      public:

         /*!
          \brief Konstruktor
          \param str Die Zeichenkette, die untersucht werden soll.
          \param delimiter Die Trennzeichen, an denen die Zeichenkette getrennt werden soll. Jedes
          Zeichen wird als Trennzeichen angesehen. es geht nicht darum, dass die gesamte
          Zeichenkette als Trenner dient.
          \param retDelim Status, ob die Trennzeichen als eigene Tokens betrachtet und zurückgegeben
          werden oder nicht.
          */
         StringTokenizer(const String& str, const String& delimiter, Bool retDelim);

         /*!
          \brief Gibt zurück, ob noch weitere Tokens in der Zeichenkette vorhanden sind.
          */
         Bool hasNext();

         /*!
          \brief Gibt das Nächste Token zurück.
          @throw Exception, wenn kein Token mehr vorhanden ist.
          */
         String next();

      private:

         /*!
          \brief Der String, der untersucht werden soll.
          */
         String mStr;

         /*!
          \brief Die Trennzeichen, an denen der String unterteilt werden soll.
          */
         String mDelimiters;

         /*!
          \brief Die aktuelle Zeigerposition.
          */
         Integer mPosition;

         /*!
          \brief Die Zeigerposition des ersten Zeichens des nächsten Tokens)
          */
         Integer mNewStart;

         /*!
          \brief Status, ob auch die Trennzeichen als Token zurückgegeben werden sollen.
          */
         Bool mRetDelim;

         /*!
          \brief Diese Methode prüft, ob das Zeichen an einer Stelle ein Trennzeichen ist
          \param index Der 0-basierte Index des Zeichens im String, das untersucht werden soll.
          \return "Wahr", wenn das Zeichen an der Stelle index ein definiertes Trennzeichen ist.
          Andernfalls "falsch".
          */
         Bool IsDelimiter(Integer index) const;

         /*!
          \brief Diese Methode such ab einer gewünschten Position nach dem Ende eines Tokens,
          also sucht den Index des ersten Delimiter-Zeichens
          \param startPos Die Position, die gesucht werden soll.
          \return Den Index im String str, an der das Tokenende gefunden wurde oder die Länge des
          Tokens, wenn kein Delimiter mehr vorkommt.
          */
         Integer FindTokenEnd(Integer startPos) const;

         /*!
          \brief Sucht nach dem Ende des Trennzeichens ab einer bestimmten Position. Wenn
          retDelim "falsch" ist, dann wird die Position des ersten Nicht-Trennzeichens ab der
          Startposition zurückgegeben. Wenn retDelim "wahr" ist, wird die startPosition
          zurückgegeben.
          \param startPos Die Position, die gesucht werden soll.
          \return Den Index im String str, an der das Trennende gefunden wurde.
          */
         Integer FindDelimEnd(Integer startPos) const;
   };


}


#endif
