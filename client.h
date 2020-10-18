#ifndef CLIENT_H
#define CLIENT_H

#include "socket.h"

typedef struct {

	char* host;
	char* port;
	socket_t socket;

} client_t;

void client_init(client_t* self, char* host, char* port);

int client_send(client_t* self, char* message, int size);

void client_connect(client_t* self);

void client_uninit(client_t* self);

#endif //CLIENT_H

