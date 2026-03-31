/*
 * repo_reserva.h
 *
 *  Created on: 27 mar 2026
 *      Author: j.li
 */

#ifndef PERSISTENCIA_REPO_RESERVA_H_
#define PERSISTENCIA_REPO_RESERVA_H_

#include "shared/modelo_reserva.h"
#include "../../Libs/sqlite/sqlite3.h"

void repo_reserva_insert(sqlite3 *db, Reserva *r);

#endif /* PERSISTENCIA_REPO_RESERVA_H_ */
