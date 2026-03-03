#include <stdio.h>
#include "productos.h"
#include "funciones.h" // Funciones de la parte A

void listar_productos(const Producto *inventario, size_t n) {
    if (n == 0) {
        printf("\nInventario vacio.\n");
        return;
    }
    printf("\n--- LISTADO DE PRODUCTOS ---\n");
    printf("ID\tNOMBRE\t\tPRECIO\n");
    for (size_t i = 0; i < n; i++) {
        printf("%d\t%-15s\t%.2f\n", inventario[i].id, inventario[i].nombre, inventario[i].precio);
    }
}

int buscar_indice_por_id(const Producto *inventario, size_t n, int id_buscar) {
    for (size_t i = 0; i < n; i++) {
        if (inventario[i].id == id_buscar) return (int)i;
    }
    return -1; // No encontrado
}

int alta_producto(Producto *inventario, size_t *n, size_t capacidad_max) {
    if (*n >= capacidad_max) {
        printf("Error: Inventario lleno.\n");
        return 0;
    }

    Producto p;
    leer_entero("Introduce ID del producto: ", &p.id);
    
    // Validar que el ID no exista ya
    if (buscar_indice_por_id(inventario, *n, p.id) != -1) {
        printf("Error: Ese ID ya existe.\n");
        return 0;
    }

    leer_cadena("Nombre del producto: ", p.nombre, 50);
    leer_float("Precio: ", &p.precio);

    inventario[*n] = p; // Guardamos en el array
    (*n)++;             // Aumentamos el contador de productos
    return 1;
}

void modificar_producto(Producto *inventario, size_t n) {
    if (n == 0) {
        printf("No hay productos para modificar.\n");
        return;
    }

    int id_a_editar;
    leer_entero("Introduce el ID del producto a modificar: ", &id_a_editar);

    int idx = buscar_indice_por_id(inventario, n, id_a_editar);

    if (idx != -1) {
        printf("\nModificando: %s (Precio actual: %.2f)\n", inventario[idx].nombre, inventario[idx].precio);

        // Sobreescribimos los datos en la posición idx
        leer_cadena("Nuevo nombre: ", inventario[idx].nombre, 50);
        leer_float("Nuevo precio: ", &inventario[idx].precio);

        printf("Producto actualizado.\n");
    } else {
        printf("Error: No existe ningun producto con el ID %d.\n", id_a_editar);
    }
}