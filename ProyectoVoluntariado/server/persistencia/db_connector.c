/*
 * db_connector.c
 *
 *  Created on: 20 mar 2026
 *      Author: danielavalentina.s
 */


#include "../../Libs/sqlite/sqlite3.h"
#include <stdlib.h>
#include <stdio.h>
sqlite3 *db;
sqlite3_stmt * stmt;

void ejecutar_sqlExec(sqlite3 *db, const char *sql) {
    char *error = NULL;
    int rc = sqlite3_exec(db, sql, NULL, NULL, &error);
    if (rc != SQLITE_OK) {
        printf("Error SQL: %s\n", error);
        sqlite3_free(error);
    } }

void open_connection() {
	if (sqlite3_open("server_data.db", &db) == SQLITE_OK) {

		ejecutar_sqlExec(db, "CREATE TABLE IF NOT EXISTS USUARIO ("
			    "ID INTEGER PRIMARY KEY AUTOINCREMENT,"
			    "NOMBRE TEXT NOT NULL UNIQUE,"
			    "TLF TEXT,"
			    "MAIL TEXT NOT NULL UNIQUE,"
			    "PW TEXT NOT NULL,"
			    "ROL INTEGER NOT NULL,"
			    "ESTADO_CUENTA INTEGER NOT NULL,"
			    "FECHA_REG TEXT NOT NULL"
			    ")");

		ejecutar_sqlExec(db, "CREATE TABLE IF NOT EXISTS ACTIVIDAD ("
			    "ID INTEGER PRIMARY KEY AUTOINCREMENT,"
			    "TITULO TEXT NOT NULL UNIQUE,"
			    "MAX_PLAZAS INT NOT NULL,"
			    "UBICACION TEXT NOT NULL,"
			    "DESCRIPCION TEXT,"
			    "HORA_INIT TEXT NOT NULL,"
				"HORA_FIN TEXT NOT NULL,"
				"TIPO TEXT NOT NULL,"
				"FECHA TEXT NOT NULL"
			    ")");
		ejecutar_sqlExec(db, "CREATE TABLE IF NOT EXISTS NOTICIA ("
					    "ID INTEGER PRIMARY KEY AUTOINCREMENT,"
					    "TITULO TEXT NOT NULL UNIQUE,"
					    "DESCRIPCION TEXT,"
						"FECHA TEXT NOT NULL,"
                		"ID_USUARIO INTEGER NOT NULL,"
						"FOREIGN KEY (ID_USUARIO) REFERENCES USUARIO(ID)"
					    ")");

		ejecutar_sqlExec(db, "CREATE TABLE IF NOT EXISTS RESERVA ("
							    "ID INTEGER PRIMARY KEY AUTOINCREMENT,"
								"ESTADO_RESERVA INTEGER NOT NULL,"
								"FECHA TEXT NOT NULL,"
								"ID_USUARIO INTEGER NOT NULL,"
								"ID_ACTIVIDAD INTEGER NOT NULL,"
								"FOREIGN KEY (ID_USUARIO) REFERENCES USUARIO(ID),"
								"FOREIGN KEY (ID_ACTIVIDAD) REFERENCES ACTIVIDAD(ID)"

							    ")");

	}
}



