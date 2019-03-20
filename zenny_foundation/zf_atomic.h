//
//  zf_atomic.h
//  FoundationBasedAlgorithms
//
//  Created by Zenny Chen on 2018/11/20.
//  Copyright © 2018 CodeLearning Studio. All rights reserved.
//

#ifndef zf_atomic_h
#define zf_atomic_h

#define ZF_SPIN_LOCK_TRY_COUNT       100

// MARK: Basic atomics declaration

#ifndef _WIN32
// Unix-like OS environment
#include <stdatomic.h>
#include <unistd.h>

/// Let the current thread briefly sleep and make another thread run
static inline void zf_nap(void)
{
    usleep(10);
}

#else
// Windows OS environment
#include <windows.h>
#include <stdbool.h>

#define ATOMIC_VAR_INIT(value)      (value)
#define ATOMIC_FLAG_INIT            { false }
#define atomic_init(object, value)  (void)(*(object) = (value))

#ifdef __GNUC__
// For GNU C compilers, use more proper way to implement atomic_store and atomic_load.
#define atomic_store(object, desired)   (void)( *(volatile typeof(*(object)) *)(object) = (desired) )
#define atomic_load(object)             *(volatile typeof(*(object)) *)(object)
#else
// For other compilers, just use common way.
#define atomic_store(object, desired)   (void)( *(object) = (desired) )
#define atomic_load(object)             *(object)
#endif

typedef int    atomic_int;
typedef struct atomic_flag { bool _Value; } atomic_flag;

extern bool atomic_flag_test_and_set(volatile atomic_flag *flag);
extern void atomic_flag_clear(volatile atomic_flag *flag);

extern int atomic_fetch_add(volatile atomic_int *object, int operand);
extern int atomic_fetch_sub(volatile atomic_int *object, int operand);
extern int atomic_fetch_or(volatile atomic_int *object, int operand);
extern int atomic_fetch_xor(volatile atomic_int *object, int operand);
extern int atomic_fetch_and(volatile atomic_int *object, int operand);

extern int atomic_exchange(volatile atomic_int *object, int desired);

extern bool atomic_compare_exchange_strong(volatile atomic_int *object, int *expected, int desired);
extern bool atomic_compare_exchange_weak(volatile atomic_int *object, int *expected, int desired);

/// Let the current thread briefly sleep and make another thread run
static inline void zf_nap(void)
{
    Sleep(1);
}

#endif  // #ifndef _WIN32

// MARK: Zenny Foundation specific sync functions

/// CPU Pause. This is a hint that indicates CPU to temporarily
/// pause the current running thread.
static inline void zf_cpu_pause(void)
{
#if defined(__x86__) || defined(__i386__) || defined(__x86_64__)
    asm("pause");
#elif defined(__arm__) || defined(__arm64__)
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

#endif /* zf_atomic_h */

