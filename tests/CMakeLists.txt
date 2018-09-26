cmake_minimum_required(VERSION 3.4.3)
project(stdutils_tests CXX)

list(APPEND CATCH_CMAKE_ARGS
    "-DCMAKE_INSTALL_PREFIX=${CMAKE_BINARY_DIR}/external"
    "-DCATCH_BUILD_TESTING=OFF"
)

if(GIT_FOUND)
    # Add catch
    ExternalProject_Add(
        catch2
        PREFIX ${CMAKE_BINARY_DIR}/catch
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG v2.3.0
        CMAKE_ARGS ${CATCH_CMAKE_ARGS}
        LOG_DOWNLOAD 1
        UPDATE_DISCONNECTED 1
    )
else()
    # Assume catch is installed in a system directory
    add_custom_target(catch2)
endif()

# Prepare "Catch" library for other executables.
add_library(Catch2 INTERFACE)
target_include_directories(
    Catch2 INTERFACE 
    ${CMAKE_BINARY_DIR}/external/include
)

# Create the main executable for each test.
add_library(test_catch2 STATIC test.cpp)
target_link_libraries(
    test_catch2
    Catch2
)

add_dependencies(test_catch2 catch2)

function(add_stdutils_test name)
    add_executable(${name} ${name}.cpp)
    target_link_libraries (
        ${name} 
        test_catch2
        stdutils_config
    ) 
    add_dependencies(${name} Catch2)
    add_test(NAME ${name} COMMAND ${name})
endfunction()

set(PROGRAMS 
    test_format
    test_stream
    test_string
)

foreach(program ${PROGRAMS})
    add_stdutils_test(${program})
endforeach()
