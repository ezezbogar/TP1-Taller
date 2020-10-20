#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "common_socket.h"
#include "client_client.h"
#include "common_crypter.h"

#define BUFFER_SIZE 32

int main(int argc, char *argv[]) {

   char buffer[64];

   crypter_t crypter;
   crypter_init(&crypter, argv[3], argv[4]);
   client_t client;
   client_init(&client, argv[1], argv[2]);
   client_connect(&client);

   while(!feof(stdin)) {

      size_t result = fread(buffer, sizeof(char), BUFFER_SIZE, stdin);
      crypter_cipher(&crypter, buffer, (int)result);
      client_send(&client, buffer, (int)result);

   }

   client_uninit(&client);

	return 0;
 }