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
#include "shared/modelo_user.h"
#include "shared/modelo_actividad.h"
#include "shared/modelo_noticia.h"
#include "UI/logIn.h"
#include "UI/UserMng.h"
#include "UI/ActMng.h"
#include "UI/InformesMng.h"
#include "UI/NewsMng.h"
#include "admin/config/config_sistema.h"
#include "server/persistencia/db_connector.h"
#include "server/persistencia/db_init.h"
#include "server/persistencia/csv_load.h"
#include "Libs/sqlite/sqlite3.h"

extern sqlite3 *db;

static ConfigAdmin config;

int cerrar_sesion_admin = 0;



void limpiar_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
    }
}

int contar_columnas(const char *linea) {
    int count = 1;
    for (int i = 0; linea[i] != '\0'; i++) {
        if (linea[i] == ';' || linea[i] == ',')  // soporta ambos
            count++;
    }
    return count;
}

void ejecutar_importacion_csv(const char *ruta, int columnas_esperadas, int tipo) {

    printf("\n--- VISTA PREVIA Y VALIDACIÓN (%s) ---\n", ruta);

    FILE *f = fopen(ruta, "r");
    if (!f) {
        printf("[ERROR] No se pudo abrir %s\n", ruta);
        return;
    }

    char linea[1024];
    int fila = 0;

    if (!fgets(linea, sizeof(linea), f)) {
        printf("[ERROR] CSV vacío.\n");
        fclose(f);
        return;
    }

    int columnas_header = contar_columnas(linea);
    printf("Columnas detectadas: %d (esperadas: %d)\n",
           columnas_header, columnas_esperadas);

    while (fgets(linea, sizeof(linea), f)) {
        fila++;
        linea[strcspn(linea, "\r\n")] = 0;

        int columnas = contar_columnas(linea);
        printf("[FILA %d] (%d columnas) %s\n", fila, columnas, linea);

        if (columnas != columnas_esperadas)
            printf("  -> ADVERTENCIA: columnas incorrectas.\n");
    }
    fclose(f);

    char confirmacion;
    printf("\n¿Importar estos datos? (s/n): ");
    fflush(stdout);
    scanf(" %c", &confirmacion);
    limpiar_buffer();

    if (confirmacion != 's' && confirmacion != 'S') {
        printf("Operación cancelada.\n");
        return;
    }

    if (db == NULL) open_connection();

    sqlite3_exec(db, "BEGIN TRANSACTION;", NULL, NULL, NULL);

    if (tipo == 1) cargar_usuarios_csv(db, ruta);
    else if (tipo == 2) cargar_actividades_csv(db, ruta);
    else if (tipo == 3) cargar_noticias_csv(db, ruta);
    else if (tipo == 4) cargar_reservas_csv(db, ruta);

    sqlite3_exec(db, "COMMIT;", NULL, NULL, NULL);

    printf("\n>>> Importación completada correctamente.\n");
}

void importar_usuarios() {
    fflush(stdout);

    ejecutar_importacion_csv(config.csv_usuarios, 7, 1);
}
void importar_actividades()  {
	fflush(stdout);
	ejecutar_importacion_csv(config.csv_actividades, 8, 2); }
void importar_noticias()     {
	fflush(stdout);
 	 ejecutar_importacion_csv(config.csv_noticias, 4, 3); }
void importar_reservas()     {
	fflush(stdout);
	ejecutar_importacion_csv(config.csv_reservas, 4, 4); }

void ejecutar_flujo_importacion() {

    char header[] = "Importación de Datos CSV";

    char *opciones[] = {
        "Importar Usuarios",
        "Importar Actividades",
        "Importar Noticias",
        "Importar Reservas",
        "Volver"
    };

    MenuCallback funciones[] = {
        importar_usuarios,
        importar_actividades,
        importar_noticias,
        importar_reservas,
        NULL
    };

    int size = sizeof(opciones) / sizeof(opciones[0]);
    MostrarMenu(header, opciones, funciones, size, size);
}


void editar_ruta_db() {
    char buffer[MAX_RUTA];
    printf("Nueva ruta DB: ");
    fflush(stdout);
    fgets(buffer, sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\n")] = 0;
    strcpy(config.db_path, buffer);
}

void editar_ruta_logs() {
    char buffer[MAX_RUTA];
    printf("Nueva ruta LOGS: ");
    fflush(stdout);
    fgets(buffer, sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\n")] = 0;
    strcpy(config.log_path, buffer);
}

void editar_limite_usuarios() {
    char buffer[32];
    printf("Nuevo límite de usuarios: ");
    fflush(stdout);
    fgets(buffer, sizeof(buffer), stdin);
    config.max_usuarios = atoi(buffer);
}

void editar_limite_actividades() {
    char buffer[32];
    printf("Nuevo límite de actividades: ");
    fflush(stdout);
    fgets(buffer, sizeof(buffer), stdin);
    config.max_actividades = atoi(buffer);
}

void guardar_configuracion_sistema() {

    FILE *f = fopen("data/admin.conf", "w");
    if (!f) {
        printf("Error al guardar admin.conf\n");
        fflush(stdout);
        return;
    }

    fprintf(f, "DB_PATH=%s\n", config.db_path);
    fprintf(f, "LOG_PATH=%s\n", config.log_path);
    fprintf(f, "CSV_USUARIOS=%s\n", config.csv_usuarios);
    fprintf(f, "CSV_ACTIVIDADES=%s\n", config.csv_actividades);
    fprintf(f, "CSV_NOTICIAS=%s\n", config.csv_noticias);
    fprintf(f, "CSV_RESERVAS=%s\n", config.csv_reservas);
    fprintf(f, "ADMIN_USER=%s\n", config.admin_user);
    fprintf(f, "ADMIN_PASS=%s\n", config.admin_pass);
    fprintf(f, "MAX_USUARIOS=%d\n", config.max_usuarios);
    fprintf(f, "MAX_ACTIVIDADES=%d\n", config.max_actividades);
    fflush(stdout);
    fclose(f);

    printf("\nConfiguración guardada correctamente.\n");
}



void menu_configuracion_sistema() {

    char header[] = "Configuración del Sistema";

    char *opciones[] = {
        "Ver configuración actual",
        "Modificar ruta DB",
        "Modificar ruta LOGS",
        "Modificar límite de usuarios",
        "Modificar límite de actividades",
        "Guardar cambios",
        "Volver"
    };

    MenuCallback funciones[] = {
        mostrar_configuracion_sistema,
        editar_ruta_db,
        editar_ruta_logs,
        editar_limite_usuarios,
        editar_limite_actividades,
        guardar_configuracion_sistema,
        NULL
    };

    int size = sizeof(opciones) / sizeof(opciones[0]);

    MostrarMenu(header, opciones, funciones, size, size);
}
void menu_admin() {

    if (!cargar_configuracion("data/admin.conf", &config)) {
        printf("No se pudo leer admin.conf\n");
        return;
    }

    fflush(stdout);
    char header[] = "B2H - ADMINISTRADOR LOCAL";

    char *opciones[] = {
        "Seleccionar archivo CSV / Importar",
        "Gestionar Usuarios",
        "Gestionar Actividades",
        "Gestionar Noticias",
        "Informes",
        "Configuración del Sistema",
        "Salir"
    };

    MenuCallback funciones[] = {
        ejecutar_flujo_importacion,
        gestion_usuarios,
        gestion_actividades,
        gestion_noticias,
        gestion_informes,
        menu_configuracion_sistema,
        salir_admin
    };

    int num_opciones = sizeof(opciones) / sizeof(opciones[0]);
    int num_funciones = sizeof(funciones) / sizeof(funciones[0]);

    cerrar_sesion_admin = 0;
    MostrarMenu(header, opciones, funciones, num_opciones, num_funciones);
}

static int listarUsuarios_wrapper(User *u) {
    (void)u;
    listarUsuarios();
    return 1;
}

void gestion_usuarios() {

    char header[] = "Gestión de Usuarios";

    const char *opciones[] = {
    	"Listar usuarios",
        "Crear usuario",
        "Modificar usuario",
        "Eliminar usuario",
        "Salir"
    };
    User usuario;
    MenuCallbackUser funciones[] = {
    	listarUsuarios_wrapper,
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
    char header[] = "Gestión de Noticias";

    const char *opciones[] = {
        "Crear noticia",
        "Modificar noticia",
        "Eliminar noticia",
        "Salir"
    };

    //Noticia noticia;

    MenuCallback funciones[] = {
        (MenuCallback)crearNoticia,
        (MenuCallback)modificarNoticia,
        (MenuCallback)eliminarNoticia,
        NULL
    };

    int num_opciones = sizeof(opciones) / sizeof(opciones[0]);
    int num_funciones = sizeof(funciones) / sizeof(funciones[0]);


    MostrarMenu(header, (char **)opciones, funciones, num_opciones, num_funciones);
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

    printf("\n===== CONFIGURACIÓN DEL SISTEMA =====\n");
    printf("DB_PATH: %s\n", config.db_path);
    printf("LOG_PATH: %s\n", config.log_path);
    printf("CSV_USUARIOS: %s\n", config.csv_usuarios);
    printf("CSV_ACTIVIDADES: %s\n", config.csv_actividades);
    printf("CSV_NOTICIAS: %s\n", config.csv_noticias);
    printf("CSV_RESERVAS: %s\n", config.csv_reservas);
    printf("MAX_USUARIOS: %d\n", config.max_usuarios);
    printf("MAX_ACTIVIDADES: %d\n", config.max_actividades);
    printf("=====================================\n");
}



void salir_admin() {
    char buffer[8];

    printf("\n¿Deseas cerrar sesión? (s/n): ");
    fflush(stdout);

    if (!fgets(buffer, sizeof(buffer), stdin)) {
        printf("Entrada inválida.\n");
        return;
    }

    if (buffer[0] == 's' || buffer[0] == 'S') {
        printf("\nCerrando sesión...\n");
        cerrar_sesion_admin = 1;
    } else {
        printf("\nOperación cancelada. Volviendo al menú administrador...\n");
        cerrar_sesion_admin = 0;
    }
}



