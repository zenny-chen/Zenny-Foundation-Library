//
//  zf_memory.c
//  ZennyFoundationTest
//
//  Created by Zenny Chen on 2018/12/2.
//  Copyright © 2018 Zenny Chen. All rights reserved.
//

#include "zf_memory.h"
#include "zf_atomic.h"
#include "zf_sync.h"

#include <stdlib.h>
#include <string.h>

void* (*zf_memalloc)(size_t) = malloc;
void (*zf_dealloc)(void*) = free;

void ZFSetAllocator(void* (*allocator)(size_t))
{
    if(allocator != NULL)
        zf_memalloc = allocator;
}

void ZFSetDeallocator(void (*deallocator)(void*))
{
    if(deallocator != NULL)
        zf_dealloc = deallocator;
}

void* (* ZFGetCurrentAllocator(void))(size_t)
{
    return zf_memalloc;
}

void (* ZFGetCurrentDeallocator(void))(void*)
{
    return zf_dealloc;
}

/// Memory profile info
struct MemoryProfileInfo
{
    /// pointer to the memory buffer
    uintptr_t ptr;
    
    /// the size of the memory buffer
    size_t size;
    
    /// the line number in the source file
    int lineNumber;
    
    /// the pointer identifier
    const char *ptrID;
    
    /// the function name
    const char *funcName;
    
    /// the file name
    const char *fileName;
    
    /// pointer to the next node
    struct MemoryProfileInfo *link;
};

/// Memory profile tree
struct MemoryProfileTree
{
    /// pointer to the MemoryProfileInfo node
    struct MemoryProfileInfo *link;
};

static struct MemoryProfileTree sMemoryList = { NULL };
static volatile atomic_flag sMemoryListLock = ATOMIC_FLAG_INIT;

static struct MemoryProfileTree sLeakedList = { NULL };
static volatile atomic_flag sLeakedListLock = ATOMIC_FLAG_INIT;

/// Create a MemoryProfileInfo object and initialize all the members to zero.
/// @return a newly created MemoryProfileInfo object
static struct MemoryProfileInfo *CreateMemoryInfoProfile(void)
{
    struct MemoryProfileInfo *memInfo = zf_memalloc(sizeof(*memInfo));
    memset(memInfo, 0, sizeof(*memInfo));
    return memInfo;
}

/// Append the specified MemoryProfileInfo node to the specified MemoryProfileTree object.
/// @param tree the specified tree
/// @param node the specified node
static void AppendMemoryProfileNode(struct MemoryProfileTree *tree, struct MemoryProfileInfo *node)
{
    if(tree->link == NULL)
        tree->link = node;
    else
    {
        struct MemoryProfileInfo *pn = tree->link;
        while(pn->link != NULL)
            pn = pn->link;
        
        pn->link = node;
    }
    
    node->link = NULL;
}

/// Remove the specified MemoryProfileInfo node from the specified MemoryProfileTree tree.
/// @param tree the specified tree
/// @param node the specified node
static void RemoveMemoryProfileNode(struct MemoryProfileTree *tree, struct MemoryProfileInfo *node)
{
    if(tree->link == node)
    {
        tree->link = node->link;
        zf_dealloc(node);
        return;
    }

    struct MemoryProfileInfo *dstNode = tree->link;
    while(dstNode->link != NULL)
    {
        if(dstNode->link == node)
            break;
        
        dstNode = dstNode->link;
    }

    if(dstNode->link == node)
    {
        dstNode->link = node->link;
        zf_dealloc(node);
    }
}

/// Begin a memory profile node iteration.
/// @param tree the specified tree
/// @return If the tree has any node, return it. Otherwise return NULL.
static struct MemoryProfileInfo * MemoryProfileNodeIteratorBegin(struct MemoryProfileTree *tree)
{
    return tree->link;
}

/// Do the memory profile node iteration.
/// @param iter the specified node to iterate
/// @return If the node has a next node, return it. Otherwise return NULL.
static struct MemoryProfileInfo * MemoryProfileNodeIteratorNext(struct MemoryProfileInfo *iter)
{
    if(iter == NULL)
        return NULL;
    
    return iter->link;
}

/// Get the number of the nodes that the specified tree contains.
/// @param tree the specified tree
/// @return the number of the nodes
static size_t GetMemoryProfileNodeCount(const struct MemoryProfileTree *tree)
{
    const struct MemoryProfileInfo *node = tree->link;
    size_t length = 0;
    while(node != NULL)
    {
        node = node->link;
        length++;
    }
    return length;
}

/// Append the specified MemoryProfileInfo info to the leaked list
/// @param info the specified MemoryProfileInfo info
static void AddLeakedItem(struct MemoryProfileInfo *info)
{
    zf_lock(&sLeakedListLock);
    
    AppendMemoryProfileNode(&sLeakedList, info);
    
    zf_unlock(&sLeakedListLock);
}

void* zf_memalloc_profile(size_t size, void *ptr, const char *ptrName, const char *funcName, const char *fileName, int lineNumber)
{
    void *memBuffer = zf_memalloc(size);
    
    zf_lock(&sMemoryListLock);
    
    struct MemoryProfileInfo *targetNode = NULL;
    // Find the node whose address has already been in the record list.
    for(struct MemoryProfileInfo *iter = MemoryProfileNodeIteratorBegin(&sMemoryList); iter != NULL; iter = MemoryProfileNodeIteratorNext(iter))
    {
        if(iter->ptr == (uintptr_t)ptr)
        {
            targetNode = iter;
            break;
        }
    }
    
    if(targetNode != NULL)
    {
        struct MemoryProfileInfo *leakedInfo = CreateMemoryInfoProfile();
        leakedInfo->ptr = (uintptr_t)memBuffer;
        leakedInfo->size = size;
        leakedInfo->lineNumber = lineNumber;
        leakedInfo->ptrID = ptrName;
        leakedInfo->funcName = funcName;
        leakedInfo->fileName = fileName;
        AddLeakedItem(leakedInfo);
    }

    struct MemoryProfileInfo *memInfo = CreateMemoryInfoProfile();
    memInfo->ptr = (uintptr_t)memBuffer;
    memInfo->size = size;
    memInfo->lineNumber = lineNumber;
    memInfo->ptrID = ptrName;
    memInfo->funcName = funcName;
    memInfo->fileName = fileName;

    AppendMemoryProfileNode(&sMemoryList, memInfo);

    zf_unlock(&sMemoryListLock);

    return memBuffer;
}

void zf_dealloc_profile(void *ptr)
{
    zf_lock(&sMemoryListLock);
    
    struct MemoryProfileInfo *targetNode = NULL;
    // Find the node whose address has already been in the record list.
    for(struct MemoryProfileInfo *iter = MemoryProfileNodeIteratorBegin(&sMemoryList); iter != NULL; iter = MemoryProfileNodeIteratorNext(iter))
    {
        if(iter->ptr == (uintptr_t)ptr)
        {
            targetNode = iter;
            break;
        }
    }

    if(targetNode != NULL)
        RemoveMemoryProfileNode(&sMemoryList, targetNode);
    
    zf_unlock(&sMemoryListLock);
    
    zf_dealloc(ptr);
}

size_t zf_mem_profile_registered_item_count(void)
{
    return GetMemoryProfileNodeCount(&sMemoryList);
}

size_t zf_mem_profile_leaked_item_count(void)
{
    return GetMemoryProfileNodeCount(&sLeakedList);
}

const struct ZFMemoryProfileInfo * zf_enumerate_registered_profile_item(const struct ZFMemoryProfileInfo *info)
{
    return info == NULL ? (const struct ZFMemoryProfileInfo*)sMemoryList.link : (const struct ZFMemoryProfileInfo*)((const struct MemoryProfileInfo*)info)->link;
}

const struct ZFMemoryProfileInfo * zf_enumerate_leaked_profile_item(const struct ZFMemoryProfileInfo *info)
{
    return info == NULL ? (const struct ZFMemoryProfileInfo*)sLeakedList.link : (const struct ZFMemoryProfileInfo*)((const struct MemoryProfileInfo*)info)->link;
}

