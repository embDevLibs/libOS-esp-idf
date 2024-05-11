/**
 * @file error.h
 * @brief Standard error codes and error code helpers.
 * 
 * @details
 * This header file implements the interface described in libOS/error.h. It
 * provides the macro definition for several error codes and also defines a
 * typedef for the 'type' of the error value itself.
 * Because this is the standard library implementation the error value is
 * just `int`, success is 0, and the error codes map to a E<type> macro.
 * Except LIBOS_ERR_FAIL and LIBOS_ERR_INVALID_STATE.
 * 
 * LIBOS_ERR_FAIL evaluates to -1 as there no such equivalent in the errno
 * header. The standard defines the errno macros to be positive integers so
 * assigning a negative integer should be safe.
 * 
 * LIBOS_ERR_INVALID_STATE is defined to -2 for the same reason as
 * LIBOS_ERR_FAIL.
 */

#pragma once
#ifndef LIBOS_PLATFORM_ERROR_H
#define LIBOS_PLATFORM_ERROR_H

#include <errno.h>

// Error codes

/**
 * @brief All OK
 * 
 */
#define LIBOS_ERR_OK ((libos_err_t)0)

/**
 * @brief General purpose/unkown failure
 * 
 */
#define LIBOS_ERR_FAIL ((libos_err_t)-1)

/**
 * @brief Could not allocate the memory required for the request.
 * 
 */
#define LIBOS_ERR_NO_MEM ((libos_err_t)ENOMEM)

/**
 * @brief A invalid argument was given to the function.
 * 
 */
#define LIBOS_ERR_INVALID_ARG ((libos_err_t)EINVAL)

/**
 * @brief The function does not support being used (as in never, if data is invalid state, use either LIBOS_ERR_INVALID_ARG, or LIBOS_ERR_INVALID_STATE).
 * 
 */
#define LIBOS_ERR_NOTSUP ((libos_err_t)ENOTSUP)

/**
 * @brief The resource was busy.
 * 
 */
#define LIBOS_ERR_BUSY ((libos_err_t)EBUSY)

/**
 * @brief The operation took too long and was cancelled as the timeout elapsed.
 * 
 */
#define LIBOS_ERR_TIMEOUT ((libos_err_t)ETIMEDOUT)

// Non POSIX standard error codes
// POSIX requires error codes to be positive anyway, and -1 is often general purpose 'error'.

/**
 * @brief The function normally supports the operation but the data that is being worked (usually a object of some sorts) is in a invalid state for this operation (but itself might still be valid).
 * 
 */
#define LIBOS_ERR_INVALID_STATE ((libos_err_t)-2)

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

// Error type

typedef int libos_err_t;

#ifdef __cplusplus
} // extern "C"
#endif // __cplusplus

#endif // LIBOS_PLATFORM_ERROR_H
