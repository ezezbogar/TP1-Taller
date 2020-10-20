#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "socket.h"
#include "server.h"
#include "crypter.h"

int main(int argc, char *argv[]) {


  //char msg[] = "Plaintext"; //unsigned char????
  //char msg[] = "pedia";


  char msg[9];
  msg[0]='P';
  msg[1]='l';
  msg[2]='a';
  msg[3]='i';
  msg[4]='n';
  msg[5]='t';
  msg[6]='e';
  msg[7]='x';
  msg[8]='t';

  int i;

  printf("%s\n", msg);
  printf("%zu\n", strlen(msg));

  crypter_t crypter;
  crypter_init(&crypter, argv[1], argv[2]);

  crypter_cipher(&crypter, msg, strlen(msg));

  printf("%s\n", msg);

  /*i = atoi(argv[1] + 6);

  char* key = argv[1] + 6;

  printf("%s\n", key);
  printf("%zu\n", strlen(key));
  printf("%d\n", i);

  */

  printf("final:\n");

  for(i = 0; i< strlen(msg); i++) {

    printf("%02X ", (unsigned char)msg[i]);
  }
  printf("\n");

  crypter_t crypter2;
  crypter_init(&crypter2, argv[1], argv[2]);
  crypter_decipher(&crypter2, msg, strlen(msg));

  printf("%s\n", msg);
  printf("\n");

  for(i = 0; i< strlen(msg); i++) {

    printf("%02X ", (unsigned char)msg[i]);
  }

  printf("\n");


   return 0;
 }