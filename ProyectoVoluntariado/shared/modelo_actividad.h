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
	int hora_init; // minutes
	int hora_fin; // minutes
	int max_plazas;
	int id_actividad;

	char ubicacion[MAX_UBICACION];
	char actividad[100];
	char descripcion[MAX_CONTENIDO];
	char fecha[FECHA];
	char tipo[50];

} Actividad;

#endif /* MODELO_ACTIVIDAD_H_ */
