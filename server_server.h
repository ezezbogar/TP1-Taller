#ifndef SERVER_SERVER_H
#define SERVER_SERVER_H

#include "common_socket.h"

typedef struct {

	char* port;
	socket_t peer, acceptor;

} server_t;

void server_init(server_t* self, char* port);

int server_recieve(server_t* self, char* message, int size);

void server_connect(server_t* self);

void server_uninit(server_t* self);







#endif //SERVER_SERVER_H