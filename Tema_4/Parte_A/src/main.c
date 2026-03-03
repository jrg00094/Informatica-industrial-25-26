#include <stdio.h>
#include "funciones.h"


// Menú

int main(void) {
    int op;
    int continuar = 1;
    while (continuar) {
        printf("\n=== MENU ===\n");
        printf("1) Leer entero\n");
        printf("2) Leer float\n");
        printf("3) Leer cadena\n");
        printf("4) Salir\n");
        if (!leer_entero("Elige una opcion: \n", &op)) return 0;


        switch (op) {
            case 1: {
                int n;    //Variable para guardar el valor leido
                leer_entero("Introduce un numero entero: ", &n);
                printf("Resultado: %d\n", n);
                break;
            }
            case 2: {
                float f;    //Variable para guardar el valor leido
                leer_float("Introduce un numero decimal: ", &f);
                printf("Resultado: %.2f\n", f);
                break;
            }
            case 3: {
                char nombre[64];    //Variable para guardar el valor leido
                leer_cadena("Introduce tu nombre: ", nombre, sizeof(nombre));
                printf("Hola, %s!\n", nombre);
                break;
            }
            case 4:
                printf("Saliendo del programa...\n");
                continuar = 0;
                break;
            default:
                printf("Opcion fuera de rango (1-4).\n");
                break;
        }
    } while (op != 0);
}
