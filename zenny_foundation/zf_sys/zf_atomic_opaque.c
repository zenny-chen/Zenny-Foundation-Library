//
//  zf_atomic_opaque.c
//  試合
//
//  Created by Zenny Chen on 2019/9/11.
//  Copyright © 2019 Zenny Chen. All rights reserved.
//

#include "zf_atomic_opaque.h"
#include "zf_atomic.h"

#ifdef _MSC_VER
#define _Atomic(type)   type
#endif


// MARK: atomic flag operations

bool zf_opaque_atomic_flag_test_and_set(volatile struct ZFOpaqueAtomicType *object)
{
    return atomic_flag_test_and_set((volatile atomic_flag*)object);
}

void zf_opaque_atomic_flag_clear(volatile struct ZFOpaqueAtomicType *object)
{
    atomic_flag_clear((volatile atomic_flag*)object);
}

// MARK: atomic load operations

bool zf_opaque_atomic_load_bool(volatile struct ZFOpaqueAtomicType *object)
{
    return atomic_load((volatile atomic_bool*)object);
}

int8_t zf_opaque_atomic_load_byte(volatile struct ZFOpaqueAtomicType *object)
{
    return atomic_load((volatile _Atomic(int8_t)*)object);
}

int16_t zf_opaque_atomic_load_short(volatile struct ZFOpaqueAtomicType *object)
{
    return atomic_load((volatile _Atomic(int16_t)*)object);
}

int32_t zf_opaque_atomic_load_int(volatile struct ZFOpaqueAtomicType *object)
{
    return atomic_load((volatile _Atomic(int32_t)*)object);
}

int64_t zf_opaque_atomic_load_long(volatile struct ZFOpaqueAtomicType *object)
{
    return atomic_load((volatile _Atomic(int64_t)*)object);
}

// MARK: atomic store operations

void zf_opaque_atomic_store_bool(volatile struct ZFOpaqueAtomicType *object, bool value)
{
    atomic_store((volatile atomic_bool*)object, value);
}

void zf_opaque_atomic_store_byte(volatile struct ZFOpaqueAtomicType *object, int8_t value)
{
    atomic_store((volatile _Atomic(int8_t)*)object, value);
}

void zf_opaque_atomic_store_short(volatile struct ZFOpaqueAtomicType *object, int16_t value)
{
    atomic_store((volatile _Atomic(int16_t)*)object, value);
}

void zf_opaque_atomic_store_int(volatile struct ZFOpaqueAtomicType *object, int32_t value)
{
    atomic_store((volatile _Atomic(int32_t)*)object, value);
}

void zf_opaque_atomic_store_long(volatile struct ZFOpaqueAtomicType *object, int64_t value)
{
    atomic_store((volatile _Atomic(int64_t)*)object, value);
}

// MARK: atomic fetch add operations

int8_t zf_opaque_atomic_fetch_add_byte(volatile struct ZFOpaqueAtomicType *object, int8_t value)
{
    return atomic_fetch_add((volatile _Atomic(int8_t)*)object, value);
}

int16_t zf_opaque_atomic_fetch_add_short(volatile struct ZFOpaqueAtomicType *object, int16_t value)
{
    return atomic_fetch_add((volatile _Atomic(int16_t)*)object, value);
}

int32_t zf_opaque_atomic_fetch_add_int(volatile struct ZFOpaqueAtomicType *object, int32_t value)
{
    return atomic_fetch_add((volatile _Atomic(int32_t)*)object, value);
}

int64_t zf_opaque_atomic_fetch_add_long(volatile struct ZFOpaqueAtomicType *object, int64_t value)
{
    return atomic_fetch_add((volatile _Atomic(int64_t)*)object, value);
}

// MARK: atomic fetch subtraction operations

int8_t zf_opaque_atomic_fetch_sub_byte(volatile struct ZFOpaqueAtomicType *object, int8_t value)
{
    return atomic_fetch_sub((volatile _Atomic(int8_t)*)object, value);
}

int16_t zf_opaque_atomic_fetch_sub_short(volatile struct ZFOpaqueAtomicType *object, int16_t value)
{
    return atomic_fetch_sub((volatile _Atomic(int16_t)*)object, value);
}

int32_t zf_opaque_atomic_fetch_sub_int(volatile struct ZFOpaqueAtomicType *object, int32_t value)
{
    return atomic_fetch_sub((volatile _Atomic(int32_t)*)object, value);
}

int64_t zf_opaque_atomic_fetch_sub_long(volatile struct ZFOpaqueAtomicType *object, int64_t value)
{
    return atomic_fetch_sub((volatile _Atomic(int64_t)*)object, value);
}

// MARK: atomic fetch or operations

int8_t zf_opaque_atomic_fetch_or_byte(volatile struct ZFOpaqueAtomicType *object, int8_t value)
{
    return atomic_fetch_or((volatile _Atomic(int8_t)*)object, value);
}

int16_t zf_opaque_atomic_fetch_or_short(volatile struct ZFOpaqueAtomicType *object, int16_t value)
{
    return atomic_fetch_or((volatile _Atomic(int16_t)*)object, value);
}

int32_t zf_opaque_atomic_fetch_or_int(volatile struct ZFOpaqueAtomicType *object, int32_t value)
{
    return atomic_fetch_or((volatile _Atomic(int32_t)*)object, value);
}

int64_t zf_opaque_atomic_fetch_or_long(volatile struct ZFOpaqueAtomicType *object, int64_t value)
{
    return atomic_fetch_or((volatile _Atomic(int64_t)*)object, value);
}

// MARK: atomic fetch xor operations

int8_t zf_opaque_atomic_fetch_xor_byte(volatile struct ZFOpaqueAtomicType *object, int8_t value)
{
    return atomic_fetch_xor((volatile _Atomic(int8_t)*)object, value);
}

int16_t zf_opaque_atomic_fetch_xor_short(volatile struct ZFOpaqueAtomicType *object, int16_t value)
{
    return atomic_fetch_xor((volatile _Atomic(int16_t)*)object, value);
}

int32_t zf_opaque_atomic_fetch_xor_int(volatile struct ZFOpaqueAtomicType *object, int32_t value)
{
    return atomic_fetch_xor((volatile _Atomic(int32_t)*)object, value);
}

int64_t zf_opaque_atomic_fetch_xor_long(volatile struct ZFOpaqueAtomicType *object, int64_t value)
{
    return atomic_fetch_xor((volatile _Atomic(int64_t)*)object, value);
}

// MARK: atomic fetch and operations

int8_t zf_opaque_atomic_fetch_and_byte(volatile struct ZFOpaqueAtomicType *object, int8_t value)
{
    return atomic_fetch_and((volatile _Atomic(int8_t)*)object, value);
}

int16_t zf_opaque_atomic_fetch_and_short(volatile struct ZFOpaqueAtomicType *object, int16_t value)
{
    return atomic_fetch_and((volatile _Atomic(int16_t)*)object, value);
}

int32_t zf_opaque_atomic_fetch_and_int(volatile struct ZFOpaqueAtomicType *object, int32_t value)
{
    return atomic_fetch_and((volatile _Atomic(int32_t)*)object, value);
}

int64_t zf_opaque_atomic_fetch_and_long(volatile struct ZFOpaqueAtomicType *object, int64_t value)
{
    return atomic_fetch_and((volatile _Atomic(int64_t)*)object, value);
}

// MARK: atomic exchange operations

int8_t zf_opaque_atomic_exchange_byte(volatile struct ZFOpaqueAtomicType *object, int8_t value)
{
    return atomic_exchange((volatile _Atomic(int8_t)*)object, value);
}

int16_t zf_opaque_atomic_exchange_short(volatile struct ZFOpaqueAtomicType *object, int16_t value)
{
    return atomic_exchange((volatile _Atomic(int16_t)*)object, value);
}

int32_t zf_opaque_atomic_exchange_int(volatile struct ZFOpaqueAtomicType *object, int32_t value)
{
    return atomic_exchange((volatile _Atomic(int32_t)*)object, value);
}

int64_t zf_opaque_atomic_exchange_long(volatile struct ZFOpaqueAtomicType *object, int64_t value)
{
    return atomic_exchange((volatile _Atomic(int64_t)*)object, value);
}

// MARK: atomic compare and exchange operations

bool zf_opaque_atomic_compare_exchange_byte(volatile struct ZFOpaqueAtomicType *object,
                                            int8_t *expected, int8_t desired)
{
    return atomic_compare_exchange_strong((volatile _Atomic(int8_t)*)object, expected, desired);
}

bool zf_opaque_atomic_compare_exchange_short(volatile struct ZFOpaqueAtomicType *object,
                                             int16_t *expected, int16_t desired)
{
    return atomic_compare_exchange_strong((volatile _Atomic(int16_t)*)object, expected, desired);
}

bool zf_opaque_atomic_compare_exchange_int(volatile struct ZFOpaqueAtomicType *object,
                                           int32_t *expected, int32_t desired)
{
    return atomic_compare_exchange_strong((volatile _Atomic(int32_t)*)object, expected, desired);
}

bool zf_opaque_atomic_compare_exchange_long(volatile struct ZFOpaqueAtomicType *object,
                                            int64_t *expected, int64_t desired)
{
    return atomic_compare_exchange_strong((volatile _Atomic(int64_t)*)object, expected, desired);
}

