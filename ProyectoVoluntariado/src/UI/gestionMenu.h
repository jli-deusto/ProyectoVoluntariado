/*
 * gestionMenu.h
 *
 *  Created on: 1 abr 2026
 *      Author: danielavalentina.s
 */

#ifndef UI_GESTIONMENU_H_
#define UI_GESTIONMENU_H_


typedef void (*MenuCallback)(void);
void MostrarMenu(char header[], char *opciones[], MenuCallback funciones[],int size1, int size2 );


#endif /* UI_GESTIONMENU_H_ */
