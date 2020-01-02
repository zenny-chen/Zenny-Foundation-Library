//
//  zenny_foundation.c
//  FoundationBasedAlgorithms
//
//  Created by Zenny Chen on 2018/5/27.
//  Copyright © 2018年 CodeLearning Studio. All rights reserved.
//

#include "zenny_foundation.h"

#include <limits.h>
#include <stdlib.h>

// MARK: Zenny Foundation Class List

static const char* const sFoundationClassList[ZENNY_FOUNDATION_CLASS_COUNT] = {
    "(null)",
    "ZFObject",
    "ZFSingleLinkNode",
    "ZFSingleLinkTable",
    "ZFNumber"
};

// MARK: Foundation Functions

void ZFReleaseObject(struct ZFObject *obj)
{
    if(obj == NULL || obj->identifier == ZENNY_FOUNDATION_NULL_IDENTIFIER)
        return;

    zf_lock(&obj->lock);
    if(--obj->ref_cnt == 0)
    {
        // Deallocate the current object
        if(obj->dealloc != NULL)
            obj->dealloc(obj);
        
        zf_unlock(&obj->lock);

        // Now free the object
        ZF_FREE(obj);
    }
    else
        zf_unlock(&obj->lock);
}

void ZFRetainObject(struct ZFObject *obj)
{
    if(obj == NULL || obj->identifier == ZENNY_FOUNDATION_NULL_IDENTIFIER)
        return;
    
    zf_lock(&obj->lock);
    
    if(obj->ref_cnt < INT_MAX)
        obj->ref_cnt++;
    
    zf_unlock(&obj->lock);
}

const char* ZFGetObjectDescription(struct ZFObject *obj, const char* (*customizedDescFuncPtr)(struct ZFObject *obj))
{
    if(obj == NULL)
        return "(null)";
        
    const uint32_t ident = obj->identifier;
    
    if(ident < ZENNY_FOUNDATION_CLASS_COUNT)
        return sFoundationClassList[obj->identifier];
    
    return customizedDescFuncPtr != NULL ? customizedDescFuncPtr(obj) : "unknown";
}

