# libOS-freertos
Implements the libOS APIs based on the FreeRTOS kernel.

LibOS has the goal to create a set of common API's that can be used on any system.
Even a bare metal system or RTOS could be a target platform.
This implementation is to use the FreeRTOS kernel to implement the API's defined in libOS.

For the more about libOS see, the [libOS](https://github.com/embDevLibs/libOS) repository.

# Usage
This implementation can be used in two ways.
One is by using the pure CMake system.
This is by using FetchContent, or ExternalProject or just a plain git submodule with add_subdirectory to fetch the sources.
Make sure that if you need to setup any configuration, you pass this along using the correct mechanism.
Then, when added to cmake, you can just use the target 'libos-freertos' to link against.
A copy of libOS will be downloaded using FetchContent if the libOS target isn't already present.

The second method is by the using the IDF Component manager from Espressif.
This method is aimed specifically as the ESP-IDF development ecosystem.
You can use the regular dependency system to get your copy of the library.
If used this way, no further configuration is needed.

# Limitations
Since FreeRTOS doesn't implement a logging system, the logging system is implemented based on top of printf.
This is functional on most systems, but may not be enough for some.

FreeRTOS must also be located in one of 2 places.
Either in 'FreeRTOS.h', or in 'freertos/FreeRTOS.h'.
This can be selected using 'LIBOS_FREERTOS_SUBDIR_FOR_INCLUDE'.

# Configuration
The defines usually set by the platform to tell libOS what is supported is taken directly from FreeRTOS.
`LIBOS_MUTEX_ENABLE_DYNAMIC_ALLOCATION` is defined as `configSUPPORT_DYNAMIC_ALLOCATION`.
And `LIBOS_MUTEX_ENABLE_RECURSIVE` is defined `configUSE_RECURSIVE_MUTEXES`.
This means that no additional configuration has to be done, besides some build-system & include path configuration.
