/*
 * UserMng.c
 *
 *  Created on: 31 mar 2026
 *      Author: danielavalentina.s
 */

#include <stdio.h>
#include <time.h>
#include <string.h>
#include "UserMng.h"
#include "shared/constantes.h"
#include "shared/modelo_user.h"
#include "server/persistencia/repo_usuario.h"
#include "gestionMenu.h"

extern sqlite3 *db;

// funciones repetidas
void extraerCadena(const char *mensaje, char *dest, size_t tam) {
	printf("%s", mensaje);
	fflush(stdout);

	if (fgets(dest, tam, stdin)) {
		dest[strcspn(dest, "\n")] = 0; // eliminar salto de línea
	}
}

void extraerNombre(char *username) {
	extraerCadena("Nombre Usuario: ", username, MAX_NOMBRE);
}

void extraerMail(char *mail) {
	extraerCadena("Mail: ", mail, MAX_EMAIL);
}

void extraerTlf(char *tlf) {
	extraerCadena("Telefono: ", tlf, MAX_TELEFONO);
}

void extraerClave(char *clave) {
	extraerCadena("Clave: ", clave, MAX_PASSWORD);
}

int crearUsuario(User *usuario) {
	char tlf[MAX_TELEFONO];
	char clave[MAX_PASSWORD];
	char username[MAX_NOMBRE];
	char mail[MAX_EMAIL];


	char fecha[FECHA];
	time_t t = time(NULL);
	struct tm tm = *localtime(&t);
	printf("=====Creando Nuevo Usuario ====\n");

	extraerMail(mail);
	extraerTlf(tlf);
	extraerNombre(username);
	extraerClave(clave);

	// fecha de registro
	sprintf(fecha, "%02d/%02d/%04d", tm.tm_mday, tm.tm_mon + 1,
			tm.tm_year + 1900);

	usuario->estado_cuenta = 1;
	usuario->rol = 0;
	strcpy(usuario->fecha_reg, fecha);
	strcpy(usuario->nombre, username);
	strcpy(usuario->pw, clave);
	strcpy(usuario->tlf, tlf);
	strcpy(usuario->mail, mail);

	// abrimos conexion con la bd
	if (sqlite3_open("data/server_data.db", &db) != SQLITE_OK) {
		printf("No se pudo abrir la base de datos\n");
		return 0;
	}
	int sol = repo_usuario_check(db, usuario);
	if (sol == 0) {
		gestion_usuarios();
	}
	sol = repo_usuario_insert(db, usuario);
	sqlite3_close(db);
	return sol;
}
;

//User obtenerUsuario(){}
int modificarUsuario(User *usuario) {
	char tlf[MAX_TELEFONO];
	char clave[MAX_PASSWORD];

	puts("\n============== Modificación de Usuario ==============\n");
	puts("**Por cuestiones de gestión y administración\n "
			"el mail y el nombre no podrán ser modificados**\n");

	if (!cargarUsuarioPorID(usuario)) {
		return 0;
	}

    printf("\n--- Datos actuales ---\n");
    printf("Nombre: %s\n", usuario->nombre);
    printf("Mail: %s\n", usuario->mail);
    printf("Teléfono: %s\n", usuario->tlf);

	extraerClave(clave);
	extraerTlf(tlf);

	strcpy(usuario->pw, clave);
	strcpy(usuario->tlf, tlf);

	if (sqlite3_open("data/server_data.db", &db) != SQLITE_OK) {
		printf("No se pudo abrir la base de datos\n");
		return 0;
	}
	int sol = repo_usuario_update(db, usuario);
	sqlite3_close(db);

	if (sol){
		printf("Usuario modificado correctamente.\n");
	}else{
		printf("Error al modificar usuario.\n");
	}

	return sol;
}
;

int eliminarUsuario(User *usuario) {
	puts("==============Eliminación de Usuario==============");

	if (!cargarUsuarioPorID(usuario)) {
		return 0;
	}

	printf("\n--- Usuario encontrado ---\n");
	printf("Nombre: %s\n", usuario->nombre);
	printf("Mail: %s\n", usuario->mail);
	printf("Teléfono: %s\n", usuario->tlf);

	char confirm[8];
	extraerCadena("¿Eliminar este usuario? (s/n): ", confirm, sizeof(confirm));

	if (confirm[0] != 's' && confirm[0] != 'S') {
		printf("Operación cancelada.\n");
		return 0;
	}

	usuario->estado_cuenta = 0; // realmente no eliminamos el usuario, solo lo desactivamos
	if (sqlite3_open("data/server_data.db", &db) != SQLITE_OK) {
		printf("No se pudo abrir la base de datos\n");
		return 0;
	}
	int sol = repo_usuario_update(db, usuario);
	sqlite3_close(db);

	if (sol){
		printf("Usuario eliminado correctamente.\n");
	}else{
		printf("Error al eliminar usuario.\n");
	}

	return sol;

}
;


int cargarUsuarioPorID(User *usuario) {
    char buffer[16];

    printf("ID del usuario: ");
    fflush(stdout);

    if (!fgets(buffer, sizeof(buffer), stdin) ||
        sscanf(buffer, "%d", &usuario->id) != 1) {
        printf("ID inválido.\n");
        return 0;
    }

    if (sqlite3_open("data/server_data.db", &db) != SQLITE_OK) {
        printf("No se pudo abrir la base de datos\n");
        return 0;
    }

    if (!repo_usuario_get(db, usuario->id, usuario)) {
        printf("No existe usuario con ese ID.\n");
        sqlite3_close(db);
        return 0;
    }

    sqlite3_close(db);
    return 1;
}


