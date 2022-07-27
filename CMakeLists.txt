cmake_minimum_required(VERSION 3.20)
project(lua_t1ha C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -march=native")
include_directories(F:/conda/Library/include ./dep)
link_directories("F:\\conda\\Library\\lib" F:/conda/Library/bin)

file(GLOB SOURCES  ./dep/src/*.c)
message(${SOURCES})

add_library(t1ha SHARED src/lt1ha.c ${SOURCES})
target_link_libraries(t1ha lua)

set_target_properties(t1ha PROPERTIES OUTPUT_NAME t1ha)

