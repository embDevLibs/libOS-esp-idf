/**
 * @file log.h
 * @brief Implements the logging endpoints for the libOS logging API.
 * 
 * @details
 * This header implements the general purpose logging module interface defined
 * in the libos/log.h header. The module implements the module definition macro
 * as a static definition of a libos_log_module_t structure. This contains the
 * logging level to support a higher minimum log level defined per file. Only
 * one instance per compilation unit is allowed (it is marked static). When
 * print is called the C function that handles the actual printout using the
 * printer callback with snprintf created frames will also take a parameter
 * to this variable. Calling print without first defining a module will result
 * in compilation problems.
 * 
 * This implementation requires a initialization step by the user before using.
 * This function takes a function pointer to a function that will take a buffer
 * and then send it on the actual logging output. And two parameters to specify
 * a buffer to be used by snprintf to prepare the buffer to send to the
 * callback. This is done to avoid dynamic memory allocation and to allow the
 * user to specify the buffer size. This is also the maximum size that one
 * logging entry can be as printf can't do windowed printing.
 */

#pragma once
#ifndef LIBOS_PLATFORM_LOG_H
#define LIBOS_PLATFORM_LOG_H

#include <stddef.h>

/**
 * @brief The log level for a error message.
 * 
 */
#define LIBOS_LOG_LEVEL_ERR 0

/**
 * @brief The log level for a warning message.
 * 
 */
#define LIBOS_LOG_LEVEL_WRN 1

/**
 * @brief The log level for a info message.
 * 
 */
#define LIBOS_LOG_LEVEL_INF 2

/**
 * @brief The log level for a debug message.
 * 
 */
#define LIBOS_LOG_LEVEL_DBG 3

/**
 * @brief Defines a new log module for this file
 * 
 */
#define LIBOS_LOG_MODULE_MIN_LEVEL(log_name, log_level) static libos_log_module_t __TAG = { .level = log_level, .name = (#log_name) };  

/**
 * @brief Initialize the logging system
 * 
 */
#define LIBOS_LOG_INIT() // Nothing to init for this. Just API compliance.

/**
 * @brief Print a given message on the given log level.
 * 
 */
#define LIBOS_LOG_PRINT(level, ...) libos_log_print(level, __TAG, __VA_ARGS__);

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

typedef void (*libos_log_print_fn)(const char* message, size_t message_size);

/**
 * @brief Info container for a log module with a specific name.
 * 
 */
typedef struct libos_log_module
{
    int level;          ///< The minimum log level of the log entries.
    const char* name;   ///< The component name of the current file that is included with every log entry.
} libos_log_module_t;

/**
 * @brief Internal API for logging log entries.
 * 
 * @param level The log entry log level.
 * @param module The module for which this log entry is.
 * @param format The printf format of the log entry
 * @param ... The variable arguments for the printf log entry.
 */
void libos_log_print(int level, const libos_log_module_t *module, const char* format, ...);

/**
 * @brief Initialize the logging subsystem (only needs to be done in main once!).
 * 
 * @param[in] print_fn The function to take a text string and send it to the output.
 */
void libos_log_init(libos_log_print_fn print_fn, const char* print_buffer, size_t print_buffer_size);

#ifdef __cplusplus
} // extern "C"
#endif // __cplusplus

#endif // LIBOS_PLATFORM_LOG_H
