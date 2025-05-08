#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

#if LIBOS_FREERTOS_SUBDIR_FOR_INCLUDE==1
#include <freertos/FreeRTOS.h>
#include <freertos/semphr.h>
#else // LIBOS_FREERTOS_SUBDIR_FOR_INCLUDE==1
#include <FreeRTOS.h>
#include <semphr.h>
#endif // LIBOS_FREERTOS_SUBDIR_FOR_INCLUDE==1

#include "libos/error.h"
#include "libos/concurrency/mutex.h"

libos_err_t libos_mutex_lock(libos_mutex_handle_t handle, libos_time_t timeout)
{
    LIBOS_ERR_RET_ARG_NOT_NULL(handle);
    TimerTick_t ticks = libos_time_to_ticks(timeout);

    if (handle->is_recursive)
    {
        xSemaphoreTakeRecursive(handle->mutex_handle, ticks);
    }
    else
    {
        xSemaphoreTake(handle->mutex_handle, ticks);
    }

    return LIBOS_ERR_OK;
}

libos_err_t libos_mutex_unlock(libos_mutex_handle_t handle)
{
    LIBOS_ERR_RET_ARG_NOT_NULL(handle);

    if (handle->is_recursive)
    {
        xSemaphoreGiveRecursive(handle->mutex_handle);
    }
    else
    {
        xSemaphoreGive(handle->mutex_handle);
    }

    return LIBOS_ERR_OK;
}

#if LIBOS_MUTEX_ENABLE_DYNAMIC_ALLOCATION==1

libos_err_t libos_mutex_create_dynamic(libos_mutex_handle_t *handle)
{
    LIBOS_ERR_RET_ARG_NOT_NULL(handle);

    libos_mutex_handle_t new_handle = (libos_mutex_handle_t)malloc(sizeof(libos_mutex_t));
    if (new_handle == NULL)
    {
        return LIBOS_ERR_NO_MEM;
    }

    new_handle->mutex_handle = xSemaphoreCreateMutex();
    if (new_handle->mutex_handle == NULL)
    {
        free(new_handle);
        return LIBOS_ERR_NO_MEM;
    }

    new_handle->is_static = false;
    new_handle->is_recursive = false;

    *handle = new_handle;

    return LIBOS_ERR_OK;
}

#if LIBOS_MUTEX_ENABLE_RECURSIVE==1

libos_err_t libos_mutex_create_recursive_dynamic(libos_mutex_handle_t *handle)
{
    LIBOS_ERR_RET_ARG_NOT_NULL(handle);

    libos_mutex_handle_t new_handle = (libos_mutex_handle_t)malloc(sizeof(libos_mutex_t));
    if (new_handle == NULL)
    {
        return LIBOS_ERR_NO_MEM;
    }

    new_handle->mutex_handle = xSemaphoreCreateRecursiveMutex();
    if (new_handle->mutex_handle == NULL)
    {
        free(new_handle);
        return LIBOS_ERR_NO_MEM;
    }

    new_handle->is_static = false;
    new_handle->is_recursive = true;

    *handle = new_handle;

    return LIBOS_ERR_OK;
}

#endif // LIBOS_MUTEX_ENABLE_RECURSIVE==1

#endif // LIBOS_MUTEX_ENABLE_DYNAMIC_ALLOCATION==1

#if LIBOS_MUTEX_ENABLE_STATIC_ALLOCATION==1

libos_err_t libos_mutex_create_static(libos_mutex_t *mutex, libos_mutex_handle_t *handle)
{
    LIBOS_ERR_RET_ARG_NOT_NULL(mutex);
    LIBOS_ERR_RET_ARG_NOT_NULL(handle);

    mutex->mutex_handle = xSemaphoreCreateMutexStatic(&(mutex->mutex));
    if (mutex->mutex_handle == NULL)
    {
        return LIBOS_ERR_NO_MEM;
    }

    mutex->is_static = true;
    mutex->is_recursive = false;

    *handle = mutex;

    return LIBOS_ERR_OK;

}

#if LIBOS_MUTEX_ENABLE_RECURSIVE==1

libos_err_t libos_mutex_create_recursive_static(libos_mutex_t *mutex, libos_mutex_handle_t *handle)
{
    LIBOS_ERR_RET_ARG_NOT_NULL(mutex);
    LIBOS_ERR_RET_ARG_NOT_NULL(handle);

    mutex->mutex_handle = xSemaphoreCreateRecursiveMutexStatic(&(mutex->mutex));
    if (mutex->mutex_handle == NULL)
    {
        return LIBOS_ERR_NO_MEM;
    }

    mutex->is_static = true;
    mutex->is_recursive = true;

    *handle = mutex;

    return LIBOS_ERR_OK;
}

#endif // LIBOS_MUTEX_ENABLE_RECURSIVE==1

#endif // LIBOS_MUTEX_ENABLE_STATIC_ALLOCATION==1

void libos_mutex_delete(libos_mutex_handle_t handle)
{
    vSemaphoreDelete(handle->mutex_handle);
    if (!handle->is_static)
    {
        free(handle);
    }
}