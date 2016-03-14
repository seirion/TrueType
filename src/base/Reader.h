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
#ifndef _BREADER_H_
#define _BREADER_H_

#include <fstream>
#include <string>

#if defined(_WIN32) || defined(_WIN64)
    #include <Winsock2.h>
#elif defined (__linux__) || defined (__CYGWIN__) || defined (__APPLE__)
    #include <netinet/in.h>
#endif

#include "base/types.h"

using namespace std;

namespace babo {

class Reader {
public:
    Reader() {}
    Reader(const string& path) { open(path); }
    ~Reader() { close(); }

    Reader& open(const string& path) {
        close();
        file.open(path, ios::in | ios::binary);
        return *this;
    }

    void close() { file.close(); }
    bool is_open() { return file.is_open(); }
    //int32 tell() const { return file.tellg(); }
    void seek(int32 offset) { file.seekg(offset, file.beg); }
    bool ok() const { return file.good(); }

    bool read(char *buffer, uint32 size) {
        file.read(buffer, size);
        return ok();
    }

    int8 getInt8() { return static_cast<int8>(getUint8()); }
    int16 getInt16() { return static_cast<int16>(getUint16()); }
    int32 getInt32() { return static_cast<int32>(getUint32()); }
    int64 getInt64() { return static_cast<int64>(getUint64()); }

    uint8 getUint8() {
        uint8 v;
        file.read((char *)(&v), sizeof(v));
        return v;
    }

    uint16 getUint16() {
        uint16 v;
        file.read((char *)(&v), sizeof(v));
        return ntohs(v);
    }

    uint32 getUint32() {
        uint32 v;
        file.read((char *)(&v), sizeof(v));
        return ntohl(v);
    }

    uint64 getUint64() {
        uint32 high, low;
        file.read((char *)(&high), sizeof(high));
        file.read((char *)(&low), sizeof(low));
        return ((uint64)ntohl(high) << 32) | (ntohl(low));
    }

private:
    ifstream file;
};

} // namespace
#endif //_BREADER_H_
