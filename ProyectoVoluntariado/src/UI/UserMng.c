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

sqlite3 *db;

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


int crearUsuario(){
	char tlf[MAX_PASSWORD];
	char clave[MAX_PASSWORD];
	char username[MAX_NOMBRE];
	char mail[MAX_EMAIL];

	User usuario;
	char fecha[FECHA];
	time_t t = time(NULL);
	struct tm tm = *localtime(&t);
	printf("=====Creando Nuevo Usuario ====\n");

	extraerMail(mail);
	extraerTlf(tlf);
	extraerNombre(username);
	extraerClave(clave);


	printf("telefono: ");
	fflush(stdout);

	// fecha de registro
	sprintf(fecha, "%02d/%02d/%04d",tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);

	usuario.estado_cuenta = 1;
	usuario.rol = 0;
	strcpy(usuario.fecha_reg, fecha);
	strcpy(usuario.nombre, username);
	strcpy(usuario.pw, clave);
	strcpy(usuario.tlf, tlf);
	strcpy(usuario.mail, mail);

	// abrimos conexion con la bd
	if (sqlite3_open("server_data.db", &db) != SQLITE_OK) {
	    printf("No se pudo abrir la base de datos\n");
	    return 0;
	}
	int sol = repo_usuario_insert(db, &usuario);
	sqlite3_close(db);
	return sol;
};


int modificarUsuario(User *usuario){

	return 0;
};
int eliminarUsuario(User *usuario){

	return 0;
};
