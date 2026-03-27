/*
 * db_init.h
 *
 *  Created on: 27 mar 2026
 *      Author: j.li
 */

#ifndef PERSISTENCIA_DB_INIT_H_
#define PERSISTENCIA_DB_INIT_H_


#include "../../Libs/sqlite/sqlite3.h"

int db_is_initialized(sqlite3 * db);
void db_cargar_datos_iniciales(sqlite3 *db);


#endif /* PERSISTENCIA_DB_INIT_H_ */
