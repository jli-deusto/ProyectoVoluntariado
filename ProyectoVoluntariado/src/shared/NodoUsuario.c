/*
 * NodoUsuario.c
 *
 *  Created on: 2 may 2026
 *      Author: danielavalentina.s
 */

#include <stdlib.h>
#include "modelo_user.h"
#include "NodoUsuario.h"

NodoUsuario* crear_nodo(User *u) {
    NodoUsuario *n = malloc(sizeof(*n));
    if (!n) return NULL;
    n->data = *u;
    n->sig  = NULL;
    return n;
}

void insertar_usuario(ListaUsuarios *l,
                      User *u) {
    NodoUsuario *n = crear_nodo(u);
    n->sig = l->cabeza;
    l->cabeza = n;
    l->tamanio++;
}


void liberar_lista(ListaUsuarios *l) {
    NodoUsuario *cur = l->cabeza;
    while (cur) {
        NodoUsuario *tmp = cur->sig;
        free(cur);
        cur = tmp;
    }
    l->cabeza = NULL;
    l->tamanio = 0;
}
