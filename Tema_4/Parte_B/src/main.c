#include <stdio.h>
#include "funciones.h"
#include "productos.h"

#define MAX_PRODUCTOS 10

int main() {
    Producto inventario[MAX_PRODUCTOS];
    size_t num_productos = 0;
    int opcion;

    do {
        printf("\n-------------------------------------------\n\n");
        printf("\n--- GoVending ---\n");
        printf("1. Alta de producto\n");
        printf("2. Listar productos\n");
        printf("3. Buscar producto por ID\n");
        printf("4. Modificar producto\n");
        printf("5. Salir\n");

        if (!leer_entero("Seleccione opcion: ", &opcion)) continue;

        switch (opcion) {
            case 1:
                if (alta_producto(inventario, &num_productos, MAX_PRODUCTOS)) {
                    printf("Producto agregado con exito.\n");
                }
                break;
            case 2:
                listar_productos(inventario, num_productos);
                break;
            case 3: {
                int id, idx;
                leer_entero("ID a buscar: ", &id);
                idx = buscar_indice_por_id(inventario, num_productos, id);
                if (idx != -1) {
                    printf("Seleccion: %s cuesta %.2f\n", inventario[idx].nombre, inventario[idx].precio);
                } else {
                    printf("Producto no encontrado.\n");
                }
                break;
            }
            case 4:
                modificar_producto(inventario, num_productos);
                break;
            case 5:
                printf("Saliendo...\n");
                opcion = 5; // O la lógica que uses para salir
                break;
        }
    } while (opcion != 5);

    return 0;
}