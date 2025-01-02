////////////////////////////////////////////////////////////////////////////////////////////////////
// Name:        Precompiled.h
// Library:     VertexFusion Library
// Purpose:     Header for precompilation
//
// Author:      Uwe Runtemund (2015-today)
// Modified by:
// Created:     30.03.2015
//
// Copyright:   (c) 2015 Jameo Software, Germany. https://jameo.de
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

#ifndef jm_Precompiled_h
#define jm_Precompiled_h

#include <cstring>
#include <cmath>
#include <iostream>
#include <vector>
#include <sys/stat.h>
#include <sstream>
#include <algorithm>
#include <iomanip>
#include <stdio.h>
#include <ctime>
#include <cstdio>
#include <typeinfo>
#include <chrono>

#ifdef __APPLE__//macOS, iOS
#include <cstdlib>
#include <dirent.h>
#include <stdint.h>
#include <unistd.h>
#include <mach-o/dyld.h>
#include "CoreFoundation/CFBundle.h"
#include <sys/time.h>
#include <execinfo.h>
#include <cxxabi.h>
#include <pthread.h>
#include <syslog.h>//Logging
#include "dlfcn.h"//macos zum Laden von dylibs
#include <sys/time.h>
#include <cstdarg>
#include <ifaddrs.h> // For MAC address
#include <netinet/in.h> // For MAC address
#include <net/if_types.h> // For MAC address
#include <net/if_dl.h> // For MAC address

#include "core/MacInterface.h"
#elif defined __linux__ //Linux

#include <errno.h>
#include <cstdlib>
#include <stdint.h>
#include <stdio.h>
#include <dirent.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>
#include <execinfo.h>
#include <cxxabi.h>
#include <pthread.h>
#include <locale.h>
#include <sys/syscall.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dlfcn.h>
#include <pwd.h>
#include <sys/xattr.h> // For File Tags
#include <ifaddrs.h>
#include <arpa/inet.h>  
#include <linux/if_packet.h>
#include <linux/if_ether.h>

#ifdef __ANDROID__
#include <jni.h>

// Implemented in nuitk
JNIEnv* getJNIEnv();
jobject activity();

#endif

#elif defined _WIN32 // Windows

#define NOMINMAX
#include <windows.h>
#undef NOMINMAX

// We have to undefine, because we have a function with that name!
#ifdef DrawText
#undef DrawText
#endif

#ifdef GetObject
#undef GetObject
#endif


#include <Lmcons.h>
#include <direct.h>
#include <Shlobj.h>
#include <shlwapi.h>

// We need that for GetUsernameEX
#define SECURITY_WIN32
#include <Security.h>
#undef SECURITY_WIN32

#endif

#include "zlib/zlib.h"
#include "core/Core.h"

#endif
