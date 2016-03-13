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
#include <iostream>
#include "base/types.h"
#include "base/Reader.h"

using namespace std;
using namespace babo;

void printUsage(const char *exe) {
    cout << "-- usgage :\n";
    cout << "  " << exe << " FILE_NAME\n";
}

int32 main(int argc, char* argv[]) {
    if (argc < 2) {
        printUsage(argv[0]);
        return -1;
    }

    Reader reader(argv[1]);

    if (!reader.is_open()) {
        cout << "cannot open file : " << argv[1] << endl;
        return -1;
    }

    return 0;
}
