cmake_minimum_required(VERSION 3.20)

set(LIB_SRCS
    "${CMAKE_CURRENT_SOURCE_DIR}/include/libos/platform/concurrent/mutex.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/libos/platform/bits.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/libos/platform/error.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/libos/platform/log.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/libos/platform/time.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/concurrent/mutex.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/time.c"
)

idf_component_register(SRCS ${LIB_SRCS}
                       INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/include"
                       REQUIRES libos esp_timer freertos)
