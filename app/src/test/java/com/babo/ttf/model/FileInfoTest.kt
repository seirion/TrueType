package com.babo.ttf.model

import com.babo.ttf.io.FileReader
import org.junit.jupiter.api.Assertions
import org.junit.jupiter.api.BeforeEach
import org.junit.jupiter.api.Test

class FileInfoTest {
    private lateinit var reader: FileReader
    private val font = Font()

    @BeforeEach
    fun setup() {
        reader = FileReader(PATH)
        font.read(reader)
    }

    @Test
    fun `read FontInfo`() {
        val fontInfo = font.fontInfo

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