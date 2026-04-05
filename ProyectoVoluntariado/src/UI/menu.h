/*
 * menu.h
 *
 *  Created on: 22 mar 2026
 *      Author: danielavalentina.s
 */

#ifndef MENU_H_
#define MENU_H_

typedef void (*MenuCallback)(void);

void limpiar_buffer();

void menu_principal();
void menu_admin();
void menu_usuarios();
void menu_actividades();
void menu_noticias();

void gestion_usuarios();
void gestion_actividades();
void gestion_noticias();
void gestion_informes();
void salir_admin();

#endif /* MENU_H_ */
