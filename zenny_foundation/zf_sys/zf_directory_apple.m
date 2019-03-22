//
//  zf_directory_apple.m
//  ZennyFoundationTest
//
//  Created by Zenny Chen on 2019/3/22.
//  Copyright © 2019 Zenny Chen. All rights reserved.
//

#ifdef __APPLE__

@import Foundation;

#include "zf_sys.h"
#include "zf_directory.h"
#include <mach-o/dyld.h>

/// Store the current executable directory
static char sCurrentExecPath[ZF_MAX_PATH_CHARACTERS];

const char* zf_get_current_exec_path(void)
{
    if(sCurrentExecPath[0] == '\0')
    {
        const int maxSize = ZF_MAX_PATH_CHARACTERS - 1;
        uint32_t size = 0;
        _NSGetExecutablePath(NULL, &size);
        if(size > maxSize)
            size = maxSize;
        
        _NSGetExecutablePath(sCurrentExecPath, &size);
        sCurrentExecPath[size] = '\0';
    }
    
    return sCurrentExecPath;
}

bool zf_create_directory(const char *path)
{
    if(path == NULL)
        return false;
    
    let pathStr = [NSString stringWithUTF8String:path];
    if(pathStr == nil || pathStr.length == 0)
        return false;

    return [NSFileManager.defaultManager createDirectoryAtPath:pathStr withIntermediateDirectories:YES attributes:nil error:NULL];
}

void zf_remove_directory(const char *path)
{
    if(path == NULL)
        return;
    
    let pathStr = [NSString stringWithUTF8String:path];
    if(pathStr == nil || pathStr.length == 0)
        return;
    
    [NSFileManager.defaultManager removeItemAtPath:pathStr error:NULL];
}

#endif

