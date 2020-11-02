#define _POSIX_C_SOURCE 200112L

#include <stdio.h>
#include "server_server.h"

#define ERROR -1

int main(int argc, char *argv[]) {
   if (argc != 4) {
      fprintf(stderr, "Argumentos Invalidos\n");
      return ERROR;
   }

   crypter_t crypter;
   crypter_init(&crypter, argv[2], argv[3]);
   server_t server;
   server_init(&server, argv[1]);
   server_connect(&server);

   server_run(&server, &crypter);

   server_uninit(&server);
   crypter_uninit(&crypter);

   return 0;
}
