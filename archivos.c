#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "cesar.h"

#include "socket.h"
#include "server.h"

//#include "encryptor.h"


#define ARRAY_SIZE(a) (sizeof(a)/sizeof(a[0]))

unsigned char S[256];


void swap(unsigned char *s, unsigned int i, unsigned int j) {
    unsigned char temp = s[i];
    s[i] = s[j];
    s[j] = temp;
}

/* KSA */
void rc4_init(unsigned char *key, unsigned int key_length) {
    
   unsigned int i, j;

    for (i = 0; i < 256; i++)
        S[i] = i;
 
    for (i = j = 0; i < 256; i++) {
        j = (j + key[i % key_length] + S[i]) & 255;
        swap(S, i, j);
    }
 
    i = j = 0;
}

/* PRGA */
unsigned char rc4_output() {
    i = (i + 1) & 255;
    j = (j + S[i]) & 255;

    swap(S, i, j);

    return S[(S[i] + S[j]) & 255];
}


int main(int argc, char *argv[]) {

   

    unsigned char *test_vectors[][2] = 
    {
        {"Key", "Plaintext"},
        {"Wiki", "pedia"},
        {"Secret", "Attack at dawn"}
    };
 
    printf("%s\n", test_vectors[0][0]);
    printf("%s\n", test_vectors[0][1]);
    printf("%s\n", test_vectors[1][0]);

   int x;
    for (x = 0; x < ARRAY_SIZE(test_vectors); x++) {
        int y;
        rc4_init(test_vectors[x][0], strlen((char*)test_vectors[x][0]));

        for (y = 0; y < strlen((char*)test_vectors[x][1]); y++)
            printf("%02X", test_vectors[x][1][y] ^ rc4_output());
        printf("\n");
    }













   FILE* fp;


   printf("%s\n", argv[1] + 9);

   char buffer[20];

  /* if(file_name != NULL){  // es siempre por stdin, esto esta de mas creo

      fp = fopen(file_name, "rb"); //binary?

   } else { 

      fp = stdin;
   }*/
   while(!feof(stdin)) {

      size_t result = fread(buffer, sizeof(char), sizeof(buffer), stdin);
      fwrite (buffer , sizeof(char), result, stdout);

   }

   printf("%zu", sizeof(char));
   return 0;
 }