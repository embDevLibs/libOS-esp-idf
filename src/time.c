/**
 * @file time.c
 * @brief Implements the libOS time interface functions for the time structure.
 * 
 * @details
 * This file implements the C functions for the libOS time interface. It work
 * on the assumption that time is the number of nanoseconds since a fixed
 * point in time.
 * It uses the xTaskGetTickCount from FreeRTOS to get the current time in ticks
 * since the start of system. This does limit the resolution of 'now' to the
 * scheduler tick frequency, but still allows calculation and specification of
 * smaller time periods because internally nanoseconds are still used.
 * 
 * There is some extra calculations with the time because the nanoseconds type
 * might be able to hold a value larger than what the TimerTick_t from FreeRTOS
 * could do. Or the other way around, where the nanosecond component is not big
 * enough to hold the TimerTick_t component of FreeRTOS.
 * 
 */

#include <time.h>
#include <stdint.h>

#include <FreeRTOS.h>
#include <task.h>

#include "libos/time.h"

#define MIN_VAL INT_LEAST64_MIN
#define MAX_VAL INT_LEAST64_MAX

const libos_time_t overflow_maximum = ((TimerTick_t)0 - 1);
const libos_time_nanoseconds_t per_tick = ((libos_time_nanoseconds_t)1000 * 1000 * 1000) / configTICK_RATE_HZ;

libos_time_t libos_time_get_now(void)
{
    return (xTaskGetTickCount() * per_tick) % overflow_maximum;
}

TimerTick_t libos_time_to_ticks(libos_time_t time)
{
    if (time < 0)
    {
        return 0;
    }
    return (TimerTick_t)(time / per_tick);
}

libos_time_nanoseconds_t libos_time_difference_ns(libos_time_t a, libos_time_t b)
{
    return libos_time_to_ns(libos_time_subtract(a, b));
}

libos_time_microseconds_t libos_time_difference_us(libos_time_t a, libos_time_t b)
{
    return libos_time_to_us(libos_time_subtract(a, b));
}

libos_time_milliseconds_t libos_time_difference_ms(libos_time_t a, libos_time_t b)
{
    return libos_time_to_ms(libos_time_subtract(a, b));
}

libos_time_seconds_t libos_time_difference_s(libos_time_t a, libos_time_t b)
{
    return libos_time_to_s(libos_time_subtract(a, b));
}

libos_time_t libos_time_from_ns(libos_time_nanoseconds_t ns)
{
    return (libos_time_t)ns;
}

libos_time_t libos_time_from_us(libos_time_microseconds_t us)
{
    return (libos_time_t)us * 1000;
}

libos_time_t libos_time_from_ms(libos_time_milliseconds_t ms)
{
    return (libos_time_t)ms * 1000 * 1000;
}

libos_time_t libos_time_from_s(libos_time_seconds_t s)
{
    return (libos_time_t)s * 1000 * 1000 * 1000;
}

libos_time_nanoseconds_t libos_time_to_ns(libos_time_t time)
{
    return time;
}

libos_time_microseconds_t libos_time_to_us(libos_time_t time)
{
    return time / 1000;
}

libos_time_milliseconds_t libos_time_to_ms(libos_time_t time)
{
    return time / 1000 / 1000;
}

libos_time_seconds_t libos_time_to_s(libos_time_t time)
{
    return time / 1000 / 1000 / 1000;
}

uint_least64_t absolute_difference(libos_time_nanoseconds_t a, libos_time_nanoseconds_t b)
{
    return 0;
}

libos_time_t libos_time_subtract(libos_time_t a, libos_time_t b)
{
    // Because of the fact that the time is signed extra safeguards are needed.
    // Assume 2s-complement and basically error if we detect anything else we
    // can't easily compensate for.


#if !((MIN_VAL < -MAX_VAL) || (-(MIN_VAL - 1 ) >= MAX_VAL))
#error "Unrecognised configuration, 0 is suppose to be counted as positive. The MIN/MAX should be symmetric around -1 and 0 (0.5 should be the 'middle')."
#endif

    libos_time_nanoseconds_t us_a = libos_time_to_ns(a);
    libos_time_nanoseconds_t us_b = libos_time_to_ns(b);

    if ((us_a < 0 && us_b < 0) || (us_a > 0 && us_b > 0)) // Both in the sign so that should always work
    {
        return us_a - us_b;
    }
    else if (us_a < 0 && us_b >= 0) // Extra range because sign not the same
    {
        libos_time_nanoseconds_t to_min = us_a - MIN_VAL; // This gives absolute value until minimal value.
        if (to_min > us_b)
        {
            return us_a - us_b;
        }
        else
        {
            libos_time_nanoseconds_t left = us_b - to_min;
            return MAX_VAL - left;
        }
    }
    else if (us_a >= 0 && us_b < 0) // Extra range because sign not the same
    {
        if (us_b == MIN_VAL) // Can't represent us_b as positive by one.
        {
            // Just break even and then proceed normally
            if (us_a == MAX_VAL)
            {
                us_a = 0;
                us_b += 1;
            }
            else
            {
                us_a += 1;
                us_b += 0;
            }
        }
        
        libos_time_nanoseconds_t pos_b = -us_b;
        libos_time_nanoseconds_t until_max = MAX_VAL - us_a;
        if (until_max > pos_b)
        {
            return us_a - us_b;
        }
        else
        {
            libos_time_nanoseconds_t left = pos_b - until_max;
            return left;
        }
    }
    else
    {
        return 0; // Should never happen
    }
}

libos_time_t libos_time_add(libos_time_t a, libos_time_t b)
{
    libos_time_nanoseconds_t us_a = libos_time_to_ns(a);
    libos_time_nanoseconds_t us_b = libos_time_to_ns(b);
    libos_time_nanoseconds_t us_result = (us_a + us_b) % overflow_maximum;
    return libos_time_from_ns(us_result);
}

bool libos_time_is_later(libos_time_t a, libos_time_t b)
{
    return b > a;
}

bool libos_time_is_earlier(libos_time_t a, libos_time_t b)
{
    return b < a;
}

bool libos_time_is_same(libos_time_t a, libos_time_t b)
{
    return b == a;
}
