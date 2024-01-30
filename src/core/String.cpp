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

Hashtable gStrings;

String::String(): Object(), Comparable<String>()
{
	mHash = 0;
	mStrLength = 0;
	mArrLength = 16;
	mValue = new uint16[mArrLength];
}

String::String(const uint16* buffer, Integer size): Object(), Comparable<String>()
{
	mHash = 0;
	CharArray array = CharArray(size);
	memcpy(array.buffer, buffer, sizeof(uint16) * size);
	Copy(array);
}

String::String(const String &another): Object(), Comparable<String>()
{
	mHash = 0;
	mStrLength = another.mStrLength;
	mArrLength = another.mArrLength;
	mValue = new uint16[mArrLength];
	memcpy(mValue, another.mValue, sizeof(uint16) * mStrLength);
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
		mValue = new uint16[mArrLength];
	}
}

String::String(const int8* cstring, Charset* charset): Object(), Comparable<String>()
{
	mHash = 0;
	CharArray array = charset->Decode(cstring);
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
	mValue = new uint16[mArrLength];
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
	uint16* tmp = new uint16 [mArrLength];
	memcpy(tmp, mValue, 2 * mStrLength);
	delete[] mValue;
	mValue = tmp;
}

String String::FromCFString(CFStringRef cfstring)
{
	// NULL string?
	if (cfstring==NULL)return kEmptyString;

	// Empty string?
	CFIndex length = CFStringGetLength(cfstring);
	if (length == 0) return kEmptyString;

	// C-String
	char* cstr=NULL;
	CFStringGetCStringPtr(cfstring,kCFStringEncodingUTF8);
	if(cstr!=NULL)return String(cstr);
	
	// Fallback
	cstr=new char[length*2];//Hope, that not all characters are greater than 4 bytes representation
	CFStringGetCString(cfstring, cstr, length*2, kCFStringEncodingUTF8);
	String result=String(cstr);
	delete[] cstr;
	
	return result;
}

CFStringRef String::ToCFString()const
{
	const char* cstring = ToCString();
	CFStringRef cfstring = CFStringCreateWithCString(kCFAllocatorDefault, cstring, kCFStringEncodingUTF8);
	delete[] cstring;
	return cfstring;
}


Integer String::Length() const
{
	return mStrLength;
}

int8* String::ToCString() const
{
	return ToCString(Charset::GetDefault());
}

int8* String::ToCString(Charset* charset) const
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

	for(uint32 a = 0; a < another.mStrLength; a++)
	{
		if(mValue[a] != another.mValue[a])return false;
	}

	return true;
}


bool String::EndsWith(const String &another) const
{
	if(another.mStrLength > mStrLength)return false;

	for(uint32 a = 1; a <= another.mStrLength; a++)
	{
		if(mValue[mStrLength - a] != another.mValue[another.mStrLength - a])return false;
	}

	return true;
}

Integer String::HashCode() const
{
	if(mHash != 0)return mHash;
	uint32 hash = 0;
	for(int32 a = 0; a < mStrLength; a++)hash = (hash << 5) - hash + mValue[a];
	const_cast<String*>(this)->mHash = (int32) hash;
	return mHash;
}

String String::ToLowerCase() const
{
	String ret = *this;

	for(uint32 a = 0; a < mStrLength; a++)
	{
		ret.mValue[a] = CharacterToLowerCase(ret.mValue[a]);
	}

	return ret;
}

String String::ToUpperCase() const
{
	String ret = *this;

	for(uint32 a = 0; a < mStrLength; a++)
	{
		ret.mValue[a] = CharacterToUpperCase(ret.mValue[a]);
	}

	return ret;
}

String String::Trim() const
{
	Integer beginIndex = 0;
	Integer endIndex = mStrLength;

	if(mStrLength == 0)return kEmptyString;

	//Von links
	while(beginIndex < mStrLength && CharacterIsWhitespace(mValue[beginIndex]))beginIndex++;

	//Von rechts
	while(endIndex > 0 && CharacterIsWhitespace(mValue[endIndex - 1]))endIndex--;

	if(endIndex <= beginIndex)return kEmptyString;

	return Substring(beginIndex, endIndex);
}

Integer String::IndexOf(uint16 character) const
{
	return IndexOf(character, 0);
}

Integer String::IndexOf(const String &str) const
{
	return IndexOf(str, 0);
}

Integer String::IndexOf(uint16 character, Integer fromIndex) const
{
	if (fromIndex < 0)fromIndex = 0;

	for(Integer a = fromIndex; a < mStrLength; a++)
	{
		if(mValue[a] == character)return a;
	}
	return -1;
}

Integer String::IndexOf(const String &str, Integer fromIndex) const
{
	if (fromIndex < 0)fromIndex = 0;

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

Integer String::LastIndexOf(uint16 character) const
{
	return LastIndexOf(character, mStrLength - 1);
}

Integer String::LastIndexOf(const String &str) const
{
	return LastIndexOf(str, mStrLength - 1);
}

Integer String::LastIndexOf(uint16 character, Integer fromIndex) const
{
	if (fromIndex >= mStrLength) throw new Exception("Index out of Bounds: " + String::ValueOf(fromIndex));
	if (fromIndex < 0)fromIndex = 0;
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


String String::Replace(uint16 oldChar, uint16 newChar) const
{
	String ret = String(*this);

	for(uint32 a = 0; a < mStrLength; a++)
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
		uint16 tmp = ret.mValue[a];
		ret.mValue[a] = ret.mValue[last];
		ret.mValue[last] = tmp;
		last--;
	}

	return ret;
}

uint16 String::CharAt(Integer index) const
{
	if(index < 0 || index >= mStrLength)
		throw new Exception("Index out of Bounds: " + String::ValueOf(index));
	return mValue[index];
}

void String::SetCharAt(Integer index, uint16 character)
{
	if(index < 0 || index >= mStrLength)throw new Exception("Index out of Bounds: " + String::ValueOf(index));
	mValue[index] = character;
	mHash = 0;
}

void String::Append(const String &another)
{
	CheckCapacity(another.mStrLength);
	memcpy(&mValue[mStrLength], &another.mValue[0], sizeof(uint16) * another.mStrLength);
	mStrLength += another.mStrLength;
	mHash = 0;
}

void String::Append(uint16 utf8char)
{
	CheckCapacity(1);
	mValue[mStrLength] = utf8char;
	mStrLength++;
	mHash = 0;
}

void String::Insert(Integer index, uint16 character)
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
	if(index<0 || index >= mStrLength)throw new Exception("Index out of Bounds: " + String::ValueOf(index));
	for(Integer a = index ; a < mStrLength - 1; a++)
	{
		mValue[a] = mValue[a + 1];
	}
	mStrLength--;
	mHash = 0;
}

void String::DeleteCharRangeAt(Integer index, Integer length)
{
	if(index<0 || index + length > mStrLength)throw new Exception("Index out of Bounds: " + String::ValueOf(index));
	for(Integer a = index ; a < mStrLength - length; a++)
	{
		mValue[a] = mValue[a + length];
	}
	mStrLength -= length;
	mHash = 0;
}


void String::Clear()
{
	Zero();
	if(mArrLength > 16)
	{
		delete[] mValue;
		mArrLength = 16;
		mValue = new uint16[mArrLength];
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
		uint16 c1 = CharacterToLowerCase(mValue[cnt]);
		uint16 c2 = CharacterToLowerCase(another.mValue[cnt]);
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
		uint16 c1 = mValue[cnt];
		uint16 c2 = another.mValue[cnt];
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
		if(mValue[cntin] >= '0' && mValue[cntin] <= '9')
		{
			uint32 number = mValue[cntin] - '0';
			while(cntin + 1 < strl1 && mValue[cntin + 1] >= '0' && mValue[cntin + 1] <= '9')
			{
				cntin++;
				number *= 10;
				number += mValue[cntin] - '0';
			}
			str1[cntout] = number;
		}
		else str1[cntout] = mValue[cntin];

		cntin++;
		cntout++;
	}
	l1 = cntout;

	// Convert 2nd String
	cntin = 0;
	cntout = 0;
	while(cntin < strl2)
	{
		if(another.mValue[cntin] >= '0' && another.mValue[cntin] <= '9')
		{
			uint32 number = another.mValue[cntin] - '0';
			while(cntin + 1 < strl2 && another.mValue[cntin + 1] >= '0' && another.mValue[cntin + 1] <= '9')
			{
				cntin++;
				number *= 10;
				number += another.mValue[cntin] - '0';
			}
			str2[cntout] = number;
		}
		else str2[cntout] = another.mValue[cntin];

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
	if (beginIndex < 0)beginIndex = 0;
	if (endIndex > mStrLength) endIndex = mStrLength;
	Integer sublength = endIndex - beginIndex;
	String ret;

	if(sublength > 0)
	{
		ret.CheckCapacity(sublength);
		memcpy(&ret.mValue[0], &mValue[beginIndex], sizeof(uint16) * sublength);
		ret.mStrLength = sublength;
	}

	return ret;
}

String String::Substring(Integer beginIndex) const
{
	return Substring(beginIndex, mStrLength);
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
		int64 digit = number % 10;
		number = number / 10;
		ret.Append((int16)(digit + '0'));
	}
	if(neg)ret.Append('-');

	// Reverse digits
	Integer cnt = ret.Length() / 2;
	for(Integer a = 0; a < cnt; a++)
	{
		uint16 s1 = ret.CharAt(a);
		uint16 s2 = ret.CharAt(ret.Length() - 1 - a);
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
		int64 digit = number % 10;
		number = number / 10;
		ret.Append((int16)(digit + '0'));
	}

	// Reverse digits
	Integer cnt = ret.Length() / 2;
	for(Integer a = 0; a < cnt; a++)
	{
		uint16 s1 = ret.CharAt(a);
		uint16 s2 = ret.CharAt(ret.Length() - 1 - a);
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

String String::ValueOf(double number,Integer precision,bool trunc)
{
	bool neg = jm::IsLess(number, 0.0);
	int64 before = static_cast<int64>(number);
	if (neg)before *= -1;

	double factor = std::pow(10, precision.Int32());

	number = std::fmod(number, 1.0) * 10 * factor;
	int64 after = Integer(static_cast<int64>(number)).Abs();

	//Runden
	int64 rnd = after % 10;
	after = after / 10;
	if (rnd >= 5)after++;
	if (after == factor)
	{
		after = 0;
		before++;
	}

	String b = String::ValueOf(before);
	if (neg)b.Insert(0, '-');

	String a = String::ValueOf(after);
	while (a.Length() < precision)a.Insert(0, '0');

	while (trunc && a.Length() > 1 && a.CharAt(a.Length() - 1) == '0')a.DeleteCharAt(a.Length() - 1);

	if (after != 0 || trunc == false)return b + "," + a;
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


/*
 int i;


 // Step through the list.
 for( i = 0; szTypes[i] != '\0'; ++i ) {
 union Printable_t {
 int     i;
 float   f;
 char    c;
 char   *s;
 } Printable;

 switch( szTypes[i] ) {   // Type to expect.
 case 'i':
 Printable.i = va_arg( vl, int );
 printf_s( "%i\n", Printable.i );
 break;

 case 'f':
 Printable.f = va_arg( vl, double );
 printf_s( "%f\n", Printable.f );
 break;

 case 'c':
 Printable.c = va_arg( vl, char );
 printf_s( "%c\n", Printable.c );
 break;

 case 's':
 Printable.s = va_arg( vl, char * );
 printf_s( "%s\n", Printable.s );
 break;

 default:
 break;
 }
 }
 va_end( vl );

 */

String String::Format(const String format, ...)
{
	// Count the number of used arguments in the string
	uint32 count1 = 0;
	for(uint32 a = 0; a < format.Length(); a++)
	{
		if(format.CharAt(a) == '%')
		{
			bool escape = (a > 0 && format.CharAt(a - 1) == '/') ? true : false;
			if(!escape)count1++;
		}
	}

	String result;


	va_list args;
	va_start(args,format);

	
	for(Integer cnt=0;cnt<format.Length();cnt++)
	{

		uint16 c = format.CharAt(cnt);

		//Formatierungsstring bearbeiten
		//Formatierung allgemein: %[argument_index$][flags][width][.precision]conversion
		// Der Index ist 1-basiert
		if(c=='%' &&
			cnt < format.Length()-1 &&
			( cnt==0 || (cnt>0 && format.CharAt(cnt-1)!='\\')) )
		{
			// Count the length of flags
			Integer count = 1;
			while (cnt + count < format.Length())
			{
				uint16 ck = format.CharAt(cnt + count);

				if (ck == 's' ||
					 ck == 'f' ||
					 ck == 'i')break;

				count++;
			}

			// The format command
			uint16 cmd = format.CharAt(cnt+count);
			Integer flg1=0;
			Integer dec = 5;
				
			//Integer parameter
			if(cmd=='i')
			{
				int32 i = va_arg(args,int32);
				String s = String::ValueOf(i);

				if (count > 1)flg1 = Integer::ValueOf(format.Substring(cnt + 1, cnt + count));

				// Leading space if flg1 > 0
				if (flg1 > 0)
				{
					for (Integer a = s.Length(); a < flg1; a++)result << ' ';
				}


				result << s;

				// Trailing space if flg1 < 0
				if (flg1 < 0)
				{
					flg1 = abs(flg1);
					for (Integer a = s.Length(); a < flg1; a++)result << ' ';
				}

			}
			//double parameter
			if (cmd == 'f')
			{
				double i = va_arg(args, double);

				bool fillzero = false;

				if (count > 1)
				{
					jm::String flag = format.Substring(cnt + 1, cnt + count);
					if (flag.CharAt(0) == '0')
					{
						fillzero = true;
						flag.DeleteCharAt(0);
					}

					Integer div = flag.IndexOf('.');
					if (div > -1)
					{
						flg1 = Integer::ValueOf(flag.Substring(0,div));
						dec = Integer::ValueOf(flag.Substring(div+1));
					}
					else
					{
						flg1 = Integer::ValueOf(flag);
					}
				}



				String s = String::ValueOf(i,dec,false);

				// Leading space if flg1 > 0
				if (flg1 > 0)
				{
					for (Integer a = s.Length(); a < flg1; a++)result << ' ';
				}


				result << s;

				// Trailing space if flg1 < 0
				if (flg1 < 0)
				{
					flg1 = abs(flg1);
					for (Integer a = s.Length(); a < flg1; a++)result << ' ';
				}
			}
			//String
			if (cmd == 's')
			{
				if (count > 1)flg1 = Integer::ValueOf(format.Substring(cnt + 1, cnt + count));

				// Works with windows!
				String* s = va_arg(args, String*);

				// Leading space if flg1 > 0
				if (flg1 > 0)
				{
					for (Integer a = s->Length(); a < flg1; a++)result << ' ';
				}
				result << *s;

				// Trailing space if flg1 < 0
				if (flg1 < 0)
				{
					flg1 = abs(flg1);
					for (Integer a = s->Length(); a < flg1; a++)result << ' ';
				}
			}

			cnt += count;
		}
		else result.Append(c);
	}

	va_end(args);

	return result;
}

const String* String::Ref(const String &str)
{
	const String* ref = (const String*)gStrings.Get(str);
	if(ref==NULL)
	{
		ref=new String(str);
		gStrings.Put(str, (void*)ref);
	}
	return ref;
}

Charset* gConsoleCharset = NULL;

void jm::String::SetConsoleCharset(Charset* cs)
{
	gConsoleCharset = cs;
}

namespace jm
{


	ostream &operator << (ostream &out, const String &str)
	{
		//\todo Charset am Besten global setzen und holen. So ist es ineffizient
		if(gConsoleCharset == NULL)gConsoleCharset = Charset::ForName("Windows-1252");
		String s = str;
		char* cstr = s.ToCString(gConsoleCharset);
		out << cstr;
		delete[] cstr;
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

	String& String::operator=(const String &another)
	{
		if(this != &another)
		{
			delete[] mValue;
			mStrLength = another.mStrLength;
			mArrLength = another.mArrLength;
			mValue = new uint16[mArrLength];
			memcpy(mValue, another.mValue, sizeof(uint16) * mStrLength);
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

uint8 jm::Digits(int64 number)
{
	uint8 i = 1;
	if(number < 0)
	{
		number *= -1;
		i++;
	}

	while(number > 9)
	{
		number = number / 10;
		i++;
	}
	return i;
}

double jm::StrToDouble(String str)
{
	int8* cstr = str.ToCString();
	std::stringstream ss;
	double d = 0;
	ss << cstr;
	ss >> d;
	delete[] cstr;
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

uint64 jm::HexToInt(const String &str)
{
	return HexToInt(str, 0, str.Length().Uint32());
}

uint64 jm::HexToInt(const String &str, uint32 begin, uint32 count)
{
	uint64 r = 0;

	uint32 cnt = begin;
	uint32 sz = begin + count;

	while(cnt < sz)
	{
		uint16 c = str.CharAt(cnt);
		cnt++;

		uint64 i = 0;

		if(c >= '0' && c <= '9')
		{
			i = c - '0';
		}
		else if(c >= 'a' && c <= 'f')
		{
			i = c - 'a' + 10;
		}
		else if(c >= 'A' && c <= 'F')
		{
			i = c - 'A' + 10;
		}

		r <<= 4;
		r |= i;

	}

	return r;
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
		switch(str.CharAt(a))
		{
			case '%':
				c = (int8)jm::HexToInt(str.Substring(a + 1, a + 3));
				a += 2;
				buffer[pos++] = c;
				break;

			case '+':
				buffer[pos++] = ' ';
				break;

			default:
				buffer[pos++] = (int8)str.CharAt(a);
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
		switch(str.CharAt(a))
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

