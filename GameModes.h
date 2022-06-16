#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifdef _WIN32 
    #include <Windows.h> 
    #define CLEAN "cls"
#else 
    #include <unistd.h> 
    #define CLEAN "clear"
#endif

#define ORG 'X'
#define VAZ '.'
#define TAM 101

void inicBlinker(char **m, int nL, int nC); // Apenas as inicializações
void inicBloco(char **m, int nL, int nC);
void inicSapo(char **m, int nL, int nC);
void inicGlider(char **m, int nL, int nC);
void inicLWSS(char **m, int nL, int nC);
void inic(char **m, int nL, int nC, char *modo);
