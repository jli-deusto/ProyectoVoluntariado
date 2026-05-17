/*
 * main.c
 *
 *  Created on: 27 mar 2026
 *      Author: j.li
 */


#include <stdio.h>
#include <unistd.h>
#include "UI/logIn.h"
#include "server/persistencia/db_connector.h"
#include "server/logs/logger.h"
#include "Libs/sqlite/sqlite3.h"

int main_server();
int main() {
    char cwd[256];
    getcwd(cwd, sizeof(cwd));
    printf("Directorio de trabajo: %s\n", cwd);

    printf("1. Modo ADMINISTRADOR\n");
    printf("2. Modo SERVIDOR\n");
    printf("Seleccione una opcion: ");
    fflush(stdout);

    int opcion;
    scanf("%d", &opcion);
    while(getchar() != '\n');

    if (opcion == 2) {
        main_server();
    } else {
        logger_init();
        while(1) {
            bienvenida();
        }
    }

    if (db != NULL) {
        sqlite3_close(db);
    }
    return 0;
}
//prueba
