////////////////////////////////////////////////////////////////////////////////////////////////////
// Name:        System.cpp
// Library:     Jameo Core Library
// Purpose:     System Object
//
// Author:      Uwe Runtemund (2013-today)
// Modified by:
// Created:     18.09.2013
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

jm::Mutex gSystemMutex;
jm::String gSystemError;

bool gSystemLogDate=true;
jm::LogLevel mSystemLogLabel=jm::kLogDebug;

jm::String jm::System::GetLanguage()
{
	#ifdef __APPLE__ //macOS und iOS

	CFArrayRef langs = CFLocaleCopyPreferredLanguages();
	CFStringRef cflangCode = (CFStringRef) CFArrayGetValueAtIndex(langs, 0);

	String langCode = String::FromCFString(cflangCode);

	CFRelease(langs);
		
	return langCode;

	#elif defined __linux__//Linux

	//const char* = setlocale(LC_ALL, NULL);

	return "de-DE";
	#elif defined _WIN32//Windows

	LANGID langid = GetUserDefaultUILanguage();

	switch (langid)
	{
		case 1031:
			return "de-DE";

		default:
			return "en";
	}

	#endif

}

void jm::System::LogEnableDate(bool status)
{
	gSystemMutex.Lock();
	gSystemLogDate=status;
	gSystemMutex.Unlock();
}

void jm::System::LogEnableLabel(jm::LogLevel logLevel)
{
	gSystemMutex.Lock();
	mSystemLogLabel=logLevel;
	gSystemMutex.Unlock();
}


void jm::System::Log(const String &message, LogLevel logLevel)
{
	gSystemMutex.Lock();

	jm::String msg;
	if(gSystemLogDate)msg <<'[' << jm::Date().ToString() << "] ";

	switch(logLevel)
	{
		case kLogError:
			msg << kTxtBold << kTxtRed;
			if(logLevel>=mSystemLogLabel)msg << Tr("ERROR: ");
			gSystemError = message;
			break;

		case 	kLogWarning:
			msg << kTxtBold << kTxtYellow;
			if(logLevel>=mSystemLogLabel)msg << Tr("WARNING: ");
			break;

		case kLogInformation:
			if(logLevel>=mSystemLogLabel)msg << Tr("INFO: ");
			break;

		case kLogDebug:
			if(logLevel>=mSystemLogLabel)msg << Tr("DEBUG: ");
			break;
	}
	msg << message;
	
	switch(logLevel)
	{
		case kLogError:
		case kLogWarning:
			msg << kTxtReset;
			break;
			
		default:
			// Do nothing here.
			break;
	}

	
	//Ausgabe auf Console
	if(logLevel > kLogDebug)std::cout << msg << std::endl;

	//Ausgabe ins Logfile
	#ifdef __APPLE__ //macOS und iOS

	if(logLevel == kLogError)
	{
		//	setlogmask (LOG_UPTO (LOG_NOTICE));

		//	openlog ("jameo", LOG_CONS | LOG_PID | LOG_NDELAY, LOG_LOCAL1);

		ByteArray cstr = msg.ToCString();
		syslog(LOG_ERR, "%s", cstr.ConstData());
		//	syslog (LOG_INFO, "A tree falls in a forest");

		//	closelog ();
	}

	#elif defined __linux__//Linux


	#elif defined _WIN32//Windows

	if(logLevel == kLogError)
	{
		gSystemError = message;
	}

	#endif

	gSystemMutex.Unlock();
}

const jm::String& jm::System::GetLastErrorMessage()
{
	return gSystemError;
}


jm::String jm::System::GetUserID()
{
	#ifdef __APPLE__ //macOS und iOS

	return String(getenv("USER"));

	#elif defined __linux__//Linux

	return String(getenv("USER"));

	#elif defined _WIN32//Windows

	uint16 user_name[UNLEN + 1];
	DWORD user_name_size = sizeof(user_name);
	GetUserName((LPWSTR)user_name, &user_name_size);  //Explizite Typumwandlung unter VC++ 2010 eingefügt.
	return String(user_name, user_name_size);

	#endif
}


jm::String jm::System::GetUserFullName()
{
	#ifdef __APPLE__ //macOS und iOS

	return "Not implemented";//String(getenv("USER"));

	#elif defined __linux__//Linux

	return "Not implemented";

	#elif defined _WIN32//Windows

	uint16 user_name[UNLEN + 1];
	DWORD user_name_size = sizeof(user_name);

	//Diese Abfrage funktioniert bei Domänen-Accounts, aber nicht bei lokalen Benutzern. Dann wird ein Fehler zurückgegeben
	int ret = GetUserNameEx(NameDisplay, (LPWSTR)user_name, &user_name_size); //Explizite Typumwandlung unter VC++ 2010 eingefügt.
	if(ret != 0)return String(user_name, user_name_size);

	//Name konnte nicht ermittelt werden. Hole ihn anders
	ret = GetUserNameEx(NameSamCompatible, (LPWSTR)user_name, &user_name_size);//Explizite Typumwandlung unter VC++ 2010 eingefügt.
	if(ret == 0)return "<ERROR while searching username>";

	//Name hat die Form "Uwe-PC\Uwe"
	String str = String(user_name, user_name_size);
	return str.Substring(str.IndexOf('\\') + 1);

	#endif

}

/*
Windows spezifisch:

char *orig = "Hello, World!";
cout << orig << " (char *)" << endl;

// Convert to a wchar_t*
size_t origsize = strlen(orig) + 1;
const size_t newsize = 100;
size_t convertedChars = 0;
wchar_t wcstring[newsize];
mbstowcs_s(&convertedChars, wcstring, origsize, orig, _TRUNCATE);
wcscat_s(wcstring, L" (wchar_t *)");
wcout << wcstring << endl;

*/

void* jm::System::LoadDynamicLibrary(jm::File* file)
{
	#ifdef __APPLE__ //macOS und iOS

	ByteArray cstr = file->GetAbsolutePath().ToCString();
	void* libptr = dlopen(cstr.ConstData(), RTLD_LAZY);   //RTLD_LAZY ist default
	if(libptr == NULL) std::cout << "Loading dynamic library " << cstr.ConstData() << " failed!" << std::endl << dlerror() << std::endl;
	return libptr;

	#elif defined __linux__//Linux

	char* cstr = file->GetAbsolutePath().ToCString();
	void* libptr = dlopen(cstr, RTLD_LAZY);   //RTLD_LAZY ist default
	if(libptr == NULL) std::cout << "Loading dynamic library " << cstr << " failed!" << std::endl << dlerror() << std::endl;
	delete cstr;
	return libptr;

	#elif defined _WIN32//Windows

	uint16* wstr = file->GetAbsolutePath().ToWString();
	HMODULE libptr = LoadLibrary((LPCWSTR) wstr);
	delete[] wstr;
	if(libptr == NULL) std::cout << "Loading dynamic library " << file->GetAbsolutePath() << " failed!" << /*std::endl << dlerror() <<*/ std::endl;
	return libptr;

	#endif
}

void jm::System::UnloadDynamicLibrary(void* library)
{
	#ifdef __APPLE__ //macOS und iOS

	int res = dlclose(library);
	if(res != 0) std::cout << "Closing dynamic library failed!" << std::endl << dlerror() << std::endl;

	#elif defined __linux__//Linux

	int res = dlclose(library);
	if(res != 0) std::cout << "Closing dynamic library failed!" << std::endl << dlerror() << std::endl;

	#elif defined _WIN32//Windows

	bool res = (bool)FreeLibrary((HMODULE) library);
	if(res == false) Log("Closing dynamic library failed!", kLogError);

	#endif
}


void* jm::System::FindSymbol(void* library, const String &name)
{
	#ifdef __APPLE__ //macOS und iOS

	ByteArray cstr = name.ToCString();
	void* symptr = dlsym(library, cstr.ConstData());
	if(symptr == NULL) std::cout << "Locating " << name << " in dynamic library " << cstr.ConstData() << " failed!" << std::endl << dlerror() << std::endl;
	return symptr;

	#elif defined __linux__//Linux

	char* cstr = name.ToCString();
	void* symptr = dlsym(library, cstr);
	if(symptr == NULL) std::cout << "Locating " << name << " in dynamic library " << cstr << " failed!" << std::endl << dlerror() << std::endl;
	delete cstr;
	return symptr;

	#elif defined _WIN32//Windows

	ByteArray cstring = name.ToCString();
	void* ptr = GetProcAddress((HMODULE) library, cstring.ConstData());

	return ptr;

	#endif
}

//Globaler AutoreleasePool...
jm::AutoreleasePool* mainthreadPool = NULL;

jm::AutoreleasePool* jm::System::GetAutoreleasePool()
{
	return mainthreadPool;
}

void jm::System::Init()
{
	//First of all, the charsets
	InitCharsets();

	// Start Autorelease pool
	if(mainthreadPool == NULL)mainthreadPool = new AutoreleasePool();
	
	// Load default translation
	I18nBundle::InitDefault();	
}

void jm::System::Quit()
{
	if(mainthreadPool != NULL)delete mainthreadPool;

	//Zu allerletzt
	QuitCharsets();
}

