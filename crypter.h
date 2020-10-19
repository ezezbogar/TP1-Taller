#ifndef CLIENT_H
#define CLIENT_H

#include "socket.h"

#define CESAR 0
#define VIGENERE 1
#define RC4 2

typedef struct {

	int method;
	//Cesar
	int N;
	//Vigenere
	int status;
	char* vigenere_key;
	int key_size;
	//RC4
	int i,j;
	unsigned char S[256];
	unsigned char* rc4_key;

} crypter_t;

int crypter_init(crypter_t* self, char* method, char* key);

void crypter_cipher(crypter_t* self, unsigned char* message, int size);

void crypter_decipher(crypter_t* self, unsigned char* message, int size);

void crypter_uninit(crypter_t* self);

void prueba(char* message);


#endif //CLIENT_H

