#ifndef SERVER_SERVER_H_
#define SERVER_SERVER_H_

#include "common_socket.h"
#include "common_crypter.h"

typedef struct {
	char* port;
	socket_t peer, acceptor;
} server_t;

/* Constructor */
void server_init(server_t* self, char* port);

/* Recibe del socket peer "size" bytes, o menos si es que nos cierran el
 * socket y los guarda en message. Devuelve la cantidad de bytes recibidos */
int server_recieve(server_t* self, char* message, int size);

/* Hace el bind al socket aceptador y conecta el socket peer con
 * el socket del cliente*/
void server_connect(server_t* self);

void server_run(server_t* self, crypter_t* crypter);

/* Destructor */
void server_uninit(server_t* self);

#endif  // SERVER_SERVER_H_
