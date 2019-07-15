cmake_minimum_required(VERSION 2.8)
project(lock_benchmark)

set(CMAKE_CXX_STANDARD 14)
add_custom_target(make_test COMMAND make -C ${make_test_SOURCE_DIR}
        CLION_EXE_DIR=${PROJECT_BINARY_DIR} && cp ${make_test_SOURCE_DIR}/make_test ./
        )
LINK_LIBRARIES(pthread)
add_executable(lock_benchmark main.cpp)
