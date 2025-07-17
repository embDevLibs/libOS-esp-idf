set(LIB_SRCS
    "${CMAKE_CURRENT_SOURCE_DIR}/include/libos/platform/concurrent/mutex.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/libos/platform/error.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/libos/platform/log.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/libos/platform/time.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/concurrent/mutex.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/time.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/log.c"
)

idf_component_register(SRCS ${LIB_SRCS}
                       INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/include"
                       REQUIRES libos freertos)

# This is given in the ESP-IDF platform.
target_compile_definitions(${COMPONENT_LIB} PUBLIC LIBOS_FREERTOS_SUBDIR_FOR_INCLUDE=1)
