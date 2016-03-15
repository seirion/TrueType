#include "gtest/gtest.h"
#include "base/Reader.h"
#include "doc/Font.h"
#include "doc/FontInfo.h"
#include "tables/head.h"
#include "tables/hhea.h"

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
    const head &head = font.get_head();

    EXPECT_EQ(head.getVersion().toString(), "1.0");
    EXPECT_EQ(head.getFontRevision().toString(), "6.9");
    EXPECT_EQ(head.getCheckSumAdjustment(), 0xfd9ba091);
    EXPECT_EQ(head.getMagicNumber(), 0x5f0f3cf5);
    EXPECT_EQ(head.getFlags(), 0x081b);
    EXPECT_EQ(head.getUnitsPerEm(), 2048);
    EXPECT_EQ(head.getCreated(), 0xa2e3272aLL);
    EXPECT_EQ(head.getModified(), 0xd19de3fdLL);
    EXPECT_EQ(head.getXMin(), -1361);
    EXPECT_EQ(head.getYMin(), -665);
    EXPECT_EQ(head.getXMax(), 4096);
    EXPECT_EQ(head.getYMax(), 2129);
    EXPECT_EQ(head.getMAcStyle(), 0);
    EXPECT_EQ(head.getLowestRecPPEM(), 9);
    EXPECT_EQ(head.getFontDirectionHint(), 1);
    EXPECT_EQ(head.getIndexToLocFormat(), 1);
    EXPECT_EQ(head.getGlyphDataFormat(), 0);
}

TEST_F(FontReadingTest, hhea) {
    const hhea &hhea = font.get_hhea();

    EXPECT_EQ(hhea.getVersion().toString(), "1.0");
    EXPECT_EQ(hhea.getAscender(), 1854);
    EXPECT_EQ(hhea.getDescender(), -434);
    EXPECT_EQ(hhea.getLineGap(), 67);
    EXPECT_EQ(hhea.getAdvanceWidthMax(), 4096);
    EXPECT_EQ(hhea.getMinLeftSideBearing(), -1361);
    EXPECT_EQ(hhea.getMinRightSideBearing(), -1414);
    EXPECT_EQ(hhea.getXMaxExtent(), 4096);
    EXPECT_EQ(hhea.getCaretSlopRise(), 1);
    EXPECT_EQ(hhea.getCaretSlopeRun(), 0);
    EXPECT_EQ(hhea.getCaretOffset(), 0);
    EXPECT_EQ(hhea.getMetricDataForamt(), 0);
    EXPECT_EQ(hhea.getNumberOfMetrices(), 4237);
}

TEST_F(FontReadingTest, maxp) {
    const maxp &maxp = font.get_maxp();

    EXPECT_EQ(maxp.getVersion().toString(), "1.0");
    EXPECT_EQ(maxp.getNumGlyphs(), 4237);
    EXPECT_EQ(maxp.getMaxPoints(), 693);
    EXPECT_EQ(maxp.getMaxContours(), 60);
    EXPECT_EQ(maxp.getMaxCompositePoints(), 202);
    EXPECT_EQ(maxp.getMaxCompositeCoutours(), 7);
    EXPECT_EQ(maxp.getMaxZones(), 2);
    EXPECT_EQ(maxp.getMaxTwilightPoints(), 16);
    EXPECT_EQ(maxp.getMaxStorage(), 64);
    EXPECT_EQ(maxp.getMaxFunctionDefs(), 134);
    EXPECT_EQ(maxp.getMaxInstructionDefs(), 0);
    EXPECT_EQ(maxp.getMaxStackElements(), 1303);
    EXPECT_EQ(maxp.getMaxSizeOfInstructions(), 1516);
    EXPECT_EQ(maxp.getMaxComponentElements(), 5);
    EXPECT_EQ(maxp.getMaxComponentDepth(), 2);
}
