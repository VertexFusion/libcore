//
//  MacInterface.h
//  Core
//
//  Created by Uwe Runtemund on 29.10.23.
//

#ifndef MacInterface_h
#define MacInterface_h

#if defined(JM_MACOS) || defined(JM_IOS)//macOS, iOS
bool File_MoveToTrash(const char* cstr);
#elif defined JM_LINUX
#elif defined JM_WINDOWS
#endif

#endif /* MacInterface_h */
