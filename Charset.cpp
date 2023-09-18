//
//  Charset.cpp
//  jameo
//
//  Created by Uwe Runtemund on 18.01.13.
//  Copyright (c) 2013 Jameo Software. All rights reserved.
//

#include "Precompiled.h"

using namespace jm;

//Unter Mac auf Jedenfall
using std::min;

uint16 Charset::gCharsetCount = 7;
Charset* Charset::gCharsets[7] = { new Charset(new UTF8Decoder()),
	         new Charset("Windows-1252", new Windows1252Decoder()),
	         new Charset("MacRoman", new MacRomanDecoder()),
	         new Charset("UTF-16LE", new UTF16Decoder(false)),
	         new Charset("UTF-16BE", new UTF16Decoder(true)),
	         new Charset("RAW", new RawDecoder()),
	         new Charset("ASCII", new RawDecoder())
};

CharArray::CharArray()
{
	length = 0;
	buffer = NULL;
}

CharArray::CharArray(const CharArray &another)
{
	length = another.length;
	buffer = new uint16[length];
	memcpy(buffer, another.buffer, length * 2);
}

CharArray::CharArray(uint32 alength)
{
	length = alength;
	buffer = new uint16[length];
}

CharArray::~CharArray()
{
	length = 0;
	if(buffer != NULL)
	{
		delete[] buffer;
		buffer = NULL;
	}
}

namespace jm
{
	CharArray &CharArray::operator=(const CharArray &another)
	{
		if(this == &another) return *this;
		if(buffer != NULL)delete[] buffer;
		length = another.length;
		buffer = new uint16[length];
		memcpy(buffer, another.buffer, length * 2);

		return *this;
	}
}

Charset::Charset(CharsetDecoder* decoder): Object()
{
	mName.Append('U');
	mName.Append('T');
	mName.Append('F');
	mName.Append('-');
	mName.Append('8');
	mAlternatives = NULL;
	mAltCount = 0;
	mDecoder = decoder;
}

Charset::Charset(const int8 *name, CharsetDecoder* decoder): Object()
{
	uint32 index = 0;
	while(name[index] != 0)mName.Append(name[index++]);

	mAlternatives = NULL;
	mAltCount = 0;
	mDecoder = decoder;
}

Charset::Charset(const String &name, const String* alternatives, uint8 altCount, CharsetDecoder* decoder): Object()
{
	mName = name;
	mAlternatives = new String[mAltCount];
	mAltCount = altCount;
	for(uint8 a = 0; a < mAltCount; a++)mAlternatives[a] = alternatives[a];
	mDecoder = decoder;
}

Charset::~Charset()
{
	delete mDecoder;
	if(mAlternatives != NULL)delete [] mAlternatives;
	mDecoder = NULL;
	mAlternatives = NULL;
	mAltCount = 0;
}

String Charset::Name()
{
	return mName;
}

bool Charset::HasName(const String &name)
{
	if(mName.Equals(name))return true;

	for(uint8 a = 0; a < mAltCount; a++)
	{
		if(mAlternatives[a].Equals(name))return true;
	}

	return false;
}

CharArray Charset::Decode(const int8* cString)
{
	return mDecoder->Decode(cString);
}

int8* Charset::Encode(const CharArray &string)
{
	return mDecoder->Encode(string);
}

Charset* Charset::ForName(const String &name)
{
	for(uint16 a = 0; a < Charset::gCharsetCount; a++)
	{
		if(Charset::gCharsets[a]->HasName(name))return Charset::gCharsets[a];
	}
	throw new Exception(jm::String::Format(Tr("Unknown Charset Name: \"%s\""), &name));
}

String Charset::Guess(uint8* stream, uint32 length)
{

	String encoding;

	#ifdef __APPLE__ //macOS
	encoding = "MacRoman";
	#elif defined __linux__ //Linux
	encoding = "UTF-8";
	#elif defined _WIN32 //Windows
	encoding = "Windows-1252";
	#endif

	//
	// Wenn UTF-Marker gesetzt sind, ist es einfach.
	//


	//UTF-16BE
	if(stream[0] == 0xFE && stream[1] == 0xFF)return "UTF-16BE";

	//UTF-16LE
	else if(stream[0] == 0xFF && stream[1] == 0xFE)return "UTF-16LE";

	//UTF-8
	else if(stream[0] == 0xEF && stream[1] == 0xBB && stream[2] == 0xBF)return "UTF-8";

	//
	// Untersuche auf UTF-16
	//

	// Es kann sein, das eine UTF16-Kodierung ohne Marker vorliegt. Die Wahrscheinlichkeit dafür ist hoch, wenn bei "europäischem" Text jedes zweite Byte 0 ist
	uint16 frame = (uint16) min(4096, static_cast<int32>(length));
	float count1 = 0;
	float count2 = 0;
	for(uint16 a = 0; a < frame; a++)
	{
		if(stream[a] == 0)
		{
			(a % 2 == 0) ? count1++ : count2++;
		}
	}

	if(count1 / (0.5f * frame) > 0.9)//Gleichbedeutend mit 00 XX 00 XX 00 XX ...
	{
		return "UTF-16BE";
	}
	else if(count2 / (0.5 * frame) > 0.9)//Gleichbedeutend mit XX 00 XX 00 XX 00 XX 00 ...
	{
		return "UTF-16LE";
	}

	//Undefinierte Zeichen in Windows-1252
	if(encoding.Equals("Windows-1252"))
	{
		for(uint32 a = 0; a < length; a++)
		{
			switch(stream[a])
			{
				case 0x81:
				case 0x8D:
				case 0x8F:
				case 0x90:
				case 0x9D:
					//Obige Zeichen gibt es in Windows-1252 nicht! Nimm MacRoman an.
					encoding = "MacRoman";
					break;

				default:
					;//Tue nichts

			}
		}
	}

	//Nimm ASCII an, wenn kein Byte größer als 0x7F ist
	bool isASCII = true;
	for(uint32 a = 0; a < length; a++)
	{
		if(stream[a] > 0x7F)
		{
			isASCII = false;
			break;
		}
	}
	if(isASCII)return "ASCII";

	//\todo Mache eine Statistische Auswertung, Oder Wörterbuch von Nicht-ASCII-Charaktern
	//Vergleiche: http://stackoverflow.com/questions/4198804/how-to-reliably-guess-the-encoding-between-macroman-cp1252-latin1-utf-8-and

	return encoding;
}


Charset* Charset::GetDefault()
{
	return Charset::gCharsets[0];
}

void jm::InitCharsets()
{
	//Braucht nichts getan zu werden. Charsets werden beim Laden automatisch initialisiert
	//Allerdings ist die Reihenfolge nicht klar....
}

void jm::QuitCharsets()
{
	for(uint16 a = 0; a < Charset::gCharsetCount; a++)delete Charset::gCharsets[a];
}

