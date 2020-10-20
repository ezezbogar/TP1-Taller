#ifndef COMMON_SOCKET_H_
#define COMMON_SOCKET_H_

#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>

typedef struct {
	int fd;  // File descriptor
} socket_t;

void socket_init(socket_t *self);

void socket_uninit(socket_t *self);

int socket_get_fd(socket_t* self);


int socket_bind(socket_t *self, struct addrinfo* addresses);

int socket_accept(socket_t *listener, socket_t* peer);

int socket_connect(socket_t *self, struct addrinfo* addresses);

void socket_listen(socket_t* self, int max_waitlist);


#endif  // COMMON_SOCKET_H_
