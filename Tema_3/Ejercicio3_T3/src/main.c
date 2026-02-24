#include <stdio.h>
#include "stats.h"

int main(void) {
    int a[] = {3, -1, 8, 8, 2};                         //Array de valores para el max, min y media
    size_t n = sizeof(a)/sizeof(a[0]);                  //Cáclculo del tamaño (cantidad de bytes/tamaño de un elemento)
    printf("max=%d\n", max_int(a, n));            //Muestra el máximo
    printf("min=%d\n", min_int(a, n));            //Muestra el mínimo
    printf("media=%.2f\n", media_int(a, n));      //Muestra ña media con 2 decimales (%.2f)

    double b[] = {1.0, 2.0, 3.0, 6.0};                              //Array de valores para el normalizado
    size_t m = sizeof(b)/sizeof(b[0]);                              //Cáclculo del tamaño
    normaliza(b, m);
    printf("normalizado: ");                                  //Muestra el normalizado
    for (size_t i = 0; i < m; ++i) printf("%.3f ", b[i]);     //para cada valor del array b
    printf("\n");
    return 0;
}