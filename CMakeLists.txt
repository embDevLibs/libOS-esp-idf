cmake_minimum_required(VERSION 3.20)
project(libOS-api C)

set(C_STANDARD 99)

option(LIBOS_FREERTOS_SUBDIR_FOR_INCLUDE "Is FreeRTOS in a subdir of the include path?" OFF)
option(LIBOS_FREERTOS_TARGET_NAME "What is the CMake Target name of FreeRTOS to also receive those header files." "freertos_kernel")

if(NOT TARGET libOS-api) # Prevent multiple instances if other libraries already provide the libos library
  include(FetchContent)
  FetchContent_Declare(
    libOS
    GIT_REPOSITORY git@github.com:embDevLibs/libos.git
    GIT_TAG main
  )
  FetchContent_MakeAvailable(libOS)
endif()

set(LIB_SRCS
    "${CMAKE_CURRENT_SOURCE_DIR}/src/time.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/log.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/concurrency/mutex.c"
)

add_library(libOS-platform STATIC "${LIB_SRCS}")
target_include_directories(libOS-platform PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")
target_link_libraries(libOS-platform PUBLIC ${LIBOS_FREERTOS_TARGET_NAME})
target_link_libraries(libOS-platform PUBLIC libOS-api)

add_library(libOS INTERFACE)

target_link_libraries(libOS INTERFACE libOS-platform)
target_link_libraries(libOS INTERFACE libOS-api)

if(${LIBOS_FREERTOS_SUBDIR_FOR_INCLUDE})
    target_compile_definitions(libOS-platform PUBLIC LIBOS_FREERTOS_SUBDIR_FOR_INCLUDE=1)
else()
    target_compile_definitions(libOS-platform PUBLIC LIBOS_FREERTOS_SUBDIR_FOR_INCLUDE=0)
endif()
