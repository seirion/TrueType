package com.babo.ttf.io

import java.io.File
import java.io.RandomAccessFile


class FileReader(private val path: String) {
    private lateinit var file: File
    private lateinit var reader: RandomAccessFile
    init {
        load()
    }

    private fun load() {
        file = File(path)
        reader = RandomAccessFile(file, "r")
    }

    fun seek(position: Long) {
        reader.seek(position)
    }

    fun tell(): Long {
        return reader.filePointer
    }

    fun getByte(): Byte {
        return reader.read().toByte()
    }

    fun getShort(): Short {
        val bytes = getBytes(2)
        val (high, low) = bytes.map { it.toUByte() }.map { it.toInt() }
        return (high.shl(8) or low).toShort()
    }

    fun getInt(): Int {
        val bytes = getBytes(4)
        val (b0, b1, b2, b3) = bytes.map { it.toUByte() }.map { it.toInt() }
        return (b0.shl(24) or b1.shl(16) or b2.shl(8) or b3)
    }

    fun getLong(): Long {
        val bytes = getBytes(8).map { it.toUByte() }.map { it.toLong() }
        return (bytes[0].shl(56) or bytes[1].shl(48) or
                bytes[2].shl(40) or bytes[3].shl(32) or
                bytes[4].shl(24) or bytes[5].shl(16) or
                bytes[6].shl(8) or bytes[7])
    }

    fun getBytes(size: Int): ByteArray {
        val bytes = ByteArray(size)
        reader.read(bytes)
        return bytes
    }
}