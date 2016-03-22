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

#ifndef _BTABLE_NAME_H_
#define _BTABLE_NAME_H_

#include "base/types.h"
#include "tables/Table.h"

#include <memory>
#include <locale>
#if !defined (__CYGWIN__)
    #include <codecvt>
#endif
#include <string>

namespace babo {

class TableInfo;

class name : public Table {
public:
    explicit name(const TableInfo *info = nullptr) : Table(info) {}
    explicit name(Reader &reader, const TableInfo *info = nullptr) : Table(info) { read(reader); }
    virtual ~name() {}

    virtual bool read(Reader &reader) override {
        uint32 delta = reader.tell();
        _format = reader.getUint16();
        _count = reader.getUint16();
        _stringOffset = reader.getUint16();
        _nameRecord.resize(_count);
        for (auto &nameRecord : _nameRecord) {
            nameRecord.setStringOffset(delta + _stringOffset);
            nameRecord.read(reader);
        }

        std::unique_ptr<char[]> buffer( new char[5000] );
        for (auto &nameRecord : _nameRecord) {

            reader.seek(delta + _stringOffset + nameRecord.getOffset());
            reader.read(buffer.get(), nameRecord.getLength());

            buffer[nameRecord.getLength()] = '\0';
            buffer[nameRecord.getLength()+1] = '\0';

            // FIXME
            wstring str(reinterpret_cast<wchar_t *>(buffer.get()));
//#define TEST_PRINT
#ifdef TEST_PRINT
            wprintf(L"%ls\n", str.c_str());
            //std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> convert;
            //std::string utf16String = convert.to_bytes(str);
            //wprintf("%ls\n", utf16String.c_str());
#endif
        }
        return reader.ok();
    }

    uint16 getFormat() const { return _format; }
    uint16 getCount() const { return _count; }

public:
    class NameRecord {
    public:
        NameRecord(uint16 stringOffset = 0) : _stringOffset(stringOffset) {}
        ~NameRecord() {}

        bool read(Reader &reader) {
            _platformID = reader.getUint16();
            _encodingID = reader.getUint16();
            _languageID = reader.getUint16();
            _nameID = reader.getUint16();
            _length = reader.getUint16();
            _offset = reader.getUint16();

            return reader.ok();
        }

        void setStringOffset(uint32 stringOffset) { _stringOffset = stringOffset; }
        uint16 getLength() const { return _length; }
        uint16 getOffset() const { return _offset; }

    private:
        uint16 _platformID; // Platform ID.
        uint16 _encodingID; // Platform-specific encoding ID.
        uint16 _languageID; // Language ID.
        uint16 _nameID;     // Name ID.
        uint16 _length;     // String length (in bytes).
        uint16 _offset;     // String offset from start of storage area (in bytes).

        uint32 _stringOffset;
    };

private:
    uint16 _format;
    uint16 _count;          // Number of name records.
    uint16 _stringOffset;   // Offset to start of string storage (from start of table).
    vector<NameRecord> _nameRecord; // The name records where count is the number of records.
};

} // namespace babo
#endif //_BTABLE_NAME_H_
