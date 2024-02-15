//
//  Exception.cpp
//  jameo
//
//  Created by Uwe Runtemund on 16.01.13.
//  Copyright (c) 2013 Jameo Software. All rights reserved.
//

#include "Precompiled.h"

using namespace jm;
using std::cerr;
using std::endl;

Exception::Exception(String _message): Object()
{
	message = _message;
	System::Log(message, kLogError);

	#if defined(__APPLE__) || defined(__linux__)   //macOS & Linux
	tid = pthread_self();

	//Stacktrace aufnehmen.
	const int max_frames = 10;

	// temporäres Speicherarray für die Adressdaten
	void* taddrlist[max_frames];

	// Bekomme die Stack Adressen
	addrlen = backtrace(taddrlist, sizeof(taddrlist) / sizeof(void*));

	// Löse die Adressen in Namen auf
	char** symbols = NULL;
	symbols = backtrace_symbols(taddrlist, addrlen);
	symbollist = new String[addrlen];
	for(uint32 a = 0; a < addrlen; a++)
	{
		symbollist[a] = String(symbols[a]);
	}

	// Free is acc. to the docs (web find) the correct way to free the memory. delete / delete[] is
	// wrong.
	free(symbols);

	#elif defined _WIN32//Windows
	//Keine Threadbib
	symbollist = NULL;
	#endif

}

Exception::~Exception()
{
	if(symbollist != NULL)delete []symbollist;
}

String Exception::GetErrorMessage() const
{
	return message;
}

void Exception::PrintStackTrace() const
{
	#if defined(__APPLE__) || defined(__linux__)   //macOS & Linux

	//1. Zeile
	cerr << "Exception in thread \"" << tid  << "\"";
	if(message.Length() > 0)cerr << " : " << message;
	cerr << endl;

	char* buffer = new char[1024];

	for(uint32 i = 1; i < addrlen; i++)
	{

		#ifdef __APPLE__ //macOS
		//Formatierung 0   libjameo.dylib                      0x00000001005d7dec _ZN2jm9ExceptionC1ENS_6StringE + 184

		//Schneide Index (o) ab
		String line = symbollist[i];
		line = line.Trim();
		Integer pos = line.IndexOf(' ');
		line = line.Substring(pos).Trim();

		//Name der Binärdatei
		pos = line.IndexOf(' ');
		String binaryName = line.Substring(0, pos);
		line = line.Substring(pos).Trim();

		// Address
		pos = line.IndexOf(' ');
		String address = line.Substring(0, pos);
		line = line.Substring(pos).Trim();

		// Function
		pos = line.IndexOf(' ');
		String function = line.Substring(0, pos);
		line = line.Substring(pos).Trim();

		int status;
		size_t size = 1024;
		ByteArray cstr = function.ToCString();
		abi::__cxa_demangle(cstr.ConstData(), buffer, &size, &status);
		function = String(buffer, (int)size, Charset::ForName("RAW"));

		cerr << "\tat [" << binaryName << "] " << function << " (" << address << " " << line << ")" << endl;
		#elif defined __linux__//Linux
		String line = symbollist[i];
		cerr << "\ta" << line << endl;
		#elif defined _WIN32//Windows
		//Bisher nix
		#endif

	}
	delete[] buffer;

	#elif defined _WIN32//Windows
	//Keine Threadbib
	#endif

}

String Exception::GetStrackTrace() const
{
	String ret;

	#if defined(__APPLE__) || defined(__linux__)   //macOS & Linux

	//1. Zeile
	ret << "Exception in thread \"" << /* reinterpret_cast<int64>(tid)  << */ "\"";
	if(message.Length() > 0)ret << " : " << message;
	ret << '\r' << '\n';

	char* buffer = new char[1024];

	for(uint32 i = 1; i < addrlen; i++)
	{

		#ifdef __APPLE__ //macOS
		//Formatierung 0   libjameo.dylib                      0x00000001005d7dec _ZN2jm9ExceptionC1ENS_6StringE + 184

		//Schneide Index (o) ab
		String line = symbollist[i];
		line = line.Trim();
		Integer pos = line.IndexOf(' ');
		line = line.Substring(pos).Trim();

		//Name der Binärdatei
		pos = line.IndexOf(' ');
		String binaryName = line.Substring(0, pos);
		line = line.Substring(pos).Trim();

		// Address
		pos = line.IndexOf(' ');
		String address = line.Substring(0, pos);
		line = line.Substring(pos).Trim();

		// Function
		pos = line.IndexOf(' ');
		String function = line.Substring(0, pos);
		line = line.Substring(pos).Trim();

		int status;
		size_t size = 1024;
		ByteArray cstr = function.ToCString();
		abi::__cxa_demangle(cstr.ConstData(), buffer, &size, &status);
		function = String(buffer, (int)size, Charset::ForName("RAW"));

		ret << "\tat [" << binaryName << "] " << function << " (" << address << " " << line << ")" << '\r' << '\n';
		#elif defined __linux__//Linux
		String line = symbollist[i];
		ret << "\ta" << line << "\r\n";
		#elif defined _WIN32//Windows
		//Bisher nix
		#endif

	}
	delete[] buffer;

	#elif defined _WIN32//Windows
	//Keine Threadbib
	#endif

	return ret;
}
