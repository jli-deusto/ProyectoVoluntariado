/*
 * repo_actividad.c
 *
 *  Created on: 19 mar 2026
 *      Author: j.li
 */

#include "../../Libs/sqlite/sqlite3.h"
#include "repo_actividad.h"
#include "src/shared/modelo_actividad.h"
#include <stdio.h>


void repo_actividad_insert(sqlite3 *db, Actividad *a) {
    sqlite3_stmt *stmt;

    const char *sql =
        "INSERT INTO ACTIVIDAD (TITULO, MAX_PLAZAS, UBICACION, DESCRIPCION, "
        "HORA_INIT, HORA_FIN, TIPO, FECHA) "
        "VALUES (?, ?, ?, ?, ?, ?, ?, ?);";

    sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);

    sqlite3_bind_text(stmt, 1, a->titulo, -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 2, a->max_plazas);
    sqlite3_bind_text(stmt, 3, a->ubicacion, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 4, a->descripcion, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 5, a->hora_init, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 6, a->hora_fin, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 7, a->tipo, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 8, a->fecha, -1, SQLITE_STATIC);

    sqlite3_step(stmt);
    sqlite3_finalize(stmt);
}
