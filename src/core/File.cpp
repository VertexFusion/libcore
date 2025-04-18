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


#include "PrecompiledCore.hpp"

using namespace jm;

File::File(): Stream(), Comparable<File>()
{
   mCstr = ByteArray();
   mHandle = nullptr;
}

File::File(const String& pathname): Stream(), Comparable<File>()
{
   mPathname = normalize(pathname);
   setCString();
   mHandle = nullptr;
}

File::File(String parent, String child): Stream(), Comparable<File>()
{
   if(child.size() < 1)throw Exception(Tr("Child is empty."));
   mPathname = resolve(normalize(parent), normalize(child));
   setCString();
   mHandle = nullptr;
}

File::File(const File& parent, String child): Stream(), Comparable<File>()
{
   if(child.size() < 1)throw Exception(Tr("Child is empty."));
   mPathname = resolve(parent.absolutePath(), normalize(child));
   setCString();
   mHandle = nullptr;
}

File::File(const File& other): Stream(), Comparable<File>()
{
   mPathname = other.mPathname;
   mHandle = other.mHandle;
   if(mPathname.size() > 0)setCString();
   else mCstr = ByteArray();
}


File::~File()
{
}

File& File::operator=(const File& another)
{
   if(this != &another)
   {
      mPathname = another.mPathname;
      mHandle = another.mHandle;
      if(mPathname.size() > 0)setCString();
      else mCstr = ByteArray();
   }

   return *this;
}

bool File::isNull()const
{
   return mCstr.size() == 0;
}


void File::setCString()
{
   #ifdef __APPLE__ //macOS
   // Under 10.10 umlauts are transferred correctly...
   mCstr = mPathname.toCString(Charset::forName("UTF-8"));
   #elif defined __linux__ //Linux
   mCstr = mPathname.toCString(Charset::forName("UTF-8"));
   #elif defined _WIN32 //Windows
   // Must be under Windows Windows-1252 for fopen
   mCstr = mPathname.toCString(Charset::forName("Windows-1252"));
   #endif
}

String File::resolve(String parent, String child)
{
   // Parent and child are normalized
   String sep;
   sep.append(DIR_SEP);

   // under UNIX:
   if(parent.size() < 1 && child.size() < 1)return sep;

   // If child begins with separator
   if(child.charAt(0) == DIR_SEP)
   {
      if(parent.equals(sep))return child;
      return parent + child;
   }
   else
   {
      if(parent.equals(sep))return parent + child;
      return parent + sep + child;
   }
}

String File::normalize(const String& path)
{
   String pathname = path;
   int64 length = pathname.size();
   Char prev = 0;

   for(int64 a = 0; a < length; a++)
   {
      Char character = pathname.charAt(a);

      // Remove duplicate separator
      if(prev == DIR_SEP && character == DIR_SEP)
      {
         pathname.deleteCharAt(a);
         a--;
         length--;
      }
      prev = character;
   }

   // If last character is path separator and file name is longer than 1
   if(prev == DIR_SEP && pathname.size() > 1)pathname.deleteCharAt(pathname.size() - 1);

   return pathname;
}

bool File::makeDirectory()
{
   #if defined(__APPLE__) || defined(__linux__) // macOS and Linux are identically

   int32 result = mkdir(mCstr.constData(), S_IRWXU | S_IRGRP | S_IROTH);
   return result == 0;

   #elif defined _WIN32//Windows
   int32 result = _mkdir(mCstr.constData());
   return result == 0;
   #endif
}

bool File::exists() const
{

   #if defined(__APPLE__) || defined(__linux__) // macOS and Linux are identically

   return access(mCstr.constData(), F_OK) == 0;

   #elif defined _WIN32//Windows
   if(mCstr.size() == 0)return false;

   struct stat filestat;
   int32 result = stat(mCstr.constData(), &filestat);
   return result == 0;
   //return PathFileExistsA(mCstr.constData());

   #endif
}

bool File::canRead() const
{

   #if defined(__APPLE__) || defined(__linux__) // macOS and Linux are identically

   return access(mCstr.constData(), R_OK) == 0;

   #elif defined _WIN32//Windows

   struct stat filestat;
   int32 result = stat(mCstr.constData(), &filestat);
   if(result != 0)return false;  //Existiert nicht
   if(filestat.st_mode & _S_IREAD) return true;
   return false;

   #endif

}

bool File::canWrite() const
{

   #if defined(__APPLE__) || defined(__linux__) // macOS and Linux are identically

   return access(mCstr.constData(), W_OK) == 0;

   #elif defined _WIN32//Windows

   struct stat filestat;
   int32 result = stat(mCstr.constData(), &filestat);
   if(result != 0)return false;  //Existiert nicht
   if(filestat.st_mode & _S_IWRITE) return true;
   return false;

   #endif

}

bool File::canExecute() const
{

   #if defined(__APPLE__) || defined(__linux__) // macOS and Linux are identically

   return access(mCstr.constData(), X_OK) == 0;

   #elif defined _WIN32//Windows

   struct stat filestat;
   int32 result = stat(mCstr.constData(), &filestat);
   if(result != 0)return false;  //Existiert nicht
   if(filestat.st_mode & _S_IEXEC) return true;
   return false;

   #endif

}

bool File::isDirectory() const
{
   #if defined(__APPLE__) || defined(__linux__) // macOS and Linux are identically

   struct stat st;
   lstat(mCstr.constData(), &st);
   bool ret = S_ISDIR(st.st_mode);
   return ret;

   #elif defined _WIN32//Windows

   struct stat filestat;
   int32 result = stat(mCstr.constData(), &filestat);
   if(result != 0)return false;  //Existiert nicht
   if(filestat.st_mode & _S_IFDIR) return true;
   return false;

   #endif

}

bool File::isFile() const
{

   #if defined(__APPLE__) || defined(__linux__) // macOS and Linux are identically

   struct stat st;
   lstat(mCstr.constData(), &st);
   bool ret = S_ISREG(st.st_mode);
   return ret;


   #elif defined _WIN32//Windows

   struct stat filestat;
   int32 result = stat(mCstr.constData(), &filestat);
   if(result != 0)return false;  //Existiert nicht
   if(filestat.st_mode & _S_IFREG) return true;
   return false;

   #endif

}

bool File::isHidden() const
{

   #if defined(__APPLE__) || defined(__linux__) // macOS and Linux are identically

   return name().charAt(0) == '.';

   #elif defined _WIN32//Windows

   DWORD attributes = GetFileAttributesA(mCstr.constData());
   if(attributes & FILE_ATTRIBUTE_HIDDEN)return true;
   return false;

   #endif

}

bool File::isLink() const
{

   #if defined(__APPLE__) || defined(__linux__) // macOS and Linux are identically

   struct stat st;
   lstat(mCstr.constData(), &st);
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

bool File::isPipe() const
{

   #if defined(__APPLE__) || defined(__linux__) // macOS and Linux are identically

   struct stat st;
   lstat(mCstr.constData(), &st);
   bool ret = S_ISFIFO(st.st_mode);
   return ret;


   #elif defined _WIN32//Windows

   struct stat filestat;
   int32 result = stat(mCstr.constData(), &filestat);
   if(result != 0)return false;  //Existiert nicht
   if(filestat.st_mode & _S_IFIFO) return true;
   return false;

   #endif

}

Date File::lastModified() const
{
   #if defined(__APPLE__) //macOS

   struct stat st;
   lstat(mCstr.constData(), &st);

   //Umrechnen
   timespec tm = st.st_mtimespec;
   int64 time = tm.tv_sec * 1000LL;
   time += (tm.tv_nsec / 1000LL);

   return Date(time);

   #elif defined(__linux__) //Linux

   struct stat st;
   lstat(mCstr.constData(), &st);

   //Umrechnen
   timespec tm = st.st_mtim;
   int64 time = tm.tv_sec * 1000LL;
   time += (tm.tv_nsec / 1000LL);

   return Date(time);

   #elif defined _WIN32//Windows

   struct stat st;
   stat(mCstr.constData(), &st);

   // Convert
   const time_t ct = st.st_mtime;//time_t is the time in seconds
   int64 epoch = (int64)ct;
   return Date(epoch * 1000LL);
   #endif

}


bool File::remove()
{
   if(isDirectory() && rmdir(mCstr.constData()) == 0)return true;
   else if(::remove(mCstr.constData()) == 0)return true;

   return false;
}

bool File::moveToTrash()
{
   #if defined(__APPLE__)//macOS

   return File_MoveToTrash(mCstr.constData());

   #elif defined(__linux__) //Linus


   #elif defined _WIN32//Windows


   #endif

   return false;
}

bool File::renameTo(const String& newPath)
{
   int32 result;


   #ifdef __APPLE__ //macOS
   ByteArray newname = newPath.toCString();
   #elif defined __linux__ //Linux
   ByteArray newname = newPath.toCString();
   #elif defined _WIN32 //Windows
   ByteArray newname = newPath.toCString(Charset::forName("Windows-1252"));
   #endif


   result = rename(mCstr.constData(), newname.constData());

   if(result == 0)
   {
      mCstr = newname;
      mPathname = String(mCstr);

      return true;
   }
   else
   {
      return false;
   }
}


Array<File>* File::listFiles()const
{
   if(!isDirectory())return
         nullptr;//throw new Exception("ShxFile \"" + absolutePath() + "\" is not a directory.");

   #if defined(__APPLE__) || defined(__linux__) // macOS and Linux are identically


   DIR* dp;
   struct dirent* dirp;
   dp = opendir(mCstr.constData());

   if(dp == nullptr)
   {
      throw Exception(Tr("Cannot open directory"));
   }

   uint32 fileCount = 0;

   //Zähle Einträge
   while(readdir(dp) != nullptr)fileCount++;

   //Zum Anfang
   rewinddir(dp);

   //Array füllen
   Array<File>* list = new Array<File>(fileCount);
   uint32 cnt = 0;

   while((dirp = readdir(dp)) != nullptr)
   {
      String filename = String(dirp->d_name);
      list->set(cnt++, File(*this, filename));
   }
   closedir(dp);

   return list;


   #elif defined _WIN32//Windows

   HANDLE hFind;
   WIN32_FIND_DATA data;

   String tmp = mPathname;
   tmp.append(DIR_SEP);
   tmp.append('*');
   uint16* wstr = tmp.toWString();

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
         list->set(a, File(mPathname, files[a]));
      }

      delete wstr;
      return list;
   }
   else
   {
      delete wstr;
      throw Exception(Tr("Cannot open directory"));
   }

   #endif
}


int64 File::size() const
{
   struct stat filestat;
   int32 result = stat(mCstr.constData(), &filestat);

   // If it doesn't exist, then I can't read it.
   if(result != 0)return 0;

   return int64((uint64)filestat.st_size);
}


const String& File::absolutePath() const
{
   return mPathname;
}

String File::path() const
{
   return mPathname;
}

String File::parent() const
{
   int64 idx = mPathname.lastIndexOf(DIR_SEP);
   if(idx < 0)idx = 0;
   return mPathname.substring(0, idx);
}

String File::name() const
{
   return mPathname.substring(mPathname.lastIndexOf(DIR_SEP) + 1);
}

String File::extension() const
{
   return mPathname.substring(mPathname.lastIndexOf('.') + 1);
}

bool File::isAbsolute() const
{
   return true;
}


bool File::createNewFile()
{
   #if defined(__APPLE__) || defined(__linux__)//linux,macOS und ios
   mHandle = fopen(mCstr.constData(), "wb");
   bool exist = (mHandle != nullptr);
   close();
   return exist;
   #elif defined _WIN32 //Windows
   int64 ret = fopen_s(&mHandle, mCstr.constData(), "wb");
   close();
   return ret == 0;
   #endif
}

Status File::open(FileMode mode)
{
   #if defined(__APPLE__) || defined(__linux__)//linux,macOS und ios
   switch(mode)
   {
      case FileMode::kRead:
         mHandle = fopen(mCstr.constData(), "rb");
         break;

      case FileMode::kWrite:
         mHandle = fopen(mCstr.constData(), "wb");
         break;

      case FileMode::kReadWrite:
         mHandle = fopen(mCstr.constData(), "rb+");
         break;
   }
   #elif defined _WIN32 //Windows
   switch(mode)
   {
      case FileMode::kRead:
         fopen_s(&mHandle, mCstr.constData(), "rb");
         break;

      case FileMode::kWrite:
         fopen_s(&mHandle, mCstr.constData(), "wb");
         break;

      case FileMode::kReadWrite:
         fopen_s(&mHandle, mCstr.constData(), "rb+");
         break;
   }
   #endif

   if(mHandle == nullptr)
   {
      String msg = Tr("Cannot open file! \"%1\" Errno: %2").arg(mPathname).arg(int64(errno));
      jm::System::log(msg, jm::LogLevel::kError);

      if(errno == EACCES)return Status::eNotAllowed;
      if(errno == ENOENT)return  Status::eNotFound;
      if(errno == ETIMEDOUT)return Status::eTimeout;
      if(errno == ENOTDIR)return Status::eNoDirectory;
      throw Exception(msg);
   }
   return Status::eOK;
}

bool File::isOpen()
{
   return mHandle != nullptr;
}

void File::close()
{
   if(mHandle == nullptr)return;
   int32 eof = fclose(mHandle);
   if(eof == EOF)throw Exception(Tr("Error while closing file!"));
   mHandle = nullptr;
}

void File::seek(int64 position)
{
   //Data type is long int in fseek
   size_t res = fseek(mHandle, (long int)position, SEEK_SET);
   if(res != 0)throw Exception(Tr("Error while moving file reading pointer!"));
}

void File::move(int64 offset)
{
   //Data type is long int in fseek
   size_t res = fseek(mHandle, (long int)offset, SEEK_CUR);
   if(res != 0)throw Exception(Tr("Error while moving file reading pointer!"));
}

int64 File::position()
{
   return int64((uint64)ftell(mHandle));
}


int64 File::read(uint8* buffer, int64 length)
{
   return fread(buffer, 1, length, mHandle);
}

int64 File::readFully(ByteArray& buffer, int64 length)
{
   int64 rest = length;
   int64 count = 0;
   int64 step;
   uint8* buf = reinterpret_cast<uint8*>(buffer.data());

   while((rest > 0) && ((step = read(&buf[count], rest)) > 0))
   {
      count += step;
      rest -= step;
   };

   return count;
}

int64 File::write(const uint8* buffer, int64 length)
{
   return fwrite(buffer, 1, length, mHandle);
}

int32 File::compareTo(const File& other) const
{
   //Erst Verzeichnis
   bool d1 = isDirectory();
   bool d2 = other.isDirectory();
   if(d1 != d2)
   {
      if(d1)return -1;
      return 1;
   }

   //Dann Name
   return mPathname.compareTo(other.mPathname);
}

StringList File::getTags()const
{
   #ifdef __APPLE__ //macOS

   #if TARGET_OS_IOS == 0
   // Create necessary system related objects
   CFStringRef cfstr = CFStringCreateWithCString(kCFAllocatorDefault,
                       mCstr.constData(),
                       kCFStringEncodingUTF8);
   CFURLRef urlref = CFURLCreateWithFileSystemPath(kCFAllocatorDefault,
                     cfstr,
                     kCFURLPOSIXPathStyle,
                     isDirectory());

   // Query tags
   CFArrayRef tags = nullptr;
   Boolean result = CFURLCopyResourcePropertyForKey(urlref,
                    kCFURLTagNamesKey,
                    &tags,
                    nullptr);

   // Clean unnecessary stuff
   CFRelease(cfstr);
   CFRelease(urlref);

   if(result == true && tags != nullptr)
   {
      // Extract the tags to our string list
      StringList taglist;
      int64 count = (uint32) CFArrayGetCount(tags);
      if(count > 0)
      {
         for(int64 index = 0; index < count; index++)
         {
            CFStringRef str = (CFStringRef)CFArrayGetValueAtIndex(tags, index);
            taglist << String::fromCFString(str);
         }

         // Clean up
         CFRelease(tags);

         return taglist;
      }
   }

   if(tags != nullptr)CFRelease(tags);

   #endif

   #endif

   #ifdef __linux__

   const int sz = 4096;
   char buffer[sz];
   int result = getxattr(mCstr.constData(), "user.xdg.tags", buffer, sz);

   if(result > 0)
   {
      // Data is stored usually as comma(,) separated list.
      ByteArray tagList = ByteArray((int8*)buffer, result);
      String string(tagList);
      return string.split(',');
   }
   #endif

   // Return empty if no tags found array
   return StringList();
}

Status File::setTags(const jm::StringList& tags)
{
   #ifdef __APPLE__ //macOS

   #if TARGET_OS_IOS == 0

   //Create new array and append tag
   int64 newsize = tags.size();
   CFStringRef* strs = new CFStringRef[newsize];
   for(int64 index = 0; index < newsize; index++)
   {
      strs[index] = tags[index].toCFString();
   }

   CFArrayRef newtags = CFArrayCreate(nullptr, (const void**)strs, newsize, &kCFTypeArrayCallBacks);

   //
   //
   //

   // Create necessary system related objects
   CFStringRef cfstr = CFStringCreateWithCString(kCFAllocatorDefault,
                       mCstr.constData(),
                       kCFStringEncodingUTF8);
   CFURLRef urlref = CFURLCreateWithFileSystemPath(kCFAllocatorDefault,
                     cfstr,
                     kCFURLPOSIXPathStyle,
                     isDirectory());

   // Set tags
   Boolean result = CFURLSetResourcePropertyForKey(urlref,
                    kCFURLTagNamesKey,
                    newtags,
                    nullptr);

   // Clean unnecessary stuff

   for(int64 index = 0; index < newsize; index++)
   {
      CFRelease(strs[index]);
   }

   CFRelease(cfstr);
   CFRelease(urlref);
   CFRelease(newtags);

   if(result == true)return Status::eOK;
   else return Status::eNo;
   #endif
   #endif

   #ifdef __linux__

   String string(tags.join(Char(',')));
   ByteArray buffer = string.toCString();

   int64 result = setxattr(mCstr.constData(), "user.xdg.tags", buffer.constData(), buffer.size(), 0);

   return (result == 0) ? jm::Status::eOK : jm::Status::eNo;

   #endif

   return Status::eNotImplemented;
}


Status File::addTag(const String& tag)
{
   #if defined(__APPLE__) || defined(__linux__)//linux,macOS und ios

   StringList tags = getTags();
   if(!tags.contains(tag))
   {
      tags.append(tag);
      return setTags(tags);
   }
   else return Status::eOK;

   #endif

   return Status::eNotImplemented;
}

Status File::removeTag(const String& tag)
{
   #if defined(__APPLE__) || defined(__linux__)//linux,macOS und ios

   StringList tags = getTags();
   if(tags.contains(tag))
   {
      tags.remove(tag);
      return setTags(tags);
   }
   else return Status::eOK;

   #endif

   return Status::eNotImplemented;
}


String jm::ExecPath()
{

   #ifdef __APPLE__ //macOS
   uint32_t size = 1024;
   char path[1024];
   int ok = _NSGetExecutablePath(path, &size);
   if(ok < 0)
   {
      throw Exception(Tr("Cannot determinate executable Path"));
   }
   path[size - 1] = '\0';
   String ret = String(path);
   return ret;
   #elif defined __linux__ //Linux
   char buff[1024];
   ssize_t len = ::readlink("/proc/self/exe", buff, sizeof(buff) - 1);
   if(len > 0)
   {
      if(len >= 1024)len = 1023;
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

   HMODULE hModule = GetModuleHandle(nullptr);
   if(hModule != nullptr)
   {

      // When passing nullptr to GetModuleHandle, it returns handle of exe itself
      GetModuleFileNameW(hModule, (LPWSTR)path, size);

      path[size - 1] = '\0';
      String ret;

      uint32 pos = 0;
      while(path[pos] != 0)ret.append(path[pos++]);

      return ret;
   }
   throw Exception(Tr("Cannot determinate executable path"));
   #endif

}

String jm::ExecName()
{
   String exec = ExecPath();
   int64 pos = exec.lastIndexOf(DIR_SEP);
   return exec.substring(pos + 1);
}

String jm::ExecDir()
{
   String exec = ExecPath();
   int64 pos = exec.lastIndexOf(DIR_SEP);
   if(exec.charAt(pos - 1) == '.' && exec.charAt(pos - 2) == DIR_SEP)pos -= 2;
   return exec.substring(0, pos);
}


#ifdef __APPLE__
File jm::ResourceDir(const String& bundleId)
{

   //CFString aus Bundle-ID erzeugen
   CFStringRef cfstr = bundleId.toCFString();

   //Erzeuge Referenzen auf das Bundle, die BundleURL und die Ressourcen-URL
   CFBundleRef thisBundle = CFBundleGetBundleWithIdentifier(cfstr);
   if(thisBundle == nullptr)
   {
      //Aufräumen
      CFRelease(cfstr);

      if(!bundleId.isEmpty())
      {
         System::log(Tr("BundleRef for %1 not found. Cannot determine resource directory.").arg(bundleId),
                     LogLevel::kError);
      }
      return File("/");
   }

   CFURLRef resourceDirURL = CFBundleCopyResourcesDirectoryURL(thisBundle);


   #if TARGET_OS_IOS == 1 // iOS add -DTARGET_OS_IPHONE as compiler option if necessary

   // On iOS, the resource folder is also the root folder of the app...

   // Convert bundle URL to string
   CFStringRef sr = CFURLCopyPath(resourceDirURL);
   String filename = String::fromCFString(sr);

   // Clean up
   CFRelease(cfstr);
   CFRelease(sr);
   CFRelease(resourceDirURL);

   // Return
   return File(filename);
}

   #else //macOS

   CFURLRef bundleURL = CFBundleCopyBundleURL(thisBundle);

   // Attention URL can be coded. For spaces, this is e.g. %20

   // Convert bundle URL to string
   CFStringRef sr1 = CFURLCopyPath(bundleURL);
   String filename = URLDecode(String::fromCFString(sr1));

   // Attach resource URL
   CFStringRef sr2 = CFURLCopyPath(resourceDirURL);
   filename.append(URLDecode(String::fromCFString(sr2)));

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
File jm::ResourceDir(const String& /*bundleId*/)
{
   // The resource directory is /usr/share/appname
   return File("/usr/share/" + ExecName());
}
#elif defined _WIN32 //Windows
File jm::ResourceDir(const String& /*bundleId*/)
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

   #ifdef __ANDROID__
   JNIEnv* env = getJNIEnv();

   if(env == nullptr)
   {
      return jm::File();
   }

   jobject act = activity();
   jclass jClass = env->GetObjectClass(act);
   jmethodID methodID = env->GetMethodID(jClass, "getFilesDirPath", "()Ljava/lang/String;");

   jstring str = (jstring)env->CallObjectMethod(act, methodID);
   jm::String text;
   if(str != nullptr)
   {
      const char* utf = env->GetStringUTFChars(str, 0);
      text = jm::String(utf);
   }

   // Clean up local object references
   env->DeleteLocalRef(jClass);
   env->DeleteLocalRef(str);
   return jm::File(text);
   #else
   // A subdirectory around the home folder with the application name is provided as the property
   // directory
   char* home = getenv("HOME");
   return File(home, "." + ExecName());
   #endif

   #elif defined _WIN32 //Windows

   return UserDir();
   /*	uint16* path[MAX_PATH];

   	if (SUCCEEDED(SHGetKnownFolderPath(nullptr, CSIDL_PROFILE, nullptr, 0,(WCHAR*)path)))
   	{
   		uint32 textlength = 0;
   		while (path[textlength] != 0)textlength++;

   		String ret = String((uint16*)path, textlength);

   		// The Exec-Dir is currently used as the PropertyDir
   		return new ShxFile(ret);
   	}

   	return nullptr;
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

   if(SUCCEEDED(SHGetFolderPath(nullptr, CSIDL_PROFILE, nullptr, 0, (WCHAR*)&path)))
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

File jm::TempDir()
{
   #ifdef __APPLE__ //macOS and ios
   char* temp = getenv("TMPDIR");
   return File(temp);
   #elif defined __linux__ //Linux
   char cwd[PATH_MAX];
   getcwd(cwd, sizeof(cwd));
   return File(cwd);
   #elif defined _WIN32 //Windows
   uint16 path[MAX_PATH];
   memset(path, 0, MAX_PATH * sizeof(uint16));
   LPWSTR ptr = (LPWSTR) & path[0];
   uint32 size = GetCurrentDirectory(MAX_PATH, ptr);
   String name = String((uint16*)path, size);
   return File(name);
   #endif
}

File jm::currentDir()
{
   #ifdef __APPLE__ //macOS and ios
   char cwd[PATH_MAX];
   getcwd(cwd, sizeof(cwd));
   return File(cwd);
   #elif defined __linux__ //Linux
   char cwd[PATH_MAX];
   getcwd(cwd, sizeof(cwd));
   return File(cwd);
   #elif defined _WIN32 //Windows
   uint16 path[MAX_PATH];
   memset(path, 0, MAX_PATH * sizeof(uint16));
   LPWSTR ptr = (LPWSTR) & path[0];
   uint32 size = GetCurrentDirectory(MAX_PATH, ptr);
   String name = String((uint16*)path, size);
   return File(name);
   #endif
}

