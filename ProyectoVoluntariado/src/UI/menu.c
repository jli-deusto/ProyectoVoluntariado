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
#include "gestionMenu.h"
#include "shared/constantes.h"
#include "UI/UserMng.h"
#include "UI/ActMng.h"
#include "UI/InformesMng.h"
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
    while ((c = getchar()) != '\n' && c != EOF) {
    }
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

	if (sel == 1) {
		ruta = "data/CSV/usuarios.csv";
		columnas_esperadas = 7;
	} else if (sel == 2) {
		ruta = "data/CSV/actividades.csv";
		columnas_esperadas = 8;
	} else if (sel == 3) {
		ruta = "data/CSV/noticias.csv";
		columnas_esperadas = 4;
	} else if (sel == 4) {
		ruta = "data/CSV/reservas.csv";
		columnas_esperadas = 4;
	} else {
		printf("\nOpcion no valida.\n");
		return;
	}

	printf("\n--- VISTA PREVIA Y VALIDACION ---\n");
	FILE *f = fopen(ruta, "r");
	if (!f) {
		printf("[ERROR] No se pudo abrir %s. Revisa la carpeta data/CSV/\n",
				ruta);
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

		if (sel == 1)
			cargar_usuarios_csv(db, ruta);
		else if (sel == 2)
			cargar_actividades_csv(db, ruta);
		else if (sel == 3)
			cargar_noticias_csv(db, ruta);
		else if (sel == 4)
			cargar_reservas_csv(db, ruta);

		sqlite3_exec(db, "COMMIT;", NULL, NULL, NULL);
		printf(
				"\n>>> EXITO: Los datos han sido registrados/actualizados en SQL.\n");
	} else {
		printf("\n>>> OPERACION CANCELADA POR EL USUARIO.\n");
	}
}


void menu_admin() {
	fflush(stdout);
	char header[] = "B2H - ADMINISTRADOR LOCAL";

	char *opciones[] = { "Seleccionar archivo CSV / Importar",
			"Gestionar Usuarios", "Gestionar Actividades", "Gestionar Noticias",
			"Informes", "Configuración del Sistema", "Salir" };
		MenuCallback funciones[] = {
	    ejecutar_flujo_importacion,   // 1
	    gestion_usuarios,             // 2
	    gestion_actividades,          // 3
	    gestion_noticias,             // 4
	    gestion_informes,             // 5
	    mostrar_configuracion_sistema,// 6
	    NULL                          // 7 -> Salir (no es función)
	};
	int num_opciones = sizeof(opciones) / sizeof(opciones[0]);
	int num_funciones = sizeof(funciones) / sizeof(funciones[0]);

	MostrarMenu(header, opciones, funciones, num_opciones, num_funciones);
}

void gestion_usuarios() {

    char header[] = "Gestión de Usuarios";

    const char *opciones[] = {
        "Crear usuario",
        "Modificar usuario",
        "Eliminar usuario",
        "Salir"
    };
    User usuario;
    MenuCallbackUser funciones[] = {
        crearUsuario,   // 1
        modificarUsuario,           // 2 -> TBD
        eliminarUsuario,           // 3 -> TBD
        NULL            // 4 -> Salir
    };

    int num_opciones = sizeof(opciones) / sizeof(opciones[0]);
    int num_funciones = sizeof(funciones) / sizeof(funciones[0]);

    MostrarMenuUsers(header, (char **)opciones, funciones, num_opciones, num_funciones, &usuario);
}


void gestion_actividades() {

	char header[] = "Gestión de Actividades";

	const char *opciones[] = {
	        "Crear Actividad",
	        "Modificar Actividad",
	        "Eliminar Actividad",
	        "Salir"
	    };

	Actividad actividad;

	MenuCallbackActividad funciones[] = {
			crearActividad,   // 1
			modificarActividad, // 2
			eliminarActividad,  // 3
			NULL            // 4 -> Salir
	};

	int num_opciones = sizeof(opciones) / sizeof(opciones[0]);
	int num_funciones = sizeof(funciones) / sizeof(funciones[0]);

	MostrarMenuActividades(header, (char **)opciones, funciones, num_opciones, num_funciones, &actividad);

}
;
void gestion_noticias() {
	// crear actividad
	// modificar actividad
	// eliminar actividad
}
;

void gestion_informes() {

    char header[] = "Módulo de Informes";

    const char *opciones[] = {
        "Informes para Administradores",
        "Salir"
    };

    MenuCallback funciones[] = {
        informes_administradores,
        NULL
    };

    int num_opciones = sizeof(opciones) / sizeof(opciones[0]);
    int num_funciones = sizeof(funciones) / sizeof(funciones[0]);

    MostrarMenu(header, (char **)opciones, funciones, num_opciones, num_funciones);
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

