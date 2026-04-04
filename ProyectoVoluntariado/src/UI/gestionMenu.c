/*
 * gestionMenu.c
 *
 *  Created on: 1 abr 2026
 *      Author: danielavalentina.s
 */

#include <stdio.h>
#include <stdlib.h>
#include "gestionMenu.h"
#include "shared/modelo_user.h"
#include "menu.h"

void MostrarMenu(char header[], char *opciones[], MenuCallback funciones[],
                 int size1, int size2)
{
    int opcion = -1;

    while (1) {

        printf("\n==========================================\n        %s      \n==========================================\n", header);

        if (size1 != size2) {
            puts("llamada a funcion mal definida");
            return;
        }

        for (int i = 0; i < size1; i++) {
            printf("%d. %s\n", i + 1, opciones[i]);
        }

        char bufferOpcion[20];
        printf("Seleccione una opcion: ");
        fflush(stdout);

        if (!fgets(bufferOpcion, sizeof(bufferOpcion), stdin) ||
            sscanf(bufferOpcion, "%d", &opcion) != 1 ||
            opcion < 1 || opcion > size1)
        {
            puts("Opción inválida");
            continue;
        }

        // si la última opción es "Salir"
        if (opcion == size1) {
            return;
        }

        funciones[opcion - 1]();

    }
}


void MostrarMenuUsers(char header[], char *opciones[], MenuCallbackUser funciones[],int size1, int size2, User *usuario) {
	int opcion = -1;
	do {

		printf("\n==========================================\n        %s      \n==========================================\n", header);
		if (size1 != size2) {
			puts("llamada a funcion mal definida");
			return;
		}
		for (int i = 0; i < size1; i++) {
			printf("%d. %s\n", i + 1, opciones[i]);
		}
		fflush(stdout);

		char bufferOpcion[20];
		printf("Seleccione una opcion: ");
		fflush(stdout);

		if (!fgets(bufferOpcion, sizeof(bufferOpcion), stdin)
				|| sscanf(bufferOpcion, "%d", &opcion) != 1 || opcion < 1
				|| opcion > size1) {

			puts("Opción inválida");
			opcion = -1;
		} else {
			funciones[opcion -1](usuario);
		}
	} while (opcion == -1);
	return;

};



void MostrarMenuActividades(char header[], char *opciones[], MenuCallbackActividad funciones[], int size1, int size2, Actividad *actividad) {
    int opcion = -1;

    while (1) {

        printf("\n==========================================\n        %s      \n==========================================\n", header);

        if (size1 != size2) {
            puts("llamada a funcion mal definida");
            return;
        }

        for (int i = 0; i < size1; i++) {
            printf("%d. %s\n", i + 1, opciones[i]);
        }
        fflush(stdout);

        char bufferOpcion[20];
        printf("Seleccione una opcion: ");
        fflush(stdout);

        if (!fgets(bufferOpcion, sizeof(bufferOpcion), stdin) ||
            sscanf(bufferOpcion, "%d", &opcion) != 1 ||
            opcion < 1 || opcion > size1)
        {
            puts("Opción inválida");
            continue;
        }

        if (opcion == size1) {
            return;
        }

        funciones[opcion - 1](actividad);

    }
}
