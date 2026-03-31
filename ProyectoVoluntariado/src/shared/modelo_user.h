/*
 * modelo_user.h
 *
 *  Created on: 20 mar 2026
 *      Author: danielavalentina.s
 */

#ifndef MODELO_USER_H_
#define MODELO_USER_H_
#include "constantes.h"

typedef struct{
	int id;
	char mail[MAX_EMAIL];
	char pw[MAX_PASSWORD];
	char nombre[MAX_NOMBRE];
    char tlf[MAX_TELEFONO];
    int  rol;                // 0 = voluntario, 1 = admin
    int  estado_cuenta; // 0 = inactiva, 1 = activa
    char fecha_reg[FECHA];
} User;

#endif /* MODELO_USER_H_ */
