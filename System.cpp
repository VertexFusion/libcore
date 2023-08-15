//
//  System.cpp
//  jameo
//
//  Created by Uwe Runtemund on 18.09.13.
//  Copyright (c) 2013 Jameo Software. All rights reserved.
//

#include "Precompiled.h"

jm::Mutex gSystemMutex;
jm::String gSystemError;

jm::String jm::System::GetLanguage()
{
	#ifdef __APPLE__ //macOS und iOS

	CFArrayRef langs = CFLocaleCopyPreferredLanguages();
	CFStringRef cflangCode = (CFStringRef) CFArrayGetValueAtIndex(langs, 0);

	int8 cstr[16];
	CFStringGetCString(cflangCode, cstr, sizeof(cstr), kCFStringEncodingUTF8);
	String langCode = String(cstr);

	CFRelease(langs);

	return langCode;

	#elif defined __linux__//Linux

	//const char* = setlocale(LC_ALL, NULL);

	return "de";
	#elif defined _WIN32//Windows

	return "de";

	#endif

}

void jm::System::Log(const String &message, LogLevel logLevel)
{
	gSystemMutex.Lock();

		jm::String msg;
		msg.Append('[');
		msg.Append(jm::Date().ToString());
		msg.Append(']');

		switch(logLevel)
		{
			case kLogError:
				msg.Append(" FEHLER: ");
				gSystemError = message;
				break;

			case 	kLogWarning:
				msg.Append(" WARNUNG: ");
				break;

			case kLogInformation:
				msg.Append(" INFO: ");
				break;

			case kLogDebug:
				msg.Append(" DEBUG: ");
				break;
		}
		msg.Append(message);

		//Ausgabe auf Console
		if(logLevel < kLogDebug)std::cout << msg << std::endl;

		//Ausgabe ins Logfile
		#ifdef __APPLE__ //macOS und iOS

		if(logLevel == kLogError)
		{
			//	setlogmask (LOG_UPTO (LOG_NOTICE));

			//	openlog ("jameo", LOG_CONS | LOG_PID | LOG_NDELAY, LOG_LOCAL1);

			const int8* cstr = msg.ToCString();
			syslog(LOG_ERR, "%s", cstr);
			delete cstr;
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

jm::String jm::System::GetLastErrorMessage()
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

	char* cstr = file->GetAbsolutePath().ToCString();
	void* libptr = dlopen(cstr, RTLD_LAZY);   //RTLD_LAZY ist default
	if(libptr == NULL) std::cout << "Loading dynamic library " << cstr << " failed!" << std::endl << dlerror() << std::endl;
	delete cstr;
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

	char* cstr = name.ToCString();
	void* symptr = dlsym(library, cstr);
	if(symptr == NULL) std::cout << "Locating " << name << " in dynamic library " << cstr << " failed!" << std::endl << dlerror() << std::endl;
	delete cstr;
	return symptr;

	#elif defined __linux__//Linux

	char* cstr = name.ToCString();
	void* symptr = dlsym(library, cstr);
	if(symptr == NULL) std::cout << "Locating " << name << " in dynamic library " << cstr << " failed!" << std::endl << dlerror() << std::endl;
	delete cstr;
	return symptr;

	#elif defined _WIN32//Windows

	const int8* cstring = name.ToCString();
	void* ptr = GetProcAddress((HMODULE) library, cstring);
	delete[] cstring;

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
	//Zu allererst
	InitCharsets();

	if(mainthreadPool == NULL)mainthreadPool = new AutoreleasePool();
}

void jm::System::Quit()
{
	if(mainthreadPool != NULL)delete mainthreadPool;

	//Zu allerletzt
	QuitCharsets();
}

