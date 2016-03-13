#include "gtest/gtest.h"
#include "base/Reader.h"

using namespace babo;

GTEST_TEST(Reader, read) {
    Reader reader("./texture/arial.ttf");
    EXPECT_EQ(reader.is_open(), true);

}

