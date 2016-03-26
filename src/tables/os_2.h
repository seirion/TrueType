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

#ifndef _BTABLE_OS_2_H_
#define _BTABLE_OS_2_H_

#include "base/types.h"
#include "tables/Table.h"

namespace babo {

class TableInfo;

class os_2 : public Table {
public:
    explicit os_2(const TableInfo *info = nullptr) : Table(info) {}
    explicit os_2(Reader &reader, const TableInfo *info = nullptr) : Table(info) { read(reader); }
    virtual ~os_2() {}

    virtual bool read(Reader &reader) override {
        _version = reader.getUint16();
        _xAvgCharWidth = reader.getInt16();
        _usWeightClass = reader.getUint16();
        _usWidthClass = reader.getUint16();
        _fsType = reader.getUint16();
        _ySubscriptXSize = reader.getInt16();
        _ySubscriptYSize = reader.getInt16();
        _ySubscriptXOffset = reader.getInt16();
        _ySubscriptYOffset = reader.getInt16();
        _ySuperscriptXSize = reader.getInt16();
        _ySuperscriptYSize = reader.getInt16();
        _ySuperscriptXOffset = reader.getInt16();
        _ySuperscriptYOffset = reader.getInt16();
        _yStrikeoutSize = reader.getInt16();
        _yStrikeoutPosition = reader.getInt16();
        _sFamilyClass = reader.getInt16();
        reader.read((char *)_panose, sizeof(_panose));
        _ulUnicodeRange1 = reader.getUint32();
        _ulUnicodeRange2 = reader.getUint32();
        _ulUnicodeRange3 = reader.getUint32();
        _ulUnicodeRange4 = reader.getUint32();
        reader.read((char *)_achVendID, sizeof(_achVendID));
        _fsSelection = reader.getUint16();
        _usFirstCharIndex = reader.getUint16();
        _usLastCharIndex = reader.getUint16();
        _sTypoAscender = reader.getInt16();
        _sTypoDescender = reader.getInt16();
        _sTypoLineGap = reader.getInt16();
        _usWinAscent = reader.getUint16();
        _usWinDescent = reader.getUint16();
        _ulCodePageRange1 = reader.getUint32();
        _ulCodePageRange2 = reader.getUint32();
        _sxHeight = reader.getInt16();
        _sCapHeight = reader.getInt16();
        _usDefaultChar = reader.getUint16();
        _usBreakChar = reader.getUint16();
        _usMaxContext = reader.getUint16();
        _usLowerOpticalPointSize = reader.getUint16();
        _usUpperOpticalPointSize = reader.getUint16();

        return reader.ok();
    }

    uint16 getVersion() const { return _version; }
    int16 getXAvgCharWidth() const { return _xAvgCharWidth; }
    uint16 getUsWeightClass() const { return _usWeightClass; }
    uint16 getUsWidthClass() const { return _usWidthClass; }
    uint16 getFsType() const { return _fsType; }
    int16 getYSubscriptXSize() const { return _ySubscriptXSize; }
    int16 getYSubscriptYSize() const { return _ySubscriptYSize; }
    int16 getYSubscriptXOffset() const { return _ySubscriptXOffset; }
    int16 getySubscriptYOffset() const { return _ySubscriptYOffset; }
    int16 getySuperscriptXSize() const { return _ySuperscriptXSize; }
    int16 getySuperscriptYSize() const { return _ySuperscriptYSize; }
    int16 getSuperscriptXOffset() const { return _ySuperscriptXOffset; }
    int16 getYSuperscriptYOffset() const { return _ySuperscriptYOffset; }
    int16 getYStrikeoutSize() const { return _yStrikeoutSize; }
    int16 getYStrikeoutPosition() const { return _yStrikeoutPosition; }
    int16 getSFamilyClass() const { return _sFamilyClass; }
    uint8 getPanose() const { return _panose[10]; }
    uint32 getUlUnicodeRange1() const { return _ulUnicodeRange1; }
    uint32 getUlUnicodeRange2() const { return _ulUnicodeRange2; }
    uint32 getUlUnicodeRange3() const { return _ulUnicodeRange3; }
    uint32 getUlUnicodeRange4() const { return _ulUnicodeRange4; }
    string getAchVendID() const { return string(_achVendID, sizeof(_achVendID)); }
    uint16 getFsSelection() const { return _fsSelection; }
    uint16 getUsFirstCharIndex() const { return _usFirstCharIndex; }
    uint16 getUsLastCharIndex() const { return _usLastCharIndex; }
    int16 getSTypoAscender() const { return _sTypoAscender; }
    int16 getSTypoDescender() const { return _sTypoDescender; }
    int16 getSTypoLineGap() const { return _sTypoLineGap; }
    uint16 getUsWinAscent() const { return _usWinAscent; }
    uint16 getUsWinDescent() const { return _usWinDescent; }
    uint32 getUlCodePageRange1() const { return _ulCodePageRange1; }
    uint32 getUlCodePageRange2() const { return _ulCodePageRange2; }
    int16 getSxHeight() const { return _sxHeight; }
    int16 getSCapHeight() const { return _sCapHeight; }
    uint16 getUsDefaultChar() const { return _usDefaultChar; }
    uint16 getUsBreakChar() const { return _usBreakChar; }
    uint16 getUsMaxContext() const { return _usMaxContext; }
    uint16 getUsLowerOpticalPointSize() const { return _usLowerOpticalPointSize; }
    uint16 getUsUpperOpticalPointSize() const { return _usUpperOpticalPointSize; }

private:
    uint16 _version; // 0x0005
    int16 _xAvgCharWidth;
    uint16 _usWeightClass;
    uint16 _usWidthClass;
    uint16 _fsType;
    int16 _ySubscriptXSize;
    int16 _ySubscriptYSize;
    int16 _ySubscriptXOffset;
    int16 _ySubscriptYOffset;
    int16 _ySuperscriptXSize;
    int16 _ySuperscriptYSize;
    int16 _ySuperscriptXOffset;
    int16 _ySuperscriptYOffset;
    int16 _yStrikeoutSize;
    int16 _yStrikeoutPosition;
    int16 _sFamilyClass;
    uint8 _panose[10];
    uint32 _ulUnicodeRange1; // Bits 0-31
    uint32 _ulUnicodeRange2; // Bits 32-63
    uint32 _ulUnicodeRange3; // Bits 64-95
    uint32 _ulUnicodeRange4; // Bits 96-127
    int8 _achVendID[4];
    uint16 _fsSelection;
    uint16 _usFirstCharIndex;
    uint16 _usLastCharIndex;
    int16 _sTypoAscender;
    int16 _sTypoDescender;
    int16 _sTypoLineGap;
    uint16 _usWinAscent;
    uint16 _usWinDescent;
    uint32 _ulCodePageRange1; // Bits 0-31
    uint32 _ulCodePageRange2; // Bits 32-63
    int16 _sxHeight;
    int16 _sCapHeight;
    uint16 _usDefaultChar;
    uint16 _usBreakChar;
    uint16 _usMaxContext;
    uint16 _usLowerOpticalPointSize;
    uint16 _usUpperOpticalPointSize;
};

} // namespace babo
#endif //_BTABLE_OS_2_H_
