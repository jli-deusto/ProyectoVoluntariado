/*
 * logger.c
 *
 *  Created on: 19 mar 2026
 *      Author: j.li
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "logger.h"
#include "log_formatter.h"


static int crear_directorio_si_no_existe(const char *ruta) {
    struct stat st;
    if (stat(ruta, &st) == 0) {
        return 1; /* ya existe */
    }
#ifdef _WIN32
    if (mkdir(ruta) != 0) {
#else
    if (mkdir(ruta, 0755) != 0) {
#endif
        fprintf(stderr, "[LOGGER] No se pudo crear directorio: %s\n", ruta);
        return 0;
    }
    return 1;
}


static int asegurar_fichero(const char *ruta) {
    FILE *f = fopen(ruta, "a");
    if (!f) {
        fprintf(stderr, "[LOGGER] No se pudo abrir/crear: %s\n", ruta);
        return 0;
    }
    fclose(f);
    return 1;
}

//API
int logger_init(void) {
    if (!crear_directorio_si_no_existe("logs")) return 0;

    int ok = 1;
    ok &= asegurar_fichero(LOG_SERVIDOR);
    ok &= asegurar_fichero(LOG_ADMIN);
    ok &= asegurar_fichero(LOG_VOLUNTARIO);

    if (ok) {
        /* Registrar inicio del sistema en los tres logs */
        log_servidor  (LOG_INFO, "Sistema iniciado.");
        log_admin     (LOG_INFO, "Módulo admin iniciado.");
        log_voluntario(LOG_INFO, "Módulo voluntario iniciado.");
    }

    return ok;
}

int logger_escribir(const char *ruta_log, LogNivel nivel,
                    const char *mensaje) {
    if (!ruta_log || !mensaje) return 0;

    char linea[768];
    formatear_linea_log(nivel, mensaje, linea, sizeof(linea));

    FILE *f = fopen(ruta_log, "a");
    if (!f) {
        fprintf(stderr, "[LOGGER] No se pudo abrir %s\n", ruta_log);
        return 0;
    }

    fputs(linea, f);
    fflush(f);
    fclose(f);

    return 1;
}


int log_servidor(LogNivel nivel, const char *mensaje) {
    return logger_escribir(LOG_SERVIDOR, nivel, mensaje);
}

int log_admin(LogNivel nivel, const char *mensaje) {
    return logger_escribir(LOG_ADMIN, nivel, mensaje);
}

int log_voluntario(LogNivel nivel, const char *mensaje) {
    return logger_escribir(LOG_VOLUNTARIO, nivel, mensaje);
}
