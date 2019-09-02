//
//  zf_sys.h
//  ZennyFoundationTest
//
//  Created by Zenny Chen on 2019/3/22.
//  Copyright © 2019 Zenny Chen. All rights reserved.
//

#ifndef zf_sys_h
#define zf_sys_h

#include <stdio.h>

#ifndef _MSC_VER

// Unix-like OS environment
#include <unistd.h>
#include <stdalign.h>

#define thread_local    _Thread_local

// For Unix-like operating systems, we can easily use GNU C syntax extensions
#ifndef let
#define let     __auto_type
#endif

#else

// For MSVC

#include <stddef.h>

#define alignof             _Alignof
#define alignas(nBytes)     __declspec(align(nBytes))

#define thread_local        __declspec(thread)

/// signed size_t type which may be used in this foundation library
typedef ptrdiff_t   ssize_t;

#endif  // #ifndef _MSC_VER

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

#endif
}



#endif /* zf_sys_h */

