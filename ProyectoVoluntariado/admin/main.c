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
<<<<<<< HEAD
#include "../UI/menu.h"
#include "../shared/constantes.h"
=======
#include "ui/menu.h"
#include "shared/constantes.h"
>>>>>>> branch 'master' of https://github.com/jli-deusto/ProyectoVoluntariado.git

<<<<<<< HEAD
int main(){
	// 1. read admin.conf
	ConfigAdmin config;

	if(!cargar_configuracion("admin.config", &config)){
		printf("Error de carga de configuración \n");
	}

	printf("Base de datos: %s \n", config.db_path);
	printf("Log: %s \n", config.log_path);
	printf("CSV usuarios: %s \n", config.csv_usuarios);
	printf("CSV actividades: %s \n", config.csv_actividades);
	printf("Admin: %s \n", config.admin_user);
	printf("Máx usuarios: %d \n", config.max_usuarios);
	printf("Máx actividades: %d \n", config.max_actividades);

	//2. open data base
=======
//// 1. read admin.conf
//
////2. open data base
//
//// 3. create database if tables do not exist
//
//// 4. show the principal menu
//
>>>>>>> branch 'master' of https://github.com/jli-deusto/ProyectoVoluntariado.git

<<<<<<< HEAD
	// 3. create database if tables do not exist

	// 4. show the principal menu
	menu_principal();
	return 0;
=======
int main() {
    printf("Arrancando programa...\n");
    menu_principal();
    return 0;
>>>>>>> branch 'master' of https://github.com/jli-deusto/ProyectoVoluntariado.git
}
