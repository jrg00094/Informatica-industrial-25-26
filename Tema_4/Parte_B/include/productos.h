#ifndef PRODUCTOS_H
#define PRODUCTOS_H

#include <stddef.h>

/**
 * Programa de una maquina expendedora que guarda el ID, Nombre y Precio de los productos leidos del teclado:
 * id: ID del producto leido desde el teclado.
 * nombre: Nombre del producto leido desde el teclado.
 * precio: Precio del producto leido desde el teclado.
 * stock: Cantidad del producto seleccionado disponible.
 * inventario: Array que guarda los productos.
 * capacidad_max: Máxima cantidad de productos que caben dentro de "inventario".
 * n: Tamaño del array "inventario".
 */
typedef struct {
    int id;
    char nombre[50];
    float precio;
    int stock;
} Producto;

// Funciones de gestión
void listar_productos(const Producto *inventario, size_t n);
int buscar_indice_por_id(const Producto *inventario, size_t n, int id_buscar);
int alta_producto(Producto *inventario, size_t *n, size_t capacidad_max);
void modificar_producto(Producto *inventario, size_t n);
int guardar_texto(const char *ruta, const Producto *arr, size_t n);
int cargar_texto(const char *ruta, Producto *arr, int cap, size_t *out_n);

#endif