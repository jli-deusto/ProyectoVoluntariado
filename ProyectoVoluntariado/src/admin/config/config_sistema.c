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
        printf("Error: no se pudo abrir el fichero %s \n", ruta);
        return 0;
    }

    char linea[512];

    while(fgets(linea, sizeof(linea), f)){

        if (linea[0] == '#' || linea[0] == '\n')
            continue;

        char *clave = strtok(linea, "=");
        char *valor = strtok(NULL, "\n");

        if(!clave || !valor)
            continue;

        // trim espacios
        while(*clave == ' ') clave++;
        while(*valor == ' ') valor++;

        if (strcmp(clave, "DB_PATH") == 0) {
            strncpy(config->db_path, valor, MAX_RUTA);
        } else if (strcmp(clave, "LOG_PATH") == 0) {
            strncpy(config->log_path, valor, MAX_RUTA);
        } else if (strcmp(clave, "CSV_USUARIOS") == 0) {
            strncpy(config->csv_usuarios, valor, MAX_RUTA);
        } else if (strcmp(clave, "CSV_ACTIVIDADES") == 0) {
            strncpy(config->csv_actividades, valor, MAX_RUTA);
        } else if (strcmp(clave, "CSV_NOTICIAS") == 0) {
            strncpy(config->csv_noticias, valor, MAX_RUTA);
        } else if (strcmp(clave, "CSV_RESERVAS") == 0) {
            strncpy(config->csv_reservas, valor, MAX_RUTA);
        } else if (strcmp(clave, "ADMIN_USER") == 0) {
            strncpy(config->admin_user, valor, MAX_NOMBRE);
        } else if (strcmp(clave, "ADMIN_PASS") == 0) {
            strncpy(config->admin_pass, valor, MAX_PASSWORD);
        } else if (strcmp(clave, "MAX_USUARIOS") == 0) {
            config->max_usuarios = atoi(valor);
        } else if (strcmp(clave, "MAX_ACTIVIDADES") == 0) {
            config->max_actividades = atoi(valor);
        }
    }

    fclose(f);
    return 1;
}
