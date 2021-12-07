// Copyright (c) 2018 Stig Rune Sellevag
//
// This file is distributed under the MIT License. See the accompanying file
// LICENSE.txt or http://www.opensource.org/licenses/mit-license.php for terms
// and conditions.

#include <stdutils/stdutils.h>
#include <gtest/gtest.h>
#include <string>

using namespace Stdutils;

TEST(TestString, TestFromFortranSciFmt)
{
    double d = from_fortran_sci_fmt("3.14D-3");
    EXPECT_TRUE(d == 3.14e-3);
}

TEST(TestString, TestStripSuffix)
{
    std::string basename = strip_suffix("test.txt", ".txt");
    EXPECT_TRUE(basename == "test");
}

TEST(TestString, TestGetSuffix)
{
    std::string suffix = get_suffix("test.txt");
    EXPECT_TRUE(suffix == ".txt");
}
