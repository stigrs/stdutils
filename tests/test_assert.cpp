// Copyright (c) 2018 Stig Rune Sellevag
//
// This file is distributed under the MIT License. See the accompanying file
// LICENSE.txt or http://www.opensource.org/licenses/mit-license.php for terms
// and conditions.

#include <stdutils/stdutils.h>
#include <gtest/gtest.h>

void f(int n)
{
    Assert::dynamic<Assert::level(1)>(
        1 <= n && n < 10, Assert::compose(__FILE__, __LINE__, "out of range"));
}

TEST(TestStdutils, TestAssert)
{
    EXPECT_ANY_THROW(f(0));
    EXPECT_ANY_THROW(f(10));
    EXPECT_NO_THROW(f(2));
}
