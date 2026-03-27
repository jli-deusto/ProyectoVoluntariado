/*
 * modelo_user.h
 *
 *  Created on: 27 mar 2026
 *      Author: j.li
 */

#ifndef MODELO_MODELO_USER_H_
#define MODELO_MODELO_USER_H_


typedef struct {
    char nombre[100];
    char tlf[20];
    char mail[100];
    char pw[50];
    int rol;
    int estado_cuenta;
    char fecha_reg[20];
} Usuario;


#endif /* MODELO_MODELO_USER_H_ */
