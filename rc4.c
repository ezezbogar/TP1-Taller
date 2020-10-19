


void swap(unsigned char *s, unsigned int i, unsigned int j) {
    unsigned char temp = s[i];
    s[i] = s[j];
    s[j] = temp;
}

/* KSA */
void rc4_init(unsigned char *key, unsigned int key_length, unsigned char *S, 
            unsigned int i, unsigned int j) {
    for (i = 0; i < 256; i++)
        S[i] = i;
 
    for (i = j = 0; i < 256; i++) {
        j = (j + key[i % key_length] + S[i]) & 255;
        swap(S, i, j);
    }
 
    i = j = 0;
}
 
/* PRGA */
unsigned char rc4_output(unsigned char* S, unsigned int* i, unsigned int* j) {
    *i = (*i + 1) & 255;
    *j = (*j + S[*i]) & 255;

    swap(S, *i, *j);

    return S[(S[*i] + S[*j]) & 255];
}
 
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define ARRAY_SIZE(a) (sizeof(a)/sizeof(a[0]))

int main() {

    unsigned int i = 0;
    unsigned int j = 0;
    unsigned char S[256];


    unsigned char message[10];

    message[0]=187;
    message[1]=243;
    message[2]=22;
    message[3]=232;
    message[4]=217;
    message[5]=64;
    message[6]=175;
    message[7]=10;
    message[8]=211;

    //unsigned char message[] = "Plaintext";
    unsigned char key[] = "Key";
    
    printf("%zu\n", strlen((char*)message));
    
    rc4_init(key, strlen((char*)key), S, i, j);

    int y;
    for (y = 0; y < strlen((char*)message); y++) {

        printf("%d ", message[y] ^ rc4_output(S, &i, &j));
    }

    printf("\n");
    getc(stdin);

    char w = 'a';

    printf("%u", (unsigned char)w);
    printf("%d", (int)w);
    return 0;
}