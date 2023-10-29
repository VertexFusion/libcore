//
//  MacBindings.m
//  Core
//
//  Created by Uwe Runtemund on 29.10.23.
//

#include "core/MacBindings.h"
#include "core/MacInterface.h"

@implementation MacBindings

bool File_MoveToTrash(const char * cstr)
{
	 return [MacBindings File_MoveToTrash:cstr];
}

+ (bool) File_MoveToTrash:(const char *)cstr
{
	bool status=true;
	 @autoreleasepool
	{
		NSString* str = [NSString stringWithUTF8String: cstr];
		NSURL* fileURL = [[NSURL alloc] initFileURLWithPath:str];
		NSFileManager * fm = [NSFileManager defaultManager];
		NSURL * trash;
		NSError * error;

		status = [fm trashItemAtURL:fileURL resultingItemURL:&trash error:&error];
	 }
	
	 return status;
}

@end
