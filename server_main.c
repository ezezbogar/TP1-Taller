#define _POSIX_C_SOURCE 200112L

#include <stdio.h>

#include "server_server.h"
#include "common_crypter.h"

#define BUFFER_SIZE 64
#define ERROR -1

int main(int argc, char *argv[]) {
   if(argc != 4) {
      fprintf(stderr, "Argumentos Invalidos\n");
      return ERROR;
   }

   char buffer[BUFFER_SIZE];
   int bytes_received;

   crypter_t crypter;
   crypter_init(&crypter, argv[2], argv[3]);
   server_t server;
   server_init(&server, argv[1]);
   server_connect(&server);

   do {
      bytes_received = server_recieve(&server, buffer, BUFFER_SIZE);
      crypter_decipher(&crypter, (unsigned char*)buffer, bytes_received);
      fwrite(buffer, sizeof(char), bytes_received, stdout);
   } while (bytes_received != 0);
   server_uninit(&server);
   crypter_uninit(&crypter);

	return 0;
}
