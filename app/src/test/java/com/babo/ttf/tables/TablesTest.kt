package com.babo.ttf.tables

import com.babo.ttf.io.FileReader
import com.babo.ttf.model.Font
import org.junit.jupiter.api.Assertions
import org.junit.jupiter.api.BeforeEach
import org.junit.jupiter.api.Test

class TablesTest {
    private lateinit var reader: FileReader
    private val font = Font()

    @BeforeEach
    fun setup() {
        reader = FileReader(PATH)
        font.read(reader)
    }

    @Test
    fun `head table`() {
        val head = font.tables["head"]

        Assertions.assertNotNull(head)
        Assertions.assertTrue(head is head)

        if (head is head) {
            Assertions.assertEquals(0x00010000, head.version)
            Assertions.assertEquals(0x0006e666, head.fontRevision)
            //Assertions.assertEquals(0xfd9ba091, head.checkSumAdjustment)
            Assertions.assertEquals(0x5f0f3cf5, head.magicNumber)
            Assertions.assertEquals(0x081b, head.flags)
            Assertions.assertEquals(2048, head.unitsPerEm)
            Assertions.assertEquals(0xa2e3272aL, head.created)
            Assertions.assertEquals(0xd19de3fdL, head.modified)
            Assertions.assertEquals(-1361, head.xMin)
            Assertions.assertEquals(-665, head.yMin)
            Assertions.assertEquals(4096, head.xMax)
            Assertions.assertEquals(2129, head.yMax)
            Assertions.assertEquals(0, head.macStyle)
            Assertions.assertEquals(9, head.lowestRecPPEM)
            Assertions.assertEquals(1, head.fontDirectionHint)
            Assertions.assertEquals(1, head.indexToLocFormat)
            Assertions.assertEquals(0, head.glyphDataFormat)
        }
    }

    @Test
    fun `hhea table`() {
        val hhea = font.tables["hhea"]

        Assertions.assertNotNull(hhea)
        Assertions.assertTrue(hhea is hhea)

        if (hhea is hhea) {
            Assertions.assertEquals(0x00010000, hhea.version)
            Assertions.assertEquals(1854, hhea.ascender)
            Assertions.assertEquals(-434, hhea.descender)
            Assertions.assertEquals(67, hhea.lineGap)
            Assertions.assertEquals(4096, hhea.advanceWidthMax)
            Assertions.assertEquals(-1361, hhea.minLeftSideBearing)
            Assertions.assertEquals(-1414, hhea.minRightSideBearing)
            Assertions.assertEquals(4096, hhea.xMaxExtent)
            Assertions.assertEquals(1, hhea.caretSlopeRise)
            Assertions.assertEquals(0, hhea.caretSlopeRun)
            Assertions.assertEquals(0, hhea.caretOffset)
            Assertions.assertEquals(0, hhea.metricDataFormat)
            Assertions.assertEquals(4237, hhea.numberOfHMetrics)
        }
    }

    @Test
    fun `maxp table`() {
        val maxp = font.tables["maxp"]

        Assertions.assertNotNull(maxp)
        Assertions.assertTrue(maxp is maxp)

        if (maxp is maxp) {
            Assertions.assertEquals(0x00010000, maxp.version)
            Assertions.assertEquals(4237, maxp.numGlyphs)
            Assertions.assertEquals(693, maxp.maxPoints)
            Assertions.assertEquals(60, maxp.maxContours)
            Assertions.assertEquals(202, maxp.maxCompositePoints)
            Assertions.assertEquals(7, maxp.maxCompositeContours)
            Assertions.assertEquals(2, maxp.maxZones)
            Assertions.assertEquals(16, maxp.maxTwilightPoints)
            Assertions.assertEquals(64, maxp.maxStorage)
            Assertions.assertEquals(134, maxp.maxFunctionDefs)
            Assertions.assertEquals(0, maxp.maxInstructionDefs)
            Assertions.assertEquals(1303, maxp.maxStackElements)
            Assertions.assertEquals(1516, maxp.maxSizeOfInstructions)
            Assertions.assertEquals(5, maxp.maxComponentElements)
            Assertions.assertEquals(2, maxp.maxComponentDepth)
        }
    }

    @Test
    fun `cmap table`() {
        val cmap = font.tables["cmap"]

        Assertions.assertNotNull(cmap)
        Assertions.assertTrue(cmap is cmap)

        if (cmap is cmap) {
            Assertions.assertEquals(0, cmap.version)
            Assertions.assertEquals(3, cmap.numTables)

            Assertions.assertEquals(0, cmap.subTables[0].platformID)
            Assertions.assertEquals(3, cmap.subTables[0].encodingID)
            Assertions.assertEquals(1, cmap.subTables[1].platformID)
            Assertions.assertEquals(0, cmap.subTables[1].encodingID)
            Assertions.assertEquals(3, cmap.subTables[2].platformID)
            Assertions.assertEquals(1, cmap.subTables[2].encodingID)

            Assertions.assertEquals(4, cmap.subTables[0].mapping?.format)
            Assertions.assertEquals(0, cmap.subTables[1].mapping?.format)
            Assertions.assertEquals(4, cmap.subTables[2].mapping?.format)
        }
    }

    @Test
    fun `name table`() {
        val name = font.tables["name"]

        Assertions.assertNotNull(name)
        Assertions.assertTrue(name is name)

        if (name is name) {
            Assertions.assertEquals(0, name.format)
            Assertions.assertEquals(58, name.count)
            Assertions.assertEquals("Arial", name.get(reader, 1))
            Assertions.assertEquals("Regular", name.get(reader, 2))
            Assertions.assertEquals("Version 6.90", name.get(reader, 5))
            Assertions.assertEquals("The Monotype Corporation", name.get(reader, 8))
        }
    }

    companion object {
        private val PATH = javaClass.getResource("/arial.ttf").path!!
    }
}