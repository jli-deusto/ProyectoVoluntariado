/*
 * modelo_reserva.h
 *
 *  Created on: 20 mar 2026
 *      Author: danielavalentina.s
 */

#ifndef MODELO_RESERVA_H_
#define MODELO_RESERVA_H_
#include "constantes.h"

typedef struct{
	int estado_reserva; // 1 aprobada 0 cancelada.
	int id_reserva;
	int id_actividad;
	int id_usuario;
	char fecha[FECHA];
} Reserva;

#endif /* MODELO_RESERVA_H_ */
