/**
 * @file error.h
 * @brief Standard error codes and error code helpers.
 * 
 * @details
 * This header file implements the interface described in libOS/error.h. It
 * provides the macro definition for several error codes and also defines a
 * typedef for the 'type' of the error value itself.
 * This is based on the ESP-IDF header `esp_err.h`. Most error codes are taken
 * from there. There are exceptions, and they are taken from either the POSIX
 * header errno, or a made up value that doesn't conflict with existing values.
 *
 * Exception(s):
 * - LIBOS_ERR_BUSY (POSIX value)
 *
 */

// IWYU pragma: private; include "libos/error.h"

#pragma once
#ifndef LIBOS_PLATFORM_ERROR_H
#define LIBOS_PLATFORM_ERROR_H

#include <errno.h>
#include "esp_err.h"

// Error codes

/**
 * @brief All OK
 * 
 */
#define LIBOS_ERR_OK ((libos_err_t)ESP_OK)

/**
 * @brief General purpose/unkown failure
 * 
 */
#define LIBOS_ERR_FAIL ((libos_err_t)ESP_FAIL)

/**
 * @brief Could not allocate the memory required for the request.
 * 
 */
#define LIBOS_ERR_NO_MEM ((libos_err_t)ESP_ERR_NO_MEM)

/**
 * @brief A invalid argument was given to the function.
 * 
 */
#define LIBOS_ERR_INVALID_ARG ((libos_err_t)ESP_ERR_INVALID_ARG)

/**
 * @brief The function does not support being used (as in never, if data is invalid state, use either LIBOS_ERR_INVALID_ARG, or LIBOS_ERR_INVALID_STATE).
 * 
 */
#define LIBOS_ERR_NOTSUP ((libos_err_t)ESP_ERR_NOT_SUPPORTED)

/**
 * @brief The resource was busy.
 * 
 */
#define LIBOS_ERR_BUSY ((libos_err_t)EBUSY) // POSIX value

/**
 * @brief The operation took too long and was cancelled as the timeout elapsed.
 * 
 */
#define LIBOS_ERR_TIMEOUT ((libos_err_t)ESP_ERR_TIMEOUT)

// Non POSIX standard error codes
// POSIX requires error codes to be positive anyway, and -1 is often general purpose 'error'.

/**
 * @brief The function normally supports the operation but the data that is being worked (usually a object of some sorts) is in a invalid state for this operation (but itself might still be valid).
 * 
 */
#define LIBOS_ERR_INVALID_STATE ((libos_err_t)ESP_ERR_INVALID_STATE)

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

// Error type

typedef esp_err_t libos_err_t;

#ifdef __cplusplus
} // extern "C"
#endif // __cplusplus

#endif // LIBOS_PLATFORM_ERROR_H
