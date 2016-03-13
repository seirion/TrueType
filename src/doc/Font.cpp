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
    int32 numTable = _fontInfo.getNumTables();
    for (int32 i = 0; i < numTable; i++) {
        if (!readAllTables(reader)) {
            return false;
        }
    }

    for (auto &t: tables) {
        const string &tag = t.first;
        const Table &table = t.second;

        if (tag == "head") { // FIXME
            _head.read(reader);
        }
    }

    return reader.ok();
}

bool Font::readAllTables(Reader &reader) {
    Table table;
    table.read(reader);
    tables[table.getTag()] = table;
    return reader.ok();
}

} // namespace babo