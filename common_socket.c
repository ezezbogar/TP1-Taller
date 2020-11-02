#define _POSIX_C_SOURCE 200112L

#include "common_socket.h"
#include <errno.h>
#include <stdio.h>
#include <string.h>

#define SUCCESS 0
#define ERROR -1

void socket_init(socket_t *self) {
	self->fd = -1;
}

int socket_get_fd(socket_t* self) {
	return self->fd;
}


int socket_connect(socket_t* self, struct addrinfo* addresses) {
	struct addrinfo* rp;

    for (rp = addresses; rp != NULL; rp = rp->ai_next) {
        self->fd = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);

        if (connect(self->fd , rp->ai_addr, rp->ai_addrlen) != -1) {
        	return SUCCESS;
        }
    }
    return ERROR;
}

int socket_bind(socket_t* self, struct addrinfo* addresses) {
	int val;
	struct addrinfo* rp;

	for (rp = addresses; rp != NULL; rp = rp->ai_next) {
    	self->fd = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);

		val = 1;
		setsockopt(self->fd, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val));

        if (bind(self->fd, rp->ai_addr, rp->ai_addrlen) == 0) {
        	return SUCCESS;
        }
    }
    return ERROR;
}

int socket_accept(socket_t *listener, socket_t* peer) {
	int peerfd;
	peerfd = accept(listener->fd, NULL, NULL);
	if (peerfd == -1) {
		return ERROR;
	} else {
		peer->fd = peerfd;
		return SUCCESS;
	}
}

void socket_uninit(socket_t* self) {
	shutdown(self->fd, SHUT_RDWR);
    close(self->fd);
}

int socket_send(socket_t* self, char* message, int size) {
	int destination = socket_get_fd(self);
	int sent = 0;

	while(sent < size) {
		int s = send(destination, message + sent, size - sent, MSG_NOSIGNAL);
		sent += s;
	}
	return sent;
}

int socket_receive(socket_t* self, char* message, int size) {
	int source = socket_get_fd(self);
	int received = 0;

	while(received < size) {
		int s = recv(source, message + received, size - received , 0);
		if (s == -1) {
			fprintf(stderr, "Error: %s\n", strerror(errno));
            return ERROR;
        } else if (s == 0) {
        	break;
        } else {
        	received += s;
        }
	}
	return received;
}

void socket_listen(socket_t* self, int max_waitlist) {
	listen(self->fd, max_waitlist);
}

