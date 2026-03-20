#include <stdio.h>
#include "productos.h"
#include "funciones.h" // Funciones de la parte A
#include "string.h"

/**
 * Función para mostrar en una lista todos los prductos guardados:
 * Comprueba si el array inventario está vacío, y si no lo está, devuelve ID, Nombre, Preico y Stock.
 */
void listar_productos(const Producto *inventario, size_t n) {
    if (n == 0) {
        printf("\nInventario vacio.\n");
        return;
    }
    printf("\n--- LISTADO DE PRODUCTOS ---\n");
    printf("ID\tNOMBRE\t\tPRECIO\tSTOCK\n");
    for (size_t i = 0; i < n; i++) {
        printf("%d\t%-15s\t%.2f\t%d\n", inventario[i].id, inventario[i].nombre, inventario[i].precio,inventario[i].stock);
    }
}

/**
 * Función para Buscar Producto por ID:
 * Busca el valor de ID indicado en el array inventario.
 */
int buscar_indice_por_id(const Producto *inventario, size_t n, int id_buscar) {
    for (size_t i = 0; i < n; i++) {
        if (inventario[i].id == id_buscar) return (int)i;
    }
    return -1; // No encontrado
}

/**
 * Función para declarar productos nuevos:
 * Comprueba que el inventario no está lleno y entonces:
 *      lee un entero como ID y comprueba que no esté ya declarado.
 *      lee una cadena de caracteres como Nombre.
 *      lee un decimal (flot) como Precio.
 *      lee un entero como Stock.
 */
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
    leer_entero("Definir stock: ", &p.stock);

    inventario[*n] = p; // Guardamos en el array
    (*n)++;             // Aumentamos el contador de productos
    return 1;
}

/**
 * Función para modificar los datos de un ID:
 * Comprueba que hay prodructos en el array inventario y entonces:
*       lee un entero como ID.
 *      lee una cadena de caracteres como Nombre.
 *      lee un decimal (flot) como Precio.
 *      lee un entero como Stock
 */
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
        leer_entero("Nuevo stock: ", &inventario[idx].stock);

        printf("Producto actualizado.\n");
    } else {
        printf("Error: No existe ningun producto con el ID %d.\n", id_a_editar);
    }
}


/**
 * Función para guardar los datos en un .csv.
 */
int guardar_texto(const char *ruta, const Producto *arr, size_t n) {
    FILE *f = fopen(ruta, "w"); // "w" para sobrescribir el archivo
    if (!f) return 0;

    for (int i = 0; i < n; i++) {
        // Formato: id;nombre;precio;stock
        fprintf(f, "%d;%s;%.2f;%d\n",
                arr[i].id, arr[i].nombre, arr[i].precio, arr[i].stock);
    }

    fclose(f); // Siempre cerrar el flujo
    return 1;
}

/**
 * Función para cargar los datos de un .csv.
 */
int cargar_texto(const char *ruta, Producto *arr, int cap, size_t *out_n) {
    FILE *f = fopen(ruta, "r"); // "r" para lectura
    if (!f) return 0;

    char linea[256];
    int n = 0;

    // Leemos línea por línea hasta el final o alcanzar capacidad
    while (n < cap && fgets(linea, sizeof(linea), f)) {
        // Limpiar el salto de línea \n [cite: 46]
        linea[strcspn(linea, "\n")] = '\0';

        Producto p;
        // Parsing con sscanf: %49[^;] lee hasta 49 caracteres o hasta encontrar ';'
        if (sscanf(linea, "%d;%49[^;];%f;%d", &p.id, p.nombre, &p.precio, &p.stock) == 4) {
            arr[n++] = p;
        }
    }
    *out_n = n; // Devolvemos la cantidad cargada
    fclose(f);
    return 1;
}
