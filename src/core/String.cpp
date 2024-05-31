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

#include "Precompiled.h"

using namespace std;
using namespace jm;

String::String(): Object(), Comparable<String>()
{
   mHash = 0;
   mStrLength = 0;
   mArrLength = 16;
   mValue = new Char[mArrLength];
}

String::String(const uint16* buffer, Integer size): Object(), Comparable<String>()
{
   mHash = 0;
   CharArray array = CharArray(size);
   memcpy(array.buffer, buffer, sizeof(Char) * size);
   Copy(array);
}

String::String(const String &another): Object(), Comparable<String>()
{
   mHash = 0;
   mStrLength = another.mStrLength;
   mArrLength = another.mArrLength;
   mValue = new Char[mArrLength];
   memcpy(mValue, another.mValue, sizeof(Char) * mStrLength);
}

String::String(const int8* buffer, Integer size): Object(), Comparable<String>()
{
   mHash = 0;
   int8* cstring = new int8[size + 1];
   memcpy(cstring, buffer, size);
   cstring[size] = 0;

   // Intentionally not used Charset::GetDefault, since this leads to problems with global strings.
   // (Initialization sequence not predictable)
   UTF8Decoder dec = UTF8Decoder();
   CharArray array = dec.Decode(cstring);
   Copy(array);

   delete[] cstring;
}

String::String(const uint8* buffer, Integer size): Object(), Comparable<String>()
{
   mHash = 0;
   int8* cstring = new int8[size + 1];
   memcpy(cstring, buffer, size);
   cstring[size] = 0;

   // Intentionally not used Charset::GetDefault, since this leads to problems with global strings.
   // (Initialization sequence not predictable)
   UTF8Decoder dec = UTF8Decoder();
   CharArray array = dec.Decode(cstring);
   Copy(array);

   delete[] cstring;
}

String::String(const int8* buffer, Integer size, Charset* charset): Object(), Comparable<String>()
{
   mHash = 0;
   int8* cstring = new int8[size + 2];
   memcpy(cstring, buffer, size);
   cstring[size] = 0;
   cstring[size + 1] = 0; //For UTF16 required
   CharArray array = charset->Decode(cstring);
   Copy(array);
   delete[] cstring;
}

String::String(const int8* cstring): Object(), Comparable<String>()
{
   mHash = 0;
   if(cstring != NULL)
   {
      // Intentionally not used Charset::GetDefault, since this leads to problems with global
      // strings. (Initialization sequence not predictable)
      UTF8Decoder dec = UTF8Decoder();
      CharArray array = dec.Decode(cstring);
      Copy(array);
   }
   else
   {
      mHash = 0;
      mStrLength = 0;
      mArrLength = 16;
      mValue = new Char[mArrLength];
   }
}

String::String(const ByteArray &buffer) : Object(), Comparable<String>()
{
   mHash = 0;
   if(buffer.Size() > 0)
   {
      // Intentionally not used Charset::GetDefault, since this leads to problems with global
      // strings. (Initialization sequence not predictable)
      UTF8Decoder dec = UTF8Decoder();
      CharArray array = dec.Decode(buffer.ConstData());
      Copy(array);
   }
   else
   {
      mHash = 0;
      mStrLength = 0;
      mArrLength = 16;
      mValue = new Char[mArrLength];
   }
}

String::String(const int8* cstring, Charset* charset): Object(), Comparable<String>()
{
   mHash = 0;
   CharArray array = charset->Decode(cstring);
   Copy(array);
}

String::String(const ByteArray &buffer, Charset* charset) : Object(), Comparable<String>()
{
   mHash = 0;
   CharArray array = charset->Decode(buffer.ConstData());
   Copy(array);
}

String::~String()
{
   mHash = 0;
   mStrLength = 0;
   mArrLength = 0;
   delete[] mValue;
   mValue = NULL;
}

void String::Copy(const CharArray &array)
{
   mStrLength = array.length;
   mArrLength = mStrLength;
   uint32 mod = mArrLength % 16;
   if(mod != 0)mArrLength += 16 - mod;
   mValue = new Char[mArrLength];
   memcpy(mValue, array.buffer, 2 * mStrLength);
}

void String::CheckCapacity(Integer more)
{
   if(mStrLength + more < mArrLength)return;

   //Vergrößere
   Integer newLength = mStrLength + more;
   Integer mod = newLength % 16;
   if(mod != 0)newLength += 16 - mod;
   mArrLength = newLength;
   Char* tmp = new Char [mArrLength];
   memcpy(tmp, mValue, 2 * mStrLength);
   delete[] mValue;
   mValue = tmp;
}

#ifdef __APPLE__

String String::FromCFString(CFStringRef cfstring)
{
   // NULL string?
   if(cfstring == NULL)return kEmptyString;

   // Empty string?
   CFIndex length = CFStringGetLength(cfstring);
   if(length == 0) return kEmptyString;

   // C-String
   const char* ccstr = CFStringGetCStringPtr(cfstring, kCFStringEncodingUTF8);
   if(ccstr != NULL)return String(ccstr);

   // Fallback
   char* cstr = new char[length * 2]; //Hope, that not all characters are greater than 4 bytes representation
   CFStringGetCString(cfstring, cstr, length * 2, kCFStringEncodingUTF8);
   String result = String(cstr);
   delete[] cstr;

   return result;
}

CFStringRef String::ToCFString()const
{
   ByteArray cstring = ToCString();
   CFStringRef cfstring = CFStringCreateWithCString(kCFAllocatorDefault,
                          cstring.ConstData(),
                          kCFStringEncodingUTF8);
   return cfstring;
}

#endif

Integer String::Length() const
{
   return mStrLength;
}

ByteArray String::ToCString() const
{
   return ToCString(Charset::GetDefault());
}

ByteArray String::ToCString(Charset* charset) const
{
   CharArray array = CharArray(mStrLength);
   memcpy(array.buffer, mValue, mStrLength * 2);
   return charset->Encode(array);
}


uint16* String::ToWString() const
{
   uint16* ret = new uint16 [mStrLength + 1];
   memcpy(ret, mValue, mStrLength * 2);
   ret[mStrLength] = 0;
   return ret;
}

bool String::StartsWith(const String &another) const
{
   if(another.mStrLength > mStrLength)return false;

   for(Integer a = 0; a < another.mStrLength; a++)
   {
      if(mValue[a] != another.mValue[a])return false;
   }

   return true;
}


bool String::EndsWith(const String &another) const
{
   if(another.mStrLength > mStrLength)return false;

   for(Integer a = 1; a <= another.mStrLength; a++)
   {
      if(mValue[mStrLength - a] != another.mValue[another.mStrLength - a])return false;
   }

   return true;
}

bool String::AtIs(Integer position,const String &another)
{
   if(position+another.mStrLength > mStrLength)return false;

   for(Integer a = 0; a < another.mStrLength; a++)
   {
      if(mValue[a+position] != another.mValue[a])return false;
   }

   return true;
}

bool String::AtIsIgnoreCase(Integer position,const String &another)
{
   if(position+another.mStrLength > mStrLength)return false;

   for(Integer a = 0; a < another.mStrLength; a++)
   {
      Char c1 = mValue[a+position].ToLowerCase();
      Char c2 = another.mValue[a].ToLowerCase();
      if(c1 != c2)return false;
   }

   return true;
}

Integer String::HashCode()
{
   if(mHash != 0)return mHash;
   uint32 hash = 0;
   for(int32 a = 0; a < mStrLength; a++)hash = (hash << 5) - hash + mValue[a].Unicode();
   mHash = (int32) hash;
   return hash;
}

Integer String::ConstHashCode() const
{
   if(mHash != 0)return mHash;
   uint32 hash = 0;
   for(int32 a = 0; a < mStrLength; a++)hash = (hash << 5) - hash + mValue[a].Unicode();
   return hash;
}

String String::ToLowerCase() const
{
   String ret = *this;

   for(Integer a = 0; a < mStrLength; a++)
   {
      ret.mValue[a] = ret.mValue[a].ToLowerCase();;
   }

   return ret;
}

String String::ToUpperCase() const
{
   String ret = *this;

   for(Integer a = 0; a < mStrLength; a++)
   {
      ret.mValue[a] = ret.mValue[a].ToUpperCase();
   }

   return ret;
}

String String::Trim() const
{
   Integer beginIndex = 0;
   Integer endIndex = mStrLength;

   if(mStrLength == 0)return kEmptyString;

   //Von links
   while(beginIndex < mStrLength && mValue[beginIndex].IsWhitespace())beginIndex++;

   //Von rechts
   while(endIndex > 0 && mValue[endIndex - 1].IsWhitespace())endIndex--;

   if(endIndex <= beginIndex)return kEmptyString;

   return Substring(beginIndex, endIndex);
}

Integer String::IndexOf(Char character) const
{
   return IndexOf(character, 0);
}

Integer String::IndexOf(const String &str) const
{
   return IndexOf(str, 0);
}

Integer String::IndexOf(Char character, Integer fromIndex) const
{
   if(fromIndex < 0)fromIndex = 0;

   for(Integer a = fromIndex; a < mStrLength; a++)
   {
      if(mValue[a] == character)return a;
   }
   return -1;
}

Integer String::IndexOf(const String &str, Integer fromIndex) const
{
   if(fromIndex < 0)fromIndex = 0;

   for(Integer a = fromIndex; a < mStrLength; a++)
   {
      bool found = true;
      for(Integer b = 0 ; b < str.mStrLength; b++)
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

Integer String::LastIndexOf(Char character) const
{
   return LastIndexOf(character, mStrLength - 1);
}

Integer String::LastIndexOf(const String &str) const
{
   return LastIndexOf(str, mStrLength - 1);
}

Integer String::LastIndexOf(Char character, Integer fromIndex) const
{
   if(fromIndex >= mStrLength) throw new Exception("Index out of Bounds: " + String::ValueOf(fromIndex));
   if(fromIndex < 0)fromIndex = 0;
   if(fromIndex > mStrLength - 1)fromIndex = mStrLength - 1;

   for(Integer a = fromIndex; a >= 0; a--)
   {
      if(mValue[a] == character)return a;
   }
   return -1;
}

Integer String::LastIndexOf(const String &str, Integer fromIndex) const
{
   Integer begin = mStrLength - str.mStrLength;
   fromIndex = (fromIndex > begin) ? begin : fromIndex;

   for(Integer a = fromIndex; a >= 0; a--)
   {
      bool found = true;
      for(Integer b = 0 ; b < str.mStrLength; b++)
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


String String::Replace(Char oldChar, Char newChar) const
{
   String ret = String(*this);

   for(Integer a = 0; a < mStrLength; a++)
   {
      if(ret.mValue[a] == oldChar)ret.mValue[a] = newChar;
   }

   return ret;
}

String String::ReplaceAll(String oldStr, String newStr)const
{
   Integer pos1 = 0;
   Integer pos2 = IndexOf(oldStr);
   if(pos2 < 0)return *this;

   String output;

   do
   {
      // Append everything in front
      output.Append(Substring(pos1, pos2));

      // Append new string
      output.Append(newStr);

      pos1 = pos2 + oldStr.Length();
      pos2 = IndexOf(oldStr, pos1);

   }
   while(pos2 >= pos1);

   // Append last part.
   output.Append(Substring(pos1));

   return output;
}


String String::Reverse() const
{
   String ret = String(*this);
   Integer cnt = mStrLength / 2;
   Integer last = mStrLength - 1;
   for(Integer a = 0; a < cnt; a++)
   {
      Char tmp = ret.mValue[a];
      ret.mValue[a] = ret.mValue[last];
      ret.mValue[last] = tmp;
      last--;
   }

   return ret;
}

Char String::CharAt(Integer index) const
{
   if(index < 0 || index >= mStrLength)
      throw new Exception("Index out of Bounds: " + String::ValueOf(index));
   return mValue[index];
}

void String::SetCharAt(Integer index, Char character)
{
   if(index < 0 || index >= mStrLength)throw new Exception("Index out of Bounds: " + String::ValueOf(index));
   mValue[index] = character;
   mHash = 0;
}

void String::Append(const String &another)
{
   CheckCapacity(another.mStrLength);
   memcpy(&mValue[mStrLength], &another.mValue[0], sizeof(Char) * another.mStrLength);
   mStrLength += another.mStrLength;
   mHash = 0;
}

void String::Append(Char utf8char)
{
   CheckCapacity(1);
   mValue[mStrLength] = utf8char;
   mStrLength++;
   mHash = 0;
}

void String::Insert(Integer index, Char character)
{
   if(index < 0 || index > mStrLength)throw new Exception("Index out of Bounds: " + String::ValueOf(index));
   CheckCapacity(1);
   for(Integer a = mStrLength; a > index; a--)mValue[a] = mValue[a - 1];
   mValue[index] = character;
   mStrLength++;
   mHash = 0;
}

void String::Insert(Integer index, const String &str)
{
   if(index < 0 || index > mStrLength)throw new Exception("Index out of Bounds: " + String::ValueOf(index));

   Integer len = str.Length();
   CheckCapacity(len);

   for(Integer a = mStrLength; a > index; a--)mValue[a + len - 1] = mValue[a - 1];

   for(Integer a = 0; a < len; a++)mValue[index + a] = str.CharAt(a);

   mStrLength += len;
   mHash = 0;
}

void String::DeleteCharAt(Integer index)
{
   if(index < 0 || index >= mStrLength)throw new Exception("Index out of Bounds: " + String::ValueOf(index));
   for(Integer a = index ; a < mStrLength - 1; a++)
   {
      mValue[a] = mValue[a + 1];
   }
   mStrLength--;
   mHash = 0;
}

void String::DeleteCharRangeAt(Integer index, Integer length)
{
   if(index < 0 || index + length > mStrLength)throw new Exception("Index out of Bounds: " + String::ValueOf(index));
   for(Integer a = index ; a < mStrLength - length; a++)
   {
      mValue[a] = mValue[a + length];
   }
   mStrLength -= length;
   mHash = 0;
}

Integer String::Count(Char character)const
{
   Integer count = 0;

   for (Integer index = 0; index < mStrLength; index++)
   {
      if (mValue[index] == character)count++;
   }

   return count;
}


void String::Clear()
{
   Zero();
   if(mArrLength > 16)
   {
      delete[] mValue;
      mArrLength = 16;
      mValue = new Char[mArrLength];
   }
}

void String::Zero()
{
   mStrLength = 0;
   mHash = 0;
}


bool String::Equals(const Object* other) const
{
   const String* str = dynamic_cast<const String*>(other);
   if(str == NULL)return false;

   return str->Equals(*this);
}

bool String::Equals(const String &another) const
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

bool String::EqualsIgnoreCase(const String &another) const
{
   if(mStrLength != another.mStrLength)return false;

   uint32 cnt = 0;
   while(cnt < mStrLength)
   {
      Char c1 = mValue[cnt].ToLowerCase();
      Char c2 = another.mValue[cnt].ToLowerCase();
      if(c1 != c2)return false;
      cnt++;
   }

   return true;
}

int32 String::CompareTo(const String &another) const
{
   Integer smallest = Min(mStrLength, another.mStrLength);

   Integer cnt = 0;
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

int32 String::CompareFancyTo(const String &another) const
{
   //Wandle String in 32bit-Zahlen um, wobei Nummernbestandteile direkt umgewandelt werden.
   uint32 str1[256];
   uint32 str2[256];

   Integer strl1 = Min(mStrLength, 256u);
   Integer strl2 = Min(another.mStrLength, 256u);

   uint32 l1, l2;

   //Konvertiere 1. String
   uint32 cntin = 0;
   uint32 cntout = 0;
   while(cntin < strl1)
   {
      if(mValue[cntin].IsDigit())
      {
         uint32 number = mValue[cntin].DigitValue();
         while(cntin + 1 < strl1 && mValue[cntin + 1].IsDigit())
         {
            cntin++;
            number *= 10;
            number += mValue[cntin].DigitValue();
         }
         str1[cntout] = number;
      }
      else str1[cntout] = mValue[cntin].Unicode();

      cntin++;
      cntout++;
   }
   l1 = cntout;

   // Convert 2nd String
   cntin = 0;
   cntout = 0;
   while(cntin < strl2)
   {
      if(another.mValue[cntin].IsDigit())
      {
         uint32 number = another.mValue[cntin].DigitValue();
         while(cntin + 1 < strl2 && another.mValue[cntin + 1].IsDigit())
         {
            cntin++;
            number *= 10;
            number += another.mValue[cntin].DigitValue();
         }
         str2[cntout] = number;
      }
      else str2[cntout] = another.mValue[cntin].Unicode();

      cntin++;
      cntout++;
   }
   l2 = cntout;

   // Compare
   uint32 smallest = min(l1, l2);

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


String String::Substring(Integer beginIndex, Integer endIndex) const
{

   if(endIndex < beginIndex)throw new Exception("End index is before start index.");
   if(beginIndex < 0)beginIndex = 0;
   if(endIndex > mStrLength) endIndex = mStrLength;
   Integer sublength = endIndex - beginIndex;
   String ret;

   if(sublength > 0)
   {
      ret.CheckCapacity(sublength);
      memcpy(&ret.mValue[0], &mValue[beginIndex], sizeof(Char) * sublength);
      ret.mStrLength = sublength;
   }

   return ret;
}

String String::Substring(Integer beginIndex) const
{
   return Substring(beginIndex, mStrLength);
}

bool String::ArgIndicies(Integer &first, Integer &second)
{
   if(IndexOf(Char('%'))<0)return false;

   Integer lowest=100;

   for(Integer index=0;index<mStrLength-1;index++)
   {
      if(CharAt(index)==Char('%') && CharAt(index+1).IsDigit())
      {
         Integer number=CharAt(index+1).DigitValue();
         if(index+2<mStrLength&&CharAt(index+2).IsDigit())
         {
            number*=10;
            number+=CharAt(index+2).DigitValue();
         }
         if(number<lowest)
         {
            first=index;
            second=index+2;
            if(number>9)second++;
            lowest=number;
         }
      }
   }

   return true;
}


String String::Arg(Integer value,
                   Integer fieldWidth,
                   Char fillchar)
{
   Integer first,second;
   Bool found = ArgIndicies(first, second);
   if(!found)return *this;

   String result=Substring(0,first);

   String s = String::ValueOf(value);

   // Leading space if fieldWidth > 0
   if(fieldWidth > 0)
   {
      for(Integer a = s.Length(); a < fieldWidth; a++)result << fillchar;
   }

   result<<s;

   // Trailing space if flg1 < 0
   if(fieldWidth < 0)
   {
      fieldWidth = abs(fieldWidth);
      for(Integer a = s.Length(); a < fieldWidth; a++)result << fillchar;
   }

   result<<Substring(second);

   return result;
}

String String::Arg(const String &value,
           Integer fieldwidth,
           Char fillchar)
{
   Integer first,second;
   Bool found = ArgIndicies(first, second);
   if(!found)return *this;

   String result=Substring(0,first);

   // Leading space if fieldWidth > 0
   if(fieldwidth > 0)
   {
      for(Integer a = value.Length(); a < fieldwidth; a++)result << fillchar;
   }

   result << value;

   // Trailing space if flg1 < 0
   if(fieldwidth < 0)
   {
      fieldwidth = fieldwidth.Abs();
      for(Integer a = value.Length(); a < fieldwidth; a++)result << fillchar;
   }


   result<<Substring(second);

   return result;

}


String String::Arg(Double value,
                   Integer fieldWidth,
                   Integer precision,
                   Char fillchar)
{
   Integer first,second;
   Bool found = ArgIndicies(first, second);
   if(!found)return *this;

   String result=Substring(0,first);

   bool cutzero = precision<0;
   if(cutzero)precision=10;

   String s = String::ValueOf(value, precision, cutzero);

   // Leading space if fieldWidth > 0
   if(fieldWidth > 0)
   {
      for(Integer a = s.Length(); a < fieldWidth; a++)result << fillchar;
   }

   result << s;

   // Trailing space if flg1 < 0
   if(fieldWidth < 0)
   {
      fieldWidth = fieldWidth.Abs();
      for(Integer a = s.Length(); a < fieldWidth; a++)result << fillchar;
   }


   result<<Substring(second);

   return result;
}

String String::ValueOf(int64 number)
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
      ret.Append('0');
   }

   // Solve the individual digits... Attention: the last digit comes first
   while(number > 0)
   {
      Integer digit = number % 10;
      number = number / 10;
      ret.Append(Char(digit.Int16() + '0'));
   }
   if(neg)ret.Append('-');

   // Reverse digits
   Integer cnt = ret.Length() / 2;
   for(Integer a = 0; a < cnt; a++)
   {
      Char s1 = ret.CharAt(a);
      Char s2 = ret.CharAt(ret.Length() - 1 - a);
      ret.SetCharAt(a, s2);
      ret.SetCharAt(ret.Length() - 1 - a, s1);
   }
   return ret;
}

String String::ValueOf(uint64 number)
{
   String ret;

   // Check 0
   if(number == 0)
   {
      ret.Append('0');
      return ret;
   }

   // Solve the individual digits... Attention: the last digit comes first
   while(number > 0)
   {
      Integer digit = number % 10;
      number = number / 10;
      ret.Append(Char(digit.Int16() + '0'));
   }

   // Reverse digits
   Integer cnt = ret.Length() / 2;
   for(Integer a = 0; a < cnt; a++)
   {
      Char s1 = ret.CharAt(a);
      Char s2 = ret.CharAt(ret.Length() - 1 - a);
      ret.SetCharAt(a, s2);
      ret.SetCharAt(ret.Length() - 1 - a, s1);
   }
   return ret;
}

String String::ValueOf(int32 number)
{
   return ValueOf((int64) number);
}

String String::ValueOf(uint32 number)
{
   return ValueOf((int64) number);
}

String String::ValueOf(double number)
{
   std::stringstream ss;
   ss << std::setprecision(10) << number;
   std::string str = ss.str();
   const int8* cstr = str.c_str();
   return String(cstr);
}

String String::ValueOf(double number, Integer precision, bool trunc)
{
   bool neg = jm::IsLess(number, 0.0);
   int64 before = static_cast<int64>(number);
   if(neg)before *= -1;

   double factor = std::pow(10, precision.Int32());

   number = std::fmod(number, 1.0) * 10 * factor;
   int64 after = Integer(static_cast<int64>(number)).Abs();

   //Runden
   int64 rnd = after % 10;
   after = after / 10;
   if(rnd >= 5)after++;
   if(after == factor)
   {
      after = 0;
      before++;
   }

   String b = String::ValueOf(before);
   if(neg)b.Insert(0, '-');

   String a = String::ValueOf(after);
   while(a.Length() < precision)a.Insert(0, '0');

   while(trunc && a.Length() > 1 && a.CharAt(a.Length() - 1) == '0')a.DeleteCharAt(a.Length() - 1);

   if(after != 0 || trunc == false)return b + "," + a;
   else return b;
}


String String::ValueOf(bool value)
{
   return value ? "true" : "false";
}

String String::LineSeparator()
{
   #ifdef __APPLE__//macOS, iOS
   return "\n";
   #elif defined __linux__ //Linux
   return "\n";
   #elif defined _WIN32//Windows
   return "\r\n";
   #endif
}

Charset* gConsoleCharset = NULL;

void jm::String::SetConsoleCharset(Charset* cs)
{
   gConsoleCharset = cs;
}

bool jm::operator!=(String const &v1, String const &v2)
{
   return !v1.Equals(v2);
}


bool jm::operator==(String const &v1, String const &v2)
{
   return v1.Equals(v2);
}

namespace jm
{

   ostream &operator << (ostream &out, const String &str)
   {
      //\todo It is best to set and get the charset globally. It's inefficient that way
      if(gConsoleCharset == NULL)gConsoleCharset = Charset::ForName("Windows-1252");
      String s = str;
      ByteArray cstr = s.ToCString(gConsoleCharset);
      out << cstr.ConstData();
      return out;
   }

   istream& operator>> (istream& in, String& str)
   {
      char cstr[256];
      in.getline(cstr, 256);
      str = String(cstr, (uint32)in.gcount());
      return in;
   }

   String& operator << (String &out, const String &str)
   {
      out.Append(str);
      return out;
   }

   String& operator << (String& out, const Integer& i)
   {
      out.Append(String::ValueOf(i));
      return out;
   }

   String& operator << (String& out, const uint64& i)
   {
      out.Append(String::ValueOf(i));
      return out;
   }

   String &operator << (String &out, const int64 &i)
   {
      out.Append(String::ValueOf(i));
      return out;
   }

   String &operator << (String &out, const int32 &i)
   {
      out.Append(String::ValueOf(i));
      return out;
   }

   String &operator << (String &out, const uint32 &i)
   {
      out.Append(String::ValueOf(i));
      return out;
   }

   String &operator << (String &out, const double &i)
   {
      out.Append(String::ValueOf(i));
      return out;
   }

   String &operator << (String &out, const char &i)
   {
      out.Append(i);
      return out;
   }

   String &operator << (String &out, const Char &i)
   {
      out.Append(i);
      return out;
   }

   String& String::operator=(const String &another)
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

   String &String::operator+=(const String &another)
   {
      this->Append(another);
      return *this;
   }

   String operator+(const String &left, const String &right)
   {
      String ret = left;
      ret.Append(right);
      return ret;
   }

   String operator+(const int8* &left, const String &right)
   {
      String ret = left;
      ret.Append(right);
      return ret;
   }

   String operator+(const String &left, const int8* &right)
   {
      String ret = left;
      ret.Append(right);
      return ret;
   }

   String operator+(int64 &left, const String &right)
   {
      String ret = String::ValueOf(left);
      ret.Append(right);
      return ret;
   }

   String operator+(const String &left, int64 &right)
   {
      String ret = left;
      ret.Append(String::ValueOf(right));
      return ret;
   }

   String operator+(double &left, const String &right)
   {
      String ret = String::ValueOf(left);
      ret.Append(right);
      return ret;
   }

   String operator+(const String &left, double &right)
   {
      String ret = left;
      ret.Append(String::ValueOf(right));
      return ret;
   }

   String operator+(const int8 &left, const String &right)
   {
      String ret;
      ret.Append(left);
      ret.Append(right);
      return ret;
   }

   String operator+(const String &left, const int8 &right)
   {
      String ret = left;
      ret.Append(right);
      return ret;
   }

   bool operator<(const String &left, const String &right)
   {
      String str = left;
      return str.CompareTo(right) < 0;
   }

}

double jm::StrToDouble(const String &str)
{
   ByteArray cstr = str.ToCString();
   std::stringstream ss;
   double d = 0;
   ss << cstr.ConstData();
   ss >> d;
   return d;
}

double jm::ConvertToDouble(String str)
{
   for(uint32 a = 0; a < str.Length(); a++)
   {
      if(str.CharAt(a) == ',') str.SetCharAt(a, '.');
   }
   return StrToDouble(str);
}

String jm::URLDecode(const String &str)
{
   //
   // A URL-encoded string contains only ASCII characters...
   //

   int8* buffer = new int8[str.Length()];
   uint32 pos = 0;

   // Eliminate URL-Decoding
   int8 c;
   for(uint32 a = 0; a < str.Length(); a++)
   {
      switch(str.CharAt(a).Unicode())
      {
         case '%':
            c = Integer::FromHex(str.Substring(a + 1, a + 3)).Int8();
            a += 2;
            buffer[pos++] = c;
            break;

         case '+':
            buffer[pos++] = ' ';
            break;

         default:
            buffer[pos++] = (int8)str.CharAt(a).Unicode();
            break;
      }
   }

   String ret = String(buffer, pos);
   delete[] buffer;
   return ret;
}

String jm::URLEncode(const String &str)
{
   //
   // A URL-encoded string contains only ASCII characters...
   //
   String ret;

   for(uint32 a = 0; a < str.Length(); a++)
   {
      switch(str.CharAt(a).Unicode())
      {
         case ' ':
            ret.Append('+');
            break;

         case '%':
            ret.Append('%');
            ret.Append('2');
            ret.Append('5');
            break;

         case '+':
            ret.Append('%');
            ret.Append('2');
            ret.Append('B');
            break;

         default:
            ret.Append(str.CharAt(a));
            break;
      }
   }

   return ret;
}

