#include <stdio.h>
#include <stdbool.h>
#include <string.h>


#include "cesar.h"

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

   /*printf("%s\n", msg);






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

   */
	return 0;
 }