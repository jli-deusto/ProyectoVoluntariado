/*
 * InformesMng.c
 *
 *  Created on: 3 abr 2026
 *      Author: j.li
 */

#include <stdio.h>
#include "Libs/sqlite/sqlite3.h"
#include "InformesMng.h"
#include "gestionMenu.h"

extern sqlite3 *db;

void informes_administradores() {

    char header[] = "Informes para Administradores";

    const char *opciones[] = {
        "Reporte de ocupación de actividades",
        "Estadísticas del centro",
        "Participación por voluntariado",
        "Registro de incidencias medioambientales",
        "Logs del sistema",
        "Salir"
    };

    MenuCallback funciones[] = {
        reporte_ocupacion,
        estadisticas_centro,
        participacion_voluntariado,
        registro_incidencias,
        mostrar_logs,
        NULL
    };

    int num_opciones = sizeof(opciones) / sizeof(opciones[0]);
    int num_funciones = sizeof(funciones) / sizeof(funciones[0]);

    MostrarMenu(header, (char **)opciones, funciones, num_opciones, num_funciones);
}


void reporte_ocupacion() {

    printf("\n===== REPORTE DE OCUPACIÓN DE ACTIVIDADES =====\n");

    const char *sql =
        "SELECT a.ID, a.TITULO, a.MAX_PLAZAS, "
        "(SELECT COUNT(*) FROM RESERVA r WHERE r.ID_ACTIVIDAD = a.ID AND r.ESTADO_RESERVA = 1) AS OCUPADAS "
        "FROM ACTIVIDAD a;";

    sqlite3_stmt *stmt;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        printf("Error al preparar consulta: %s\n", sqlite3_errmsg(db));
        return;
    }

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        int id = sqlite3_column_int(stmt, 0);
        const unsigned char *titulo = sqlite3_column_text(stmt, 1);
        int max = sqlite3_column_int(stmt, 2);
        int ocupadas = sqlite3_column_int(stmt, 3);

        printf("\nActividad %d: %s\n", id, titulo);
        printf("Plazas totales: %d\n", max);
        printf("Ocupadas: %d\n", ocupadas);
        printf("Disponibles: %d\n", max - ocupadas);
    }

    sqlite3_finalize(stmt);
}


void estadisticas_centro() {

    printf("\n===== ESTADÍSTICAS DEL CENTRO =====\n");

    if (db == NULL) {
       printf("Error: no hay conexión con la base de datos.\n");
       return;
    }

    sqlite3_stmt *stmt;

    {
    	const char *sql = "SELECT COUNT(*) FROM USUARIO;";
    	if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK) {
    		if (sqlite3_step(stmt) == SQLITE_ROW)
    			printf("Usuarios registrados:        %d\n", sqlite3_column_int(stmt, 0));
    		sqlite3_finalize(stmt);
    	}
    }


	{
		const char *sql = "SELECT COUNT(*) FROM USUARIO WHERE ESTADO_CUENTA = 1;";
		if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK) {
			if (sqlite3_step(stmt) == SQLITE_ROW)
				printf("Usuarios activos:            %d\n", sqlite3_column_int(stmt, 0));
			sqlite3_finalize(stmt);
		}
	}


	{
		const char *sql = "SELECT COUNT(*) FROM ACTIVIDAD;";
		if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK) {
			if (sqlite3_step(stmt) == SQLITE_ROW)
				printf("Actividades en el sistema:   %d\n", sqlite3_column_int(stmt, 0));
			sqlite3_finalize(stmt);
		}
	}


	{
		const char *sql =
			"SELECT TIPO, COUNT(*) AS TOTAL "
			"FROM ACTIVIDAD "
			"GROUP BY TIPO "
			"ORDER BY TOTAL DESC;";

		if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK) {
			printf("\nActividades por tipo:\n");
			while (sqlite3_step(stmt) == SQLITE_ROW) {
				const unsigned char *tipo = sqlite3_column_text(stmt, 0);
				int total = sqlite3_column_int(stmt, 1);
				printf("  %-20s %d\n", tipo ? (const char *)tipo : "sin tipo", total);
			}

			sqlite3_finalize(stmt);
		}
	}


	{
		const char *sql = "SELECT COUNT(*) FROM RESERVA WHERE ESTADO_RESERVA = 1;";
		if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK) {
			if (sqlite3_step(stmt) == SQLITE_ROW)
				printf("\nReservas aprobadas:          %d\n", sqlite3_column_int(stmt, 0));
			sqlite3_finalize(stmt);
		}
	}


	{
		const char *sql = "SELECT COUNT(*) FROM RESERVA WHERE ESTADO_RESERVA = 0;";
		if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK) {
			if (sqlite3_step(stmt) == SQLITE_ROW)
				printf("Reservas canceladas:         %d\n", sqlite3_column_int(stmt, 0));
			sqlite3_finalize(stmt);
		}
	}


	{
		const char *sql =
			"SELECT a.TITULO, COUNT(r.ID) AS TOTAL "
			"FROM ACTIVIDAD a "
			"LEFT JOIN RESERVA r ON a.ID = r.ID_ACTIVIDAD AND r.ESTADO_RESERVA = 1 "
			"GROUP BY a.ID "
			"ORDER BY TOTAL DESC "
			"LIMIT 1;";

		if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK) {
			if (sqlite3_step(stmt) == SQLITE_ROW) {
				const unsigned char *titulo = sqlite3_column_text(stmt, 0);
				int total = sqlite3_column_int(stmt, 1);
				printf("\nActividad más popular:       %s (%d reservas)\n",
						titulo ? (const char *)titulo : "N/A", total);
			}
			sqlite3_finalize(stmt);
		}
	}


	{
		const char *sql =
			"SELECT u.NOMBRE, COUNT(r.ID) AS PARTICIPACIONES "
			"FROM USUARIO u "
			"JOIN RESERVA r ON u.ID = r.ID_USUARIO "
			"WHERE u.ROL = '0' AND r.ESTADO_RESERVA = 1 "
			"GROUP BY u.ID "
			"ORDER BY PARTICIPACIONES DESC "
			"LIMIT 1;";

		if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK) {
			if (sqlite3_step(stmt) == SQLITE_ROW) {
				const unsigned char *nombre = sqlite3_column_text(stmt, 0);
				int partic = sqlite3_column_int(stmt, 1);
				printf("Voluntario más activo:       %s (%d actividades)\n",
						nombre ? (const char *)nombre : "N/A", partic);
			}
			sqlite3_finalize(stmt);
		}
	}


	{
		const char *sql = "SELECT COUNT(*) FROM NOTICIA;";
		if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK) {
			if (sqlite3_step(stmt) == SQLITE_ROW)
				printf("Noticias publicadas:         %d\n", sqlite3_column_int(stmt, 0));
			sqlite3_finalize(stmt);
		}
	}

        printf("=====================================\n");
}

void participacion_voluntariado() {

    printf("\n===== PARTICIPACIÓN POR VOLUNTARIADO =====\n");
    fflush(stdout);

    const char *sql =
        "SELECT u.ID, u.NOMBRE, COUNT(r.ID) AS asistencias "
        "FROM USUARIO u "
        "LEFT JOIN RESERVA r ON u.ID = r.ID_USUARIO "
        "WHERE u.ROL='0' "
        "GROUP BY u.ID;";

    sqlite3_stmt *stmt;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        printf("Error al preparar consulta: %s\n", sqlite3_errmsg(db));
        return;
    }

    int hay_filas = 0;

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        hay_filas = 1;

        int id = sqlite3_column_int(stmt, 0);
        const unsigned char *nombre = sqlite3_column_text(stmt, 1);
        int asistencias = sqlite3_column_int(stmt, 2);

        printf("\nVoluntario %d: %s\n", id, nombre);
        printf("Asistencias: %d\n", asistencias);
    }

    sqlite3_finalize(stmt);

    if (!hay_filas) {
        printf("\nNo hay voluntarios registrados o no hay reservas.\n");
    }

}


void registro_incidencias() {
    printf("\n===== REGISTRO DE INCIDENCIAS MEDIOAMBIENTALES =====\n");

    if (db == NULL) {
        printf("Error: no hay conexión con la base de datos.\n");
        return;
    }

    const char *sql =
        "SELECT i.ID, i.DESCRIPCION, i.UBICACION, i.FECHA_REPORTE, i.HORA_REPORTE, u.NOMBRE "
        "FROM INCIDENCIA i "
        "JOIN USUARIO u ON i.ID_USUARIO = u.ID "
        "ORDER BY i.FECHA_REPORTE DESC, i.HORA_REPORTE DESC;";

    sqlite3_stmt *stmt;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        printf("Error al preparar consulta: %s\n", sqlite3_errmsg(db));
        return;
    }

    int hay_filas = 0;

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        hay_filas = 1;
        int id                      = sqlite3_column_int(stmt, 0);
        const unsigned char *desc   = sqlite3_column_text(stmt, 1);
        const unsigned char *ubic   = sqlite3_column_text(stmt, 2);
        const unsigned char *fecha  = sqlite3_column_text(stmt, 3);
        const unsigned char *hora   = sqlite3_column_text(stmt, 4);
        const unsigned char *nombre = sqlite3_column_text(stmt, 5);

        printf("\nIncidencia #%d\n", id);
        printf("  Reportada por: %s\n", nombre ? (const char *)nombre : "N/A");
        printf("  Descripción:   %s\n", desc   ? (const char *)desc   : "N/A");
        printf("  Ubicación:     %s\n", ubic   ? (const char *)ubic   : "N/A");
        printf("  Fecha:         %s\n", fecha  ? (const char *)fecha  : "N/A");
        printf("  Hora:          %s\n", hora   ? (const char *)hora   : "N/A");
    }

    sqlite3_finalize(stmt);

    if (!hay_filas) {
        printf("\nNo hay incidencias registradas.\n");
    }

    printf("=====================================================\n");
}

void mostrar_logs() {

    printf("\n===== LOGS DEL SISTEMA =====\n");

    const char *logs[] = {
        "logs/server.log",
        "logs/admin.log",
        "logs/volunteer.log"
    };

    for (int i = 0; i < 3; i++) {
        printf("\n--- %s ---\n", logs[i]);

        FILE *f = fopen(logs[i], "r");
        if (!f) {
            printf("No se pudo abrir. Creando archivo...\n");
            f = fopen(logs[i], "w");
            if (!f) {
                printf("No se pudo crear.\n");
                continue;
            }
            fclose(f);
            f = fopen(logs[i], "r");
        }

        int vacio = 1;

        char linea[512];
        while (fgets(linea, sizeof(linea), f)) {
        	vacio = 0;
            printf("%s", linea);
        }

        if (vacio) {
        	printf("[Contenido vacío]\n");
        }

        fclose(f);
    }
}
