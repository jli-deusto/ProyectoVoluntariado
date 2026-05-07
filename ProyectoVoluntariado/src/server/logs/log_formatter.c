/*
 * log_formatter.c
 *
 *  Created on: 19 mar 2026
 *      Author: j.li
 */

#include <stdio.h>
#include <time.h>
#include <string.h>
#include "log_formatter.h"

const char *nivel_a_cadena(LogNivel nivel) {
    switch (nivel) {
        case LOG_INFO:  return "INFO ";
        case LOG_WARN:  return "WARN ";
        case LOG_ERROR: return "ERROR";
        default:        return "?????";
    }
}

void formatear_linea_log(LogNivel nivel, const char *mensaje,
                         char *dest, size_t tam) {

    time_t ahora = time(NULL);
    struct tm *tm_info = localtime(&ahora);

    char timestamp[32];
    strftime(timestamp, sizeof(timestamp), "%d/%m/%Y %H:%M:%S", tm_info);

    snprintf(dest, tam, "[%s] [%s] %s\n",
             timestamp,
             nivel_a_cadena(nivel),
             mensaje ? mensaje : "");
}
