////////////////////////////////////////////////////////////////////////////////////////////////////
// Name:        ZipFile.cpp
// Library:     Jameo Core Library
// Purpose:     Helper for zip
//
// Author:      Uwe Runtemund (2013-today)
// Modified by:
// Created:     28.12.2020
//
// Copyright:   (c) 2020 Jameo Software, Germany. https://jameo.de
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

//
// ZIP FILE
//

ZipFile::ZipFile(File* file): jm::Object(),
mEntries(this)
{
	mFile = file;
}

void ZipFile::Open()
{
	uint32 length = (uint32)mFile->Length();
	uint32 seek = length - 22;

	mFile->Open(kFmRead);

	//Wenn die Datei leer ist, dann sind wir fertig
	if(length == 0)return;

	//Wir lesen zuerst die Datei am Ende ein, wo das Verzeichnis mit den Einträgen steht.
	//Idiotischer Weise muss man das Ende suchen, weil der letzte Eintrag eine variable Länge hat.
	//Außerdem kann man die Datei nicht einfach vom Anfang an lesen, weil Einträge unvollständig
	//sein dürfen und die Datenlänge der komprimierten Daten nicht am Anfang gespeichert werden muss.

	uint32 signature;
	uint8 eocd[22];
	bool found = false;
	do
	{
		mFile->Seek(seek);
		mFile->ReadFully(eocd, 22);
		signature = jm::DeserializeLEInt32(eocd, 0);
		seek--;

		if(signature == 0x06054b50)
		{
			found = true;
			break;
		}
	}
	while(seek > 0);

	if(!found)throw new jm::Exception("ZIP-File is invalid.");

	uint16 recordCount = jm::DeserializeLEUInt16(eocd, 10);
	uint32 dictSize = jm::DeserializeLEUInt32(eocd, 12);
	uint32 dictOffset = jm::DeserializeLEUInt32(eocd, 16);

	uint8* dict = new uint8[dictSize];
	mFile->Seek(dictOffset);
	mFile->ReadFully(dict, dictSize);


	uint32 index = 0;
	uint32 count = 0;
	while(count < recordCount)
	{
		signature = jm::DeserializeLEInt32(dict, index);
		uint32 compressedSize = jm::DeserializeLEUInt32(dict, index + 20);
		uint32 uncompressedSize = jm::DeserializeLEUInt32(dict, index + 24);
		uint32 fileNameLength = jm::DeserializeLEUInt16(dict, index + 28);
		uint32 extraFieldLength = jm::DeserializeLEUInt16(dict, index + 30);
		uint32 commentLength = jm::DeserializeLEUInt16(dict, index + 32);
		uint32 offset = jm::DeserializeLEUInt32(dict, index + 42);

		jm::String name = jm::String(&dict[index + 46], fileNameLength);
		jm::String extra = jm::String(&dict[index + 46 + fileNameLength], extraFieldLength);
		jm::String comment = jm::String(&dict[index + 46 + fileNameLength + extraFieldLength], commentLength);

		ZipEntry* entry = new ZipEntry(name);
		entry->mExtra = extra;
		entry->mComment = comment;
		entry->mUncompressedSize = uncompressedSize;
		entry->mCompressedSize = compressedSize;
		entry->mHeaderOffset = offset;

		mEntries.Add(entry, NULL);

		//Lies nächsten Eintrag
		index += 46 + fileNameLength + extraFieldLength + commentLength;
		count++;
	}


}

void ZipFile::Close()
{
	mFile->Close();
}

jm::String ZipFile::GetComment()
{
	return kEmptyString;
}

ZipEntry* ZipFile::GetEntry(const String &name)
{
	LinkedListIterator iter = GetEntryIterator();

	while(iter.HasNext())
	{
		ZipEntry* entry = static_cast<ZipEntry*>(iter.Next());
		if(entry->mName.Equals(name))return entry;
	}

	return NULL;
}

LinkedListIterator ZipFile::GetEntryIterator()
{
	return mEntries.GetIterator();
}

uint32 ZipFile::GetEntryCount() const
{
	return mEntries.Length();
}

jm::Stream* ZipFile::GetStream(const ZipEntry* entry)
{
	uint8* input = new uint8[entry->mCompressedSize];
	uint8* buffer = new uint8[entry->mUncompressedSize];

	//Local Header
	uint8 localHeader[30];
	mFile->Seek(entry->mHeaderOffset);
	mFile->ReadFully(localHeader, 30);
	uint32 signature = jm::DeserializeLEUInt32(localHeader, 0);

	if(signature != 0x04034b50)throw new jm::Exception("ZIP file Error. Signature of Entry wrong.");

	uint16 cm = jm::DeserializeLEUInt16(localHeader, 8);
	uint32 fl = jm::DeserializeLEUInt16(localHeader, 26);
	uint32 el = jm::DeserializeLEUInt16(localHeader, 28);


	mFile->Seek(entry->mHeaderOffset + 30 + fl + el);
	mFile->ReadFully(input, entry->mCompressedSize);

	if(cm == 0) //Daten unkomprimiert
	{
		memcpy(buffer, input, entry->mCompressedSize);
	}
	if(cm == 8) //Deflate
	{
		Inflater inf = Inflater(true);
		uint32 control;
		inf.SetInput(input, entry->mCompressedSize);
		inf.Inflate(buffer, control);
	}

	delete[]input;

	return new MemoryStream(buffer, entry->mUncompressedSize);
}

//
// ZIP ENTRY
//

ZipEntry::ZipEntry(const String &name): jm::Object()
{
	mName = name;
	mUncompressedSize = 0;
	mCompressedSize = 0;
	mHeaderOffset = 0;
	mCRC = 0;
	mDataOffset = 0;
}

String ZipEntry::GetName()const
{
	return mName;
}

void ZipEntry::SetUncompressedSize(uint32 size)
{
	mUncompressedSize = size;
}

uint32 ZipEntry::GetUncompressedSize()const
{
	return mUncompressedSize;
}

bool ZipEntry::IsDirectory()const
{
	return false;
}
