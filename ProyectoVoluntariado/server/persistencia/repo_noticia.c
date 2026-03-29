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

void repo_noticia_insert(sqlite3 *db, Noticia *n) {
    sqlite3_stmt *stmt;

    const char *sql =
        "INSERT INTO NOTICIA (TITULO, DESCRIPCION, FECHA, ID_USUARIO) "
        "VALUES (?, ?, ?, ?);";

    sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);

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
