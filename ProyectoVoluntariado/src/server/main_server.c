/*
 * main_server.c
 *
 *  Created on: 19 mar 2026
 *      Author: j.li
 */

#include "persistencia/db_connector.h"
#include "persistencia/db_init.h"
#include "comms/coms_servidor.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int puerto_conf = 8080;

static void leer_config(const char *ruta) {
    FILE *f = fopen(ruta, "r");
    if (!f) return;
    char linea[256];
    while (fgets(linea, sizeof(linea), f)) {
        char clave[64], valor[128];
        if (sscanf(linea, "%63[^=]=%127s", clave, valor) == 2) {
            if (strcmp(clave, "PORT") == 0)
                puerto_conf = atoi(valor);
        }
    }
    fclose(f);
}

void debug_contadores(sqlite3 *db);

int main_server() {

	printf("Entrando en main_server()\n");
	fflush(stdout);

    leer_config("./data/server.conf");

    open_connection();  // crea tablas y abre BD

    printf("open_connection() ejecutada\n");
    fflush(stdout);

    if (db == NULL) {
        printf("ERROR: db es NULL\n");
        fflush(stdout);
    }

    int init = db_is_initialized(db);
    printf("db_is_initialized devuelve: %d\n", init);
    fflush(stdout);


    if (!db_is_initialized(db)) {
    	printf("Cargando datos....\n");
        db_cargar_datos_iniciales(db);
        printf("Carga de base de datos completado.\n");
    } else {
        printf("Base de datos ya cargada anteriormente.\n");
    }

    debug_contadores(db);


    iniciar_servidor();

//    endSession();

    return 0;
}

void debug_contadores(sqlite3 *db) {
    const char *tablas[] = {"USUARIO", "ACTIVIDAD", "RESERVA", "NOTICIA"};
    for (int i = 0; i < 4; i++) {
        char sql[128];
        sprintf(sql, "SELECT COUNT(*) FROM %s;", tablas[i]);

        sqlite3_stmt *stmt;
        sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
        sqlite3_step(stmt);
        int count = sqlite3_column_int(stmt, 0);
        sqlite3_finalize(stmt);

        printf("%s tiene %d filas\n", tablas[i], count);
    }
}

//void endSession() {
//	sqlite3_close(db);
//}

