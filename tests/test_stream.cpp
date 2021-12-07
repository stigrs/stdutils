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

TEST(TestStream, TestFindToken)
{
    std::ifstream from;
    fopen(from, "test_stream.inp");

    auto pos = find_token(from, "ParseThis");
    EXPECT_TRUE(pos != -1);
}

TEST(TestStream, TestGetTokenValue)
{
    std::ifstream from;
    fopen(from, "test_stream.inp");

    int i = 0;
    double d = 0.0;
    std::complex<double> cx;
    std::complex<double> cx_ans{2.0, 1.0};
    std::string s;

    auto pos = find_token(from, "ParseThis");
    if (pos != -1) {
        get_token_value(from, pos, "integer", i, 100);
        get_token_value(from, pos, "double", d, 20.0);
        get_token_value(from, pos, "complex", cx);
        pos = find_token(from, "SubSection", pos);
        if (pos != -1) {
            get_token_value(from, pos, "string", s, s);
        }
    }
    EXPECT_TRUE(i == 100);
    EXPECT_TRUE(std::abs(d - 2.0) < 1.0e-12);
    EXPECT_TRUE(cx == cx_ans);
    EXPECT_TRUE(s == "world");
}
