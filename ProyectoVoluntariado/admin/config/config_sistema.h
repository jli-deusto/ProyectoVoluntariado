/*
 * config_sistema.h
 *
 *  Created on: 19 mar 2026
 *      Author: j.li
 */

#ifndef CONFIG_CONFIG_SISTEMA_H_
#define CONFIG_CONFIG_SISTEMA_H_
#include "../../shared/constantes.h"

typedef struct {
	char db_path[MAX_RUTA];
	char log_path[MAX_RUTA];
	char csv_usuarios[MAX_RUTA];
	char csv_actividades[MAX_RUTA];
	char admin_user[MAX_NOMBRE];
	char admin_pass[MAX_PASSWORD];
	int max_usuarios;
	int max_actividades;
} ConfigAdmin;

int cargar_configuracion(const char *ruta, ConfigAdmin *config);

#endif /* CONFIG_CONFIG_SISTEMA_H_ */
