/*
 * repo_incidencia.h
 *
 *  Created on: 13 may 2026
 *      Author: j.li
 */

#ifndef SERVER_PERSISTENCIA_REPO_INCIDENCIA_H_
#define SERVER_PERSISTENCIA_REPO_INCIDENCIA_H_

#include "../../Libs/sqlite/sqlite3.h"

typedef struct {
    int  id;
    char descripcion[500];
    char ubicacion[100];
    char fecha_reporte[12];
    char hora_reporte[7];
    int  id_usuario;
} Incidencia;

int repo_incidencia_insert(sqlite3 *db, Incidencia *inc);

#endif /* SERVER_PERSISTENCIA_REPO_INCIDENCIA_H_ */
