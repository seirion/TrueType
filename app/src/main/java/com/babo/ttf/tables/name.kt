package com.babo.ttf.tables

import com.babo.ttf.io.FileReader
import java.nio.charset.StandardCharsets

class name : Table() {
    var format: Short = 0
    var count: Short = 0          // Number of name records.
    var stringOffset: Short = 0   // Offset to start of string storage (from start of table).
    var nameRecord = ArrayList<NameRecord>() // The name records where count is the number of records.

    override fun read(reader: FileReader) {
        val delta = tableInfo.offset
        format = reader.getShort()
        count = reader.getShort()
        stringOffset = reader.getShort()

        repeat(count.toInt()) {
            val record = if (format.toInt() == 0) NameRecord0() else NameRecord1()
            record.stringOffset = (delta + stringOffset).toShort()
            record.read(reader)
            nameRecord.add(record)
        }

        nameRecord.forEach {
        }
    }

    fun get(reader: FileReader, i: Int): String {
        val delta = tableInfo.offset
        nameRecord[i].let {
            reader.seek(delta.toLong() + stringOffset + it.offset)
            val bytes = reader.getBytes(it.length.toInt())
            return when (it.platformID.toInt()) {
                0 -> String(bytes, StandardCharsets.UTF_16)
                3 -> {
                    if (it.encodingID.toInt() == 1) { // Unicode BMP
                        String(bytes, StandardCharsets.UTF_16)
                    } else {
                        String(bytes)
                    }
                }
                else -> String(bytes)
            }
        }
    }
}

open class NameRecord(var stringOffset: Short = 0) {
    var platformID: Short = 0 // Platform ID.
    var encodingID: Short = 0 // Platform-specific encoding ID.
    var languageID: Short = 0 // Language ID.
    var nameID: Short = 0     // Name ID.
    var length: Short = 0     // String length (in bytes).
    var offset: Short = 0     // String offset from start of storage area (in bytes).

    open fun read(reader: FileReader) {
        platformID = reader.getShort()
        encodingID = reader.getShort()
        languageID = reader.getShort()
        nameID = reader.getShort()
        length = reader.getShort()
        offset = reader.getShort()
    }
}
/**
 * Naming table format 0
 */
class NameRecord0(stringOffset: Short = 0): NameRecord(stringOffset)

/**
 * Naming table format 1
 */
class NameRecord1(stringOffset: Short = 0): NameRecord(stringOffset) {
    var langTagCount: Short = 0 // Number of language-tag records.
    val langTagRecord = ArrayList<LangTagRecord>() // The language-tag records where langTagCount is the number of records.

    override fun read(reader: FileReader) {
        super.read(reader)
        langTagCount = reader.getShort()
        repeat(langTagCount.toInt()) {
            val record = LangTagRecord().also {
                it.length = reader.getShort()
                it.offset = reader.getShort()
            }
            langTagRecord.add(record)
        }
    }
}

class LangTagRecord {
    var length: Short = 0 // Language-tag string length (in bytes)
    var offset: Short = 0 // Language-tag string offset from start of storage area (in bytes).
}

enum class EncodingID(val value: Short) {
    UNICODE_1_0(0), // Unicode 1.0 semantics
    UNICODE_1_1(1), // Unicode 1.1 semantics
    ISO_IEC(2),     // ISO/IEC 10646 semantics
    UNICODE_2_0(3), // Unicode 2.0 and onwards semantics, Unicode BMP only ('cmap' subtable formats 0, 4, 6).
    //4	Unicode 2.0 and onwards semantics, Unicode full repertoire ('cmap' subtable formats 0, 4, 6, 10, 12).
    //5	Unicode Variation Sequences ('cmap' subtable format 14).
    //6	Unicode full repertoire ('cmap' subtable formats 0, 4, 6, 10, 12, 13).
}