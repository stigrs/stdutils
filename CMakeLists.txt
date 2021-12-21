cmake_minimum_required(VERSION 3.13)
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

option(Stdutils_BUILD_TESTS "Build tests." ${Stdutils_STANDALONE_PROJECT})

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

# Set compiler options.
if (CMAKE_CXX_COMPILER_ID MATCHES "GNU")
    set(Stdutils_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wpedantic -Wall -Wshadow -Wextra -Wno-missing-braces -Werror -Wno-error=strict-overflow -Wno-maybe-uninitialized -std=c++2a")
    set(Stdutils_CXX_FLAGS_DEBUG "${Stdutils_CXX_FLAGS} -g")
    set(Stdutils_CXX_FLAGS_RELEASE "${Stdutils_CXX_FLAGS} -O3")
endif()
if (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    set(Stdutils_CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wpedantic -Wall -Wshadow -Wextra -Wno-missing-braces -Werror -Wno-error=strict-overflow -std=c++2a")
    set(Stdutils_CXX_FLAGS_DEBUG "${Stdutils_CXX_FLAGS} -g")
    set(Stdutils_CXX_FLAGS_RELEASE "${Stdutils_CXX_FLAGS} -O3")
endif()
if(MSVC)
    set(Stdutils_CXX_FLAGS "/DWIN32 /D_WINDOWS /W4 /WX /wd4100 /GR /EHsc /MT /std:c++latest")
    set(Stdutils_CXX_FLAGS_DEBUG "${Stdutils_CXX_FLAGS} /Zi /Od")
    set(Stdutils_CXX_FLAGS_RELEASE "${Stdutils_CXX_FLAGS} /DNDEBUG /O2")
endif()
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

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

if(Stdutils_BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()
