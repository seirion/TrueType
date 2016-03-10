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

#include <string>
#include "base/types.h"

using namespace std;
using namespace babo;

#if defined (__CYGWIN__)
    #include <sstream>
#endif

namespace babo {

class Fixed {
public:
    explicit Fixed(uint32 value = 0) : _high(value >> 16), _low(value & 0xFFFF) {}
    explicit Fixed(int16 high = 0, uint16 low = 0) : _high(high), _low(low) {}

    string version() const {
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
