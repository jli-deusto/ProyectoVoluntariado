/*
 * modelo_reserva.h
 *
 *  Created on: 27 mar 2026
 *      Author: j.li
 */

#ifndef MODELO_MODELO_RESERVA_H_
#define MODELO_MODELO_RESERVA_H_

typedef struct {
    int estado_reserva;
    char fecha[20];
    int id_usuario;
    int id_actividad;
} Reserva;


#endif /* MODELO_MODELO_RESERVA_H_ */
