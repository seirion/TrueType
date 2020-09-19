package com.babo.ttf.tables

import com.babo.ttf.io.FileReader

class os_2 : Table() {
    var version: Short = 0 // 0x0005
    var xAvgCharWidth: Short = 0
    var usWeightClass: Short = 0
    var usWidthClass: Short = 0
    var fsType: Short = 0
    var ySubscriptXSize: Short = 0
    var ySubscriptYSize: Short = 0
    var ySubscriptXOffset: Short = 0
    var ySubscriptYOffset: Short = 0
    var ySuperscriptXSize: Short = 0
    var ySuperscriptYSize: Short = 0
    var ySuperscriptXOffset: Short = 0
    var ySuperscriptYOffset: Short = 0
    var yStrikeoutSize: Short = 0
    var yStrikeoutPosition: Short = 0
    var sFamilyClass: Short = 0
    var panose = ByteArray(10)
    var ulUnicodeRange1: Int = 0 // Bits 0-31
    var ulUnicodeRange2: Int = 0 // Bits 32-63
    var ulUnicodeRange3: Int = 0 // Bits 64-95
    var ulUnicodeRange4: Int = 0 // Bits 96-127
    var achVendID = ByteArray(4)
    var fsSelection: Short = 0
    var usFirstCharIndex: Short = 0
    var usLastCharIndex: Short = 0
    var sTypoAscender: Short = 0
    var sTypoDescender: Short = 0
    var sTypoLineGap: Short = 0
    var usWinAscent: Short = 0
    var usWinDescent: Short = 0
    var ulCodePageRange1: Int = 0 // Bits 0-31
    var ulCodePageRange2: Int = 0 // Bits 32-63
    var sxHeight: Short = 0
    var sCapHeight: Short = 0
    var usDefaultChar: Short = 0
    var usBreakChar: Short = 0
    var usMaxContext: Short = 0
    var usLowerOpticalPointSize: Short = 0
    var usUpperOpticalPointSize: Short = 0

    override fun read(reader: FileReader) {
        version = reader.getShort()
        xAvgCharWidth = reader.getShort()
        usWeightClass = reader.getShort()
        usWidthClass = reader.getShort()
        fsType = reader.getShort()
        ySubscriptXSize = reader.getShort()
        ySubscriptYSize = reader.getShort()
        ySubscriptXOffset = reader.getShort()
        ySubscriptYOffset = reader.getShort()
        ySuperscriptXSize = reader.getShort()
        ySuperscriptYSize = reader.getShort()
        ySuperscriptXOffset = reader.getShort()
        ySuperscriptYOffset = reader.getShort()
        yStrikeoutSize = reader.getShort()
        yStrikeoutPosition = reader.getShort()
        sFamilyClass = reader.getShort()
        panose = reader.getBytes(10)
        ulUnicodeRange1 = reader.getInt()
        ulUnicodeRange2 = reader.getInt()
        ulUnicodeRange3 = reader.getInt()
        ulUnicodeRange4 = reader.getInt()
        achVendID = reader.getBytes(4)
        fsSelection = reader.getShort()
        usFirstCharIndex = reader.getShort()
        usLastCharIndex = reader.getShort()
        sTypoAscender = reader.getShort()
        sTypoDescender = reader.getShort()
        sTypoLineGap = reader.getShort()
        usWinAscent = reader.getShort()
        usWinDescent = reader.getShort()
        ulCodePageRange1 = reader.getInt()
        ulCodePageRange2 = reader.getInt()
        sxHeight = reader.getShort()
        sCapHeight = reader.getShort()
        usDefaultChar = reader.getShort()
        usBreakChar = reader.getShort()
        usMaxContext = reader.getShort()
        usLowerOpticalPointSize = reader.getShort()
        usUpperOpticalPointSize = reader.getShort()
    }
}