#include <stdio.h>
#include <stdbool.h>
#include <string.h>


#include "cesar.h"

#include "socket.h"
#include "client.h"


int main(int argc, char *argv[]) {


   char msg[] = "messi flexi";

   printf("%s\n", msg);
   printf("%i\n", (int)strlen(msg));

   client_t client;

   client_init(&client, argv[1], argv[2]);
   client_connect(&client);
   client_send(&client, msg, 11);
   client_uninit(&client);

	return 0;
 }