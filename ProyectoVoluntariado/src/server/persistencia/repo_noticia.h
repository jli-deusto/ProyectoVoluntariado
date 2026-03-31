/*
 * repo_noticia.h
 *
 *  Created on: 27 mar 2026
 *      Author: j.li
 */

#ifndef PERSISTENCIA_REPO_NOTICIA_H_
#define PERSISTENCIA_REPO_NOTICIA_H_

#include "../../Libs/sqlite/sqlite3.h"
#include "src/shared/modelo_noticia.h"

void repo_noticia_insert(sqlite3 *db, Noticia *n);

#endif /* PERSISTENCIA_REPO_NOTICIA_H_ */
