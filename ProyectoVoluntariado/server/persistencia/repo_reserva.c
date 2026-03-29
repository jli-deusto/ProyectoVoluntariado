/*
 * repo_reserva.c
 *
 *  Created on: 19 mar 2026
 *      Author: j.li
 */

#include "../../Libs/sqlite/sqlite3.h"
#include "repo_reserva.h"
#include "shared/modelo_reserva.h"
#include <stdio.h>

void repo_reserva_insert(sqlite3 *db, Reserva *r) {
    sqlite3_stmt *stmt;

    const char *sql =
        "INSERT INTO RESERVA (ESTADO_RESERVA, FECHA, ID_USUARIO, ID_ACTIVIDAD) "
        "VALUES (?, ?, ?, ?);";

    sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);

    sqlite3_bind_int(stmt, 1, r->estado);
    sqlite3_bind_text(stmt, 2, r->fecha, -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 3, r->id_usuario);
    sqlite3_bind_int(stmt, 4, r->id_actividad);
    int rc = sqlite3_step(stmt);
        if (rc != SQLITE_DONE) {
            printf("Error SQL en insert: %s\n", sqlite3_errmsg(db));
        }

    sqlite3_finalize(stmt);
}
