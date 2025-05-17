#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

// Define função para limpar tela em maquinas Windows ou Linux / Mac 
#ifdef _WIN32
#include <conio.h>
#else
#define clrscr() printf("\e[1;1H\e[2J")
#endif




int main() {

    setlocale(LC_ALL, "Portuguese");

    FILE* arquivo = abreOuCriaArquivo();

    if (arquivo == NULL) {
        printf("Falha ao abrir o arquivo.");
        return -1;
    }

    
    return 0;
}
