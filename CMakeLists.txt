cmake_minimum_required(VERSION 3.16)
project(SerializeAndDiff)

set(CMAKE_CXX_COMPILER hipcc)
set(CMAKE_CXX_STANDARD 17)

include_directories(${PROJECT_SOURCE_DIR}/include)
add_subdirectory(tests)