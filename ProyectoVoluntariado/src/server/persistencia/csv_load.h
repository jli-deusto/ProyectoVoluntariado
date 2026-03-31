/*
 * csv_load.h
 *
 *  Created on: 27 mar 2026
 *      Author: j.li
 */

#ifndef PERSISTENCIA_CSV_LOAD_H_
#define PERSISTENCIA_CSV_LOAD_H_

#include "../../Libs/sqlite/sqlite3.h"

void cargar_usuarios_csv(sqlite3 *db, const char *ruta);
void cargar_actividades_csv(sqlite3 *db, const char *ruta);
void cargar_reservas_csv(sqlite3 *db, const char *ruta);
void cargar_noticias_csv(sqlite3 *db, const char *ruta);

#endif /* PERSISTENCIA_CSV_LOAD_H_ */
