#include <stdio.h>

int main(void) {
    int x = 5;
    int *p = &x;

    // 1. Imprimir x, &x, p, *p
    printf("Valor de x: %d\n", x);          // El valor actual de x
    printf("Direccion de x (&x): %p\n", (void*)&x); // Dónde está x en la memoria
    printf("Valor de p: %p\n", (void*)p);   // La dirección de p en la memoria (que es &x)
    printf("Valor de *p: %d\n", *p);        // Qué hay en la dirección p

    // 2. Modificar x a 99 usando p
    *p = 99; // Cambiar *p, cambia x

    // 3. Imprimir x
    printf("Nuevo valor de x: %d\n", x);

    return 0;
}