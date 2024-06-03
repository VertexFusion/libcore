////////////////////////////////////////////////////////////////////////////////////////////////////
// Name:        File.cpp
// Library:     Jameo Core Library
// Purpose:     Implementation of file
//
// Author:      Uwe Runtemund (2013-today)
// Modified by:
// Created:     12.05.2013
//
// Copyright:   (c) 2013 Jameo Software, Germany. https://jameo.de
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

File::File(): Stream(), Comparable<File>()
{
   mCstr = ByteArray();
   mHandle = NULL;
}

File::File(const String &pathname): Stream(), Comparable<File>()
{
   mPathname = Normalize(pathname);
   SetCString();
   mHandle = NULL;
}

File::File(String parent, String child): Stream(), Comparable<File>()
{
   if(child.Length() < 1)throw new Exception(Tr("Child is empty."));
   mPathname = Resolve(Normalize(parent), Normalize(child));
   SetCString();
   mHandle = NULL;
}

File::File(const File& parent, String child): Stream(), Comparable<File>()
{
   if(child.Length() < 1)throw new Exception(Tr("Child is empty."));
   mPathname = Resolve(parent.GetAbsolutePath(), Normalize(child));
   SetCString();
   mHandle = NULL;
}

File::File(const File &other): Stream(), Comparable<File>()
{
   mPathname = other.mPathname;
   mHandle = other.mHandle;
   if(mPathname.Length() > 0)SetCString();
   else mCstr = ByteArray();
}


File::~File()
{
}

File& File::operator=(const File &another)
{
   if(this != &another)
   {
      mPathname = another.mPathname;
      mHandle = another.mHandle;
      if (mPathname.Length() > 0)SetCString();
      else mCstr = ByteArray();
   }

   return *this;
}


void File::SetCString()
{
   #ifdef __APPLE__ //macOS
   // Under 10.10 umlauts are transferred correctly...
   mCstr = mPathname.ToCString(Charset::ForName("UTF-8"));
   #elif defined __linux__ //Linux
   mCstr = mPathname.ToCString(Charset::ForName("UTF-8"));
   #elif defined _WIN32 //Windows
   // Must be under Windows Windows-1252 for fopen
   mCstr = mPathname.ToCString(Charset::ForName("Windows-1252"));
   #endif
}

String File::Resolve(String parent, String child)
{
   // Parent and child are normalized
   String sep;
   sep.Append(DIR_SEP);

   // under UNIX:
   if(parent.Length() < 1 && child.Length() < 1)return sep;

   // If child begins with separator
   if(child.CharAt(0) == DIR_SEP)
   {
      if(parent.Equals(sep))return child;
      return parent + child;
   }
   else
   {
      if(parent.Equals(sep))return parent + child;
      return parent + sep + child;
   }
}

String File::Normalize(const String &path)
{
   String pathname = path;
   Integer length = pathname.Length();
   Char prev = 0;

   for(Integer a = 0; a < length; a++)
   {
      Char character = pathname.CharAt(a);

      // Remove duplicate separator
      if(prev == DIR_SEP && character == DIR_SEP)
      {
         pathname.DeleteCharAt(a);
         a--;
         length--;
      }
      prev = character;
   }

   // If last character is path separator and file name is longer than 1
   if(prev == DIR_SEP && pathname.Length() > 1)pathname.DeleteCharAt(pathname.Length() - 1);

   return pathname;
}

bool File::MakeDirectory()
{
   #if defined(__APPLE__) || defined(__linux__) // macOS and Linux are identically

   int32 result = mkdir(mCstr.ConstData(), S_IRWXU | S_IRGRP | S_IROTH);
   return result == 0;

   #elif defined _WIN32//Windows
   int32 result = _mkdir(mCstr.ConstData());
   return result == 0;
   #endif
}

bool File::Exists() const
{

   #if defined(__APPLE__) || defined(__linux__) // macOS and Linux are identically

   return access(mCstr.ConstData(), F_OK) == 0;

   #elif defined _WIN32//Windows
   if(mCstr.Size() == 0)return false;

   struct stat filestat;
   int32 result = stat(mCstr.ConstData(), &filestat);
   return result == 0;

   #endif
}

bool File::CanRead() const
{

   #if defined(__APPLE__) || defined(__linux__) // macOS and Linux are identically

   return access(mCstr.ConstData(), R_OK) == 0;

   #elif defined _WIN32//Windows

   struct stat filestat;
   int32 result = stat(mCstr.ConstData(), &filestat);
   if(result != 0)return false;  //Existiert nicht
   if(filestat.st_mode & _S_IREAD) return true;
   return false;

   #endif

}

bool File::CanWrite() const
{

   #if defined(__APPLE__) || defined(__linux__) // macOS and Linux are identically

   return access(mCstr.ConstData(), W_OK) == 0;

   #elif defined _WIN32//Windows

   struct stat filestat;
   int32 result = stat(mCstr.ConstData(), &filestat);
   if(result != 0)return false;  //Existiert nicht
   if(filestat.st_mode & _S_IWRITE) return true;
   return false;

   #endif

}

bool File::IsDirectory() const
{
   #if defined(__APPLE__) || defined(__linux__) // macOS and Linux are identically

   struct stat st;
   lstat(mCstr.ConstData(), &st);
   bool ret = S_ISDIR(st.st_mode);
   return ret;

   #elif defined _WIN32//Windows

   struct stat filestat;
   int32 result = stat(mCstr.ConstData(), &filestat);
   if(result != 0)return false;  //Existiert nicht
   if(filestat.st_mode & _S_IFDIR) return true;
   return false;

   #endif

}

bool File::IsFile() const
{

   #if defined(__APPLE__) || defined(__linux__) // macOS and Linux are identically

   struct stat st;
   lstat(mCstr.ConstData(), &st);
   bool ret = S_ISREG(st.st_mode);
   return ret;


   #elif defined _WIN32//Windows

   struct stat filestat;
   int32 result = stat(mCstr.ConstData(), &filestat);
   if(result != 0)return false;  //Existiert nicht
   if(filestat.st_mode & _S_IFREG) return true;
   return false;

   #endif

}

bool File::IsHidden() const
{

   #if defined(__APPLE__) || defined(__linux__) // macOS and Linux are identically

   return GetName().CharAt(0) == '.';

   #elif defined _WIN32//Windows

   struct stat filestat;
   int32 result = stat(mCstr.ConstData(), &filestat);
   if(result != 0)return false;  //Existiert nicht
   if((filestat.st_mode & _S_IFREG) == 0) return true;
   return false;

   #endif

}

bool File::IsLink() const
{

   #if defined(__APPLE__) || defined(__linux__) // macOS and Linux are identically

   struct stat st;
   lstat(mCstr.ConstData(), &st);
   bool ret = S_ISLNK(st.st_mode);
   return ret;


   #elif defined _WIN32//Windows

   /* \todo Muss noch geklärt werden, wann ein Symlink vorliegt
   struct stat filestat;
   int32 result = stat( cstr, &filestat );
   if( result != 0 )return false;//Existiert nicht
   if( filestat.st_mode & _S_IFLNK ) return true;*/
   return false;

   #endif

}

bool File::IsPipe() const
{

   #if defined(__APPLE__) || defined(__linux__) // macOS and Linux are identically

   struct stat st;
   lstat(mCstr.ConstData(), &st);
   bool ret = S_ISFIFO(st.st_mode);
   return ret;


   #elif defined _WIN32//Windows

   struct stat filestat;
   int32 result = stat(mCstr.ConstData(), &filestat);
   if(result != 0)return false;  //Existiert nicht
   if(filestat.st_mode & _S_IFIFO) return true;
   return false;

   #endif

}

Date File::LastModified() const
{
   #if defined(__APPLE__) //macOS

   struct stat st;
   lstat(mCstr.ConstData(), &st);

   //Umrechnen
   timespec tm = st.st_mtimespec;
   int64 time = tm.tv_sec * 1000LL;
   time += (tm.tv_nsec / 1000LL);

   return Date(time);

   #elif defined(__linux__) //Linux

   struct stat st;
   lstat(mCstr.ConstData(), &st);

   //Umrechnen
   timespec tm = st.st_mtim;
   int64 time = tm.tv_sec * 1000LL;
   time += (tm.tv_nsec / 1000LL);

   return Date(time);

   #elif defined _WIN32//Windows

   struct stat st;
   stat(mCstr.ConstData(), &st);

   // Convert
   const time_t ct = st.st_mtime;//time_t is the time in seconds
   int64 epoch = (int64)ct;
   return Date(epoch * 1000LL);
   #endif

}


bool File::Delete()
{
   if(remove(mCstr.ConstData()) == 0)return true;
   else return false;
}

bool File::MoveToTrash()
{
   #if defined(__APPLE__)//macOS

   return File_MoveToTrash(mCstr.ConstData());

   #elif defined(__linux__) //Linus


   #elif defined _WIN32//Windows


   #endif

   return false;
}

bool File::RenameTo(const String &newPath)
{
   int32 result;


   #ifdef __APPLE__ //macOS
   ByteArray newname = newPath.ToCString();
   #elif defined __linux__ //Linux
   ByteArray newname = newPath.ToCString();
   #elif defined _WIN32 //Windows
   ByteArray newname = newPath.ToCString(Charset::ForName("Windows-1252"));
   #endif


   result = rename(mCstr.ConstData(), newname.ConstData());

   if(result == 0)
   {
      mCstr = newname;
      return true;
   }
   else
   {
      return false;
   }
}


Array<File>* File::ListFiles()const
{
   if(!IsDirectory())return NULL;//throw new Exception("ShxFile \"" + GetAbsolutePath() + "\" is not a directory.");

   #if defined(__APPLE__) || defined(__linux__) // macOS and Linux are identically


   DIR* dp;
   struct dirent* dirp;
   dp = opendir(mCstr.ConstData());

   if(dp == NULL)
   {
      throw new Exception(Tr("Cannot open directory"));
   }

   uint32 fileCount = 0;

   //Zähle Einträge
   while(readdir(dp) != NULL)fileCount++;

   //Zum Anfang
   rewinddir(dp);

   //Array füllen
   Array<File>* list = new Array<File>(fileCount);
   uint32 cnt = 0;

   while((dirp = readdir(dp)) != NULL)
   {
      String filename = String(dirp->d_name);
      list->Set(cnt++, File(*this, filename));
   }
   closedir(dp);

   return list;


   #elif defined _WIN32//Windows

   HANDLE hFind;
   WIN32_FIND_DATA data;

   String tmp = mPathname;
   tmp.Append(DIR_SEP);
   tmp.Append('*');
   uint16* wstr = tmp.ToWString();

   hFind = FindFirstFile((LPCWSTR)wstr, &data);

   if(hFind != INVALID_HANDLE_VALUE)
   {
      std::vector<String> files;
      do
      {
         // cFilename is the raw file name without path.
         uint16* wstr2 = (uint16*)data.cFileName;
         uint32 len = 0;
         while(wstr2[len] != 0)len++;
         files.push_back(String(wstr2, len));
      }
      while(FindNextFile(hFind, &data));
      FindClose(hFind);

      // Fill array
      Array<File>* list = new Array<File>((uint32)files.size());
      for(uint32 a = 0; a < files.size(); a++)
      {
         // Only the file name is stored in Files.
         // The path name must therefore precede it for it to work...
         list->Set(a, File(mPathname, files[a]));
      }

      delete wstr;
      return list;
   }
   else
   {
      delete wstr;
      throw new Exception(Tr("Cannot open directory"));
   }

   #endif
}


Integer File::Length() const
{
   struct stat filestat;
   int32 result = stat(mCstr.ConstData(), &filestat);

   // If it doesn't exist, then I can't read it.
   if(result != 0)throw new Exception(Tr("File \"%1\" does not exist.").Arg(GetAbsolutePath()));

   return Integer((uint64)filestat.st_size);
}


const String& File::GetAbsolutePath() const
{
   return mPathname;
}

String File::GetPath() const
{
   return mPathname;
}

String File::GetParent() const
{
   Integer idx = mPathname.LastIndexOf(DIR_SEP);
   if(idx < 0)idx = 0;
   return mPathname.Substring(0, idx);
}

String File::GetName() const
{
   return mPathname.Substring(mPathname.LastIndexOf(DIR_SEP) + 1);
}

String File::GetExtension() const
{
   return mPathname.Substring(mPathname.LastIndexOf('.') + 1);
}

bool File::CreateNewFile()
{
   #if defined(__APPLE__) || defined(__linux__)//linux,macOS und ios
   mHandle = fopen(mCstr.ConstData(), "wb");
   Integer ret = mHandle != NULL;
   #elif defined _WIN32 //Windows
   Integer ret = fopen_s(&mHandle, mCstr.ConstData(), "wb");
   #endif

   Close();
   return ret == 0;
}

void File::Open(FileMode mode)
{
   Integer ret = 0;

   #if defined(__APPLE__) || defined(__linux__)//linux,macOS und ios
   switch(mode)
   {
      case kFmRead:
         mHandle = fopen(mCstr.ConstData(), "rb");
         break;

      case kFmWrite:
         mHandle = fopen(mCstr.ConstData(), "wb");
         break;

      case kFmReadWrite:
         mHandle = fopen(mCstr.ConstData(), "rb+");
         break;
   }
   ret = mHandle != NULL;
   #elif defined _WIN32 //Windows
   switch(mode)
   {
      case kFmRead:
         ret = fopen_s(&mHandle, mCstr.ConstData(), "rb");
         break;

      case kFmWrite:
         ret = fopen_s(&mHandle, mCstr.ConstData(), "wb");
         break;

      case kFmReadWrite:
         ret = fopen_s(&mHandle, mCstr.ConstData(), "rb+");
         break;
   }
   #endif

   if(mHandle == NULL)
   {
      if(errno == EACCES)throw new Exception(Tr("Permission denied! \"%1\"").Arg(mPathname));
      if(errno == ENOENT)throw new Exception(Tr("File not found! \"%1\"").Arg(mPathname));
      if(errno == ETIMEDOUT)throw new Exception(Tr("Connection timed out! \"%1\"").Arg(mPathname));
      if(errno == ENOTDIR)throw new Exception(Tr("Not a directory \"%1\"").Arg(mPathname));
      throw new Exception(Tr("Cannot open file! \"%1\" Errno: %2").Arg(mPathname).Arg(Integer(errno)));
   }
}

bool File::IsOpen()
{
   return mHandle != NULL;
}

void File::Close()
{
   if(mHandle == NULL)return;
   int32 eof = fclose(mHandle);
   if(eof == EOF)throw new Exception(Tr("Error while closing file!"));
   mHandle = NULL;
}

void File::Seek(Integer position)
{
   //Data type is long int in fseek
   size_t res = fseek(mHandle, (long int)position, SEEK_SET);
   if(res != 0)throw new Exception(Tr("Error while moving file reading pointer!"));
}

void File::Move(Integer offset)
{
   //Data type is long int in fseek
   size_t res = fseek(mHandle, (long int)offset, SEEK_CUR);
   if(res != 0)throw new Exception(Tr("Error while moving file reading pointer!"));
}

Integer File::GetPosition()
{
   return Integer((uint64)ftell(mHandle));
}


Integer File::Read(uint8* buffer, Integer length)
{
   return (uint32)fread(buffer, 1, length, mHandle);
}

Integer File::ReadFully(ByteArray& buffer, Integer length)
{
   Integer rest = length;
   Integer read = 0;
   Integer step;
   uint8* buf = (uint8*)buffer.Data();

   while((rest > 0) && ((step = Read(&buf[read], rest)) > 0))
   {
      read += step;
      rest -= step;
   };

   return read;
}

Integer File::Write(const uint8* buffer, Integer length)
{
   return fwrite(buffer, 1, length, mHandle);
}

int32 File::CompareTo(const File &other) const
{
   //Erst Verzeichnis
   bool d1 = IsDirectory();
   bool d2 = other.IsDirectory();
   if(d1 != d2)
   {
      if(d1)return -1;
      return 1;
   }

   //Dann Name
   return mPathname.CompareTo(other.mPathname);
}

StringList File::GetTags()const
{
   #ifdef __APPLE__ //macOS

   // Create necessary system related objects
   CFStringRef cfstr = CFStringCreateWithCString(kCFAllocatorDefault,
                       mCstr.ConstData(),
                       kCFStringEncodingUTF8);
   CFURLRef urlref = CFURLCreateWithFileSystemPath(kCFAllocatorDefault,
                     cfstr,
                     kCFURLPOSIXPathStyle,
                     IsDirectory());

   // Query tags
   CFArrayRef tags = NULL;
   Boolean result = CFURLCopyResourcePropertyForKey(urlref,
                    kCFURLTagNamesKey,
                    &tags,
                    NULL);

   // Clean unnecessary stuff
   CFRelease(cfstr);
   CFRelease(urlref);

   if(result == true && tags != NULL)
   {
      // Extract the tags to our string list
      StringList taglist;
      Integer count = (uint32) CFArrayGetCount(tags);
      if(count > 0)
      {
         for(Integer index = 0; index < count; index++)
         {
            CFStringRef str = (CFStringRef)CFArrayGetValueAtIndex(tags, index);
            taglist << String::FromCFString(str);
         }

         // Clean up
         CFRelease(tags);

         return taglist;
      }
   }

   if(tags != NULL)CFRelease(tags);

   #endif

   #ifdef __linux__
   
	const int sz=4096;
	char buffer[sz];
	int result = getxattr(mCstr.ConstData(),"user.xdg.tags",buffer,sz);

	if(result>0)
	{
		// Data is store usually as comma(,) separated list.
		// So we just need to replace ',' by '\n'.
		ByteArray tagList = ByteArray((int8*)buffer,result);
		//TODO: tagList.replace(',','\n');
	}
   #endif

   // Return empty if no tags found array
   return StringList();
}

VxfErrorStatus File::AddTag(const String &tag)
{
   #ifdef __APPLE__ //macOS
   StringList oldtags = GetTags();

   //Check is tag is present, if yes, just return
   for(Integer index = 0; index < oldtags.Size(); index++)
   {
      if(oldtags[index].EqualsIgnoreCase(tag))return eOK;
   }

   //Create new array and append tag
   Integer newsize = oldtags.Size() + 1;
   CFStringRef* strs = new CFStringRef[newsize];
   for(Integer index = 0; index < newsize - 1; index++)
   {
      strs[index] = oldtags[index].ToCFString();;
   }

   strs[newsize - 1] = tag.ToCFString();

   CFArrayRef newtags = CFArrayCreate(NULL, (const void**)strs, newsize, &kCFTypeArrayCallBacks);

   //
   //
   //

   // Create necessary system related objects
   CFStringRef cfstr = CFStringCreateWithCString(kCFAllocatorDefault,
                       mCstr.ConstData(),
                       kCFStringEncodingUTF8);
   CFURLRef urlref = CFURLCreateWithFileSystemPath(kCFAllocatorDefault,
                     cfstr,
                     kCFURLPOSIXPathStyle,
                     IsDirectory());

   // Query tags
   Boolean result = CFURLSetResourcePropertyForKey(urlref,
                    kCFURLTagNamesKey,
                    newtags,
                    NULL);

   // Clean unnecessary stuff

   for(Integer index = 0; index < newsize; index++)
   {
      CFRelease(strs[index]);
   }

   CFRelease(cfstr);
   CFRelease(urlref);
   CFRelease(newtags);

   if(result == true)return eOK;
   else return eNo;

   #endif
   return eNotImplemented;
}

VxfErrorStatus File::RemoveTag(const String &tag)
{
   #ifdef __APPLE__ //macOS
   StringList oldtags = GetTags();

   //Check is tag is present, if not, just return
   bool found = false;
   for(Integer index = 0; index < oldtags.Size(); index++)
   {
      if(oldtags[index].EqualsIgnoreCase(tag))
      {
         found = true;
         break;
      }
   }
   if(!found)return eOK;

   //Create new array and remove tag
   Integer newsize = oldtags.Size() - 1;
   CFStringRef* strs = new CFStringRef[newsize];
   Integer cnt = 0;
   for(Integer index = 0; index < newsize + 1; index++)
   {
      if(oldtags[index].EqualsIgnoreCase(tag) == false)
      {
         CFStringRef cfstr = oldtags[index].ToCFString();
         strs[cnt] = cfstr;
         cnt++;
      }
   }

   CFArrayRef newtags = CFArrayCreate(NULL, (const void**)strs, newsize, &kCFTypeArrayCallBacks);

   //
   //
   //

   // Create necessary system related objects
   CFStringRef cfstr = CFStringCreateWithCString(kCFAllocatorDefault,
                       mCstr.ConstData(),
                       kCFStringEncodingUTF8);
   CFURLRef urlref = CFURLCreateWithFileSystemPath(kCFAllocatorDefault,
                     cfstr,
                     kCFURLPOSIXPathStyle,
                     IsDirectory());

   // Query tags
   Boolean result = CFURLSetResourcePropertyForKey(urlref,
                    kCFURLTagNamesKey,
                    newtags,
                    NULL);

   // Clean unnecessary stuff

   for(Integer index = 0; index < newsize; index++)
   {
      CFRelease(strs[index]);
   }

   CFRelease(cfstr);
   CFRelease(urlref);
   CFRelease(newtags);

   if(result == true)return eOK;
   else return eNo;

   #endif
   return eNotImplemented;
}


String jm::ExecPath()
{

   #ifdef __APPLE__ //macOS
   uint32_t size = 1024;
   char path[1024];
   int ok = _NSGetExecutablePath(path, &size);
   if(ok < 0)
   {
      throw new Exception(Tr("Cannot determinate executable Path"));
   }
   path[size - 1] = '\0';
   String ret = String(path);
   return ret;
   #elif defined __linux__ //Linux
   char buff[1024];
   ssize_t len = ::readlink("/proc/self/exe", buff, sizeof(buff) - 1);
   if(len > 0)
   {
      buff[len] = '\0';
      return String(buff);
   }
   else
   {
      return jm::kEmptyString;
   }
   #elif defined _WIN32 //Windows

   const uint32 size = MAX_PATH;
   uint16 path[size];

   HMODULE hModule = GetModuleHandle(NULL);
   if(hModule != NULL)
   {

      // When passing NULL to GetModuleHandle, it returns handle of exe itself
      GetModuleFileNameW(hModule, (LPWSTR)path, size);

      path[size - 1] = '\0';
      String ret;

      uint32 pos = 0;
      while(path[pos] != 0)ret.Append(path[pos++]);

      return ret;
   }
   throw new Exception(Tr("Cannot determinate executable Path"));
   #endif

}

String jm::ExecName()
{
   String exec = ExecPath();
   Integer pos = exec.LastIndexOf(DIR_SEP);
   return exec.Substring(pos + 1);
}

String jm::ExecDir()
{
   String exec = ExecPath();
   Integer pos = exec.LastIndexOf(DIR_SEP);
   if(exec.CharAt(pos - 1) == '.' && exec.CharAt(pos - 2) == DIR_SEP)pos -= 2;
   return exec.Substring(0, pos);
}


   #ifdef __APPLE__
File jm::ResourceDir(const String &bundleId)
{

   //CFString aus Bundle-ID erzeugen
   CFStringRef cfstr = bundleId.ToCFString();

   //Erzeuge Referenzen auf das Bundle, die BundleURL und die Ressourcen-URL
   CFBundleRef thisBundle = CFBundleGetBundleWithIdentifier(cfstr);
   if(thisBundle == NULL)
   {
      //Aufräumen
      CFRelease(cfstr);

      System::Log(Tr("BundleRef for %1 not found. Cannot determine resource directory.").Arg(bundleId), kLogError);
      return File("/");
   }

   CFURLRef resourceDirURL = CFBundleCopyResourcesDirectoryURL(thisBundle);


   #if TARGET_OS_IPHONE == 1 // iOS add -DTARGET_OS_IPHONE as compiler option if necessary

   // On iOS, the resource folder is also the root folder of the app...

   // Convert bundle URL to string
   CFStringRef sr = CFURLCopyPath(resourceDirURL);
   String filename = String::FromCFString(sr);

   // Clean up
   CFRelease(cfstr);
   CFRelease(sr);
   CFRelease(resourceDirURL);
   delete cstring;

   // Return
   return new File(filename);
}

   #else //macOS

   CFURLRef bundleURL = CFBundleCopyBundleURL(thisBundle);

   // Attention URL can be coded. For spaces, this is e.g. %20

   // Convert bundle URL to string
   CFStringRef sr1 = CFURLCopyPath(bundleURL);
   String filename = URLDecode(String::FromCFString(sr1));

   // Attach resource URL
   CFStringRef sr2 = CFURLCopyPath(resourceDirURL);
   filename.Append(URLDecode(String::FromCFString(sr2)));

   // Clean up
   CFRelease(cfstr);
   CFRelease(bundleURL);
   CFRelease(resourceDirURL);
   CFRelease(sr1);
   CFRelease(sr2);

   // Return
   return File(filename);
   }
   #endif

   #elif defined __linux__ //Linux
File jm::ResourceDir(const String &/*bundleId*/)
{
   // The resource directory is /usr/share/appname
   return File("/usr/share/"+ExecName());
}
   #elif defined _WIN32 //Windows
File jm::ResourceDir(const String &/*bundleId*/)
{
   // The Exec-Dir is currently used as the resource directory
   return File(ExecDir());
}
   #endif

File jm::PropertyDir()
{
   #ifdef __APPLE__ //macOS und ios
   // Method is designed for IOS so far, but also works under macOS, but still needs to be tested.
   char* home = getenv("HOME");
   //IOS: https://developer.apple.com/library/mac/documentation/FileManagement/Conceptual/FileSystemProgrammingGuide/FileSystemOverview/FileSystemOverview.html
   return File(home, "Library");
   #elif defined __linux__ //Linux
   // A subdirectory around the home folder with the application name is provided as the property
   // directory
   char* home = getenv("HOME");
   return File(home, "." + ExecName());
   #elif defined _WIN32 //Windows

   return UserDir();
   /*	uint16* path[MAX_PATH];

   	if (SUCCEEDED(SHGetKnownFolderPath(NULL, CSIDL_PROFILE, NULL, 0,(WCHAR*)path)))
   	{
   		uint32 textlength = 0;
   		while (path[textlength] != 0)textlength++;

   		String ret = String((uint16*)path, textlength);

   		// The Exec-Dir is currently used as the PropertyDir
   		return new ShxFile(ret);
   	}

   	return NULL;
   	*/
   #endif

}

File jm::UserDir()
{
   #ifdef __APPLE__ //macOS and ios
   // Method is designed for IOS so far, but also works under macOS, but still needs to be tested.
   char* home = getenv("HOME");
   //IOS: https://developer.apple.com/library/mac/documentation/FileManagement/Conceptual/FileSystemProgrammingGuide/FileSystemOverview/FileSystemOverview.html
   return File(home);
   #elif defined __linux__ //Linux
   // A subdirectory around the home folder with the application name is provided as the property
   // directory
   char* home = getenv("HOME");
   return File(home);
   #elif defined _WIN32 //Windows

   uint16 path[MAX_PATH];

   if(SUCCEEDED(SHGetFolderPath(NULL, CSIDL_PROFILE, NULL, 0, (WCHAR *)&path)))
   {
      uint32 textlength = 0;
      while(path[textlength] != 0)textlength++;

      String ret = String((uint16*)path, textlength);

      // The Exec-Dir is currently used as the PropertyDir
      return File(ret);
   }

   return File();
   #endif

}

