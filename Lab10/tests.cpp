// tests/tests.cpp
// Unit tests using GoogleTest to test our functions

#include "gtest/gtest.h"
#include "../calculator.hpp"

TEST(TrimTest, RemovesSpaces) {
    EXPECT_EQ(trim("  123.45  "), "123.45");
    EXPECT_EQ(trim("\t\n12\n\t"), "12");
}

TEST(DoubleValidation, ValidDoubles) {
    EXPECT_TRUE(isValidDouble("1"));
    EXPECT_TRUE(isValidDouble("1.0"));
    EXPECT_TRUE(isValidDouble("+1.5"));
    EXPECT_TRUE(isValidDouble("-123.456"));
}

TEST(DoubleValidation, InvalidDoubles) {
    EXPECT_FALSE(isValidDouble("A"));
    EXPECT_FALSE(isValidDouble("+-1"));
    EXPECT_FALSE(isValidDouble("-5."));
    EXPECT_FALSE(isValidDouble("1.2.3"));
}

TEST(AdditionTest, BasicCases) {
    EXPECT_EQ(addStrings("1.0", "2.0"), "3.0");
    EXPECT_EQ(addStrings("0.5", "0.5"), "1.0");
    EXPECT_EQ(addStrings("10", "-5"), "5");
    EXPECT_EQ(addStrings("123.456", "-123.456"), "0.0");
}