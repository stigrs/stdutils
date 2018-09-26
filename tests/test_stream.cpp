// Copyright (c) 2018 Stig Rune Sellevag
//
// This file is distributed under the MIT License. See the accompanying file
// LICENSE.txt or http://www.opensource.org/licenses/mit-license.php for terms
// and conditions.

#include <stdutils/stdutils.h>
#include <catch2/catch.hpp>
#include <fstream>
#include <string>

TEST_CASE("test_stream")
{
    using namespace Stdutils;

    SECTION("fopen")
    {
        std::ifstream from;
        CHECK_THROWS(fopen(from, "non_existing_file"));
    }

    SECTION("lexical_cast")
    {
        std::string s =
            lexical_cast<std::string>(lexical_cast<double>("  3.14  "));
        CHECK(s == "3.14");
    }
}
