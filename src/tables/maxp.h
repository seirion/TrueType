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

#ifndef _BTABLE_MAXP_H_
#define _BTABLE_MAXP_H_

#include "base/types.h"
#include "tables/Table.h"

namespace babo {

class TableInfo;

class maxp : public Table {
public:
    explicit maxp(const TableInfo *info = nullptr) : Table(info) {}
    explicit maxp(Reader &reader, const TableInfo *info = nullptr) : Table(info) { read(reader); }
    virtual ~maxp() {}

    virtual bool read(Reader &reader) override {

        _version.read(reader);
        _numGlyphs = reader.getUint16();
        if (_version.value() == 0x00005000) return reader.ok();

        _maxPoints = reader.getUint16();
        _maxContours = reader.getUint16();
        _maxCompositePoints = reader.getUint16();
        _maxCompositeContours = reader.getUint16();
        _maxZones = reader.getUint16();
        _maxTwilightPoints = reader.getUint16();
        _maxStorage = reader.getUint16();
        _maxFunctionDefs = reader.getUint16();
        _maxInstructionDefs = reader.getUint16();
        _maxStackElements = reader.getUint16();
        _maxSizeOfInstructions = reader.getUint16();
        _maxComponentElements = reader.getUint16();
        _maxComponentDepth = reader.getUint16();

        return reader.ok();
    }

    Fixed getVersion() const { return _version; }
    uint16 getNumGlyphs() const { return _numGlyphs; }
    uint16 getMaxPoints() const { return _maxPoints; }
    uint16 getMaxContours() const { return _maxContours; }
    uint16 getMaxCompositePoints() const { return _maxCompositePoints; }
    uint16 getMaxCompositeCoutours() const { return _maxCompositeContours; }
    uint16 getMaxZones() const { return _maxZones; }
    uint16 getMaxTwilightPoints() const { return _maxTwilightPoints; }
    uint16 getMaxStorage() const { return _maxStorage; }
    uint16 getMaxFunctionDefs() const { return _maxFunctionDefs; }
    uint16 getMaxInstructionDefs() const { return _maxInstructionDefs; }
    uint16 getMaxStackElements() const { return _maxStackElements; }
    uint16 getMaxSizeOfInstructions() const { return _maxSizeOfInstructions; }
    uint16 getMaxComponentElements() const { return _maxComponentElements; }
    uint16 getMaxComponentDepth() const { return _maxComponentDepth; }

private:
    Fixed _version;                 // Table version number    0x00010000 for version 1.0.
    uint16 _numGlyphs;              // The number of glyphs in the font.
    uint16 _maxPoints;              // Maximum points in a non-composite glyph.
    uint16 _maxContours;            // Maximum contours in a non-composite glyph.
    uint16 _maxCompositePoints;     // Maximum points in a composite glyph.
    uint16 _maxCompositeContours;   // Maximum contours in a composite glyph.
    uint16 _maxZones;               // 1 if instructions do not use the twilight zone (Z0), or
                                    // 2 if instructions do use Z0; should be set to 2 in most cases.
    uint16 _maxTwilightPoints;      // Maximum points used in Z0.
    uint16 _maxStorage;             // Number of Storage Area locations.
    uint16 _maxFunctionDefs;        // Number of FDEFs, equals to the highest function number + 1.
    uint16 _maxInstructionDefs;     // Number of IDEFs.
    uint16 _maxStackElements;       // Maximum stack depth2.
    uint16 _maxSizeOfInstructions;  // Maximum byte count for glyph instructions.
    uint16 _maxComponentElements;   // Maximum number of components referenced at "top level"
                                    //     for any composite glyph.
    uint16 _maxComponentDepth;      // Maximum levels of recursion; 1 for simple components.
};

} // namespace babo
#endif //_BTABLE_MAXP_H_
