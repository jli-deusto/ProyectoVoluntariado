/*
 * contrasena.h
 *
 *  Created on: 2 may 2026
 *      Author: danielavalentina.s
 */

#ifndef SERVER_SEGURIDAD_CONTRASENA_H_
#define SERVER_SEGURIDAD_CONTRASENA_H_

#include <stdio.h>



#endif /* SERVER_SEGURIDAD_CONTRASENA_H_ */

void hashear_password(const char *pw,char *dest, size_t n);

unsigned long hash_djb2(const char *str);
