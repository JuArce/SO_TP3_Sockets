#ifndef SO_TP3_SOCKETS_CHALLENGES_H
#define SO_TP3_SOCKETS_CHALLENGES_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TOTAL_CHALLENGES 12

typedef int (*challenge)(char *, size_t, FILE *);

int challenge1(char *answer, size_t n, FILE *serverInput);

int challenge2(char *answer, size_t n, FILE *serverInput);

int challenge3(char *answer, size_t n, FILE *serverInput);

int challenge4(char *answer, size_t n, FILE *serverInput);

int challenge5(char *answer, size_t n, FILE *serverInput);

int challenge6(char *answer, size_t n, FILE *serverInput);

int challenge7(char *answer, size_t n, FILE *serverInput);

int challenge8(char *answer, size_t n, FILE *serverInput);

int challenge9(char *answer, size_t n, FILE *serverInput);

int challenge10(char *answer, size_t n, FILE *serverInput);

int challenge11(char *answer, size_t n, FILE *serverInput);

int challenge12(char *answer, size_t n, FILE *serverInput);

#endif //SO_TP3_SOCKETS_CHALLENGES_H
