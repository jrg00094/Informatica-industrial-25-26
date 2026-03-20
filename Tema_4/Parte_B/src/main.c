#include <stdio.h>
#include <stdbool.h>
#include "funciones.h"
#include "productos.h"

#define MAX_PRODUCTOS 100
#define RUTA_POR_DEFECTO "inventario.csv"

int main() {
    Producto inventario[MAX_PRODUCTOS];
    size_t num_productos = 0;
    int opcion;
    bool salir = false;

    do {
        printf("\n-------------------------------------------\n");
        printf("--- GoVending (Gestion de Maquina) ---\n");
        printf("1. Cargar productos (ruta por defecto)\n");
        printf("2. Listar productos\n");
        printf("3. Añadir producto\n");
        printf("4. Modificar producto (nombre/precio/stock)\n");
        printf("5. Guardar productos\n");
        printf("6. Salir\n");
        printf("-------------------------------------------\n");

        if (!leer_entero("Seleccione opcion: ", &opcion)) continue;

        switch (opcion) {
            case 1: // Cargar productos
                if (cargar_texto(RUTA_POR_DEFECTO, inventario, MAX_PRODUCTOS, &num_productos)) {
                    printf("[OK] Productos cargados desde %s. Total: %zu\n", RUTA_POR_DEFECTO, num_productos);
                } else {
                    printf("[ERROR] No se pudo abrir el archivo o no existe.\n");
                }
                break;

            case 2: // Listar productos
                // Convertimos num_productos a size_t para la función de listado si es necesario
                listar_productos(inventario, (size_t)num_productos);
                break;

            case 3: // Añadir producto
                // Pasamos la dirección de num_productos para que alta_producto lo incremente
                if (alta_producto(inventario, (size_t *)&num_productos, MAX_PRODUCTOS)) {
                    printf("[OK] Producto agregado con exito.\n");
                }
                break;

            case 4: // Modificar producto
                modificar_producto(inventario, (size_t)num_productos);
                break;

            case 5: // Guardar productos
                if (guardar_texto(RUTA_POR_DEFECTO, inventario, num_productos)) {
                    printf("[OK] Inventario guardado exitosamente en %s.\n", RUTA_POR_DEFECTO);
                } else {
                    printf("[ERROR] No se pudo guardar el archivo.\n");
                }
                break;

            case 6: // Salir [cite: 95]
                printf("Cerrando sistema GoVending...\n");
                salir = true;
                break;

            default:
                printf("Opcion no valida (1-6).\n");
                break;
        }
    } while (!salir);

    return 0;
}