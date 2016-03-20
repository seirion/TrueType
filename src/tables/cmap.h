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

#ifndef _BTABLE_CMAP_H_
#define _BTABLE_CMAP_H_

#include "base/types.h"
#include "tables/Table.h"
#include "tables/cmap_mapping.h"

#include <vector>

namespace babo {

class TableInfo;

/**
 * mapping of character codes to the glyph index
 */
class cmap : public Table {
public:
    explicit cmap(const TableInfo *info = nullptr) : Table(info) {}
    explicit cmap(Reader &reader, const TableInfo *info = nullptr) : Table(info) { read(reader); }
    virtual ~cmap() {}

    virtual bool read(Reader &reader) override {
        _version = reader.getUint16();
        _numTables = reader.getUint16();

        for (int32 i = 0; i < _numTables; i++) {
            SubTable table(reader);
            _subTables.push_back(table);
        }

        for (auto &subTable : _subTables) {
            reader.seek(_tableInfo->getOffset() + subTable.getOffset());

            uint16 format = reader.getUint16();
            cmap_mapping *mapping = cmap_mapping::build(format);
            if (!mapping) {
                //"===== not support this format currently\n";
                continue;
            }
            mapping->read(reader);
            subTable.setMapping(mapping);
        }
        return reader.ok();
    }

public:
    class SubTable {
    public:
        SubTable(Reader &reader) : _mapping(nullptr) {
            _platformID = reader.getUint16();
            _encodingID = reader.getUint16();
            _offset = reader.getUint32();
        }
        virtual ~SubTable() { delete _mapping; }

        uint16 getPlatformID() const { return _platformID; }
        uint16 getEncodingID() const { return _encodingID; }
        uint16 getOffset() const { return _offset; }
        cmap_mapping *getMapping() const { return _mapping; }

        void setMapping(cmap_mapping *mapping) { _mapping = mapping; }

    private:
        uint16 _platformID; // Platform ID.
        uint16 _encodingID; // Platform-specific encoding ID.
        uint32 _offset;     // Byte offset from beginning of table to the subtable for this encoding.
        cmap_mapping *_mapping;
    };

    enum { // Platforms
        Unicode = 0,        // Indicates Unicode version.
        Macintosh = 1,      // Script Manager code.
                            // (reserved; do not use)
        Microsoft = 3,      // Microsoft encoding.
    };
public:
    uint16 getVersion() const { return _version; }
    uint16 getNumTables() const { return _numTables; }
    const vector<SubTable> &getSubTables() const { return _subTables; }

private:
    uint16  _version;   // Table version number (0).
    uint16  _numTables; // Number of encoding tables that follow.

    std::vector<SubTable> _subTables;
};

} // namespace babo
#endif //_BTABLE_CMAP_H_
