/*
 * ActMng.h
 *
 *  Created on: 2 abr 2026
 *      Author: j.li
 */

#ifndef UI_ACTMNG_H_
#define UI_ACTMNG_H_

#include "shared/constantes.h"
#include "shared/modelo_actividad.h"

int crearActividad(Actividad *act);
int modificarActividad(Actividad *act);
int eliminarActividad(Actividad *act);

void extraerCadenaAct(const char *mensaje, char *dest, size_t tam);
void extraerTitulo(char *titulo);
void extraerDescripcion(char *descripcion);
void extraerUbicacion(char *ubicacion);
void extraerFecha(char *fecha);
void extraerHoraInit(char *hora);
void extraerHoraFin(char *hora);
void extraerTipo(char *tipo);

#endif /* UI_ACTMNG_H_ */
