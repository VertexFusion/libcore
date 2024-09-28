////////////////////////////////////////////////////////////////////////////////////////////////////
// Name:        String.cpp
// Library:     Jameo Core Library
// Purpose:     Implementation of String class
//
// Author:      Uwe Runtemund (2014-today)
// Modified by:
// Created:     08.10.2012
//
// Copyright:   (c) 2012 Jameo Software, Germany. https://jameo.de
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

#include "Precompiled.hpp"

using namespace std;
using namespace jm;

String::String(): Object(), Comparable<String>(),
mArrLength(16),
mStrLength(0),
mHash(0)
{
   mValue = new Char[mArrLength];
}

String::String(const uint16* buffer, int64 size): Object(), Comparable<String>(),
mHash(0)
{
   CharArray array = CharArray(size);
   memcpy(array.buffer, buffer, sizeof(Char) * size);
   copy(array);
}

String::String(const String& another): Object(), Comparable<String>(),
mArrLength(another.mArrLength),
mStrLength(another.mStrLength),
mHash(another.mHash)
{
   mValue = new Char[mArrLength];
   memcpy(mValue, another.mValue, sizeof(Char) * mStrLength);
}

String::String(const char* buffer, int64 size): Object(), Comparable<String>(),
mHash(0)
{
   char* cstring = new char[size + 1];
   memcpy(cstring, buffer, size);
   cstring[size] = 0;

   // Intentionally not used Charset::GetDefault, since this leads to problems with global strings.
   // (Initialization sequence not predictable)
   UTF8Decoder dec = UTF8Decoder();
   CharArray array = dec.decode(cstring);
   copy(array);

   delete[] cstring;
}

String::String(const char* buffer, int64 size, Charset* charset): Object(), Comparable<String>(),
mHash(0)
{
   char* cstring = new char[size + 2];
   memcpy(cstring, buffer, size);
   cstring[size] = 0;
   cstring[size + 1] = 0; //For UTF16 required
   CharArray array = charset->decode(cstring);
   copy(array);
   delete[] cstring;
}

String::String(const char* cstring): Object(), Comparable<String>(),
mHash(0)
{
   if(cstring != nullptr)
   {
      // Intentionally not used Charset::GetDefault, since this leads to problems with global
      // strings. (Initialization sequence not predictable)
      UTF8Decoder dec = UTF8Decoder();
      CharArray array = dec.decode(cstring);
      copy(array);
   }
   else
   {
      mStrLength = 0;
      mArrLength = 16;
      mValue = new Char[mArrLength];
   }
}

String::String(const ByteArray& buffer) : Object(), Comparable<String>(),
mHash(0)
{
   if(buffer.size() > 0)
   {
      // Intentionally not used Charset::GetDefault, since this leads to problems with global
      // strings. (Initialization sequence not predictable)
      UTF8Decoder dec = UTF8Decoder();
      CharArray array = dec.decode(buffer.constData());
      copy(array);
   }
   else
   {
      mStrLength = 0;
      mArrLength = 16;
      mValue = new Char[mArrLength];
   }
}

String::String(const char* cstring, Charset* charset): Object(), Comparable<String>(),
mHash(0)
{
   CharArray array = charset->decode(cstring);
   copy(array);
}

String::String(const ByteArray& buffer, Charset* charset) : Object(), Comparable<String>(),
mHash(0)
{
   CharArray array = charset->decode(buffer.constData());
   copy(array);
}

String::~String()
{
   mHash = 0;
   mStrLength = 0;
   mArrLength = 0;
   delete[] mValue;
   mValue = nullptr;
}

void String::copy(const CharArray& array)
{
   mStrLength = array.length;
   mArrLength = mStrLength;
   uint32 mod = mArrLength % 16;
   if(mod != 0)mArrLength += 16 - mod;
   mValue = new Char[mArrLength];
   memcpy(mValue, array.buffer, 2 * mStrLength);
}

void String::checkCapacity(int64 more)
{
   if(mStrLength + more < mArrLength)return;

   //Vergrößere
   int64 newLength = mStrLength + more;
   int64 mod = newLength % 16;
   if(mod != 0)newLength += 16 - mod;
   mArrLength = newLength;
   Char* tmp = new Char [mArrLength];
   memcpy(tmp, mValue, 2 * mStrLength);
   delete[] mValue;
   mValue = tmp;
}

#ifdef __APPLE__

String String::fromCFString(CFStringRef cfstring)
{
   // NULL string?
   if(cfstring == nullptr)return kEmptyString;

   // Empty string?
   CFIndex length = CFStringGetLength(cfstring);
   if(length == 0) return kEmptyString;

   // C-String
   const char* ccstr = CFStringGetCStringPtr(cfstring, kCFStringEncodingUTF8);
   if(ccstr != nullptr)return String(ccstr);

   // Fallback
   char* cstr = new char[length *
                                2]; //Hope, that not all characters are greater than 4 bytes representation
   CFStringGetCString(cfstring, cstr, length * 2, kCFStringEncodingUTF8);
   String result = String(cstr);
   delete[] cstr;

   return result;
}

CFStringRef String::toCFString()const
{
   ByteArray cstring = toCString();
   CFStringRef cfstring = CFStringCreateWithCString(kCFAllocatorDefault,
                          cstring.constData(),
                          kCFStringEncodingUTF8);
   return cfstring;
}

#endif

int64 String::size() const
{
   return mStrLength;
}

ByteArray String::toCString() const
{
   return toCString(Charset::getDefault());
}

ByteArray String::toCString(Charset* charset) const
{
   CharArray array = CharArray(mStrLength);
   memcpy(array.buffer, mValue, mStrLength * 2);
   return charset->encode(array);
}


uint16* String::toWString() const
{
   uint16* ret = new uint16 [mStrLength + 1];
   memcpy(ret, mValue, mStrLength * 2);
   ret[mStrLength] = 0;
   return ret;
}

bool String::startsWith(const String& another) const
{
   if(another.mStrLength > mStrLength)return false;

   for(int64 a = 0; a < another.mStrLength; a++)
   {
      if(mValue[a] != another.mValue[a])return false;
   }

   return true;
}


bool String::endsWith(const String& another) const
{
   if(another.mStrLength > mStrLength)return false;

   for(int64 a = 1; a <= another.mStrLength; a++)
   {
      if(mValue[mStrLength - a] != another.mValue[another.mStrLength - a])return false;
   }

   return true;
}

bool String::atIs(int64 position, const String& another)
{
   if(position + another.mStrLength > mStrLength)return false;

   for(int64 a = 0; a < another.mStrLength; a++)
   {
      if(mValue[a + position] != another.mValue[a])return false;
   }

   return true;
}

bool String::atIsIgnoreCase(int64 position, const String& another)
{
   if(position + another.mStrLength > mStrLength)return false;

   for(int64 a = 0; a < another.mStrLength; a++)
   {
      Char c1 = mValue[a + position].toLowerCase();
      Char c2 = another.mValue[a].toLowerCase();
      if(c1 != c2)return false;
   }

   return true;
}

int64 String::hashCode()
{
   if(mHash != 0)return mHash;
   uint32 hash = 0;
   for(int32 a = 0; a < mStrLength; a++)hash = (hash << 5) - hash + mValue[a].unicode();
   mHash = (int32) hash;
   return hash;
}

int64 String::constHashCode() const
{
   if(mHash != 0)return mHash;
   uint32 hash = 0;
   for(int32 a = 0; a < mStrLength; a++)hash = (hash << 5) - hash + mValue[a].unicode();
   return hash;
}

String String::toLowerCase() const
{
   String ret = *this;

   for(int64 a = 0; a < mStrLength; a++)
   {
      ret.mValue[a] = ret.mValue[a].toLowerCase();;
   }

   return ret;
}

String String::toUpperCase() const
{
   String ret = *this;

   for(int64 a = 0; a < mStrLength; a++)
   {
      ret.mValue[a] = ret.mValue[a].toUpperCase();
   }

   return ret;
}

String String::trim() const
{
   int64 beginIndex = 0;
   int64 endIndex = mStrLength;

   if(mStrLength == 0)return kEmptyString;

   //Von links
   while(beginIndex < mStrLength && mValue[beginIndex].isWhitespace())beginIndex++;

   //Von rechts
   while(endIndex > 0 && mValue[endIndex - 1].isWhitespace())endIndex--;

   if(endIndex <= beginIndex)return kEmptyString;

   return substring(beginIndex, endIndex);
}

int64 String::indexOf(Char character) const
{
   return indexOf(character, 0);
}

int64 String::indexOf(const String& str) const
{
   return indexOf(str, 0);
}

int64 String::indexOf(Char character, int64 fromIndex) const
{
   if(fromIndex < 0)fromIndex = 0;

   for(int64 a = fromIndex; a < mStrLength; a++)
   {
      if(mValue[a] == character)return a;
   }
   return -1;
}

int64 String::indexOf(const String& str, int64 fromIndex) const
{
   if(fromIndex < 0)fromIndex = 0;

   for(int64 a = fromIndex; a < mStrLength; a++)
   {
      bool found = true;
      for(int64 b = 0 ; b < str.mStrLength; b++)
      {
         if(mValue[a + b] != str.mValue[b])
         {
            found = false;
            break;
         }
      }
      if(found)return a;
   }
   return -1;
}

int64 String::lastIndexOf(Char character) const
{
   return lastIndexOf(character, mStrLength - 1);
}

int64 String::lastIndexOf(const String& str) const
{
   return lastIndexOf(str, mStrLength - 1);
}

int64 String::lastIndexOf(Char character, int64 fromIndex) const
{
   if(fromIndex >= mStrLength)
      throw Exception(Tr("Index out of Bounds: %1").arg(fromIndex));
   if(fromIndex < 0)fromIndex = 0;
   if(fromIndex > mStrLength - 1)fromIndex = mStrLength - 1;

   for(int64 a = fromIndex; a >= 0; a--)
   {
      if(mValue[a] == character)return a;
   }
   return -1;
}

int64 String::lastIndexOf(const String& str, int64 fromIndex) const
{
   int64 begin = mStrLength - str.mStrLength;
   fromIndex = (fromIndex > begin) ? begin : fromIndex;

   for(int64 a = fromIndex; a >= 0; a--)
   {
      bool found = true;
      for(int64 b = 0 ; b < str.mStrLength; b++)
      {
         if(mValue[a + b] != str.mValue[b])
         {
            found = false;
            break;
         }
      }
      if(found)return a;
   }
   return -1;
}


String String::replace(Char oldChar, Char newChar) const
{
   String ret = String(*this);

   for(int64 a = 0; a < mStrLength; a++)
   {
      if(ret.mValue[a] == oldChar)ret.mValue[a] = newChar;
   }

   return ret;
}

String String::replace(const String& oldStr,const String& newStr)const
{
   int64 pos1 = 0;
   int64 pos2 = indexOf(oldStr);
   if(pos2 < 0)return *this;

   String output;

   do
   {
      // Append everything in front
      output.append(substring(pos1, pos2));

      // Append new string
      output.append(newStr);

      pos1 = pos2 + oldStr.size();
      pos2 = indexOf(oldStr, pos1);

   }
   while(pos2 >= pos1);

   // Append last part.
   output.append(substring(pos1));

   return output;
}


String String::reverse() const
{
   String ret = String(*this);
   int64 cnt = mStrLength / 2;
   int64 last = mStrLength - 1;
   for(int64 a = 0; a < cnt; a++)
   {
      Char tmp = ret.mValue[a];
      ret.mValue[a] = ret.mValue[last];
      ret.mValue[last] = tmp;
      last--;
   }

   return ret;
}

StringList String::split(Char character)
{
   StringList result;
   String delim;
   delim << character;
   StringTokenizer st(*this, delim, false);
   while(st.hasNext())result << st.next();

   return result;
}


Char String::charAt(int64 index) const
{
   if(index < 0 || index >= mStrLength)
      throw Exception(Tr("Index out of Bounds: %1 of %2").arg(index).arg(mStrLength));

   return mValue[index];
}

void String::setCharAt(int64 index, Char character)
{
   if(index < 0 || index >= mStrLength)
      throw Exception(Tr("Index out of Bounds: %1 of %2").arg(index).arg(mStrLength));

   mValue[index] = character;
   mHash = 0;
}

void String::append(const String& another)
{
   if(another.mStrLength == 0)return;
   checkCapacity(another.mStrLength);
   memcpy(&mValue[mStrLength], &another.mValue[0], sizeof(Char) * another.mStrLength);
   mStrLength += another.mStrLength;
   mHash = 0;
}

void String::append(Char utf8char)
{
   checkCapacity(1);
   mValue[mStrLength] = utf8char;
   mStrLength++;
   mHash = 0;
}

void String::insert(int64 index, Char character)
{
   if(index < 0 || index > mStrLength)
      throw Exception(Tr("Index out of Bounds: %1 of %2").arg(index).arg(mStrLength));
   checkCapacity(1);
   for(int64 a = mStrLength; a > index; a--)mValue[a] = mValue[a - 1];
   mValue[index] = character;
   mStrLength++;
   mHash = 0;
}

void String::insert(int64 index, const String& str)
{
   if(index < 0 || index > mStrLength)
      throw Exception(Tr("Index out of Bounds: %1 of %2").arg(index).arg(mStrLength));

   int64 len = str.size();
   checkCapacity(len);

   for(int64 a = mStrLength; a > index; a--)mValue[a + len - 1] = mValue[a - 1];

   for(int64 a = 0; a < len; a++)mValue[index + a] = str.charAt(a);

   mStrLength += len;
   mHash = 0;
}

void String::deleteCharAt(int64 index)
{
   if(index < 0 || index >= mStrLength)
      throw Exception(Tr("Index out of Bounds: %1 of %2").arg(index).arg(mStrLength));

   for(int64 a = index ; a < mStrLength - 1; a++)
   {
      mValue[a] = mValue[a + 1];
   }
   mStrLength--;
   mHash = 0;
}

void String::deleteCharRangeAt(int64 index, int64 length)
{
   if(index < 0 || index > mStrLength)
      throw Exception(Tr("Index out of Bounds: %1 of %2").arg(index).arg(mStrLength));

   for(int64 a = index ; a < mStrLength - length; a++)
   {
      mValue[a] = mValue[a + length];
   }
   mStrLength -= length;
   mHash = 0;
}

int64 String::count(Char character)const
{
   int64 count = 0;

   for(int64 index = 0; index < mStrLength; index++)
   {
      if(mValue[index] == character)count++;
   }

   return count;
}


void String::clear()
{
   zero();
   if(mArrLength > 16)
   {
      delete[] mValue;
      mArrLength = 16;
      mValue = new Char[mArrLength];
   }
}

void String::zero()
{
   mStrLength = 0;
   mHash = 0;
}


bool String::equals(const Object* other) const
{
   const String* str = dynamic_cast<const String*>(other);
   if(str == nullptr)return false;

   return str->equals(*this);
}

bool String::equals(const String& another) const
{
   if(mStrLength != another.mStrLength)return false;

   uint32 cnt = 0;
   while(cnt < mStrLength)
   {
      if(mValue[cnt] != another.mValue[cnt])return false;
      cnt++;
   }

   return true;
}

bool String::equalsIgnoreCase(const String& another) const
{
   if(mStrLength != another.mStrLength)return false;

   uint32 cnt = 0;
   while(cnt < mStrLength)
   {
      Char c1 = mValue[cnt].toLowerCase();
      Char c2 = another.mValue[cnt].toLowerCase();
      if(c1 != c2)return false;
      cnt++;
   }

   return true;
}

int32 String::compareTo(const String& another) const
{
   int64 smallest = std::min(mStrLength, another.mStrLength);

   int64 cnt = 0;
   while(cnt < smallest)
   {
      Char c1 = mValue[cnt];
      Char c2 = another.mValue[cnt];
      if(c1 < c2)return -1;
      if(c1 > c2)return 1;
      cnt++;
   }

   if(mStrLength < another.mStrLength)return -1;
   if(mStrLength > another.mStrLength)return 1;

   return 0;

}

int32 String::compareFancyTo(const String& another) const
{
   //Wandle String in 32bit-Zahlen um, wobei Nummernbestandteile direkt umgewandelt werden.
   uint32 str1[256];
   uint32 str2[256];

   int64 strl1 = std::min(mStrLength, (int64)256);
   int64 strl2 = std::min(another.mStrLength, (int64)256);

   uint32 l1, l2;

   //Konvertiere 1. String
   uint32 cntin = 0;
   uint32 cntout = 0;
   while(cntin < strl1)
   {
      if(mValue[cntin].isDigit())
      {
         uint32 number = mValue[cntin].digitValue();
         while(cntin + 1 < strl1 && mValue[cntin + 1].isDigit())
         {
            cntin++;
            number *= 10;
            number += mValue[cntin].digitValue();
         }
         str1[cntout] = number;
      }
      else str1[cntout] = mValue[cntin].unicode();

      cntin++;
      cntout++;
   }
   l1 = cntout;

   // Convert 2nd String
   cntin = 0;
   cntout = 0;
   while(cntin < strl2)
   {
      if(another.mValue[cntin].isDigit())
      {
         uint32 number = another.mValue[cntin].digitValue();
         while(cntin + 1 < strl2 && another.mValue[cntin + 1].isDigit())
         {
            cntin++;
            number *= 10;
            number += another.mValue[cntin].digitValue();
         }
         str2[cntout] = number;
      }
      else str2[cntout] = another.mValue[cntin].unicode();

      cntin++;
      cntout++;
   }
   l2 = cntout;

   // Compare
   uint32 smallest = std::min(l1, l2);

   uint32 cnt = 0;
   while(cnt < smallest)
   {
      uint32 c1 = str1[cnt];
      uint32 c2 = str2[cnt];
      if(c1 < c2)return -1;
      if(c1 > c2)return 1;
      cnt++;
   }

   if(l1 < l2)return -1;
   if(l1 > l2)return 1;

   return 0;
}


String String::substring(int64 beginIndex, int64 endIndex) const
{

   if(endIndex < beginIndex)throw Exception(Tr("End index is before start index."));
   if(beginIndex < 0)beginIndex = 0;
   if(endIndex > mStrLength) endIndex = mStrLength;
   int64 sublength = endIndex - beginIndex;
   String ret;

   if(sublength > 0)
   {
      ret.checkCapacity(sublength);
      memcpy(&ret.mValue[0], &mValue[beginIndex], sizeof(Char) * sublength);
      ret.mStrLength = sublength;
   }

   return ret;
}

String String::substring(int64 beginIndex) const
{
   return substring(beginIndex, mStrLength);
}

bool String::argIndicies(int64& first, int64& second)
{
   if(indexOf(Char('%')) < 0)return false;

   int64 lowest = 100;

   for(int64 index = 0; index < mStrLength - 1; index++)
   {
      if(charAt(index) == Char('%') && charAt(index + 1).isDigit())
      {
         int64 number = charAt(index + 1).digitValue();
         if(index + 2 < mStrLength && charAt(index + 2).isDigit())
         {
            number *= 10;
            number += charAt(index + 2).digitValue();
         }
         if(number < lowest)
         {
            first = index;
            second = index + 2;
            if(number > 9)second++;
            lowest = number;
         }
      }
   }

   return true;
}

String String::arg(Char character,
                   int64 fieldWidth,
                   Char fillchar)
{
   int64 first, second;
   bool found = argIndicies(first, second);
   if(!found)return *this;

   String result = substring(0, first);

   // Leading space if fieldWidth > 0
   if(fieldWidth > 0)
   {
      for(int64 a = 1; a < fieldWidth; a++)result << fillchar;
   }

   result << character;

   // Trailing space if flg1 < 0
   if(fieldWidth < 0)
   {
      fieldWidth = abs(fieldWidth);
      for(int64 a = 1; a < fieldWidth; a++)result << fillchar;
   }

   result << substring(second);

   return result;
}


String String::arg(int64 value,
                   int64 fieldWidth,
                   Char fillchar)
{
   int64 first, second;
   bool found = argIndicies(first, second);
   if(!found)return *this;

   String result = substring(0, first);

   String s = String::valueOf(value);

   // Leading space if fieldWidth > 0
   if(fieldWidth > 0)
   {
      for(int64 a = s.size(); a < fieldWidth; a++)result << fillchar;
   }

   result << s;

   // Trailing space if flg1 < 0
   if(fieldWidth < 0)
   {
      fieldWidth = abs(fieldWidth);
      for(int64 a = s.size(); a < fieldWidth; a++)result << fillchar;
   }

   result << substring(second);

   return result;
}

String String::arg(int32 value,
                   int64 fieldWidth,
                   Char fillchar)
{
   return arg(static_cast<int64>(value), fieldWidth, fillchar);
}

String String::arg(uint32 value,
                   int64 fieldWidth,
                   Char fillchar)
{
   return arg(static_cast<int64>(value), fieldWidth, fillchar);
}

String String::arg(uint64 value,
                   int64 fieldWidth,
                   Char fillchar)
{
   return arg(static_cast<int64>(value), fieldWidth, fillchar);
}

String String::arg(const String& value,
                   int64 fieldwidth,
                   Char fillchar)
{
   int64 first, second;
   bool found = argIndicies(first, second);
   if(!found)return *this;

   String result = substring(0, first);

   // Leading space if fieldWidth > 0
   if(fieldwidth > 0)
   {
      for(int64 a = value.size(); a < fieldwidth; a++)result << fillchar;
   }

   result << value;

   // Trailing space if flg1 < 0
   if(fieldwidth < 0)
   {
      fieldwidth = std::abs(fieldwidth);
      for(int64 a = value.size(); a < fieldwidth; a++)result << fillchar;
   }


   result << substring(second);

   return result;

}


String String::arg(double value,
                   int64 fieldWidth,
                   int64 precision,
                   Char fillchar)
{
   int64 first, second;
   bool found = argIndicies(first, second);
   if(!found)return *this;

   String result = substring(0, first);

   bool cutzero = precision < 0;
   if(cutzero)precision = 10;

   String s = String::valueOf(value, precision, cutzero);

   // Leading space if fieldWidth > 0
   if(fieldWidth > 0)
   {
      for(int64 a = s.size(); a < fieldWidth; a++)result << fillchar;
   }

   result << s;

   // Trailing space if flg1 < 0
   if(fieldWidth < 0)
   {
      fieldWidth = std::abs(fieldWidth);
      for(int64 a = s.size(); a < fieldWidth; a++)result << fillchar;
   }


   result << substring(second);

   return result;
}

String String::valueOf(int64 number)
{
   String ret;
   bool neg = false;

   // Check sign
   if(number < 0)
   {
      number *= -1;
      neg = true;
   }
   // Check 0
   else if(number == 0)
   {
      ret.append('0');
   }

   // Solve the individual digits... Attention: the last digit comes first
   while(number > 0)
   {
      int64 digit = number % 10;
      number = number / 10;
      ret.append(Char(digit + '0'));
   }
   if(neg)ret.append('-');

   // Reverse digits
   int64 cnt = ret.size() / 2;
   for(int64 a = 0; a < cnt; a++)
   {
      Char s1 = ret.charAt(a);
      Char s2 = ret.charAt(ret.size() - 1 - a);
      ret.setCharAt(a, s2);
      ret.setCharAt(ret.size() - 1 - a, s1);
   }
   return ret;
}

String String::valueOf(uint64 number)
{
   String ret;

   // Check 0
   if(number == 0)
   {
      ret.append('0');
      return ret;
   }

   // Solve the individual digits... Attention: the last digit comes first
   while(number > 0)
   {
      int64 digit = number % 10;
      number = number / 10;
      ret.append(Char(digit + '0'));
   }

   // Reverse digits
   int64 cnt = ret.size() / 2;
   for(int64 a = 0; a < cnt; a++)
   {
      Char s1 = ret.charAt(a);
      Char s2 = ret.charAt(ret.size() - 1 - a);
      ret.setCharAt(a, s2);
      ret.setCharAt(ret.size() - 1 - a, s1);
   }
   return ret;
}

String String::valueOf(int32 number)
{
   return valueOf((int64) number);
}

String String::valueOf(uint32 number)
{
   return valueOf((int64) number);
}

String String::valueOf(double number)
{
   std::stringstream ss;
   ss << std::setprecision(10) << number;
   std::string str = ss.str();
   const char* cstr = str.c_str();
   return String(cstr);
}

String String::valueOf(double number, int64 precision, bool trunc)
{
   bool neg = jm::isLess(number, 0.0);
   int64 before = static_cast<int64>(number);
   if(neg)before *= -1;

   double factor = std::pow(10, precision);

   number = std::fmod(number, 1.0) * 10 * factor;
   int64 after = std::abs(number);

   //Runden
   int64 rnd = after % 10;
   after = after / 10;
   if(rnd >= 5)after++;
   if(after == factor)
   {
      after = 0;
      before++;
   }

   String b = String::valueOf(before);
   if(neg)b.insert(0, '-');

   String a = String::valueOf(after);
   while(a.size() < precision)a.insert(0, '0');

   while(trunc && a.size() > 1 && a.charAt(a.size() - 1) == '0')a.deleteCharAt(a.size() - 1);

   if(after != 0 || trunc == false)return b + "," + a;
   else return b;
}


String String::valueOf(bool value)
{
   return value ? "true" : "false";
}

bool String::toBool() const
{
   return equalsIgnoreCase("true");
}

double String::toDouble() const
{
   jm::ByteArray cstr = toCString();
   std::stringstream ss;
   double d = 0.0;
   ss << cstr.constData();
   ss >> d;
   return d;
}


int64 String::toInt() const
{
   int64 val = 0;
   bool neg = false;

   for(int64 a = 0; a < size(); a++)
   {
      jm::Char c = charAt(a);

      if(c.isDigit())
      {
         val *= 10;
         val += c.digitValue();
      }
      else if(c == '-')neg = true;
      else throw jm::Exception("Number format exception for input string: \"" + *this + "\"");
   }

   if(neg)val *= -1;
   return val;
}

String String::lineSeparator()
{
   #ifdef __APPLE__//macOS, iOS
   return "\n";
   #elif defined __linux__ //Linux
   return "\n";
   #elif defined _WIN32//Windows
   return "\r\n";
   #endif
}

Charset* gConsoleCharset = nullptr;

void jm::String::setConsoleCharset(Charset* cs)
{
   gConsoleCharset = cs;
}

bool jm::operator!=(String const& v1, String const& v2)
{
   return !v1.equals(v2);
}


bool jm::operator==(String const& v1, String const& v2)
{
   return v1.equals(v2);
}

namespace jm
{

   ostream& operator << (ostream& out, const String& str)
   {
      //\todo It is best to set and get the charset globally. It's inefficient that way
      if(gConsoleCharset == nullptr)gConsoleCharset = Charset::forName("Windows-1252");
      String s = str;
      ByteArray cstr = s.toCString(gConsoleCharset);
      out << cstr.constData();
      return out;
   }

   istream& operator>> (istream& in, String& str)
   {
      char cstr[256];
      in.getline(cstr, 256);
      str = String(cstr, (uint32)in.gcount());
      return in;
   }

   String& operator << (String& out, const String& str)
   {
      out.append(str);
      return out;
   }

   String& operator << (String& out, const int64& i)
   {
      out.append(String::valueOf(i));
      return out;
   }

   String& operator << (String& out, const uint64& i)
   {
      out.append(String::valueOf(i));
      return out;
   }

   String& operator << (String& out, const int32& i)
   {
      out.append(String::valueOf(i));
      return out;
   }

   String& operator << (String& out, const uint32& i)
   {
      out.append(String::valueOf(i));
      return out;
   }

   String& operator << (String& out, const double& i)
   {
      out.append(String::valueOf(i));
      return out;
   }

   String& operator << (String& out, const char& i)
   {
      out.append(i);
      return out;
   }

   String& operator << (String& out, const Char& i)
   {
      out.append(i);
      return out;
   }

   String& String::operator=(const String& another)
   {
      if(this != &another)
      {
         delete[] mValue;
         mStrLength = another.mStrLength;
         mArrLength = another.mArrLength;
         mValue = new Char[mArrLength];
         memcpy(mValue, another.mValue, sizeof(Char) * mStrLength);
      }

      return *this;
   }

   String& String::operator+=(const String& another)
   {
      this->append(another);
      return *this;
   }

   String operator+(const String& left, const String& right)
   {
      String ret = left;
      ret.append(right);
      return ret;
   }

   String operator+(const char*& left, const String& right)
   {
      String ret = left;
      ret.append(right);
      return ret;
   }

   String operator+(const String& left, const char*& right)
   {
      String ret = left;
      ret.append(right);
      return ret;
   }

   String operator+(int64& left, const String& right)
   {
      String ret = String::valueOf(left);
      ret.append(right);
      return ret;
   }

   String operator+(const String& left, int64& right)
   {
      String ret = left;
      ret.append(String::valueOf(right));
      return ret;
   }

   String operator+(double& left, const String& right)
   {
      String ret = String::valueOf(left);
      ret.append(right);
      return ret;
   }

   String operator+(const String& left, double& right)
   {
      String ret = left;
      ret.append(String::valueOf(right));
      return ret;
   }

   String operator+(const int8& left, const String& right)
   {
      String ret;
      ret.append(left);
      ret.append(right);
      return ret;
   }

   String operator+(const String& left, const int8& right)
   {
      String ret = left;
      ret.append(right);
      return ret;
   }

   bool operator<(const String& left, const String& right)
   {
      String str = left;
      return str.compareTo(right) < 0;
   }

}

double jm::ConvertToDouble(String str)
{
   for(uint32 a = 0; a < str.size(); a++)
   {
      if(str.charAt(a) == ',') str.setCharAt(a, '.');
   }
   return str.toDouble();
}

String jm::URLDecode(const String& str)
{
   //
   // A URL-encoded string contains only ASCII characters...
   //

   ByteArray buffer = ByteArray(str.size(), 0);
   uint32 pos = 0;

   // Eliminate URL-Decoding
   int8 c;
   for(uint32 a = 0; a < str.size(); a++)
   {
      switch(str.charAt(a).unicode())
      {
         case '%':
            c = Integer::fromHex(str.substring(a + 1, a + 3)).Int8();
            a += 2;
            buffer[pos++] = c;
            break;

         case '+':
            buffer[pos++] = ' ';
            break;

         default:
            buffer[pos++] = (int8)str.charAt(a).unicode();
            break;
      }
   }
   buffer.resize(pos);
   String ret = String(buffer);
   return ret;
}

String jm::URLEncode(const String& str)
{
   //
   // A URL-encoded string contains only ASCII characters...
   //
   String ret;

   for(uint32 a = 0; a < str.size(); a++)
   {
      switch(str.charAt(a).unicode())
      {
         case ' ':
            ret.append('+');
            break;

         case '%':
            ret.append('%');
            ret.append('2');
            ret.append('5');
            break;

         case '+':
            ret.append('%');
            ret.append('2');
            ret.append('B');
            break;

         default:
            ret.append(str.charAt(a));
            break;
      }
   }

   return ret;
}

