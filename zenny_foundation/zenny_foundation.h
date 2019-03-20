//
//  zenny_foundation.h
//  FoundationBasedAlgorithms
//
//  Created by Zenny Chen on 2018/5/27.
//  Copyright © 2018年 CodeLearning Studio. All rights reserved.
//

#ifndef zenny_foundation_h
#define zenny_foundation_h

#include "zf_core_api.h"

// MARK: The basic types which will be used in this foundation library

#include <stdbool.h>

#ifdef _WIN32
/// signed size_t type which may be used in this foundation library
typedef ptrdiff_t   ssize_t;
#endif

// MARK: Zenny Foundation Class Identifiers

#define ZENNY_FOUNDATION_NULL_IDENTIFIER        0
#define ZENNY_FOUNDATION_OBJECT_IDENTIFIER      1
#define ZENNY_SINGLE_LINK_NODE_IDENTIFIER       2
#define ZENNY_SINGLE_LINK_TABLE_IDENTIFIER      3
#define ZENNY_NUMBER_IDENTIFIER                 4

#define ZENNY_FOUNDATION_CLASS_COUNT            5

// MARK: Basic Foundation functions

/// Easy way to retain the foundation object
#define ZF_RETAIN_OBJECT(obj)       ZFRetainObject((struct ZFObject*)(obj))

/// Easy way to retain the foundation object and return the object
#define ZF_RETAIN_RET_OBJECT(obj)   (ZF_RETAIN_OBJECT(obj), (obj))

/// Easy way to release the foundation object
#define ZF_RELEASE_OBJECT(obj)      ( ZFReleaseObject((struct ZFObject*)(obj)), ((obj) = NULL) )

/// Easy way to fetch the description of the object
#define ZF_OBJECT_DESC(obj)         ZFGetObjectDescription((struct ZFObject*)(obj), NULL)

/// Easy way to get the number of elements in a C array
#define zf_countof(array)           (sizeof(array) / sizeof((array)[0]))


/// Common object type
struct ZFObject
{
    /// This member is used to identify that which class this object belongs to.
    uint32_t identifier;
    
    /// object reference count
    volatile int ref_cnt;
    
    /// lock used to retain/release
    volatile atomic_flag lock;
    
    /// This member can be used casually.
    uintptr_t data;
    
    /// dealloc callback function
    void (*dealloc)(struct ZFObject *obj);
};

/// Initialize a specified object
/// @param obj a ZFObject instance
static inline void ZFInitObject(struct ZFObject *obj)
{
    obj->identifier = ZENNY_FOUNDATION_OBJECT_IDENTIFIER;
    obj->ref_cnt = 1;
    obj->lock = (atomic_flag)ATOMIC_FLAG_INIT;
    obj->data = 0;
    obj->dealloc = NULL;
}

/// Create a ZFObject instance
/// @param obj_id the object identifier
/// @return a ZFObject instance
#define ZF_CREATE_OBJECT(obj_id)    {  ZF_MALLOC(obj_id, sizeof(*(obj_id))); ZFInitObject(obj_id); }

/// Release a specified ZFObject instance
/// @param obj a ZFObject compliant instance
extern void ZFReleaseObject(struct ZFObject *obj);

/// Retain a ZFObject instance
/// @param obj a ZFObject compliant instance
extern void ZFRetainObject(struct ZFObject *obj);

/// Get the description of the specified object.
/// @param obj a ZFObject compliant instance
/// @param customizedDescFuncPtr the customized object description fetch function you provide, if you have defined your own ZFObject-basded class.
/// @return the description of the specified object
extern const char* ZFGetObjectDescription(struct ZFObject *obj, const char* (*customizedDescFuncPtr)(struct ZFObject *obj));

#endif /* zenny_foundation_h */

