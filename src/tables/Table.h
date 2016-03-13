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
    Table() {}
    explicit Table(Reader &reader) { read(reader); }
    virtual ~Table() {}

    bool read(Reader &reader) {
        const uint32 TAG_LENGTH = 4;
        _tag.resize(TAG_LENGTH);
        reader.read((char *)&_tag[0], TAG_LENGTH);
        _checkSum = reader.getUint32();
        _offset = reader.getUint32();
        _length = reader.getUint32();
        return (reader.ok());
    }

    uint32 calcTableChecksum(uint32 *address, uint32 Length) const {
        uint32 sum = 0;
        uint32 *endptr = address+((Length+3) & ~3) / sizeof(uint32);
        while (address < endptr)
            sum += *address++;
        return sum;
    }

    string getTag() const { return _tag; }
    uint32 getCheckSum() const { return _checkSum; }
    uint32 getOffset() const { return _offset; }
    uint32 getLength() const { return _length; }

private:
    string _tag;        // 4 -byte identifier.
    uint32 _checkSum;   // CheckSum for this table.
    uint32 _offset;     // Offset from beginning of TrueType font file.
    uint32 _length;     // Length of this table.
};

} // namespace babo
#endif // _BTABLE_H_
