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

/* Constructor */
void socket_init(socket_t *self);

/* Devuelve el File descriptor */
int socket_get_fd(socket_t* self);

/* Hace el bind del socket para alguna direccion valida. Devuelve
 * -1 ante algun error, 0 en caso de exito */
int socket_bind(socket_t *self, struct addrinfo* addresses);

/* Deja el socket a la espera de alguna conexion entrante hasta que algun 
 * cliente se conecte. Devuelve -1 ante algun error, 0 en caso de exito */
int socket_accept(socket_t *self, socket_t* peer);

/* Conecta el socket a algun peer del servidor. Devuelve -1 ante algun 
 * error, 0 en caso de exito */
int socket_connect(socket_t *self, struct addrinfo* addresses);

/* Define la cantidad de clientes que pueden estar a la espera de 
 * conectarse a algun peer */
void socket_listen(socket_t* self, int max_waitlist);

/* Destructor */
void socket_uninit(socket_t *self);

#endif  // COMMON_SOCKET_H_
