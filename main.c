#include <stdio.h>
#include <stdbool.h>
#include <string.h>


#include "cesar.h"

#include "socket.h"
#include "server.h"


int main(int argc, char *argv[]) {


   char msg[10];
   for(int i =0; i<10; i++) {
      msg[i] = 'a';
   }
   printf("%s\n", msg);

   server_t server;
	
   server_init(&server, argv[1]);

   server_connect(&server);

   server_recieve(&server, msg, 10);

   server_uninit(&server);

   printf("%s\n", msg);

	return 0;
 }