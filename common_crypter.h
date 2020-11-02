#ifndef COMMON_CRYPTER_H_
#define COMMON_CRYPTER_H_

#define CESAR 0
#define VIGENERE 1
#define RC4 2

typedef struct {
	int method;
	int key_size;
	// Cesar
	int N;
	// Vigenere
	int status;
	char* vigenere_key;
	// RC4
	int i, j;
	unsigned char S[256];
	unsigned char* rc4_key;
} crypter_t;

/* Constructor */
int crypter_init(crypter_t* self, char* method, char* key);

/* Cifra los primeros "size" bytes de message de acuerdo a "self", que es el que contiene
 * la informacion para el cifrado */
void crypter_cipher(crypter_t* self, unsigned char* message, int size);

/* Descifra los primeros "size" bytes de message de acuerdo a "self", que es el que contiene
 * la informacion para el descifrado */
void crypter_decipher(crypter_t* self, unsigned char* message, int size);

/* Destructor */
void crypter_uninit(crypter_t* self);

#endif  // COMMON_CRYPTER_H_
