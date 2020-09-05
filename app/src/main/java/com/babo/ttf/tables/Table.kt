package com.babo.ttf.tables

import com.babo.ttf.io.FileReader

/**
 * The required tables
 * 'cmap'   character to glyph mapping
 * 'glyf'   glyph data
 * 'head'   font header
 * 'hhea'   horizontal header
 * 'hmtx'   horizontal metrics
 * 'loca'   index to location
 * 'maxp'   maximum profile
 * 'name'   naming
 * 'post'   PostScript
 *
 * The optional tables
 * 'cvt '   control value
 * 'fpgm'   font program
 * 'hdmx'   horizontal device metrics
 * 'kern'   kerning
 * 'OS/2'   OS/2
 * 'prep'   control value program
 */

open abstract class Table {
    lateinit var tableInfo: TableInfo
    abstract fun read(reader: FileReader)

    companion object {
        fun from(tag: String): Table? {
            return when (tag) {
                "head" -> head()
                else -> null
            }
        }
    }
}
