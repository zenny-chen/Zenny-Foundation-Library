//
//  zf_sync.h
//  ZennyFoundationTest
//
//  Created by Zenny Chen on 2019/3/22.
//  Copyright © 2019 Zenny Chen. All rights reserved.
//

#ifndef zf_sync_h
#define zf_sync_h

#include "zf_sys.h"
#include "zf_atomic.h"

#define ZF_SPIN_LOCK_TRY_COUNT       100

#ifndef _WIN32
// Unix-like OS environment

/// Let the current thread briefly sleep and make another thread run
static inline void zf_nap(void)
{
    usleep(10);
}

#else
// Windows OS environment

/// Let the current thread briefly sleep and make another thread run
static inline void zf_nap(void)
{
    Sleep(1);
}

#endif  // #ifdef _WIN32

/// CPU Pause. This is a hint that indicates CPU to temporarily
/// pause the current running thread.
static inline void zf_cpu_pause(void)
{
#if defined(__x86__) || defined(__i386__) || defined(__x86_64__)
    asm("pause");
#elif defined(__arm__)
    
#if defined(__ARM_ARCH_7__) || defined(__ARM_ARCH_7A__) || defined(__ARM_ARCH_7R__) || defined(__ARM_ARCH_7M__) || defined(__ARM_ARCH_7S__)
    asm("yield");
#endif

#elif defined(__aarch64__)
    asm("yield");
#else
    // For other CPU architectures, do nothing here...
#endif
}

/// Atomically lock
/// @param lock a pointer to atomic_flag instance
static inline void zf_lock(volatile atomic_flag *lock)
{
    int lockCount = 0;
    while(atomic_flag_test_and_set(lock))
    {
        zf_cpu_pause();
        if(++lockCount == ZF_SPIN_LOCK_TRY_COUNT)
        {
            lockCount = 0;
            zf_nap();
        }
    }
}

/// Atomically unlock
/// @param lock a pointer to atomic_flag instance
static inline void zf_unlock(volatile atomic_flag *lock)
{
    atomic_flag_clear(lock);
}

#endif  /* zf_sync_h */

