/*
 * NodoUsuario.h
 *
 *  Created on: 2 may 2026
 *      Author: danielavalentina.s
 */

#ifndef NODOUSUARIO_H_
#define NODOUSUARIO_H_

typedef struct NodoUsuario {
    User data;
    struct NodoUsuario *sig;
} NodoUsuario;

typedef struct {
    NodoUsuario *cabeza;
    int tamanio;
} ListaUsuarios;

NodoUsuario* crear_nodo(User *u);

void insertar_usuario(ListaUsuarios *l,User *u);

void liberar_lista(ListaUsuarios *l);

#endif /* NODOUSUARIO_H_ */

