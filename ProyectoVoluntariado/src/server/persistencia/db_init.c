/*
 * db_init.c
 *
 *  Created on: 27 mar 2026
 *      Author: j.li
 */

#include "db_init.h"
#include "csv_load.h"
#include <stdio.h>

int db_is_initialized(sqlite3 *db) {
    sqlite3_stmt *stmt; //puntero a estructura interna
    const char *sql = "SELECT COUNT(*) FROM USUARIO;";

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK)
        return 0;

    int count = 0;
    if (sqlite3_step(stmt) == SQLITE_ROW)
        count = sqlite3_column_int(stmt, 0);

    sqlite3_finalize(stmt);
    return count > 0;
}

void db_cargar_datos_iniciales(sqlite3 *db) {
    printf("Cargando datos iniciales desde CSV...\n");

    cargar_usuarios_csv(db, "data/CSV/usuarios.csv");
    cargar_actividades_csv(db, "data/CSV/actividades.csv");
    cargar_reservas_csv(db, "data/CSV/reservas.csv");
    cargar_noticias_csv(db, "data/CSV/noticias.csv");

    printf("Carga inicial completada.\n");
}
