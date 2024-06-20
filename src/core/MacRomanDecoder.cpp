////////////////////////////////////////////////////////////////////////////////////////////////////
// Name:        MacRomanDecoder.cpp
// Library:     Jameo Core Library
// Purpose:     Decoder for mac roman encoded text.
//
// Author:      Uwe Runtemund (2013-today)
// Modified by:
// Created:     09.05.2013
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

using namespace jm;

MacRomanDecoder::MacRomanDecoder(): CharsetDecoder()
{
   uint16 cp[]
   =
   {
      0x0000, 0x0001, 0x0002, 0x0003, 0x0004, 0x0005, 0x0006, 0x0007, 0x0008, 0x0009, 0x000A, 0x000B, 0x000C, 0x000D, 0x000E, 0x000F,
      0x0010, 0x0011, 0x0012, 0x0013, 0x0014, 0x0015, 0x0016, 0x0017, 0x0018, 0x0019, 0x001A, 0x001B, 0x001C, 0x001D, 0x001E, 0x001F,
      0x0020, 0x0021, 0x0022, 0x0023, 0x0024, 0x0025, 0x0026, 0x0027, 0x0028, 0x0029, 0x002A, 0x002B, 0x002C, 0x002D, 0x002E, 0x002F,
      0x0030, 0x0031, 0x0032, 0x0033, 0x0034, 0x0035, 0x0036, 0x0037, 0x0038, 0x0039, 0x003A, 0x003B, 0x003C, 0x003D, 0x003E, 0x003F,
      0x0040, 0x0041, 0x0042, 0x0043, 0x0044, 0x0045, 0x0046, 0x0047, 0x0048, 0x0049, 0x004A, 0x004B, 0x004C, 0x004D, 0x004E, 0x004F,
      0x0050, 0x0051, 0x0052, 0x0053, 0x0054, 0x0055, 0x0056, 0x0057, 0x0058, 0x0059, 0x005A, 0x005B, 0x005C, 0x005D, 0x005E, 0x005F,
      0x0060, 0x0061, 0x0062, 0x0063, 0x0064, 0x0065, 0x0066, 0x0067, 0x0068, 0x0069, 0x006A, 0x006B, 0x006C, 0x006D, 0x006E, 0x006F,
      0x0070, 0x0071, 0x0072, 0x0073, 0x0074, 0x0075, 0x0076, 0x0077, 0x0078, 0x0079, 0x007A, 0x007B, 0x007C, 0x007D, 0x007E, 0x007F,
      0x00C4, 0x00C5, 0x00C7, 0x00C9, 0x00D1, 0x00D6, 0x00DC, 0x00E1, 0x00E0, 0x00E2, 0x00E4, 0x00E3, 0x00E5, 0x00E7, 0x00E9, 0x00E8, //
      0x00EA, 0x00EB, 0x00EC, 0x00ED, 0x00EE, 0x00EF, 0x00F1, 0x00F3, 0x00F2, 0x00F4, 0x00F6, 0x00F5, 0x00FA, 0x00F9, 0x00FB, 0x00FC, //
      0x2020, 0x00B0, 0x00A2, 0x00A3, 0x00A7, 0x2022, 0x00B6, 0x00DF, 0x00AE, 0x00A9, 0x2122, 0x00B4, 0x00A8, 0x2260, 0x00C6, 0x00D8, //
      0x211E, 0x00B1, 0x2264, 0x2265, 0x00A5, 0x00B5, 0x2202, 0x2211, 0x220F, 0x03C0, 0x222B, 0x00AA, 0x00BA, 0x03A9, 0x00E6, 0x00F8, //
      0x00BF, 0x00A1, 0x00AC, 0x221A, 0x0192, 0x2248, 0x2206, 0x00AB, 0x00BB, 0x2026, 0x00A0, 0x00C0, 0x00C3, 0x00D5, 0x0152, 0x0153, //
      0x2013, 0x2014, 0x201C, 0x201D, 0x2018, 0x2019, 0x00F7, 0x25CA, 0x00FF, 0x0178, 0x2044, 0x20AC, 0x2039, 0x203A, 0xFB01, 0xFB02, //
      0x2021, 0x00B7, 0x201A, 0x201E, 0x2030, 0x00C2, 0x00CA, 0x00C1, 0x00CB, 0x00C8, 0x00CD, 0x00CE, 0x00CF, 0x00CC, 0x00D3, 0x00D4, //
      0xF8FF, 0x00D2, 0x00DA, 0x00DB, 0x00D9, 0x0131, 0x02C6, 0x02DC, 0x00AF, 0x02D8, 0x02D9, 0x02DA, 0x00B8, 0x02DD, 0x02DB, 0x02C7 //
   };
   codepage = new Char[256];
   memcpy(codepage, cp, 256 * 2);
}

MacRomanDecoder::~MacRomanDecoder()
{
   delete[] codepage;
}

Char MacRomanDecoder::DecodeCharacter(uint8 macencode)
{
   return codepage[macencode];
}

uint8 MacRomanDecoder::EncodeCharacter(uint16 unicode)
{
   switch(unicode)
   {
      case 0:
         return 0;
      case 1:
         return 1;
      case 2:
         return 2;
      case 3:
         return 3;
      case 4:
         return 4;
      case 5:
         return 5;
      case 6:
         return 6;
      case 7:
         return 7;
      case 8:
         return 8;
      case 9:
         return 9;
      case 10:
         return 10;
      case 11:
         return 11;
      case 12:
         return 12;
      case 13:
         return 13;
      case 14:
         return 14;
      case 15:
         return 15;
      case 16:
         return 16;
      case 17:
         return 17;
      case 18:
         return 18;
      case 19:
         return 19;
      case 20:
         return 20;
      case 21:
         return 21;
      case 22:
         return 22;
      case 23:
         return 23;
      case 24:
         return 24;
      case 25:
         return 25;
      case 26:
         return 26;
      case 27:
         return 27;
      case 28:
         return 28;
      case 29:
         return 29;
      case 30:
         return 30;
      case 31:
         return 31;
      case ' ':
         return 0x20;
      case '!':
         return 0x21;
      case '"':
         return 0x22;
      case '#':
         return 0x23;
      case '$':
         return 0x24;
      case '%':
         return 0x25;
      case '&':
         return 0x26;
      case '\'':
         return 0x27;
      case '(':
         return 0x28;
      case ')':
         return 0x29;
      case '*':
         return 0x2A;
      case '+':
         return 0x2B;
      case ',':
         return 0x2C;
      case '-':
         return 0x2D;
      case '.':
         return 0x2E;
      case '/':
         return 0x2F;
      case '0':
         return 0x30;
      case '1':
         return 0x31;
      case '2':
         return 0x32;
      case '3':
         return 0x33;
      case '4':
         return 0x34;
      case '5':
         return 0x35;
      case '6':
         return 0x36;
      case '7':
         return 0x37;
      case '8':
         return 0x38;
      case '9':
         return 0x39;
      case ':':
         return 0x3A;
      case ';':
         return 0x3B;
      case '<':
         return 0x3C;
      case '=':
         return 0x3D;
      case '>':
         return 0x3E;
      case '?':
         return 0x3F;
      case '@':
         return 0x40;
      case 'A':
         return 0x41;
      case 'B':
         return 0x42;
      case 'C':
         return 0x43;
      case 'D':
         return 0x44;
      case 'E':
         return 0x45;
      case 'F':
         return 0x46;
      case 'G':
         return 0x47;
      case 'H':
         return 0x48;
      case 'I':
         return 0x49;
      case 'J':
         return 0x4A;
      case 'K':
         return 0x4B;
      case 'L':
         return 0x4C;
      case 'M':
         return 0x4D;
      case 'N':
         return 0x4E;
      case 'O':
         return 0x4F;
      case 'P':
         return 0x50;
      case 'Q':
         return 0x51;
      case 'R':
         return 0x52;
      case 'S':
         return 0x53;
      case 'T':
         return 0x54;
      case 'U':
         return 0x55;
      case 'V':
         return 0x56;
      case 'W':
         return 0x57;
      case 'X':
         return 0x58;
      case 'Y':
         return 0x59;
      case 'Z':
         return 0x5A;
      case '[':
         return 0x5B;
      case '\\':
         return 0x5C;
      case ']':
         return 0x5D;
      case '^':
         return 0x5E;
      case '_':
         return 0x5F;
      case '`':
         return 0x60;
      case 'a':
         return 0x61;
      case 'b':
         return 0x62;
      case 'c':
         return 0x63;
      case 'd':
         return 0x64;
      case 'e':
         return 0x65;
      case 'f':
         return 0x66;
      case 'g':
         return 0x67;
      case 'h':
         return 0x68;
      case 'i':
         return 0x69;
      case 'j':
         return 0x6A;
      case 'k':
         return 0x6B;
      case 'l':
         return 0x6C;
      case 'm':
         return 0x6D;
      case 'n':
         return 0x6E;
      case 'o':
         return 0x6F;
      case 'p':
         return 0x70;
      case 'q':
         return 0x71;
      case 'r':
         return 0x72;
      case 's':
         return 0x73;
      case 't':
         return 0x74;
      case 'u':
         return 0x75;
      case 'v':
         return 0x76;
      case 'w':
         return 0x77;
      case 'x':
         return 0x78;
      case 'y':
         return 0x79;
      case 'z':
         return 0x7A;
      case '{':
         return 0x7B;
      case '|':
         return 0x7C;
      case '}':
         return 0x7D;
      case '~':
         return 0x7E;
      //0x7f is DEL (invisible)
      case 0x00C4:
         return 0x80; //Adieresis (Ä)
      case 0x00C5:
         return 0x81;//Aring (Å)
      case 0x00C7:
         return 0x82; //Ccedilla (Ç)
      case 0x00C9:
         return 0x83; //Eacute (É)
      case 0x00D1:
         return 0x84; //Ntilde (Ñ)
      case 0x00D6:
         return 0x85; //Odieresis (Ö)
      case 0x00DC:
         return 0x86; //Udieresis (Ü)
      case 0x00E1:
         return 0x87; //aacute (á)
      case 0x00E0:
         return 0x88; //agrave (à)
      case 0x00E2:
         return 0x89; //acircumflex (â)
      case 0x00E4:
         return 0x8A; //adieresis (ä)
      case 0x00E3:
         return 0x8B; //atilde (ã)
      case 0x00E5:
         return 0x8C; //aring (å)
      case 0x00E7:
         return 0x8D; //ccedilla (ç)
      case 0x00E9:
         return 0x8E;//eacute (é)
      case 0x00E8:
         return 0x8F;//egrave (è)
      case 0x00EA:
         return 0x90;//ecircumflex (ê)
      case 0x00EB:
         return 0x91;//edieresis (ë)
      case 0x00ED:
         return 0x92;//iacute (í)
      case 0x00EC:
         return 0x93;//igrave (ì)
      case 0x00EE:
         return 0x94;//icircumflex (î)
      case 0x00EF:
         return 0x95;//idieresis (ï)
      case 0x00F1:
         return 0x96;//ntilde (ñ)
      case 0x00F3:
         return 0x97;//oacute (ó)
      case 0x00F2:
         return 0x98;//ograve (ò)
      case 0x00F4:
         return 0x99;//ocircumflex (ô)
      case 0x00F6:
         return 0x9A;//odieresis (ö)
      case 0x00F5:
         return 0x9B;//otilde (õ)
      case 0x00FA:
         return 0x9C;//uacute (ú)
      case 0x00F9:
         return 0x9D;//ugrave (ù)
      case 0x00FB:
         return 0x9E;//ucircumflex (û)
      case 0x00FC:
         return 0x9F;//udieresis (ü)
      case 0x2020:
         return 0xA0;//dagger (†)
      case 0x00B0:
         return 0xA1;//degree (°)
      case 0x00A2:
         return 0xA2;//cent (¢)
      case 0x00A3:
         return 0xA3;//sterling (£)
      case 0x00A7:
         return 0xA4;//section (§)
      case 0x2022:
         return 0xA5;//bullet (•)
      case 0x00B6:
         return 0xA6;//paragraph (¶)
      case 0x00DF:
         return 0xA7;//germandbls (ß)
      case 0x00AE:
         return 0xA8;//registered (®)
      case 0x00A9:
         return 0xA9;//copyright (©)
      case 0x2122:
         return 0xAA;//trademark (™)
      case 0x00B4:
         return 0xAB;//acute (´)
      case 0x00A8:
         return 0xAC;//dieresis (¨)
      case 0x2260:
         return 0xAD;//notequal (≠)
      case 0x00C6:
         return 0xAE;//AE (Æ)
      case 0x00D8:
         return 0xAF;//Oslash (Ø)
      case 0x221E:
         return 0xB0;//146 infinity (∞)
      case 0x00B1:
         return 0xB1;//147 plusminus (±)
      case 0x2264:
         return 0xB2;//148 lessequal (≤)
      case 0x2265:
         return 0xB3;//149 greaterequal (≥)
      case 0x00A5:
         return 0xB4;//150 yen (¥)
      case 0x00B5:
         return 0xB5;//151 mu (µ)
      case 0x2202:
         return 0xB6;//152 partialdiff (∂)
      case 0x2211:
         return 0xB7;//153 summation (∑)
      case 0x220F:
         return 0xB8;//154 product (∏)
      case 0x03C0:
         return 0xB9;//155 pi (π)
      case 0x222B:
         return 0xBA;//156 integral (∫)
      case 0x00AA:
         return 0xBB;//157 ordfeminine (ª)
      case 0x00BA:
         return 0xBC;//158 ordmasculine (º)
      case 0x03A9:
         return 0xBD;//159 Omega (Ω)
      case 0x00E6:
         return 0xBE;//160 ae (æ)
      case 0x00F8:
         return 0xBF;//161 oslash (ø)
      case 0x00BF:
         return 0xC0;//162 questiondown (¿)
      case 0x00A1:
         return 0xC1;//163 exclamdown (¡)
      case 0x00AC:
         return 0xC2;//164 logicalnot (¬)
      case 0x221A:
         return 0xC3;//165 radical (√)
      case 0x0192:
         return 0xC4;//166 florin (ƒ)
      case 0x2248:
         return 0xC5;//167 approxequal (≈)
      case 0x2206:
         return 0xC6;//168 Delta / increment (∆)
      case 0x00AB:
         return 0xC7;//169 guillemotleft («)
      case 0x00BB:
         return 0xC8;//170 guillemotright (»)
      case 0x2026:
         return 0xC9;//171 ellipsis (…)
      case 0x00A0:
         return 0xCA;//172 nonbreakingspace
      case 0x00C0:
         return 0xCB;//173 Agrave (À)
      case 0x00C3:
         return 0xCC;//174 Atilde (Ã)
      case 0x00D5:
         return 0xCD;//175 Otilde (Õ)
      case 0x0152:
         return 0xCE;//176 OE (Œ)
      case 0x0153:
         return 0xCF;//177 oe (œ)
      case 0x2013:
         return 0xD0;//178 endash (–)
      case 0x2014:
         return 0xD1;//179 emdash (—)
      case 0x201C:
         return 0xD2;//180 quotedblleft (“)
      case 0x201D:
         return 0xD3;//181 quotedblright (”)
      case 0x2018:
         return 0xD4;//182 quoteleft (‘)
      case 0x2019:
         return 0xD5;//183 quoteright (’)
      case 0x00F7:
         return 0xD6;//184 divide (÷)
      case 0x25CA:
         return 0xD7;//185 lozenge (◊)
      case 0x00FF:
         return 0xD8;//186 ydieresis (ÿ)
      case 0x0178:
         return 0xD9;//187 Ydieresis (Ÿ)
      case 0x2044:
         return 0xDA;//188 fraction (⁄)
      case 0x00A4:
         return 0xDB;//189 currency //wude ab MAC 8.5 durch Euro ersetzt. (¤)
      case 0x20AC:
         return 0xDB;//189 currency //wude ab MAC 8.5 durch Euro ersetzt. (€)
      case 0x2039:
         return 0xDC;//190 guilsinglleft (‹)
      case 0x203A:
         return 0xDD;//191 guilsinglright (›)
      case 0xFB01:
         return 0xDE;//192 fi (ﬁ)
      case 0xFB02:
         return 0xDF;//193 fl (ﬂ)
      case 0x2021:
         return 0xE0;//194 daggerdbl (‡)
      case 0x00B7:
         return 0xE1;//195 periodcentered (·)
      case 0x201A:
         return 0xE2;//196 quotesinglbase (‚)
      case 0x201E:
         return 0xE3;//197 quotedblbase („)
      case 0x2030:
         return 0xE4;//198 perthousand (‰)
      case 0x00C2:
         return 0xE5;//199 Acircumflex (Â)
      case 0x00CA:
         return 0xE6;//200 Ecircumflex (Ê)
      case 0x00C1:
         return 0xE7;//201 Aacute (Á)
      case 0x00CB:
         return 0xE8;//202 Edieresis (Ë)
      case 0x00C8:
         return 0xE9;//203 Egrave (È)
      case 0x00CD:
         return 0xEA;//204 Iacute (Í)
      case 0x00CE:
         return 0xEB;//205 Icircumflex (Î)
      case 0x00CF:
         return 0xEC;//206 Idieresis (Ï)
      case 0x00CC:
         return 0xED;//207 Igrave (Ì)
      case 0x00D3:
         return 0xEE;//208 Oacute (Ó)
      case 0x00D4:
         return 0xEF;//209 Ocircumflex (Ô)
      case 0xF8FF:
         return 0xF0;//210 apple
      case 0x00D2:
         return 0xF1;//211 Ograve (Ò)
      case 0x00DA:
         return 0xF2;//212 Uacute (Ú)
      case 0x00DB:
         return 0xF3;//213 Ucircumflex (Û)
      case 0x00D9:
         return 0xF4;//214 Ugrave (Ù)
      case 0x0131:
         return 0xF5;//215 dotlessi (ı)
      case 0x02C6:
         return 0xF6;//216 circumflex (ˆ)
      case 0x02DC:
         return 0xF7;//217 tilde (˜)
      case 0x00AF:
         return 0xF8;//218 macron (¯)
      case 0x02D8:
         return 0xF9;//219 breve (˘)
      case 0x02D9:
         return 0xFA;//220 dotaccent (˙)
      case 0x02DA:
         return 0xFB;//221 ring (˚)
      case 0x00B8:
         return 0xFC;//222 cedilla (¸)
      case 0x02DD:
         return 0xFD;//223 hungarumlaut (˝)
      case 0x02DB:
         return 0xFE;//224 ogonek (˛)
      case 0x02C7:
         return 0xFF;//225 caron (ˇ)
      //Wo kommen die her? PDF-Doku?
      /*case 'Ł': return 0x00;//226 Lslash
      case 'ł': return 0x01;//227 lslash
      case 'Š': return 0x02;//228 Scaron
      case 'š': return 0x03;//229 scaron
      case 'Ž': return 0x04;//230 Zcaron
      case 'ž': return 0x05;//231 zcaron
      case '¦': return 0x06;//232 brokenbar
      case 'Ð': return 0x07;//233 Eth
      case 'ð': return 0x08;//234 eth
      case 'Ý': return 0x09;//235 Yacute
      case 'ý': return 0x0A;//236 yacute
      case 'Þ': return 0x0B;//237 Thorn
      case 'þ': return 0x0C;//238 thorn
      case '−': return 0x0D;//239 minus
      case '×': return 0x0E;//240 multiply
      case '¹': return 0x0F;//241 onesuperior
      	*/
      default: //Buchstabe nicht bekannt
         return 0;
   }
}


CharArray MacRomanDecoder::Decode(const char* cstring)
{
   // Determine length
   uint32 length = 0;
   while(cstring[length] != 0)length++;

   CharArray array = CharArray(length);

   for(uint32 a = 0; a < length; a++)
   {
      array.buffer[a] = DecodeCharacter(cstring[a]);
   }

   return array;
}

ByteArray MacRomanDecoder::Encode(const CharArray &string)
{
   // The number of encoded bytes remains the same.
   ByteArray cstring = ByteArray(string.length, 0);

   for(Integer a = 0; a < string.length; a++)
   {
      cstring[a] = EncodeCharacter(string.buffer[a].unicode());
   }

   return cstring;
}
