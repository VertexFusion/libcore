////////////////////////////////////////////////////////////////////////////////////////////////////
// Name:        ZipOutputFile.cpp
// Library:     Jameo Core Library
// Purpose:     Zip Helper
//
// Author:      Uwe Runtemund (2021-today)
// Modified by:
// Created:     31.01.2021
//
// Copyright:   (c) 2021 Jameo Software, Germany. https://jameo.de
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

uint32 CRC32(const char *s, uint32 n)
{
	uint32 crc = 0xFFFFFFFF;

	for(uint32 i = 0; i < n; i++)
	{
		char ch = s[i];
		for(uint32 j = 0; j < 8; j++)
		{
			uint32 b = (ch ^ crc) & 1;
			crc >>= 1;
			if(b) crc = crc ^ 0xEDB88320;
			ch >>= 1;
		}
	}

	return ~crc;
}

ZipOutputFile::ZipOutputFile(File* file): jm::Object(),
mEntries(this)
{
	mFile = file;
	mTemp = NULL;
}

void ZipOutputFile::Open()
{
	if(mFile->Exists() == false)mFile->CreateNewFile();
	mFile->Open(kFmReadWrite);
}

void ZipOutputFile::Close()
{
	uint32 start = static_cast<uint32>(mFile->GetPosition());

	//Schreibe Finales Verzeichnis
	mEntries.Rewind();
	while(mEntries.HasNext())
	{
		ZipEntry* entry = (ZipEntry*)mEntries.Next();

		ByteArray cname = entry->mName.ToCString();
		ByteArray cextra = entry->mExtra.ToCString();
		ByteArray ccomment = entry->mComment.ToCString();

		uint8 cdfh[46];
		jm::SerializeLEInt32(cdfh, 0, 0x02014b50);//Signature
		jm::SerializeLEInt16(cdfh, 4, 0);//Version made by. Auf 0 gesetzt
		jm::SerializeLEInt16(cdfh, 6, 0);//Minimum Version needed. Auf 0 gesetzt
		jm::SerializeLEInt16(cdfh, 8, 0);//General Purpose Bit Flag. Auf 0 gesetzt
		jm::SerializeLEInt16(cdfh, 10, 0); //Compression Method
		jm::SerializeLEInt16(cdfh, 12, 0);//ShxFile last modification time
		jm::SerializeLEInt16(cdfh, 14, 0);//ShxFile last modification date
		jm::SerializeLEInt32(cdfh, 16, entry->mCRC);//CRC
		jm::SerializeLEInt32(cdfh, 20, entry->mCompressedSize);//Compressed Size
		jm::SerializeLEInt32(cdfh, 24, entry->mUncompressedSize);//Uncompressed Size
		jm::SerializeLEInt16(cdfh, 28, cname.Size());//ShxFile name Length
		jm::SerializeLEInt16(cdfh, 30, cextra.Size());//Extra field length
		jm::SerializeLEInt16(cdfh, 32, ccomment.Size());//Comment field length
		jm::SerializeLEInt16(cdfh, 34, 0);//Disk Number where file starts. Zu 0 gesetzt
		jm::SerializeLEInt16(cdfh, 36, 0);//Internal ShxFile Attributes. Zu 0 gesetzt
		jm::SerializeLEInt32(cdfh, 38, 0);//External ShxFile Attributes. Zu 0 gesetzt
		jm::SerializeLEInt32(cdfh, 42, entry->mHeaderOffset);//Relative offset to local ShxFile Header

		mFile->Write(cdfh, 46);
		if(cname.Size() > 0)mFile->Write((uint8*)cname.ConstData(), cname.Size());
		if(cextra.Size() > 0)mFile->Write((uint8*)cextra.ConstData(), cextra.Size());
		if(ccomment.Size() > 0)mFile->Write((uint8*)ccomment.ConstData(), ccomment.Size());

	}

	uint32 end = static_cast<uint32>(mFile->GetPosition());

	//Frilte End of Directory Record
	uint8 eof[22];
	jm::SerializeLEInt32(eof, 0, 0x06054b50);//Signature
	jm::SerializeLEInt16(eof, 4, 0);//Number of Disks
	jm::SerializeLEInt16(eof, 6, 0);//Disk where centra directory starts.
	jm::SerializeLEInt16(eof, 8,  (int16)mEntries.Size());//Number of Central directory records on this disk
	jm::SerializeLEInt16(eof, 10, (int16)mEntries.Size());//Total Number of Central directory records
	jm::SerializeLEInt32(eof, 12, end - start); //Size of central directory (bytes)
	jm::SerializeLEInt32(eof, 16, start);//Start of central directory relative to start of archive
	jm::SerializeLEInt16(eof, 20, 0);//Comment Length.

	mFile->Write(eof, 22);

	mFile->Close();
}

void ZipOutputFile::CloseEntry()
{
	ZipEntry* entry = (ZipEntry*)mEntries.Last();

	entry->mUncompressedSize = static_cast<uint32>(mTemp->GetPosition());
	mTemp->Seek(0);
	ByteArray buffer = ByteArray(entry->mUncompressedSize,0);
	mTemp->Stream::ReadFully(buffer);
	mTemp->Close();
	mTemp->Delete();
	delete mTemp;
	mTemp = NULL;

	//CRC berechnen
	entry->mCRC = CRC32(buffer.ConstData(), entry->mUncompressedSize);

	//Schreibe unkomprimiert
	entry->mCompressedSize = entry->mUncompressedSize;

	mFile->Write((uint8*)buffer.ConstData(), entry->mUncompressedSize);
	uint32 pos = static_cast<uint32>(mFile->GetPosition());

	//Aktualisiere Header
	uint8 lfhfragment[12];
	jm::SerializeLEInt32(lfhfragment, 0, entry->mCRC);
	jm::SerializeLEInt32(lfhfragment, 4, entry->mCompressedSize);
	jm::SerializeLEInt32(lfhfragment, 8, entry->mUncompressedSize);

	mFile->Seek(entry->mHeaderOffset + 14);
	mFile->Write(lfhfragment, 12);
	mFile->Seek(pos);
}

void ZipOutputFile::WriteAndClose(jm::File* file)
{
	ZipEntry* entry = static_cast<ZipEntry*>(mEntries.Last());

	entry->mUncompressedSize = static_cast<uint32>(file->Length());
	file->Open(kFmRead);
	ByteArray buffer = ByteArray(entry->mUncompressedSize,0);
	file->Stream::ReadFully(buffer);
	file->Close();

	mTemp->Close();
	mTemp->Delete();
	delete mTemp;
	mTemp = NULL;

	//CRC berechnen
	entry->mCRC = CRC32(buffer.ConstData(), entry->mUncompressedSize);

	//Schreibe unkomprimiert
	entry->mCompressedSize = entry->mUncompressedSize;

	mFile->Write((uint8*)buffer.ConstData(), entry->mUncompressedSize);
	uint32 pos = static_cast<uint32>(mFile->GetPosition());

	//Aktualisiere Header
	uint8 lfhfragment[12];
	jm::SerializeLEInt32(lfhfragment, 0, entry->mCRC);
	jm::SerializeLEInt32(lfhfragment, 4, entry->mCompressedSize);
	jm::SerializeLEInt32(lfhfragment, 8, entry->mUncompressedSize);

	mFile->Seek(entry->mHeaderOffset + 14);
	mFile->Write(lfhfragment, 12);
	mFile->Seek(pos);
}

void ZipOutputFile::PutNextEntry(ZipEntry* entry)
{
	entry->mHeaderOffset = static_cast<uint32>(mFile->GetPosition());

	ByteArray cname = entry->mName.ToCString();
	ByteArray cextra = entry->mExtra.ToCString();

	//Schreibe Local FileHeader
	uint8 lfh[30];
	jm::SerializeLEInt32(lfh, 0, 0x04034b50);//Signature
	jm::SerializeLEInt16(lfh, 4, 0);//Minimum Version needed. Auf 0 gesetzt
	jm::SerializeLEInt16(lfh, 6, 0);//General Purpose Bit Flag. Auf 0 gesetzt
	jm::SerializeLEInt16(lfh, 8, 0);//Compression Method
	jm::SerializeLEInt16(lfh, 10, 0);//ShxFile last modification time
	jm::SerializeLEInt16(lfh, 12, 0);//ShxFile last modification date
	jm::SerializeLEInt32(lfh, 14, 0);//CRC
	jm::SerializeLEInt32(lfh, 18, 0);//Compressed Size
	jm::SerializeLEInt32(lfh, 22, 0);//Uncompressed Size
	jm::SerializeLEInt16(lfh, 26, cname.Size());//ShxFile name Length
	jm::SerializeLEInt16(lfh, 28, cextra.Size());//Extra field length

	mFile->Write(lfh, 30);
	if(cname.Size() > 0)mFile->Write((uint8*)cname.ConstData(), cname.Size());
	if(cextra.Size() > 0)mFile->Write((uint8*)cextra.ConstData(), cextra.Size());

	entry->mDataOffset = static_cast<uint32>(mFile->GetPosition());

	mTemp = new jm::File(mFile->GetParent(), "jmzipdata.tmp");
	mTemp->CreateNewFile();
	mTemp->Open(kFmReadWrite);

	mEntries.Add(entry, NULL);
}

void ZipOutputFile::Write(uint8* data, Integer offset, Integer length)
{
	mTemp->Write(&data[offset], length);
}
