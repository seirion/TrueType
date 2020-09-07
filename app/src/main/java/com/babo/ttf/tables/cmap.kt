package com.babo.ttf.tables

import com.babo.ttf.io.FileReader

class cmap : Table() {
    var version: Short = 0   // Table version number (0).
    var numTables: Short = 0 // Number of encoding tables that follow.
    var subTables: ArrayList<SubTable> = ArrayList()

    override fun read(reader: FileReader) {
        version = reader.getShort()
        numTables = reader.getShort()

        repeat(numTables.toInt()) {
            val subTable = SubTable()
            subTable.read(reader)
            subTables.add(subTable)
        }

        subTables.forEach { sub ->
            reader.seek(tableInfo.offset.toLong() + sub.offset)
            val format = reader.getShort()
            cmap_mapping.build(format)?.let {
                it.read(reader)
                sub.mapping = it
            }
        }
    }
}

class SubTable {
    var platformID: Short = 0 // Platform ID.
    var encodingID: Short = 0 // Platform-specific encoding ID.
    var offset: Int = 0       // Byte offset from beginning of table to the subtable for this encoding.
    var mapping: cmap_mapping? = null

    fun read(reader: FileReader) {
        platformID = reader.getShort()
        encodingID = reader.getShort()
        offset = reader.getInt()
    }
}
