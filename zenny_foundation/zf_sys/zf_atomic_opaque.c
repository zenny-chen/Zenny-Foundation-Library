//
//  zf_atomic_opaque.c
//  試合
//
//  Created by Zenny Chen on 2019/9/11.
//  Copyright © 2019 Zenny Chen. All rights reserved.
//

#include "zf_atomic_opaque.h"

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

char zf_opaque_atomic_load_char(volatile struct ZFOpaqueAtomicType *object)
{
    return  atomic_load((volatile atomic_char*)object);
}

int8_t zf_opaque_atomic_load_int8(volatile struct ZFOpaqueAtomicType *object)
{
    return atomic_load((volatile _Atomic(int8_t)*)object);
}

uint8_t zf_opaque_atomic_load_uint8(volatile struct ZFOpaqueAtomicType *object)
{
    return atomic_load((volatile _Atomic(uint8_t)*)object);
}

int16_t zf_opaque_atomic_load_int16(volatile struct ZFOpaqueAtomicType *object)
{
    return atomic_load((volatile _Atomic(int16_t)*)object);
}

uint16_t zf_opaque_atomic_load_uint16(volatile struct ZFOpaqueAtomicType *object)
{
    return atomic_load((volatile _Atomic(uint16_t)*)object);
}

int32_t zf_opaque_atomic_load_int32(volatile struct ZFOpaqueAtomicType *object)
{
    return  atomic_load((volatile _Atomic(int32_t)*)object);
}

uint32_t zf_opaque_atomic_load_uint32(volatile struct ZFOpaqueAtomicType *object)
{
    return atomic_load((volatile _Atomic(uint32_t)*)object);
}

int zf_opaque_atomic_load_int(volatile struct ZFOpaqueAtomicType *object)
{
    return atomic_load((volatile atomic_int*)object);
}

unsigned zf_opaque_atomic_load_uint(volatile struct ZFOpaqueAtomicType *object)
{
    return atomic_load((volatile atomic_uint*)object);
}

intptr_t zf_opaque_atomic_load_intptr(volatile struct ZFOpaqueAtomicType *object)
{
    return atomic_load((volatile atomic_intptr_t*)object);
}

uintptr_t zf_opaque_atomic_load_uintptr(volatile struct ZFOpaqueAtomicType *object)
{
    return atomic_load((volatile atomic_uintptr_t*)object);
}

size_t zf_opaque_atomic_load_size(volatile struct ZFOpaqueAtomicType *object)
{
    return atomic_load((volatile atomic_size_t*)object);
}

ssize_t zf_opaque_atomic_load_ssize(volatile struct ZFOpaqueAtomicType *object)
{
    return atomic_load((volatile _Atomic(ssize_t)*)object);
}

ptrdiff_t zf_opaque_atomic_load_ptrdiff(volatile struct ZFOpaqueAtomicType *object)
{
    return atomic_load((volatile atomic_ptrdiff_t*)object);
}

intmax_t zf_opaque_atomic_load_intmax(volatile struct ZFOpaqueAtomicType *object)
{
    return atomic_load((volatile atomic_intmax_t*)object);
}

uintmax_t zf_opaque_atomic_load_uintmax(volatile struct ZFOpaqueAtomicType *object)
{
    return atomic_load((volatile atomic_uintmax_t*)object);
}

char16_t zf_opaque_atomic_load_char16(volatile struct ZFOpaqueAtomicType *object)
{
    return atomic_load((volatile atomic_char16_t*)object);
}

char32_t zf_opaque_atomic_load_char32(volatile struct ZFOpaqueAtomicType *object)
{
    return atomic_load((volatile atomic_char32_t*)object);
}

wchar_t zf_opaque_atomic_load_wchar(volatile struct ZFOpaqueAtomicType *object)
{
    return atomic_load((volatile atomic_wchar_t*)object);
}

// MARK: atomic store operations

void zf_opaque_atomic_store_bool(volatile struct ZFOpaqueAtomicType *object, bool value)
{
    atomic_store((volatile atomic_bool*)object, value);
}

void zf_opaque_atomic_store_char(volatile struct ZFOpaqueAtomicType *object, char value)
{
    atomic_store((volatile atomic_char*)object, value);
}

void zf_opaque_atomic_store_int8(volatile struct ZFOpaqueAtomicType *object, int8_t value)
{
    atomic_store((volatile _Atomic(int8_t)*)object, value);
}

void zf_opaque_atomic_store_uint8(volatile struct ZFOpaqueAtomicType *object, uint8_t value)
{
    atomic_store((volatile _Atomic(uint8_t)*)object, value);
}

void zf_opaque_atomic_store_int16(volatile struct ZFOpaqueAtomicType *object, int16_t value)
{
    atomic_store((volatile _Atomic(int16_t)*)object, value);
}

void zf_opaque_atomic_store_uint16(volatile struct ZFOpaqueAtomicType *object, uint16_t value)
{
    atomic_store((volatile _Atomic(uint16_t)*)object, value);
}

void zf_opaque_atomic_store_int32(volatile struct ZFOpaqueAtomicType *object, int32_t value)
{
    atomic_store((volatile _Atomic(int32_t)*)object, value);
}

void zf_opaque_atomic_store_uint32(volatile struct ZFOpaqueAtomicType *object, uint32_t value)
{
    atomic_store((volatile _Atomic(uint32_t)*)object, value);
}

void zf_opaque_atomic_store_int(volatile struct ZFOpaqueAtomicType *object, int value)
{
    atomic_store((volatile atomic_int*)object, value);
}

void zf_opaque_atomic_store_uint(volatile struct ZFOpaqueAtomicType *object, unsigned value)
{
    atomic_store((volatile atomic_uint*)object, value);
}

void zf_opaque_atomic_store_intptr(volatile struct ZFOpaqueAtomicType *object, intptr_t value)
{
    atomic_store((volatile atomic_intptr_t*)object, value);
}

void zf_opaque_atomic_store_uintptr(volatile struct ZFOpaqueAtomicType *object, uintptr_t value)
{
    atomic_store((volatile atomic_uintptr_t*)object, value);
}

void zf_opaque_atomic_store_size(volatile struct ZFOpaqueAtomicType *object, size_t value)
{
    atomic_store((volatile atomic_size_t*)object, value);
}

void zf_opaque_atomic_store_ssize(volatile struct ZFOpaqueAtomicType *object, ssize_t value)
{
    atomic_store((volatile _Atomic(ssize_t)*)object, value);
}

void zf_opaque_atomic_store_ptrdiff(volatile struct ZFOpaqueAtomicType *object, ptrdiff_t value)
{
    atomic_store((volatile atomic_ptrdiff_t*)object, value);
}

void zf_opaque_atomic_store_intmax(volatile struct ZFOpaqueAtomicType *object, intmax_t value)
{
    atomic_store((volatile atomic_intmax_t*)object, value);
}

void zf_opaque_atomic_store_uintmax(volatile struct ZFOpaqueAtomicType *object, uintmax_t value)
{
    atomic_store((volatile atomic_uintmax_t*)object, value);
}

void zf_opaque_atomic_store_char16(volatile struct ZFOpaqueAtomicType *object, char16_t value)
{
    atomic_store((volatile atomic_char16_t*)object, value);
}

void zf_opaque_atomic_store_char32(volatile struct ZFOpaqueAtomicType *object, char32_t value)
{
    atomic_store((volatile atomic_char32_t*)object, value);
}

void zf_opaque_atomic_store_wchar(volatile struct ZFOpaqueAtomicType *object, wchar_t value)
{
    atomic_store((volatile atomic_wchar_t*)object, value);
}

// MARK: atomic fetch add operations

char zf_opaque_atomic_fetch_add_char(volatile struct ZFOpaqueAtomicType *object, char value)
{
    return  atomic_fetch_add((volatile atomic_char*)object, value);
}

int8_t zf_opaque_atomic_fetch_add_int8(volatile struct ZFOpaqueAtomicType *object, int8_t value)
{
    return atomic_fetch_add((volatile _Atomic(int8_t)*)object, value);
}

uint8_t zf_opaque_atomic_fetch_add_uint8(volatile struct ZFOpaqueAtomicType *object, uint8_t value)
{
    return atomic_fetch_add((volatile _Atomic(uint8_t)*)object, value);
}

int16_t zf_opaque_atomic_fetch_add_int16(volatile struct ZFOpaqueAtomicType *object, int16_t value)
{
    return atomic_fetch_add((volatile _Atomic(int16_t)*)object, value);
}

uint16_t zf_opaque_atomic_fetch_add_uint16(volatile struct ZFOpaqueAtomicType *object, uint16_t value)
{
    return atomic_fetch_add((volatile _Atomic(uint16_t)*)object, value);
}

int32_t zf_opaque_atomic_fetch_add_int32(volatile struct ZFOpaqueAtomicType *object, int32_t value)
{
    return atomic_fetch_add((volatile _Atomic(int32_t)*)object, value);
}

uint32_t zf_opaque_atomic_fetch_add_uint32(volatile struct ZFOpaqueAtomicType *object, uint32_t value)
{
    return atomic_fetch_add((volatile _Atomic(uint32_t)*)object, value);
}

int zf_opaque_atomic_fetch_add_int(volatile struct ZFOpaqueAtomicType *object, int value)
{
    return atomic_fetch_add((volatile atomic_int*)object, value);
}

unsigned zf_opaque_atomic_fetch_add_uint(volatile struct ZFOpaqueAtomicType *object, unsigned value)
{
    return atomic_fetch_add((volatile atomic_uint*)object, value);
}

intptr_t zf_opaque_atomic_fetch_add_intptr(volatile struct ZFOpaqueAtomicType *object, intptr_t value)
{
    return atomic_fetch_add((volatile atomic_intptr_t*)object, value);
}

uintptr_t zf_opaque_atomic_fetch_add_uintptr(volatile struct ZFOpaqueAtomicType *object, uintptr_t value)
{
    return atomic_fetch_add((volatile atomic_uintptr_t*)object, value);
}

size_t zf_opaque_atomic_fetch_add_size(volatile struct ZFOpaqueAtomicType *object, size_t value)
{
    return atomic_fetch_add((volatile atomic_size_t*)object, value);
}

ssize_t zf_opaque_atomic_fetch_add_ssize(volatile struct ZFOpaqueAtomicType *object, ssize_t value)
{
    return atomic_fetch_add((volatile _Atomic(ssize_t)*)object, value);
}

ptrdiff_t zf_opaque_atomic_fetch_add_ptrdiff(volatile struct ZFOpaqueAtomicType *object, ptrdiff_t value)
{
    return atomic_fetch_add((volatile atomic_ptrdiff_t*)object, value);
}

intmax_t zf_opaque_atomic_fetch_add_intmax(volatile struct ZFOpaqueAtomicType *object, intmax_t value)
{
    return atomic_fetch_add((volatile atomic_intmax_t*)object, value);
}

uintmax_t zf_opaque_atomic_fetch_add_uintmax(volatile struct ZFOpaqueAtomicType *object, intmax_t value)
{
    return atomic_fetch_add((volatile atomic_uintmax_t*)object, value);
}

char16_t zf_opaque_atomic_fetch_add_char16(volatile struct ZFOpaqueAtomicType *object, char16_t value)
{
    return atomic_fetch_add((volatile atomic_char16_t*)object, value);
}

char32_t zf_opaque_atomic_fetch_add_char32(volatile struct ZFOpaqueAtomicType *object, char32_t value)
{
    return atomic_fetch_add((volatile atomic_char32_t*)object, value);
}

wchar_t zf_opaque_atomic_fetch_add_wchar(volatile struct ZFOpaqueAtomicType *object, wchar_t value)
{
    return atomic_fetch_add((volatile atomic_wchar_t*)object, value);
}

// MARK: atomic subtraction operations

char zf_opaque_atomic_fetch_sub_char(volatile struct ZFOpaqueAtomicType *object, char value)
{
    return atomic_fetch_sub((volatile atomic_char*)object, value);
}

int8_t zf_opaque_atomic_fetch_sub_int8(volatile struct ZFOpaqueAtomicType *object, int8_t value)
{
    return atomic_fetch_sub((volatile _Atomic(int8_t)*)object, value);
}

uint8_t zf_opaque_atomic_fetch_sub_uint8(volatile struct ZFOpaqueAtomicType *object, uint8_t value)
{
    return atomic_fetch_sub((volatile _Atomic(uint8_t)*)object, value);
}

int16_t zf_opaque_atomic_fetch_sub_int16(volatile struct ZFOpaqueAtomicType *object, int16_t value)
{
    return atomic_fetch_sub((volatile _Atomic(int16_t)*)object, value);
}

uint16_t zf_opaque_atomic_fetch_sub_uint16(volatile struct ZFOpaqueAtomicType *object, uint16_t value)
{
    return atomic_fetch_sub((volatile _Atomic(uint16_t)*)object, value);
}

int32_t zf_opaque_atomic_fetch_sub_int32(volatile struct ZFOpaqueAtomicType *object, int32_t value)
{
    return atomic_fetch_sub((volatile _Atomic(int32_t)*)object, value);
}

uint32_t zf_opaque_atomic_fetch_sub_uint32(volatile struct ZFOpaqueAtomicType *object, uint32_t value)
{
    return  atomic_fetch_sub((volatile _Atomic(uint32_t)*)object, value);
}

int zf_opaque_atomic_fetch_sub_int(volatile struct ZFOpaqueAtomicType *object, int value)
{
    return atomic_fetch_sub((volatile atomic_int*)object, value);
}

unsigned zf_opaque_atomic_fetch_sub_uint(volatile struct ZFOpaqueAtomicType *object, unsigned value)
{
    return atomic_fetch_sub((volatile atomic_uint*)object, value);
}

intptr_t zf_opaque_atomic_fetch_sub_intptr(volatile struct ZFOpaqueAtomicType *object, intptr_t value)
{
    return atomic_fetch_sub((volatile atomic_intptr_t*)object, value);
}

uintptr_t zf_opaque_atomic_fetch_sub_uintptr(volatile struct ZFOpaqueAtomicType *object, uintptr_t value)
{
    return atomic_fetch_sub((volatile atomic_uintptr_t*)object, value);
}

size_t zf_opaque_atomic_fetch_sub_size(volatile struct ZFOpaqueAtomicType *object, size_t value)
{
    return atomic_fetch_sub((volatile atomic_size_t*)object, value);
}

ssize_t zf_opaque_atomic_fetch_sub_ssize(volatile struct ZFOpaqueAtomicType *object, ssize_t value)
{
    return atomic_fetch_sub((volatile _Atomic(ssize_t)*)object, value);
}

ptrdiff_t zf_opaque_atomic_fetch_sub_ptrdiff(volatile struct ZFOpaqueAtomicType *object, ptrdiff_t value)
{
    return atomic_fetch_sub((volatile atomic_ptrdiff_t*)object, value);
}

intmax_t zf_opaque_atomic_fetch_sub_intmax(volatile struct ZFOpaqueAtomicType *object, intmax_t value)
{
    return atomic_fetch_sub((volatile atomic_intmax_t*)object, value);
}

uintmax_t zf_opaque_atomic_fetch_sub_uintmax(volatile struct ZFOpaqueAtomicType *object, uintmax_t value)
{
    return atomic_fetch_sub((volatile atomic_uintmax_t*)object, value);
}

char16_t zf_opaque_atomic_fetch_sub_char16(volatile struct ZFOpaqueAtomicType *object, char16_t value)
{
    return atomic_fetch_sub((volatile atomic_char16_t*)object, value);
}

char32_t zf_opaque_atomic_fetch_sub_char32(volatile struct ZFOpaqueAtomicType *object, char32_t value)
{
    return atomic_fetch_sub((volatile atomic_char32_t*)object, value);
}

wchar_t zf_opaque_atomic_fetch_sub_wchar(volatile struct ZFOpaqueAtomicType *object, wchar_t value)
{
    return atomic_fetch_sub((volatile atomic_wchar_t*)object, value);
}


