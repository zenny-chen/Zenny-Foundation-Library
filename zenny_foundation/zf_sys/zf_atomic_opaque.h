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

/// Atomically load the 1-byte integer value in the opaque atomic object
/// @param object pointer to the opaque atomic object
/// @return the boolean value
extern int8_t zf_opaque_atomic_load_byte(volatile struct ZFOpaqueAtomicType *object);

/// Atomically load the 2-byte integer value in the opaque atomic object
/// @param object pointer to the opaque atomic object
/// @return the boolean value
extern int16_t zf_opaque_atomic_load_short(volatile struct ZFOpaqueAtomicType *object);

/// Atomically load the 4-byte integer value in the opaque atomic object
/// @param object pointer to the opaque atomic object
/// @return the boolean value
extern int32_t zf_opaque_atomic_load_int(volatile struct ZFOpaqueAtomicType *object);

/// Atomically load the 8-byte integer value in the opaque atomic object
/// @param object pointer to the opaque atomic object
/// @return the boolean value
extern int64_t zf_opaque_atomic_load_long(volatile struct ZFOpaqueAtomicType *object);

#define zf_opaque_atomic_load(object, pValue)   if((object) != NULL && (pValue) != NULL) { \
        switch(sizeof(*(pValue))) {                                         \
        case 1:             \
            *(int8_t*)(pValue) = zf_opaque_atomic_load_byte(object);        \
            break;          \
        case 2:             \
            *(int16_t*)(pValue) = zf_opaque_atomic_load_short(object);      \
            break;          \
        case 4:             \
        default:            \
            *(int32_t*)(pValue) = zf_opaque_atomic_load_int(object);        \
            break;          \
        case 8:             \
            *(int64_t*)(pValue) = zf_opaque_atomic_load_long(object);       \
            break;          \
        }                   \
    }                       \
    else

// MARK: atomic store operations

/// Atomically store the specified boolean value to the opaque atomic object
/// @param object pointer to the opaque atomic object
/// @param value the boolean value that'll be stored
extern void zf_opaque_atomic_store_bool(volatile struct ZFOpaqueAtomicType *object, bool value);

/// Atomically store the specified 1-byte value to the opaque atomic object
/// @param object pointer to the opaque atomic object
/// @param value the 1-byte value that'll be stored
extern void zf_opaque_atomic_store_byte(volatile struct ZFOpaqueAtomicType *object, int8_t value);

/// Atomically store the specified 2-byte value to the opaque atomic object
/// @param object pointer to the opaque atomic object
/// @param value the 2-byte value that'll be stored
extern void zf_opaque_atomic_store_short(volatile struct ZFOpaqueAtomicType *object, int16_t value);

/// Atomically store the specified 4-byte value to the opaque atomic object
/// @param object pointer to the opaque atomic object
/// @param value the 4-byte value that'll be stored
extern void zf_opaque_atomic_store_int(volatile struct ZFOpaqueAtomicType *object, int32_t value);

/// Atomically store the specified 8-byte value to the opaque atomic object
/// @param object pointer to the opaque atomic object
/// @param value the 8-byte value that'll be stored
extern void zf_opaque_atomic_store_long(volatile struct ZFOpaqueAtomicType *object, int64_t value);

#define zf_opaque_atomic_store(object, value)   if((object) != NULL) {  \
        switch(sizeof(value)) {     \
        case 1:                     \
            zf_opaque_atomic_store_byte((object), (int8_t)value);       \
            break;                  \
        case 2:                     \
            zf_opaque_atomic_store_short((object), (int16_t)value);     \
            break;                  \
        case 4:                     \
        default:                    \
            zf_opaque_atomic_store_int((object), (int32_t)value);       \
            break;                  \
        case 8:                     \
            zf_opaque_atomic_store_long((object), (int64_t)value);      \
            break;                  \
        }                           \
    }                               \
    else

// MARK: atomic fetch add operations

/// Atomically add the 1-byte value in the opaque atomic object and the specified value,
/// and store the result to the atomic object.
/// @param object pointer to the opaque atomic object
/// @param value the addend
/// @return the original value stored in the opaque atomic object before this operation
extern int8_t zf_opaque_atomic_fetch_add_byte(volatile struct ZFOpaqueAtomicType *object, int8_t value);

/// Atomically add the 2-byte value in the opaque atomic object and the specified value,
/// and store the result to the atomic object.
/// @param object pointer to the opaque atomic object
/// @param value the addend
/// @return the original value stored in the opaque atomic object before this operation
extern int16_t zf_opaque_atomic_fetch_add_short(volatile struct ZFOpaqueAtomicType *object, int16_t value);

/// Atomically add the 4-byte value in the opaque atomic object and the specified value,
/// and store the result to the atomic object.
/// @param object pointer to the opaque atomic object
/// @param value the addend
/// @return the original value stored in the opaque atomic object before this operation
extern int32_t zf_opaque_atomic_fetch_add_int(volatile struct ZFOpaqueAtomicType *object, int32_t value);

/// Atomically add the 8-byte value in the opaque atomic object and the specified value,
/// and store the result to the atomic object.
/// @param object pointer to the opaque atomic object
/// @param value the addend
/// @return the original value stored in the opaque atomic object before this operation
extern int64_t zf_opaque_atomic_fetch_add_long(volatile struct ZFOpaqueAtomicType *object, int64_t value);

#define zf_opaque_atomic_fetch_add(object, value)   type_cast(value)  \
    (   sizeof(value) == 1 ? zf_opaque_atomic_fetch_add_byte((object), (int8_t)(value)) : \
        (sizeof(value) == 2 ? zf_opaque_atomic_fetch_add_short((object), (int16_t)(value)) : \
        (sizeof(value) == 4 ? zf_opaque_atomic_fetch_add_int((object), (int32_t)(value)) : \
        (sizeof(value) == 8 ? zf_opaque_atomic_fetch_add_long((object), (int64_t)(value)) : \
        zf_opaque_atomic_fetch_add_int((object), (int32_t)(value)) ) ) )       \
    )

// MARK: atomic fetch subtraction operations

/// Atomically subtract the specified value from the 1-byte value in the opaque atomic object,
/// and store the result to the atomic object.
/// @param object pointer to the opaque atomic object
/// @param value the subtrahend
/// @return the original value stored in the opaque atomic object before this operation
extern int8_t zf_opaque_atomic_fetch_sub_byte(volatile struct ZFOpaqueAtomicType *object, int8_t value);

/// Atomically subtract the specified value from the 2-byte value in the opaque atomic object,
/// and store the result to the atomic object.
/// @param object pointer to the opaque atomic object
/// @param value the subtrahend
/// @return the original value stored in the opaque atomic object before this operation
extern int16_t zf_opaque_atomic_fetch_sub_short(volatile struct ZFOpaqueAtomicType *object, int16_t value);

/// Atomically subtract the specified value from the 4-byte value in the opaque atomic object,
/// and store the result to the atomic object.
/// @param object pointer to the opaque atomic object
/// @param value the subtrahend
/// @return the original value stored in the opaque atomic object before this operation
extern int32_t zf_opaque_atomic_fetch_sub_int(volatile struct ZFOpaqueAtomicType *object, int32_t value);

/// Atomically subtract the specified value from the 4-byte value in the opaque atomic object,
/// and store the result to the atomic object.
/// @param object pointer to the opaque atomic object
/// @param value the subtrahend
/// @return the original value stored in the opaque atomic object before this operation
extern int64_t zf_opaque_atomic_fetch_sub_long(volatile struct ZFOpaqueAtomicType *object, int64_t value);

#define zf_opaque_atomic_fetch_sub(object, value)   type_cast(value)    \
    (   sizeof(value) == 1 ? zf_opaque_atomic_fetch_sub_byte((object), (int8_t)(value)) : \
        (sizeof(value) == 2 ? zf_opaque_atomic_fetch_sub_short((object), (int16_t)(value)) : \
        (sizeof(value) == 4 ? zf_opaque_atomic_fetch_sub_int((object), (int32_t)(value)) : \
        (sizeof(value) == 8 ? zf_opaque_atomic_fetch_sub_long((object), (int64_t)(value)) : \
        zf_opaque_atomic_fetch_sub_int((object), (int32_t)(value)) ) ) )       \
    )

// MARK: atomic fetch or operations

/// Atomically bitwise OR the the 1-byte value in the opaque atomic object with the specified value,
/// and store the result to the atomic object.
/// @param object pointer to the opaque atomic object
/// @param value the operand
/// @return the original value stored in the opaque atomic object before this operation
extern int8_t zf_opaque_atomic_fetch_or_byte(volatile struct ZFOpaqueAtomicType *object, int8_t value);

/// Atomically bitwise OR the the 2-byte value in the opaque atomic object with the specified value,
/// and store the result to the atomic object.
/// @param object pointer to the opaque atomic object
/// @param value the operand
/// @return the original value stored in the opaque atomic object before this operation
extern int16_t zf_opaque_atomic_fetch_or_short(volatile struct ZFOpaqueAtomicType *object, int16_t value);

/// Atomically bitwise OR the the 4-byte value in the opaque atomic object with the specified value,
/// and store the result to the atomic object.
/// @param object pointer to the opaque atomic object
/// @param value the operand
/// @return the original value stored in the opaque atomic object before this operation
extern int32_t zf_opaque_atomic_fetch_or_int(volatile struct ZFOpaqueAtomicType *object, int32_t value);

/// Atomically bitwise OR the the 8-byte value in the opaque atomic object with the specified value,
/// and store the result to the atomic object.
/// @param object pointer to the opaque atomic object
/// @param value the operand
/// @return the original value stored in the opaque atomic object before this operation
extern int64_t zf_opaque_atomic_fetch_or_long(volatile struct ZFOpaqueAtomicType *object, int64_t value);

#define zf_opaque_atomic_fetch_or(object, value)   type_cast(value)     \
        (   sizeof(value) == 1 ? zf_opaque_atomic_fetch_or_byte((object), (int8_t)(value)) : \
            (sizeof(value) == 2 ? zf_opaque_atomic_fetch_or_short((object), (int16_t)(value)) : \
            (sizeof(value) == 4 ? zf_opaque_atomic_fetch_or_int((object), (int32_t)(value)) : \
            (sizeof(value) == 8 ? zf_opaque_atomic_fetch_or_long((object), (int64_t)(value)) : \
            zf_opaque_atomic_fetch_or_int((object), (int32_t)(value)) ) ) )       \
        )

// MARK: atomic fetch xor operations

/// Atomically bitwise XOR the the 1-byte value in the opaque atomic object with the specified value,
/// and store the result to the atomic object.
/// @param object pointer to the opaque atomic object
/// @param value the operand
/// @return the original value stored in the opaque atomic object before this operation
extern int8_t zf_opaque_atomic_fetch_xor_byte(volatile struct ZFOpaqueAtomicType *object, int8_t value);

/// Atomically bitwise XOR the the 2-byte value in the opaque atomic object with the specified value,
/// and store the result to the atomic object.
/// @param object pointer to the opaque atomic object
/// @param value the operand
/// @return the original value stored in the opaque atomic object before this operation
extern int16_t zf_opaque_atomic_fetch_xor_short(volatile struct ZFOpaqueAtomicType *object, int16_t value);

/// Atomically bitwise XOR the the 4-byte value in the opaque atomic object with the specified value,
/// and store the result to the atomic object.
/// @param object pointer to the opaque atomic object
/// @param value the operand
/// @return the original value stored in the opaque atomic object before this operation
extern int32_t zf_opaque_atomic_fetch_xor_int(volatile struct ZFOpaqueAtomicType *object, int32_t value);

/// Atomically bitwise XOR the the 8-byte value in the opaque atomic object with the specified value,
/// and store the result to the atomic object.
/// @param object pointer to the opaque atomic object
/// @param value the operand
/// @return the original value stored in the opaque atomic object before this operation
extern int64_t zf_opaque_atomic_fetch_xor_long(volatile struct ZFOpaqueAtomicType *object, int64_t value);

#define zf_opaque_atomic_fetch_xor(object, value)   type_cast(value)    \
    (   sizeof(value) == 1 ? zf_opaque_atomic_fetch_xor_byte((object), (int8_t)(value)) : \
        (sizeof(value) == 2 ? zf_opaque_atomic_fetch_xor_short((object), (int16_t)(value)) : \
        (sizeof(value) == 4 ? zf_opaque_atomic_fetch_xor_int((object), (int32_t)(value)) : \
        (sizeof(value) == 8 ? zf_opaque_atomic_fetch_xor_long((object), (int64_t)(value)) : \
        zf_opaque_atomic_fetch_xor_int((object), (int32_t)(value)) ) ) )       \
    )

// MARK: atomic fetch and operations

/// Atomically bitwise AND the the 1-byte value in the opaque atomic object with the specified value,
/// and store the result to the atomic object.
/// @param object pointer to the opaque atomic object
/// @param value the operand
/// @return the original value stored in the opaque atomic object before this operation
extern int8_t zf_opaque_atomic_fetch_and_byte(volatile struct ZFOpaqueAtomicType *object, int8_t value);

/// Atomically bitwise AND the the 2-byte value in the opaque atomic object with the specified value,
/// and store the result to the atomic object.
/// @param object pointer to the opaque atomic object
/// @param value the operand
/// @return the original value stored in the opaque atomic object before this operation
extern int16_t zf_opaque_atomic_fetch_and_short(volatile struct ZFOpaqueAtomicType *object, int16_t value);

/// Atomically bitwise AND the the 2-byte value in the opaque atomic object with the specified value,
/// and store the result to the atomic object.
/// @param object pointer to the opaque atomic object
/// @param value the operand
/// @return the original value stored in the opaque atomic object before this operation
extern int16_t zf_opaque_atomic_fetch_and_short(volatile struct ZFOpaqueAtomicType *object, int16_t value);

/// Atomically bitwise AND the the 4-byte value in the opaque atomic object with the specified value,
/// and store the result to the atomic object.
/// @param object pointer to the opaque atomic object
/// @param value the operand
/// @return the original value stored in the opaque atomic object before this operation
extern int32_t zf_opaque_atomic_fetch_and_int(volatile struct ZFOpaqueAtomicType *object, int32_t value);

/// Atomically bitwise AND the the 8-byte value in the opaque atomic object with the specified value,
/// and store the result to the atomic object.
/// @param object pointer to the opaque atomic object
/// @param value the operand
/// @return the original value stored in the opaque atomic object before this operation
extern int64_t zf_opaque_atomic_fetch_and_long(volatile struct ZFOpaqueAtomicType *object, int64_t value);

#define zf_opaque_atomic_fetch_and(object, value)   type_cast(value)    \
    (   sizeof(value) == 1 ? zf_opaque_atomic_fetch_and_byte((object), (int8_t)(value)) : \
        (sizeof(value) == 2 ? zf_opaque_atomic_fetch_and_short((object), (int16_t)(value)) : \
        (sizeof(value) == 4 ? zf_opaque_atomic_fetch_and_int((object), (int32_t)(value)) : \
        (sizeof(value) == 8 ? zf_opaque_atomic_fetch_and_long((object), (int64_t)(value)) : \
        zf_opaque_atomic_fetch_and_int((object), (int32_t)(value)) ) ) )       \
    )

// MARK: atomic exchange operations

/// Atomically exchange the opaque atomic object and the specified 1-byte value.
/// @param object pointer to the opaque atomic object
/// @param value the value to be exchanged
/// @return the original value stored in the opaque atomic object before this operation
extern int8_t zf_opaque_atomic_exchange_byte(volatile struct ZFOpaqueAtomicType *object, int8_t value);

/// Atomically exchange the opaque atomic object and the specified 2-byte value.
/// @param object pointer to the opaque atomic object
/// @param value the value to be exchanged
/// @return the original value stored in the opaque atomic object before this operation
extern int16_t zf_opaque_atomic_exchange_short(volatile struct ZFOpaqueAtomicType *object, int16_t value);

/// Atomically exchange the opaque atomic object and the specified 4-byte value.
/// @param object pointer to the opaque atomic object
/// @param value the value to be exchanged
/// @return the original value stored in the opaque atomic object before this operation
extern int32_t zf_opaque_atomic_exchange_int(volatile struct ZFOpaqueAtomicType *object, int32_t value);

/// Atomically exchange the opaque atomic object and the specified 8-byte value.
/// @param object pointer to the opaque atomic object
/// @param value the value to be exchanged
/// @return the original value stored in the opaque atomic object before this operation
extern int64_t zf_opaque_atomic_exchange_long(volatile struct ZFOpaqueAtomicType *object, int64_t value);

#define zf_opaque_atomic_exchange(object, value)    type_cast(value) \
        (   sizeof(value) == 1 ? zf_opaque_atomic_exchange_byte((object), (int8_t)(value)) : \
            (sizeof(value) == 2 ? zf_opaque_atomic_exchange_short((object), (int16_t)(value)) : \
            (sizeof(value) == 4 ? zf_opaque_atomic_exchange_int((object), (int32_t)(value)) : \
            (sizeof(value) == 8 ? zf_opaque_atomic_exchange_long((object), (int64_t)(value)) : \
            zf_opaque_atomic_exchange_int((object), (int32_t)(value)) ) ) ) \
        )

// MARK: atomic compare and exchange operations

/// Atomically compare the the value stores in the opaque atomic object
/// and the value stores in the `expected` for 1 byte.
/// It they are equal, write the `desired` value to the opaque atomic object;
/// Otherwise the value stores in the `expected` will be put into opaque atomic object.
/// @param object pointer to the opaque atomic object
/// @param expected the expected object
/// @param desired the value that'll be updated to opaque atomic object
/// @return true if update succeeds, false otherwise.
extern bool zf_opaque_atomic_compare_exchange_byte(volatile struct ZFOpaqueAtomicType *object,
                                                   int8_t *expected, int8_t desired);

/// Atomically compare the the value stores in the opaque atomic object
/// and the value stores in the `expected` for 2 bytes.
/// It they are equal, write the `desired` value to the opaque atomic object;
/// Otherwise the value stores in the `expected` will be put into opaque atomic object.
/// @param object pointer to the opaque atomic object
/// @param expected the expected object
/// @param desired the value that'll be updated to opaque atomic object
/// @return true if update succeeds, false otherwise.
extern bool zf_opaque_atomic_compare_exchange_short(volatile struct ZFOpaqueAtomicType *object,
                                                   int16_t *expected, int16_t desired);

/// Atomically compare the the value stores in the opaque atomic object
/// and the value stores in the `expected` for 4 bytes.
/// It they are equal, write the `desired` value to the opaque atomic object;
/// Otherwise the value stores in the `expected` will be put into opaque atomic object.
/// @param object pointer to the opaque atomic object
/// @param expected the expected object
/// @param desired the value that'll be updated to opaque atomic object
/// @return true if update succeeds, false otherwise.
extern bool zf_opaque_atomic_compare_exchange_int(volatile struct ZFOpaqueAtomicType *object,
                                                    int32_t *expected, int32_t desired);

/// Atomically compare the the value stores in the opaque atomic object
/// and the value stores in the `expected` for 4 bytes.
/// It they are equal, write the `desired` value to the opaque atomic object;
/// Otherwise the value stores in the `expected` will be put into opaque atomic object.
/// @param object pointer to the opaque atomic object
/// @param expected the expected object
/// @param desired the value that'll be updated to opaque atomic object
/// @return true if update succeeds, false otherwise.
extern bool zf_opaque_atomic_compare_exchange_long(volatile struct ZFOpaqueAtomicType *object,
                                                  int64_t *expected, int64_t desired);

#define zf_opaque_atomic_compare_exchange(object, expected, desired)    type_cast(*(expected)) \
    (   sizeof(*(expected)) == 1 ? zf_opaque_atomic_compare_exchange_byte((object), (int8_t*)(expected), (int8_t)(desired)) : \
        (sizeof(*(expected)) == 2 ? zf_opaque_atomic_compare_exchange_short((object), (int16_t*)(expected), (int16_t)(desired)) : \
        (sizeof(*(expected)) == 4 ? zf_opaque_atomic_compare_exchange_int((object), (int32_t*)(expected), (int32_t)(desired)) : \
        (sizeof(*(expected)) == 8 ? zf_opaque_atomic_compare_exchange_long((object), (int64_t*)(expected), (int64_t)(desired)) : \
        zf_opaque_atomic_compare_exchange_int((object), (int32_t*)(expected), (int32_t)(desired)) ) ) ) \
    )

#endif /* zf_atomic_opaque_h */

