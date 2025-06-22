/**
 * @file time.h
 * @brief Implements the time interface for libOS
 * 
 * @details
 * This header implements the interface for the time module in libOS. It
 * defines the typedefs required for the time structure and the time components
 * themselves. The default implementation will just use at least a int64_t,
 * larger types are allowed but compiler dependent. The comparision and
 * conversion functions are defined the accompanying time.c file. Whilst they
 * are very short, they are not macros and need to have a C function for each.
 * This can be done using static inline for each function as they are trivial
 * and might still be done in the future if more significant advantages than
 * just less files appear.
 * 
 * The libos_time_t is now just a alias for the C11 timespec value. This does
 * mean this implementation needs at least C11, but the mutex part also
 * requires C11 anyway. It is also one of the easiest ways to supports both
 * windows (yes, MSVC also support for this part of C11 at the time of writing)
 * and unix systems (which tend to conform quicker to newer standards). Another
 * option would be to use POSIX, but while Windows had support for this, since 
 * Windows 8/Server 2012 it has dropped this.
 * 
 * This header also implements a function that is only available for this
 * platform. The *_get_timespec function is used to get a native timespec value
 * from the time to be used in the platform specific code (since this
 * implementation is stdlib based).
 * 
 */

#pragma once
#ifndef LIBOS_PLATFORM_TIME_H
#define LIBOS_PLATFORM_TIME_H

#include <stdint.h>

#if LIBOS_FREERTOS_SUBDIR_FOR_INCLUDE==1
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#else // LIBOS_FREERTOS_SUBDIR_FOR_INCLUDE==1
#include <FreeRTOS.h>
#include <task.h>
#endif // LIBOS_FREERTOS_SUBDIR_FOR_INCLUDE==1

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/**
 * @brief System native type to store time in.
 * 
 */
typedef int_least64_t libos_time_t;

/**
 * @brief Type used to represent days on this system.
 * 
 */
typedef int_least64_t libos_time_days_t;

/**
 * @brief Type used to represent seconds on this system.
 * 
 */
typedef int_least64_t libos_time_seconds_t;

/**
 * @brief Type used to represent milliseconds on this system.
 * 
 */
typedef int_least64_t libos_time_milliseconds_t;

/**
 * @brief Type used to represent microseconds on this system.
 * 
 */
typedef int_least64_t libos_time_microseconds_t;

/**
 * @brief Type used to represent nanoseconds on this system.
 * 
 */
typedef int_least64_t libos_time_nanoseconds_t;


/**
 * @brief Returns the number of FreeRTOS ticks that represent this time.
 * Any negative time will be converted to 0.
 * 
 * @param[in] time The time to convert to FreeRTOS ticks.
 * 
 * @return TickType_t The resulting number of FreeRTOS ticks that represent the time period.
 */
TickType_t libos_time_to_ticks(libos_time_t time);

#ifdef __cplusplus
} // extern "C"
#endif // __cplusplus

#endif // LIBOS_PLATFORM_TIME_H
