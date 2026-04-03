/*
 * repo_actividad.c
 *
 *  Created on: 19 mar 2026
 *      Author: j.li
 */

#include "../../Libs/sqlite/sqlite3.h"
#include "repo_actividad.h"
#include "shared/modelo_actividad.h"
#include <stdio.h>
#include <string.h>



int repo_actividad_insert(sqlite3 *db, Actividad *a) {
    sqlite3_stmt *stmt;

    const char *sql =
        "INSERT INTO ACTIVIDAD "
        "(TITULO, MAX_PLAZAS, UBICACION, DESCRIPCION, HORA_INIT, HORA_FIN, TIPO, FECHA) "
        "VALUES (?, ?, ?, ?, ?, ?, ?, ?);";

    int prep = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (prep != SQLITE_OK) {
        printf("ERROR PREPARE: %s\n", sqlite3_errmsg(db));
        return 0;
    }

    sqlite3_bind_text(stmt, 1, a->titulo, -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 2, a->max_plazas);
    sqlite3_bind_text(stmt, 3, a->ubicacion, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 4, a->descripcion, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 5, a->hora_init, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 6, a->hora_fin, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 7, a->tipo, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 8, a->fecha, -1, SQLITE_STATIC);

    int step = sqlite3_step(stmt);
    if (step != SQLITE_DONE) {
        printf("ERROR STEP: %s\n", sqlite3_errmsg(db));
        sqlite3_finalize(stmt);
        return 0;
    }

    sqlite3_finalize(stmt);
    return 1;
}



int repo_actividad_update(sqlite3 *db, Actividad *a) {

    sqlite3_stmt *stmt;

    const char *sql =
        "UPDATE ACTIVIDAD SET "
        "TITULO=?, MAX_PLAZAS=?, UBICACION=?, DESCRIPCION=?, "
        "HORA_INIT=?, HORA_FIN=?, TIPO=?, FECHA=? "
        "WHERE ID=?;";

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK)
        return 0;

    sqlite3_bind_text(stmt, 1, a->titulo, -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 2, a->max_plazas);
    sqlite3_bind_text(stmt, 3, a->ubicacion, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 4, a->descripcion, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 5, a->hora_init, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 6, a->hora_fin, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 7, a->tipo, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 8, a->fecha, -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 9, a->id_actividad);

    int ok = (sqlite3_step(stmt) == SQLITE_DONE);
    sqlite3_finalize(stmt);

    return ok;
}



int repo_actividad_delete(sqlite3 *db, int id) {

    sqlite3_stmt *stmt;

    const char *sql = "DELETE FROM ACTIVIDAD WHERE ID=?;";

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK)
        return 0;

    sqlite3_bind_int(stmt, 1, id);

    int ok = (sqlite3_step(stmt) == SQLITE_DONE);
    sqlite3_finalize(stmt);

    return ok;
}




int repo_actividad_get(sqlite3 *db, int id, Actividad *a) {

    sqlite3_stmt *stmt;

    const char *sql =
        "SELECT TITULO, MAX_PLAZAS, UBICACION, DESCRIPCION, "
        "HORA_INIT, HORA_FIN, TIPO, FECHA "
        "FROM ACTIVIDAD WHERE ID=?;";

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK)
        return 0;

    sqlite3_bind_int(stmt, 1, id);

    if (sqlite3_step(stmt) == SQLITE_ROW) {

        strcpy(a->titulo,      (const char*)sqlite3_column_text(stmt, 0));
        a->max_plazas =         sqlite3_column_int(stmt, 1);
        strcpy(a->ubicacion,   (const char*)sqlite3_column_text(stmt, 2));
        strcpy(a->descripcion, (const char*)sqlite3_column_text(stmt, 3));
        strcpy(a->hora_init,   (const char*)sqlite3_column_text(stmt, 4));
        strcpy(a->hora_fin,    (const char*)sqlite3_column_text(stmt, 5));
        strcpy(a->tipo,        (const char*)sqlite3_column_text(stmt, 6));
        strcpy(a->fecha,       (const char*)sqlite3_column_text(stmt, 7));

        a->id_actividad = id;

        sqlite3_finalize(stmt);
        return 1;
    }

    sqlite3_finalize(stmt);
    return 0;
}
