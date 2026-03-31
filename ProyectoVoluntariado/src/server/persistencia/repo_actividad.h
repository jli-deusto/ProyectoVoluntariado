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

void repo_actividad_insert(sqlite3 *db, Actividad *a);

#endif /* PERSISTENCIA_REPO_ACTIVIDAD_H_ */
