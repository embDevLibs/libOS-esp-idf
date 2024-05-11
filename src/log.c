/**
 * @file log.c
 * @brief The C function implementations for the implementations C function of the libOS logging interface.
 * 
 * @details
 * 
 * This file implements the low-level libos_logging_print function. It takes
 * the log level, module information and the print arguments and formats them
 * to be printed out on the stdout using a regular printf and vprintf.
 * It does first check if the modules minimum log level is high enough for the
 * log statement to be logged.
 * 
 * It also depends on the time module of libos, it namely also prints the
 * timestamp in the log message of each log statement.
 */

#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdarg.h>
#include <string.h>

#include "libos/time.h"
#include "libos/log.h"

static const char *err_name = "ERR";
static const char *wrn_name = "WRN";
static const char *inf_name = "INF";
static const char *dbg_name = "DBG";
static const char *unkown_name = "UNK";

static libos_log_print_fn printer = NULL;
static char* print_buffer = NULL;
static size_t print_buffer_size = 0;

static const char *err_to_name(int level)
{
    if (level == LIBOS_LOG_LEVEL_ERR)
    {
        return err_name;
    }
    else if (level == LIBOS_LOG_LEVEL_WRN)
    {
        return wrn_name;
    }
    else if (level == LIBOS_LOG_LEVEL_INF)
    {
        return inf_name;
    }
    else if (level == LIBOS_LOG_LEVEL_DBG)
    {
        return dbg_name;
    }
    else
    {
        return unkown_name;
    }
}

void libos_log_print(int level, const libos_log_module_t *module, const char *format, ...)
{
    if (module == NULL || level < module->level)
    {
        return;
    }

    va_list list;
    va_start(list, format);
    int64_t now = libos_time_to_ms(libos_time_get_now());
    const char *name = err_to_name(level);
    size_t written = snprintf(print_buffer, print_buffer_size, "%8" PRId64 " [%s] %s: ", now, module->name, name); // 3 -> milliseconds -> 5 digits means max is 9 9999 which is about 27 hours in seconds, should be fine. Next step would be less than 3 hours.
    printer(print_buffer, written);
    written = vsnprintf(print_buffer, print_buffer_size, format, list);
    printer(print_buffer, written);

    const char* endl = "\n"; // Add that final newline
    printer(endl, strnlen(endl, 2));
}

void libos_log_init(libos_log_print_fn print_fn, const char* print_buffer, size_t print_buffer_size)
{
    printer = print_fn;
    print_buffer = print_buffer;
    print_buffer_size = print_buffer_size;
}
