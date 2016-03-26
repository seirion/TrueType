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

#include "doc/Font.h"
#include "tables/TableBuilder.h"

namespace babo {

bool Font::read(Reader &reader) {
    _open = false;
    _fontInfo.read(reader);
    int32 size = _fontInfo.getNumTables();
    for (int32 i = 0; i < size; i++) {
        if (!readAllTableInfo(reader)) {
            return false;
        }
    }

    for (auto &t: _tableInfos) {
        const string &tag = t.first;
        const TableInfo &info = t.second;

        reader.seek(info.getOffset());
        if (!readTable(reader, tag, info)) return false;
    }

    vector<string> job(move(_job));
    for (string &tag : job) {
        auto it = _tableInfos.find(tag);
        if (it == _tableInfos.end()) continue;

        const TableInfo &info = _tableInfos[tag];

        reader.seek(info.getOffset());
        if (!readTable(reader, tag, info)) return false;
    }

    _job.clear();
    _open = reader.ok();
    return _open;
}

bool Font::readTable(Reader &reader, const string &tag, const TableInfo &info) {
    Table *table = TableBuilder::build(tag);

    if (table) {
        table->setTableInfo(&info);
        table->read(reader);
        _tables[tag] = table;
    }
    return reader.ok();
}

bool Font::readAllTableInfo(Reader &reader) {
    TableInfo info;
    info.read(reader);
    _tableInfos[info.getTag()] = info;
    return reader.ok();
}

} // namespace babo
