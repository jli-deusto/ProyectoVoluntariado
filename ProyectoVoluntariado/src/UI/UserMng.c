/*
 * UserMng.c
 *
 *  Created on: 31 mar 2026
 *      Author: danielavalentina.s
 */


#include <stdio.h>
#include "UserMng.h"
#include "shared/constantes.h"
#include "shared/modelo_user.h"
#include <time.h>

// funciones repetidas
void extraerNombre(char username[MAX_NOMBRE]){
	char buffer_user[MAX_NOMBRE];
	printf("Nombre Usuario: ");
	fflush(stdout);
	fgets(buffer_user, sizeof(buffer_user), stdin);
	sscanf(buffer_user, "%s", username);
};
void extraerMail(char mail[MAX_EMAIL]){
	char buffer_mail[MAX_NOMBRE];
	printf("Mail: ");
	fflush(stdout);
	fgets(buffer_mail, sizeof(buffer_mail), stdin);
	sscanf(buffer_mail, "%s", mail);

};
void extraerTlf(char tlf[MAX_TELEFONO]){
	char buffer_tlf[MAX_PASSWORD];

	printf("Telefono: ");
	fflush(stdout);
	fgets(buffer_tlf, sizeof(buffer_tlf), stdin);
	sscanf(buffer_tlf, "%s", tlf);
};

void extraerClave(char clave[MAX_PASSWORD]){
	char buffer_pwd[MAX_PASSWORD];
	printf("Clave: ");
	fflush(stdout);
	fgets(buffer_pwd, sizeof(buffer_pwd), stdin);
	sscanf(buffer_pwd, "%s", clave);
};


int crearUsuario(){
	char tlf[MAX_PASSWORD];
	char clave[MAX_PASSWORD];
	char username[MAX_NOMBRE];
	char mail[MAX_EMAIL];

	User usuario;
	char fecha[FECHA];
	time_t t = time(NULL);
	struct tm tm = *localtime(&t);
	printf("=====Creando Nuevo Usuario ====");

	extraerMail(mail);
	extraerTlf(clave);
	extraerNombre(username);
	extraerClave(mail);

	printf("telefono: ");
	fflush(stdout);

	// fecha de registro
	sprintf(fecha, "%02d/%02d/%04d",tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);

	usuario.estado_cuenta = 1;
	usuario.rol = 0;
	usuario.fecha_reg = fecha;
	usuario.mail = mail;
	usuario.nombre = username;
	usuario.pw = clave;
	usuario.tlf = tlf;


	return 0;
};


int modificarUsuario(User *usuario){

	return 0;
};
int eliminarUsuario(User *usuario){

	return 0;
};
