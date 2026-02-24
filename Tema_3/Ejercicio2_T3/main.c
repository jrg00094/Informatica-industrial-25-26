#include <stdio.h>

//Hay que mover A a una variable temporal, B a A y luego el valor copiado de A a B
void swap(int *a, int *b) {
    int temp;    // Creo variable temporal

    temp = *a;   // Guardar el valor de x en temp
    *a = *b;     // Copiar el valor de y donde estaba x
    *b = temp;   // Copiar el valor de temp (el viejo x) donde estaba y
}

int main(void) {
    // Caso 1: Positivos
    int x = 1, y = 2;
    swap(&x, &y); // Enviamos las DIRECCIONES con &
    printf("Caso 1 (positivos) -> x=%d y=%d\n", x, y);

    // Caso 2: Negativos
    int n1 = -10, n2 = 50;
    swap(&n1, &n2);
    printf("Caso 2 (negativos) -> n1=%d n2=%d\n", n1, n2);

    return 0;
}