cmake_minimum_required(VERSION 3.13)
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
set(BUILD_GMOCK OFF)

if(NOT TARGET stdutils::stdutils)
  find_package(stdutils REQUIRED)
endif()

function(add_stdutils_test name)
    add_executable(${name} ${name}.cpp)
    target_link_libraries(
        ${name} 
        stdutils::stdutils
        gtest_main
    ) 
    target_compile_options(
        ${name}
        PRIVATE
        "$<$<CONFIG:Debug>:${Stdutils_CXX_FLAGS_DEBUG}>"
        "$<$<CONFIG:Release>:${Stdutils_CXX_FLAGS_RELEASE}>"
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
