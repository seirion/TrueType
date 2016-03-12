
BUILD_DIR=build
GTEST_DIR=.


rm -rf ${BUILD_DIR}
mkdir -p ${BUILD_DIR}
g++ -isystem ${GTEST_DIR}/include -I${GTEST_DIR}  -pthread -c ${GTEST_DIR}/src/gtest-all.cc -o ${BUILD_DIR}/gtest-all.o
g++ -std=gnu++0x src/gtest_main.cc -I./include -c -o ${BUILD_DIR}/gtest_main.o
g++ -std=gnu++0x ${BUILD_DIR}/gtest_main.o ${BUILD_DIR}/gtest-all.o

