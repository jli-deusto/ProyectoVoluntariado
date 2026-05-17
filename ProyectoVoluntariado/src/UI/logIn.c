/*
 * logIn.c
 *
 *  Created on: 29 mar 2026
 *      Author: danielavalentina.s
 */

#include <string.h>
#include <time.h>

#include "stdio.h"
#include "stdlib.h"
#include "logIn.h"
#include "gestionMenu.h"
#include "shared/constantes.h"
#include "shared/modelo_user.h"
#include "admin/validar/data_validar.h"
#include "UI/logIn.h"
#include "UI/menu.h"
#include "server/persistencia/repo_usuario.h"
#include "server/seguridad/contrasena.h"
#include "Libs/sqlite/sqlite3.h"
#include "server/logs/logger.h"

extern sqlite3 *db;

void bienvenida() {

    char header[] = "~ Bienvenido a B2H: Back to heaven ~";

    const char *opciones[] = {
        "Iniciar sesión",
        "Salir del sistema"
    };

    MenuCallback funciones[] = {
        inicio_sesion,   // 1
        log_out          // 2
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

	//limpiar_buffer();
	fflush(stdout);

	// desatascar buffr stdin

	printf("=================Iniciar Sesion=================\n");
	fflush(stdout);

	printf("Usuario: ");
	fflush(stdout);
	fgets(buffer_user, sizeof(buffer_user), stdin);
	sscanf(buffer_user, "%s", username);

	printf("Clave/password: ");
	fflush(stdout);
	fgets(buffer_pwd, sizeof(buffer_pwd), stdin);
	sscanf(buffer_pwd, "%s", clave);

	if (validarAdmin(username, clave) == 1) {
		log_admin(LOG_INFO, "Inicio de sesión de administrador correcto.");
	    menu_admin();
	} else {
		log_admin(LOG_WARN, "Intento de inicio de sesión fallido.");
	    puts("Usuario o clave incorrecta");
	}

	fflush(stdout);

}

void registro() {
	printf("\n===== Registro de Nuevo Usuario =====\n");
	fflush(stdout);

	User nuevo;
	memset(&nuevo, 0, sizeof(User));

	// introduccion de datos
	printf("Nombre: ");
	fflush(stdout);
	fgets(nuevo.nombre, MAX_NOMBRE, stdin);
	nuevo.nombre[strcspn(nuevo.nombre, "\n")] = 0;

    printf("Email: ");
    fflush(stdout);
    fgets(nuevo.mail, MAX_EMAIL, stdin);
    nuevo.mail[strcspn(nuevo.mail, "\n")] = 0;

    printf("Teléfono: ");
    fflush(stdout);
    fgets(nuevo.tlf, MAX_TELEFONO, stdin);
    nuevo.tlf[strcspn(nuevo.tlf, "\n")] = 0;

    //contraseña (x2 para confirmacion)
    char clave1[MAX_PASSWORD];
    char clave2[MAX_PASSWORD];

    while (1) {
        printf("Contraseña: ");
        fflush(stdout);
        fgets(clave1, MAX_PASSWORD, stdin);
        clave1[strcspn(clave1, "\n")] = 0;

        printf("Confirmar contraseña: ");
        fflush(stdout);
        fgets(clave2, MAX_PASSWORD, stdin);
        clave2[strcspn(clave2, "\n")] = 0;

        if (strcmp(clave1, clave2) == 0) {
            break;
        }
        printf("Las contraseñas no coinciden. Inténtalo de nuevo.\n");
    }

    hashear_password(clave1, nuevo.pw, sizeof(nuevo.pw));

    //FECHA DE REGISTRO
    time_t t = time(NULL);
    struct tm tm_info = *localtime(&t);
    snprintf(nuevo.fecha_reg, FECHA, "%02d/%02d/%04d", tm_info.tm_mday,
    		tm_info.tm_mon + 1, tm_info.tm_year + 1900);


    nuevo.rol = 0;
    nuevo.estado_cuenta = 1;

    //GUARDAR EN LA BD
    if (sqlite3_open("data/server_data.db", &db) != SQLITE_OK) {
        printf("Error: no se pudo conectar con la base de datos.\n");
        log_servidor(LOG_ERROR, "registro(): no se pudo abrir la BD.");
        return;
    }

    //COMPROBAR GMAIL
    if (repo_usuario_check(db, &nuevo) == 0) {
        printf("Ya existe un usuario con ese email. Volviendo al menú...\n");
        sqlite3_close(db);
        return;
    }

    int ok = repo_usuario_insert(db, &nuevo);
    sqlite3_close(db);

    if (ok) {
        printf("\nRegistro completado. ¡Bienvenido/a, %s!\n", nuevo.nombre);
        log_voluntario(LOG_INFO, "Nuevo voluntario registrado correctamente.");
    } else {
        printf("\nError al registrar el usuario. Inténtalo más tarde.\n");
        log_servidor(LOG_ERROR, "registro(): fallo en repo_usuario_insert.");
    }

	fflush(stdout);
}

void log_out() {
    char buffer[8];

    printf("\n¿Deseas salir del programa? (s/n): ");
    fflush(stdout);

    if (!fgets(buffer, sizeof(buffer), stdin)) {
        printf("Entrada inválida.\n");
        return;
    }

    if (buffer[0] == 's' || buffer[0] == 'S') {
        printf("\nSaliendo del programa...\n");
        exit(0);
    } else {
        printf("\nOperación cancelada. Volviendo al menú inicial...\n");
    }
}



