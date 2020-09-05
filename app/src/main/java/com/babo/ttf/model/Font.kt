package com.babo.ttf.model

import com.babo.ttf.io.FileReader

class Font {
    val fontInfo = FontInfo()

    fun read(reader: FileReader) {
        fontInfo.read(reader)
    }
}