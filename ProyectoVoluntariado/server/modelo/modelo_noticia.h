/*
 * modelo_noticia.h
 *
 *  Created on: 27 mar 2026
 *      Author: j.li
 */

#ifndef MODELO_MODELO_NOTICIA_H_
#define MODELO_MODELO_NOTICIA_H_

typedef struct {
    char titulo[100];
    char descripcion[300];
    char fecha[20];
    int id_usuario;
} Noticia;


#endif /* MODELO_MODELO_NOTICIA_H_ */
