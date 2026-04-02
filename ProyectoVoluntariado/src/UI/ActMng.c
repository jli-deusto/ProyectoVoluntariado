/*
 * ActMng.c
 *
 *  Created on: 2 abr 2026
 *      Author: j.li
 */

#include <stdio.h>
#include <string.h>
#include <time.h>

#include "UI/ActMng.h"
#include "server/persistencia/repo_actividad.h"
#include "gestionMenu.h"

extern sqlite3 *db;

const char *TIPOS_ACTIVIDAD[] = {
    "limpieza",
    "rescate",
    "observacion",
    "educacion",
    "restauracion"
};
const int NUM_TIPOS = 5;

void extraerCadenaAct(const char *mensaje, char *dest, size_t tam) {
    printf("%s", mensaje);
    fflush(stdout);

    if (fgets(dest, tam, stdin)) {
        dest[strcspn(dest, "\n")] = 0;
    }
}

void extraerTitulo(char *titulo) {
    extraerCadenaAct("Título: ", titulo, MAX_TITULO);
}

void extraerDescripcion(char *descripcion) {
    extraerCadenaAct("Descripción: ", descripcion, MAX_CONTENIDO);
}

void extraerUbicacion(char *ubicacion) {
    extraerCadenaAct("Ubicación: ", ubicacion, MAX_UBICACION);
}

void extraerFecha(char *fecha) {
    extraerCadenaAct("Fecha (DD/MM/AAAA): ", fecha, FECHA);
}

void extraerHoraInit(char *hora) {
    extraerCadenaAct("Hora inicio (HH:MM): ", hora, HORA);
}

void extraerHoraFin(char *hora) {
    extraerCadenaAct("Hora fin (HH:MM): ", hora, HORA);
}

void elegirTipoActividad(char *dest) {
    int opcion = -1;

    printf("\nSeleccione el tipo de actividad:\n");
    for (int i = 0; i < NUM_TIPOS; i++) {
        printf("%d. %s\n", i + 1, TIPOS_ACTIVIDAD[i]);
    }

    do {
        printf("Opción: ");
        fflush(stdout);

        char buffer[20];
        if (!fgets(buffer, sizeof(buffer), stdin) ||
            sscanf(buffer, "%d", &opcion) != 1 ||
            opcion < 1 || opcion > NUM_TIPOS) {

            printf("Opción inválida. Intente de nuevo.\n");
            opcion = -1;
        }
    } while (opcion == -1);

    strcpy(dest, TIPOS_ACTIVIDAD[opcion - 1]);
}

int crearActividad(Actividad *act) {

    printf("\n===== Creando Nueva Actividad =====\n");

    extraerTitulo(act->titulo);
    extraerDescripcion(act->descripcion);
    extraerUbicacion(act->ubicacion);

    extraerFecha(act->fecha);

    extraerHoraInit(act->hora_init);
    extraerHoraFin(act->hora_fin);

    elegirTipoActividad(act->tipo);

    printf("Máximo de plazas: ");
    if (scanf("%d", &act->max_plazas) != 1) {
        limpiar_buffer();
        printf("Valor inválido para plazas.\n");
        return 0;
    }
    limpiar_buffer();

    if (sqlite3_open("server_data.db", &db) != SQLITE_OK) {
        printf("No se pudo abrir la base de datos\n");
        return 0;
    }

    int sol = repo_actividad_insert(db, act);
    sqlite3_close(db);

    return sol;
}

int modificarActividad(Actividad *act) {

    printf("\n===== Modificación de Actividad =====\n");

    printf("ID de actividad a modificar: ");
    if (scanf("%d", &act->id_actividad) != 1) {
        limpiar_buffer();
        printf("ID inválido.\n");
        return 0;
    }
    limpiar_buffer();

    if (sqlite3_open("server_data.db", &db) != SQLITE_OK) {
        printf("No se pudo abrir la base de datos\n");
        return 0;
    }

    if (!repo_actividad_get(db, act->id_actividad, act)) {
        printf("No existe actividad con ese ID\n");
        sqlite3_close(db);
        return 0;
    }

    printf("\n--- Datos actuales cargados ---\n");
    printf("Título actual: %s\n", act->titulo);

    extraerTitulo(act->titulo);
    extraerDescripcion(act->descripcion);
    extraerUbicacion(act->ubicacion);

    extraerFecha(act->fecha);
    extraerHoraInit(act->hora_init);
    extraerHoraFin(act->hora_fin);

    elegirTipoActividad(act->tipo);

    printf("Máximo de plazas: ");
    if (scanf("%d", &act->max_plazas) != 1) {
        limpiar_buffer();
        printf("Valor inválido para plazas.\n");
        sqlite3_close(db);
        return 0;
    }
    limpiar_buffer();

    int sol = repo_actividad_update(db, act);
    sqlite3_close(db);

    return sol;
}

int eliminarActividad(Actividad *act) {

    printf("\n===== Eliminación de Actividad =====\n");

    printf("ID de actividad a eliminar: ");
    if (scanf("%d", &act->id_actividad) != 1) {
        limpiar_buffer();
        printf("ID inválido.\n");
        return 0;
    }
    limpiar_buffer();

    if (sqlite3_open("server_data.db", &db) != SQLITE_OK) {
        printf("No se pudo abrir la base de datos\n");
        return 0;
    }

    int sol = repo_actividad_delete(db, act->id_actividad);
    sqlite3_close(db);

    return sol;
}
