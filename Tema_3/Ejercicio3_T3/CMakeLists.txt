cmake_minimum_required(VERSION 3.20)
project(Ejercicio3_T3 C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

add_library(stats src/stats.c)
target_include_directories(stats PUBLIC include)

add_executable(Ejercicio3_T3 src/main.c)
target_link_libraries(Ejercicio3_T3 PRIVATE stats m)