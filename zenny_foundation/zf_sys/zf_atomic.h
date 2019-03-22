//
//  zf_atomic.h
//  FoundationBasedAlgorithms
//
//  Created by Zenny Chen on 2018/11/20.
//  Copyright © 2018 CodeLearning Studio. All rights reserved.
//

#ifndef zf_atomic_h
#define zf_atomic_h

#ifndef _WIN32
// Unix-like OS environment
#include <stdatomic.h>

#else
// Windows OS environment
#include <stdbool.h>

#define ATOMIC_VAR_INIT(value)      (value)
#define ATOMIC_FLAG_INIT            { false }
#define atomic_init(object, value)  (void)(*(object) = (value))

#ifdef __GNUC__
// For GNU C compilers, use more proper way to implement atomic_store and atomic_load.
#define atomic_store(object, desired)   (void)( *(volatile typeof(*(object)) *)(object) = (desired) )
#define atomic_load(object)             *(volatile typeof(*(object)) *)(object)
#else
// For other compilers, just use common way.
#define atomic_store(object, desired)   (void)( *(object) = (desired) )
#define atomic_load(object)             *(object)
#endif

typedef int    atomic_int;
typedef struct atomic_flag { bool _Value; } atomic_flag;

extern bool atomic_flag_test_and_set(volatile atomic_flag *flag);
extern void atomic_flag_clear(volatile atomic_flag *flag);

extern int atomic_fetch_add(volatile atomic_int *object, int operand);
extern int atomic_fetch_sub(volatile atomic_int *object, int operand);
extern int atomic_fetch_or(volatile atomic_int *object, int operand);
extern int atomic_fetch_xor(volatile atomic_int *object, int operand);
extern int atomic_fetch_and(volatile atomic_int *object, int operand);

extern int atomic_exchange(volatile atomic_int *object, int desired);

extern bool atomic_compare_exchange_strong(volatile atomic_int *object, int *expected, int desired);
extern bool atomic_compare_exchange_weak(volatile atomic_int *object, int *expected, int desired);

#endif  // #ifdef _WIN32

#endif /* zf_atomic_h */

