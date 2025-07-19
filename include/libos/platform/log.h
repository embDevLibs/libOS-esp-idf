/**
 * @file log.h
 * @brief Implements the logging endpoints for the libOS logging API.
 * 
 * @details
 * This header implements the general purpose logging module interface defined
 * in the libos/log.h header. The module implements the module definition macro
 * as a static definition of a libos_log_module_t structure. This contains the
 * logging level to support a higher minimum log level defined per file. Only
 * one instance per compilation unit is allowed (it is marked static). Calling
 * print without first defining a module will result in compilation problems.
 * 
 * Since the module is build on top of ESP-IDF own logging functionality, you
 * can use the usual tools for ESP-IDF to configure which of the log statements
 * are compiled into the final binary. And you can use the dynamic configuration
 * at runtime to decide if more or less logging is required for a module. The
 * 'tag' in ESP-IDF terms is the same as the name of the module in libOS terms.
 *
 */

#pragma once
#include "esp_log_level.h"
#ifndef LIBOS_PLATFORM_LOG_H
#define LIBOS_PLATFORM_LOG_H

#include <stddef.h>

#include "esp_log.h"

#define LIBOS_LOG_LEVEL_MIN CONFIG_LOG_MAXIMUM_LEVEL

/**
 * @brief The log level for a error message.
 * 
 */
#define LIBOS_LOG_LEVEL_ERR ESP_LOG_ERROR

/**
 * @brief The log level for a warning message.
 * 
 */
#define LIBOS_LOG_LEVEL_WRN ESP_LOG_WARN

/**
 * @brief The log level for a info message.
 * 
 */
#define LIBOS_LOG_LEVEL_INF ESP_LOG_INFO

/**
 * @brief The log level for a debug message.
 * 
 */
#define LIBOS_LOG_LEVEL_DBG ESP_LOG_DEBUG

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
#define LIBOS_LOG_PRINT(log_level, ...) do { if ((int)(log_level) >= (int)__TAG.level) { ESP_LOG_LEVEL_LOCAL(log_level, __TAG.name, ##__VA_ARGS__); } } while(0)

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/**
 * @brief Info container for a log module with a specific name.
 * 
 */
typedef struct libos_log_module
{
    esp_log_level_t level;  ///< The minimum log level of the log entries.
    const char* name;       ///< The component name of the current file that is included with every log entry.
} libos_log_module_t;

#ifdef __cplusplus
} // extern "C"
#endif // __cplusplus

#endif // LIBOS_PLATFORM_LOG_H
