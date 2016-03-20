# Copyright 2016 seirion
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#

# Setup testing
enable_testing()

set(CMAKE_CXX_FLAGS "-Wall -std=gnu++0x")

include_directories(".")
include_directories("./include")
include_directories("../src")

# unit tests
add_executable(unit_test
   	src/gtest_main.cc
   	src/gtest-all.cc
	test_cases/test_fixed.cpp
	test_cases/test_reader.cpp
	../src/doc/Font.cpp
	../src/tables/cmap_mapping.cpp
)

target_link_libraries(unit_test pthread)
