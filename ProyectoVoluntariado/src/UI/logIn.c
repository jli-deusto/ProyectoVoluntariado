/*
 * logIn.c
 *
 *  Created on: 29 mar 2026
 *      Author: danielavalentina.s
 */
#include "stdio.h"
#include "stdlib.h"
#include "logIn.h"
#include "shared/constantes.h"
#include "admin/validar/data_validar.h"
#include "UI/logIn.h"
#include "UI/menu.h"

void bienvenida() {
	int opcion;
	char buffer[opt];
	printf("=========================================\n");
	printf("~ Bienvenido a B2H: Back to heaven ~\n");
	printf("=========================================\n");
	printf("1. iniciar sesion\n");
	printf("2. registrarse\n");
	printf("3. Salir del sistema\n");
	printf("Selecciona una opcion: ");
	fflush(stdout);
	fgets(buffer, sizeof(buffer), stdin);
	sscanf(buffer, "%d", &opcion);
	switch (opcion) {
	case 1: inicio_sesion(); break;
	case 2:	registro(); break;
	case 3: log_out(); break;
	default: {
		puts("opcion no valida\n");
		bienvenida();
	}

	}
}

void inicio_sesion() {
	char username[MAX_NOMBRE];
	char clave[MAX_PASSWORD];
	char buffer_user[MAX_NOMBRE];
	char buffer_pwd[MAX_PASSWORD];
	// desatascar buffr stdin
	int c;
	while ((c = getchar()) != '\n' && c != EOF);

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
