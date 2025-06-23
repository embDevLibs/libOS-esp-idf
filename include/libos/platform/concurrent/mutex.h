/**
 * @file mutex.h
 * @brief Implementation of the mutex API for libOS
 *
 * @details
 * This implements the interface defined in libos/concurrent/mutex.h. It is
 * implemented using the C11 stdlib interface for mutexes. This supports all
 * the features also found in libos (and more but those not used).
 */

#pragma once
#ifndef LIBOS_PLATFORM_CONCURRENT_MUTEX_H
#define LIBOS_PLATFORM_CONCURRENT_MUTEX_H

#include <stdint.h>
#include <stdbool.h>

#ifndef LIBOS_MUTEX_ENABLE_STATIC_ALLOCATION
#define LIBOS_MUTEX_ENABLE_STATIC_ALLOCATION configSUPPORT_STATIC_ALLOCATION
#endif // LIBOS_MUTEX_ENABLE_STATIC_ALLOCATION

#ifndef LIBOS_MUTEX_ENABLE_DYNAMIC_ALLOCATION
#define LIBOS_MUTEX_ENABLE_DYNAMIC_ALLOCATION configSUPPORT_DYNAMIC_ALLOCATION
#endif // LIBOS_MUTEX_ENABLE_DYNAMIC_ALLOCATION

#ifndef LIBOS_MUTEX_ENABLE_RECURSIVE
#define LIBOS_MUTEX_ENABLE_RECURSIVE configUSE_RECURSIVE_MUTEXES
#endif // LIBOS_MUTEX_ENABLE_RECURSIVE

#if LIBOS_FREERTOS_SUBDIR_FOR_INCLUDE==1
#include <freertos/FreeRTOS.h>
#include <freertos/semphr.h>
#else // LIBOS_FREERTOS_SUBDIR_FOR_INCLUDE==1
#include <FreeRTOS.h>
#include <semphr.h>
#endif // LIBOS_FREERTOS_SUBDIR_FOR_INCLUDE==1

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/**
 * @brief Container structure of a mutex itself (for static allocation purpose only, content should not be directly accessed).
 *
 */
typedef struct {

    #if configSUPPORT_STATIC_ALLOCATION==1
    /**
     * @brief The static data structure for a mutex.
     * 
     */
    StaticSemaphore_t mutex;
    #endif // configSUPPORT_STATIC_ALLOCATION==1
    
    /**
     * @brief Handle to the actual mutex.
     * 
     */
    SemaphoreHandle_t mutex_handle;

    /**
     * @brief Is this mutex statically allocated or dynamically from the heap.
     * 
     */
    bool is_static;

    /**
     * @brief Is the mutex recursive.
     * 
     */
    bool is_recursive;
} libos_mutex_t;

/**
 * @brief Handle to a mutex.
 * 
 */
typedef libos_mutex_t *libos_mutex_handle_t;

#ifdef __cplusplus
} // extern "C"
#endif // __cplusplus

#endif // LIBOS_PLATFORM_CONCURRENT_MUTEX_H
