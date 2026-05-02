/*
 * repo_usuario.c
 *
 *  Created on: 19 mar 2026
 *      Author: j.li
 */

#include "../../Libs/sqlite/sqlite3.h"
#include "repo_usuario.h"
#include "shared/modelo_user.h"
#include "server/seguridad/contrasena.h"
#include <stdio.h>
#include <string.h>

int repo_usuario_insert(sqlite3 *db, User *u) {

	sqlite3_stmt *stmt;
	// hashear la contrasena antes de guardar
	char hash_pw[32];
	hashear_password(u->pw, hash_pw, sizeof(hash_pw));

	const char *sql =
			"INSERT OR REPLACE INTO USUARIO (NOMBRE, TLF, MAIL, PW, ROL, ESTADO_CUENTA, FECHA_REG) "
					"VALUES (?, ?, ?, ?, ?, ?, ?);";

	sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);

	sqlite3_bind_text(stmt, 1, u->nombre, -1, SQLITE_STATIC);
	if (u->tlf[0] == '\0') {
		sqlite3_bind_null(stmt, 2);
	} else {
		sqlite3_bind_text(stmt, 2, u->tlf, -1, SQLITE_STATIC);
	}
	sqlite3_bind_text(stmt, 3, u->mail, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 4, hash_pw,  -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 5, u->rol);
	sqlite3_bind_int(stmt, 6, u->estado_cuenta);
	sqlite3_bind_text(stmt, 7, u->fecha_reg, -1, SQLITE_STATIC);

	int rc = sqlite3_step(stmt);
	if (rc != SQLITE_DONE) {
		printf("Error SQL en insert: %s\n", sqlite3_errmsg(db));
		sqlite3_finalize(stmt);
		return 0;
	}

	int changes = sqlite3_changes(db);
	if (changes == 1) {
		printf("Usuario insertado correctamente.\n");
	} else {
		printf("Advertencia: no se insertó ninguna fila.\n");
		sqlite3_finalize(stmt);
		return 0;
	}

	sqlite3_finalize(stmt);
	return 1;
}

int repo_usuario_update(sqlite3 *db, User *u) {

	sqlite3_stmt *stmt;

	const char *sql = "UPDATE USUARIO SET "
			"NOMBRE = ?, "
			"TLF = ?, "
			"MAIL = ?, "
			"PW = ?, "
			"ROL = ?, "
			"ESTADO_CUENTA = ?, "
			"FECHA_REG = ? "
			"WHERE ID = ?;";

	// Preparar statement
	if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
		printf("Error preparando UPDATE: %s\n", sqlite3_errmsg(db));
		return 0;
	}

	// Bind de parámetros
	sqlite3_bind_text(stmt, 1, u->nombre, -1, SQLITE_STATIC);

	if (u->tlf[0] == '\0')
		sqlite3_bind_null(stmt, 2);
	else
		sqlite3_bind_text(stmt, 2, u->tlf, -1, SQLITE_STATIC);

	sqlite3_bind_text(stmt, 3, u->mail, -1, SQLITE_STATIC);
	sqlite3_bind_text(stmt, 4, u->pw, -1, SQLITE_STATIC);
	sqlite3_bind_int(stmt, 5, u->rol);
	sqlite3_bind_int(stmt, 6, u->estado_cuenta);
	sqlite3_bind_text(stmt, 7, u->fecha_reg, -1, SQLITE_STATIC);

	// IMPORTANTE: el ID del usuario a actualizar
	sqlite3_bind_int(stmt, 8, u->id);

	// Ejecutar
	int rc = sqlite3_step(stmt);

	if (rc != SQLITE_DONE) {
		printf("Error SQL en update: %s\n", sqlite3_errmsg(db));
		sqlite3_finalize(stmt);
		return 0;
	}

	// Verificar filas afectadas
	int changes = sqlite3_changes(db);
	if (changes == 1) {
		printf("Usuario actualizado correctamente.\n");
	} else if (changes == 0) {
		printf(
				"Advertencia: no se actualizó ninguna fila (ID inexistente o datos idénticos).\n");
		sqlite3_finalize(stmt);
		return 0;
	}

	sqlite3_finalize(stmt);
	return 1;
}

int repo_usuario_check(sqlite3 *db, User *u) {

	sqlite3_stmt *stmt;

	const char *sql =
			"SELECT NOMBRE, MAIL FROM USUARIO WHERE NOMBRE LIKE ? AND MAIL LIKE ?";

	if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
		printf("Error preparando SELECT: %s\n", sqlite3_errmsg(db));
		return 0;
	}

	// Bind 1: nombre
	sqlite3_bind_text(stmt, 1, u->nombre, -1, SQLITE_STATIC);

	// Bind 2: mail
	sqlite3_bind_text(stmt, 2, u->mail, -1, SQLITE_STATIC);

	int rc = sqlite3_step(stmt);

	if (rc == SQLITE_ROW) {
		// Existe un usuario con ese nombre y mail
		printf("Ya existe un usuario con ese nombre y con ese correo.\n");
		sqlite3_finalize(stmt);
		return 0;
	}

	if (rc == SQLITE_DONE) {
		// No existe
		sqlite3_finalize(stmt);
		return 1;
	}

	// Error SQL
	printf("Error ejecutando SELECT: %s\n", sqlite3_errmsg(db));
	sqlite3_finalize(stmt);
	return 0;
}

int repo_usuario_get(sqlite3 *db, int id, User *u) {

	sqlite3_stmt *stmt;

	const char *sql =
			"SELECT ID, NOMBRE, TLF, MAIL, PW, ROL, ESTADO_CUENTA, FECHA_REG "
					"FROM USUARIO WHERE ID = ?;";

	if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
		printf("Error preparando SELECT: %s\n", sqlite3_errmsg(db));
		return 0;
	}

	sqlite3_bind_int(stmt, 1, id);

	int rc = sqlite3_step(stmt);

	if (rc == SQLITE_ROW) {
		u->id = sqlite3_column_int(stmt, 0);
		strcpy(u->nombre, (const char*) sqlite3_column_text(stmt, 1));
		strcpy(u->tlf, (const char*) sqlite3_column_text(stmt, 2));
		strcpy(u->mail, (const char*) sqlite3_column_text(stmt, 3));
		strcpy(u->pw, (const char*) sqlite3_column_text(stmt, 4));
		u->rol = sqlite3_column_int(stmt, 5);
		u->estado_cuenta = sqlite3_column_int(stmt, 6);
		strcpy(u->fecha_reg, (const char*) sqlite3_column_text(stmt, 7));

		sqlite3_finalize(stmt);
		return 1;
	}

	sqlite3_finalize(stmt);
	return 0;
}
