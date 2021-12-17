cmake_minimum_required(VERSION 3.14)
project(Stdutils 
    VERSION 1.0
    LANGUAGES CXX
)

################################################################################

include(GNUInstallDirs)

################################################################################

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

################################################################################

set(Stdutils_STANDALONE_PROJECT OFF)
if (CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
    set(Stdutils_STANDALONE_PROJECT ON)
endif()

option(BUILD_TESTS "Build tests." ${Stdutils_STANDALONE_PROJECT})

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

# Check if C++20 standard is available.
if("cxx_std_20" IN_LIST CMAKE_CXX_COMPILE_FEATURES)
    message(STATUS "Using C++20 standard")
    set(CMAKE_CXX_STANDARD 20)
else()
    message(FATAL_ERROR "Requested STDUTILS_CXX_STANDARD \"20\" not supported by provided C++ compiler")
endif()

# Set release compiler options.
if (CMAKE_CXX_COMPILER_ID MATCHES "GNU")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wpedantic -Wall -Wshadow -Wextra -Wno-missing-braces -Werror -Wno-error=strict-overflow -Wno-maybe-uninitialized -std=c++2a")
endif()
if (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wpedantic -Wall -Wshadow -Wextra -Wno-missing-braces -Werror -Wno-error=strict-overflow -std=c++2a")
endif()
if(MSVC)
    set(CMAKE_CXX_FLAGS_RELEASE "/DNDEBUG /W4 /WX /wd4100 /GR /EHsc /MT /O2 /std:c++latest")
endif()

# Set debugging compiler options.
if (CMAKE_CXX_COMPILER_ID MATCHES "GNU")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wpedantic -Wall -Wshadow -Wextra -Wno-missing-braces -Werror -Wno-error=strict-overflow -Wno-maybe-uninitialized -std=c++2a")
endif()
if (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wpedantic -Wall -Wshadow -Wextra -Wno-missing-braces -Werror -Wno-error=strict-overflow -std=c++2a")
endif()
if(MSVC)
    set(CMAKE_CXX_FLAGS_DEBUG "/EHsc /W4 /WX /wd4100 /MT /GR /Zi /Od /std:c++latest")
endif()

################################################################################

add_library(stdutils INTERFACE)
add_library(stdutils::stdutils ALIAS stdutils)

target_include_directories(stdutils INTERFACE
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

install(TARGETS stdutils 
    EXPORT stdutilsTargets
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/stdutils DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

install(EXPORT stdutilsTargets
    FILE stdutilsTargets.cmake
    NAMESPACE stdutils::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/stdutils
)

include(CMakePackageConfigHelpers)

write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/stdutilsConfigVersion.cmake"
    COMPATIBILITY AnyNewerVersion
)

configure_package_config_file(${CMAKE_CURRENT_SOURCE_DIR}/cmake/stdutilsConfig.cmake.in
    "${CMAKE_CURRENT_BINARY_DIR}/stdutilsConfig.cmake"
    INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/stdutils
)
install(FILES 
    "${CMAKE_CURRENT_BINARY_DIR}/stdutilsConfig.cmake" 
    "${CMAKE_CURRENT_BINARY_DIR}/stdutilsConfigVersion.cmake"
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/stdutils
)

################################################################################

if(BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()
