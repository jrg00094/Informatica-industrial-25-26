cmake_minimum_required(VERSION 4.1)
project(Parte_A C)

set(CMAKE_C_STANDARD 11)

add_executable(Parte_A src/main.c
        src/funciones.c)
target_include_directories(Parte_A PUBLIC include)
