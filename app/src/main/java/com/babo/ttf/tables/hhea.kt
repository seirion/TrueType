package com.babo.ttf.tables

import com.babo.ttf.io.FileReader

class hhea : Table() {
    var version: Int = 0                 // Table version number    0x00010000 for version 1.0.
    var ascender: Short = 0              // Typographic ascent. (Distance from baseline of highest ascender)
    var descender: Short = 0             // Typographic descent. (Distance from baseline of lowest descender)
    var lineGap: Short = 0               // Typographic line gap.
                                         // Negative LineGap values are treated as zero
                                         // in Windows 3.1 System 6 and System 7.
    var advanceWidthMax: Short = 0       // Maximum advance width value in 'hmtx' table.
    var minLeftSideBearing: Short = 0    // Minimum left sidebearing value in 'hmtx' table.
    var minRightSideBearing: Short = 0   // Minimum right sidebearing value; calculated as Min(aw - lsb - (xMax - xMin)).
    var xMaxExtent: Short = 0            // Max(lsb + (xMax - xMin)).
    var caretSlopeRise: Short = 0        // Used to calculate the slope of the cursor (rise/run); 1 for vertical.
    var caretSlopeRun: Short = 0         // 0 for vertical.
    var caretOffset: Short = 0           // The amount by which a slanted highlight on a glyph needs to be shifted
                                         // to produce the best appearance. Set to 0 for non-slanted fonts
    var reserved = ShortArray(4) {0}//SHORT   (reserved)  set to 0
                                         //SHORT   (reserved)  set to 0
                                         //SHORT   (reserved)  set to 0
                                         //SHORT   (reserved)  set to 0
    var metricDataFormat: Short = 0      //  0 for current format.
    var numberOfHMetrics: Short = 0      //  Number of hMetric entries in 'hmtx' table

    override fun read(reader: FileReader) {
        version = reader.getInt()
        ascender = reader.getShort()
        descender = reader.getShort()
        lineGap = reader.getShort()
        advanceWidthMax = reader.getShort()
        minLeftSideBearing = reader.getShort()
        minRightSideBearing = reader.getShort()
        xMaxExtent = reader.getShort()
        caretSlopeRise = reader.getShort()
        caretSlopeRun = reader.getShort()
        caretOffset = reader.getShort()
        reserved.indices.forEach {
            reserved[it] = reader.getShort()
        }
        metricDataFormat = reader.getShort()
        numberOfHMetrics = reader.getShort()
    }
}
