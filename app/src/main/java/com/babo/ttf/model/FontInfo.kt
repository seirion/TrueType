package com.babo.ttf.model

import com.babo.ttf.io.FileReader

data class FontInfo(
    var sfntVersion: Int = 0,     // 0x00010000 for version 1.0.
    var numTables: Short = 0,     // Number of tables
    var searchRange: Short = 0,   // (Maximum power of 2 <= numTables) * 16
    var entrySelector: Short = 0, // Log2(Maximum power of 2 <= numTables)
    var rangeShift: Short = 0     // NumTables * 16 - serachRange
) {
    fun read(reader: FileReader) {
        sfntVersion = reader.getInt()
        numTables = reader.getShort()
        searchRange = reader.getShort()
        entrySelector = reader.getShort()
        rangeShift = reader.getShort()
    }
}