// Copyright (c) 2018 Stig Rune Sellevag
//
// This file is distributed under the MIT License. See the accompanying file
// LICENSE.txt or http://www.opensource.org/licenses/mit-license.php for terms
// and conditions.

#include <stdutils/stdutils.h>
#include <catch2/catch.hpp>
#include <fstream>
#include <string>
#include <cmath>
#include <complex>

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

    SECTION("find_token")
    {
        std::ifstream from;
        fopen(from, "test_stream.inp");

        auto pos = find_token(from, "ParseThis");
        CHECK(pos != -1);
    }

    SECTION("get_token_value")
    {
        std::ifstream from;
        fopen(from, "test_stream.inp");

        int i = 0;
        double d = 0.0;
        std::complex<double> cx;
        std::complex<double> cx_ans{2.0, 1.0};

        auto pos = find_token(from, "ParseThis");
        if (pos != -1) {
            get_token_value(from, pos, "integer", i, 100);
            get_token_value(from, pos, "double", d, 20.0);
            get_token_value(from, pos, "complex", cx);
        }
        CHECK(i == 10);
        CHECK(std::abs(d - 2.0) < 1.0e-12);
        CHECK(cx == cx_ans);
    }
}
