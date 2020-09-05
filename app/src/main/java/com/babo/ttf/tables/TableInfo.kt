package com.babo.ttf.tables

import com.babo.ttf.io.FileReader

data class TableInfo(
        var tag: String = "",       // 4 -byte identifier.
        var checkSum: Int = 0,      // CheckSum for this table.
        var offset: Int = 0,        // Offset from beginning of TrueType font file.
        var length: Int = 0         // Length of this table.
) {
    fun read(reader: FileReader) {
        tag = reader.getBytes(4).map { it.toChar() }.joinToString("")
        checkSum = reader.getInt()
        offset = reader.getInt()
        length = reader.getInt()
    }
}