package com.babo.ttf.tables

import com.babo.ttf.io.FileReader

abstract class cmap_mapping(val format: Short) {
    abstract fun read(reader: FileReader)

    companion object {
        fun build(format: Short): cmap_mapping? {
            return when (format.toInt()) {
                0 -> cmap_mapping_format0(format)
                4 -> cmap_mapping_format4(format)
                else -> null
            }
        }
    }
}

class cmap_mapping_format0(format: Short) : cmap_mapping(format) {
    var length: Short = 0    // This is the length in bytes of the subtable.
    var language: Short = 0
    lateinit var glyphIdArray: ByteArray // An array that maps character codes to glyph index values.

    override fun read(reader: FileReader) {
        length = reader.getShort()
        language = reader.getShort()
        glyphIdArray = reader.getBytes(length.toInt())
    }
}

class cmap_mapping_format4(format: Short) : cmap_mapping(format) {
    var length: Short = 0                 // This is the length in bytes of the subtable.
    var language: Short = 0               //
    var segCountX2: Short = 0             // 2 x segCount.
    var searchRange: Short = 0            // 2 x (2**floor(log2(segCount)))
    var entrySelector: Short = 0          // log2(searchRange/2)
    var rangeShift: Short = 0             // 2 x segCount - searchRange
    lateinit var endCount: ShortArray  // End characterCode for each segment, last=0xFFFF.
    var reservedPad: Short = 0            // Set to 0.
    lateinit var startCount: ShortArray // Start character code for each segment.
    lateinit var idDelta: ShortArray     // Delta for all character codes in segment.
    lateinit var idRangeOffset: ShortArray  //Offsets into glyphIdArray or 0
    lateinit var glyphIdArray: ShortArray   //Glyph index array (arbitrary length)

    override fun read(reader: FileReader) {
        length = reader.getShort()
        language = reader.getShort()
        segCountX2 = reader.getShort()
        searchRange = reader.getShort()
        entrySelector = reader.getShort()
        rangeShift = reader.getShort()

        val size = segCountX2.toInt() / 2
        endCount = ShortArray(size)
        endCount.indices.forEach {
            endCount[it] = reader.getShort()
        }

        reservedPad = reader.getShort()

        startCount = ShortArray(size)
        startCount.indices.forEach {
            startCount[it] = reader.getShort()
        }

        idDelta = ShortArray(size)
        idDelta.indices.forEach {
            idDelta[it] = reader.getShort()
        }

        glyphIdArray = ShortArray((length - (segCountX2 * 4)) / 2)
        glyphIdArray.indices.forEach {
            glyphIdArray[it] = reader.getShort()
        }
    }
}
