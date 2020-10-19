#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "socket.h"
#include "client.h"

#define BUFFER_SIZE 32

int main(int argc, char *argv[]) {

   char buffer[64];

   client_t client;
   client_init(&client, argv[1], argv[2]);
   client_connect(&client);

   while(!feof(stdin)) {

      size_t result = fread(buffer, sizeof(char), BUFFER_SIZE, stdin);

      client_send(&client, buffer, (int)result);

   }

   client_uninit(&client);

	return 0;
 }