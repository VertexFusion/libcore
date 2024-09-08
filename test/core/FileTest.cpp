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
   SetName("Test File");
}

void FileTest::doTest()
{
    // Test is null
    File file = File();
    TestTrue(file.isNull(),"File::isNull()==true failed");
    TestFalse(file.exists(),"File::exists()==false failed");

    // Test properties on current directory
    file=jm::currentDir();
    TestFalse(file.isNull(),"File::isNull()==false failed");
    TestTrue(file.exists(),"File::exists()==true failed");
    TestTrue(file.isDirectory(),"File::isDirectory()==true failed");
    TestFalse(file.isFile(),"File::isFile()==false failed");
    TestFalse(file.isLink(),"File::isLink()==false failed");
    TestFalse(file.isPipe(),"File::isPipe()==false failed");
    TestFalse(file.isHidden(),"File::isHidden()==false failed");

    // Create new file
    file=File(jm::currentDir(),"test.txt");
    TestFalse(file.isNull(),"File::isNull()==false failed");
    TestFalse(file.exists(),"File::exists()==false failed");
    TestTrue(file.createNewFile(),"File::createNewFile()==true failed");
    TestTrue(file.exists(),"File::exists()==true failed");
    TestFalse(file.isDirectory(),"File::isDirectory()==false failed");
    TestTrue(file.isFile(),"File::isFile()==true failed");
    TestFalse(file.isLink(),"File::isLink()==false failed");
    TestFalse(file.isPipe(),"File::isPipe()==false failed");
    TestFalse(file.isHidden(),"File::isHidden()==false failed");

    TestFalse(file.canExecute(),"File::canExecute()==true failed");
    TestTrue(file.canRead(),"File::canRead()==true failed");
    TestTrue(file.canWrite(),"File::canWrite()==true failed");

    TestEquals(file.name(),"test.txt","file.name()==test.txt failed");
    TestEquals(file.size(),0,"File.size()==0 failed");
    TestEquals(file.parent(),jm::currentDir().absolutePath(),"file.parent() failed");
    TestEquals(file.extension(),"txt","file::extension() failed");
    TestTrue(file.isAbsolute(),"File::isAbsolute() failed");

    // Test writing
    TestFalse(file.isOpen(),"File::isOpen()==false failed");
    TestTrue(file.open(jm::kFmWrite)==jm::eOK,"File::open() failed");
    TestTrue(file.isOpen(),"File::isOpen()==true failed");
    TestTrue(file.position()==0,"File::position()==0 failed");
    TestTrue(file.write((uint8*)"teststring",10)==10,"File::write() failed");
    TestTrue(file.position()==10,"File::position()==10 failed.");
    file.close();
    TestFalse(file.isOpen(),"File::isOpen()==false failed");

    // Test reading 1
    TestTrue(file.open(jm::kFmRead)==jm::eOK,"File::open() failed");
    TestTrue(file.isOpen(),"File::isOpen()==true failed");
    TestTrue(file.position()==0,"File::position()==0 failed");
    jm::ByteArray buffer=jm::ByteArray(10,0);
    TestTrue(file.readFully(buffer,10)==10,"File::readFully() failed");
    TestTrue(file.position()==10,"File::position()==10 failed.");
    file.close();
    TestFalse(file.isOpen(),"File::isOpen()==false failed");
    TestTrue(jm::String(buffer)=="teststring","Read content is wrong");

    // Test reading 2
    TestTrue(file.open(jm::kFmRead)==jm::eOK,"File::open() failed");
    TestTrue(file.isOpen(),"File::isOpen()==true failed");
    TestTrue(file.position()==0,"File::position()==0 failed");
    uint8 buffer2[11];
    buffer2[10]=0;
    TestTrue(file.read(buffer2,10)==10,"File::readFully() failed");
    TestTrue(file.position()==10,"File::position()==10 failed.");
    file.close();
    TestFalse(file.isOpen(),"File::isOpen()==false failed");
    TestTrue(jm::String(buffer2)=="teststring","Read content 2 is wrong");

    // Test positioning
    TestTrue(file.open(jm::kFmRead)==jm::eOK,"File::open() failed");
    TestTrue(file.position()==0,"File::position()==0 failed");
    file.seek(3);
    TestTrue(file.position()==3,"File::position()==3 failed");
    file.seek(6);
    TestTrue(file.position()==6,"File::position()==6 failed");
    file.move(3);
    TestTrue(file.position()==9,"File::position()==9 failed");
    file.move(-7);
    TestTrue(file.position()==2,"File::position()==2 failed");
    file.seek(0);
    TestTrue(file.position()==0,"File::position()==0 failed");
    file.close();
    TestFalse(file.isOpen(),"File::isOpen()==false failed");

    // 2nd and 3rd file
    File file2=File(jm::currentDir(),"test2.txt");
    file2.createNewFile();
    file2.open(jm::kFmWrite);
    file2.write((uint8*)"teststring",10);
    file2.close();

    File file3=File(jm::currentDir(),"test3.txt");
    file3.createNewFile();
    file3.open(jm::kFmWrite);
    file3.write((uint8*)"testString",10);
    file3.close();

    // Test
    TestTrue(file.compareTo(file)==0,"File::compareTo()==0 failed");
    TestTrue(file.compareTo(file3)!=0,"File::compareTo()!=0 failed");

    // Make directory
    File dir = File(jm::currentDir(),"testdir");

    TestFalse(dir.isNull(),"File::isNull()==false failed");
    TestFalse(dir.exists(),"File::exists()==false failed");
    TestTrue(dir.makeDirectory(),"File::makeDirectory()==true failed");
    TestTrue(dir.exists(),"File::exists()==true failed");
    TestTrue(dir.isDirectory(),"File::isDirectory()==true failed");
    TestFalse(dir.isFile(),"File::isFile()==false failed");
    TestFalse(dir.isLink(),"File::isLink()==false failed");
    TestFalse(dir.isPipe(),"File::isPipe()==false failed");
    TestFalse(dir.isHidden(),"File::isHidden()==false failed");
    TestEquals(dir.name(),"testdir","file.name()==test.txt failed");

    // Renaming
    TestTrue(file.renameTo("renfile"),"File::renameTo()==true failed");
    TestEquals(file.name(),"renfile","file.name()==renfile failed");

    TestTrue(dir.renameTo("rendir"),"File::renameTo()==true failed");
    TestEquals(dir.name(),"rendir","file.name()==rendir failed");

    // Last modofied
    Date now=Date();
    Date mod1=file.lastModified();

    // We just test the day, so that is is very unlikely that the test will fail.
    TestTrue(now.time()!=0,"Date==0");
    TestEquals(now.year(),mod1.year(),"Year of file change != 0");
    TestEquals(now.month(),mod1.month(),"Month of file change != 0");
    TestEquals(now.day(),mod1.day(),"Day of file change != 0");

    // Deleting file and directory
    TestTrue(dir.Delete(),"File::Delete() failed");
    TestTrue(file2.Delete(),"File::Delete() failed");
    TestTrue(file3.Delete(),"File::Delete() failed");
    file2=File(jm::currentDir(),"rendir");
    TestFalse(file2.exists(),"File::exists()==false failed");
    file2=File(jm::currentDir(),"test2.txt");
    TestFalse(file2.exists(),"File::exists()==false failed");
    file2=File(jm::currentDir(),"test3.txt");
    TestFalse(file2.exists(),"File::exists()==false failed");

    // Test tags
    StringList tags = file.getTags();
    TestEquals(tags.size(),0,"File::getTags().size()==0 failed");

    TestTrue(file.addTag("tag1")==jm::eOK,"File::addTag() failed");
    tags = file.getTags();
    TestEquals(tags.size(),1,"File::getTags().size()==1 failed");
    if(tags.size()>0)
    {
        TestEquals(tags[0],"tag1","Wrong tag returned");
    }

    TestTrue(file.addTag("tag2")==jm::eOK,"File::addTag() failed");
    tags = file.getTags();
    TestEquals(tags.size(),2,"File::getTags().size()==2 failed");
    if(tags.size()>0)
    {
        tags.sort();
        TestEquals(tags[0],"tag1","Wrong tag returned");
        TestEquals(tags[1],"tag2","Wrong tag returned");
    }

    TestTrue(file.removeTag("tag1")==jm::eOK,"File::removeTag() failed");
    tags = file.getTags();
    TestEquals(tags.size(),1,"File::getTags().size()==1 failed");
    if(tags.size()!=0)
    {
        TestEquals(tags[0],"tag2","Wrong tag returned");
    }

    file.Delete();
}
