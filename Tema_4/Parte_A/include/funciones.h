#include <stdlib.h>
#ifndef FUNCIONES_H
/**
 * Leemos un entero de entrada por teclado
 *      pront: cadena de texto a mostrar.
 *      out: entero introducido por teclado.
 *      return: 1 lectura correcta, 0 error de lectura.
 */
int leer_entero(const char *prompt, int *out);
int leer_float(const char *prompt, float *out);
int leer_cadena(const char *prompt, char *dst, size_t cap);

#endif
