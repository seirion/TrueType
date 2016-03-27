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

#ifndef _BTABLE_BUILDER_H_
#define _BTABLE_BUILDER_H_

#include "base/types.h"
#include "tables/cmap.h"
#include "tables/head.h"
#include "tables/hhea.h"
#include "tables/hmtx.h"
#include "tables/maxp.h"
#include "tables/name.h"
#include "tables/os_2.h"
#include "tables/post.h"

using namespace std;
using namespace babo;

namespace babo {

class TableBuilder {
private:
    TableBuilder() {}
    ~TableBuilder() {}

public:
    static Table *build(const string &tag) {
        if (tag == "head") return new head();
        if (tag == "hhea") return new hhea();
        if (tag == "hmtx") return new hmtx();
        if (tag == "maxp") return new maxp();
        if (tag == "cmap") return new cmap();
        if (tag == "name") return new name();
        if (tag == "OS/2") return new os_2();
        if (tag == "post") return new post();
        return nullptr;
    }
};

} // namespace babo
#endif // _BTABLE_BUILDER_H_
