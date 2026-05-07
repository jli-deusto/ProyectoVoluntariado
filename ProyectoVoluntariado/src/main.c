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

    //int opcion;
    main_server(); //carga de datos
    logger_init();
    while(1){
    	bienvenida(); // Pagina inicial; datos admin
    }

    //inicio_sesion(); // inicio sesion admin

    if (db != NULL) {
    	sqlite3_close(db);
    }

    return 0;

//    printf("1. Ejecutar modo ADMIN\n");
//    printf("2. Ejecutar modo SERVER\n");
//    printf("Seleccione una opción: ");
//	fflush(stdout);
//    scanf("%d", &opcion);
//
//    if (opcion == 1) {
//        return main_admin();
//    } else if (opcion == 2) {
//        return main_server();
//    } else {
//        printf("Opción no válida.\n");
//        return 1;
//    }
}

//prueba
