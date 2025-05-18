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
void gerenciaUsuarios(FILE* bancoDeDados);
void gerenciaFilmes(FILE* bancoDeDados);
void gerenciaSeries(FILE* bancoDeDados);
void gerenciaDiretores(FILE* bancoDeDados);
void gerenciaCategorias(FILE* bancoDeDados);
void exibeMenuUsuarios();
void exibeMenuFilmes();
void exibeMenuSeries();
void exibeMenuDiretores();
void exibeMenuCategorias();


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

    int opcao;

    do {
        clrscr();
        exibeMenuPrincipal();
        scanf(" %d", &opcao);

        switch (opcao) {
            case 1:
                gerenciaUsuarios(bancoDeDados);
                break;
            case 2:
                gerenciaFilmes(bancoDeDados);
                break;
            case 3:
                gerenciaSeries(bancoDeDados);
                break;
            case 4:
                gerenciaDiretores(bancoDeDados);
                break;
            case 5:
                gerenciaCategorias(bancoDeDados);
                break;
            default:
                opcao = 0;
        }

    } while(opcao != 0);
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

void gerenciaUsuarios(FILE* bancoDeDados) {

    int opcao;

    do {
        clrscr();
        exibeMenuUsuarios();
        scanf(" %d", &opcao);

        switch(opcao) {
            default:
                break;
        }

    } while (opcao != 0);
}

void gerenciaFilmes(FILE* bancoDeDados) {

    int opcao;

    do {
        clrscr();
        exibeMenuFilmes();
        scanf(" %d", &opcao);

        switch(opcao) {
            default:
                break;
        }
        
    } while (opcao != 0);
}

void gerenciaSeries(FILE* bancoDeDados) {

    int opcao;

    do {
        clrscr();
        exibeMenuSeries();
        scanf(" %d", &opcao);

        switch(opcao) {
            default:
                break;
        }
        
    } while (opcao != 0);
}

void gerenciaDiretores(FILE* bancoDeDados) {

    int opcao;

    do {
        clrscr();
        exibeMenuDiretores();
        scanf(" %d", &opcao);

        switch(opcao) {
            default:
                break;
        }
        
    } while (opcao != 0);
}

void gerenciaCategorias(FILE* bancoDeDados) {

    int opcao;

    do {
        clrscr();
        exibeMenuCategorias();
        scanf(" %d", &opcao);

        switch(opcao) {
            default:
                break;
        }
        
    } while (opcao != 0);
}

void exibeMenuUsuarios() {
    printf("Gerenciador de Usuários\n\n\n");

    printf("Escolha uma opção:\n\n");
    
    printf("1 - Adicionar usuário\n");
    printf("2 - Buscar usuário\n");
    printf("3 - Listar usuários\n");
    printf("4 - Editar usuario\n");
    printf("5 - Deletar usuario\n\n");
    printf("0 - Voltar ao menu principal\n\n\n");

    printf("Opção desejada: ");
}

void exibeMenuFilmes() {
    printf("Gerenciador de Filmes\n\n\n");

    printf("Escolha uma opção:\n\n");
    
    printf("1 - Adicionar filme\n");
    printf("2 - Buscar filme\n");
    printf("3 - Listar filmes\n");
    printf("4 - Editar filme\n");
    printf("5 - Deletar filme\n\n");
    printf("0 - Voltar ao menu principal\n\n\n");

    printf("Opção desejada: ");
}

void exibeMenuSeries() {
    printf("Gerenciador de Séries\n\n\n");

    printf("Escolha uma opção:\n\n");
    
    printf("1 - Adicionar série\n");
    printf("2 - Buscar série\n");
    printf("3 - Listar séries\n");
    printf("4 - Editar série\n");
    printf("5 - Deletar série\n\n");
    printf("0 - Voltar ao menu principal\n\n\n");

    printf("Opção desejada: ");
}

void exibeMenuDiretores() {
    printf("Gerenciador de Diredores\n\n\n");

    printf("Escolha uma opção:\n\n");
    
    printf("1 - Adicionar diretor\n");
    printf("2 - Buscar diretor\n");
    printf("3 - Listar diretores\n");
    printf("4 - Editar diretor\n");
    printf("5 - Deletar diretor\n\n");
    printf("0 - Voltar ao menu principal\n\n\n");

    printf("Opção desejada: ");
}

void exibeMenuCategorias() {
    printf("Gerenciador de Categorias\n\n\n");

    printf("Escolha uma opção:\n\n");
    
    printf("1 - Adicionar categoria\n");
    printf("2 - Buscar categoria\n");
    printf("3 - Listar categorias\n");
    printf("4 - Editar categoria\n");
    printf("5 - Deletar categoria\n\n");
    printf("0 - Voltar ao menu principal\n\n\n");

    printf("Opção desejada: ");
}
