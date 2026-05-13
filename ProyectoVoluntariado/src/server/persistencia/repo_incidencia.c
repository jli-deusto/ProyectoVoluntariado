/*
 * repo_incidencia.c
 *
 *  Created on: 13 may 2026
 *      Author: j.li
 */


#include "repo_incidencia.h"
#include "../../Libs/sqlite/sqlite3.h"
#include <stdio.h>

int repo_incidencia_insert(sqlite3 *db, Incidencia *inc) {
    sqlite3_stmt *stmt;

    const char *sql =
        "INSERT INTO INCIDENCIA "
        "(DESCRIPCION, UBICACION, FECHA_REPORTE, HORA_REPORTE, ID_USUARIO) "
        "VALUES (?, ?, ?, ?, ?);";

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        printf("Error preparando INSERT incidencia: %s\n", sqlite3_errmsg(db));
        return 0;
    }

    sqlite3_bind_text(stmt, 1, inc->descripcion, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, inc->ubicacion, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, inc->fecha_reporte, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 4, inc->hora_reporte, -1, SQLITE_STATIC);
    sqlite3_bind_int (stmt, 5, inc->id_usuario);

    int rc = sqlite3_step(stmt);
    sqlite3_finalize(stmt);

    if (rc != SQLITE_DONE) {
        printf("Error SQL insert incidencia: %s\n", sqlite3_errmsg(db));
        return 0;
    }

    return 1;
}

