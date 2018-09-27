cmake_minimum_required(VERSION 3.4.3)
project(stdutils CXX)

include(ExternalProject)
find_package(Git)

# Enforce C++14 standard.
set(CMAKE_CXX_STANDARD 14)

# Export compile commands.
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Set default MSVC compiler options to avoid D9025 error.
if(MSVC)
    set(CMAKE_CXX_FLAGS "/DWIN32 /D_WINDOWS")
endif()

# Set release compiler options.
if (CMAKE_CXX_COMPILER_ID MATCHES "Clang" OR CMAKE_CXX_COMPILER_ID MATCHES "GNU")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_RELEASE} -Wpedantic -Wall -Wshadow -Wextra -Wno-missing-braces -Werror -Wno-error=strict-overflow")
endif()
if(MSVC)
    set(CMAKE_CXX_FLAGS_RELEASE "/DNDEBUG /std:c++14 /W4 /WX /wd4100 /GR /EHsc /MT /O2")
endif()

# Set debugging compiler options.
if (CMAKE_CXX_COMPILER_ID MATCHES "Clang" OR CMAKE_CXX_COMPILER_ID MATCHES "GNU")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wpedantic -Wall -Wshadow -Wextra -Wno-missing-braces -Werror -Wno-error=strict-overflow")
endif()
if(MSVC)
    set(CMAKE_CXX_FLAGS_DEBUG "/std:c++14 /EHsc /W4 /WX /wd4100 /MT /GR /Zi /Od")
endif()

# Create stdutils interface library.
add_library(stdutils_config INTERFACE)
target_include_directories(stdutils_config INTERFACE
    $<BUILD_INTERFACE:
        ${CMAKE_CURRENT_SOURCE_DIR}/include
    >
)

install(
    DIRECTORY include/stdutils
    DESTINATION include
    FILES_MATCHING PATTERN "*.h"
)

# Enable testing.
option(BUILD_TESTS "Build tests." ON)

if(BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()
