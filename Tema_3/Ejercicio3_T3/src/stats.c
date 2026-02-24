#include "stats.h"
#include <math.h>

int max_int(const int *v, size_t n) {
    if (n == 0) return 0;               //Si el tamaño del array es 0, no hacer nada
    int max = v[0];                     //Asumir el primer elemento como máximo
    for (size_t i = 1; i < n; i++) {    //Barrer el array
        if (v[i] > max) max = v[i];     //Si hay un número mayor al guardado, cambiarlo
    }
    return max;
}

int min_int(const int *v, size_t n) {
    if (n == 0) return 0;               //Si el tamaño del array es 0, no hacer nada
    int min = v[0];                     //Asumir el primer elemento como mínimo
    for (size_t i = 1; i < n; i++) {    //Barrer el array
        if (v[i] < min) min = v[i];     //Si hay un número menor al guardado, cambiarlo
    }
    return min;
}

double media_int(const int *v, size_t n) {
    if (n == 0) return 0.0;                         //Si el tamaño del array es 0, no hacer nada
    double suma = 0;                                //double da precisión en decimales
    for (size_t i = 0; i < n; i++) suma += v[i];    //Barrer el array sumando los valores del mismo
    return suma / (double)n;                        //Calcula la media
}

void normaliza(double *v, size_t n) {
    if (n == 0) return;                                                     //Si el tamaño del array es 0, no hacer nada
    double m = 0;                                                           //m es la suma de los valores del array
    for (size_t i = 0; i < n; i++) m += v[i];                               //Barrer el array sumando los valores en m
    m /= n;                                                                 //Hace la media

    double suma_sq = 0;                                                     //Variable suma de cuadrados
    for (size_t i = 0; i < n; i++) suma_sq += pow(v[i] - m, 2);       //Suma((v[i]-media)^2)
    double desviacion = sqrt(suma_sq / n);                               //Suma/n: varianza; sqrt(varianza): desviación típica

    if (desviacion > 0) {                                                   //Evita dividir por 0 si todos los valores son iguales
        for (size_t i = 0; i < n; i++) v[i] = (v[i] - m) / desviacion;      //Indica cuánto es la desviación respecto del centro
    }
}