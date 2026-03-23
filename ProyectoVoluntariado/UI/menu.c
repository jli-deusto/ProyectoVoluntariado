/*
 * menu.c
 *
 *  Created on: 22 mar 2026
 *      Author: danielavalentina.s
 */

#include <stdio.h>
#include "menu.h"

void menu_usuarios() {}

void menu_actividades() {}

void menu_noticias() {}

void menu_principal() {
    int opcion = -1;
    char buffer[10];

    do {
        printf("\n================================\n");
        printf("    B2H - ADMINISTRADOR LOCAL   \n");
        printf("================================\n");
        printf("1. Gestionar usuarios\n");
        printf("2. Gestionar actividades\n");
        printf("3. Gestionar noticias\n");
        printf("4. Salir\n");
        printf("Selecciona una opcion: ");
        fgets(buffer, sizeof(buffer), stdin);
        sscanf(buffer, "%d", &opcion);

        switch(opcion) {
            case 1:
                menu_usuarios();
                break;
            case 2:
                menu_actividades();
                break;
            case 3:
                menu_noticias();
                break;
            case 4:
                printf("Cerrando sesion...\n");
                break;
            default:
                printf("Opcion no valida, intentalo de nuevo\n");
        }
    } while (opcion != 4);
}

