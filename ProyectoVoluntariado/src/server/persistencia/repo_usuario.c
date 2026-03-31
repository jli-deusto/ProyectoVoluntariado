/*
 * repo_usuario.c
 *
 *  Created on: 19 mar 2026
 *      Author: j.li
 */

#include "../../Libs/sqlite/sqlite3.h"
#include "repo_usuario.h"
#include "src/shared/modelo_user.h"
#include <stdio.h>

void repo_usuario_insert(sqlite3 *db, User *u) {

	sqlite3_stmt *stmt;

    const char *sql =
        "INSERT INTO USUARIO (NOMBRE, TLF, MAIL, PW, ROL, ESTADO_CUENTA, FECHA_REG) "
        "VALUES (?, ?, ?, ?, ?, ?, ?);";

    sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);

    sqlite3_bind_text(stmt, 1, u->nombre, -1, SQLITE_STATIC);
    if (u->tlf[0] == '\0'){
    	sqlite3_bind_null(stmt, 2);
    }else{
    	sqlite3_bind_text(stmt, 2, u->tlf, -1, SQLITE_STATIC);
    }
    sqlite3_bind_text(stmt, 3, u->mail, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 4, u->pw, -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 5, u->rol);
    sqlite3_bind_int(stmt, 6, u->estado_cuenta);
    sqlite3_bind_text(stmt, 7, u->fecha_reg, -1, SQLITE_STATIC);

    int rc = sqlite3_step(stmt);
        if (rc != SQLITE_DONE) {
            printf("Error SQL en insert: %s\n", sqlite3_errmsg(db));
        }

    sqlite3_finalize(stmt);
}
