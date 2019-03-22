//
//  zf_atomic.c
//  FoundationBasedAlgorithms
//
//  Created by Zenny Chen on 2018/11/20.
//  Copyright © 2018 CodeLearning Studio. All rights reserved.
//

#ifdef _WIN32

#include "zf_atomic.h"
#include <intrin.h>

int atomic_fetch_add(volatile atomic_int *object, int operand)
{
    int expected = *object;
    int desired;
    bool success;
    
    do
    {
        desired = expected + operand;
    }
    while ((success = atomic_compare_exchange_strong(object, &expected, desired)),
           (success? (void)0 : _mm_pause()),
           !success);
    
    return expected;
}

int atomic_fetch_sub(volatile atomic_int *object, int operand)
{
    int expected = *object;
    int desired;
    bool success;
    
    do
    {
        desired = expected - operand;
    } while ((success = atomic_compare_exchange_strong(object, &expected, desired)),
             (success ? (void)0 : _mm_pause()),
             !success);
    
    return expected;
}

int atomic_fetch_or(volatile atomic_int *object, int operand)
{
    return _InterlockedOr((long volatile *)object, operand);
}

int atomic_fetch_xor(volatile atomic_int *object, int operand)
{
    return _InterlockedXor((long volatile *)object, operand);
}

int atomic_fetch_and(volatile atomic_int *object, int operand)
{
    return _InterlockedAnd((long volatile *)object, operand);
}

int atomic_exchange(volatile atomic_int *object, int desired)
{
    return _InterlockedExchange((volatile long*)object, desired);
}

bool atomic_compare_exchange_strong(volatile atomic_int *object, int *expected, int desired)
{
    int comparand = *expected;
    int dstValue = _InterlockedCompareExchange((volatile long*)object, desired, comparand);
    bool success = dstValue == comparand;
    if (!success)
        *expected = dstValue;
    
    return success;
}

bool atomic_compare_exchange_weak(volatile atomic_int *object, int *expected, int desired)
{
    return atomic_compare_exchange_strong(object, expected, desired);
}

bool atomic_flag_test_and_set(volatile atomic_flag *flag)
{
    return _InterlockedExchange8((volatile char*)flag, 1) == 1;
}

void atomic_flag_clear(volatile atomic_flag *flag)
{
    _InterlockedExchange8((volatile char*)flag, 0);
}

#endif  // #ifdef _WIN32

