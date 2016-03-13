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
#include "base/types.h"
#include "base/ReadWrite.h"

#if defined(_WIN32) || defined(_WIN64)
    #include <Winsock2.h>
#elif defined (__linux__) || defined (__CYGWIN__) || defined (__APPLE__)
    #include <netinet/in.h>
#endif

#if defined (__CYGWIN__)
    #include <sstream>
#endif

using namespace std;
using namespace babo;

namespace babo {

class Fixed : public ReadWrite {
public:
    explicit Fixed(uint32 value = 0) : _high(value >> 16), _low(value & 0xFFFF) {}
    explicit Fixed(int16 high, uint16 low) : _high(high), _low(low) {}
    explicit Fixed(Reader &reader) { read(reader); }
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

    string toString() const {
#if defined (__CYGWIN__)
      std::ostringstream os ;
      os << _high << "." << _low;
      return os.str() ;
#else
        return to_string(_high) + "." + to_string(_low); }
#endif
}
private:
    int16 _high;
    uint16 _low;
};

} // namespace babo
#endif //_BFIXED_H_
