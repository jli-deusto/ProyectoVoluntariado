/*
 * gestionMenu.h
 *
 *  Created on: 1 abr 2026
 *      Author: danielavalentina.s
 */

#ifndef UI_GESTIONMENU_H_
#define UI_GESTIONMENU_H_
#include "shared/modelo_user.h"

typedef void (*MenuCallback)(void);
typedef int (*MenuCallbackUser)(User*);

void MostrarMenu(char header[], char *opciones[], MenuCallback funciones[],int size1, int size2 );
void MostrarMenuUsers(char header[], char *opciones[], MenuCallbackUser funciones[],int size1, int size2, User *usuario);


#endif /* UI_GESTIONMENU_H_ */
