//
//  zf_atomic_opaque.h
//  試合
//
//  Created by Zenny Chen on 2019/9/11.
//  Copyright © 2019 Zenny Chen. All rights reserved.
//

#ifndef zf_atomic_opaque_h
#define zf_atomic_opaque_h

#include "zf_sys.h"
#include "zf_uchar.h"
#include "zf_atomic.h"

/// An opaque atomic type for the environment
/// that does not support C11 atomic operations directly
///
/// You can easily initialize the opaque atomic type object
/// by directly write the initial value to values[0].
/// values[1] is for the lock if atomic fetch arithmetic operations,
/// CAS operations, or LL-SC operations do not support.
/// For example:
///
/// volatile struct ZFOpaqueAtomicType atomInt = { 0 };
struct ZFOpaqueAtomicType
{
    /// The memory buffer that stores the atomic object
    /// and the relevant lock if necessary
    intmax_t values[2];
};

// MARK: atomic flag operations

/// Atomic flag test and set
/// @param object pointer to the opaque atomic object
extern bool zf_opaque_atomic_flag_test_and_set(volatile struct ZFOpaqueAtomicType *object);

/// Atomic flag clear
/// @param object pointer to the opaque atomic object
extern void zf_opaque_atomic_flag_clear(volatile struct ZFOpaqueAtomicType *object);

// MARK: atomic load operations

/// Atomically load the boolean value in the opaque atomic object
/// @param object pointer to the opaque atomic object
/// @return the boolean value
extern bool zf_opaque_atomic_load_bool(volatile struct ZFOpaqueAtomicType *object);

/// Atomically load the char value in the opaque atomic object
/// @param object pointer to the opaque atomic object
/// @return the char value
extern char zf_opaque_atomic_load_char(volatile struct ZFOpaqueAtomicType *object);

/// Atomically load the int8_t value in the opaque atomic object
/// @param object pointer to the opaque atomic object
/// @return the int8_t value
extern int8_t zf_opaque_atomic_load_int8(volatile struct ZFOpaqueAtomicType *object);

/// Atomically load the uint8_t value in the opaque atomic object
/// @param object pointer to the opaque atomic object
/// @return the unsigned char value
extern uint8_t zf_opaque_atomic_load_uint8(volatile struct ZFOpaqueAtomicType *object);
 
/// Atomically load the int16_t value in the opaque atomic object
/// @param object pointer to the opaque atomic object
/// @return the int16_t value
extern int16_t zf_opaque_atomic_load_int16(volatile struct ZFOpaqueAtomicType *object);

/// Atomically load the uint16_t value in the opaque atomic object
/// @param object pointer to the opaque atomic object
/// @return the uint16_t value
extern uint16_t zf_opaque_atomic_load_uint16(volatile struct ZFOpaqueAtomicType *object);

/// Atomically load the int32_t value in the opaque atomic object
/// @param object pointer to the opaque atomic object
/// @return the int32_t value
extern int32_t zf_opaque_atomic_load_int32(volatile struct ZFOpaqueAtomicType *object);

/// Atomically load the uint32_t value in the opaque atomic object
/// @param object pointer to the opaque atomic object
/// @return the uint32_t value
extern uint32_t zf_opaque_atomic_load_uint32(volatile struct ZFOpaqueAtomicType *object);

/// Atomically load the int value in the opaque atomic object
/// @param object pointer to the opaque atomic object
/// @return the int value
extern int zf_opaque_atomic_load_int(volatile struct ZFOpaqueAtomicType *object);

/// Atomically load the unsigned int value in the opaque atomic object
/// @param object pointer to the opaque atomic object
/// @return the unsigned int value
extern unsigned zf_opaque_atomic_load_uint(volatile struct ZFOpaqueAtomicType *object);

/// Atomically load the intptr_t value in the opaque atomic object
/// @param object pointer to the opaque atomic object
/// @return the intptr_t value
extern intptr_t zf_opaque_atomic_load_intptr(volatile struct ZFOpaqueAtomicType *object);

/// Atomically load the uintptr_t value in the opaque atomic object
/// @param object pointer to the opaque atomic object
/// @return the uintptr_t value
extern uintptr_t zf_opaque_atomic_load_uintptr(volatile struct ZFOpaqueAtomicType *object);

/// Atomically load the size_t value in the opaque atomic object
/// @param object pointer to the opaque atomic object
/// @return the size_t value
extern size_t zf_opaque_atomic_load_size(volatile struct ZFOpaqueAtomicType *object);

/// Atomically load the ssize_t value in the opaque atomic object
/// @param object pointer to the opaque atomic object
/// @return the ssize_t value
extern ssize_t zf_opaque_atomic_load_ssize(volatile struct ZFOpaqueAtomicType *object);

/// Atomically load the ptrdiff_t value in the opaque atomic object
/// @param object pointer to the opaque atomic object
/// @return the ptrdiff_t value
extern ptrdiff_t zf_opaque_atomic_load_ptrdiff(volatile struct ZFOpaqueAtomicType *object);

/// Atomically load the intmax_t value in the opaque atomic object
/// @param object pointer to the opaque atomic object
/// @return the intmax_t value
extern intmax_t zf_opaque_atomic_load_intmax(volatile struct ZFOpaqueAtomicType *object);

/// Atomically load the uintmax_t value in the opaque atomic object
/// @param object pointer to the opaque atomic object
/// @return the uintmax_t value
extern uintmax_t zf_opaque_atomic_load_uintmax(volatile struct ZFOpaqueAtomicType *object);

/// Atomically load the char16_t value in the opaque atomic object
/// @param object pointer to the opaque atomic object
/// @return the char16_t value
extern char16_t zf_opaque_atomic_load_char16(volatile struct ZFOpaqueAtomicType *object);

/// Atomically load the char32_t value in the opaque atomic object
/// @param object pointer to the opaque atomic object
/// @return the char32_t value
extern char32_t zf_opaque_atomic_load_char32(volatile struct ZFOpaqueAtomicType *object);

/// Atomically load the wchar_t value in the opaque atomic object
/// @param object pointer to the opaque atomic object
/// @return the wchar_t value
extern wchar_t zf_opaque_atomic_load_wchar(volatile struct ZFOpaqueAtomicType *object);

// MARK: atomic store operations

/// Atomically store the specified boolean value to the opaque atomic object
/// @param object pointer to the opaque atomic object
/// @param value the boolean value that'll be stored
extern void zf_opaque_atomic_store_bool(volatile struct ZFOpaqueAtomicType *object, bool value);

/// Atomically store the specified char value to the opaque atomic object
/// @param object pointer to the opaque atomic object
/// @param value the char value that'll be stored
extern void zf_opaque_atomic_store_char(volatile struct ZFOpaqueAtomicType *object, char value);

/// Atomically store the specified int8_t value to the opaque atomic object
/// @param object pointer to the opaque atomic object
/// @param value the int8_t value that'll be stored
extern void zf_opaque_atomic_store_int8(volatile struct ZFOpaqueAtomicType *object, int8_t value);

/// Atomically store the specified uint8_t value to the opaque atomic object
/// @param object pointer to the opaque atomic object
/// @param value the uint8_t value that'll be stored
extern void zf_opaque_atomic_store_uint8(volatile struct ZFOpaqueAtomicType *object, uint8_t value);

/// Atomically store the specified int16_t value to the opaque atomic object
/// @param object pointer to the opaque atomic object
/// @param value the int16_t value that'll be stored
extern void zf_opaque_atomic_store_int16(volatile struct ZFOpaqueAtomicType *object, int16_t value);

/// Atomically store the specified uint16_t value to the opaque atomic object
/// @param object pointer to the opaque atomic object
/// @param value the uint16_t value that'll be stored
extern void zf_opaque_atomic_store_uint16(volatile struct ZFOpaqueAtomicType *object, uint16_t value);

/// Atomically store the specified int32_t value to the opaque atomic object
/// @param object pointer to the opaque atomic object
/// @param value the int32_t value that'll be stored
extern void zf_opaque_atomic_store_int32(volatile struct ZFOpaqueAtomicType *object, int32_t value);

/// Atomically store the specified uint32_t value to the opaque atomic object
/// @param object pointer to the opaque atomic object
/// @param value the uint32_t value that'll be stored
extern void zf_opaque_atomic_store_uint32(volatile struct ZFOpaqueAtomicType *object, uint32_t value);

/// Atomically store the specified int value to the opaque atomic object
/// @param object pointer to the opaque atomic object
/// @param value the int value that'll be stored
extern void zf_opaque_atomic_store_int(volatile struct ZFOpaqueAtomicType *object, int value);

/// Atomically store the specified unsigned int value to the opaque atomic object
/// @param object pointer to the opaque atomic object
/// @param value the unsigned int value that'll be stored
extern void zf_opaque_atomic_store_uint(volatile struct ZFOpaqueAtomicType *object, unsigned value);

/// Atomically store the specified intptr_t value to the opaque atomic object
/// @param object pointer to the opaque atomic object
/// @param value the intptr_t value that'll be stored
extern void zf_opaque_atomic_store_intptr(volatile struct ZFOpaqueAtomicType *object, intptr_t value);

/// Atomically store the specified uintptr_t value to the opaque atomic object
/// @param object pointer to the opaque atomic object
/// @param value the uintptr_t value that'll be stored
extern void zf_opaque_atomic_store_uintptr(volatile struct ZFOpaqueAtomicType *object, uintptr_t value);

/// Atomically store the specified size_t value to the opaque atomic object
/// @param object pointer to the opaque atomic object
/// @param value the size_t value that'll be stored
extern void zf_opaque_atomic_store_size(volatile struct ZFOpaqueAtomicType *object, size_t value);

/// Atomically store the specified ssize_t value to the opaque atomic object
/// @param object pointer to the opaque atomic object
/// @param value the ssize_t value that'll be stored
extern void zf_opaque_atomic_store_ssize(volatile struct ZFOpaqueAtomicType *object, ssize_t value);

/// Atomically store the specified ptrdiff_t value to the opaque atomic object
/// @param object pointer to the opaque atomic object
/// @param value the ptrdiff_t value that'll be stored
extern void zf_opaque_atomic_store_ptrdiff(volatile struct ZFOpaqueAtomicType *object, ptrdiff_t value);

/// Atomically store the specified intmax_t value to the opaque atomic object
/// @param object pointer to the opaque atomic object
/// @param value the intmax_t value that'll be stored
extern void zf_opaque_atomic_store_intmax(volatile struct ZFOpaqueAtomicType *object, intmax_t value);

/// Atomically store the specified uintmax_t value to the opaque atomic object
/// @param object pointer to the opaque atomic object
/// @param value the uintmax_t value that'll be stored
extern void zf_opaque_atomic_store_uintmax(volatile struct ZFOpaqueAtomicType *object, uintmax_t value);

/// Atomically store the specified char16_t value to the opaque atomic object
/// @param object pointer to the opaque atomic object
/// @param value the char16_t value that'll be stored
extern void zf_opaque_atomic_store_char16(volatile struct ZFOpaqueAtomicType *object, char16_t value);

/// Atomically store the specified char32_t value to the opaque atomic object
/// @param object pointer to the opaque atomic object
/// @param value the char32_t value that'll be stored
extern void zf_opaque_atomic_store_char32(volatile struct ZFOpaqueAtomicType *object, char32_t value);

/// Atomically store the specified wchar_t value to the opaque atomic object
/// @param object pointer to the opaque atomic object
/// @param value the wchar_t value that'll be stored
extern void zf_opaque_atomic_store_wchar(volatile struct ZFOpaqueAtomicType *object, wchar_t value);

// MARK: atomic fetch add operations

/// Atomically add the char value in the opaque atomic object and the specified value,
/// and store the result to the atomic object.
/// @param object pointer to the opaque atomic object
/// @param value the addend
/// @return the original value stored in the opaque atomic object before this operation
extern char zf_opaque_atomic_fetch_add_char(volatile struct ZFOpaqueAtomicType *object, char value);

/// Atomically add the int8_t value in the opaque atomic object and the specified value,
/// and store the result to the atomic object.
/// @param object pointer to the opaque atomic object
/// @param value the addend
/// @return the original value stored in the opaque atomic object before this operation
extern int8_t zf_opaque_atomic_fetch_add_int8(volatile struct ZFOpaqueAtomicType *object, int8_t value);

/// Atomically add the uint8_t value in the opaque atomic object and the specified value,
/// and store the result to the atomic object.
/// @param object pointer to the opaque atomic object
/// @param value the addend
/// @return the original value stored in the opaque atomic object before this operation
extern uint8_t zf_opaque_atomic_fetch_add_uint8(volatile struct ZFOpaqueAtomicType *object, uint8_t value);

/// Atomically add the int16_t value in the opaque atomic object and the specified value,
/// and store the result to the atomic object.
/// @param object pointer to the opaque atomic object
/// @param value the addend
/// @return the original value stored in the opaque atomic object before this operation
extern int16_t zf_opaque_atomic_fetch_add_int16(volatile struct ZFOpaqueAtomicType *object, int16_t value);

/// Atomically add the uint16_t value in the opaque atomic object and the specified value,
/// and store the result to the atomic object.
/// @param object pointer to the opaque atomic object
/// @param value the addend
/// @return the original value stored in the opaque atomic object before this operation
extern uint16_t zf_opaque_atomic_fetch_add_uint16(volatile struct ZFOpaqueAtomicType *object, uint16_t value);

/// Atomically add the int32_t value in the opaque atomic object and the specified value,
/// and store the result to the atomic object.
/// @param object pointer to the opaque atomic object
/// @param value the addend
/// @return the original value stored in the opaque atomic object before this operation
extern int32_t zf_opaque_atomic_fetch_add_int32(volatile struct ZFOpaqueAtomicType *object, int32_t value);

/// Atomically add the uint32_t value in the opaque atomic object and the specified value,
/// and store the result to the atomic object.
/// @param object pointer to the opaque atomic object
/// @param value the addend
/// @return the original value stored in the opaque atomic object before this operation
extern uint32_t zf_opaque_atomic_fetch_add_uint32(volatile struct ZFOpaqueAtomicType *object, uint32_t value);

/// Atomically add the int value in the opaque atomic object and the specified value,
/// and store the result to the atomic object.
/// @param object pointer to the opaque atomic object
/// @param value the addend
/// @return the original value stored in the opaque atomic object before this operation
extern int zf_opaque_atomic_fetch_add_int(volatile struct ZFOpaqueAtomicType *object, int value);

/// Atomically add the int value unsigned in the opaque atomic object and the specified value,
/// and store the result to the atomic object.
/// @param object pointer to the opaque atomic object
/// @param value the addend
/// @return the original value stored in the opaque atomic object before this operation
extern unsigned zf_opaque_atomic_fetch_add_uint(volatile struct ZFOpaqueAtomicType *object, unsigned value);

/// Atomically add the intptr_t value in the opaque atomic object and the specified value,
/// and store the result to the atomic object.
/// @param object pointer to the opaque atomic object
/// @param value the addend
/// @return the original value stored in the opaque atomic object before this operation
extern intptr_t zf_opaque_atomic_fetch_add_intptr(volatile struct ZFOpaqueAtomicType *object, intptr_t value);

/// Atomically add the uintptr_t value in the opaque atomic object and the specified value,
/// and store the result to the atomic object.
/// @param object pointer to the opaque atomic object
/// @param value the addend
/// @return the original value stored in the opaque atomic object before this operation
extern uintptr_t zf_opaque_atomic_fetch_add_uintptr(volatile struct ZFOpaqueAtomicType *object, uintptr_t value);

/// Atomically add the size_t value in the opaque atomic object and the specified value,
/// and store the result to the atomic object.
/// @param object pointer to the opaque atomic object
/// @param value the addend
/// @return the original value stored in the opaque atomic object before this operation
extern size_t zf_opaque_atomic_fetch_add_size(volatile struct ZFOpaqueAtomicType *object, size_t value);

/// Atomically add the ssize_t value in the opaque atomic object and the specified value,
/// and store the result to the atomic object.
/// @param object pointer to the opaque atomic object
/// @param value the addend
/// @return the original value stored in the opaque atomic object before this operation
extern ssize_t zf_opaque_atomic_fetch_add_ssize(volatile struct ZFOpaqueAtomicType *object, ssize_t value);

/// Atomically add the ptrdiff_t value in the opaque atomic object and the specified value,
/// and store the result to the atomic object.
/// @param object pointer to the opaque atomic object
/// @param value the addend
/// @return the original value stored in the opaque atomic object before this operation
extern ptrdiff_t zf_opaque_atomic_fetch_add_ptrdiff(volatile struct ZFOpaqueAtomicType *object, ptrdiff_t value);

/// Atomically add the intmax_t value in the opaque atomic object and the specified value,
/// and store the result to the atomic object.
/// @param object pointer to the opaque atomic object
/// @param value the addend
/// @return the original value stored in the opaque atomic object before this operation
extern intmax_t zf_opaque_atomic_fetch_add_intmax(volatile struct ZFOpaqueAtomicType *object, intmax_t value);

/// Atomically add the intmax_t value in the opaque atomic object and the specified value,
/// and store the result to the atomic object.
/// @param object pointer to the opaque atomic object
/// @param value the addend
/// @return the original value stored in the opaque atomic object before this operation
extern uintmax_t zf_opaque_atomic_fetch_add_uintmax(volatile struct ZFOpaqueAtomicType *object, intmax_t value);

/// Atomically add the char16_t value in the opaque atomic object and the specified value,
/// and store the result to the atomic object.
/// @param object pointer to the opaque atomic object
/// @param value the addend
/// @return the original value stored in the opaque atomic object before this operation
extern char16_t zf_opaque_atomic_fetch_add_char16(volatile struct ZFOpaqueAtomicType *object, char16_t value);

/// Atomically add the char32_t value in the opaque atomic object and the specified value,
/// and store the result to the atomic object.
/// @param object pointer to the opaque atomic object
/// @param value the addend
/// @return the original value stored in the opaque atomic object before this operation
extern char32_t zf_opaque_atomic_fetch_add_char32(volatile struct ZFOpaqueAtomicType *object, char32_t value);

/// Atomically add the wchar_t value in the opaque atomic object and the specified value,
/// and store the result to the atomic object.
/// @param object pointer to the opaque atomic object
/// @param value the addend
/// @return the original value stored in the opaque atomic object before this operation
extern wchar_t zf_opaque_atomic_fetch_add_wchar(volatile struct ZFOpaqueAtomicType *object, wchar_t value);

// MARK: atomic fetch subtraction operations

/// Atomically subtract the specified value from the char value in the opaque atomic object,
/// and store the result to the atomic object.
/// @param object pointer to the opaque atomic object
/// @param value the subtrahend
/// @return the original value stored in the opaque atomic object before this operation
extern char zf_opaque_atomic_fetch_sub_char(volatile struct ZFOpaqueAtomicType *object, char value);

/// Atomically subtract the specified value from the int8_t value in the opaque atomic object,
/// and store the result to the atomic object.
/// @param object pointer to the opaque atomic object
/// @param value the subtrahend
/// @return the original value stored in the opaque atomic object before this operation
extern int8_t zf_opaque_atomic_fetch_sub_int8(volatile struct ZFOpaqueAtomicType *object, int8_t value);

/// Atomically subtract the specified value from the uint8_t value in the opaque atomic object,
/// and store the result to the atomic object.
/// @param object pointer to the opaque atomic object
/// @param value the subtrahend
/// @return the original value stored in the opaque atomic object before this operation
extern uint8_t zf_opaque_atomic_fetch_sub_uint8(volatile struct ZFOpaqueAtomicType *object, uint8_t value);

/// Atomically subtract the specified value from the int16_t value in the opaque atomic object,
/// and store the result to the atomic object.
/// @param object pointer to the opaque atomic object
/// @param value the subtrahend
/// @return the original value stored in the opaque atomic object before this operation
extern int16_t zf_opaque_atomic_fetch_sub_int16(volatile struct ZFOpaqueAtomicType *object, int16_t value);

/// Atomically subtract the specified value from the uint16_t value in the opaque atomic object,
/// and store the result to the atomic object.
/// @param object pointer to the opaque atomic object
/// @param value the subtrahend
/// @return the original value stored in the opaque atomic object before this operation
extern uint16_t zf_opaque_atomic_fetch_sub_uint16(volatile struct ZFOpaqueAtomicType *object, uint16_t value);

/// Atomically subtract the specified value from the int32_t value in the opaque atomic object,
/// and store the result to the atomic object.
/// @param object pointer to the opaque atomic object
/// @param value the subtrahend
/// @return the original value stored in the opaque atomic object before this operation
extern int32_t zf_opaque_atomic_fetch_sub_int32(volatile struct ZFOpaqueAtomicType *object, int32_t value);

/// Atomically subtract the specified value from the uint32_t value in the opaque atomic object,
/// and store the result to the atomic object.
/// @param object pointer to the opaque atomic object
/// @param value the subtrahend
/// @return the original value stored in the opaque atomic object before this operation
extern uint32_t zf_opaque_atomic_fetch_sub_uint32(volatile struct ZFOpaqueAtomicType *object, uint32_t value);

/// Atomically subtract the specified value from the int value in the opaque atomic object,
/// and store the result to the atomic object.
/// @param object pointer to the opaque atomic object
/// @param value the subtrahend
/// @return the original value stored in the opaque atomic object before this operation
extern int zf_opaque_atomic_fetch_sub_int(volatile struct ZFOpaqueAtomicType *object, int value);

/// Atomically subtract the specified value from the unsigned int value in the opaque atomic object,
/// and store the result to the atomic object.
/// @param object pointer to the opaque atomic object
/// @param value the subtrahend
/// @return the original value stored in the opaque atomic object before this operation
extern unsigned zf_opaque_atomic_fetch_sub_uint(volatile struct ZFOpaqueAtomicType *object, unsigned value);

/// Atomically subtract the specified value from the intptr_t value in the opaque atomic object,
/// and store the result to the atomic object.
/// @param object pointer to the opaque atomic object
/// @param value the subtrahend
/// @return the original value stored in the opaque atomic object before this operation
extern intptr_t zf_opaque_atomic_fetch_sub_intptr(volatile struct ZFOpaqueAtomicType *object, intptr_t value);

/// Atomically subtract the specified value from the uintptr_t value in the opaque atomic object,
/// and store the result to the atomic object.
/// @param object pointer to the opaque atomic object
/// @param value the subtrahend
/// @return the original value stored in the opaque atomic object before this operation
extern uintptr_t zf_opaque_atomic_fetch_sub_uintptr(volatile struct ZFOpaqueAtomicType *object, uintptr_t value);

/// Atomically subtract the specified value from the size_t value in the opaque atomic object,
/// and store the result to the atomic object.
/// @param object pointer to the opaque atomic object
/// @param value the subtrahend
/// @return the original value stored in the opaque atomic object before this operation
extern size_t zf_opaque_atomic_fetch_sub_size(volatile struct ZFOpaqueAtomicType *object, size_t value);

/// Atomically subtract the specified value from the size_t value in the opaque atomic object,
/// and store the result to the atomic object.
/// @param object pointer to the opaque atomic object
/// @param value the subtrahend
/// @return the original value stored in the opaque atomic object before this operation
extern ssize_t zf_opaque_atomic_fetch_sub_ssize(volatile struct ZFOpaqueAtomicType *object, ssize_t value);

/// Atomically subtract the specified value from the ptrdiff_t value in the opaque atomic object,
/// and store the result to the atomic object.
/// @param object pointer to the opaque atomic object
/// @param value the subtrahend
/// @return the original value stored in the opaque atomic object before this operation
extern ptrdiff_t zf_opaque_atomic_fetch_sub_ptrdiff(volatile struct ZFOpaqueAtomicType *object, ptrdiff_t value);

/// Atomically subtract the specified value from the intmax_t value in the opaque atomic object,
/// and store the result to the atomic object.
/// @param object pointer to the opaque atomic object
/// @param value the subtrahend
/// @return the original value stored in the opaque atomic object before this operation
extern intmax_t zf_opaque_atomic_fetch_sub_intmax(volatile struct ZFOpaqueAtomicType *object, intmax_t value);

/// Atomically subtract the specified value from the uintmax_t value in the opaque atomic object,
/// and store the result to the atomic object.
/// @param object pointer to the opaque atomic object
/// @param value the subtrahend
/// @return the original value stored in the opaque atomic object before this operation
extern uintmax_t zf_opaque_atomic_fetch_sub_uintmax(volatile struct ZFOpaqueAtomicType *object, uintmax_t value);

/// Atomically subtract the specified value from the char16_t value in the opaque atomic object,
/// and store the result to the atomic object.
/// @param object pointer to the opaque atomic object
/// @param value the subtrahend
/// @return the original value stored in the opaque atomic object before this operation
extern char16_t zf_opaque_atomic_fetch_sub_char16(volatile struct ZFOpaqueAtomicType *object, char16_t value);

/// Atomically subtract the specified value from the char32_t value in the opaque atomic object,
/// and store the result to the atomic object.
/// @param object pointer to the opaque atomic object
/// @param value the subtrahend
/// @return the original value stored in the opaque atomic object before this operation
extern char32_t zf_opaque_atomic_fetch_sub_char32(volatile struct ZFOpaqueAtomicType *object, char32_t value);

/// Atomically subtract the specified value from the wchar_t value in the opaque atomic object,
/// and store the result to the atomic object.
/// @param object pointer to the opaque atomic object
/// @param value the subtrahend
/// @return the original value stored in the opaque atomic object before this operation
extern wchar_t zf_opaque_atomic_fetch_sub_wchar(volatile struct ZFOpaqueAtomicType *object, wchar_t value);

#endif /* zf_atomic_opaque_h */

