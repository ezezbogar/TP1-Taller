#define _POSIX_C_SOURCE 200112L

#include "client_client.h"

struct addrinfo* _get_address(client_t* self){

	struct addrinfo hints, *result;

	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_family = AF_INET;    		/* IPv4 (or AF_INET6 for IPv6)     */
    hints.ai_socktype = SOCK_STREAM; 	/* TCP  (or SOCK_DGRAM for UDP)    */
    hints.ai_protocol = 0;          	/* Any protocol */

	getaddrinfo(self->host, self->port, &hints, &result);

	return result;
}

void client_init(client_t* self, char* host, char* port) {

	self->host = host;
	self->port = port;
	socket_init(&self->socket);

}

int client_send(client_t* self, char* message, int size) {

	int destination = socket_get_fd(&self->socket);
	int sent = 0;
	int s = 0;

	while(sent < size) {

		s = send(destination, message + sent, size - sent, MSG_NOSIGNAL); //MSG_NOSIGNAL?
		sent += s;
	}

	return sent;
}

void client_connect(client_t* self) {

	struct addrinfo* address = _get_address(self);
	socket_connect(&self->socket, address);
	freeaddrinfo(address);
}

void client_uninit(client_t* self) {
	socket_uninit(&self->socket);
}