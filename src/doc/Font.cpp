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

namespace babo {

bool Font::open(Reader &reader) {
    _fontInfo.read(reader);
    int32 size = _fontInfo.getNumTables();
    for (int32 i = 0; i < size; i++) {
        if (!readAllTableInfo(reader)) {
            return false;
        }
    }

    for (auto &t: tableInfos) {
        const string &tag = t.first;
        const TableInfo &tableInfos = t.second;

        reader.seek(tableInfos.getOffset());
        if (tag == "head") { // FIXME
            _head.read(reader);
        }
        else if (tag == "hhea") { // FIXME
            _hhea.read(reader);
        }
    }

    return reader.ok();
}

bool Font::readAllTableInfo(Reader &reader) {
    TableInfo info;
    info.read(reader);
    tableInfos[info.getTag()] = info;
    return reader.ok();
}

} // namespace babo
