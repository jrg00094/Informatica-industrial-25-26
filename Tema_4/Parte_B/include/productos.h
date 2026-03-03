#ifndef PRODUCTOS_H
#define PRODUCTOS_H

#include <stddef.h>

typedef struct {
    int id;
    char nombre[50];
    float precio;
} Producto;

// Funciones de gestión
void listar_productos(const Producto *inventario, size_t n);
int buscar_indice_por_id(const Producto *inventario, size_t n, int id_buscar);
int alta_producto(Producto *inventario, size_t *n, size_t capacidad_max);
void modificar_producto(Producto *inventario, size_t n);

#endif