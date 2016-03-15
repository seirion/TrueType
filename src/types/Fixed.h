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

#ifndef _BFIXED_H_
#define _BFIXED_H_

#include <cstdio>
#include <string>

#if defined(_WIN32) || defined(_WIN64)
    #include <Winsock2.h>
#elif defined (__linux__) || defined (__CYGWIN__) || defined (__APPLE__)
    #include <netinet/in.h>
#endif

#include <sstream>
#include <iomanip>

#include "base/types.h"
#include "base/ReadWrite.h"

using namespace std;
using namespace babo;

namespace babo {

class Fixed : public ReadWrite {
public:
    explicit Fixed(uint32 value = 0) : _high(value >> 16), _low(value & 0xFFFF) {}
    explicit Fixed(int16 high, uint16 low) : _high(high), _low(low) {}
    explicit Fixed(Reader &reader) { read(reader); }
    Fixed(float f) { fromFloat(f); }
    Fixed(double d) { fromDouble(d); }
    virtual ~Fixed() {}

    virtual Reader& read(Reader &reader) override {
        int32 temp = reader.getInt32();
        _high = (temp>> 16); _low = (temp & 0xFFFF);
        return reader;
    }

    /*
    virtual Writer& write(Writer &writer) const override {
        int32 temp((int)_high << 16 | _low);
        temp = htonl(temp);
        return writer.write(reinterpret_cast<char *>(&temp), sizeof(temp));
    }
    */

    float toFloat() const { return _high + static_cast<float>(_low) / 0xFFFF; }
    double toDouble() const { return _high + static_cast<double>(_low) / 0xFFFF; }
    void fromFloat(float f) {
        _high = static_cast<int>(f);
        _low = static_cast<int>((f - _high) * 0xFFFF);
    }
    void fromDouble(double d) {
        _high = static_cast<int>(d);
        _low = static_cast<int>((d - _high) * 0xFFFF);
    }

    string toString() const {
        std::ostringstream os ;
        os.setf(ios::fixed, ios::floatfield);
        os << setprecision(1) << toDouble();
        return os.str() ;
    }

    int32 value() const { return (static_cast<int32>(_high) << 16) | _low; }

private:
    int16 _high;
    uint16 _low;
};

} // namespace babo
#endif //_BFIXED_H_
