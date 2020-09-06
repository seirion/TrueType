package com.babo.ttf.tables

import com.babo.ttf.io.FileReader

class maxp : Table() {
    var version: Int = 0                  // Table version number    0x00010000 for version 1.0.
    var numGlyphs: Short = 0              // The number of glyphs in the font.
    var maxPoints: Short = 0              // Maximum points in a non-composite glyph.
    var maxContours: Short = 0            // Maximum contours in a non-composite glyph.
    var maxCompositePoints: Short = 0     // Maximum points in a composite glyph.
    var maxCompositeContours: Short = 0   // Maximum contours in a composite glyph.
    var maxZones: Short = 0               // 1 if instructions do not use the twilight zone (Z0), or
                                          // 2 if instructions do use Z0; should be set to 2 in most cases.
    var maxTwilightPoints: Short = 0      // Maximum points used in Z0.
    var maxStorage: Short = 0             // Number of Storage Area locations.
    var maxFunctionDefs: Short = 0        // Number of FDEFs, equals to the highest function number + 1.
    var maxInstructionDefs: Short = 0     // Number of IDEFs.
    var maxStackElements: Short = 0       // Maximum stack depth2.
    var maxSizeOfInstructions: Short = 0  // Maximum byte count for glyph instructions.
    var maxComponentElements: Short = 0   // Maximum number of components referenced at "top level"
                                          //     for any composite glyph.
    var maxComponentDepth: Short = 0      // Maximum levels of recursion; 1 for simple components.

    override fun read(reader: FileReader) {
        version = reader.getInt()
        numGlyphs = reader.getShort()
        maxPoints = reader.getShort()
        maxContours = reader.getShort()
        maxCompositePoints = reader.getShort()
        maxCompositeContours = reader.getShort()
        maxZones = reader.getShort()
        maxTwilightPoints = reader.getShort()
        maxStorage = reader.getShort()
        maxFunctionDefs = reader.getShort()
        maxInstructionDefs = reader.getShort()
        maxStackElements = reader.getShort()
        maxSizeOfInstructions = reader.getShort()
        maxComponentElements = reader.getShort()
        maxComponentDepth = reader.getShort()
    }
}