//
//  zf_sys.h
//  ZennyFoundationTest
//
//  Created by Zenny Chen on 2019/3/22.
//  Copyright © 2019 Zenny Chen. All rights reserved.
//

#ifndef zf_sys_h
#define zf_sys_h

#ifdef _WIN32
#include <Windows.h>
#endif

#include <stdio.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#ifndef _MSC_VER

#include <stdalign.h>
#include <stdnoreturn.h>

#define thread_local        _Thread_local

#else
// For MSVC

#define alignof             _Alignof
#define alignas(nBytes)     __declspec(align(nBytes))

#define thread_local        __declspec(thread)

#define noreturn            __declspec(noreturn)

/// signed size_t type which may be used in this foundation library
typedef ptrdiff_t   ssize_t;

#endif  // #ifndef _MSC_VER


#ifdef __GNUC__
// GNU C extensions

#ifndef let
#define let                 __auto_type
#endif

#define type_cast(expr)     (typeof(expr))

#else

#define type_cast(expr)

#endif  // #ifdef __GNUC__


// MARK: stdio relevant

#ifdef __ANDROID__

#include <syslog.h>

#define printf(...)     syslog(LOG_INFO, __VA_ARGS__)

#define puts(cstr)      printf("%s\n", cstr)

#endif  // #ifdef __ANDROID__

/// Gets a whole line from the stdin stream, excluding the last newline character.
/// @param buffer the buffer that stores the input string
/// @param maxBufferSize the maximum size of the buffer
/// @return if successful, return the number of bytes the buffer stores; Otherwise, return -1.
static inline ssize_t zf_get_console_line(char* buffer, size_t maxBufferSize)
{
    if (buffer == NULL)
        return -1;

#ifdef _WIN32

    char* result = gets_s(buffer, maxBufferSize);
    return result == NULL ? -1 : strlen(result);
    
#else
    
    char *tmpBuf = NULL;
    size_t nBytes = 0;
    ssize_t result = getline(&tmpBuf, &nBytes, stdin);
    if(result > 0)
    {
        int nIters = result < 2 ? (int)result : 2;
        for(ssize_t index = result - 1; nIters > 0; nIters--, index--)
        {
            if(tmpBuf[index] == '\r' || tmpBuf[index] == '\n')
                result--;
        }
        
        if(result >= maxBufferSize)
            result = maxBufferSize - 1;
        
        strncpy(buffer, tmpBuf, result);
    }
    
    if(tmpBuf != NULL)
        free(tmpBuf);
    
    if(result >= 0)
        buffer[result] = '\0';
    
    return result;

#endif
}

#endif /* zf_sys_h */

