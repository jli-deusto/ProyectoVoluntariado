/*
 * repo_usuario.h
 *
 *  Created on: 27 mar 2026
 *      Author: j.li
 */

#ifndef PERSISTENCIA_REPO_USUARIO_H_
#define PERSISTENCIA_REPO_USUARIO_H_

#include "../../Libs/sqlite/sqlite3.h"
#include "../modelo/modelo_user.h"

void repo_usuario_insert(sqlite3 *db, Usuario *u);

#endif /* PERSISTENCIA_REPO_USUARIO_H_ */
