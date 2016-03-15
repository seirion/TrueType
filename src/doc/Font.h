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
#include "tables/head.h"
#include "tables/hhea.h"
#include "tables/maxp.h"

namespace babo {

class Font {
public:
    Font() : _open(false) {}
    explicit Font(Reader &reader) : _open(false) {
        open(reader);
    }
    ~Font() {}

    bool open(Reader &reader);
    bool readAllTableInfo(Reader &reader);

    const FontInfo &getFontInfo() const { return _fontInfo; }
    const TableInfo getTableInfo(const string &tag) const {
        auto it = _tableInfos.find(tag);
        if (it == _tableInfos.end()) {
            return TableInfo();
        }
        return it->second;
    }

    const head &get_head() const { return _head; }
    const hhea &get_hhea() const { return _hhea; }
    const maxp &get_maxp() const { return _maxp; }

private:
    bool _open;
    FontInfo _fontInfo;
    map<string, TableInfo> _tableInfos;

    head _head;
    hhea _hhea;
    maxp _maxp;
};

} // namespace babo
#endif //_BFONT_H_
