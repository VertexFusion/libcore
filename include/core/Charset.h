////////////////////////////////////////////////////////////////////////////////////////////////////
// Name:        Charset.h
// Library:     Jameo Core Library
// Purpose:     Character Encodings
//
// Author:      Uwe Runtemund (2013-today)
// Modified by:
// Created:     18.01.2013
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

#ifndef jm_Charset_h
#define jm_Charset_h

#include "CharArray.h"
#include "String.h"

namespace jm
{

   /*!
    \brief The class Charset is a mapping function to make a string out of arbitrarily coded
    C-strings, or vice versa.
    \ingroup core
    */
   class DllExport CharsetDecoder: public Object
   {
      public:
         /*!
          \brief Constructor
          */
         CharsetDecoder();

         /*!
          \brief Destructor
          */
         ~CharsetDecoder() override;

         /*!
          \brief This method decodes a C-string using the encoding implemented in the decoder
          and converts it into a Unicode-encoded chararray.
          \param cString The C-string that is to be converted.
          \return The chararray, which contains the Unicode-encoded representation of the C-string.
          */
         virtual CharArray decode(const char* cString) = 0;

         /*!
          \brief This Method encodes the given string into an encoded String using the encoding implemented in the decoder.
          \param string The Unicode-encoded String be converted.
          \return A C-string whose coding is determined by this decoder.
          */
         virtual ByteArray encode(const CharArray& string) = 0;

   };

   /*!
    \brief  The class Charset is a factory class to make a string out of arbitrarily coded C-strings
    and vice versa.
    \ingroup core
    */
   class DllExport Charset: public Object
   {

      public:

         /*!
          \brief Special constructor for the static initialisation of the default decoder. This is always the UTF-8 encoding.
          */
         Charset(CharsetDecoder* decoder);

         /*!
          \brief Constructor for the static initialisation (therefore not a string).
          \param name Name of the character set
          \param decoder The decoder for this character set
          */
         Charset(const char* name,
                 CharsetDecoder* decoder);

         /*!
          \brief Constructor
          \param name Name of the character set
          \param alternatives Alternative names for the character set
          \param altCount Number of alternative names for this character set
          \param decoder The decoder for this character set
          */
         Charset(const String& name,
                 const String* alternatives,
                 uint8 altCount, CharsetDecoder*
                 decoder);

         /*!
          \brief Destructor
          */
         virtual ~Charset();

         /*!
          \brief This method returns the name of the character set.
          */
         String name() const;

         /*!
          \brief This method tests whether the character set is addressed under the desired name.
          \param name The name that is to be checked using this method.
          \return Returns true if either the name of the character set or one of the alternative names matches \c name. Otherwise, return value is false.
          */
         bool hasName(const String& name);

         /*!
          \brief This method decodes the C-string and generates a chararray that has been converted through the encoding.
          \param cString The C-string that is to be converted.
          */
         CharArray decode(const char* cString);

         /*!
          \brief This Method generates the corresponding C-string from a string using this character set.
          \param string The C-string that is to be converted.
          */
         ByteArray encode(const CharArray& string);

         /*!
          \brief This method returns the desired charset by name.
          \param name The name of the charset.
          \return The charset, or NULL, if the charset for name was not found.
          */
         static Charset* forName(const String& name);

         /*!
          \brief This method returns the default character set (UTF-8).
          */
         static Charset* getDefault();

         /*!
          \brief This method guesses the character encoding from the given array and returns the guessed name.
          If no character set is recognised, depending on the operating system, the default character set is returned.
          Corresponding to the operating system, those are the following:
          - Windows: Windows-1252
          - Mac: MacRoman
          - Linux: UTF-8
          However, even if one of the values above is returned it does not automatically mean that no character set was recognised.
          */
         static String guess(const char* stream,
                             int64 length);

      private:

         /*!
          \brief Number of character encodings
          */
         static uint16 gCharsetCount;

         /*!
          \brief Array with the character encodings
          */
         static Charset* gCharsets[];

         /*!
         \brief The name of this character set. E.g. UTF-8
         */
         String mName;

         /*!
         \brief An array with alternative names in the event that this character set has several common names.
         */
         String* mAlternatives;

         /*!
         \brief Number of alternative names.
         */
         uint8 mAltCount;

         /*!
         \brief The encoding function for this character set.
         */
         CharsetDecoder* mDecoder;

         friend void quitCharsets();
   };

   /*!
    \brief Decoder converts the bytes 1 to 1. Only the LSB is taken into account. Values > 255 are
    therefore truncated.
    \ingroup core
    */
   class DllExport RawDecoder: public CharsetDecoder
   {
      public:
         RawDecoder();
         CharArray decode(const char* cString)override;
         ByteArray encode(const CharArray& string) override;
   };

   /*!
    \brief Decoder for UTF8 encoding.
    \ingroup core
    */
   class DllExport UTF8Decoder: public CharsetDecoder
   {
      public:
         UTF8Decoder();
         CharArray decode(const char* cString)override;
         ByteArray encode(const CharArray& string) override;
   };


   /*!
    \brief Decoder for UTF16 encoding.
    \ingroup core
    */
   class DllExport UTF16Decoder: public CharsetDecoder
   {
      private:
         bool be;
      public:
         UTF16Decoder(bool isBE);
         CharArray decode(const char* cString)override;
         ByteArray encode(const CharArray& string) override;
   };

   /*!
    \brief  Decoder for Windows CP 1252 encoding.
    \ingroup core
    */
   class DllExport Windows1252Decoder: public CharsetDecoder
   {
      private:
         Char* codepage;

      public:
         Windows1252Decoder();
         ~Windows1252Decoder();
         CharArray decode(const char* cString)override;
         ByteArray encode(const CharArray& string) override;
   };

   /*!
    \brief Decoder for Macintosh Roman Codierung (CP 10000) encoding.
    \ingroup core
    */
   class DllExport MacRomanDecoder: public CharsetDecoder
   {
      private:
         Char* codepage;

      public:
         MacRomanDecoder();
         ~MacRomanDecoder();
         CharArray decode(const char* cString)override;
         ByteArray encode(const CharArray& string) override;

         Char decodeCharacter(uint8 macencode);
         uint8 encodeCharacter(uint16 unicode);
   };

   /*!
   \brief Initialises the charsets.
   \discussion Called by System::init. Therefore no export necessary.
   */
   void initCharsets();

   /*!
   \brief Deletes the charset objects.
   \discussion Called by System::quit. Therefore no export necessary.
   */
   void quitCharsets();

}

#endif
