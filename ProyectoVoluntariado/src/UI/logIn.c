/*
 * logIn.c
 *
 *  Created on: 29 mar 2026
 *      Author: danielavalentina.s
 */
#include "stdio.h"
#include "stdlib.h"
#include "logIn.h"
#include "gestionMenu.h"
#include "shared/constantes.h"
#include "admin/validar/data_validar.h"
#include "UI/logIn.h"
#include "UI/menu.h"

void bienvenida() {

    char header[] = "~ Bienvenido a B2H: Back to heaven ~";

    const char *opciones[] = {
        "Iniciar sesión",
        "Registrarse",
        "Salir del sistema"
    };

    MenuCallback funciones[] = {
        inicio_sesion,   // 1
        registro,        // 2
        log_out          // 3
    };

    int num_opciones   = sizeof(opciones)  / sizeof(opciones[0]);
    int num_funciones  = sizeof(funciones) / sizeof(funciones[0]);

    MostrarMenu(header, (char **)opciones, funciones,
                num_opciones, num_funciones);
}


void inicio_sesion() {
	char username[MAX_NOMBRE];
	char clave[MAX_PASSWORD];
	char buffer_user[MAX_NOMBRE];
	char buffer_pwd[MAX_PASSWORD];
	// desatascar buffr stdin

	printf("=================Iniciar Sesion=================\n");
	printf("Usuario: ");
	fflush(stdout);
	fgets(buffer_user, sizeof(buffer_user), stdin);
	sscanf(buffer_user, "%s", username);
	printf("Clave/password: ");
	fflush(stdout);
	fgets(buffer_pwd, sizeof(buffer_pwd), stdin);
	sscanf(buffer_pwd, "%s", clave);
	if (validarAdmin(username, clave) == 1) {
	    menu_admin();
	} else {
	    puts("Usuario o clave incorrecta");
	}

	fflush(stdout);

}

void registro() {
	puts("tbd");
	fflush(stdout);
}

void log_out() {
	puts("tbd");
	fflush(stdout);
}
