#ifndef CRYPTER_H
#define CRYPTER_H

#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define CESAR 0
#define VIGENERE 1
#define RC4 2

typedef struct {

	int method;
	int key_size;
	//Cesar
	int N;
	//Vigenere
	int status;
	char* vigenere_key;
	//RC4
	int i,j;
	unsigned char S[256];
	unsigned char* rc4_key;

} crypter_t;

int crypter_init(crypter_t* self, char* method, char* key);

void crypter_cipher(crypter_t* self, unsigned char* message, int size);

void crypter_decipher(crypter_t* self, unsigned char* message, int size);

void crypter_uninit(crypter_t* self);

#endif //CRYPTER_H