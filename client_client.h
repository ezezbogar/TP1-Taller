#ifndef CLIENT_CLIENT_H_
#define CLIENT_CLIENT_H_

#include "common_socket.h"
#include "common_crypter.h"

/* El TDA client permite conectarse al puerto y direccion ip especificados
 * y enviar bytes cifrados a un servidor*/

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

/* Cifra los bytes leidos y los envia hasta que se termina el archivo
 * de entrada */
void client_run(client_t* self, crypter_t* crypter);

/* Destructor */
void client_uninit(client_t* self);

#endif  // CLIENT_CLIENT_H_
