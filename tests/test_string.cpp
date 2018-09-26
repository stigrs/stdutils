// Copyright (c) 2018 Stig Rune Sellevag
//
// This file is distributed under the MIT License. See the accompanying file
// LICENSE.txt or http://www.opensource.org/licenses/mit-license.php for terms
// and conditions.

#include <stdutils/stdutils.h>
#include <catch2/catch.hpp>
#include <string>

TEST_CASE("test_string")
{
    using namespace Stdutils;

    SECTION("to_string")
    {
        std::string s = to_string<double>(3.14);
        CHECK(s == "3.14");
    }

    SECTION("from_string")
    {
        double d = from_string<double>("3.14");
        CHECK(d == 3.14);
    }

    SECTION("from_fortran_sci_fmt")
    {
        double d = from_fortran_sci_fmt("3.14D-3");
        CHECK(d == 3.14e-3);
    }

    SECTION("strip_suffix")
    {
        std::string basename = strip_suffix("test.txt", ".txt");
        CHECK(basename == "test");
    }

    SECTION("get_suffix")
    {
        std::string suffix = get_suffix("test.txt");
        CHECK(suffix == ".txt");
    }
}
