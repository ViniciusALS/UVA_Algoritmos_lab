/*
    Projeto A4 da disciplina de algoritmos do professor Lazaro de Oliveira

    Grupo:  Igor Sousa Alves    - 1240207519
            Kamilla Lucas Tré   - 1230106915
            Thalles Henriques   - 1240114928
            Vinícius de Azevedo - 1240201902
*/

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
void sistemaLocadora(FILE* bancoDeDados);
void exibeMenuPrincipal();


int main() {

    setlocale(LC_ALL, "Portuguese");

    FILE* bancoDeDados = abreOuCriaArquivo("locadora_digital.txt");

    if (bancoDeDados == NULL) {
        printf("Falha ao abrir o arquivo.");
        return -1;
    }

    sistemaLocadora(bancoDeDados);

    return 0;
}

FILE* abreOuCriaArquivo(char* nomeArquivo) {
    return fopen(nomeArquivo, "a+"); 
}

void sistemaLocadora(FILE* bancoDeDados) {

    clrscr();
    
    exibeMenuPrincipal();
    
}

void exibeMenuPrincipal() {
    printf("Locadora Digital Veiga de Almeida\n\n");

    printf("Escolha uma opção:\n\n");
    
    printf("1 - Gerenciar usuários\n");
    printf("2 - Gerenciar filmes\n");
    printf("3 - Gerenciar séries\n");
    printf("4 - Gerenciar diretores\n");
    printf("5 - Gerenciar categorias\n\n");
    printf("0 - Encerrar programa\n\n\n");

    printf("Opção desejada: ");
}
