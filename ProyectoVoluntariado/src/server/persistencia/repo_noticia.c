/*
 * repo_noticia.c
 *
 *  Created on: 19 mar 2026
 *      Author: j.li
 */

#include "../../Libs/sqlite/sqlite3.h"
#include "repo_noticia.h"
#include "shared/modelo_noticia.h"
#include <stdio.h>
#include <string.h>

void repo_noticia_insert(sqlite3 *db, Noticia *n) {

    sqlite3_stmt *stmt;

    const char *sql =
        "INSERT INTO NOTICIA (TITULO, CONTENIDO, FECHA, ID_USUARIO) "
        "VALUES (?, ?, ?, ?);";

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        printf("Error preparando INSERT: %s\n", sqlite3_errmsg(db));
        return;
    }

    sqlite3_bind_text(stmt, 1, n->titulo, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, n->contenido, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, n->fecha_pub, -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 4, n->id_usuario);

    int rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        printf("Error SQL en insert: %s\n", sqlite3_errmsg(db));
    }

    sqlite3_finalize(stmt);
}

int repo_noticia_get(sqlite3 *db, int id, Noticia *n) {

    sqlite3_stmt *stmt;

    const char *sql =
        "SELECT TITULO, CONTENIDO, FECHA, ID_USUARIO "
        "FROM NOTICIA WHERE ID=?;";

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK)
        return 0;

    sqlite3_bind_int(stmt, 1, id);

    if (sqlite3_step(stmt) == SQLITE_ROW) {

        strcpy(n->titulo,      (const char*)sqlite3_column_text(stmt, 0));
        strcpy(n->contenido, (const char*)sqlite3_column_text(stmt, 1));
        strcpy(n->fecha_pub,   (const char*)sqlite3_column_text(stmt, 2));
        n->id_usuario =         sqlite3_column_int(stmt, 3);
        n->id_noticia = id;

        sqlite3_finalize(stmt);
        return 1;
    }

    sqlite3_finalize(stmt);
    return 0;
}

int repo_noticia_update(sqlite3 *db, Noticia *n) {

    sqlite3_stmt *stmt;

    const char *sql =
        "UPDATE NOTICIA SET "
        "TITULO=?, CONTENIDO=?, FECHA=?, ID_USUARIO=? "
        "WHERE ID=?;";

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK)
        return 0;

    sqlite3_bind_text(stmt, 1, n->titulo, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, n->contenido, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, n->fecha_pub, -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 4, n->id_usuario);
    sqlite3_bind_int(stmt, 5, n->id_noticia);

    int ok = (sqlite3_step(stmt) == SQLITE_DONE);
    sqlite3_finalize(stmt);
    return ok;
}

int repo_noticia_delete(sqlite3 *db, int id) {

    sqlite3_stmt *stmt;

    const char *sql = "DELETE FROM NOTICIA WHERE ID=?;";

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK)
        return 0;

    sqlite3_bind_int(stmt, 1, id);

    int ok = (sqlite3_step(stmt) == SQLITE_DONE);
    sqlite3_finalize(stmt);
    return ok;
}
