#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

// Define função para limpar tela em maquinas Windows ou Linux / Mac 
#ifdef _WIN32
#include <conio.h>
#else
#define clrscr() printf("\e[1;1H\e[2J")
#endif


#define TAMANHO_STRING 50

FILE* abreOuCriaArquivo();
void moveParaInicioDoArquivo(FILE* arquivo);
void moveParaFimDoArquivo(FILE* arquivo);
void sistemaLoja(FILE* lojaBD);
OpcoesMenu exibeMenu();
void iniciaNovoDiaDeVenda(Venda listaDeVendas[]);


typedef struct venda {
    char nomeCliente[TAMANHO_STRING];
    int diaDaVenda;
    int mesDaVenda;
    int anoDaVenda;
    char codigoItem[TAMANHO_STRING];
    char nomeItem[TAMANHO_STRING];
    char marcaItem[TAMANHO_STRING];
    int quantidadeItem;
    float precoUnitarioItem;
} Venda;

typedef enum opcoesMenu {
    SAIR,
    INICIAR_DIA
} OpcoesMenu;

typedef enum opcoesRegistro {
    VOLTAR,
    CONTINUAR
} OpcoesRegistro;



int main() {

    setlocale(LC_ALL, "Portuguese");

    FILE* arquivo = abreOuCriaArquivo();

    if (arquivo == NULL) {
        printf("Falha ao abrir o arquivo.");
        return -1;
    }

    sistemaLoja(arquivo);
    
    return 0;
}


FILE* abreOuCriaArquivo() {
    return fopen("loja_roupa.txt", "a+"); 
}

// void moveParaInicioDoArquivo(FILE* arquivo) {
//     rewind(arquivo);
// }

// void moveParaFimDoArquivo(FILE* arquivo) {
//     fseek(arquivo, 0, SEEK_END);
// }

void sistemaLoja(FILE* lojaBD) {

    Venda listaDeVendas[50];

    while(1) {    
        OpcoesMenu opcao = exibeMenu();

        switch (opcao) {
            case INICIAR_DIA:
                iniciaNovoDiaDeVenda(listaDeVendas);
                break;
            
            case SAIR:
            default:
                return;
        }
    }
}

OpcoesMenu exibeMenu() {

    OpcoesMenu opcao;

    clrscr();

    printf("Loja de roupas Veiga de Almeida\n\n\n");

    printf("Escolha o que você deseja fazer: \n\n");

    printf("1 - Iniciar dia de venda \n");
    printf("0 - Sair do programa \n\n");

    printf("Opção desejada: ");
    scanf(" %d", &opcao);

    return opcao;
}

void iniciaNovoDiaDeVenda(Venda listaDeVendas[]) {

    int dia, mes, ano;
    
    clrscr();

    printf("Entre com a data do dia (dd/mm/aaaa): ");
    scanf(" %d/%d/%d", &dia, &mes, &ano);

    clrscr();

    while(1) {

        OpcoesRegistro opcao;

        printf("Escolha uma opcão: \n\n");

        printf("1 - Registrar novo cliente. \n");
        printf("0 - Terminar dia de venda. \n\n");

        printf("Opção desejada: ");
        scanf(" %d", &opcao);

        if (opcao == VOLTAR)
            return;

        while(1) {
            char nomeCliente[50];

            clrscr();

            printf("Nome do cliente: ");
            scanf("%s", nomeCliente);

            
        }

    }
}
