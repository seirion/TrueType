/**
 * Copyright 2016 seirion
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef _BTABLE_HEAD_H_
#define _BTABLE_HEAD_H_

#include "base/types.h"
#include "tables/Table.h"

namespace babo {

class TableInfo;

class head : public Table {
public:
    explicit head(const TableInfo *info = nullptr) : Table(info) {}
    explicit head(Reader &reader, const TableInfo *info = nullptr) : Table(info) { read(reader); }
    virtual ~head() {}

    virtual bool read(Reader &reader) override {
        _version.read(reader);
        _fontRevision.read(reader);
        _checkSumAdjustment = reader.getUint32();
        _magicNumber = reader.getUint32();
        _flags = reader.getUint16();
        _unitsPerEm = reader.getUint16();
        _created = reader.getUint64();
        _modified = reader.getUint64();
        _xMin = reader.getInt16();
        _yMin = reader.getInt16();
        _xMax = reader.getInt16();
        _yMax = reader.getInt16();
        _macStyle = reader.getUint16();
        _lowestRecPPEM = reader.getUint16();
        _fontDirectionHint = reader.getInt16();
        _indexToLocFormat = reader.getInt16();
        _glyphDataFormat = reader.getInt16();

        return reader.ok();
    }

    Fixed getVersion() const { return _version; }
    Fixed getFontRevision() const { return _fontRevision; }
    uint32 getCheckSumAdjustment() const { return _checkSumAdjustment; }
    uint32 getMagicNumber() const { return _magicNumber; }
    uint16 getFlags() const { return _flags; }
    uint16 getUnitsPerEm() const { return _unitsPerEm; }
    uint64 getCreated() const { return _created; }
    uint64 getModified() const { return _modified; }
    int16 getXMin() const { return _xMin; }
    int16 getYMin() const { return _yMin; }
    int16 getXMax() const { return _xMax; }
    int16 getYMax() const { return _yMax; }
    uint16 getMAcStyle() const { return _macStyle; }
    uint16 getLowestRecPPEM() const { return _lowestRecPPEM; }
    int16 getFontDirectionHint() const { return _fontDirectionHint; }
    int16 getIndexToLocFormat() const { return _indexToLocFormat; }
    int16 getGlyphDataFormat() const { return _glyphDataFormat; }

private:
    Fixed _version;            // Table version number    0x00010000 for version 1.0.
    Fixed _fontRevision;       // Set by font manufacturer.
    uint32 _checkSumAdjustment;// To compute: set it to 0, sum the entire font as ULONG, then store 0xB1B0AFBA - sum.
    uint32 _magicNumber;       // Set to 0x5F0F3CF5.
    uint16 _flags;             // Bit 0: Baseline for font at y=0;
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
        uint16 _unitsPerEm;    // Valid range is from 16 to 16384. This value should be a power of 2 for fonts that have TrueType outlines.
        uint64 _created;       // Number of seconds since 12:00 midnight that started January 1st 1904 in GMT/UTC time zone. 64-bit integer
        uint64 _modified;      // Number of seconds since 12:00 midnight that started January 1st 1904 in GMT/UTC time zone. 64-bit integer
        int16 _xMin;           // For all glyph bounding boxes.
        int16 _yMin;           // For all glyph bounding boxes.
        int16 _xMax;           // For all glyph bounding boxes.
        int16 _yMax;           // For all glyph bounding boxes.
        uint16 _macStyle;      // Bit 0: Bold (if set to 1);
                               // Bit 1: Italic (if set to 1)
                               // Bit 2: Underline (if set to 1)
                               // Bit 3: Outline (if set to 1)
                               // Bit 4: Shadow (if set to 1)
                               // Bit 5: Condensed (if set to 1)
                               // Bit 6: Extended (if set to 1)
                               // Bits 7-15: Reserved (set to 0).
        uint16 _lowestRecPPEM; //  Smallest readable size in pixels.
        int16 _fontDirectionHint; // Deprecated (Set to 2).
                                  // 0: Fully mixed directional glyphs;
                                  // 1: Only strongly left to right;
                                  // 2: Like 1 but also contains neutrals;
                                  // -1: Only strongly right to left;
                                  // -2: Like -1 but also contains neutrals. 1
        int16 _indexToLocFormat;  // 0 for short offsets, 1 for long.
        int16 _glyphDataFormat;   // 0 for current format.
};

} // namespace babo
#endif //_BTABLE_HEAD_H_
