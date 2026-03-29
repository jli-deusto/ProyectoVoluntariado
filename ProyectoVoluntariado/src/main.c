/*
 * main.c
 *
 *  Created on: 27 mar 2026
 *      Author: j.li
 */


#include <stdio.h>
#include "UI/logIn.h"
int main_server();
int main_admin();

int main() {
    int opcion;

    bienvenida();
    inicio_sesion();
    printf("1. Ejecutar modo ADMIN\n");
    printf("2. Ejecutar modo SERVER\n");
    printf("Seleccione una opción: ");
	fflush(stdout);
    scanf("%d", &opcion);

    if (opcion == 1) {
        return main_admin();
    } else if (opcion == 2) {
        return main_server();
    } else {
        printf("Opción no válida.\n");
        return 1;
    }
}
