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

#ifndef _BTABLE_H_
#define _BTABLE_H_

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

class Table {
public:
    explicit Table() {}
    explicit Table(const int8 *buffer) { load(buffer); }

    bool load(const int8 *buffer) {
        // TODO
    }

private:
    Fixed sfnt_version;     // 0x00010000 for version 1.0.
    uint16 numTables;       // Number of tables
    uint16 searchRange;     // (Maximum power of 2 <= numTables) * 16
    uint16 entrySelector;   // Log2(Maximum power of 2 <= numTables)
    uint16 rangeShift;      // NumTables * 16 - serachRange
};

#endif // _BTABLE_H_
