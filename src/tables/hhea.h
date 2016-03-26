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

#ifndef _BTABLE_HHEA_H_
#define _BTABLE_HHEA_H_

#include "base/types.h"
#include "tables/Table.h"

namespace babo {

class TableInfo;

class hhea : public Table {
public:
    explicit hhea(const TableInfo *info = nullptr) : Table(info) {}
    explicit hhea(Reader &reader, const TableInfo *info = nullptr) : Table(info) { read(reader); }
    virtual ~hhea() {}

    virtual bool read(Reader &reader) override {

        _version.read(reader);
        _ascender = reader.getInt16();
        _descender = reader.getInt16();
        _lineGap = reader.getInt16();
        _advanceWidthMax = reader.getUint16();
        _minLeftSideBearing = reader.getInt16();
        _minRightSideBearing = reader.getInt16();
        _xMaxExtent = reader.getInt16();
        _caretSlopeRise = reader.getInt16();
        _caretSlopeRun = reader.getInt16();
        _caretOffset = reader.getInt16();
        reader.read((char *)_reserved, sizeof(_reserved));
        _metricDataFormat = reader.getInt16();
        _numberOfHMetrics = reader.getUint16();

        return reader.ok();
    }

    Fixed getVersion() const { return _version; }
    int16 getAscender() const { return _ascender; }
    int16 getDescender() const { return _descender; }
    int16 getLineGap() const { return _lineGap; }
    uint16 getAdvanceWidthMax() const { return _advanceWidthMax; }
    int16 getMinLeftSideBearing() const { return _minLeftSideBearing; }
    int16 getMinRightSideBearing() const { return _minRightSideBearing; }
    int16 getXMaxExtent() const { return _xMaxExtent; }
    int16 getCaretSlopRise() const { return _caretSlopeRise; }
    int16 getCaretSlopeRun() const { return _caretSlopeRun; }
    int16 getCaretOffset() const { return _caretOffset; }
    int16 getMetricDataForamt() const { return _metricDataFormat; }
    uint16 getNumberOfHMetrics() const { return _numberOfHMetrics; }

private:
    Fixed _version;             // Table version number    0x00010000 for version 1.0.
    int16 _ascender;            // Typographic ascent. (Distance from baseline of highest ascender)
    int16 _descender;           // Typographic descent. (Distance from baseline of lowest descender)
    int16 _lineGap;             // Typographic line gap.
                                // Negative LineGap values are treated as zero
                                // in Windows 3.1, System 6, and System 7.
    uint16 _advanceWidthMax;    // Maximum advance width value in 'hmtx' table.
    int16 _minLeftSideBearing;  // Minimum left sidebearing value in 'hmtx' table.
    int16 _minRightSideBearing; // Minimum right sidebearing value; calculated as Min(aw - lsb - (xMax - xMin)).
    int16 _xMaxExtent;          // Max(lsb + (xMax - xMin)).
    int16 _caretSlopeRise;      // Used to calculate the slope of the cursor (rise/run); 1 for vertical.
    int16 _caretSlopeRun;       // 0 for vertical.
    int16 _caretOffset;         // The amount by which a slanted highlight on a glyph needs to be shifted
                                // to produce the best appearance. Set to 0 for non-slanted fonts
    int16 _reserved[4];         //SHORT   (reserved)  set to 0
                                //SHORT   (reserved)  set to 0
                                //SHORT   (reserved)  set to 0
                                //SHORT   (reserved)  set to 0
    int16 _metricDataFormat;    //  0 for current format.
    uint16 _numberOfHMetrics;   //  Number of hMetric entries in 'hmtx' table
};

} // namespace babo
#endif //_BTABLE_HHEA_H_
