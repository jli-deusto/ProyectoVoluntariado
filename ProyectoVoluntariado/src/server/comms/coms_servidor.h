/*
 * coms_servidor.h
 *
 *  Created on: 7 may 2026
 *      Author: danielavalentina.s
 */

#ifndef SERVER_COMMS_COMS_SERVIDOR_H_
#define SERVER_COMMS_COMS_SERVIDOR_H_
#include <winsock2.h>

void iniciar_servidor();
void atender_cliente(SOCKET client_socket);
#endif /* SERVER_COMMS_COMS_SERVIDOR_H_ */
