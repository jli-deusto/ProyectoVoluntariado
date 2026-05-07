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
        "INSERT OR REPLACE INTO RESERVA (ESTADO_RESERVA, FECHA, ID_USUARIO, ID_ACTIVIDAD) "
        "VALUES (?, ?, ?, ?);";

    sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);

    sqlite3_bind_int(stmt, 1, r->estado_reserva);
    sqlite3_bind_text(stmt, 2, r->fecha, -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 3, r->id_usuario);
    sqlite3_bind_int(stmt, 4, r->id_actividad);
    int rc = sqlite3_step(stmt);
        if (rc != SQLITE_DONE) {
            printf("Error SQL en insert: %s\n", sqlite3_errmsg(db));
        }

    sqlite3_finalize(stmt);
}//

int repo_reserva_delete(sqlite3 *db, int id_reserva) {
    sqlite3_stmt *stmt;
    const char *sql = "DELETE FROM RESERVA WHERE ID = ?;";

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK)
        return 0;

    sqlite3_bind_int(stmt, 1, id_reserva);

    int rc = sqlite3_step(stmt);
    sqlite3_finalize(stmt);

    return (rc == SQLITE_DONE && sqlite3_changes(db) > 0);
}
