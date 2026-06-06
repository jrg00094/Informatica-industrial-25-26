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

typedef struct {
    int max_productos;
    char ruta_inventario[100];
    char puerto_serie[50];
    int baudrate;
} ConfigApp;

// Funciones de gestión
void listar_productos(const Producto *inventario, int n);
int buscar_indice_por_id(const Producto *inventario, int n, int id_buscar);
int alta_producto(Producto *inventario, int *n, int capacidad_max);
void modificar_producto(Producto *inventario, int n);

// Funciones de configuración y comunicación
int guardar_texto(const char *ruta, const Producto *arr, int n);
int cargar_texto(const char *ruta, Producto *arr, int cap, int *out_n);
int cargar_configuracion(const char *ruta_config, ConfigApp *config);
int guardar_configuracion(const char *ruta_config, const ConfigApp *config);

// Enlace UART
void comunicarse_stm32(const ConfigApp *config, const Producto *inventario, int n);
#endif