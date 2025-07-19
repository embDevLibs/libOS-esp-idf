# libOS-esp-idf
Implements the libOS APIs based on the ESP-IDF platform.

LibOS has the goal to create a set of common API's that can be used on any system.
Even a bare metal system or RTOS could be a target platform.
This implementation is to use the ESP-IDF modules to implement the API's defined in libOS.

For the more about libOS see, the [libOS](https://github.com/embDevLibs/libOS) repository.

# Usage
The component can be used by using the component manager that comes with ESP-IDF.
This will also automatically install libos as a dependency of this package.

# Configuration
The configuration is based on the libOS configuration.
If that configuration is not available, it will fall back to the defines provided by ESP-IDF, `LIBOS_MUTEX_ENABLE_DYNAMIC_ALLOCATION` is then defined as `configSUPPORT_DYNAMIC_ALLOCATION` for example.
And `LIBOS_MUTEX_ENABLE_RECURSIVE` is defined `configUSE_RECURSIVE_MUTEXES`.
