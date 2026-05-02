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
#include "server/seguridad/contrasena.h"
#include <unistd.h>

int validarAdmin(char usuario[MAX_NOMBRE], char password[MAX_PASSWORD]) {
	ConfigAdmin configAdmin;
	char r[32] = "data/admin.conf";

	if (cargar_configuracion(r, &configAdmin) == 0) {
		puts("problemas con el sistema, intentelo mas tarde.\n");

		char cwd[256];
		getcwd(cwd, sizeof(cwd));
		printf("Directorio actual: %s\n", cwd);
		return 0;
	}

	// validar usuario
	if (strcmp(usuario, configAdmin.admin_user) != 0) {
		puts("Usuario incorrecto.\n");
		return 0;
	}
	// hashear la contrasena ingresada

	char hash_pw[32];
	hashear_password(password, hash_pw, sizeof(hash_pw));

	// comparar hash calculado con hash almacenado
	if (strcmp(hash_pw, configAdmin.admin_pass) != 0) {
		puts("contrasena incorrecta.\n");
		return 0;
	}

	return 1;
}
