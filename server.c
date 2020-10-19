#include "server.h"

#define MAX_LISTENERS 10
#define SUCCESS 0
#define ERROR -1

struct addrinfo* _get_address(server_t* self) {

	int s;
	struct addrinfo hints, *result;

	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_family = AF_INET;    		/* IPv4 (or AF_INET6 for IPv6)     */
    hints.ai_socktype = SOCK_STREAM; 	/* TCP  (or SOCK_DGRAM for UDP)    */
    hints.ai_flags = AI_PASSIVE;    	/* AI_PASSIVE for server           */
    hints.ai_protocol = 0;          	/* Any protocol */

	s = getaddrinfo(NULL, self->port, &hints, &result);

	return result;
}

int server_init(server_t* self, char* port){

	self->port = port;
	socket_init(&self->peer);
	socket_init(&self->acceptor);

	//copiar puntero?
}

int server_recieve(server_t* self, char* message, int size) {

	int source = socket_get_fd(&self->peer);

	int received = 0;
	int s = 0;

	while(received < size) {//o buf len?

		s = recv(source, message + received, size - received , 0);

		if (s == -1){ //Hubo un error

			fprintf(stderr,"Error: %s\n", strerror(errno));
            return ERROR;

        } else if (s == 0) { //Nos cerraron el socket

        	return 0;

        } else {

        	received += s;
	
        }

     		}

	return received;

}

int server_connect(server_t* self) {

	struct addrinfo* address = _get_address(self);

	socket_bind(&self->acceptor, address);
	freeaddrinfo(address);
	socket_listen(&self->acceptor, MAX_LISTENERS);
	socket_accept(&self->acceptor, &self->peer);
}

int server_uninit(server_t* self) {

	socket_uninit(&self->acceptor);
	socket_uninit(&self->peer);

	return 0;
}

