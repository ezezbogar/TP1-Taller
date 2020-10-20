#ifndef CLIENT_CLIENT_H_
#define CLIENT_CLIENT_H_

#include "common_socket.h"

typedef struct {
	char* host;
	char* port;
	socket_t socket;
} client_t;

/* Constructor */
void client_init(client_t* self, char* host, char* port);

/* Conecta el socket del cliente al servidor */
void client_connect(client_t* self);

/* Envia los primeros "size" bytes de "message" al server con el cual
 * esta manteniendo una conexion. Devuelve la cantidad de bytes enviados */
int client_send(client_t* self, char* message, int size);

/* Destructor */
void client_uninit(client_t* self);

#endif  // CLIENT_CLIENT_H_
