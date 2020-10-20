#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "socket.h"
#include "server.h"
#include "crypter.h"

#define BUFFER_SIZE 32

int main(int argc, char *argv[]) {

   char buffer[64];
   int bytes_received;

   server_t server;
   server_init(&server, argv[1]);
   server_connect(&server);

   do {

      bytes_received = server_recieve(&server, buffer, BUFFER_SIZE);
      fwrite(buffer, sizeof(char), bytes_received, stdout);

   }
   while(bytes_received != 0);
   

   server_uninit(&server);

	return 0;
 }