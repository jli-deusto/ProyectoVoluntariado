/*
 * log_formatter.h
 *
 *  Created on: 7 may 2026
 *      Author: j.li
 */

#ifndef LOG_FORMATTER_H_
#define LOG_FORMATTER_H_

#include <stddef.h>
#include <stdlib.h>

typedef enum {
    LOG_INFO  = 0,
    LOG_WARN  = 1,
    LOG_ERROR = 2
} LogNivel;

const char *nivel_a_cadena(LogNivel nivel);

void formatear_linea_log(LogNivel nivel, const char *mensaje, char *dest, size_t tam);


#endif /* LOG_FORMATTER_H_ */
