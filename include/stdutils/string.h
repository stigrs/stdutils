// Copyright (c) 2018 Stig Rune Sellevag
//
// This file is distributed under the MIT License. See the accompanying file
// LICENSE.txt or http://www.opensource.org/licenses/mit-license.php for terms
// and conditions.

#ifndef STDUTILS_STRING_H
#define STDUTILS_STRING_H

#include <cctype>
#include <sstream>
#include <stdexcept>
#include <string>

namespace Stdutils {

//------------------------------------------------------------------------------
//
// String utility methods:

// Simple convert to string method.
template <typename T>
inline std::string to_string(const T& t)
{
    std::ostringstream oss;
    oss << t;
    return oss.str();
}

// Simple extract from string method.
template <typename T>
inline T from_string(const std::string& s)
{
    std::istringstream iss(s);
    T t;
    if (!(iss >> t)) {
        throw std::runtime_error("bad cast from string '" + s + "'");
    }
    return t;
}

// Convert Fortran scientific D format to double.
inline double from_fortran_sci_fmt(const std::string& s)
{
    std::string ss = s;
    std::string::size_type pos = ss.find('D');
    if (pos != std::string::npos) {
        ss.replace(pos, 1, 1, 'e');
    }
    return from_string<double>(ss);
}

// Trim leading and trailing characters from string.
inline std::string trim(const std::string& str, const char* sep)
{
    const std::string::size_type pos = str.find_first_not_of(sep);
    return (pos == std::string::npos)
               ? std::string()
               : str.substr(pos, str.find_last_not_of(sep) - pos + 1);
}

// Strip suffix from filename.
inline std::string strip_suffix(const std::string& filename,
                                const std::string& suffix)
{
    std::string basename = filename;
    std::string::size_type pos = basename.rfind(suffix);
    if (pos == std::string::npos) {
        throw std::runtime_error(filename + " does not contain " + suffix);
    }
    return basename.erase(pos, basename.size() - pos);
}

// Get suffix from filename.
inline std::string get_suffix(const std::string& filename)
{
    std::string suffix = filename;
    std::string::size_type pos = suffix.rfind(".");
    if (pos == std::string::npos) {
        throw std::runtime_error(filename + " does not have a suffix");
    }
    return suffix.erase(0, pos);
}

// Check if string has only blank characters.
inline bool str_has_only_blanks(const std::string& str)
{
    if (!str.empty()) {
        if (str.find_first_not_of(" \t") != std::string::npos) {
            return false;
        }
    }
    return true;
}

} // namespace Stdutils

#endif // STDUTILS_STRING_H
