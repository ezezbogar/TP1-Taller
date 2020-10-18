#include "cesar.h"
#include <stdio.h>

int cesar_cipher(unsigned char* string, int key, int lenght) {

	int i = 0;

	while (i < lenght) {
		string[i] = string[i] + key;
		i++;
	}

	return 0;
}

int cesar_decipher(unsigned char* string, int key, int lenght) {

	int i = 0;

	while (i < lenght) {
		string[i] = string[i] - key;
		i++;
	}

	return 0;
}
