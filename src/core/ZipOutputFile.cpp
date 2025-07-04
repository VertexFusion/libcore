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

#include "PrecompiledCore.hpp"

using namespace jm;

uint32 CRC32(const char* s, uint32 n)
{
   uint32 crc = 0xFFFFFFFF;

   for(uint32 i = 0; i < n; i++)
   {
      char ch = s[i];
      for(uint32 j = 0; j < 8; j++)
      {
         uint32 b = (static_cast<uint32>(ch) ^ crc) & 1;
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
   mTemp = nullptr;
}

void ZipOutputFile::open()
{
   if(mFile->exists() == false)mFile->createNewFile();
   mFile->open(FileMode::kReadWrite);
}

void ZipOutputFile::close()
{
   size_t start = mFile->position();

   //Schreibe Finales Verzeichnis
   mEntries.rewind();
   while(mEntries.hasNext())
   {
      ZipEntry* entry = static_cast<ZipEntry*>(mEntries.next());

      ByteArray cname = entry->mName.toCString();
      ByteArray cextra = entry->mExtra.toCString();
      ByteArray ccomment = entry->mComment.toCString();

      uint8 cdfh[46];
      jm::serializeLEInt32(cdfh, 0, 0x02014b50);//Signature
      jm::serializeLEInt16(cdfh, 4, 0);//Version made by. Auf 0 gesetzt
      jm::serializeLEInt16(cdfh, 6, 0);//Minimum Version needed. Auf 0 gesetzt
      jm::serializeLEInt16(cdfh, 8, 0);//General Purpose Bit Flag. Auf 0 gesetzt
      jm::serializeLEInt16(cdfh, 10, 0); //Compression Method
      jm::serializeLEInt16(cdfh, 12, 0);//ShxFile last modification time
      jm::serializeLEInt16(cdfh, 14, 0);//ShxFile last modification date
      jm::serializeLEInt32(cdfh, 16, (int32)entry->mCRC);//CRC
      jm::serializeLEInt32(cdfh, 20, (int32)entry->mCompressedSize);//Compressed Size
      jm::serializeLEInt32(cdfh, 24, (int32)entry->mUncompressedSize);//Uncompressed Size
      jm::serializeLEInt16(cdfh, 28, cname.size());//ShxFile name Length
      jm::serializeLEInt16(cdfh, 30, cextra.size());//Extra field length
      jm::serializeLEInt16(cdfh, 32, ccomment.size());//Comment field length
      jm::serializeLEInt16(cdfh, 34, 0);//Disk Number where file starts. Zu 0 gesetzt
      jm::serializeLEInt16(cdfh, 36, 0);//Internal ShxFile Attributes. Zu 0 gesetzt
      jm::serializeLEInt32(cdfh, 38, 0);//External ShxFile Attributes. Zu 0 gesetzt
      jm::serializeLEInt32(cdfh, 42, (int32)entry->mHeaderOffset);//Relative offset to local ShxFile Header

      mFile->write(cdfh, 46);
      if(cname.size() > 0)mFile->write(reinterpret_cast<const uint8*>(cname.constData()), cname.size());
      if(cextra.size() > 0)mFile->write(reinterpret_cast<const uint8*>(cextra.constData()), cextra.size());
      if(ccomment.size() > 0)mFile->write(reinterpret_cast<const uint8*>(ccomment.constData()), ccomment.size());

   }

   size_t end = mFile->position();

   //Frilte End of Directory Record
   uint8 eof[22];
   jm::serializeLEInt32(eof, 0, 0x06054b50);//Signature
   jm::serializeLEInt16(eof, 4, 0);//Number of Disks
   jm::serializeLEInt16(eof, 6, 0);//Disk where centra directory starts.
   jm::serializeLEInt16(eof, 8, (int16)
                        mEntries.size()); //Number of Central directory records on this disk
   jm::serializeLEInt16(eof, 10, (int16)mEntries.size());//Total Number of Central directory records
   jm::serializeLEInt32(eof, 12, (int32)(end - start)); //Size of central directory (bytes)
   jm::serializeLEInt32(eof, 16, (int32)start);//Start of central directory relative to start of archive
   jm::serializeLEInt16(eof, 20, 0);//Comment Length.

   mFile->write(eof, 22);

   mFile->close();
}

void ZipOutputFile::closeEntry()
{
   ZipEntry* entry = static_cast<ZipEntry*>(mEntries.last());

   entry->mUncompressedSize = static_cast<uint32>(mTemp->position());
   mTemp->seek(0);
   ByteArray buffer = ByteArray(entry->mUncompressedSize, 0);
   mTemp->Stream::readFully(buffer);
   mTemp->close();
   mTemp->remove();
   delete mTemp;
   mTemp = nullptr;

   //CRC berechnen
   entry->mCRC = CRC32(buffer.constData(), entry->mUncompressedSize);

   //Schreibe unkomprimiert
   entry->mCompressedSize = entry->mUncompressedSize;

   mFile->write(reinterpret_cast<const uint8*>(buffer.constData()), entry->mUncompressedSize);
   uint32 pos = static_cast<uint32>(mFile->position());

   //Aktualisiere Header
   uint8 lfhfragment[12];
   jm::serializeLEInt32(lfhfragment, 0, (int32)entry->mCRC);
   jm::serializeLEInt32(lfhfragment, 4, (int32)entry->mCompressedSize);
   jm::serializeLEInt32(lfhfragment, 8, (int32)entry->mUncompressedSize);

   mFile->seek(entry->mHeaderOffset + 14);
   mFile->write(lfhfragment, 12);
   mFile->seek(pos);
}

void ZipOutputFile::writeAndClose(jm::File* file)
{
   ZipEntry* entry = static_cast<ZipEntry*>(mEntries.last());

   entry->mUncompressedSize = static_cast<uint32>(file->size());
   file->open(FileMode::kRead);
   ByteArray buffer = ByteArray(entry->mUncompressedSize, 0);
   file->Stream::readFully(buffer);
   file->close();

   mTemp->close();
   mTemp->remove();
   delete mTemp;
   mTemp = nullptr;

   //CRC berechnen
   entry->mCRC = CRC32(buffer.constData(), entry->mUncompressedSize);

   //Schreibe unkomprimiert
   entry->mCompressedSize = entry->mUncompressedSize;

   mFile->write(reinterpret_cast<const uint8*>(buffer.constData()), entry->mUncompressedSize);
   uint32 pos = static_cast<uint32>(mFile->position());

   //Aktualisiere Header
   uint8 lfhfragment[12];
   jm::serializeLEInt32(lfhfragment, 0, (int32)entry->mCRC);
   jm::serializeLEInt32(lfhfragment, 4, (int32)entry->mCompressedSize);
   jm::serializeLEInt32(lfhfragment, 8, (int32)entry->mUncompressedSize);

   mFile->seek(entry->mHeaderOffset + 14);
   mFile->write(lfhfragment, 12);
   mFile->seek(pos);
}

void ZipOutputFile::putNextEntry(ZipEntry* entry)
{
   entry->mHeaderOffset = static_cast<uint32>(mFile->position());

   ByteArray cname = entry->mName.toCString();
   ByteArray cextra = entry->mExtra.toCString();

   //Schreibe Local FileHeader
   uint8 lfh[30];
   jm::serializeLEInt32(lfh, 0, 0x04034b50);//Signature
   jm::serializeLEInt16(lfh, 4, 0);//Minimum Version needed. Auf 0 gesetzt
   jm::serializeLEInt16(lfh, 6, 0);//General Purpose Bit Flag. Auf 0 gesetzt
   jm::serializeLEInt16(lfh, 8, 0);//Compression Method
   jm::serializeLEInt16(lfh, 10, 0);//File last modification time
   jm::serializeLEInt16(lfh, 12, 0);//File last modification date
   jm::serializeLEInt32(lfh, 14, 0);//CRC
   jm::serializeLEInt32(lfh, 18, 0);//Compressed Size
   jm::serializeLEInt32(lfh, 22, 0);//Uncompressed Size
   jm::serializeLEInt16(lfh, 26, cname.size());//File name Length
   jm::serializeLEInt16(lfh, 28, cextra.size());//Extra field length

   mFile->write(lfh, 30);
   if(cname.size() > 0)mFile->write(reinterpret_cast<const uint8*>(cname.constData()), cname.size());
   if(cextra.size() > 0)mFile->write(reinterpret_cast<const uint8*>(cextra.constData()), cextra.size());

   entry->mDataOffset = static_cast<uint32>(mFile->position());

   mTemp = new jm::File(mFile->parent(), "jmzipdata.tmp");
   mTemp->createNewFile();
   mTemp->open(FileMode::kReadWrite);

   mEntries.add(entry, nullptr);
}

void ZipOutputFile::write(uint8* data, int64 offset, size_t length)
{
   mTemp->write(&data[offset], length);
}
