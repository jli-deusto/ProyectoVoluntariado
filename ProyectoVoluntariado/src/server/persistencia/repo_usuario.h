/*
 * repo_usuario.h
 *
 *  Created on: 27 mar 2026
 *      Author: j.li
 */

#ifndef PERSISTENCIA_REPO_USUARIO_H_
#define PERSISTENCIA_REPO_USUARIO_H_

#include "Libs/sqlite/sqlite3.h"
#include "shared/modelo_user.h"

int repo_usuario_insert(sqlite3 *db, User *u);
int repo_usuario_update(sqlite3 *db, User *u);
int repo_usuario_check(sqlite3 *db, User *u); // comprueba si el usuario esta en la base de datos
#endif /* PERSISTENCIA_REPO_USUARIO_H_ */
