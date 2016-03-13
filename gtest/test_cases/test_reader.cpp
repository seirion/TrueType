#include "gtest/gtest.h"
#include "base/Reader.h"
#include "doc/Font.h"
#include "doc/FontInfo.h"
#include "tables/head.h"

using namespace babo;

class FontReadingTest : public ::testing::Test {
public:
    Reader reader;
    Font font;
    virtual void SetUp() {
        reader.open("../gtest/texture/arial.ttf");
        ASSERT_TRUE(reader.is_open());
        font.open(reader);
        ASSERT_TRUE(reader.ok());
    }
    virtual void TearDown() {
    }
};

TEST_F(FontReadingTest, read) {
    const FontInfo fontInfo = font.getFontInfo();

    EXPECT_EQ(fontInfo.version().toString(), "1.0");
    EXPECT_EQ(fontInfo.getNumTables(), 25);
    EXPECT_EQ(fontInfo.getSearchRange(), 256);
    EXPECT_EQ(fontInfo.getEntrySelector(), 4);
    EXPECT_EQ(fontInfo.getRangeShift(), 144);
}

TEST_F(FontReadingTest, head) {
    const head &head = font.getHead();

    EXPECT_EQ(head.getVersion().toString(), "1.0");
    EXPECT_EQ(head.getFontRevision().toString(), "6.90");
    /* FIXME
    EXPECT_EQ(head.getCheckSumAdjustment(), 0);
    EXPECT_EQ(head.getMagicNumber(), 0);
    EXPECT_EQ(head.getFlags(), 0);
    EXPECT_EQ(head.getUnitsPerEm(), 0);
    EXPECT_EQ(head.getCreated(), 0);
    EXPECT_EQ(head.getModified(), 0);
    EXPECT_EQ(head.getXMin(), 0);
    EXPECT_EQ(head.getYMin(), 0);
    EXPECT_EQ(head.getXMax(), 0);
    EXPECT_EQ(head.getYMax(), 0);
    EXPECT_EQ(head.getMAcStyle(), 0);
    EXPECT_EQ(head.getLowestRecPPEM(), 0);
    EXPECT_EQ(head.getFontDirectionHint(), 0);
    EXPECT_EQ(head.getIndexToLocFormat(), 0);
    EXPECT_EQ(head.getGlyphDataFormat(), 0);
    */
}

