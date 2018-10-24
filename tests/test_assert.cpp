// Copyright (c) 2018 Stig Rune Sellevag
//
// This file is distributed under the MIT License. See the accompanying file
// LICENSE.txt or http://www.opensource.org/licenses/mit-license.php for terms
// and conditions.

#include <stdutils/stdutils.h>
#include <catch2/catch.hpp>

void f(int n)
{
    Assert::dynamic<Assert::level(1)>(
        1 <= n && n < 10, Assert::compose(__FILE__, __LINE__, "out of range"));
}

TEST_CASE("test_assert")
{
    CHECK_THROWS(f(0));
    CHECK_THROWS(f(10));
    CHECK_NOTHROW(f(2));
}

