#include "gtest/gtest.h"
#include "base/Reader.h"
#include "tables/FontInfo.h"

using namespace babo;

GTEST_TEST(Reader, read) {
    Reader reader("../gtest/texture/arial.ttf");
    ASSERT_TRUE(reader.is_open());

    FontInfo fontInfo(reader);
    EXPECT_EQ(fontInfo.version().toString(), "1.0");
    EXPECT_EQ(fontInfo.getNumTables(), 25);
    EXPECT_EQ(fontInfo.getSearchRange(), 256);
    EXPECT_EQ(fontInfo.getEntrySelector(), 4);
    EXPECT_EQ(fontInfo.getRangeShift(), 144);
}

