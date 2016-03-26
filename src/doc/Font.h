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
#ifndef _BFONT_H_
#define _BFONT_H_

#include <map>
#include <string>

#include "base/types.h"
#include "base/Reader.h"
#include "doc/FontInfo.h"
#include "tables/TableInfo.h"
#include "tables/Table.h"

namespace babo {

class Font {
private:
    Font() : _open(false) {}

public:
    static Font &instance() { // singleton
        static Font instance;
        return instance;
    }

    virtual ~Font() {
        for (auto &table : _tables) {
            delete table.second;
        }
    }

    bool read(Reader &reader);
    bool readTable(Reader &reader, const string &tag, const TableInfo &info);
    bool readAllTableInfo(Reader &reader);

    const FontInfo &getFontInfo() const { return _fontInfo; }
    const TableInfo getTableInfo(const string &tag) const {
        auto it = _tableInfos.find(tag);
        if (it == _tableInfos.end()) {
            return TableInfo();
        }
        return it->second;
    }

    const Table* getTable(const string &tag) {
        auto it = _tables.find(tag);
        if (it == _tables.end()) return nullptr;
        else return it->second;
    }

    bool is_open() const { return _open; }

private:
    bool _open;
    FontInfo _fontInfo;
    map<string, TableInfo> _tableInfos;
    map<string, Table*> _tables;
};

} // namespace babo
#endif //_BFONT_H_
