//
//  MacBindings.h
//  Core
//
//  Created by Uwe Runtemund on 29.10.23.
//

#ifndef MacBindings_h
#define MacBindings_h

#import <Foundation/Foundation.h>

@interface MacBindings : NSObject
{
}
// The Objective-C member function you want to call from C++
+ (bool) File_MoveToTrash:(const char *) cstr;
@end

#endif /* MacBindings_h */
