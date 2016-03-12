#include "gtest/gtest.h"
#include "types/Fixed.h"

GTEST_TEST(Fixed, version) {
    Fixed version(1, 0);
    EXPECT_EQ(version.toString(), "1.0");

    Fixed negative(-1, 15);
    EXPECT_EQ(negative.toString(), "-1.15");
}

GTEST_TEST(Fixed, read_stream) {
    // TODO
}
