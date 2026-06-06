#include <stdio.h>
#include "productos.h"
#include "funciones.h"
#include "string.h"

#if defined(_WIN32) || defined(_WIN64) // Necesarior para conexión PC-STM32
#include <windows.h>
#else
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>
#endif
/**
 * Función para mostrar en una lista todos los prductos guardados:
 * Comprueba si el array inventario está vacío, y si no lo está, devuelve ID, Nombre, Preico y Stock.
 */
void listar_productos(const Producto *inventario, int n) {
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
int buscar_indice_por_id(const Producto *inventario, int n, int id_buscar) {
    for (int i = 0; i < n; i++) {
        if (inventario[i].id == id_buscar) return i;
    }
    return -1;
}

/**
 * Función para declarar productos nuevos:
 * Comprueba que el inventario no está lleno y entonces:
 *      lee un entero como ID y comprueba que no esté ya declarado.
 *      lee una cadena de caracteres como Nombre.
 *      lee un decimal (flot) como Precio.
 *      lee un entero como Stock.
 */
int alta_producto(Producto *inventario, int *n, int capacidad_max) {
    // --- CANDADO DE SEGURIDAD CONTRA DESBORDAMIENTO ---
    if (*n >= capacidad_max) {
        printf("[Error]: El inventario esta lleno (Maximo %d productos). No puedes agregar mas.\n", capacidad_max);
        return 0;
    }

    Producto p;
    leer_entero("Introduce ID del producto: ", &p.id);

    if (buscar_indice_por_id(inventario, *n, p.id) != -1) {
        printf("[Error]: Ese ID ya existe.\n");
        return 0;
    }

    leer_cadena("Nombre del producto: ", p.nombre, 50);
    leer_float("Precio: ", &p.precio);
    leer_entero("Definir stock: ", &p.stock);

    inventario[*n] = p;
    (*n)++;
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
void modificar_producto(Producto *inventario, int n) {
    if (n == 0) {
        printf("No hay productos para modificar.\n");
        return;
    }

    int id_a_editar;
    leer_entero("Introduce el ID del producto a modificar: ", &id_a_editar);
    int idx = buscar_indice_por_id(inventario, n, id_a_editar);

    if (idx != -1) {
        printf("\nModificando: %s (Precio actual: %.2f)\n", inventario[idx].nombre, inventario[idx].precio);

        leer_cadena("Nuevo nombre: ", inventario[idx].nombre, 50);
        leer_float("Nuevo precio: ", &inventario[idx].precio);
        leer_entero("Nuevo stock: ", &inventario[idx].stock);

        printf("Producto actualizado.\n");
    } else {
        printf("[Error]: No existe ningun producto con el ID %d.\n", id_a_editar);
    }
}


/**
 * Función para guardar los datos en un .csv.
 */
int guardar_texto(const char *ruta, const Producto *arr, int n) {
    FILE *f = fopen(ruta, "w");
    if (!f) return 0;

    for (int i = 0; i < n; i++) {
        fprintf(f, "%d;%s;%.2f;%d\n", arr[i].id, arr[i].nombre, arr[i].precio, arr[i].stock);
    }

    fclose(f);
    return 1;
}

/**
 * Función para cargar los datos de un .csv.
 */
int cargar_texto(const char *ruta, Producto *arr, int cap, int *out_n) {
    FILE *f = fopen(ruta, "r");
    if (!f) return 0;

    char linea[256];
    int n = 0;

    // Leemos línea por línea cuidando de no superar bajo ningún concepto la capacidad asignada
    while (fgets(linea, sizeof(linea), f)) {
        if (n >= cap) {
            printf("[AVISO]: El archivo .csv contiene mas productos de la capacidad maxima (%d).\n", cap);
            break;
        }

        linea[strcspn(linea, "\n")] = '\0';

        Producto p;
        if (sscanf(linea, "%d;%49[^;];%f;%d", &p.id, p.nombre, &p.precio, &p.stock) == 4) {
            arr[n++] = p;
        }
    }
    *out_n = n;
    fclose(f);
    return 1;
}

/**
 * Función para cargar la configuración de la máquina:
 * Comprueba si el array está vacío, y si no lo está, devuelve MAX_PRODUCTOS, RUTA_INVENTARIO, PUERTO, BAUDRATE y FRECUENCIA_LED.
 */
int cargar_configuracion(const char *ruta_config, ConfigApp *config) {
    FILE *f = fopen(ruta_config, "r");
    if (!f) return 0;

    char linea[256];
    while (fgets(linea, sizeof(linea), f)) {
        sscanf(linea, "MAX_PRODUCTOS=%d", &config->max_productos);
        sscanf(linea, "RUTA_INVENTARIO=%99s", config->ruta_inventario);
        sscanf(linea, "PUERTO=%49s", config->puerto_serie);
        sscanf(linea, "BAUDRATE=%d", &config->baudrate);
        sscanf(linea, "FRECUENCIA_LED=%d", &config->frecuencia_led);
    }
    fclose(f);
    return 1;
}

/**
 * Función para guardar la configuración de la máquina:
 * Guarda MAX_PRODUCTOS, RUTA_INVENTARIO, PUERTO y BAUDRATE.
 */
int guardar_configuracion(const char *ruta_config, const ConfigApp *config) {
    FILE *f = fopen(ruta_config, "w");
    if (!f) return 0;

    fprintf(f, "MAX_PRODUCTOS=%d\n", config->max_productos);
    fprintf(f, "RUTA_INVENTARIO=%s\n", config->ruta_inventario);
    fprintf(f, "PUERTO=%s\n", config->puerto_serie);
    fprintf(f, "BAUDRATE=%d\n", config->baudrate);
    fprintf(f, "FRECUENCIA_LED=%d\n", config->frecuencia_led);

    fclose(f);
    return 1;
}

void comunicarse_stm32(const ConfigApp *config, Producto *inventario, int n) {
    int id_prod;
    float importe_int;

    leer_entero("Introduce el ID del producto que deseas comprar: ", &id_prod);
    int idx = buscar_indice_por_id(inventario, n, id_prod);

    if (idx == -1) {
        printf("[Error]: Producto no encontrado.\n");
        return;
    }

    if (inventario[idx].stock <= 0) {
        printf("[Error]: No queda stock de este producto.\n");
        return;
    }

    printf("Producto seleccionado: %s - Precio: %.2f\n", inventario[idx].nombre, inventario[idx].precio);
    leer_float("Introduce el importe introducido: ", &importe_int);

    // Trabajamos en céntimos enteros para simplificar la transmisión
    int precio_centimos = (int)(inventario[idx].precio * 100);
    int importe_centimos = (int)(importe_int * 100);

    char cadena_enviar[64];
    sprintf(cadena_enviar, "%d,%d\n", precio_centimos, importe_centimos);

    printf("[Conectando a %s a %d baudios...]\n", config->puerto_serie, config->baudrate);

#if defined(_WIN32) || defined(_WIN64) // CONFIGURACIÓN PARA WINDOWS
    HANDLE hSerial = CreateFile(config->puerto_serie, GENERIC_READ | GENERIC_WRITE, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
    if (hSerial == INVALID_HANDLE_VALUE) {
        printf("[Error]: No se pudo abrir el puerto serie.\n");
        return;
    }

    // FIJAR TIMEOUTS PARA EVITAR CONGELAMIENTOS
    COMMTIMEOUTS timeouts = { 0 };
    timeouts.ReadIntervalTimeout = 50;          // Máximo tiempo entre caracteres (ms)
    timeouts.ReadTotalTimeoutConstant = 1000;    // Espera máxima total para la lectura (1 segundo)
    timeouts.ReadTotalTimeoutMultiplier = 10;
    timeouts.WriteTotalTimeoutConstant = 50;
    timeouts.WriteTotalTimeoutMultiplier = 10;
    SetCommTimeouts(hSerial, &timeouts);
    // ---------------------------------------------------------

    DCB dcbSerialParams = {0};
    dcbSerialParams.DCBlength = sizeof(dcbSerialParams);
    GetCommState(hSerial, &dcbSerialParams);
    dcbSerialParams.BaudRate = config->baudrate;
    dcbSerialParams.ByteSize = 8;
    dcbSerialParams.StopBits = ONESTOPBIT;
    dcbSerialParams.Parity = NOPARITY;
    SetCommState(hSerial, &dcbSerialParams);

    // Preparar la cadena con el formato '#frecuencia\n'
    char msg_led[32];
    sprintf(msg_led, "#%d\n", config->frecuencia_led);

    // Limpiar los buffers del puerto antes de enviar/recibir
    PurgeComm(hSerial, PURGE_RXCLEAR | PURGE_TXCLEAR);

    // Enviar los datos por el cable
    DWORD bytesWrittenLed;
    WriteFile(hSerial, msg_led, strlen(msg_led), &bytesWrittenLed, NULL);
    Sleep(100);

    DWORD bytesWritten;
    WriteFile(hSerial, cadena_enviar, strlen(cadena_enviar), &bytesWritten, NULL);

    char rx_buf[128] = {0};
    DWORD bytesRead = 0;

    // Esperamos un instante a que el micro termine de computar e iterar por interrupciones
    Sleep(200);

    // Con los timeouts configurados, ReadFile ya no se congelará si recibe menos bytes de los pedidos
    ReadFile(hSerial, rx_buf, sizeof(rx_buf) - 1, &bytesRead, NULL);

    if (bytesRead > 0) {
        printf("\n--- RESPUESTA DE STM32 ---\n%s\n", rx_buf);

        // Comprobamos si la respuesta de la placa contiene la palabra "OK"
        if (strstr(rx_buf, "OK") != NULL) {

            inventario[idx].stock--; // Restamos una unidad en la memoria

            printf("[Sistema]: Compra validada. Se ha descontado 1 unidad de %s.\n", inventario[idx].nombre);
            printf("[Sistema]: Stock restante: %d\n", inventario[idx].stock);

            // ALGORITMO DE DESGLOSE DE MONEDAS
            int cambio_total = importe_centimos - precio_centimos;

            if (cambio_total < 0) {
                printf("[Sistema]: Error inesperado, el saldo es insuficiente.\n");
            } else if (cambio_total == 0) {
                printf("[Sistema]: Importe exacto introducido. No hay cambio que devolver.\n");
            } else {
                printf("[Sistema]: Cambio total a devolver: %.2f eur (%d centimos)\n", (float)cambio_total / 100.0, cambio_total);
                printf("          Desglose de monedas:\n");

                // Valores de las monedas que maneja la máquina (en céntimos)
                // 200 = 2€, 100 = 1€, 50 = 50c, 20 = 20c, 10 = 10c, 5 = 5c
                int valores_monedas[] = {200, 100, 50, 20, 10, 5};
                const char* nombres_monedas[] = {"2 euros", "1 euro", "50 centimos", "20 centimos", "10 centimos", "5 centimos"};
                int total_monedas = sizeof(valores_monedas) / sizeof(valores_monedas[0]);

                for (int i = 0; i < total_monedas; i++) {
                    if (cambio_total >= valores_monedas[i]) {
                        int cantidad_monedas = cambio_total / valores_monedas[i]; // Cuántas de este tipo caben
                        cambio_total = cambio_total % valores_monedas[i];        // El residuo que queda por desglosar

                        printf("          - %d moneda(s) de %s\n", cantidad_monedas, nombres_monedas[i]);
                    }
                }

                //  Si quedan céntimos sueltos menores a 5c (1c o 2c)
                if (cambio_total > 0) {
                    printf("          - Sobrante no almacenable: %d centimos\n", cambio_total);
                }
            }

            // Guardado automático
            guardar_texto(config->ruta_inventario, inventario, n);
            printf("[Sistema]: El archivo %s ha sido actualizado.\n", config->ruta_inventario);
        } else {
            printf("[Sistema]: La STM32 ha devuelto un error. No se modifica el stock.\n");
        }

    } else {
        printf("\n[AVISO]: No se ha recibido respuesta de la STM32 (Timeout).\n");
    }

    CloseHandle(hSerial);

#else // CONFIGURACIÓN PARA LINUX/MAC
    int fd = open(config->puerto_serie, O_RDWR | O_NOCTTY | O_NDELAY);
    if (fd == -1) {
        printf("[Error]: No se pudo abrir el puerto serie.\n");
        return;
    }
    struct termios options;
    tcgetattr(fd, &options);
    cfsetispeed(&options, B9600);
    cfsetospeed(&options, B9600);
    options.c_cflag |= (CLOCAL | CREAD);
    options.c_cflag &= ~PARENB;
    options.c_cflag &= ~CSTOPB;
    options.c_cflag &= ~CSIZE;
    options.c_cflag |= CS8;
    tcsetattr(fd, TCSANOW, &options);

    write(fd, cadena_enviar, strlen(cadena_enviar));
    usleep(500000);

    char rx_buf[128] = {0};
    read(fd, rx_buf, sizeof(rx_buf) - 1);
    printf("\n--- RESPUESTA DE STM32 ---\n%s\n", rx_buf);
    close(fd);
#endif
}