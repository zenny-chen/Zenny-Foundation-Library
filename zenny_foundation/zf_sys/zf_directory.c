//
//  zf_directory.c
//  ZennyFoundationTest
//
//  Created by Zenny Chen on 2019/3/18.
//  Copyright © 2019 Zenny Chen. All rights reserved.
//

#include "zf_directory.h"
#include <stdint.h>

#define ZF_MAX_PATH_CHARACTERS	512

/// Store the current executable directory
static char sCurrentExecPath[ZF_MAX_PATH_CHARACTERS];

#ifdef __APPLE__

#include <mach-o/dyld.h>

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

#elif defined(_WIN32)

#include <windows.h>
#include <uchar.h>

const char* zf_get_current_exec_path(void)
{
    if(sCurrentExecPath[0] == '\0')
    {
        char16_t path[ZF_MAX_PATH_CHARACTERS];

        const int maxSize = ZF_MAX_PATH_CHARACTERS - 1;
        GetModuleFileNameW(NULL, path, maxSize);
        
        int len = WideCharToMultiByte(CP_UTF8, 0, path, -1, NULL, 0, NULL, NULL);
        if(len > maxSize)
            len = maxSize;

        WideCharToMultiByte(CP_UTF8, 0, path, -1, sCurrentExecPath, len, NULL, NULL);
    }

    return sCurrentExecPath;
}

bool zf_create_directory(const char *path)
{
    if (path == NULL)
        return false;

    const int pathLen = (int)strlen(path);
    if (pathLen == 0)
        return false;

    const int wideStrLen = MultiByteToWideChar(CP_UTF8, 0, path, pathLen, NULL, 0);
    if (wideStrLen >= ZF_MAX_PATH_CHARACTERS)
        return false;

    char16_t wideStr[ZF_MAX_PATH_CHARACTERS];
    MultiByteToWideChar(CP_UTF8, 0, path, pathLen, wideStr, wideStrLen);
    wideStr[wideStrLen] = 0;

    return CreateDirectoryW(wideStr, NULL);
}

#else

// Other unix-like operating systems
#include <unistd.h>

const char* zf_get_current_exec_path(void)
{
    if(sCurrentExecPath[0] == '\0')
    {
        const int maxSize = ZF_MAX_PATH_CHARACTERS - 1;
        int size = readlink("/proc/self/exe", sCurrentExecPath, sizeof(sCurrentExecPath));
        if(size > maxSize)
            size = maxSize;
        
        sCurrentExecPath[size] = '\0';
    }
    
    return sCurrentExecPath;
}

#endif


#ifndef _WIN32

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

bool zf_create_directory(const char *path)
{
    if(path == NULL)
        return false;

    struct stat st = { };

    if(stat(path, &st) == -1)
        return mkdir(path, 0777) == 0;

    return true;
}

#endif

