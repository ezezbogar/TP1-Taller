#define _POSIX_C_SOURCE 200112L

#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "client_client.h"
#include "common_crypter.h"

#define BUFFER_SIZE 64

int main(int argc, char *argv[]) {
   char buffer[BUFFER_SIZE];

   crypter_t crypter;
   crypter_init(&crypter, argv[3], argv[4]);
   client_t client;
   client_init(&client, argv[1], argv[2]);
   client_connect(&client);

   while (!feof(stdin)) {
      size_t result = fread(buffer, sizeof(char), BUFFER_SIZE, stdin);
      crypter_cipher(&crypter, (unsigned char*)buffer, (int)result);
      client_send(&client, buffer, (int)result);
   }

   client_uninit(&client);
   crypter_uninit(&crypter);

	return 0;
 }
