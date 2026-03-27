/*
 * db_connector.h
 *
 *  Created on: 20 mar 2026
 *      Author: danielavalentina.s
 */

#ifndef PERSISTENCIA_DB_CONNECTOR_H_
#define PERSISTENCIA_DB_CONNECTOR_H_

#include "../../Libs/sqlite/sqlite3.h"
extern sqlite3 *db;

void ejecutar_sqlExec(sqlite3 *db, const char *sql);
void open_connection();
void prepare_Statements();
void filling_params();
void executeStmt();
void readSelectResults();
void endConsult();
void endSession();


#endif /* PERSISTENCIA_DB_CONNECTOR_H_ */
