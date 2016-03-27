#include "gtest/gtest.h"
#include "base/Reader.h"
#include "doc/Font.h"
#include "doc/FontInfo.h"
#include "tables/cmap.h"
#include "tables/head.h"
#include "tables/hhea.h"
#include "tables/hmtx.h"
#include "tables/maxp.h"
#include "tables/name.h"
#include "tables/os_2.h"
#include "tables/post.h"

using namespace babo;

class FontReadingTest : public ::testing::Test {
public:
    Reader reader;
    virtual void SetUp() {
        reader.open("../gtest/texture/arial.ttf");
        ASSERT_TRUE(reader.is_open());
        Font::instance().read(reader);
        ASSERT_TRUE(reader.ok());
    }
    virtual void TearDown() {
    }
};

TEST_F(FontReadingTest, read) {
    const FontInfo fontInfo = Font::instance().getFontInfo();

    EXPECT_EQ(fontInfo.version().toString(), "1.0");
    EXPECT_EQ(fontInfo.getNumTables(), 25);
    EXPECT_EQ(fontInfo.getSearchRange(), 256);
    EXPECT_EQ(fontInfo.getEntrySelector(), 4);
    EXPECT_EQ(fontInfo.getRangeShift(), 144);
}

TEST_F(FontReadingTest, head) {
    const head *table = reinterpret_cast<const head *>(Font::instance().getTable("head"));

    EXPECT_EQ(table->getVersion().toString(), "1.0");
    EXPECT_EQ(table->getFontRevision().toString(), "6.9");
    EXPECT_EQ(table->getCheckSumAdjustment(), 0xfd9ba091);
    EXPECT_EQ(table->getMagicNumber(), 0x5f0f3cf5);
    EXPECT_EQ(table->getFlags(), 0x081b);
    EXPECT_EQ(table->getUnitsPerEm(), 2048);
    EXPECT_EQ(table->getCreated(), 0xa2e3272aLL);
    EXPECT_EQ(table->getModified(), 0xd19de3fdLL);
    EXPECT_EQ(table->getXMin(), -1361);
    EXPECT_EQ(table->getYMin(), -665);
    EXPECT_EQ(table->getXMax(), 4096);
    EXPECT_EQ(table->getYMax(), 2129);
    EXPECT_EQ(table->getMAcStyle(), 0);
    EXPECT_EQ(table->getLowestRecPPEM(), 9);
    EXPECT_EQ(table->getFontDirectionHint(), 1);
    EXPECT_EQ(table->getIndexToLocFormat(), 1);
    EXPECT_EQ(table->getGlyphDataFormat(), 0);
}

TEST_F(FontReadingTest, hhea) {
    const hhea *table = reinterpret_cast<const hhea *>(Font::instance().getTable("hhea"));

    EXPECT_EQ(table->getVersion().toString(), "1.0");
    EXPECT_EQ(table->getAscender(), 1854);
    EXPECT_EQ(table->getDescender(), -434);
    EXPECT_EQ(table->getLineGap(), 67);
    EXPECT_EQ(table->getAdvanceWidthMax(), 4096);
    EXPECT_EQ(table->getMinLeftSideBearing(), -1361);
    EXPECT_EQ(table->getMinRightSideBearing(), -1414);
    EXPECT_EQ(table->getXMaxExtent(), 4096);
    EXPECT_EQ(table->getCaretSlopRise(), 1);
    EXPECT_EQ(table->getCaretSlopeRun(), 0);
    EXPECT_EQ(table->getCaretOffset(), 0);
    EXPECT_EQ(table->getMetricDataForamt(), 0);
    EXPECT_EQ(table->getNumberOfHMetrics(), 4237);
}

TEST_F(FontReadingTest, maxp) {
    const maxp *table = reinterpret_cast<const maxp *>(Font::instance().getTable("maxp"));

    EXPECT_EQ(table->getVersion().toString(), "1.0");
    EXPECT_EQ(table->getNumGlyphs(), 4237);
    EXPECT_EQ(table->getMaxPoints(), 693);
    EXPECT_EQ(table->getMaxContours(), 60);
    EXPECT_EQ(table->getMaxCompositePoints(), 202);
    EXPECT_EQ(table->getMaxCompositeCoutours(), 7);
    EXPECT_EQ(table->getMaxZones(), 2);
    EXPECT_EQ(table->getMaxTwilightPoints(), 16);
    EXPECT_EQ(table->getMaxStorage(), 64);
    EXPECT_EQ(table->getMaxFunctionDefs(), 134);
    EXPECT_EQ(table->getMaxInstructionDefs(), 0);
    EXPECT_EQ(table->getMaxStackElements(), 1303);
    EXPECT_EQ(table->getMaxSizeOfInstructions(), 1516);
    EXPECT_EQ(table->getMaxComponentElements(), 5);
    EXPECT_EQ(table->getMaxComponentDepth(), 2);
}

TEST_F(FontReadingTest, cmap) {
    const cmap *table = reinterpret_cast<const cmap *>(Font::instance().getTable("cmap"));

    EXPECT_EQ(table->getVersion(), 0);

    int32 numTables = table->getNumTables();
    EXPECT_EQ(numTables, 3);

    const vector<cmap::SubTable> &subTables = table->getSubTables();
    EXPECT_EQ(subTables[0].getPlatformID(), 0);
    EXPECT_EQ(subTables[0].getEncodingID(), 3);
    EXPECT_EQ(subTables[1].getPlatformID(), 1);
    EXPECT_EQ(subTables[1].getEncodingID(), 0);
    EXPECT_EQ(subTables[2].getPlatformID(), 3);
    EXPECT_EQ(subTables[2].getEncodingID(), 1);

    cmap_mapping *mapping = subTables[0].getMapping();
    EXPECT_EQ(mapping->getFormat(), 4);

    mapping = subTables[1].getMapping();
    EXPECT_EQ(mapping->getFormat(), 0);

    mapping = subTables[2].getMapping();
    EXPECT_EQ(mapping->getFormat(), 4);
}


TEST_F(FontReadingTest, name) {
    const name *table = reinterpret_cast<const name *>(Font::instance().getTable("name"));

    EXPECT_EQ(table->getFormat(), 0);
    EXPECT_EQ(table->getCount(), 58);
}

//TEST_F(FontReadingTest, hmtx) {
//    const hmtx *table = reinterpret_cast<const hmtx *>(Font::instance().getTable("hmtx"));
//}

TEST_F(FontReadingTest, os_2) {
    const os_2 *table = reinterpret_cast<const os_2 *>(Font::instance().getTable("OS/2"));

    EXPECT_EQ(table->getVersion(), 0x0003);
    EXPECT_EQ(table->getXAvgCharWidth(), 904);
    EXPECT_EQ(table->getUsWeightClass(), 400);
    EXPECT_EQ(table->getUsWidthClass(), 5);
    EXPECT_EQ(table->getFsType(), 0x0008);
    EXPECT_EQ(table->getAchVendID(), "TMC ");

}

TEST_F(FontReadingTest, post) {
    const post *table = reinterpret_cast<const post *>(Font::instance().getTable("post"));

    EXPECT_EQ(table->getVersion().toString(), "3.0");
    EXPECT_EQ(table->getItalicAngle().toString(), "0.0");
    EXPECT_EQ(table->getUnderlinePosition(), -217);
    EXPECT_EQ(table->getUnderlineThickness(), 150);
    EXPECT_EQ(table->isFixedPitch(), 0);
    EXPECT_EQ(table->getMinMemType42(), 0);
    EXPECT_EQ(table->getMaxMemType42(), 0);
    EXPECT_EQ(table->getMinMemType1(), 0);
    EXPECT_EQ(table->getMaxMemType1(), 0);
}
