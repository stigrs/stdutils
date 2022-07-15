# Stdutils 
[![CMake](https://github.com/stigrs/stdutils/actions/workflows/cmake.yml/badge.svg?branch=master)](https://github.com/stigrs/stdutils/actions/workflows/cmake.yml)

Stdutils extends the C++ standard library with a few utility methods.

## Licensing

Stdutils is released under the [MIT](LICENSE) license.

## Usage of Third Party Libraries

This project makes use of [GoogleTest](https://github.com/google/googletest). 
Please see the [ThirdPartyNotices.txt](ThirdPartyNotices.txt) file for details 
regarding the licensing of GoogleTest.

## Quick Start

### Requirements

* [CMake](https://cmake.org) 3.13

### Supported Compilers

| Compiler      | Versions Tested |
|:--------------|----------------:|
| GCC           | 9, 10           |
| Clang         | 10, 11, 12      |
| Visual Studio | VS2019, VS2022  |
| XCode         | 13.0            |

### Obtaining the Source Code

The source code can be obtained from

        git clone git@github.com:stigrs/stdutils.git

### Building the Software

These steps assumes that the source code of this repository has been cloned
into a directory called `stdutils`.

1. Create a directory to contain the build outputs:

        cd stdutils
        mkdir build
        cd build

2. Configure CMake to use the compiler of your choice (you can see a list by
   running `cmake --help`):

        cmake -G "Visual Studio 16 2019" ..

3. Build the software (in this case in the Release configuration):

        cmake --build . --config Release

4. Run the test suite:

        ctest -C Release

5. Install the software:

        cmake --build . --config Release --target install

   All tests should pass, indicating that your platform is fully supported.
