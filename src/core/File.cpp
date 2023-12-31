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
	mCstr = NULL;
	mHandle = NULL;
}

File::File(const String &pathname): Stream(), Comparable<File>()
{
	if(pathname.Length() < 1)throw new Exception(Tr("Pathname is empty."));
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
	else mCstr = NULL;
}


File::~File()
{
	if(mCstr != NULL)
	{
		delete[] mCstr;
		mCstr = NULL;
	}
}

File& File::operator=(const File &another)
{
	if(this != &another)
	{
		if(mCstr != NULL)delete[] mCstr;
		mPathname = another.mPathname;
		mHandle = another.mHandle;
		if(mPathname.Length() > 0)SetCString();
		else mCstr = NULL;
	}

	return *this;
}


void File::SetCString()
{

	#ifdef __APPLE__ //macOS
	//Unter 10.10 werden Umlaute korrekt übernommen...
	mCstr = mPathname.ToCString(Charset::ForName("UTF-8"));
	#elif defined __linux__ //Linux
	mCstr = mPathname.ToCString(Charset::ForName("UTF-8"));
	#elif defined _WIN32 //Windows
	mCstr = mPathname.ToCString(Charset::ForName("Windows-1252"));     //Muss unter Windows Windows-1252 sein bei fopen
	#endif
}

String File::Resolve(String parent, String child)
{
	//Parent und child sind normalisiert.
	String sep;
	sep.Append(DIR_SEP);

	//Unter UNIX:
	if(parent.Length() < 1 && child.Length() < 1)return sep;

	//Wenn child mit Trenner beginnt
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
	uint16 prev = 0;

	for(Integer a = 0; a < length; a++)
	{
		uint16 character = pathname.CharAt(a);

		//Entferne doppelte Pfadtrenner
		if(prev == DIR_SEP && character == DIR_SEP)
		{
			pathname.DeleteCharAt(a);
			a--;
			length--;
		}
		prev = character;
	}

	//Wenn letzter Buchstabe Pfadtrenner ist und Dateiname länger als 1
	if(prev == DIR_SEP && pathname.Length() > 1)pathname.DeleteCharAt(pathname.Length() - 1);
	//_pathname = URLDecode( _pathname ); //ACHTUNG, dies ist wegen iOS und Leerzeichen eingefügt worden, es ist zu prüfen, ob das allgemeingültig sein muss
	//Unter Windows definitiv NEIN
	//Unter macOS definitiv NEIN
	return pathname;
}

bool File::MakeDirectory()
{
	#if defined(__APPLE__) || defined(__linux__) //macOS und Linux sind gleich (POSIX?!)

	int32 result = mkdir(mCstr,S_IRWXU|S_IRGRP|S_IROTH);
	return result == 0;

	#elif defined _WIN32//Windows
	int32 result = _mkdir(mCstr);
	return result == 0;
	#endif
}

bool File::Exists() const
{

	#if defined(__APPLE__) || defined(__linux__) //macOS und Linux sind gleich (POSIX?!)

	return access(mCstr, F_OK) == 0;

	#elif defined _WIN32//Windows
	if (mCstr == NULL)return false;

	struct stat filestat;
	int32 result = stat(mCstr, &filestat);
	return result == 0;

	#endif
}

bool File::CanRead() const
{

	#if defined(__APPLE__) || defined(__linux__) //macOS und Linux sind gleich (POSIX?!)

	return access(mCstr, R_OK) == 0;

	#elif defined _WIN32//Windows

	struct stat filestat;
	int32 result = stat(mCstr, &filestat);
	if(result != 0)return false;  //Existiert nicht
	if(filestat.st_mode & _S_IREAD) return true;
	return false;

	#endif

}

bool File::CanWrite() const
{

	#if defined(__APPLE__) || defined(__linux__) //macOS und Linux sind gleich (POSIX?!)

	return access(mCstr, W_OK) == 0;

	#elif defined _WIN32//Windows

	struct stat filestat;
	int32 result = stat(mCstr, &filestat);
	if(result != 0)return false;  //Existiert nicht
	if(filestat.st_mode & _S_IWRITE) return true;
	return false;

	#endif

}

bool File::IsDirectory() const
{
	#if defined(__APPLE__) || defined(__linux__) //macOS und Linux sind gleich (POSIX?!)

	struct stat st;
	lstat(mCstr, &st);
	bool ret = S_ISDIR(st.st_mode);
	return ret;

	#elif defined _WIN32//Windows

	struct stat filestat;
	int32 result = stat(mCstr, &filestat);
	if(result != 0)return false;  //Existiert nicht
	if(filestat.st_mode & _S_IFDIR) return true;
	return false;

	#endif

}

bool File::IsFile() const
{

	#if defined(__APPLE__) || defined(__linux__) //macOS und Linux sind gleich (POSIX?!)

	struct stat st;
	lstat(mCstr, &st);
	bool ret = S_ISREG(st.st_mode);
	return ret;


	#elif defined _WIN32//Windows

	struct stat filestat;
	int32 result = stat(mCstr, &filestat);
	if(result != 0)return false;  //Existiert nicht
	if(filestat.st_mode & _S_IFREG) return true;
	return false;

	#endif

}

bool File::IsHidden() const
{

	#if defined(__APPLE__) || defined(__linux__) //macOS und Linux sind gleich (POSIX?!)

	return GetName().CharAt(0) == '.';

	#elif defined _WIN32//Windows

	struct stat filestat;
	int32 result = stat(mCstr, &filestat);
	if(result != 0)return false;  //Existiert nicht
	if((filestat.st_mode & _S_IFREG) == 0) return true;
	return false;

	#endif

}

bool File::IsLink() const
{

	#if defined(__APPLE__) || defined(__linux__) //macOS und Linux sind gleich (POSIX?!)

	struct stat st;
	lstat(mCstr, &st);
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

	#if defined(__APPLE__) || defined(__linux__) //macOS und Linux sind gleich (POSIX?!)

	struct stat st;
	lstat(mCstr, &st);
	bool ret = S_ISFIFO(st.st_mode);
	return ret;


	#elif defined _WIN32//Windows

	struct stat filestat;
	int32 result = stat(mCstr, &filestat);
	if(result != 0)return false;  //Existiert nicht
	if(filestat.st_mode & _S_IFIFO) return true;
	return false;

	#endif

}

Date File::LastModified() const
{
	#if defined(__APPLE__) //macOS

	struct stat st;
	lstat(mCstr, &st);

	//Umrechnen
	timespec tm = st.st_mtimespec;
	int64 time = tm.tv_sec * 1000LL;
	time += (tm.tv_nsec / 1000LL);

	return Date(time);

	#elif defined(__linux__) //Linux

	struct stat st;
	lstat(mCstr, &st);

	//Umrechnen
	timespec tm = st.st_mtim;
	int64 time = tm.tv_sec * 1000LL;
	time += (tm.tv_nsec / 1000LL);

	return Date(time);

	#elif defined _WIN32//Windows

	struct stat st;
	stat(mCstr, &st);

	//Umrechnen
	const time_t ct = st.st_mtime;//time_t ist die Zeit in Sekunden
	int64 epoch = (int64)ct;
	return Date(epoch * 1000LL);
	#endif

}


bool File::Delete()
{
	if(remove(mCstr) == 0)return true;
	else return false;
}

bool File::MoveToTrash()
{
	#if defined(__APPLE__)//macOS

	return File_MoveToTrash(mCstr);

	#elif defined(__linux__) //Linus


	#elif defined _WIN32//Windows


	#endif

	return false;
}

bool File::RenameTo(const String &newPath)
{
	int32 result;


	#ifdef __APPLE__ //macOS
	int8* newname = newPath.ToCString();
	#elif defined __linux__ //Linux
	int8* newname = newPath.ToCString();
	#elif defined _WIN32 //Windows
	int8* newname = newPath.ToCString(Charset::ForName("Windows-1252"));
	#endif


	result = rename(mCstr, newname);

	if(result == 0)
	{
		delete[] mCstr;
		mCstr = newname;
		return true;
	}
	else
	{
		delete[] newname;
		return false;
	}
}


Array<File>* File::ListFiles()
{
	if(!IsDirectory())return NULL;//throw new Exception("ShxFile \"" + GetAbsolutePath() + "\" is not a directory.");

	#if defined(__APPLE__) || defined(__linux__) //macOS und Linux sind gleich (POSIX?!)


	DIR* dp;
	struct dirent* dirp;
	dp = opendir(mCstr);

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
			//cFilename ist der nackte Dateiname ohne Pfad.
			uint16* wstr2 = (uint16*)data.cFileName;
			uint32 len = 0;
			while(wstr2[len] != 0)len++;
			files.push_back(String(wstr2, len));
		}
		while(FindNextFile(hFind, &data));
		FindClose(hFind);

		//Array füllen
		Array<File>* list = new Array<File>((uint32)files.size());
		for(uint32 a = 0; a < files.size(); a++)
		{
			//In Files ist nur der Dateiname gespeichert. Pfadname muss also davor, damit es klappt...
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
	int32 result = stat(mCstr, &filestat);

	//Wenn sie nicht existiert, dann kann ich sie nicht lesen.
	if(result != 0)throw new Exception(jm::String::Format(Tr("File \"%s\" does not exist."),
																			&GetAbsolutePath()));

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
	mHandle = fopen(mCstr, "wb");
	Integer ret = mHandle!=NULL;
#elif defined _WIN32 //Windows
	Integer ret = fopen_s(&mHandle,mCstr, "wb");
#endif

	Close();
	return ret==0;
}

void File::Open(FileMode mode)
{
	Integer ret = 0;

#if defined(__APPLE__) || defined(__linux__)//linux,macOS und ios
	switch(mode)
	{
		case kFmRead:
			mHandle = fopen(mCstr, "rb");
			break;

		case kFmWrite:
			mHandle = fopen(mCstr, "wb");
			break;

		case kFmReadWrite:
			mHandle = fopen(mCstr, "rb+");
			break;
	}
	ret=mHandle!=NULL;
#elif defined _WIN32 //Windows
	switch(mode)
	{
		case kFmRead:
			ret = fopen_s(&mHandle, mCstr, "rb");
			break;

		case kFmWrite:
			ret = fopen_s(&mHandle, mCstr, "wb");
			break;

		case kFmReadWrite:
			ret = fopen_s(&mHandle, mCstr, "rb+");
			break;
	}
#endif

	if(mHandle == NULL)
	{
		if(errno == EACCES)throw new Exception(String::Format(Tr("Permission denied! \"%s\""),
																				&mPathname));
		if(errno == ENOENT)throw new Exception(String::Format(Tr("File not found! \"%s\""),
																				&mPathname));
		if(errno == ETIMEDOUT)throw new Exception(String::Format(Tr("Connection timed out! \"%s\""),
																					&mPathname));
		if(errno == ENOTDIR)throw new Exception(String::Format(Tr("Not a directory \"%s\""),
																				 &mPathname));
		throw new Exception(String::Format(Tr("Cannot open file! \"%s\" Errno: %i"),
													  &mPathname,
													  errno));
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

Integer File::ReadFully(uint8* buffer, Integer length)
{
	Integer rest = length;
	Integer read = 0;
	Integer step;

	while((rest > 0) && ((step = Read(&buffer[read], rest)) > 0))
	{
		read += step;
		rest -= step;
	};

	return read;
}

Integer File::Write(uint8* buffer, Integer length)
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
		if(d2)return 1;
	}

	//Dann Name
	return mPathname.CompareTo(other.mPathname);
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
		return "";
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


File jm::ResourceDir(const String &bundleId)
{
	#ifdef __APPLE__

	//CFString aus Bundle-ID erzeugen
	const char* cstring = bundleId.ToCString();
	CFStringRef cfstr = CFStringCreateWithCString(kCFAllocatorDefault, cstring, kCFStringEncodingUTF8);

	//Erzeuge Referenzen auf das Bundle, die BundleURL und die Ressourcen-URL
	CFBundleRef thisBundle = CFBundleGetBundleWithIdentifier(cfstr);
	if(thisBundle == NULL)
	{
		//Aufräumen
		CFRelease(cfstr);

		System::Log(String::Format(Tr("NO BUNDLE-REF for %s"),&bundleId), kLogError);
		return File("/");
	}

	CFURLRef resourceDirURL = CFBundleCopyResourcesDirectoryURL(thisBundle);


	#if TARGET_OS_IPHONE == 1 // iOS ggf. -DTARGET_OS_IPHONE als Kompileroption ergänzen

	//Unter IOS ist das Resourcedir gleichzeitig der Rootordner der App...

	//Kovertiere Bundle-URL in String
	char path[1024];
	CFStringRef sr = CFURLCopyPath(resourceDirURL);
	CFStringGetCString(sr, path, sizeof(path), kCFStringEncodingUTF8);
	String filename = String(path);

	//Aufräumen
	CFRelease(cfstr);
	CFRelease(sr);
	CFRelease(resourceDirURL);
	delete cstring;

	//Rückgabe
	return new File(filename);


	#else //macOS

	CFURLRef bundleURL = CFBundleCopyBundleURL(thisBundle);

	//Achtung URL kann kodiert sein. Für Leerzeichen ist das z.B. %20

	//Kovertiere Bundle-URL in String
	char path[1024];
	CFStringRef sr1 = CFURLCopyPath(bundleURL);
	CFStringGetCString(sr1, path, sizeof(path), kCFStringEncodingUTF8);
	String filename = URLDecode(String(path));

	//Hänge Ressourcen-URL an
	CFStringRef sr2 = CFURLCopyPath(resourceDirURL);
	CFStringGetCString(sr2, path, sizeof(path), kCFStringEncodingUTF8);
	filename.Append(URLDecode(String(path)));

	//Aufräumen
	CFRelease(cfstr);
	CFRelease(bundleURL);
	CFRelease(resourceDirURL);
	CFRelease(sr1);
	CFRelease(sr2);
	delete cstring;

	#endif

	//Rückgabe
	return File(filename);

	#elif defined __linux__ //Linux
	//Als Resourcedirectory wird zurzeit des Exec-Dir genommen
	return File(ExecDir());
	#elif defined _WIN32 //Windows

	//Als Resourcedirectory wird zurzeit des Exec-Dir genommen
	return File(ExecDir());

	#endif
}

File jm::PropertyDir()
{
	#ifdef __APPLE__ //macOS und ios
	//Methode ist auf IOS ausgelegt bisher, funkioniert aber auch unter macOS, muss abernoch geprüft werden.
	char* home = getenv("HOME");
	//IOS: https://developer.apple.com/library/mac/documentation/FileManagement/Conceptual/FileSystemProgrammingGuide/FileSystemOverview/FileSystemOverview.html
	return File(home, "Library");
	#elif defined __linux__ //Linux
	//Als Propertydirectory wird ein Unterverzeichnis um Homeordner mit dem Applicationnamen vorgesehen
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

			//Als PropertyDir wird zurzeit des Exec-Dir genommen
			return new ShxFile(ret);
		}

		return NULL;
		*/
	#endif

}

File jm::UserDir()
{
	#ifdef __APPLE__ //macOS und ios
	//Methode ist auf IOS ausgelegt bisher, funkioniert aber auch unter macOS, muss abernoch geprüft werden.
	char* home = getenv("HOME");
	//IOS: https://developer.apple.com/library/mac/documentation/FileManagement/Conceptual/FileSystemProgrammingGuide/FileSystemOverview/FileSystemOverview.html
	return File(home);
	#elif defined __linux__ //Linux
	//Als Propertydirectory wird ein Unterverzeichnis um Homeordner mit dem Applicationnamen vorgesehen
	char* home = getenv("HOME");
	return File(home);
	#elif defined _WIN32 //Windows

	uint16 path[MAX_PATH];

	if(SUCCEEDED(SHGetFolderPath(NULL, CSIDL_PROFILE, NULL, 0, (WCHAR*)&path)))
	{
		uint32 textlength = 0;
		while(path[textlength] != 0)textlength++;

		String ret = String((uint16*)path, textlength);

		//Als PropertyDir wird zurzeit des Exec-Dir genommen
		return File(ret);
	}

	return File();
	#endif

}

