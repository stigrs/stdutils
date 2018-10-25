// Copyright (c) 2018 Stig Rune Sellevag
//
// This file is distributed under the MIT License. See the accompanying file
// LICENSE.txt or http://www.opensource.org/licenses/mit-license.php for terms
// and conditions.

#ifndef STDUTILS_ASSERT_H
#define STDUTILS_ASSERT_H

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable : 4127) // conditional expression is constant
#endif

#include <stdexcept>
#include <string>
#include <sstream>
#include <iostream>
#include <exception>

//
// Implementation of Stroustrup's Assert example in TC++PL4.
//

#ifndef ASSERT_MODE
#define ASSERT_MODE Assert::Mode::throw_
#endif

#ifndef ASSERT_LEVEL
#ifdef NDEBUG
#define ASSERT_LEVEL 1
#else
#define ASSERT_LEVEL 2
#endif
#endif

namespace Assert {

enum class Mode { throw_, terminate_, ignore_ };
constexpr Mode current_mode = ASSERT_MODE;
constexpr int current_level = ASSERT_LEVEL;
constexpr int default_level = 1;

inline constexpr bool level(int n) { return n <= current_level; }

struct Error : std::runtime_error {
    Error(const std::string& p) : std::runtime_error(p) {}
};

inline std::string
compose(const char* file, int line, const std::string& message)
{
    std::ostringstream os;
    os << "Failure at " << file << ", line " << line << ": " << message;
    return os.str();
}

template <bool condition = level(default_level), typename Except = Error>
inline void dynamic(bool assertion,
                    const std::string& message = "Assert::dynamic failed")
{
    if (assertion) {
        return;
    }
    if /* constexpr */ (current_mode == Mode::throw_) {
        throw Except{message};
    }
    if /* constexpr */ (current_mode == Mode::terminate_) {
        std::terminate();
    }
    if /* constexpr */ (current_mode == Mode::ignore_) {
#ifndef NDEBUG
        std::cerr << message << '\n';
#endif
    }
}

template <>
inline void dynamic<false, Error>(bool, const std::string&)
{ // do nothing
}

inline void dynamic(bool b, const std::string& s)
{ // default action
    dynamic<true, Error>(b, s);
}

inline void dynamic(bool b)
{ // default message
    dynamic<true, Error>(b);
}

} // namespace Assert

#ifdef _MSC_VER
#pragma warning(pop)
#endif

#endif // STDUTILS_ASSERT_H

