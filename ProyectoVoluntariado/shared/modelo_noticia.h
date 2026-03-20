/*
 * modelo_noticia.h
 *
 *  Created on: 20 mar 2026
 *      Author: danielavalentina.s
 */

#ifndef MODELO_NOTICIA_H_
#define MODELO_NOTICIA_H_
#include "constantes.h"
typedef struct {
	char fecha_pub[FECHA];
	char titulo[MAX_TITULO];
	char contenido[MAX_CONTENIDO];
	int id_noticia;
} Noticia;

#endif /* MODELO_NOTICIA_H_ */
