/*
 * gestionMenu.h
 *
 *  Created on: 1 abr 2026
 *      Author: danielavalentina.s
 */

#ifndef UI_GESTIONMENU_H_
#define UI_GESTIONMENU_H_
#include "shared/modelo_user.h"
#include "shared/modelo_actividad.h"

typedef void (*MenuCallback)(void);
typedef int (*MenuCallbackUser)(User*);
typedef int (*MenuCallbackActividad)(Actividad*);


void MostrarMenu(char header[], char *opciones[], MenuCallback funciones[],int size1, int size2 );
void MostrarMenuUsers(char header[], char *opciones[], MenuCallbackUser funciones[],int size1, int size2, User *usuario);
void MostrarMenuActividades(char header[], char *opciones[], MenuCallbackActividad funciones[],int size1, int size2, Actividad *actividad);


void gestion_usuarios();
void gestion_actividades();
void gestion_noticias();
void gestion_informes();
void mostrar_configuracion_sistema();

void limpiar_buffer(void);

#endif /* UI_GESTIONMENU_H_*/
