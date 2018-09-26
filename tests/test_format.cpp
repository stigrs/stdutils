// Copyright (c) 2018 Stig Rune Sellevag
//
// This file is distributed under the MIT License. See the accompanying file
// LICENSE.txt or http://www.opensource.org/licenses/mit-license.php for terms
// and conditions.

#include <stdutils/stdutils.h>
#include <catch2/catch.hpp>
#include <sstream>

TEST_CASE("test_format")
{
    SECTION("fixed")
    {
        Stdutils::Format<double> fix;
        fix.fixed().precision(2);
        double d = 1.23456;
        std::ostringstream s;
        s << fix(d);
        CHECK(s.str() == "1.23");
    }

    SECTION("scientific")
    {
        Stdutils::Format<double> sci;
        sci.scientific().precision(4);
        double d = 1.23456e-3;
        std::ostringstream s;
        s << sci(d);
        CHECK(s.str() == "1.2346e-03");
    }

    SECTION("line")
    {
        Stdutils::Format<char> line;
        line.width(3).fill('-');
        std::ostringstream s;
        s << line('-');
        CHECK(s.str() == "---");
    }
}
