GTEST_DIR=.
g++ -isystem ${GTEST_DIR}/include -I${GTEST_DIR}  -pthread -c ${GTEST_DIR}/src/gtest-all.cc
ar -rv libgtest.a gtest-all.o
