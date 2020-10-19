#include "crypter.h"

#define CESAR 0
#define VIGENERE 1
#define RC4 2

void _cesar_cipher(crypter_t* self, unsigned char* message, int size){

	int i = 0;
	for(i = 0; i < size; i++) {

		message[i] = message[i] + (self->N); 
	}
}

void _cesar_decipher(crypter_t* self, unsigned char* message, int size){

	int i = 0;
	for(i = 0; i < size; i++) {

		message[i] = message[i] - (self->N); 
	}
}

void _vigenere_cipher(crypter_t* self, unsigned char* message, int size){

	int i = 0;
	for(i = 0; i < size; i++) {

		message[i] = message[i] + self->vigenere_key[self->status];
		self->status++;

		if (self->status >= self->key_size) {
			self->status = 0;
		} 
	}

}

void _vigenere_decipher(crypter_t* self, unsigned char* message, int size){

}

void _rc4_cipher_decipher(crypter_t* self, unsigned char* message, int size){

}



int crypter_init(crypter_t* self, char* method, char* key){


	if(strcmp("--method=cesar", method) == 0){

		self->N = atoi(key);
		self->method = CESAR;
		return 0;

	} else if (strcmp("--method=vigenere", method) == 0) {

		self->status = 0;
		self->vigenere_key = key;
		self->method = VIGENERE;
		return 0;

	} else if (strcmp("--method=rc4", method) == 0) {

		self->i = 0;
		self->j = 0;
		self->rc4_key = key;
		self->method = RC4;
		return 0;
	} else {
		return -1;
	}

}

void crypter_cipher(crypter_t* self, unsigned char* message, int size) {

	if (self->method == CESAR) {

		_cesar_cipher(self, message, size);

	} else if (self->method == VIGENERE) {

		_vigenere_cipher(self, message, size);

	} else if (self->method == RC4) {

		_rc4_cipher_decipher(self, message, size);
	}
}

void crypter_decipher(crypter_t* self, unsigned char* message, int size){

	if (self->method == CESAR) {

		_cesar_decipher(self, message, size);

	} else if (self->method == VIGENERE) {

		_vigenere_decipher(self, message, size);

	} else if (self->method == RC4) {

		_rc4_cipher_decipher(self, message, size);
	}

}

void crypter_uninit(crypter_t* self){

}



void prueba(char* message) {

	printf("%zu", strlen(message));
}