//
//  zf_directory.c
//  ZennyFoundationTest
//
//  Created by Zenny Chen on 2019/3/18.
//  Copyright © 2019 Zenny Chen. All rights reserved.
//

#ifndef __APPLE__

#include "zf_sys.h"
#include "zf_directory.h"
#include <stdio.h>
#include <string.h>
#include <stdint.h>

/// Store the current executable directory
static char sCurrentExecPath[ZF_MAX_PATH_CHARACTERS];

#ifdef _WIN32

// For Windows platforms
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
    wideStr[wideStrLen] = u'\0';

    if(CreateDirectoryW(wideStr, NULL) == 0)
        return GetLastError() == ERROR_ALREADY_EXISTS;
    
    return true;
}

/* Recursively remove all the files in the specified directory */
static bool RecursivelyRemoveDirectory(const char16_t *wpath)
{
    HANDLE hFind;  // file handle
    WIN32_FIND_DATA findFileData;

    char16_t dirPath[MAX_PATH];
    char16_t fileName[MAX_PATH];

    wcscpy_s(dirPath, _countof(dirPath), wpath);
    wcscat(dirPath, u"/*");     // searching all files
    wcscpy_s(fileName, _countof(fileName), wpath);
    wcscat(fileName, u"/");

    hFind = FindFirstFile(dirPath, &findFileData); // find the first file
    if (hFind == INVALID_HANDLE_VALUE)
        return false;

    wcscpy_s(dirPath, _countof(dirPath), fileName);

    const char16_t currDir[] = { u'.', u'\0' };
    const char16_t upperDir[] = { u'.', u'.', u'\0' };

    bool bSearch = true;
    while (bSearch) 
    {
        // until we finds an entry
        if (FindNextFile(hFind, &findFileData))
        {
            const char16_t *currFoundFileName = findFileData.cFileName;

            // Ignore the '.' and '..' directories
            if (wcscmp(currFoundFileName, currDir) == 0 || wcscmp(currFoundFileName, upperDir) == 0)
                continue;

            wcscat(fileName, currFoundFileName);
            if ((findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0) 
            {
                // we have found a directory, recurse
                if (!RecursivelyRemoveDirectory(fileName))
                {
                    FindClose(hFind);
                    return false; // directory couldn't be deleted
                }

                RemoveDirectoryW(fileName); // remove the empty directory
                wcscpy_s(fileName, _countof(fileName), dirPath);
            }
            else 
            {
                if (findFileData.dwFileAttributes & FILE_ATTRIBUTE_READONLY)
                    SetFileAttributes(fileName, FILE_ATTRIBUTE_NORMAL);

                if (!DeleteFileW(fileName)) 
                {  
                    // delete the file
                    FindClose(hFind);
                    return false;
                }
                wcscpy_s(fileName, _countof(fileName), dirPath);
            }
        }
        else 
        {
            if (GetLastError() == ERROR_NO_MORE_FILES) // no more files there
                bSearch = false;
            else 
            {
                // some error occured, close the handle and return FALSE
                FindClose(hFind);
                return false;
            }
        }
    }

    FindClose(hFind);  // closing file handle

    return RemoveDirectoryW(wpath); // remove the empty directory
}

void zf_remove_directory(const char *path)
{
    if (path == NULL)
        return;

    const int pathLen = (int)strlen(path);
    if (pathLen == 0 || pathLen >= ZF_MAX_PATH_CHARACTERS)
        return;

    const int wpathLen = MultiByteToWideChar(CP_UTF8, 0, path, pathLen, NULL, 0);
    if (wpathLen >= MAX_PATH)
        return;

    char16_t wpath[ZF_MAX_PATH_CHARACTERS];
    MultiByteToWideChar(CP_UTF8, 0, path, pathLen, wpath, wpathLen);
    wpath[wpathLen] = u'\0';

    RecursivelyRemoveDirectory(wpath);
}

#else

// Other unix-like operating systems but not Apple platforms
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <fcntl.h>

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

bool zf_create_directory(const char *path)
{
    if(path == NULL)
        return false;

    struct stat st = { };

    if(stat(path, &st) == -1)
        return mkdir(path, 0777) == 0;

    return true;
}

void zf_remove_directory(const char *path)
{
    if(path == NULL)
        return;

    const char currDir[] = { '.', '\0' };
    const char upperDir[] = { '.', '.', '\0' };
    
    char dirName[ZF_MAX_PATH_CHARACTERS];
    struct stat dir_stat;
    
    // If the path does not exist, just return
    if(access(path, F_OK) != 0)
        return;
    
    // Failed to get the attribute of the directory
    if(stat(path, &dir_stat) < 0)
        return;
    
    // Remove the regular file directly
    if(S_ISREG(dir_stat.st_mode))
        remove(path);
    else if(S_ISDIR(dir_stat.st_mode))
    {
        // Recursively remove the sub-directories
        DIR *dirp = opendir(path);
        if(dirp == NULL)
            return;
        
        struct dirent *dp;
        while((dp = readdir(dirp)) != NULL)
        {
            // Ignore the `.` and `..` directories
            if (strcmp(currDir, dp->d_name) == 0 || strcmp(upperDir, dp->d_name) == 0)
                continue;
            
            sprintf(dirName, "%s/%s", path, dp->d_name);
            
            // call the function recursively
            zf_remove_directory(dirName);
        }
        
        closedir(dirp);
        
        // Remove the empty directory
        rmdir(path);
    }
}

#endif      // #ifndef _WIN32

#endif      // #ifndef __APPLE__

