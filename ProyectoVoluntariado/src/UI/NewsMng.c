/*
 * NewsMng.c
 *
 *  Created on: 4 abr 2026
 *      Author: teodoraalexandra.b
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "NewsMng.h"
#include "shared/constantes.h"
#include "server/persistencia/repo_noticia.h"
#include "Libs/sqlite/sqlite3.h"
#include "shared/modelo_noticia.h"

extern sqlite3 *db;

static void extraerCadena(const char *msg, char *dest, size_t tam){
    printf("%s", msg);
    fflush(stdout);
    if (fgets(dest, tam, stdin)) {
        dest[strcspn(dest, "\n")] = 0;
    }
}

int crearNoticia(Noticia *ignored) {

    Noticia n_local;
    Noticia *n = &n_local;

    char buffer_id[16];

    printf("\n===== Crear Noticia =====\n");

    extraerCadena("Título: ", n->titulo, MAX_TITULO);
    extraerCadena("Contenido: ", n->contenido, MAX_CONTENIDO);
    extraerCadena("Fecha (DD/MM/AAAA): ", n->fecha_pub, FECHA);
    extraerCadena("ID usuario autor: ", buffer_id, sizeof(buffer_id));

    n->id_usuario = atoi(buffer_id);

    repo_noticia_insert(db, n);

    printf("Noticia creada correctamente.\n");
    return 1;
}

int modificarNoticia(Noticia *ignored) {

    Noticia n_local;
    Noticia *n = &n_local;

    char buffer_id[16];

    printf("\n===== Modificar Noticia =====\n");

    printf("ID de la noticia a modificar: ");
    fflush(stdout);

    if (!fgets(buffer_id, sizeof(buffer_id), stdin) ||
        sscanf(buffer_id, "%d", &n->id_noticia) != 1) {
        printf("ID inválido.\n");
        return 0;
    }

    if (!repo_noticia_get(db, n->id_noticia, n)) {
        printf("No existe noticia con ese ID.\n");
        return 0;
    }

    printf("\n--- Datos actuales ---\n");
    printf("Título: %s\n", n->titulo);
    printf("Contenido: %s\n", n->contenido);
    printf("Fecha: %s\n", n->fecha_pub);
    printf("ID Usuario: %d\n", n->id_usuario);

    extraerCadena("Nuevo título: ", n->titulo, MAX_TITULO);
    extraerCadena("Nuevo contenido: ", n->contenido, MAX_CONTENIDO);
    extraerCadena("Nueva fecha (DD/MM/AAAA): ", n->fecha_pub, FECHA);

    char buffer_user[16];
    extraerCadena("Nuevo ID usuario autor: ", buffer_user, sizeof(buffer_user));
    n->id_usuario = atoi(buffer_user);

    int ok = repo_noticia_update(db, n);

    if (ok)
        printf("Noticia modificada correctamente.\n");
    else
        printf("Error al modificar la noticia.\n");

    return ok;
}
int eliminarNoticia(Noticia *ignored) {

    Noticia n_local;
    Noticia *n = &n_local;

    char buffer_id[16];

    printf("\n===== Eliminar Noticia =====\n");

    printf("ID de la noticia a eliminar: ");
    fflush(stdout);

    if (!fgets(buffer_id, sizeof(buffer_id), stdin) ||
        sscanf(buffer_id, "%d", &n->id_noticia) != 1) {
        printf("ID inválido.\n");
        return 0;
    }

    if (!repo_noticia_get(db, n->id_noticia, n)) {
        printf("No existe noticia con ese ID.\n");
        return 0;
    }

    printf("\n--- Noticia encontrada ---\n");
    printf("Título: %s\n", n->titulo);
    printf("Fecha: %s\n", n->fecha_pub);
    printf("Autor: %d\n", n->id_usuario);

    char confirm[8];
    extraerCadena("¿Eliminar esta noticia? (s/n): ", confirm, sizeof(confirm));

    if (confirm[0] != 's' && confirm[0] != 'S') {
        printf("Operación cancelada.\n");
        return 0;
    }

    int ok = repo_noticia_delete(db, n->id_noticia);

    if (ok)
        printf("Noticia eliminada correctamente.\n");
    else
        printf("Error al eliminar la noticia.\n");

    return ok;
}
