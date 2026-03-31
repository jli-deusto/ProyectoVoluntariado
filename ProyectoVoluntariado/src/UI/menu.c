/*
 * menu.c
 *
 *  Created on: 22 mar 2026
 *      Author: danielavalentina.s
 */

#include <stdio.h>
#include "menu.h"
#include "shared/constantes.h"
void menu_usuarios() {}

void menu_actividades() {}

void menu_noticias() {}

void menu_admin() {
    int opcion = -1;
    char buffer[opt];

    do {
        printf("\n================================\n"); // puts lo mismo que printf pero sin formateado
        printf("    B2H - ADMINISTRADOR LOCAL   \n");
        printf("================================\n");
        printf("1. Gestionar usuarios\n");
        printf("2. Gestionar actividades\n");
        printf("3. Gestionar noticias\n");
        printf("4. Salir\n");
        printf("Selecciona una opcion: ");
        fflush(stdout); // desatasca el fichero de salida - esto indica que la lectura antes de imprimir ir over
        fgets(buffer, sizeof(buffer), stdin);
        sscanf(buffer, "%d", &opcion);

        switch(opcion) {
            case 1:
                gestion_usuarios();
                break;
            case 2:
                gestion_actividades();
                break;
            case 3:
                gestion_noticias();
                break;
            case 4:
                printf("Cerrando sesion...\n");
                break;
            default:
                printf("Opcion no valida, intentalo de nuevo\n");
        }
    } while (opcion != 4);
}
gestion_usuarios() {
	// crear usuario
	// modificar usuario
	// eliminar usuario

};
gestion_actividades(){
	// crear actividad
	// modificar actividad
	// eliminar actividad
};
gestion_noticias(){
	// crear actividad
	// modificar actividad
	// eliminar actividad
};

