#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "funciones.h"
#include "productos.h"

#define ARCHIVO_CONFIG "config.txt"

int main() {
    ConfigApp config;
    memset(&config, 0, sizeof(ConfigApp));

    char stm32_config[32];
    sprintf(stm32_config, "#%d\n", config.frecuencia_led);


    // Si no existe la configuración, inicializar valores por defecto
    if (!cargar_configuracion(ARCHIVO_CONFIG, &config)) {
        config.max_productos = 50;
        strcpy(config.ruta_inventario, "inventario.csv");
        strcpy(config.puerto_serie, "COM7");
        config.baudrate = 9600;
        config.frecuencia_led = 60000;
        guardar_configuracion(ARCHIVO_CONFIG, &config);
    }

    // Memoria Dinamica: Alocación dinámica basada en fichero
    Producto *inventario = (Producto *)malloc(config.max_productos * sizeof(Producto));
    if (inventario == NULL) {
        printf("Error de memoria\n");
        return 1;
    }

    int num_productos = 0;
    int opcion;
    bool salir = false;

    do {
        printf("+-----------------------------------------+\n");
        printf("|      GoVending (Gestion de Maquina)     |\n");
        printf("+-----------------------------------------+\n");
        printf("  1. Cargar productos desde fichero\n");
        printf("  2. Listar productos\n");
        printf("  3. Agregar producto\n");
        printf("  4. Modificar campos de un producto\n");
        printf("  5. Guardar productos\n");
        printf("  6. Modificar parametros del Puerto Serie\n");
        printf("  7. Realizar compra (Conectar con STM32)\n");
        printf("  8. Salir\n");
        printf("-------------------------------------------\n");

        if (!leer_entero("Seleccione opcion:   ", &opcion)) {
            // Si falla la lectura, hacemos una pequeña pausa para que el usuario lo vea
            printf("\nPresione ENTER para continuar...");
            while (getchar() != '\n'); getchar();
            continue;
        }

        switch (opcion) {
            case 1: // Cargar productos desde fichero en cmake-build-debug
                if (cargar_texto(config.ruta_inventario, inventario, config.max_productos, &num_productos)) {
                    printf("[OK] Productos cargados. Total: %d\n", num_productos);
                } else {
                    printf("[Error] No se pudo abrir el archivo.\n");
                }
                break;

            case 2: // Listar productos
                listar_productos(inventario, num_productos);
                break;

            case 3: // Añadir producto
                // Pasamos la dirección de num_productos para que alta_producto lo incremente
                if (alta_producto(inventario, &num_productos, config.max_productos)) {
                    printf("[OK] Producto agregado con exito.\n");
                }
                break;

            case 4: // Modificar producto
                modificar_producto(inventario, num_productos);
                break;

            case 5: // Guardar productos
                if (guardar_texto(config.ruta_inventario, inventario, num_productos)) {
                    printf("[OK] Inventario guardado exitosamente.\n");
                } else {
                    printf("[Error] No se pudo guardar el archivo.\n");
                }
                break;

            case 6: // Modificar puerto serie
                printf("\n--- MODIFICAR PUERTO SERIE ---\n");
                printf("Puerto actual: %s | Baudrate actual: %d\n | Frecuencia del LED actual: %d\n", config.puerto_serie, config.baudrate,config.frecuencia_led);
                leer_cadena("Introduce el nuevo puerto (Ej: COM3, COM7): ", config.puerto_serie, 50);
                leer_entero("Introduce la velocidad de transmision de datos (Ej: 9600, 115200): ", &config.baudrate);
                leer_entero("Introduce la frecuencia de parapdeo del LED (Ej: 40000, 100000): ", &config.frecuencia_led);
                guardar_configuracion(ARCHIVO_CONFIG, &config);
                printf("Parametros actualizados correctamente.\n");

                break;

            case 7:
                if (num_productos == 0) {
                    printf("[Error] Estructura vacia. Cargue productos primero.\n");
                } else {
                    comunicarse_stm32(&config, inventario, num_productos);
                }
                break;

            case 8:
                printf("Cerrando GoVending...\n");
                salir = true;
                break;

            default:
                printf("Opcion no valida (1-8).\n");
                break;
        }

        if (!salir) {
            // 1. Primero hacemos la pausa. La respuesta de la STM32 se queda fija y visible.
            printf("\nPresione ENTER para volver al menu...");
            getchar();

            // 2. Al pulsar ENTER, imprimimos 40 saltos de línea
            printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
        }

    } while (!salir);
    free(inventario); // Liberar memoria al cerrar
    return 0;
}