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

#include "PrecompiledCore.hpp"

jm::Mutex gSystemMutex;
jm::String gSystemError;

bool gSystemLogDate = true;
jm::LogLevel mSystemLogLabel = jm::LogLevel::kDebug;
jm::Preferences*  gPreferences = nullptr;
jm::File* gPrefFile = nullptr;

jm::String jm::System::language()
{
#if defined(JM_MACOS) || defined(JM_IOS) //macOS und iOS

   CFArrayRef langs = CFLocaleCopyPreferredLanguages();
   CFStringRef cflangCode = (CFStringRef) CFArrayGetValueAtIndex(langs, 0);

   jm::String langCode = jm::String::fromCFString(cflangCode);

   CFRelease(langs);

   return langCode;

#elif defined JM_LINUX

// Set the locale to the user's environment locale (if not already set)
   if(setlocale(LC_ALL, "") == nullptr)
   {
      std::cerr << "Failed to set locale" << std::endl;
   }

   // Use nl_langinfo to get the language
   const char* language = setlocale(LC_ALL, nullptr);

   jm::String lang = jm::String(language);
   size_t index = lang.indexOf('.');
   if(index > 0)lang = lang.substring(0, index);
   return lang;

#elif defined JM_ANDROID
   return osSystemLanguage();

#elif defined JM_WINDOWS

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


void jm::System::log(const String& message, LogLevel logLevel)
{
   gSystemMutex.lock();

   jm::String msg;
   if(gSystemLogDate)msg << '[' << jm::Date().toString() << "] ";

   switch(logLevel)
   {
      case LogLevel::kError:
         msg << kTxtBold << kTxtRed;
         if(logLevel >= mSystemLogLabel)msg << Tr("ERROR: ");
         gSystemError = message;
         break;

      case 	LogLevel::kWarning:
         msg << kTxtBold << kTxtYellow;
         if(logLevel >= mSystemLogLabel)msg << Tr("WARNING: ");
         break;

      case LogLevel::kInformation:
         if(logLevel >= mSystemLogLabel)msg << Tr("INFO: ");
         break;

      case LogLevel::kDebug:
         if(logLevel >= mSystemLogLabel)msg << Tr("DEBUG: ");
         break;
   }
   msg << message;

   switch(logLevel)
   {
      case LogLevel::kError:
      case LogLevel::kWarning:
         msg << kTxtReset;
         break;

      default:
         // Do nothing here.
         break;
   }


   // Output to console
   if(logLevel > LogLevel::kDebug)std::cout << msg << std::endl;

   // Output to log file
#ifdef __APPLE__ //macOS and iOS

   if(logLevel == LogLevel::kError)
   {
      //	setlogmask (LOG_UPTO (LOG_NOTICE));

      //	openlog ("jameo", LOG_CONS | LOG_PID | LOG_NDELAY, LOG_LOCAL1);

      ByteArray cstr = msg.toCString();
      syslog(LOG_ERR, "%s", cstr.constData());
      //	syslog (LOG_INFO, "A tree falls in a forest");

      //	closelog ();
   }

#elif defined(JM_LINUX) || defined(JM_ANDROID)


#elif defined JM_WINDOWS

   if(logLevel == LogLevel::kError)
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

   return String(std::getenv("USER"));

#elif defined(JM_LINUX) || defined(JM_ANDROID)

   return String(std::getenv("USER"));

#elif defined JM_WINDOWS

   uint16 user_name[UNLEN + 1];
   DWORD user_name_size = sizeof(user_name);
   // Explicit type conversion under VC++ 2010 added.
   GetUserName((LPWSTR)user_name, &user_name_size);
   return String(user_name, user_name_size-1); // Size contains 0 at end

#endif
}

jm::String jm::System::userFullName()
{
#ifdef __APPLE__ //macOS und iOS

   return " jm::System::userFullName() not implemented";//String(getenv("USER"));

#elif defined(JM_LINUX) || defined(JM_ANDROID)

   uid_t uid = geteuid();
   struct passwd* pw = nullptr;
   pw = getpwuid(uid);
   if(pw)
   {
      return pw->pw_gecos;
   }

   return "userFullName Not Found";

#elif defined JM_WINDOWS

   uint16 user_name[UNLEN + 1];
   DWORD user_name_size = sizeof(user_name);

   // This query works for domain accounts, but not for local users. An error is then returned.
   // Explicit type conversion under VC++ 2010 added.
   int ret = GetUserNameEx(NameDisplay, (LPWSTR)user_name, &user_name_size);
   if(ret != 0)return String(user_name, user_name_size);

   // Name could not be determined. Get it differently.
   // Explicit type conversion under VC++ 2010 added.
   ret = GetUserNameEx(NameSamCompatible, (LPWSTR)user_name, &user_name_size);
   if(ret == 0)return "userFullName Not Found";

   // Name has form "Uwe-PC\Uwe"
   String str = String(user_name, user_name_size);
   return str.substring(str.indexOf('\\') + 1);

#endif

}

jm::String jm::System::macAddress1()
{
#ifdef __APPLE__ //macOS und iOS

   struct ifaddrs* ifap, *ifa;
   char macAddress[18] = {0};

   if(getifaddrs(&ifap) == -1)
   {
      perror("getifaddrs");
      return "";
   }

   for(ifa = ifap; ifa != nullptr; ifa = ifa->ifa_next)
   {
      if(ifa->ifa_addr->sa_family == AF_LINK)  // check for ethernet
      {
         struct sockaddr_dl* sdl = (struct sockaddr_dl*)ifa->ifa_addr;
         if(sdl->sdl_type == IFT_ETHER)  // Ethernet interface
         {
            const unsigned char* mac = (const unsigned char*)LLADDR(sdl);
            snprintf(macAddress, sizeof(macAddress), "%02x:%02x:%02x:%02x:%02x:%02x",
                     mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
            break;
         }
      }
   }

   freeifaddrs(ifap);

   return jm::String(macAddress);

#elif defined(JM_LINUX) || defined(JM_ANDROID)

   struct ifaddrs* ifap, *ifa;
   struct sockaddr_ll* sll;
   char macAddress[18] = {0};

   if(getifaddrs(&ifap) == -1)
   {
      perror("getifaddrs");
      return "";
   }

   for(ifa = ifap; ifa != nullptr; ifa = ifa->ifa_next)
   {
      if(ifa->ifa_addr->sa_family == AF_PACKET)  // check for ethernet
      {
         sll = (struct sockaddr_ll*)ifa->ifa_addr;
         if(sll->sll_protocol == htons(ETH_P_IP))
         {
            unsigned char* mac = sll->sll_addr;
            snprintf(macAddress, sizeof(macAddress), "%02x:%02x:%02x:%02x:%02x:%02x",
                     mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
            break;
         }
      }
   }

   freeifaddrs(ifap);

   return jm::String(macAddress);

#elif defined JM_WINDOWS
   return jm::kEmptyString;
#endif
}

void* jm::System::loadDynamicLibrary(jm::File* file)
{
#ifdef __APPLE__ //macOS and iOS

   ByteArray cstr = file->absolutePath().toCString();
   void* libptr = dlopen(cstr.constData(), RTLD_LAZY);   //RTLD_LAZY is default
   if(libptr == nullptr) std::cout << "Loading dynamic library " << cstr.constData() << " failed!" <<
                                      std::endl << dlerror() << std::endl;
   return libptr;

#elif defined(JM_LINUX) || defined(JM_ANDROID)

   ByteArray cstr = file->absolutePath().toCString();
   void* libptr = dlopen(cstr.constData(), RTLD_LAZY);   //RTLD_LAZY is default
   if(libptr == nullptr) std::cout << "Loading dynamic library " << cstr.constData() << " failed!" <<
                                      std::endl << dlerror() << std::endl;
   return libptr;

#elif defined JM_WINDOWS

   uint16* wstr = file->absolutePath().toWString();
   HMODULE libptr = LoadLibrary((LPCWSTR) wstr);
   delete[] wstr;
   if(libptr == nullptr) std::cout << "Loading dynamic library " << file->absolutePath() << " failed!"
                                      << /*std::endl << dlerror() <<*/ std::endl;
   return libptr;

#endif
}

void jm::System::unloadDynamicLibrary(void* library)
{
#ifdef __APPLE__ //macOS und iOS

   int res = dlclose(library);
   if(res != 0) std::cout << "Closing dynamic library failed!" << std::endl << dlerror() << std::endl;

#elif defined(JM_LINUX) || defined(JM_ANDROID)

   int res = dlclose(library);
   if(res != 0) std::cout << "Closing dynamic library failed!" << std::endl << dlerror() << std::endl;

#elif defined JM_WINDOWS

   bool res = (bool)FreeLibrary((HMODULE) library);
   if(res == false) log("Closing dynamic library failed!", LogLevel::kError);

#endif
}


void* jm::System::findSymbol(void* library, const String& name)
{
#ifdef __APPLE__ //macOS and iOS

   ByteArray cstr = name.toCString();
   void* symptr = dlsym(library, cstr.constData());
   if(symptr == nullptr) std::cout << "Locating " << name << " in dynamic library " << cstr.constData() <<
                                      " failed!" << std::endl << dlerror() << std::endl;
   return symptr;

#elif defined(JM_LINUX) || defined(JM_ANDROID)

   ByteArray cstr = name.toCString();
   void* symptr = dlsym(library, cstr.constData());
   if(symptr == nullptr) std::cout << "Locating " << name << " in dynamic library " << cstr.constData() <<
                                      " failed!" << std::endl << dlerror() << std::endl;
   return symptr;

#elif defined JM_WINDOWS

   ByteArray cstring = name.toCString();
   void* ptr = GetProcAddress((HMODULE) library, cstring.constData());

   return ptr;

#endif
}

// Global AutoreleasePool...
jm::AutoreleasePool* gMainThreadPool = nullptr;
jm::String gBundleId;

jm::AutoreleasePool* jm::System::autoreleasePool()
{
   return gMainThreadPool;
}

const jm::String& jm::System::bundleId()
{
   return gBundleId;
}

void jm::System::init(const jm::String& bundleId)
{
   // First of all, the charsets
   initCharsets();

   gBundleId = bundleId;

   // Start autorelease pool
   if(gMainThreadPool == nullptr)gMainThreadPool = new AutoreleasePool();

   // Load default translation
   I18nBundle::initDefault();

   // Preferences hashtable should be always there
   gPreferences = new jm::Preferences();

   if(bundleId.size() == 0)return; // No preferences for this bundle

   // Load default preferences, if any
   jm::File propDir = jm::PropertyDir();
   gPrefFile  = new jm::File(propDir, bundleId + ".properties");
   if(gPrefFile->exists())gPreferences->load(*gPrefFile);
}

void jm::System::quit()
{
   // save preferences
   jm::System::savePreferences();
   if(gPreferences != nullptr)
   {
      delete gPreferences;
      delete gPrefFile;
      gPreferences = nullptr;
      gPrefFile = nullptr;
   }

   if(gMainThreadPool != nullptr)
   {
      delete gMainThreadPool;
      gMainThreadPool = nullptr;
   }

   jm::I18nBundle::quitDefault();

   // Finally
   quitCharsets();
}

jm::Preferences* jm::System::preferences()
{
   return gPreferences;
}

void jm::System::savePreferences()
{
   if(gPreferences != nullptr && gPrefFile != nullptr)
   {
      gPreferences->save(*gPrefFile);
   }
}
