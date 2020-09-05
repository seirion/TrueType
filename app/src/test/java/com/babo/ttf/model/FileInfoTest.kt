package com.babo.ttf.model

import com.babo.ttf.io.FileReader
import org.junit.jupiter.api.Assertions
import org.junit.jupiter.api.Test

class FileInfoTest {
    @Test
    fun `read FontInfo`() {
        val reader = FileReader(PATH)
        val fontInfo = FontInfo()
        fontInfo.read(reader)
        println(fontInfo)

        Assertions.assertEquals(0x00010000, fontInfo.sfntVersion)
        Assertions.assertEquals(25, fontInfo.numTables)
        Assertions.assertEquals(256, fontInfo.searchRange)
        Assertions.assertEquals(4, fontInfo.entrySelector)
        Assertions.assertEquals(144, fontInfo.rangeShift)
    }

    companion object {
        private val PATH = javaClass.getResource("/arial.ttf").path!!
    }
}