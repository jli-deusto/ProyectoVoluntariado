/*
 * main.c
 *
 *  Created on: 19 mar 2026
 *      Author: j.li
 */

#include <stdio.h>
#include <stdlib.h>
#include "config/config_sistema.h" // to read admin.conf
#include "guardar/admin_data_manager.h" // to open DB
#include "../UI/menu.h"
#include "shared/constantes.h"
#include "server/persistencia/db_connector.h"
#include "Libs/sqlite/sqlite3.h"

int main_admin(){
	// 1. read admin.conf
	ConfigAdmin config;

	if(!cargar_configuracion("admin.conf", &config)){
		printf("Error de carga de configuración \n");
	} else {

	printf("Base de datos: %s \n", config.db_path);
	printf("Log: %s \n", config.log_path);
	printf("CSV usuarios: %s \n", config.csv_usuarios);
	printf("CSV actividades: %s \n", config.csv_actividades);
	printf("Admin: %s \n", config.admin_user);
	printf("Máx usuarios: %d \n", config.max_usuarios);
	printf("Máx actividades: %d \n", config.max_actividades); }

	//2. open data base
	open_connection();

	if (db == NULL) {
		printf("ERROR: No se pudo abrir la base de datos.\n");
		return 1;
	}

	printf("DEBUG → Base de datos abierta: %s\n", sqlite3_db_filename(db, NULL));


//// 3. create database if tables do not exist .
//
//// 4. show the principal menu.
//

	// 3. create database if tables do not exist

	// 4. show the principal menu
	//menu_principal();
	return 0; }

// ..
