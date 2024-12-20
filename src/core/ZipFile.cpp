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

#include "PrecompiledCore.hpp"

using namespace jm;

//
// ZIP FILE
//

ZipFile::ZipFile(File* file): jm::Object(),
   mEntries(this)
{
   mFile = file;
}

ZipFile::~ZipFile()
{
   mEntries.rewind();
   while(mEntries.hasNext())
   {
      ZipEntry* entry = static_cast<ZipEntry*>(mEntries.next());
      entry->release();
   }
}

void ZipFile::open()
{
   uint32 length = (uint32)mFile->size();
   uint32 seek = length - 22;

   mFile->open(FileMode::kRead);

   // If the file is empty, then we are done
   if(length == 0)return;

   // We first read the file at the end, where the directory with the entries is located.
   // It's idiotic that you have to search for the end because the last entry has a variable length.
   // In addition, the file cannot simply be read from the beginning, because entries may be
   // incomplete and the data length of the compressed data does not have to be saved at the
   // beginning.

   uint32 signature;
   ByteArray eocd = ByteArray(22, 0);
   bool found = false;
   do
   {
      mFile->seek(seek);
      mFile->Stream::readFully(eocd);
      signature = jm::deserializeLEInt32((uint8*)eocd.constData(), 0);
      seek--;

      if(signature == 0x06054b50)
      {
         found = true;
         break;
      }
   }
   while(seek > 0);

   if(!found)throw jm::Exception(Tr("ZIP-File is invalid."));

   uint16 recordCount = jm::deserializeLEUInt16((uint8*)eocd.constData(), 10);
   uint32 dictSize = jm::deserializeLEUInt32((uint8*)eocd.constData(), 12);
   uint32 dictOffset = jm::deserializeLEUInt32((uint8*)eocd.constData(), 16);

   ByteArray dict = ByteArray(dictSize, 0);
   mFile->seek(dictOffset);
   mFile->Stream::readFully(dict);


   uint32 index = 0;
   uint32 count = 0;
   while(count < recordCount)
   {
      //signature = jm::DeserializeLEInt32(dict, index);
      uint32 compressedSize = jm::deserializeLEUInt32((uint8*)dict.constData(), index + 20);
      uint32 uncompressedSize = jm::deserializeLEUInt32((uint8*)dict.constData(), index + 24);
      uint32 fileNameLength = jm::deserializeLEUInt16((uint8*)dict.constData(), index + 28);
      uint32 extraFieldLength = jm::deserializeLEUInt16((uint8*)dict.constData(), index + 30);
      uint32 commentLength = jm::deserializeLEUInt16((uint8*)dict.constData(), index + 32);
      uint32 offset = jm::deserializeLEUInt32((uint8*)dict.constData(), index + 42);

      jm::String name = jm::String((char*)&dict[index + 46], fileNameLength);
      jm::String extra = jm::String((char*)&dict[index + 46 + fileNameLength], extraFieldLength);
      jm::String comment = jm::String((char*)&dict[index + 46 + fileNameLength + extraFieldLength],
                                      commentLength);

      ZipEntry* entry = new ZipEntry(name);
      entry->mExtra = extra;
      entry->mComment = comment;
      entry->mUncompressedSize = uncompressedSize;
      entry->mCompressedSize = compressedSize;
      entry->mHeaderOffset = offset;

      mEntries.add(entry, nullptr);

      //Lies nächsten Eintrag
      index += 46 + fileNameLength + extraFieldLength + commentLength;
      count++;
   }


}

void ZipFile::close()
{
   mFile->close();
}

jm::String ZipFile::comment()
{
   return kEmptyString;
}

ZipEntry* ZipFile::entry(const String& name)
{
   LinkedListIterator iter = entryIterator();

   while(iter.hasNext())
   {
      ZipEntry* entry = static_cast<ZipEntry*>(iter.next());
      if(entry->mName.equals(name))return entry;
   }

   return nullptr;
}

LinkedListIterator ZipFile::entryIterator()
{
   return mEntries.iterator();
}

uint32 ZipFile::entryCount() const
{
   return mEntries.size();
}

jm::Stream* ZipFile::stream(const ZipEntry* entry)
{
   ByteArray input = ByteArray(entry->mCompressedSize, 0);

   //Local Header
   ByteArray localHeader = ByteArray(30, 0);
   mFile->seek(entry->mHeaderOffset);
   mFile->Stream::readFully(localHeader);
   uint32 signature = jm::deserializeLEUInt32((uint8*)localHeader.constData(), 0);

   if(signature != 0x04034b50)
   {
      throw jm::Exception(Tr("ZIP file Error. Signature of Entry wrong."));
   }

   uint16 cm = jm::deserializeLEUInt16(localHeader, 8);
   uint32 fl = jm::deserializeLEUInt16(localHeader, 26);
   uint32 el = jm::deserializeLEUInt16(localHeader, 28);


   mFile->seek(entry->mHeaderOffset + 30 + fl + el);
   mFile->Stream::readFully(input);

   uint8* buffer=nullptr;
   if(cm == 0) //Daten uncompressed
   {
      buffer = new uint8[entry->mUncompressedSize];
      memcpy(buffer, input.constData(), entry->mCompressedSize);
   }
   if(cm == 8) //Deflate
   {
      Inflater inf = Inflater(true);
      int64 control;
      inf.SetInput(reinterpret_cast<uint8*>(input.data()), entry->mCompressedSize);
      // buffer is initialized and set by Inflater
      inf.Inflate(buffer, control);
   }

   return new MemoryStream(buffer, entry->mUncompressedSize,true);
}

//
// ZIP ENTRY
//

ZipEntry::ZipEntry(const String& name): jm::Object()
{
   mName = name;
   mUncompressedSize = 0;
   mCompressedSize = 0;
   mHeaderOffset = 0;
   mCRC = 0;
   mDataOffset = 0;
}

String ZipEntry::name()const
{
   return mName;
}

void ZipEntry::setUncompressedSize(uint32 size)
{
   mUncompressedSize = size;
}

uint32 ZipEntry::uncompressedSize()const
{
   return mUncompressedSize;
}

bool ZipEntry::isDirectory()const
{
   return false;
}
