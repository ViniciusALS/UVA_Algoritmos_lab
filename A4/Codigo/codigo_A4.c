/**************************************************
 
    Projeto da A4 da disciplina de algoritmos 
    do professor Lazaro de Oliveira

    Grupo:  Igor Sousa Alves    - 1240207519
            Kamilla Lucas Tré   - 1230106915
            Thalles Henriques   - 1240114928
            Vinícius de Azevedo - 1240201902

***************************************************/


////////////// IMPORTA BIBLIOTECAS ////////////////

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>



//////////// DEFINE MACROS E TIPOS ////////////////

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

typedef enum {
    VOLTAR_MENU_PRINCIPAL,
    LISTAR_TODAS_VENDAS,
    LISTAR_VENDAS_POR_DATA
} OpcaoMenuRelatorios;

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



///////////////// DECLARA FUNÇÕES /////////////////

void sistemaLoja();
void exibeMenu();
void processaMenu(OpcaoMenu opcao);
void iniciaDiaDeVenda();
void apresentaRelatorios();
void exibePedidoPorData();
Data recebeDataAtual();
void salvaDataAoArquivo(Data data);
void exibeMenuDiaDeVenda();
void processaMenuDiaDeVenda(OpcaoMenuDiaDeVenda opcao);
void adicionaItemNovo();
void registraNovoCliente();
void salvaClienteNovoAoArquivo();
void exibeMenuVendaCliente();
void processaMenuVendaCliente(OpcaoMenuVendaCliente opcao);
Venda recebeInformacoesDaVenda();
void salvaVendaAoArquivo(Venda venda);
float calculaPrecoTotal(Venda venda);
void exibeMenuDeRelatorios();
int contaNumeroDeClientesPorDia(Data data);
char* converteDataEmString(Data data);
char* extraiTextoDoArquivo(char* buffer);
int determinaTamanhoDoArquivo(FILE* arquivo);
void escreveEmArquivo(char* texto);
FILE* abreArquivo();
void limpaTela();
int recebeOpcao();
void movePtrParaInicioDoArquivo(FILE* arquivo);
void movePtrParaFimDoArquivo(FILE* arquivo);



////////////////////// MAIN ///////////////////////

int main() {

    setlocale(LC_ALL, "Portuguese");

    sistemaLoja();
    
    return 0;
}



////////////////// DEFINE FUNÇÕES /////////////////

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

    printf("Loja de Roupas Veiga de Almeida\n\n\n");

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
        apresentaRelatorios();
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


void apresentaRelatorios() {

    int opcao;

    do {
        exibeMenuDeRelatorios();
        opcao = recebeOpcao();
        processaMenuRelatorios(opcao);
    } while(opcao != VOLTAR_MENU_PRINCIPAL);
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


void salvaDataAoArquivo(Data data) {
    char texto[TAMANHO_MAX_STRING] = converteDataEmString(data);
    escreveEmArquivo(texto);
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
        registraNovoCliente();
}


void registraNovoCliente() {
    salvaClienteNovoAoArquivo();    

    OpcaoMenuVendaCliente opcao;

    do {
        exibeMenuVendaCliente();
        opcao = recebeOpcao();
        processaMenuVendaCliente(opcao);
    } while(opcao != ENCERRAR_VENDAS_DE_CLIENTE);
}


void salvaClienteNovoAoArquivo() {
    char texto[] = "\nCLIENTE NOVO\n";
    escreveEmArquivo(texto);
}


void exibeMenuVendaCliente() {
    limpaTela();
    printf("Escolha uma opcão: \n\n");

    printf("1 - Adicionar nova venda de item. \n");
    printf("0 - Encerrar vendas do cliente. \n\n");

    printf("Opção desejada: ");
}


void processaMenuVendaCliente(OpcaoMenuVendaCliente opcao) {
    if (opcao == ADICIONAR_ITEM) 
        adicionaItemNovo();
}


void adicionaItemNovo() {
    Venda venda;
    
    venda = recebeInformacoesDaVenda();

    salvaVendaAoArquivo(venda);
}


Venda recebeInformacoesDaVenda() {
    Venda venda;

    limpaTela();
    
    printf("Digite o código do item: ");
    scanf(" %[^\n]", venda.codigoItem);

    printf("Digite o nome do item: ");
    scanf(" %[^\n]", venda.nomeItem);

    printf("Digite a marca do item: ");
    scanf(" %[^\n]", venda.marcaItem);

    printf("Digite a quantidade de items: ");
    scanf(" %d", &venda.quantidadeItem);

    printf("Digite o preço unitário do item: ");
    scanf(" %f", &venda.precoUnitarioItem);

    venda.precoTotal = calculaPrecoTotal(venda);

    return venda;
}


void salvaVendaAoArquivo(Venda venda) {
    char texto[250];
    
    sprintf(texto, 
        "%s, %s, %s, %d, %.2f, %.2f \n", 
        venda.codigoItem,
        venda.nomeItem, 
        venda.marcaItem, 
        venda.quantidadeItem, 
        venda.precoUnitarioItem, 
        venda.precoTotal);

    escreveEmArquivo(texto);
}


float calculaPrecoTotal(Venda venda) {
    float precoTotal = venda.precoUnitarioItem * venda.quantidadeItem;

    // TODO: Tirar duvida com professor se o desconto é aplicado na venda de produtos do mesmo tipo 
    if (venda.quantidadeItem >= 3)
        precoTotal *= 0.9;

    return precoTotal;
}


void exibeMenuDeRelatorios() {
    limpaTela();
    printf("Escolha o relatório que deseja ver: \n\n");

    printf("1 - Listar todas as vendas. \n");
    printf("2 - Lister vendas por dia. \n");
    printf("0 - Voltar ao menu principal. \n\n");

    printf("Opção desejada: ");
}


int contaNumeroDeClientesPorDia(Data data) {
    int numeroDeClientes = 0;

    char stringData[TAMANHO_MAX_STRING] = converteDataEmString(data);
    char* textoArquivo;
    
    extraiTextoDoArquivo(textoArquivo);

    char* tempSubstringArquivo = strstr(tempSubstringArquivo, stringData);

    if (tempSubstringArquivo != NULL) {
        
        while(tempSubstringArquivo = strstr(tempSubstringArquivo, "CLIENTE NOVO")) {
            numeroDeClientes++;
            tempSubstringArquivo++;
        }
    }

    free(textoArquivo);
    return numeroDeClientes;
}


char* converteDataEmString(Data data) {
    char texto[TAMANHO_MAX_STRING];
    sprintf(texto, "\n\nDATA: %02d/%02d/%04d \n", data.dia, data.mes, data.ano);
    return texto;
}


char* extraiTextoDoArquivo(char* buffer) {

    FILE* arquivo = abreArquivo();

    if (arquivo != NULL) {
        
        int tamanhoArquivo = determinaTamanhoDoArquivo(arquivo);

        buffer = malloc(tamanhoArquivo);

        if (buffer) 
            fread(buffer, 1, tamanhoArquivo, arquivo);

        fclose(arquivo);
    }

    return buffer;
}


int determinaTamanhoDoArquivo(FILE* arquivo) {

    movePtrParaFimDoArquivo(arquivo);
    int tamanhoDoArquivo = ftell(arquivo);
    movePtrParaInicioDoArquivo(arquivo);

    return(tamanhoDoArquivo);
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


void limpaTela() {
    printf("\e[H\e[2J\e[3J");
}


int recebeOpcao() {
    int opcao;
    scanf(" %d", &opcao);
    return opcao;
}


void movePtrParaInicioDoArquivo(FILE* arquivo) {
    rewind(arquivo);
}


void movePtrParaFimDoArquivo(FILE* arquivo) {
    fseek(arquivo, 0, SEEK_END);
}
