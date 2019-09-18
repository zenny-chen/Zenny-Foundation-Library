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

