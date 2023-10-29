//
//  MacInterface.h
//  Core
//
//  Created by Uwe Runtemund on 29.10.23.
//

#ifndef MacInterface_h
#define MacInterface_h

#ifdef __APPLE__//macOS, iOS
bool File_MoveToTrash(const char * cstr);
#elif defined __linux__ //Linux
#elif defined _WIN32//Windows
#endif

#endif /* MacInterface_h */
