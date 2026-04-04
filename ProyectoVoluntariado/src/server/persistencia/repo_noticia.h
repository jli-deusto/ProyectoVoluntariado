/*
 * repo_noticia.h
 *
 *  Created on: 27 mar 2026
 *      Author: j.li
 */

#ifndef PERSISTENCIA_REPO_NOTICIA_H_
#define PERSISTENCIA_REPO_NOTICIA_H_

#include "Libs/sqlite/sqlite3.h"
#include "shared/modelo_noticia.h"

void repo_noticia_insert(sqlite3 *db, Noticia *n);
int repo_noticia_get(sqlite3 *db, int id, Noticia *n);
int repo_noticia_update(sqlite3 *db, Noticia *n);
int repo_noticia_delete(sqlite3 *db, int id);


#endif /* PERSISTENCIA_REPO_NOTICIA_H_ */
