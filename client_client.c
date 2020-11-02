#define _POSIX_C_SOURCE 200112L
#define BUFFER_SIZE 64

#include "client_client.h"
#include <string.h>
#include <stdio.h>

static struct addrinfo* _get_address(client_t* self) {
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
	int bytes_sent;
	bytes_sent = socket_send(&self->socket, message, size);
	return bytes_sent;
}

void client_connect(client_t* self) {
	struct addrinfo* address = _get_address(self);
	socket_connect(&self->socket, address);
	freeaddrinfo(address);
}

void client_run(client_t* self, crypter_t* crypter) {
	char buffer[BUFFER_SIZE];

	while (!feof(stdin)) {
      size_t result = fread(buffer, sizeof(char), BUFFER_SIZE, stdin);
      crypter_cipher(crypter, (unsigned char*)buffer, (int)result);
      client_send(self, buffer, (int)result);
   }
}

void client_uninit(client_t* self) {
	socket_uninit(&self->socket);
}
