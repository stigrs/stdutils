# Stdutils 
[![Build Status](https://dev.azure.com/stigrs0020/stigrs/_apis/build/status/stigrs.stdutils?branchName=master)](https://dev.azure.com/stigrs0020/stigrs/_build/latest?definitionId=7&branchName=master)

Stdutils extends the C++ standard library with a few utility methods.

## Code of Conduct

This project has adopted the [Covenant Code of Conduct](CODE_OF_CONDUCT.md).

## Licensing

Stdutils is released under the [MIT](LICENSE) license.

## Usage of Third Party Libraries

This project makes use of the [Catch2](https://github.com/catchorg/Catch2)
testing library. Please see the [ThirdPartyNotices.txt](ThirdPartyNotices.txt) 
file for details regarding the licensing of Catch2.

## Quick Start

### Requirements

* [CMake](https://cmake.org) 3.4.3

### Supported Compilers

| Compiler      | Toolset Versions Currently Tested |
|:--------------|----------------------------------:|
| GCC           | 9 & 8                             |
| Clang         | 11 & 10                           |
| Visual Studio | VS2019 & VS2017                   |
| XCode         | 11.4 & 10.3                       |

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

        cmake -G "Visual Studio 15 2017" ..

3. Build the software (in this case in the Release configuration):

        cmake --build . --config Release

4. Run the test suite:

        ctest -C Release

5. Install the software:

        cmake --build . --config Release --target install

   All tests should pass, indicating that your platform is fully supported.
