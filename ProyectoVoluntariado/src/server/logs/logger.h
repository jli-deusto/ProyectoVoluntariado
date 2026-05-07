/*
 * logger.h
 *
 *  Created on: 7 may 2026
 *      Author: j.li
 */

#ifndef LOGGER_H_
#define LOGGER_H_

#include "log_formatter.h"

#define LOG_SERVIDOR   "logs/server.log"
#define LOG_ADMIN      "logs/admin.log"
#define LOG_VOLUNTARIO "logs/volunteer.log"

int logger_init(void);

int logger_escribir(const char *ruta_log, LogNivel nivel,
                    const char *mensaje);

int log_servidor  (LogNivel nivel, const char *mensaje);
int log_admin     (LogNivel nivel, const char *mensaje);
int log_voluntario(LogNivel nivel, const char *mensaje);


#endif /* LOGGER_H_ */
