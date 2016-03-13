#include "gtest/gtest.h"
#include "base/Reader.h"
#include "doc/Font.h"
#include "doc/FontInfo.h"

using namespace babo;

class FontReadingTest : public ::testing::Test {
public:
    Reader reader;
    virtual void SetUp() {
        reader.open("../gtest/texture/arial.ttf");
    }
    virtual void TearDown() {
    }
};

TEST_F(FontReadingTest, read) {
    ASSERT_TRUE(reader.is_open());

    Font font(reader);
    ASSERT_TRUE(reader.ok());

    const FontInfo fontInfo = font.getFontInfo();

    EXPECT_EQ(fontInfo.version().toString(), "1.0");
    EXPECT_EQ(fontInfo.getNumTables(), 25);
    EXPECT_EQ(fontInfo.getSearchRange(), 256);
    EXPECT_EQ(fontInfo.getEntrySelector(), 4);
    EXPECT_EQ(fontInfo.getRangeShift(), 144);
}

TEST_F(FontReadingTest, head) {
}

