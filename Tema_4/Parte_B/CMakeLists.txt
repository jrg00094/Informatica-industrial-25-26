cmake_minimum_required(VERSION 4.1)
project(Parte_B C)

set(CMAKE_C_STANDARD 11)

add_executable(Parte_B
        src/main.c
        src/productos.c
        ../Parte_A/src/funciones.c   # Referencia al archivo de funciones de la otra carpeta
)

target_include_directories(Parte_B PUBLIC
        include                      # Los .h de productos
        ../Parte_A/include           # Los .h de funciones.h
)
