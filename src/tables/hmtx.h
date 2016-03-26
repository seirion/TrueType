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

#ifndef _BTABLE_HMTX_H_
#define _BTABLE_HMTX_H_

#include "base/types.h"
#include "tables/Table.h"
#include "tables/hhea.h"
#include "tables/maxp.h"

namespace babo {

class TableInfo;

class hmtx : public Table {
public:
    explicit hmtx(const TableInfo *info = nullptr) : Table(info) {}
    explicit hmtx(Reader &reader, const TableInfo *info = nullptr) : Table(info) { read(reader); }
    virtual ~hmtx() {}

    virtual bool read(Reader &reader) override {
        
        {
            const hhea *table = reinterpret_cast<const hhea *>(Font::instance().getTable("hhea"));
            int size = table->getNumberOfHMetrics();
            _hMetrics.resize(size);
            for (int i = 0; i < size; i++) {
                _hMetrics[i].read(reader);
            }
        }

        {
            const maxp *table = reinterpret_cast<const maxp *>(Font::instance().getTable("maxp"));
            int size = table->getNumGlyphs();
            _leftSideBearing.resize(size);
            for (int i = 0; i < size; i++) {
                _leftSideBearing[i] = reader.getInt16();
            }
        }

        return reader.ok();
    }

public:
    struct LongHorMetric {
        uint16 _advanceWidth;
        int16 _lsb;

        bool read(Reader &reader) {
            _advanceWidth = reader.getUint16();
            _lsb = reader.getInt16();
            return reader.ok();
        }
    };
private:
    vector<LongHorMetric> _hMetrics;
    vector<uint16> _leftSideBearing;
};

} // namespace babo
#endif //_BTABLE_HMTX_H_
