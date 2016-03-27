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

#ifndef _BTABLE_POST_H_
#define _BTABLE_POST_H_

#include "base/types.h"
#include "tables/Table.h"

namespace babo {

class TableInfo;

class post : public Table {
public:
    explicit post(const TableInfo *info = nullptr) : Table(info) {}
    explicit post(Reader &reader, const TableInfo *info = nullptr) : Table(info) { read(reader); }
    virtual ~post() {}

    virtual bool read(Reader &reader) override {
        _version.read(reader);
        _italicAngle.read(reader);
        _underlinePosition = reader.getInt16();
        _underlineThickness = reader.getInt16();
        _isFixedPitch = reader.getUint32();
        _minMemType42 = reader.getUint32();
        _maxMemType42 = reader.getUint32();
        _minMemType1 = reader.getUint32();
        _maxMemType1 = reader.getUint32();

        return reader.ok();
    }

    Fixed getVersion() const { return _version; }
    Fixed getItalicAngle() const { return _italicAngle; }
    int16 getUnderlinePosition() const { return _underlinePosition; }
    int16 getUnderlineThickness() const { return _underlineThickness; }
    uint32 isFixedPitch() const { return _isFixedPitch; }
    uint32 getMinMemType42() const { return _minMemType42; }
    uint32 getMaxMemType42() const { return _maxMemType42; }
    uint32 getMinMemType1() const { return _minMemType1; }
    uint32 getMaxMemType1() const { return _maxMemType1; }

private:
    Fixed _version;             // 0x00010000 for version 1.0 
                                // 0x00020000 for version 2.0 
                                // 0x00025000 for version 2.5 (deprecated)
                                // 0x00030000 for version 3.0
    Fixed _italicAngle;         // Italic angle in counter-clockwise degrees from the vertical.
                                // Zero for upright text, negative for text that leans to the right (forward).
    int16 _underlinePosition;   // This is the suggested distance of the top of the underline from the baseline
                                // (negative values indicate below baseline). 
                                // The PostScript definition of this FontInfo dictionary key
                                // (the y coordinate of the center of the stroke)
                                // is not used for historical reasons.
                                // The value of the PostScript key may be calculated by
                                // subtracting half the underlineThickness from the value of this field.
    int16 _underlineThickness;  // Suggested values for the underline thickness.
    uint32 _isFixedPitch;       // Set to 0 if the font is proportionally spaced,
                                // non-zero if the font is not proportionally spaced (i.e. monospaced).
    uint32 _minMemType42;       // Minimum memory usage when an OpenType font is downloaded.
    uint32 _maxMemType42;       // Maximum memory usage when an OpenType font is downloaded.
    uint32 _minMemType1;        // Minimum memory usage when an OpenType font is downloaded as a Type 1 font.
    uint32 _maxMemType1;        // Maximum memory usage when an OpenType font is downloaded as a Type 1 font.
};

} // namespace babo
#endif //_BTABLE_POST_H_
