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

// For Unix-like operating systems, we can easily use GNU C syntax extensions

#include <stdalign.h>

#define thread_local    _Thread_local

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

#endif /* zf_sys_h */

