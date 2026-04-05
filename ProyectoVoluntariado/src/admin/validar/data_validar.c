/*
 * data_validar.c
 *
 *  Created on: 19 mar 2026
 *      Author: j.li
 */

#include "stdio.h"
#include "stdlib.h"
#include <string.h>
#include "data_validar.h"
#include "admin/config/config_sistema.h"


#include <unistd.h>

int validarAdmin(char usuario[MAX_NOMBRE], char password[MAX_PASSWORD]) {
	ConfigAdmin configAdmin;
	char r[16] = "data/admin.conf";
	if (cargar_configuracion(r, &configAdmin) == 0) {
		puts("problemas con el sistema, intentelo mas tarde.\n");

		char cwd[256];
		getcwd(cwd, sizeof(cwd));
		printf("Directorio actual: %s\n", cwd);
		return 0;
	} else if (strcmp(usuario, configAdmin.admin_user) != 0 || strcmp(password, configAdmin.admin_pass) != 0 ) {
//		printf("Admin user correcto: %s\n",configAdmin.admin_user);
//		printf("Admin pw correcto: %s\n",configAdmin.admin_pass);
//
//		puts("Usuario y/o clave incorrecta");
		return 0;
	}


	return 1;
}
