/*
 * menu.c
 *
 *  Created on: 22 mar 2026
 *      Author: danielavalentina.s
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "menu.h"
#include "shared/constantes.h"
#include  "UI/UserMng.h"
#include "admin/config/config_sistema.h"
#include "server/persistencia/db_connector.h"
#include "server/persistencia/db_init.h"
#include "server/persistencia/csv_load.h"

extern sqlite3 *db;
void gestion_usuarios();
void gestion_actividades();
void gestion_noticias();
void gestion_informes();
void mostrar_configuracion_sistema();

void limpiar_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void ejecutar_flujo_importacion() {

    int sel = 0;
    char *ruta = NULL;
    int columnas_esperadas = 0;
    char confirmacion;

    if (db == NULL) {
        open_connection();
    }

    printf("\n========================================\n");
    printf("  SELECCIONAR ARCHIVO CSV PARA IMPORTAR \n");
    printf("========================================\n");
    printf("1. Usuarios (7 cols)\n");
    printf("2. Actividades (8 cols)\n");
    printf("3. Noticias (4 cols)\n");
    printf("4. Reservas (4 cols)\n");
    printf("Seleccion: ");
    fflush(stdout);

    if (scanf("%d", &sel) != 1) {
        limpiar_buffer();
        return;
    }

    if (sel == 1) { ruta = "data/CSV/usuarios.csv";    columnas_esperadas = 7; }
    else if (sel == 2) { ruta = "data/CSV/actividades.csv"; columnas_esperadas = 8; }
    else if (sel == 3) { ruta = "data/CSV/noticias.csv";    columnas_esperadas = 4; }
    else if (sel == 4) { ruta = "data/CSV/reservas.csv";    columnas_esperadas = 4; }
    else { printf("\nOpcion no valida.\n"); return; }

    printf("\n--- VISTA PREVIA Y VALIDACION ---\n");
    FILE *f = fopen(ruta, "r");
    if (!f) {
        printf("[ERROR] No se pudo abrir %s. Revisa la carpeta data/CSV/\n", ruta);
        return;
    }

    char linea[1024];
    int fila = 0;
    fgets(linea, sizeof(linea), f);

    while (fgets(linea, sizeof(linea), f)) {
        fila++;
        linea[strcspn(linea, "\r\n")] = 0;
        printf("[FILA %d] OK: %s\n", fila, linea);
    }
    fclose(f);

    printf("\n--- CONFIRMAR IMPORTACION ---\n");
    printf("Desea importar estos datos a la Base de Datos SQL? (s/n): ");
    fflush(stdout);

    scanf(" %c", &confirmacion);
    limpiar_buffer();

    if (confirmacion == 's' || confirmacion == 'S') {
        printf("\nProcesando carga en la base de datos...\n");
        sqlite3_exec(db, "BEGIN TRANSACTION;", NULL, NULL, NULL);

        if (sel == 1) cargar_usuarios_csv(db, ruta);
        else if (sel == 2) cargar_actividades_csv(db, ruta);
        else if (sel == 3) cargar_noticias_csv(db, ruta);
        else if (sel == 4) cargar_reservas_csv(db, ruta);

        sqlite3_exec(db, "COMMIT;", NULL, NULL, NULL);
        printf("\n>>> EXITO: Los datos han sido registrados/actualizados en SQL.\n");
    } else {
        printf("\n>>> OPERACION CANCELADA POR EL USUARIO.\n");
    }
}



void menu_admin() {
    int opcion = -1;
    char buffer[opt];

    do {
    	printf("\n================================\n");
    	printf("    B2H - ADMINISTRADOR LOCAL   \n");
    	printf("================================\n");
    	printf("1. Seleccionar archivo CSV / Importar\n");
    	printf("2. Gestionar Usuarios\n");
        printf("3. Gestionar Actividades\n");
    	printf("4. Gestionar Noticias\n");
    	printf("5. Informes\n");
        printf("6. Configuración del Sistema\n");
    	printf("7. Salir\n");
    	printf("Selecciona una opcion: ");
    	fflush(stdout);

    	if (fgets(buffer, sizeof(buffer), stdin)) {
    		if (sscanf(buffer, "%d", &opcion) != 1) {
    			opcion = -1;
    		}
    	 }

        switch(opcion) {
            case 1:
            	ejecutar_flujo_importacion();
            	break;
            case 2:
            	gestion_usuarios();
				break;
            case 3:
                gestion_actividades();
                break;
            case 4:
            	gestion_noticias();
            	break;
            case 5:
            	gestion_informes();
            	break;
            case 6:
            	mostrar_configuracion_sistema();
            	break;
            case 7:
            	printf("Cerrando sesion...\n");
            	break;
            default:
                printf("Opcion no valida, intentalo de nuevo\n");
        }
    } while (opcion != 7);
}

void gestion_usuarios() {
	 int opcion = -1;
	    char buffer[opt];

	    do {
	        printf("\n================================\n"); // puts lo mismo que printf pero sin formateado
	        printf("        Gestión de Usuarios   \n");
	        printf("================================\n");
	        printf("1. Crear usuario\n");
	        printf("2. Modificar usuario\n");
	        printf("3. Eliminar Usuario\n");
	        printf("4. Salir\n");
	        printf("Selecciona una opcion: ");
	        fflush(stdout); // desatasca el fichero de salida - esto indica que la lectura antes de imprimir ir over

	        fgets(buffer, sizeof(buffer), stdin);
	        if (sscanf(buffer, "%d", &opcion) != 1) {
	            opcion = -1; // valor inválido
	        }
	        fflush(stdout);

	        switch(opcion) {
	            case 1:
	                crearUsuario(); break;
	            case 2:
	                puts("tbd"); break;
	            case 3:
	            	puts("tbd"); break;
	            case 4:
	                printf("Cerrando sesion...\n"); break;
	            default:
	                printf("Opcion no valida, intentalo de nuevo\n");// esto se imprime incluso cuando no deberia
	        }
	    } while (opcion != 4);
};

void gestion_actividades(){
	// crear actividad
	// modificar actividad
	// eliminar actividad
};
void gestion_noticias(){
	// crear actividad
	// modificar actividad
	// eliminar actividad
};

void gestion_informes() {
    printf("\n===== MÓDULO DE INFORMES =====\n");
    //RELLENAR
    printf("==============================\n");
}

void mostrar_configuracion_sistema() {
    ConfigAdmin config;
    if (cargar_configuracion("data/admin.conf", &config)) {
        printf("\n===== CONFIGURACIÓN DEL SISTEMA =====\n");
        printf("Base de Datos: %s\n", config.db_path);
        printf("Archivo Logs:  %s\n", config.log_path);
        printf("Límite Usuarios: %d\n", config.max_usuarios);
        printf("Límite Actividades: %d\n", config.max_actividades);
        printf("=====================================\n");
    } else {
        printf("Error: No se pudo leer admin.conf\n");
    }
}

