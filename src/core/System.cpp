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

bool gSystemLogDate = true;
jm::LogLevel mSystemLogLabel = jm::kLogDebug;
jm::Preferences*  gPreferences=NULL;
jm::File* gPrefFile = NULL;

jm::String jm::System::language()
{
   #ifdef __APPLE__ //macOS und iOS

   CFArrayRef langs = CFLocaleCopyPreferredLanguages();
   CFStringRef cflangCode = (CFStringRef) CFArrayGetValueAtIndex(langs, 0);

   jm::String langCode = jm::String::fromCFString(cflangCode);

   CFRelease(langs);

   return langCode;

   #elif defined __linux__//Linux

   //const char* = setlocale(LC_ALL, NULL);

   return "de-DE";
   #elif defined _WIN32//Windows

   LANGID langid = GetUserDefaultUILanguage();

   switch(langid)
   {
      case 1031:
         return "de-DE";

      default:
         return "en";
   }

   #endif

}

void jm::System::logEnableDate(bool status)
{
   gSystemMutex.lock();
   gSystemLogDate = status;
   gSystemMutex.unlock();
}

void jm::System::logEnableLabel(jm::LogLevel logLevel)
{
   gSystemMutex.lock();
   mSystemLogLabel = logLevel;
   gSystemMutex.unlock();
}


void jm::System::log(const String &message, LogLevel logLevel)
{
   gSystemMutex.lock();

   jm::String msg;
   if(gSystemLogDate)msg << '[' << jm::Date().toString() << "] ";

   switch(logLevel)
   {
      case kLogError:
         msg << kTxtBold << kTxtRed;
         if(logLevel >= mSystemLogLabel)msg << Tr("ERROR: ");
         gSystemError = message;
         break;

      case 	kLogWarning:
         msg << kTxtBold << kTxtYellow;
         if(logLevel >= mSystemLogLabel)msg << Tr("WARNING: ");
         break;

      case kLogInformation:
         if(logLevel >= mSystemLogLabel)msg << Tr("INFO: ");
         break;

      case kLogDebug:
         if(logLevel >= mSystemLogLabel)msg << Tr("DEBUG: ");
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


   // Output to console
   if(logLevel > kLogDebug)std::cout << msg << std::endl;

   // Output to log file
   #ifdef __APPLE__ //macOS and iOS

   if(logLevel == kLogError)
   {
      //	setlogmask (LOG_UPTO (LOG_NOTICE));

      //	openlog ("jameo", LOG_CONS | LOG_PID | LOG_NDELAY, LOG_LOCAL1);

      ByteArray cstr = msg.toCString();
      syslog(LOG_ERR, "%s", cstr.constData());
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

   gSystemMutex.unlock();
}

const jm::String& jm::System::lastErrorMessage()
{
   return gSystemError;
}


jm::String jm::System::userId()
{
   #ifdef __APPLE__ //macOS und iOS

   return String(getenv("USER"));

   #elif defined __linux__//Linux

   return String(getenv("USER"));

   #elif defined _WIN32//Windows

   uint16 user_name[UNLEN + 1];
   DWORD user_name_size = sizeof(user_name);
   // Explicit type conversion under VC++ 2010 added.
   GetUserName((LPWSTR)user_name, &user_name_size);
   return String(user_name, user_name_size);

   #endif
}

jm::String jm::System::userFullName()
{
   #ifdef __APPLE__ //macOS und iOS

   return "Not implemented";//String(getenv("USER"));

   #elif defined __linux__//Linux

   uid_t uid= geteuid ();
   struct passwd* pw = NULL;
   pw = getpwuid (uid);
   if (pw)
   {
      return pw->pw_gecos;
   }

   return "Not Found";

   #elif defined _WIN32//Windows

   uint16 user_name[UNLEN + 1];
   DWORD user_name_size = sizeof(user_name);

   // This query works for domain accounts, but not for local users. An error is then returned.
   // Explicit type conversion under VC++ 2010 added.
   int ret = GetUserNameEx(NameDisplay, (LPWSTR)user_name, &user_name_size);
   if(ret != 0)return String(user_name, user_name_size);

   // Name could not be determined. Get it differently.
   // Explicit type conversion under VC++ 2010 added.
   ret = GetUserNameEx(NameSamCompatible, (LPWSTR)user_name, &user_name_size);
   if(ret == 0)return "<ERROR while searching username>";

   // Name has form "Uwe-PC\Uwe"
   String str = String(user_name, user_name_size);
   return str.substring(str.indexOf('\\') + 1);

   #endif

}

/*
Windows specific:

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

void* jm::System::loadDynamicLibrary(jm::File* file)
{
   #ifdef __APPLE__ //macOS and iOS

   ByteArray cstr = file->absolutePath().toCString();
   void* libptr = dlopen(cstr.constData(), RTLD_LAZY);   //RTLD_LAZY is default
   if(libptr == NULL) std::cout << "Loading dynamic library " << cstr.constData() << " failed!" << std::endl << dlerror() << std::endl;
   return libptr;

   #elif defined __linux__//Linux

   ByteArray cstr = file->absolutePath().toCString();
   void* libptr = dlopen(cstr.constData(), RTLD_LAZY);   //RTLD_LAZY is default
   if(libptr == NULL) std::cout << "Loading dynamic library " << cstr.constData() << " failed!" << std::endl << dlerror() << std::endl;
   return libptr;

   #elif defined _WIN32// Windows

   uint16* wstr = file->absolutePath().toWString();
   HMODULE libptr = LoadLibrary((LPCWSTR) wstr);
   delete[] wstr;
   if(libptr == NULL) std::cout << "Loading dynamic library " << file->absolutePath() << " failed!" << /*std::endl << dlerror() <<*/ std::endl;
   return libptr;

   #endif
}

void jm::System::unloadDynamicLibrary(void* library)
{
   #ifdef __APPLE__ //macOS und iOS

   int res = dlclose(library);
   if(res != 0) std::cout << "Closing dynamic library failed!" << std::endl << dlerror() << std::endl;

   #elif defined __linux__//Linux

   int res = dlclose(library);
   if(res != 0) std::cout << "Closing dynamic library failed!" << std::endl << dlerror() << std::endl;

   #elif defined _WIN32//Windows

   bool res = (bool)FreeLibrary((HMODULE) library);
   if(res == false) log("Closing dynamic library failed!", kLogError);

   #endif
}


void* jm::System::findSymbol(void* library, const String &name)
{
   #ifdef __APPLE__ //macOS and iOS

   ByteArray cstr = name.toCString();
   void* symptr = dlsym(library, cstr.constData());
   if(symptr == NULL) std::cout << "Locating " << name << " in dynamic library " << cstr.constData() << " failed!" << std::endl << dlerror() << std::endl;
   return symptr;

   #elif defined __linux__//Linux

   ByteArray cstr = name.toCString();
   void* symptr = dlsym(library, cstr.constData());
   if(symptr == NULL) std::cout << "Locating " << name << " in dynamic library " << cstr.constData() << " failed!" << std::endl << dlerror() << std::endl;
   return symptr;

   #elif defined _WIN32//Windows

   ByteArray cstring = name.toCString();
   void* ptr = GetProcAddress((HMODULE) library, cstring.constData());

   return ptr;

   #endif
}

// Global AutoreleasePool...
jm::AutoreleasePool* gMainThreadPool = NULL;
jm::String gBundleId;

jm::AutoreleasePool* jm::System::autoreleasePool()
{
   return gMainThreadPool;
}

const jm::String& jm::System::bundleId()
{
   return gBundleId;
}

void jm::System::init(const jm::String &bundleId)
{
   // First of all, the charsets
   InitCharsets();

   gBundleId=bundleId;

   // Start autorelease pool
   if(gMainThreadPool == NULL)gMainThreadPool = new AutoreleasePool();

   // Load default translation
   I18nBundle::initDefault();

   // Load default preferences, if any
   jm::File propDir = jm::PropertyDir();
   gPreferences = new jm::Preferences();
   gPrefFile  = new jm::File(propDir, bundleId + ".properties");
   std::cout<<gPrefFile->absolutePath()<<std::endl;
   if(gPrefFile->exists())gPreferences->load(*gPrefFile);
}

void jm::System::quit()
{
   // save preferences
   gPreferences->save(*gPrefFile);
   delete gPreferences;
   delete gPrefFile;

   if(gMainThreadPool != NULL)delete gMainThreadPool;

   // Finally
   QuitCharsets();
}

jm::Preferences* jm::System::preferences()
{
   return gPreferences;
}

