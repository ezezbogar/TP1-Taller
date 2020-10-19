#include <stdio.h>
#include <stdbool.h>
#include <string.h>


#include "cesar.h"

#include "socket.h"
#include "server.h"

#include "crypter.h"

#define BUFFER_SIZE 32

int main(int argc, char *argv[]) {

   server_t server;
   
   server_init(&server, argv[1]);

   server_connect(&server);

   server_recieve(&server, msg, 20);

   server_uninit(&server);

   printf("%s\n", msg);

   char buffer[64];

   while(!feof(stdin)) {

      size_t result = fread(buffer, sizeof(char), sizeof(buffer), stdin);
      fwrite (buffer , sizeof(char), result, stdout);

   }


   char msg[30];

   printf("%zu\n", strlen(argv[1]));

   char cosa[] = "messi flexi\0";
   for(int i =0; i<20; i++) {
      msg[i] = 'a';
   }
   printf("%s\n", msg);

   printf("%d\n", (int)strlen(msg));

   printf("%s\n", cosa);

   printf("%d\n", (int)strlen(cosa));

   prueba(msg);
  

	return 0;
 }