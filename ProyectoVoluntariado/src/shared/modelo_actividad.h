/*
 * modelo_actividad.h
 *
 *  Created on: 20 mar 2026
 *      Author: danielavalentina.s
 */

#ifndef MODELO_ACTIVIDAD_H_
#define MODELO_ACTIVIDAD_H_
#include "constantes.h"
typedef struct {
	char hora_init[HORA]; // HH:MM
	char hora_fin[HORA]; // HH:MM
	int max_plazas;
	int id_actividad;
	char titulo[MAX_TITULO];
	char ubicacion[MAX_UBICACION];
	char descripcion[MAX_CONTENIDO];
	char fecha[FECHA];
	char tipo[50];

} Actividad;

#endif /* MODELO_ACTIVIDAD_H_ */
