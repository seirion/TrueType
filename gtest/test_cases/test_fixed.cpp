#include "gtest/gtest.h"
#include "types/Fixed.h"

GTEST_TEST(Fixed, version) {
    Fixed version(1, 0);
    EXPECT_EQ(version.toString(), "1.0");

    Fixed fixed = 3.7;
    EXPECT_EQ(fixed.toString(), "3.7");
}

GTEST_TEST(Fixed, read_stream) {
    // TODO
}
