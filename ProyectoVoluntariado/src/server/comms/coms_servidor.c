/*
 * coms_servidor.c
 *
 *  Created on: 19 mar 2026
 *      Author: j.li
 */

// coms_servidor.c
#include <winsock2.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "coms_servidor.h"
#include "server/persistencia/repo_usuario.h"
#include "server/persistencia/repo_actividad.h"
#include "server/persistencia/repo_reserva.h"
#include "server/persistencia/repo_noticia.h"
#include "server/persistencia/repo_incidencia.h"
#include "server/seguridad/contrasena.h"
#include "server/persistencia/db_connector.h"

#define MAX_BUFFER 2048
#define PUERTO 8080

void iniciar_servidor() {
	// 1. inicializar Winsock
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
		printf("Error iniciando Winsock\n");
		return;
	}

	// 2. crear socket
	SOCKET server_socket = socket(AF_INET, SOCK_STREAM, 0);
	if (server_socket == INVALID_SOCKET) {
		printf("Error creando socket\n");
		WSACleanup();
		return;
	}

	// 3. bind (asociar socket al puerto)
	struct sockaddr_in server_addr;
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = INADDR_ANY;
	server_addr.sin_port = htons(PUERTO);

	if (bind(server_socket, (struct sockaddr*) &server_addr,
			sizeof(server_addr)) == SOCKET_ERROR) {
		printf("Error en bind\n");
		closesocket(server_socket);
		WSACleanup();
		return;
	}

	// 4. listen
	listen(server_socket, 1);
	printf("[SERVIDOR] Escuchando en puerto %d...\n", PUERTO);

	// 5. bucle principal (aceptamos un cliente a la vez)
	while (1) {
		struct sockaddr_in client_addr;
		int client_len = sizeof(client_addr);

		SOCKET client_socket = accept(server_socket,
				(struct sockaddr*) &client_addr, &client_len);
		if (client_socket == INVALID_SOCKET) continue;

		printf("[SERVIDOR] Cliente conectado\n");
		atender_cliente(client_socket);  // función que implementarás después

		closesocket(client_socket);
		printf("[SERVIDOR] Cliente desconectado\n");
	}

	closesocket(server_socket);
	WSACleanup();
}


// enviar respuesta al cliente
static void enviar(SOCKET s, const char *msg) {
	send(s, msg, strlen(msg), 0);
}

// manejar LOGIN|usuario|hash_pw
static void cmd_login(SOCKET s, char *params, int *usuario_id, int *rol) {
	char *usuario = strtok(params, "|");
	char *hash_pw = strtok(NULL, "|");

	if (!usuario || !hash_pw) {
		enviar(s, "ERROR|Parametros incorrectos\n");
		return;
	}

	User u;
	if (!repo_usuario_get_by_mail(db, usuario, &u) &&
			!repo_usuario_get_by_nombre(db, usuario, &u)) {
		enviar(s, "ERROR|Usuario no encontrado\n");
		return;
	}

	if (strcmp(u.pw, hash_pw) != 0) {
		enviar(s, "ERROR|Contrasena incorrecta\n");
		return;
	}

	*usuario_id = u.id;
	*rol = u.rol;

	char respuesta[64];
	snprintf(respuesta, sizeof(respuesta), "OK|%d|%d\n", u.id, u.rol);
	enviar(s, respuesta);
}






static void cmd_registro(SOCKET s, char *params) {
    char *nombre = strtok(params, "|");
    char *mail = strtok(NULL, "|");
    char *hash_pw = strtok(NULL, "|");
    char *tlf = strtok(NULL,"|");

    if (!nombre || !mail || !hash_pw || !tlf) {
        enviar(s, "ERROR|Parametros incorrectos\n");
        return;
    }

    User existe;
    if (repo_usuario_get_by_mail(db, mail, &existe)) {
        enviar(s, "ERROR|El email ya esta registrado\n");
        return;
    }

    User nuevo;
    memset(&nuevo, 0, sizeof(User));

    strncpy(nuevo.nombre, nombre, MAX_NOMBRE - 1);
    strncpy(nuevo.mail, mail, MAX_EMAIL - 1);
    strncpy(nuevo.pw, hash_pw,MAX_PASSWORD - 1);
    strncpy(nuevo.tlf, tlf, MAX_TELEFONO - 1);

    time_t t = time(NULL);
    struct tm *tm_info = localtime(&t);
    snprintf(nuevo.fecha_reg, FECHA, "%02d/%02d/%04d",
             tm_info->tm_mday, tm_info->tm_mon + 1, tm_info->tm_year + 1900);

    nuevo.rol = 0;
    nuevo.estado_cuenta = 1;

    if (repo_usuario_insert_prehashed(db, &nuevo)) {
        enviar(s, "OK|Usuario registrado correctamente\n");
    } else {
        enviar(s, "ERROR|No se pudo registrar el usuario\n");
    }
}







// manejar GET_ACTS
static void cmd_get_acts(SOCKET s) {
	// obtener actividades de la BD y serializar
	const char *sql =
			"SELECT ID, TITULO, FECHA, TIPO, MAX_PLAZAS FROM ACTIVIDAD;";

	sqlite3_stmt *stmt;
	char buffer[MAX_BUFFER];
	strcpy(buffer, "OK");

	if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK) {
		while (sqlite3_step(stmt) == SQLITE_ROW) {
			char item[256];
			snprintf(item, sizeof(item), "|%d,%s,%s,%s,%d",
					sqlite3_column_int(stmt, 0),
					sqlite3_column_text(stmt, 1),
					sqlite3_column_text(stmt, 2),
					sqlite3_column_text(stmt, 3),
					sqlite3_column_int(stmt, 4));
			strncat(buffer, item, MAX_BUFFER - strlen(buffer) - 1);
		}
		sqlite3_finalize(stmt);
	}

	strncat(buffer, "\n", MAX_BUFFER - strlen(buffer) - 1);
	enviar(s, buffer);
}

static void cmd_reservar(SOCKET s, char *params, int usuario_id) {
    if (usuario_id == -1) {
        enviar(s, "ERROR|No autenticado\n");
        return;
    }

    char *id_str = strtok(params, "|");
    if (!id_str) {
        enviar(s, "ERROR|Parametros incorrectos\n");
        return;
    }

    int id_actividad = atoi(id_str);

    Reserva r;
    r.id_usuario     = usuario_id;
    r.id_actividad   = id_actividad;
    r.estado_reserva = 1;

    time_t t = time(NULL);
    struct tm *tm_info = localtime(&t);   // ← renombrado para no chocar con <time.h>
    snprintf(r.fecha, sizeof(r.fecha), "%02d/%02d/%04d",
             tm_info->tm_mday, tm_info->tm_mon + 1, tm_info->tm_year + 1900);

    repo_reserva_insert(db, &r);          // ← sin if, devuelve void
    enviar(s, "OK|Reserva realizada\n");
}

// manejar CANCELAR|id_reserva
static void cmd_cancelar(SOCKET s, char *params) {
	char *id_str = strtok(params, "|");
	if (!id_str) {
		enviar(s, "ERROR|Parametros incorrectos\n");
		return;
	}

	int id_reserva = atoi(id_str);

	if (repo_reserva_delete(db, id_reserva)) {
		enviar(s, "OK|Reserva cancelada\n");
	} else {
		enviar(s, "ERROR|No se pudo cancelar\n");
	}
}

// manejar GET_NOTICIAS
static void cmd_get_noticias(SOCKET s) {
	const char *sql = "SELECT ID, TITULO, CONTENIDO, FECHA_PUB FROM NOTICIA;";

	sqlite3_stmt *stmt;
	char buffer[MAX_BUFFER];
	strcpy(buffer, "OK");

	if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK) {
		while (sqlite3_step(stmt) == SQLITE_ROW) {
			char item[512];
			snprintf(item, sizeof(item), "|%d,%s,%s,%s",
					sqlite3_column_int(stmt, 0),
					sqlite3_column_text(stmt, 1),
					sqlite3_column_text(stmt, 2),
					sqlite3_column_text(stmt, 3));
			strncat(buffer, item, MAX_BUFFER - strlen(buffer) - 1);
		}
		sqlite3_finalize(stmt);
	}

	strncat(buffer, "\n", MAX_BUFFER - strlen(buffer) - 1);
	enviar(s, buffer);
}



static void cmd_get_mis_reservas(SOCKET s, char *params) {
    char *id_str = strtok(params, "|");
    if (!id_str) {
        enviar(s, "ERROR|Parametros incorrectos\n");
        return;
    }

    int id_usuario = atoi(id_str);

    const char *sql =
        "SELECT r.ID, r.ID_ACTIVIDAD, a.TITULO, r.FECHA, r.ESTADO_RESERVA "
        "FROM RESERVA r "
        "JOIN ACTIVIDAD a ON r.ID_ACTIVIDAD = a.ID "
        "WHERE r.ID_USUARIO = ?;";

    sqlite3_stmt *stmt;
    char buffer[MAX_BUFFER];
    strcpy(buffer, "OK");

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK) {
        sqlite3_bind_int(stmt, 1, id_usuario);

        while (sqlite3_step(stmt) == SQLITE_ROW) {
            char item[256];
            snprintf(item, sizeof(item), "|%d,%d,%s,%s,%d",
                    sqlite3_column_int(stmt, 0),
                    sqlite3_column_int(stmt, 1),
                    sqlite3_column_text(stmt, 2),
                    sqlite3_column_text(stmt, 3),
                    sqlite3_column_int(stmt, 4));
            strncat(buffer, item, MAX_BUFFER - strlen(buffer) - 1);
        }
        sqlite3_finalize(stmt);
    }

    strncat(buffer, "\n", MAX_BUFFER - strlen(buffer) - 1);
    enviar(s, buffer);
}



static void cmd_incidencia(SOCKET s, char *params, int usuario_id) {
    if (usuario_id == -1) {
        enviar(s, "ERROR|No autenticado\n");
        return;
    }

    char *descripcion = strtok(params, "|");
    char *ubicacion = strtok(NULL, "|");

    if (!descripcion || !ubicacion) {
        enviar(s, "ERROR|Parametros incorrectos\n");
        return;
    }

    Incidencia inc;
    inc.id_usuario = usuario_id;
    strncpy(inc.descripcion, descripcion, sizeof(inc.descripcion) - 1);
    strncpy(inc.ubicacion, ubicacion, sizeof(inc.ubicacion) - 1);

    time_t t = time(NULL);
    struct tm *tm_info = localtime(&t);
    snprintf(inc.fecha_reporte, sizeof(inc.fecha_reporte), "%02d/%02d/%04d",
             tm_info->tm_mday, tm_info->tm_mon + 1, tm_info->tm_year + 1900);
    snprintf(inc.hora_reporte, sizeof(inc.hora_reporte), "%02d:%02d",
             tm_info->tm_hour, tm_info->tm_min);

    if (repo_incidencia_insert(db, &inc)) {
        enviar(s, "OK|Incidencia registrada correctamente\n");
    } else {
        enviar(s, "ERROR|No se pudo registrar la incidencia\n");
    }
}



// bucle principal que atiende a un cliente
void atender_cliente(SOCKET client_socket) {
	char buffer[MAX_BUFFER];
	int usuario_id = -1;   // -1 = no autenticado
	int rol = -1;

	while (1) {
		memset(buffer, 0, sizeof(buffer));
		int bytes = recv(client_socket, buffer, sizeof(buffer) - 1, 0);

		if (bytes <= 0) break;  // cliente desconectado

		// quitar '\n' del final
		buffer[strcspn(buffer, "\r\n")] = 0;

		printf("[SERVIDOR] Recibido: %s\n", buffer);

		// separar comando del resto
		char *comando = strtok(buffer, "|");
		char *params = strtok(NULL, "");  // todo lo que queda

		if (!comando) continue;

		if(strcmp(comando, "LOGIN")== 0)
			cmd_login(client_socket, params, &usuario_id, &rol);
		else if (strcmp(comando, "REGISTRO")== 0)
			cmd_registro(client_socket, params);
		else if (strcmp(comando, "GET_ACTS")== 0)
			cmd_get_acts(client_socket);
		else if (strcmp(comando, "RESERVAR")== 0)
			cmd_reservar(client_socket, params, usuario_id);
		else if (strcmp(comando, "CANCELAR")== 0)
			cmd_cancelar(client_socket, params);
		else if (strcmp(comando, "GET_NOTICIAS")== 0)
			cmd_get_noticias(client_socket);
		else if (strcmp(comando, "GET_MIS_RESERVAS")== 0)
			cmd_get_mis_reservas(client_socket, params);
		else if (strcmp(comando, "INCIDENCIA")== 0)
			cmd_incidencia(client_socket, params, usuario_id);
		else if (strcmp(comando, "LOGOUT")== 0) {
			enviar(client_socket, "OK|Hasta luego\n");
			break;
		} else
			enviar(client_socket, "ERROR|Comando desconocido\n");
	}
}
