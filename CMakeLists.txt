cmake_minimum_required(VERSION 3.20)
project(lua_t1ha C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -march=native")
include_directories(E:/pyproject/Lua_5.4_WinBuild/lua-5.4.7/src ./dep)
link_directories(E:/pyproject/Lua_5.4_WinBuild/cmake-build-release)

file(GLOB SOURCES ./dep/src/*.c)
foreach(FILE ${SOURCES})
    message(STATUS "Processing file: ${FILE}")
endforeach()
add_library(t1ha SHARED src/lt1ha.c ${SOURCES})
target_link_libraries(t1ha lua)

set_target_properties(t1ha PROPERTIES OUTPUT_NAME t1ha)

