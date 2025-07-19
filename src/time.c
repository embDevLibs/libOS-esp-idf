#include "esp_timer.h"

#include "libos/time.h"

libos_time_t libos_time_get_now(void)
{
    return esp_timer_get_time();
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

libos_time_t absolute_difference(libos_time_nanoseconds_t a, libos_time_nanoseconds_t b)
{
    if (a > b)
    {
        return a - b;
    }
    else
    {
        return b - a;
    }
}

libos_time_t libos_time_subtract(libos_time_t a, libos_time_t b)
{
    // This can be a simple subtract. int64 is so large, that only if you deal
    // with time spans longer than 290 thousand years, you get into trouble.
    return a - b;
}

libos_time_t libos_time_add(libos_time_t a, libos_time_t b)
{
    return a + b;
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
