cmake_minimum_required(VERSION 3.14)
project(Stdutils 
    VERSION 1.0
    LANGUAGES CXX
)

################################################################################

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

################################################################################

option(BUILD_TESTS "Build tests." ON)

################################################################################

# Set installation directory.
if (WIN32)
    if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
        set(CMAKE_INSTALL_PREFIX $ENV{USERPROFILE} CACHE PATH "USERPROFILE" FORCE)
    endif()
else()
    if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
        set(CMAKE_INSTALL_PREFIX $ENV{HOME} CACHE PATH "HOME" FORCE)
    endif()
endif()

################################################################################

# Option to override which C++ standard to use
set(STDUTILS_CXX_STANDARD DETECT CACHE STRING "Override the default CXX_STANDARD to compile with.")
set_property(CACHE STDUTILS_CXX_STANDARD PROPERTY STRINGS DETECT 14 17 20)

option(STDUTILS_ENABLE_CONCEPTS "Try to enable concepts support by giving extra flags." ON)

# Decide on the standard to use
if(STDUTILS_CXX_STANDARD STREQUAL "17")
    if("cxx_std_17" IN_LIST CMAKE_CXX_COMPILE_FEATURES)
        message(STATUS "Using C++17 standard")
        set(CMAKE_CXX_STANDARD 17)
    else()
        message(FATAL_ERROR "Requested STDUTILS_CXX_STANDARD \"17\" not supported by provided C++ compiler")
    endif()
elseif(STDUTILS_CXX_STANDARD STREQUAL "14")
    if("cxx_std_14" IN_LIST CMAKE_CXX_COMPILE_FEATURES)
        message(STATUS "Using C++14 standard")
        set(CMAKE_CXX_STANDARD 14)
    else()
        message(FATAL_ERROR "Requested STDUTILS_CXX_STANDARD \"14\" not supported by provided C++ compiler")
    endif()
elseif(STDUTILS_CXX_STANDARD STREQUAL "20")
    if("cxx_std_20" IN_LIST CMAKE_CXX_COMPILE_FEATURES)
        message(STATUS "Using C++20 standard")
        set(CMAKE_CXX_STANDARD 20)
    else()
        message(FATAL_ERROR "Requested STDUTILS_CXX_STANDARD \"20\" not supported by provided C++ compiler")
    endif()
else()
    if("cxx_std_20" IN_LIST CMAKE_CXX_COMPILE_FEATURES)
        set(CMAKE_CXX_STANDARD 20)
        message(STATUS "Detected support for C++20 standard")
    elseif("cxx_std_17" IN_LIST CMAKE_CXX_COMPILE_FEATURES)
        set(CMAKE_CXX_STANDARD 17)
        message(STATUS "Detected support for C++17 standard")
    elseif("cxx_std_14" IN_LIST CMAKE_CXX_COMPILE_FEATURES)
        set(CMAKE_CXX_STANDARD 14)
        message(STATUS "Detected support for C++14 standard")
    else()
        message(FATAL_ERROR "Cannot detect CXX_STANDARD of C++14 or newer.")
    endif()
endif()

if(STDUTILS_ENABLE_CONCEPTS)
    if(CMAKE_CXX_STANDARD STREQUAL "20")
        include(CheckCXXCompilerFlag)
        CHECK_CXX_COMPILER_FLAG("-fconcepts" COMPILER_SUPPORTS_FCONCEPTS)
        if(COMPILER_SUPPORTS_FCONCEPTS)
            message(STATUS "-- Using \"-fconcepts\" to enable concepts support")
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fconcepts")
        else()
            CHECK_CXX_COMPILER_FLAG("-fconcepts-ts" COMPILER_SUPPORTS_FCONCEPTS_TS)
            if(COMPILER_SUPPORTS_FCONCEPTS)
                message(STATUS "-- Using \"-fconcepts-ts\" to enable concepts support")
                set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fconcepts-ts")
            endif()
        endif()
        # Otherwise, it's possible that the compiler supports concepts without flags,
        # but if it doesn't, they just won't be used, which is fine
    endif()
endif()

# Export compile commands.
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(WIN32)
    option(BUILD_SHARED_LIBS "Compile shared libraries." OFF)
else()
    option(BUILD_SHARED_LIBS "Compile shared libraries." ON)
endif()

# Set default MSVC compiler options to avoid D9025 error.
if(MSVC)
    set(CMAKE_CXX_FLAGS "/DWIN32 /D_WINDOWS")
endif()

# Set release compiler options.
if (CMAKE_CXX_COMPILER_ID MATCHES "GNU")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wpedantic -Wall -Wshadow -Wextra -Wno-missing-braces -Werror -Wno-error=strict-overflow -Wno-maybe-uninitialized")
endif()
if (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wpedantic -Wall -Wshadow -Wextra -Wno-missing-braces -Werror -Wno-error=strict-overflow")
endif()
if(MSVC)
    set(CMAKE_CXX_FLAGS_RELEASE "/DNDEBUG /W4 /WX /wd4100 /GR /EHsc /MT /O2")
endif()

# Set debugging compiler options.
if (CMAKE_CXX_COMPILER_ID MATCHES "GNU")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wpedantic -Wall -Wshadow -Wextra -Wno-missing-braces -Werror -Wno-error=strict-overflow -Wno-maybe-uninitialized")
endif()
if (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wpedantic -Wall -Wshadow -Wextra -Wno-missing-braces -Werror -Wno-error=strict-overflow")
endif()
if(MSVC)
    set(CMAKE_CXX_FLAGS_DEBUG "/EHsc /W4 /WX /wd4100 /MT /GR /Zi /Od")
endif()

################################################################################

add_library(stdutils INTERFACE)
target_include_directories(stdutils INTERFACE
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
)

################################################################################

install(TARGETS stdutils EXPORT StdutilsTargets
  INCLUDES DESTINATION include
)

install(EXPORT StdutilsTargets
    FILE StdutilsTargets.cmake
    NAMESPACE Stdutils::
    DESTINATION lib/cmake/stdutils
)

export(TARGETS stdutils
    NAMESPACE Stdutils::
    FILE StdutilsTargets.cmake
)

install(DIRECTORY include/stdutils DESTINATION include)

include(CMakePackageConfigHelpers)
configure_package_config_file(cmake/StdutilsConfig.cmake.in
  ${CMAKE_CURRENT_BINARY_DIR}/StdutilsConfig.cmake
  INSTALL_DESTINATION lib/cmake/stdutils
)
write_basic_package_version_file(${CMAKE_CURRENT_BINARY_DIR}/StdutilsConfigVersion.cmake
  COMPATIBILITY SameMajorVersion
)

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/StdutilsConfig.cmake ${CMAKE_CURRENT_BINARY_DIR}/StdutilsConfigVersion.cmake
    DESTINATION lib/cmake/stdutils
)

################################################################################

if(BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()
