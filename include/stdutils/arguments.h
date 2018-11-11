// Copyright (c) 2018 Stig Rune Sellevag
//
// This file is distributed under the MIT License. See the accompanying file
// LICENSE.txt or http://www.opensource.org/licenses/mit-license.php for terms
// and conditions.

#ifndef STDUTILS_ARGUMENTS_H
#define STDUTILS_ARGUMENTS_H

#include <vector>
#include <string>

namespace Stdutils {

// Vector for holding program arguments.
inline std::vector<std::string> arguments(int argc, char* argv[])
{
    std::vector<std::string> res;
    for (int i = 0; i != argc; ++i) {
        res.push_back(argv[i]);
    }
    return res;
}

} // namespace Stdutils

#endif // STDUTILS_ARGUMENTS_H

