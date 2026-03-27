/*
 * modelo_actividad.h
 *
 *  Created on: 27 mar 2026
 *      Author: j.li
 */

#ifndef MODELO_MODELO_ACTIVIDAD_H_
#define MODELO_MODELO_ACTIVIDAD_H_

typedef struct {
    char titulo[100];
    int max_plazas;
    char ubicacion[100];
    char descripcion[200];
    char hora_init[20];
    char hora_fin[20];
    char tipo[50];
    char fecha[20];
} Actividad;

#endif /* MODELO_MODELO_ACTIVIDAD_H_ */
