cmake_minimum_required(VERSION 2.8)
project(OMP_EXERCISE)

set(CMAKE_C_COMPILER "g++-7")
set(CMAKE_CXX_COMPILER "g++-7")

# Use compiler optimization or not
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O")

find_package(OpenMP)
if (OPENMP_FOUND)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
endif()
add_executable(ex_test test.cpp)
add_executable(ex_rowcol_access src/ex_rowcol_access.cpp)
add_executable(ex_loop_unroll src/ex_loop_unroll.cpp)
add_executable(ex_loop_tiling src/ex_loop_tiling.cpp)