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

#ifndef _BTABLE_CMAP_MAPPING_H_
#define _BTABLE_CMAP_MAPPING_H_

#include "base/types.h"
#include "base/Reader.h"

#include <vector>

namespace babo {

class cmap_mapping {
public:
    cmap_mapping(uint16 format) : _format(format) {}
    virtual ~cmap_mapping() {}

    uint16 getFormat() const { return _format; }
    virtual bool read(Reader &reader) = 0;

public:
    static cmap_mapping *build(uint16 format);

protected:
    uint16  _format;
};

/**
 * Format 0: Byte encoding table
 * the Apple standard character to glyph index mapping table.
 */
class cmap_mapping_format0 : public cmap_mapping {
public:
    cmap_mapping_format0(uint16 format) : cmap_mapping(format) {}
    virtual ~cmap_mapping_format0() {}

    virtual bool read(Reader &reader) override {
        _length = reader.getUint16();
        _language = reader.getUint16();
        for (int i = 0; i < _length; i++) {
            _glyphIdArray[i] = reader.getUint8();
        }
        return reader.ok();
    }

private:
    uint16 _length;     // This is the length in bytes of the subtable.
    uint16 _language;   //
    uint8 _glyphIdArray[256]; // An array that maps character codes to glyph index values.
};

/**
 * Format 4: Segment mapping to delta values
 */
class cmap_mapping_format4 : public cmap_mapping {
public:
    cmap_mapping_format4(uint16 format) : cmap_mapping(format) {}
    virtual ~cmap_mapping_format4() {}

    virtual bool read(Reader &reader) override {
        _length = reader.getUint16();
        _language = reader.getUint16();
        _segCountX2 = reader.getUint16();
        _searchRange = reader.getUint16();
        _entrySelector = reader.getUint16();
        _rangeShift = reader.getUint16();

        uint16 size = _length - (_segCountX2 * 4);
        _endCount.resize(size);
        for (uint32 i = 0; i < size; i++) {
            _endCount[i] = reader.getUint16();
        }

        _reservedPad = reader.getUint16();

        _startCount.resize(size);
        for (uint32 i = 0; i < size; i++) {
            _startCount[i] = reader.getUint16();
        }
        _idDelta.resize(size);
        for (uint32 i = 0; i < size; i++) {
            _idDelta[i] = reader.getUint16();
        }
        _idRangeOffset.resize(size);
        for (uint32 i = 0; i < size; i++) {
            _idRangeOffset[i] = reader.getUint16();
        }
        _glyphIdArray.resize(size);
        for (uint32 i = 0; i < size; i++) {
            _glyphIdArray[i] = reader.getUint16();
        }

        return reader.ok();
    }

private:
    uint16 _length;                 // This is the length in bytes of the subtable.
    uint16 _language;               // 
    uint16 _segCountX2;             // 2 x segCount.
    uint16 _searchRange;            // 2 x (2**floor(log2(segCount)))
    uint16 _entrySelector;          // log2(searchRange/2)
    uint16 _rangeShift;             // 2 x segCount - searchRange
    std::vector<uint16> _endCount;  // End characterCode for each segment, last=0xFFFF.
    uint16 _reservedPad;            // Set to 0.
    std::vector<uint16> _startCount;// Start character code for each segment.
    std::vector<int16> _idDelta;    // Delta for all character codes in segment.
    std::vector<uint16> _idRangeOffset; //Offsets into glyphIdArray or 0
    std::vector<uint16> _glyphIdArray;  //Glyph index array (arbitrary length)
};

} // namespace babo
#endif //_BTABLE_CMAP_MAPPING_H_
