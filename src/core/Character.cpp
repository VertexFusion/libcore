////////////////////////////////////////////////////////////////////////////////////////////////////
// Name:        Character.cpp
// Library:     Jameo Core Library
// Purpose:     Implementation of Character
//
// Author:      Uwe Runtemund (2013-today)
// Modified by:
// Created:     17.01.2013
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

#include "Precompiled.h"


bool jm::Char::IsWhitespace() const
{
   switch(mChar)
   {
      case ' ':
      case '\r':
      case '\n':
      case '\t':
      case '\b':
      case '\f':
         return true;

      default:
         return false;
   }
}


bool jm::Char::IsDigit()const
{
   if(mChar >= '0' && mChar <= '9')return true;
   return false;
}

int32 jm::Char::DigitValue()const
{
   if(mChar >= '0' && mChar <= '9') return mChar-'0';
   return -1;
}


jm::Char jm::Char::ToLowerCase() const
{
   // Encoding is unicode

   switch(mChar)
   {
      case 'A':
         return Char('a');
      case 'B':
         return Char('b');
      case 'C':
         return Char('c');
      case 'D':
         return Char('d');
      case 'E':
         return Char('e');
      case 'F':
         return Char('f');
      case 'G':
         return Char('g');
      case 'H':
         return Char('h');
      case 'I':
         return Char('i');
      case 'J':
         return Char('j');
      case 'K':
         return Char('k');
      case 'L':
         return Char('l');
      case 'M':
         return Char('m');
      case 'N':
         return Char('n');
      case 'O':
         return Char('o');
      case 'P':
         return Char('p');
      case 'Q':
         return Char('q');
      case 'R':
         return Char('r');
      case 'S':
         return Char('s');
      case 'T':
         return Char('t');
      case 'U':
         return Char('u');
      case 'V':
         return Char('v');
      case 'W':
         return Char('w');
      case 'X':
         return Char('x');
      case 'Y':
         return Char('y');
      case 'Z':
         return Char('z');

      case 0x00C4://Ä
         return Char(0x00E4);//ä

      case 0x00D6://Ö
         return Char(0x00F6);//ö

      case 0x00DC://Ü
         return Char(0x00FC);//ü

      default:
         return Char(mChar);
   }
}

jm::Char jm::Char::ToUpperCase() const
{
   // Encoding is unicode

   switch(mChar)
   {
      case 'a':
         return 'A';
      case 'b':
         return 'B';
      case 'c':
         return 'C';
      case 'd':
         return 'D';
      case 'e':
         return 'E';
      case 'f':
         return 'F';
      case 'g':
         return 'G';
      case 'h':
         return 'H';
      case 'i':
         return 'I';
      case 'j':
         return 'J';
      case 'k':
         return 'K';
      case 'l':
         return 'L';
      case 'm':
         return 'M';
      case 'n':
         return 'N';
      case 'o':
         return 'O';
      case 'p':
         return 'P';
      case 'q':
         return 'Q';
      case 'r':
         return 'R';
      case 's':
         return 'S';
      case 't':
         return 'T';
      case 'u':
         return 'U';
      case 'v':
         return 'V';
      case 'w':
         return 'W';
      case 'x':
         return 'X';
      case 'y':
         return 'Y';
      case 'z':
         return 'Z';

      case 0x00E4://ä
         return 0x00C4;//Ä

      case 0x00F6://ö
         return 0x00D6;//Ö

      case 0x00FC://ü
         return 0x00DC;//Ü

      default:
         return mChar;
   }
}

bool jm::Char::IsUpperCase() const
{
   return (mChar >= 'A' && mChar <= 'Z');
}

bool jm::Char::IsLowerCase() const
{
   return (mChar >= 'a' && mChar <= 'z');
}
