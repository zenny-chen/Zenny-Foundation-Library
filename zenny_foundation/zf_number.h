//
//  zf_number.h
//  FoundationBasedAlgorithms
//
//  Created by Zenny Chen on 2018/11/21.
//  Copyright © 2018 CodeLearning Studio. All rights reserved.
//

#ifndef zf_number_h
#define zf_number_h

#include "zenny_foundation.h"

/// Number encoding for ZFNumber class
enum ZF_NUMBER_ENCODING
{
    /// Unknown encoding
    ZF_NUMBER_ENCODING_UNKNOWN = '\0',
    
    /// bool encoding
    ZF_NUMBER_ENCODING_BOOL = 'b',
    
    /// int8_t encoding
    ZF_NUMBER_ENCODING_BYTE = 'a',
    
    /// uint8_t encoding
    ZF_NUMBER_ENCODING_UBYTE = 'A',
    
    /// char encoding for UTF-8 characters
    ZF_NUMBER_ENCODING_CHAR = 'c',
    
    /// char16_t encoding for UTF-16 characters
    ZF_NUMBER_ENCODING_CHAR16 = 'u',

    /// int16_t encoding
    ZF_NUMBER_ENCODING_SHORT = 's',
    
    /// uint16_t encoding
    ZF_NUMBER_ENCODING_USHORT = 'S',
    
    /// int32_t encoding
    ZF_NUMBER_ENCODING_INT = 'i',
    
    /// uint32_t encoding
    ZF_NUMBER_ENCODING_UINT = 'I',
    
    /// int64_t encoding
    ZF_NUMBER_ENCODING_LONG = 'l',
    
    /// uint64_t encoding
    ZF_NUMBER_ENCODING_ULONG = 'L',

    /// ptrdiff_t encoding
    ZF_NUMBER_ENCODING_PTRDIFF = 't',
    
    /// ssize_t encoding
    ZF_NUMBER_ENCODING_SSIZE = 'z',
    
    /// size_t encoding
    ZF_NUMBER_ENCODING_SIZE = 'Z',
    
    /// intptr_t encoding
    ZF_NUMBER_ENCODING_INTPTR = 'p',
    
    /// uintptr_t encoding
    ZF_NUMBER_ENCODING_UINTPTR = 'P',
    
    /// intmax_t encoding
    ZF_NUMBER_ENCODING_INTMAX = 'x',
    
    /// uintmax_t encoding
    ZF_NUMBER_ENCODING_UINTMAX = 'X',
    
    /// float encoding
    ZF_NUMBER_ENCODING_FLOAT = 'f',
    
    /// double encoding
    ZF_NUMBER_ENCODING_DOUBLE = 'd'
};

/// The value type used for ZFNumber object
union ZFNumberValueType
{
    bool b;
    int8_t a;
    uint8_t A;
    char c;
    char16_t u;
    int16_t s;
    uint16_t S;
    int32_t i;
    uint32_t I;
    int64_t l;
    uint64_t L;
    ptrdiff_t t;
    ssize_t z;
    size_t Z;
    intptr_t p;
    uintptr_t P;
    intmax_t x;
    uintmax_t X;
    float f;
    double d;
};

/// Zenny Foundation Number class
struct ZFNumber
{
    /// the foundation object
    struct ZFObject obj;
    
    /// the number value
    union ZFNumberValueType value;

    /// the number encoding
    enum ZF_NUMBER_ENCODING encoding;
};

/// Create a ZFNumber object with a number value and the corresponding encoding.
/// @param obj_id the object identifier
/// @param value the value of the number object
/// @param encoding the number encoding
/// @return a ZFNumber object
#define ZF_CREATE_NUMBER(obj_id, value, encoding)   { ZF_MALLOC(obj_id, sizeof(*(obj_id))); ZFInitNumber((obj_id), (value), (encoding)); }

/// An easy way to wrap a basic number value into a ZFNumber object
#define ZF_NUMBER(num)  ({  union ZFNumberValueType value = { }; \
                            enum ZF_NUMBER_ENCODING encoding = ZF_NUMBER_ENCODING_UNKNOWN; \
                            _Generic((num), \
                                bool : (value.b = (num), encoding = ZF_NUMBER_ENCODING_BOOL), \
                                int8_t : (value.a = (num), encoding = ZF_NUMBER_ENCODING_BYTE), \
                                uint8_t : (value.A = (num), encoding = ZF_NUMBER_ENCODING_UBYTE), \
                                char : (value.c = (num), encoding = ZF_NUMBER_ENCODING_CHAR), \
                                int16_t : (value.s = (num), encoding = ZF_NUMBER_ENCODING_SHORT), \
                                uint16_t : (value.S = (num), encoding = ZF_NUMBER_ENCODING_USHORT), \
                                int32_t : (value.i = (num), encoding = ZF_NUMBER_ENCODING_INT), \
                                uint32_t : (value.I = (num), encoding = ZF_NUMBER_ENCODING_UINT), \
                                int64_t : (value.l = (num), encoding = ZF_NUMBER_ENCODING_LONG), \
                                uint64_t : (value.L = (num), encoding = ZF_NUMBER_ENCODING_ULONG), \
                                float : (value.f = (num), encoding = ZF_NUMBER_ENCODING_FLOAT), \
                                double : (value.d = (num), encoding = ZF_NUMBER_ENCODING_DOUBLE), \
                                default : (void)0 ); \
                            struct ZFNumber *number = NULL; \
                            ZF_CREATE_NUMBER(number, value, encoding); \
                            number; \
                        })

/// An easy way to fetch the basic value of the specified ZFNumber object.
#define ZF_NUMBER_GET_VALUE(numObj, typeExpr)   _Generic((typeExpr), \
                                bool : (numObj)->value.b, \
                                int8_t : (numObj)->value.a, \
                                uint8_t : (numObj)->value.A, \
                                char : (numObj)->value.c, \
                                int16_t : (numObj)->value.s, \
                                uint16_t : (numObj)->value.S, \
                                int32_t : (numObj)->value.i, \
                                uint32_t : (numObj)->value.I, \
                                int64_t : (numObj)->value.l, \
                                uint64_t : (numObj)->value.L, \
                                float : (numObj)->value.f, \
                                double : (numObj)->value.d, \
                                default : 0)

/// Initialize a specified object
/// @param number a ZFNumber instance
/// @param value the value of the number object
/// @param encoding the number encoding
static inline void ZFInitNumber(struct ZFNumber *number, union ZFNumberValueType value, enum ZF_NUMBER_ENCODING encoding)
{
    ZFInitObject(&number->obj);
    number->obj.identifier = ZENNY_NUMBER_IDENTIFIER;
    number->value = value;
    number->encoding = encoding;
}

/// Convert a specified ZFNumber object to a UTF-8 C-string which is JSON compatible.
/// @param numObj specified ZFNumber object
/// @param dstBuffer used to store the converted string. Its size should be at least 64 bytes.
extern void ZFConvertNumberToUTF8String(const struct ZFNumber *numObj, char dstBuffer[64]);

#endif /* zf_number_h */

