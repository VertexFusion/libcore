//
//  Exception.cpp
//  jameo
//
//  Created by Uwe Runtemund on 16.01.13.
//  Copyright (c) 2013 Jameo Software. All rights reserved.
//

#include "PrecompiledCore.hpp"

using namespace jm;

Exception::Exception(const String& message): Object()
{
   mMessage = message;
   System::log(mMessage, LogLevel::kError);

#if defined(JM_MACOS) || defined(JM_IOS) || defined(JM_LINUX)

   tid = pthread_self();

   //Stacktrace aufnehmen.
   const int max_frames = 10;

   // temporäres Speicherarray für die Adressdaten
   void* taddrlist[max_frames];

   // Bekomme die Stack Adressen
   addrlen = backtrace(taddrlist, sizeof(taddrlist) / sizeof(void*));

   // Löse die Adressen in Namen auf
   char** symbols = nullptr;
   symbols = backtrace_symbols(taddrlist, addrlen);

   for(uint32 a = 0; a < addrlen; a++)
   {
      mSymbolList.append(String(symbols[a]));
   }

   // Free is acc. to the docs (web find) the correct way to free the memory. delete / delete[] is
   // wrong.
   free(symbols);

#elif defined JM_WINDOWS
   //Keine Threadbib
#endif

}

Exception::Exception(const Exception& other): Object(),
   mMessage(other.mMessage),
   addrlen(other.addrlen),
   mSymbolList(other.mSymbolList)
{
#if defined(JM_MACOS) || defined(JM_IOS) || defined(JM_LINUX) || defined(JM_ANDROID)
   tid = other.tid;
#elif defined JM_WINDOWS
   //Keine Threadbib
#endif
}

String Exception::errorMessage() const
{
   return mMessage;
}

void Exception::printStackTrace() const
{
#if defined(JM_MACOS) || defined(JM_IOS) || defined(JM_LINUX) || defined(JM_ANDROID)

   //1. Zeile
   std::cerr << "Exception in thread \"" << tid  << "\"";
   if(mMessage.size() > 0)std::cerr << " : " << mMessage;
   std::cerr << std::endl;

   char* buffer = new char[1024];
   memset(buffer, 0, 1024);

   for(uint32 i = 1; i < addrlen; i++)
   {

#if defined(JM_MACOS) || defined(JM_IOS)
      //Formatierung 0   libjameo.dylib                      0x00000001005d7dec _ZN2jm9ExceptionC1ENS_6StringE + 184

      //Schneide Index (o) ab
      String line = mSymbolList[i];
      line = line.trim();
      int64 pos = line.indexOf(' ');
      line = line.substring(pos).trim();

      //Name der Binärdatei
      pos = line.indexOf(' ');
      String binaryName = line.substring(0, pos);
      line = line.substring(pos).trim();

      // Address
      pos = line.indexOf(' ');
      String address = line.substring(0, pos);
      line = line.substring(pos).trim();

      // Function
      pos = line.indexOf(' ');
      String function = line.substring(0, pos);
      line = line.substring(pos).trim();

      int status;
      size_t size = 1024;
      ByteArray cstr = function.toCString();
      abi::__cxa_demangle(cstr.constData(), buffer, &size, &status);
      function = String(buffer, (int)size, Charset::forName("RAW"));

      std:: cerr << "\tat [" << binaryName << "] " << function << " (" << address << " " << line << ")" <<
                 std::endl;
#elif defined(JM_LINUX) || defined(JM_ANDROID)
      String line = mSymbolList[i];
      std::cerr << "\ta" << line << std::endl;
#elif defined JM_WINDOWS
      //Bisher nix
#endif

   }
   delete[] buffer;

#elif defined JM_WINDOWS
   //Keine Threadbib
#endif

}

String Exception::GetStrackTrace() const
{
   String ret;

#if defined(JM_MACOS) || defined(JM_IOS) || defined(JM_LINUX) || defined(JM_ANDROID)

   //1. Zeile
   ret << "Exception in thread \"" << /* reinterpret_cast<int64>(tid)  << */ "\"";
   if(mMessage.size() > 0)ret << " : " << mMessage;
   ret << '\r' << '\n';

   char* buffer = new char[1024];
   memset(buffer, 0, 1024);

   for(uint32 i = 1; i < addrlen; i++)
   {

#if defined(JM_MACOS) || defined(JM_IOS) //macOS
      //Formatierung 0   libjameo.dylib                      0x00000001005d7dec _ZN2jm9ExceptionC1ENS_6StringE + 184

      //Schneide Index (o) ab
      String line = mSymbolList[i];
      line = line.trim();
      int64 pos = line.indexOf(' ');
      line = line.substring(pos).trim();

      //Name der Binärdatei
      pos = line.indexOf(' ');
      String binaryName = line.substring(0, pos);
      line = line.substring(pos).trim();

      // Address
      pos = line.indexOf(' ');
      String address = line.substring(0, pos);
      line = line.substring(pos).trim();

      // Function
      pos = line.indexOf(' ');
      String function = line.substring(0, pos);
      line = line.substring(pos).trim();

      int status;
      size_t size = 1024;
      ByteArray cstr = function.toCString();
      abi::__cxa_demangle(cstr.constData(), buffer, &size, &status);
      function = String(buffer, (int)size, Charset::forName("RAW"));

      ret << "\tat [" << binaryName << "] " << function << " (" << address << " " << line << ")" << '\r'
          << '\n';
#elif defined(JM_LINUX) || defined(JM_ANDROID)
      String line = mSymbolList[i];
      ret << "\ta" << line << "\r\n";
#elif defined JM_WINDOWS
      //Bisher nix
#endif

   }
   delete[] buffer;

#elif defined JM_WINDOWS
   //Keine Threadbib
#endif

   return ret;
}
