/*
 * config_sistema.c
 *
 *  Created on: 19 mar 2026
 *      Author: j.li
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "config_sistema.h"

int cargar_configuracion(const char *ruta, ConfigAdmin *config){

	FILE *f = fopen(ruta, "r");

	if (!f){
		printf("Error: no de pudo abrir el fichero %s \n", ruta);
		return 0;
	}

	char linea[512];

	while(fgets(linea, sizeof(linea), f)){

		//ignorar comentarios y lineas vacias
		if (linea[0] == '#' || linea[0] == '\n')
			continue;

		//separar clave y valor
		char *clave = strtok(linea, "=");
		char * valor = strtok(NULL, "\n");

		if(!clave || !valor)
			continue;

		//asignar valores segun clave
		if (strcmp(clave, "db_path") == 0) {
			strncpy(config->db_path, valor, MAX_RUTA);
		}else if (strcmp(clave, "log_path") == 0) {
		    strncpy(config->log_path, valor, MAX_RUTA);
		}else if (strcmp(clave, "csv_usuarios") == 0) {
		    strncpy(config->csv_usuarios, valor, MAX_RUTA);
		}else if (strcmp(clave, "csv_actividades") == 0) {
		    strncpy(config->csv_actividades, valor, MAX_RUTA);
		}else if (strcmp(clave, "admin_user") == 0) {
		    strncpy(config->admin_user, valor, MAX_NOMBRE);
		}else if (strcmp(clave, "admin_pass") == 0) {
		    strncpy(config->admin_pass, valor, MAX_PASSWORD);
		}else if (strcmp(clave, "max_usuarios") == 0) {
		    config->max_usuarios = atoi(valor);
		}else if (strcmp(clave, "max_actividades") == 0) {
		    config->max_actividades = atoi(valor);
		}

	}

	fclose(f);

	return 1;
	//...
}
