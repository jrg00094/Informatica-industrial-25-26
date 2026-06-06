cmake_minimum_required(VERSION 3.28)
project(untitled C)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)


add_executable(Maquina_Expendedora
        src/main.c
        src/funciones.c
        src/productos.c
)

target_include_directories(Maquina_Expendedora PUBLIC include)

configure_file(
        "${CMAKE_CURRENT_SOURCE_DIR}/inventario.csv"
        "${CMAKE_CURRENT_BINARY_DIR}/inventario.csv"
        COPYONLY
)
configure_file(
        "${CMAKE_CURRENT_SOURCE_DIR}/config.txt"
        "${CMAKE_CURRENT_BINARY_DIR}/config.txt"
        COPYONLY
)