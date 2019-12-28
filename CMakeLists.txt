project(replace)
cmake_minimum_required(VERSION 3.13)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
include_directories(inc)
include_directories(src)
set(CMAKE_BUILD_TYPE Debug)

add_executable(replace
        inc/lruList.h
        inc/optArray.h
        inc/replace.h
        src/lruList.c
        src/optArray.c
        src/replace.c
        CMakeLists.txt)
