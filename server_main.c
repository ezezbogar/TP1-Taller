#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "common_socket.h"
#include "server_server.h"
#include "common_crypter.h"

#define BUFFER_SIZE 32

int main(int argc, char *argv[]) {

   char buffer[64];
   int bytes_received;

   crypter_t crypter;
   crypter_init(&crypter, argv[2], argv[3]);

   server_t server;
   server_init(&server, argv[1]);
   server_connect(&server);

   do {

      bytes_received = server_recieve(&server, buffer, BUFFER_SIZE);
      crypter_decipher(&crypter, buffer, bytes_received);
      fwrite(buffer, sizeof(char), bytes_received, stdout);

   }
   while(bytes_received != 0);
   

   //crypter uninit?
   server_uninit(&server);

	return 0;
 }