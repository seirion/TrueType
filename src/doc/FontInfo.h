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

#ifndef _BFONT_INFO_H_
#define _BFONT_INFO_H_

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

#include "base/types.h"
#include "base/Reader.h"
#include "types/Fixed.h"

using namespace std;
using namespace babo;

namespace babo {

class FontInfo {
public:
    explicit FontInfo() {}
    explicit FontInfo(Reader &reader) { read(reader); }

    bool read(Reader &reader) {
        sfnt_version.read(reader);
        numTables = reader.getUint16();
        searchRange = reader.getUint16();
        entrySelector = reader.getUint16();
        rangeShift = reader.getUint16();
        return (reader.ok());
    }

    Fixed version() const { return sfnt_version; }
    uint16 getNumTables() const { return numTables; }
    uint16 getSearchRange() const { return searchRange; }
    uint16 getEntrySelector() const { return entrySelector; }
    uint16 getRangeShift() const { return rangeShift; }

private:
    Fixed sfnt_version;     // 0x00010000 for version 1.0.
    uint16 numTables;       // Number of tables
    uint16 searchRange;     // (Maximum power of 2 <= numTables) * 16
    uint16 entrySelector;   // Log2(Maximum power of 2 <= numTables)
    uint16 rangeShift;      // NumTables * 16 - serachRange
};

} // namespace babo
#endif // _BFONT_INFO_H_
