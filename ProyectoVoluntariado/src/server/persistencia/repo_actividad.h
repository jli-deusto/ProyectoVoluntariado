/*
 * repo_actividad.h
 *
 *  Created on: 27 mar 2026
 *      Author: j.li
 */

#ifndef PERSISTENCIA_REPO_ACTIVIDAD_H_
#define PERSISTENCIA_REPO_ACTIVIDAD_H_

#include "../../Libs/sqlite/sqlite3.h"
#include "shared/modelo_actividad.h"

int repo_actividad_insert(sqlite3 *db, Actividad *a);
int repo_actividad_update(sqlite3 *db, Actividad *a);
int repo_actividad_delete(sqlite3 *db, int id);
int repo_actividad_get(sqlite3 *db, int id, Actividad *a);

#endif /* PERSISTENCIA_REPO_ACTIVIDAD_H_ */
