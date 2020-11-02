#define _POSIX_C_SOURCE 200112L
#define BUFFER_SIZE 64

#include "server_server.h"
#include <string.h>
#include <stdio.h>

#define MAX_LISTENERS 10
#define SUCCESS 0
#define ERROR -1

static struct addrinfo* _get_address(server_t* self) {
	struct addrinfo hints, *result;

	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_family = AF_INET;    		/* IPv4 (or AF_INET6 for IPv6)     */
    hints.ai_socktype = SOCK_STREAM; 	/* TCP  (or SOCK_DGRAM for UDP)    */
    hints.ai_flags = AI_PASSIVE;    	/* AI_PASSIVE for server           */
    hints.ai_protocol = 0;          	/* Any protocol */

	getaddrinfo(NULL, self->port, &hints, &result);

	return result;
}

void server_init(server_t* self, char* port) {
	self->port = port;
	socket_init(&self->peer);
	socket_init(&self->acceptor);
}

int server_recieve(server_t* self, char* message, int size) {
	int bytes_received;
	bytes_received = socket_receive(&self->peer, message, size);
	return bytes_received;
}

void server_connect(server_t* self) {
	struct addrinfo* address = _get_address(self);

	socket_bind(&self->acceptor, address);
	freeaddrinfo(address);
	socket_listen(&self->acceptor, MAX_LISTENERS);
	socket_accept(&self->acceptor, &self->peer);
}

void server_run(server_t* self, crypter_t* crypter) {
	char buffer[BUFFER_SIZE];
	int bytes_received;

	do {
		bytes_received = server_recieve(self, buffer, BUFFER_SIZE);
		crypter_decipher(crypter, (unsigned char*)buffer, bytes_received);
		fwrite(buffer, sizeof(char), bytes_received, stdout);
	} while (bytes_received != 0);
}

void server_uninit(server_t* self) {
	socket_uninit(&self->acceptor);
	socket_uninit(&self->peer);
}

