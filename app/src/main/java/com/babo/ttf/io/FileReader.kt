package com.babo.ttf.io

import java.io.File
import java.io.FileInputStream
import java.io.InputStream


class FileReader(private val path: String) {
    private lateinit var file: File
    private lateinit var inputStream: InputStream
    init {
        load()
    }

    private fun load() {
        file = File(path)
        inputStream = FileInputStream(file).buffered()
    }

    fun getByte(): Byte {
        return inputStream.read().toByte()
    }

    fun getShort(): Short {
        val bytes = read(2)
        val (high, low) = bytes.map { it.toUByte() }.map { it.toInt() }
        return (high.shl(8) or low).toShort()
    }

    fun getInt(): Int {
        val bytes = read(4)
        val (b0, b1, b2, b3) = bytes.map { it.toUByte() }.map { it.toInt() }
        return (b0.shl(24) or b1.shl(16) or b2.shl(8) or b3)
    }

    private fun read(size: Int): ByteArray {
        val bytes = ByteArray(size)
        inputStream.read(bytes)
        return bytes
    }
}