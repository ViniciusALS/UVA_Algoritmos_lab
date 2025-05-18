#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

// Define função para limpar tela em maquinas Windows ou Linux / Mac 
#ifdef _WIN32
#include <conio.h>
#else
#define clrscr() printf("\e[1;1H\e[2J")
#endif

FILE* abreOuCriaArquivo(char* nomeArquivo);


int main() {

    setlocale(LC_ALL, "Portuguese");

    FILE* bancoDeDados = abreOuCriaArquivo("locadora_digital.txt");

    if (bancoDeDados == NULL) {
        printf("Falha ao abrir o arquivo.");
        return -1;
    }

    
    return 0;
}

FILE* abreOuCriaArquivo(char* nomeArquivo) {
    return fopen(nomeArquivo, "a+"); 
}
