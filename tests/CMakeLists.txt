cmake_minimum_required(VERSION 3.14)
project(Stdutils_tests CXX)

include(FetchContent)
FetchContent_Declare(
  googletest
  # Specify the commit you depend on and update it regularly.
  URL https://github.com/google/googletest/archive/refs/heads/main.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

if(NOT TARGET Stdutils::Stdutils)
  find_package(stdutils REQUIRED)
endif()

# Copy *.inp files to build directory.
file(GLOB INP_FILES RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.inp")

foreach(inp_file_name ${INP_FILES})
    file(COPY "${inp_file_name}" DESTINATION "${PROJECT_BINARY_DIR}/tests")
endforeach()

function(add_stdutils_test name)
    add_executable(${name} ${name}.cpp)
    target_link_libraries (
        ${name} 
        Stdutils::Stdutils
        gtest_main
    ) 
    add_test(NAME ${name} COMMAND ${name})
endfunction()

set(PROGRAMS 
    test_assert
    test_stream
    test_string
)

foreach(program ${PROGRAMS})
    add_stdutils_test(${program})
endforeach()
