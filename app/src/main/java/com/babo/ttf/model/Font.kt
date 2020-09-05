package com.babo.ttf.model

import com.babo.ttf.io.FileReader
import com.babo.ttf.tables.Table
import com.babo.ttf.tables.TableInfo

class Font {
    val fontInfo = FontInfo()
    val tableInfos = HashMap<String, TableInfo>()
    val tables = HashMap<String, Table>()

    fun read(reader: FileReader) {
        fontInfo.read(reader)
        repeat(fontInfo.numTables.toInt()) {
            readTableInfos(reader)
        }

        tableInfos.forEach { (tag, tableInfo) ->
            readTable(reader, tag, tableInfo)
        }
    }

    private fun readTableInfos(reader: FileReader) {
        val info = TableInfo()
        info.read(reader)
        tableInfos[info.tag] = info
    }

    private fun readTable(reader: FileReader, tag: String, tableInfo: TableInfo) {
        reader.seek(tableInfo.offset.toLong())
        Table.from(tag)?.let { table ->
            table.tableInfo = tableInfo
            table.read(reader)
            tables[tag] = table
        }
    }
}