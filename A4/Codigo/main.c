/*
    Projeto de Extensão da disciplina de algoritmos do professor Lazaro de Oliveira

    Grupo:  Igor Sousa Alves    - 1240207519
            Kamilla Lucas Tré   - 1230106915
            Thalles Henriques   - 1240114928
            Vinícius de Azevedo - 1240201902
*/

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>


#define TAMANHO_MAX_STRING 50
#define NOME_ARQUIVO "loja_roupa.txt"

typedef enum {
    SAIR,
    INICIAR_DIA,
    APRESENTAR_RELATORIO
} OpcaoMenu;

typedef enum {
    TERMINAR,
    REGISTRAR_CLIENTE
} OpcaoMenuDiaDeVenda;

typedef enum {
    ENCERRAR_VENDAS_DE_CLIENTE,
    ADICIONAR_ITEM
} OpcaoMenuVendaCliente;

typedef struct {
    int dia;
    int mes;
    int ano;
} Data;

typedef struct {
    char codigoItem[TAMANHO_MAX_STRING];
    char nomeItem[TAMANHO_MAX_STRING];
    char marcaItem[TAMANHO_MAX_STRING];
    int quantidadeItem;
    float precoUnitarioItem;
    float precoTotal;
} Venda;

// void moveParaInicioDoArquivo(FILE* arquivo);
// void moveParaFimDoArquivo(FILE* arquivo);
void sistemaLoja();
void limpaTela();
void exibeMenu();
int recebeOpcao();
void processaMenu(OpcaoMenu opcao);
void iniciaDiaDeVenda();
void exibePedidoPorData();
Data recebeDataAtual();
void exibeMenuDiaDeVenda();
void processaMenuDiaDeVenda(OpcaoMenuDiaDeVenda opcao);
void exibeMenuVendaCliente();
void processaMenuVendaCliente(OpcaoMenuVendaCliente opcao);
Venda recebeInformacoesDaVenda();
float calculaPrecoTotal(Venda venda);
void salvaVendaAoArquivo(Venda venda);
void salvaClienteNovoAoArquivo();
void salvaDataAoArquivo(Data data);
void escreveEmArquivo(char* texto);
FILE* abreArquivo();
void registraVendaCliente();


int main() {

    setlocale(LC_ALL, "Portuguese");

    sistemaLoja();
    
    return 0;
}


// void moveParaInicioDoArquivo(FILE* arquivo) {
//     rewind(arquivo);
// }

// void moveParaFimDoArquivo(FILE* arquivo) {
//     fseek(arquivo, 0, SEEK_END);
// }

void sistemaLoja() {

    OpcaoMenu opcao;

    do {    
        exibeMenu();
        opcao = recebeOpcao();
        processaMenu(opcao);
    } while(opcao != SAIR);
}


void exibeMenu() {
    limpaTela();

    printf("Loja de roupas Veiga de Almeida\n\n\n");

    printf("Escolha o que você deseja fazer: \n\n");

    printf("1 - Iniciar dia de venda \n");
    printf("2 - Apresentar relatório \n");
    printf("0 - Sair do programa \n\n");

    printf("Opção desejada: ");
}


void processaMenu(OpcaoMenu opcao) {
    if (opcao == INICIAR_DIA)
        iniciaDiaDeVenda();

    if (opcao == APRESENTAR_RELATORIO) 
        return; // Apresenta relatorio
}


void iniciaDiaDeVenda() {

    exibePedidoPorData();    
    Data dataAtual = recebeDataAtual();
    salvaDataAoArquivo(dataAtual);

    OpcaoMenuDiaDeVenda opcao;

    do {
        exibeMenuDiaDeVenda();
        opcao = recebeOpcao();
        processaMenuDiaDeVenda(opcao);
    } while(opcao != TERMINAR);
}


void exibePedidoPorData() {
    limpaTela();
    printf("Entre com a data de hoje (dd/mm/aaaa): ");
}


Data recebeDataAtual() {
    Data dataAtual;
    scanf(" %d/%d/%d", &dataAtual.dia, &dataAtual.mes, &dataAtual.ano);
    return dataAtual;
}


void exibeMenuDiaDeVenda() {
    limpaTela();
    printf("Escolha uma opcão: \n\n");

    printf("1 - Registrar novo cliente. \n");
    printf("0 - Terminar dia de venda. \n\n");

    printf("Opção desejada: ");
}


void processaMenuDiaDeVenda(OpcaoMenuDiaDeVenda opcao) {
    if (opcao == REGISTRAR_CLIENTE)
        registraVendaCliente();
}


void registraVendaCliente() {
    salvaClienteNovoAoArquivo();    

    OpcaoMenuVendaCliente opcao;

    do {
        exibeMenuVendaCliente();
        opcao = recebeOpcao();
        processaMenuVendaCliente(opcao);
    } while(opcao != ENCERRAR_VENDAS_DE_CLIENTE);
}


void exibeMenuVendaCliente() {
    limpaTela();
    printf("Escolha uma opcão: \n\n");

    printf("1 - Adicionar nova venda de item. \n");
    printf("0 - Encerrar vendas do cliente. \n\n");

    printf("Opção desejada: ");
}


void processaMenuVendaCliente(OpcaoMenuVendaCliente opcao) {
    if (opcao == ADICIONAR_ITEM) {
        Venda venda = recebeInformacoesDaVenda();
    }
}


Venda recebeInformacoesDaVenda() {
    Venda venda;

    limpaTela();
    
    printf("Digite o código do item: ");
    scanf(" %[^\n]", venda.codigoItem);

    printf("Digite o nome do item:");
    scanf(" %[^\n]", venda.nomeItem);

    printf("Digite a marca do item: ");
    scanf(" %[^\n]", venda.marcaItem);

    printf("Digite a quantidade de items: ");
    scanf(" %d", venda.quantidadeItem);

    printf("Digite o preço unitário do item: ");
    scanf(" %.2f", venda.precoUnitarioItem);

    venda.precoTotal = calculaPrecoTotal(venda);

    return venda;
}

float calculaPrecoTotal(Venda venda) {
    float precoTotal = venda.precoUnitarioItem * venda.quantidadeItem;

    // TODO: Tirar duvida com professor se o desconto é aplicado na venda de produtos do mesmo tipo 
    if (venda.quantidadeItem >= 3)
        precoTotal *= 0.9;

    return precoTotal;
}

void salvaVendaAoArquivo(Venda venda) {
    char texto[250];
    sprintf(texto, "%s, %s, %s, %d, %.2f, %.2f \n");
    escreveEmArquivo(texto);
}


void limpaTela() {
    printf("\e[H\e[2J\e[3J");
}


int recebeOpcao() {
    int opcao;
    scanf(" %d", &opcao);
    return opcao;
}


void salvaClienteNovoAoArquivo() {
    char texto[] = "CLIENTE NOVO\n";
    escreveEmArquivo(texto);
}


void salvaDataAoArquivo(Data data) {
    char texto[20];
    sprintf(texto, "DATA: %d/%d/%d \n\n", data.dia, data.mes, data.ano);
    escreveEmArquivo(texto);
}


void escreveEmArquivo(char* texto) {

    FILE* arquivo = abreArquivo();

    int resultadoEscrita = fputs(texto, arquivo);

    if (resultadoEscrita == EOF) {
        limpaTela();
        printf("Erro ao tentar escrever. \n\n");
    }

    fclose(arquivo);
}


FILE* abreArquivo() {
    FILE* arquivo = fopen(NOME_ARQUIVO, "a+");

    if (arquivo == NULL) {
        limpaTela();
        printf("Erro ao tentar abrir o arquivo \n\n");
    }

    return arquivo;
}
