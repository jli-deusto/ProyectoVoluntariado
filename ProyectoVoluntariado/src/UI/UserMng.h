/*
 * UserMng.h
 *
 *  Created on: 31 mar 2026
 *      Author: danielavalentina.s
 */

#ifndef UI_USERMNG_H_
#define UI_USERMNG_H_
#include "shared/constantes.h"
#include "shared/modelo_user.h"

int crearUsuario(User *usuario);
int modificarUsuario(User *usuario);
int eliminarUsuario(User *usuario);
int cargarUsuarioPorID(User *u);
void extraerNombre(char usuario[MAX_NOMBRE]);
void extraerMail(char usuario[MAX_NOMBRE]);
void extraerTlf(char usuario[MAX_NOMBRE]);
void extraerClave(char usuario[MAX_NOMBRE]);
void listarUsuarios();

#endif /* UI_USERMNG_H_ */
