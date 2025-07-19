option(LIBOS_FREERTOS_SUBDIR_FOR_INCLUDE "Is FreeRTOS in a subdir of the include path?" OFF)
option(LIBOS_FREERTOS_TARGET_NAME "What is the CMake Target name of FreeRTOS to also receive those header files." "freertos_kernel")

set(C_STANDARD 99)

if(NOT TARGET libos) # Prevent multiple instances if other libraries already provide the libos library
  include(FetchContent)
  FetchContent_Declare(
    libos
    GIT_REPOSITORY git@github.com:embDevLibs/libos.git
    GIT_TAG main
  )
  FetchContent_MakeAvailable(libos)
endif()

set(LIB_SRCS
    "${CMAKE_CURRENT_SOURCE_DIR}/include/libos/platform/concurrent/mutex.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/libos/platform/bits.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/libos/platform/error.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/libos/platform/log.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/libos/platform/time.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/concurrent/mutex.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/time.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/log.c"
)

add_library(${PROJECT_NAME} STATIC "${LIB_SRCS}")
target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")

target_link_libraries(${PROJECT_NAME} PUBLIC libos)

if (NOT "${LIBOS_FREERTOS_TARGET_NAME}" STREQUAL "")
  target_link_libraries(${PROJECT_NAME} PUBLIC ${LIBOS_FREERTOS_TARGET_NAME})
endif()

if(${LIBOS_FREERTOS_SUBDIR_FOR_INCLUDE})
    target_compile_definitions(${PROJECT_NAME} PUBLIC LIBOS_FREERTOS_SUBDIR_FOR_INCLUDE=1)
else()
    target_compile_definitions(${PROJECT_NAME} PUBLIC LIBOS_FREERTOS_SUBDIR_FOR_INCLUDE=0)
endif()

