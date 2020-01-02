//
//  zf_memory.h
//  ZennyFoundationTest
//
//  Created by Zenny Chen on 2018/12/2.
//  Copyright © 2018 Zenny Chen. All rights reserved.
//

#ifndef zf_memory_h
#define zf_memory_h

#include <stddef.h>
#include <stdint.h>

/// Configure whether to enable the memory allocation profile or not
#define ZF_USE_MEMORY_PROFILE   1


/// Zenny Foundation general memory allocation
#define ZF_MALLOC(ptr, size)    (   ZF_USE_MEMORY_PROFILE ? \
                                (   (ptr) = zf_memalloc_profile((size), (ptr), #ptr, __func__, __FILE__, __LINE__) ) : \
                                (   (ptr) = zf_memalloc((size)) ) \
                                )

/// Zenny Foundation general memory free
#define ZF_FREE(ptr)            (   (ZF_USE_MEMORY_PROFILE ? \
                                    zf_dealloc_profile((ptr)) : \
                                    zf_dealloc((ptr)) ), (ptr) = NULL   )


/// Zenny Foundation Memory profile info
struct ZFMemoryProfileInfo
{
    /// pointer to the memory buffer
    const uintptr_t ptr;
    
    /// the size of the memory buffer
    const size_t size;
    
    /// the line number in the source file
    const int lineNumber;
    
    /// the pointer identifier
    const char * const ptrID;
    
    /// the function name
    const char * const funcName;
    
    /// the file name
    const char * const fileName;
};


extern void* (*zf_memalloc)(size_t);
extern void (*zf_dealloc)(void*);

/// Set customized allocator for Zenny Foundation objects allocation.
/// The default allocator is `malloc` function from <stdlib.h>.
/// @param allocator the customized allocator
extern void ZFSetAllocator(void* (*allocator)(size_t));

/// Set customized deallocator for Zenny Foundation objects deallocation.
/// The default deallocator is `free` function from <stdlib.h>.
/// @param deallocator the customized deallocator
extern void ZFSetDeallocator(void (*deallocator)(void*));

/// Get current allocator for Zenny Foundation framework.
/// @return the current allocator
extern void* (* ZFGetCurrentAllocator(void))(size_t);

/// Get current deallocator for Zenny Foundation framework.
extern void (* ZFGetCurrentDeallocator(void))(void*);

/// Allocatate a memory buffer with profile info.
/// @param size the size of allocated memory buffer
/// @param ptr the pointer's original address
/// @param ptrName the identifier of the specified pointer varaible
/// @param funcName the name of the function in which the allocation is performed
/// @param fileName the name of the source file in which the allocation is performed
/// @param lineNumber the line number of the source file
/// @return the newly allocated memory buffer
extern void* zf_memalloc_profile(size_t size, void *ptr, const char *ptrName, const char *funcName, const char *fileName, int lineNumber);

/// Deallocatate a memory buffer with profile info.
/// @param ptr the pointer to the memory buffer to be deallocated
extern void zf_dealloc_profile(void *ptr);

/// Fetch the total count of the registered memory buffers.
/// @return the total count of the registered memory buffers
extern size_t zf_mem_profile_registered_item_count(void);

/// Fetch the count of the leaked memory buffers.
/// @return the count of the leaked memory buffers
extern size_t zf_mem_profile_leaked_item_count(void);

/// Enumerate the registered memory profile info.
/// @param info the current memory profile info. For the start of the enumeration, pass NULL.
/// @return the next memory profile info. If the parameter `info` is the last node, return NULL.
extern const struct ZFMemoryProfileInfo * zf_enumerate_registered_profile_item(const struct ZFMemoryProfileInfo *info);

/// Enumerate the leaked memory profile info.
/// @param info the current memory profile info. For the start of the enumeration, pass NULL.
/// @return the next memory profile info. If the parameter `info` is the last node, return NULL.
extern const struct ZFMemoryProfileInfo * zf_enumerate_leaked_profile_item(const struct ZFMemoryProfileInfo *info);

#endif /* zf_memory_h */

