package com.babo.ttf.tables

import com.babo.ttf.io.FileReader

class head : Table() {
    var version: Int = 0            // Table version number    0x00010000 for version 1.0.
    var fontRevision: Int = 0       // Set by font manufacturer.
    var checkSumAdjustment: Int = 0 // To compute: set it to 0, sum the entire font as ULONG, then store 0xB1B0AFBA - sum.
    var magicNumber: Int = 0        // Set to 0x5F0F3CF5.
    var flags: Short = 0            // Bit 0: Baseline for font at y=0;
                                    // Bit 1: Left sidebearing point at x=0;
                                    // Bit 2: Instructions may depend on point size;
                                    // Bit 3: Force ppem to integer values for all internal scaler math;
                                    //        may use fractional ppem sizes if this bit is clear;
                                    // Bit 4: Instructions may alter advance width (the advance widths might not scale linearly);
                                    // Bits 5-10: These should be set according to Apple's specification . However, they are not implemented in OpenType.
                                    // Bit 11: Font data is ‘lossless’ as a results of having been subjected to optimizing transformation and/or compression (such as e.g. compression mechanisms defined by ISO/IEC 14496-18, MicroType Express, WOFF 2.0 or similar) where the original font functionality and features are retained but the binary compatibility between input and output font files is not guaranteed. As a result of the applied transform, the ‘DSIG’ Table may also be invalidated.
                                    // Bit 12: Font converted (produce compatible metrics)
                                    // Bit 13: Font optimized for ClearType™. Note, fonts that rely on embedded bitmaps (EBDT) for rendering should not be considered optimized for ClearType, and therefore should keep this bit cleared.
                                    // Bit 14: Last Resort font. If set, indicates that the glyphs encoded in the cmap subtables are simply generic symbolic representations of code point ranges and don’t truly represent support for those code points. If unset, indicates that the glyphs encoded in the cmap subtables represent proper support for those code points.
                                    // Bit 15: Reserved, set to 0
    var unitsPerEm: Short = 0       // Valid range is from 16 to 16384. This value should be a power of 2 for fonts that have TrueType outlines.
    var created: Long = 0           // Number of seconds since 12:00 midnight that started January 1st 1904 in GMT/UTC time zone. 64-bit integer
    var modified: Long = 0          // Number of seconds since 12:00 midnight that started January 1st 1904 in GMT/UTC time zone. 64-bit integer
    var xMin: Short = 0             // For all glyph bounding boxes.
    var yMin: Short = 0             // For all glyph bounding boxes.
    var xMax: Short = 0             // For all glyph bounding boxes.
    var yMax: Short= 0              // For all glyph bounding boxes.
    var macStyle: Short = 0         // Bit 0: Bold (if set to 1);
                                    // Bit 1: Italic (if set to 1)
                                    // Bit 2: Underline (if set to 1)
                                    // Bit 3: Outline (if set to 1)
                                    // Bit 4: Shadow (if set to 1)
                                    // Bit 5: Condensed (if set to 1)
                                    // Bit 6: Extended (if set to 1)
                                    // Bits 7-15: Reserved (set to 0).
    var lowestRecPPEM: Short  = 0   //  Smallest readable size in pixels.
    var fontDirectionHint: Short  = 0// Deprecated (Set to 2).
                                    // 0: Fully mixed directional glyphs;
                                    // 1: Only strongly left to right;
                                    // 2: Like 1 but also contains neutrals;
                                    // -1: Only strongly right to left;
                                    // -2: Like -1 but also contains neutrals. 1
    var indexToLocFormat: Short = 0 // 0 for short offsets, 1 for long.
    var glyphDataFormat: Short = 0  // 0 for current format.

    override fun read(reader: FileReader) {
        version = reader.getInt()
        fontRevision = reader.getInt()
        checkSumAdjustment = reader.getInt()
        magicNumber = reader.getInt()
        flags = reader.getShort()
        unitsPerEm = reader.getShort()
        created = reader.getLong()
        modified = reader.getLong()
        xMin = reader.getShort()
        yMin = reader.getShort()
        xMax = reader.getShort()
        yMax = reader.getShort()
        macStyle = reader.getShort()
        lowestRecPPEM = reader.getShort()
        fontDirectionHint = reader.getShort()
        indexToLocFormat = reader.getShort()
        glyphDataFormat = reader.getShort()
    }
}