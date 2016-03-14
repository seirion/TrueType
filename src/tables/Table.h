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

#ifndef _BTABLE_H_
#define _BTABLE_H_

#include "base/types.h"
#include "base/Reader.h"
#include "types/Fixed.h"

using namespace std;
using namespace babo;

namespace babo {

class Table {
public:
    Table(const TableInfo *info = nullptr) : _tableInfo(info) {}
    virtual ~Table() {}
    virtual bool read(Reader &reader) = 0;

    void setTableInfo(const TableInfo *info) { _tableInfo = info; }
    const TableInfo *getTableInfo() const { return _tableInfo; }

protected:
    const TableInfo *_tableInfo;
};

} // namespace babo
#endif // _BTABLE_H_
