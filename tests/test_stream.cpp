// Copyright (c) 2018 Stig Rune Sellevag
//
// This file is distributed under the MIT License. See the accompanying file
// LICENSE.txt or http://www.opensource.org/licenses/mit-license.php for terms
// and conditions.

#include <stdutils/stdutils.h>
#include <gtest/gtest.h>
#include <fstream>
#include <string>
#include <cmath>
#include <complex>

using namespace Stdutils;

TEST(TestStream, TestFopen)
{
    std::ifstream from;
    EXPECT_ANY_THROW(fopen(from, "non_existing_file"));
}

TEST(TestStream, TestLexicalCast)
{
    std::string s = lexical_cast<std::string>(lexical_cast<double>("  3.14  "));
    EXPECT_TRUE(s == "3.14");
}
