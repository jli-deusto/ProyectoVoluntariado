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

#endif /* PERSISTENCIA_REPO_USUARIO_H_ */
