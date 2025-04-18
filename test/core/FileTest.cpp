//
//  DateTest.cpp
//  test
//
//  Created by Uwe Runtemund on 07.05.22.
//  Copyright © 2022 Jameo Software. All rights reserved.
//

#include "FileTest.h"
#include "core/File.h"

using namespace jm;

FileTest::FileTest(): Test()
{
   setName("Test File");
}

void FileTest::doTest()
{
   // Test is null
   File file = File();
   testTrue(file.isNull(), "File::isNull()==true failed");
   testFalse(file.exists(), "null File::exists()==false failed");

   // Test properties on current directory
   file = jm::currentDir();
   testFalse(file.isNull(), "File::isNull()==false failed");
   testTrue(file.exists(), "File::exists()==true failed");
   testTrue(file.isDirectory(), "File::isDirectory()==true failed");
   testFalse(file.isFile(), "File::isFile()==false failed");
   testFalse(file.isLink(), "File::isLink()==false failed");
   testFalse(file.isPipe(), "File::isPipe()==false failed");
   testFalse(file.isHidden(), "File::isHidden()==false failed");

   // Create new file
   file = File(jm::currentDir(), "test.txt");
   testFalse(file.isNull(), "File::isNull()==false failed");
   testFalse(file.exists(), "test.txt File::exists()==false failed");
   testTrue(file.createNewFile(), "File::createNewFile()==true failed");
   testTrue(file.exists(), "File::exists()==true failed");
   testFalse(file.isDirectory(), "File::isDirectory()==false failed");
   testTrue(file.isFile(), "File::isFile()==true failed");
   testFalse(file.isLink(), "File::isLink()==false failed");
   testFalse(file.isPipe(), "File::isPipe()==false failed");
   testFalse(file.isHidden(), "File::isHidden()==false failed");

   testFalse(file.canExecute(), "File::canExecute()==true failed");
   testTrue(file.canRead(), "File::canRead()==true failed");
   testTrue(file.canWrite(), "File::canWrite()==true failed");

   testEquals(file.name(), "test.txt", "file.name()==test.txt failed");
   testEquals(file.size(), 0, "File.size()==0 failed");
   testEquals(file.parent(), jm::currentDir().absolutePath(), "file.parent() failed");
   testEquals(file.extension(), "txt", "file::extension() failed");
   testTrue(file.isAbsolute(), "File::isAbsolute() failed");

   // Test writing
   testFalse(file.isOpen(), "File::isOpen()==false failed");
   testTrue(file.open(jm::FileMode::kWrite) == jm::Status::eOK, "File::open() failed");
   testTrue(file.isOpen(), "File::isOpen()==true failed");
   testTrue(file.position() == 0, "File::position()==0 failed");
   testTrue(file.write((uint8*)"teststring", 10) == 10, "File::write() failed");
   testTrue(file.position() == 10, "File::position()==10 failed.");
   file.close();
   testFalse(file.isOpen(), "File::isOpen()==false failed");

   // Test reading 1
   testTrue(file.open(jm::FileMode::kRead) == jm::Status::eOK, "File::open() failed");
   testTrue(file.isOpen(), "File::isOpen()==true failed");
   testTrue(file.position() == 0, "File::position()==0 failed");
   jm::ByteArray buffer = jm::ByteArray(10, 0);
   testTrue(file.readFully(buffer, 10) == 10, "File::readFully() failed");
   testTrue(file.position() == 10, "File::position()==10 failed.");
   file.close();
   testFalse(file.isOpen(), "File::isOpen()==false failed");
   testTrue(jm::String(buffer) == "teststring", "Read content is wrong");

   // Test reading 2
   testTrue(file.open(jm::FileMode::kRead) == jm::Status::eOK, "File::open() failed");
   testTrue(file.isOpen(), "File::isOpen()==true failed");
   testTrue(file.position() == 0, "File::position()==0 failed");
   uint8 buffer2[11];
   buffer2[10] = 0;
   testTrue(file.read(buffer2, 10) == 10, "File::readFully() failed");
   testTrue(file.position() == 10, "File::position()==10 failed.");
   file.close();
   testFalse(file.isOpen(), "File::isOpen()==false failed");
   testTrue(jm::String(buffer2) == "teststring", "Read content 2 is wrong");

   // Test positioning
   testTrue(file.open(jm::FileMode::kRead) == jm::Status::eOK, "File::open() failed");
   testTrue(file.position() == 0, "File::position()==0 failed");
   file.seek(3);
   testTrue(file.position() == 3, "File::position()==3 failed");
   file.seek(6);
   testTrue(file.position() == 6, "File::position()==6 failed");
   file.move(3);
   testTrue(file.position() == 9, "File::position()==9 failed");
   file.move(-7);
   testTrue(file.position() == 2, "File::position()==2 failed");
   file.seek(0);
   testTrue(file.position() == 0, "File::position()==0 failed");
   file.close();
   testFalse(file.isOpen(), "File::isOpen()==false failed");

   // 2nd and 3rd file
   File file2 = File(jm::currentDir(), "test2.txt");
   file2.createNewFile();
   file2.open(jm::FileMode::kWrite);
   file2.write((uint8*)"teststring", 10);
   file2.close();

   File file3 = File(jm::currentDir(), "test3.txt");
   file3.createNewFile();
   file3.open(jm::FileMode::kWrite);
   file3.write((uint8*)"testString", 10);
   file3.close();

   // Test
   testTrue(file.compareTo(file) == 0, "File::compareTo()==0 failed");
   testTrue(file.compareTo(file3) != 0, "File::compareTo()!=0 failed");

   // Make directory
   File dir = File(jm::currentDir(), "testdir");

   testFalse(dir.isNull(), "File::isNull()==false failed");
   testFalse(dir.exists(), dir.absolutePath() + " File::exists()==false failed");
   testTrue(dir.makeDirectory(), "File::makeDirectory()==true failed");
   testTrue(dir.exists(), "File::exists()==true failed");
   testTrue(dir.isDirectory(), "File::isDirectory()==true failed");
   testFalse(dir.isFile(), "File::isFile()==false failed");
   testFalse(dir.isLink(), "File::isLink()==false failed");
   testFalse(dir.isPipe(), "File::isPipe()==false failed");
   testFalse(dir.isHidden(), "File::isHidden()==false failed");
   testEquals(dir.name(), "testdir", "file.name()==test.txt failed");

   // Renaming
   testTrue(file.renameTo("renfile"), "renfile File::renameTo()==true failed");
   testEquals(file.name(), "renfile", "file.name()==renfile failed");

   jm::String newName = File(jm::currentDir(), "rendir").absolutePath();
   testTrue(dir.renameTo(newName), "rendir File::renameTo()==true failed");
   testEquals(dir.name(), "rendir", "file.name()==rendir failed");

   // Last modofied
   Date now = Date();
   Date mod1 = file.lastModified();

   // We just test the day, so that is is very unlikely that the test will fail.
   testTrue(now.time() != 0, "Date==0");
   testEquals(now.year(), mod1.year(), "Year of file change != 0");
   testEquals(now.month(), mod1.month(), "Month of file change != 0");
   testEquals(now.day(), mod1.day(), "Day of file change != 0");

   // Deleting file and directory
   testTrue(dir.remove(), "dir File::remove() failed");
   testTrue(file2.remove(), "file2 File::remove() failed");
   testTrue(file3.remove(), "file3 File::remove() failed");
   file2 = File(jm::currentDir(), "rendir");
   testFalse(file2.exists(), "rendir File::exists()==false failed");
   file2 = File(jm::currentDir(), "test2.txt");
   testFalse(file2.exists(), "test2.txt File::exists()==false failed");
   file2 = File(jm::currentDir(), "test3.txt");
   testFalse(file2.exists(), "test3.txt File::exists()==false failed");


   // Test tags (actually only on macOS and Linux)
   #if defined(__APPLE__) || defined(__linux__)

   StringList tags = file.getTags();
   testEquals(tags.size(), 0, "File::getTags().size()==0 failed");

   testTrue(file.addTag("tag1") == jm::Status::eOK, "File::addTag() failed");
   tags = file.getTags();
   testEquals(tags.size(), 1, "File::getTags().size()==1 failed");
   if(tags.size() > 0)
   {
      testEquals(tags[0], "tag1", "Wrong tag returned");
   }

   testTrue(file.addTag("tag2") == jm::Status::eOK, "File::addTag() failed");
   tags = file.getTags();
   testEquals(tags.size(), 2, "File::getTags().size()==2 failed");
   if(tags.size() > 0)
   {
      tags.sort();
      testEquals(tags[0], "tag1", "Wrong tag returned");
      testEquals(tags[1], "tag2", "Wrong tag returned");
   }

   testTrue(file.removeTag("tag1") == jm::Status::eOK, "File::removeTag() failed");
   tags = file.getTags();
   testEquals(tags.size(), 1, "File::getTags().size()==1 failed");
   if(tags.size() != 0)
   {
      testEquals(tags[0], "tag2", "Wrong tag returned");
   }

   // Remove last tag
   testTrue(file.removeTag("tag2") == jm::Status::eOK, "File::removeTag() failed");
   tags = file.getTags();
   testEquals(tags.size(), 0, "File::getTags().size()==0 failed");
   #endif

   file.remove();
}
