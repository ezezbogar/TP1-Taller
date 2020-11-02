#define _POSIX_C_SOURCE 200112L

#include <stdio.h>
#include "client_client.h"

#define ERROR -1

int main(int argc, char *argv[]) {
   if (argc != 5) {
      fprintf(stderr, "Argumentos Invalidos\n");
      return ERROR;
   }

   crypter_t crypter;
   crypter_init(&crypter, argv[3], argv[4]);
   client_t client;
   client_init(&client, argv[1], argv[2]);
   client_connect(&client);

   client_run(&client, &crypter);

   client_uninit(&client);
   crypter_uninit(&crypter);

	return 0;
}
