/**
 * @file time.h
 * @brief Implements the time interface for libOS
 * 
 * @details
 * This header implements the interface for the time module in libOS. It
 * defines the typedefs required for the time structure and the time components
 * themselves. The implementation is based on the ESP-IDF ESP Timer component.
 *
 * The time is kept based on the High Resolution timer component from ESP-IDF.
 * This component keeps a int64 in microseconds since boot. This is affected by
 * the various sleep modes that the ESP can be in. Generally, the time is
 * advanced by the amount of time passed according to the RTC clock. The
 * exception here is that recovering from a deep sleep (or deeper), the time is
 * reset to 0. So, light-sleep or higher -> time recovered from RTC, deep sleep
 * or less -> time resets to 0.
 * The documentation doesn't explicitly mention anything about the overflow
 * behaviour of the counter. This is also rather useless, since a signed 64 bit
 * number in microseconds can keep time up to just over a 100 million days.
 * That is more than 290 thousand years. If your device is still online after
 * that without any downtime, respect.
 * 
 */

#pragma once
#ifndef LIBOS_PLATFORM_TIME_H
#define LIBOS_PLATFORM_TIME_H

#include <stdint.h>

#include "esp_timer.h"

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


#ifdef __cplusplus
} // extern "C"
#endif // __cplusplus

#endif // LIBOS_PLATFORM_TIME_H
