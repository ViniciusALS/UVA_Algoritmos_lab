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

#ifdef _WIN32
#define limpaTela() system("cls")
#else
#define limpaTela() printf("\e[1;1H\e[2J")
#endif

#define NOME_ARQUIVO "loja_roupa.bin"
#define TAMANHO_MAX_STRING 50


typedef enum OrdemDeListagem {
    ORDEM_DECRESCENTE,
    ORDEM_DE_REGISTRO,
    ORDEM_CRESCENTE
} OrdemDeListagem;


typedef struct Data {
    int dia;
    int mes;
    int ano;
} Data;


typedef struct Item {
    char codigo[TAMANHO_MAX_STRING];
    char nome[TAMANHO_MAX_STRING];
    char marca[TAMANHO_MAX_STRING];
    int quantidade;
    float precoUnitario;
    float precoTotal;
} Item;


typedef struct Venda {
    int id;
    Data data;
    char nomeCliente[TAMANHO_MAX_STRING];
    Item item;
} Venda;



///////////////// DECLARA FUNÇÕES /////////////////

void registraNovoDiaDeVenda();  
void registrarCliente(Data dataDeVenda);                                              
void registraItem(Data dataDeVenda, char nomeCliente[]); 
Item recebeInformacoesDoItem(); 
Venda criaVenda(Data data, char* nomeCliente, Item item); 
void salvaVendaEmArquivo(Venda venda); 
void exibeRelatorios();                                      
void listaTodasAsVendas(OrdemDeListagem ordem); 
int calculaNumeroDeVendasTotais(); 
void retornaTodasAsVendas(int numeroDeVendas, Venda* listaDeVendas); 
void listaVendasPorData(Data dataDeConsulta, OrdemDeListagem ordem); 
int calculaNumeroDeVendasPorData(Data dataDeConsulta); 
void retornaVendasPorData(int numeroDeVendas, Venda* listaDeVendas, Data dataDeConsulta); 
int comparaDatas(Data a, Data b); 
void listaVendasPorCliente(char nomeCliente[], OrdemDeListagem ordem); 
int calculaNumeroDeVendasPorCliente(char nomeCliente[]); 
void retornaVendasPorCliente(int numeroDeVendas, Venda* listaDeVendas, char nomeCliente[]); 
Venda* criaListaDeVendas(int tamanhoDaLista); 
void imprimeLista(Venda listaDeVendas[], int quantidadeDeVendas, OrdemDeListagem ordem); 
float calculaFaturamentoTotal(Venda* listaDeVendas, int quantidadeDeVendas); 
int contaNumeroClientes(Venda* listaDeVendas, int quantidadeDeVendas); 
void quickSort(Venda listaDeVendas[], int tamanhoDaLista); 
void quickSortAxiliar(Venda vendas[], int limiteInferior, int limiteSuperior);
int particiona(Venda vendas[], int limiteInferior, int limiteSuperior); 
void trocaVendas(Venda* a, Venda* b);
void inverteLista(Venda lista[], int tamanhoDaLista); 
Venda determinaVendaDoItemMaisVendido(Venda* listaDeVendas, int quantidadeDeVendas); 
Venda determinaVendaDoItemMenosVendido(Venda* listaDeVendas, int quantidadeDeVendas);
Data recebeData();              
OrdemDeListagem recebeOrdemDeListagem();
void editaVenda();           
float calculaPrecoTotalDeProduto(int quantidadeDeProdutos, float precoUnitarioDoProduto); 
void deletaVenda();             
void esperaPorInputDoUsuario(); 



////////////////////// MAIN ///////////////////////

int main() {

    setlocale(LC_ALL, "Portuguese");

    int opcao;
    do {    
        limpaTela();
        printf("Loja de Roupas Veiga de Almeida\n\n");

        printf("Donos da Loja: \n");
        printf("Igor Sousa Alves \t- 1240207519 \n");
        printf("Kamilla Lucas Tré \t- 1230106915 \n");
        printf("Thalles Henriques \t- 1240114928 \n");
        printf("Vinícius de Azevedo \t- 1240201902 \n\n\n");

        printf("Escolha o que você deseja fazer: \n\n");

        printf("1 - Registrar novo dia de venda \n");
        printf("2 - Exibir relatórios \n");
        printf("3 - Editar venda \n");
        printf("4 - Deletar venda \n");
        printf("0 - Sair do programa \n\n");

        printf("Opção desejada: ");
        scanf(" %d", &opcao);

        switch (opcao) {
            case 1:
                registraNovoDiaDeVenda();
                break;
            
            case 2:
                exibeRelatorios();
                break;

            case 3:
                editaVenda();
                break;

            case 4:
                deletaVenda();
                break;
        }
    } while(opcao != 0);
    
    return 0;
}



////////////////// DEFINE FUNÇÕES /////////////////

void registraNovoDiaDeVenda() {
    limpaTela();
    printf("Iniciando novo dia de vendas. \n\n");
    
    Data dataDeVenda = recebeData();

    int opcao;
    do {
        limpaTela();
        printf("Registro de vendas do dia: %02d/%02d/%04d \n\n\n", 
            dataDeVenda.dia, dataDeVenda.mes, dataDeVenda.ano);

        printf("Selecione uma opção: \n\n");
        printf("1 - Registrar novo cliente \n");
        printf("0 - Voltar ao menu principal \n\n");
        
        printf("Opção desejada: ");
        scanf(" %d", &opcao);

        switch (opcao) {
            case 1:
                registrarCliente(dataDeVenda);
                break;
        }
    } while(opcao != 0);

    // Exibe relatório sobre o dia ao final de cada dia de venda
    listaVendasPorData(dataDeVenda, ORDEM_CRESCENTE);
}


void registrarCliente(Data dataDeVenda) {
    limpaTela();
    printf("Entre com o nome do cliente: ");
    
    char nomeCliente[TAMANHO_MAX_STRING];
    scanf(" %[^\n]", nomeCliente);

    int opcao;
    do {
        limpaTela();

        printf("Registro de vendas para %s \n\n", nomeCliente);

        printf("Escolha uma opção: \n\n");
        printf("1 - Registrar novo item \n");
        printf("0 - Encerrar vendas de cliente e voltar ao menu anterior \n\n");

        printf("Opção desejada: ");
        scanf(" %d", &opcao);

        switch (opcao) {
            case 1:
                registraItem(dataDeVenda, nomeCliente);
                break;
        } 
    } while(opcao != 0);
}


void registraItem(Data dataDeVenda, char nomeCliente[]) {
    limpaTela();
    printf("Registro de item \n\n");
    
    Item novoItem = recebeInformacoesDoItem();

    novoItem.precoTotal = calculaPrecoTotalDeProduto(
            novoItem.quantidade, novoItem.precoUnitario);
    printf("O preço final dessa venda será: %.2f \n\n\n", novoItem.precoTotal);

    // Cria e salva vendas em arquivo binario ao fim de cada transação
    Venda novaVenda = criaVenda(dataDeVenda, nomeCliente, novoItem);
    salvaVendaEmArquivo(novaVenda);

    // Exibe relatório da quantidade de items vendidos no dia ao fim de cada transação
    printf("Quantidade de items vendidos no dia: %d \n\n\n", calculaNumeroDeVendasPorData(dataDeVenda));
    
    esperaPorInputDoUsuario();
}


Item recebeInformacoesDoItem() {
    Item item;

    printf("Insira o código do item: ");
    scanf(" %[^\n]", item.codigo);

    printf("Insira o nome do item: ");
    scanf(" %[^\n]", item.nome);

    printf("Insira a marca do item: ");
    scanf(" %[^\n]", item.marca);

    printf("Insira a quantidade do items: ");
    scanf(" %d", &item.quantidade);

    printf("Insira o preço unitário do item: ");
    scanf(" %f", &item.precoUnitario);

    return item;
}


Venda criaVenda(Data data, char* nomeCliente, Item item) {
    Venda venda;
    venda.id = 0;
    venda.data = data;
    strcpy(venda.nomeCliente, nomeCliente);
    venda.item = item;

    return venda;
}


void salvaVendaEmArquivo(Venda venda) {
    FILE* arquivo = fopen(NOME_ARQUIVO, "a+b");

    // Testa se arquivo foi aberto com sucesso
    if (arquivo == NULL) {
        printf("Erro: falha ao tentar abrir o arquivo. \n");
        exit(1);
    }

    int teveSucessoAoGravar = fwrite(&venda, sizeof(Venda), 1, arquivo);

    if (!teveSucessoAoGravar) {
        printf("Erro: Falha ao tentar gravar dados no arquivo. \n");
        exit(1);
    }

    fclose(arquivo);
}


void exibeRelatorios() {
    int opcao;
    do {
        limpaTela();

        printf("Relatorios da loja \n\n\n");

        printf("Escolha o relatório que deseja ver: \n\n");
        printf("1 - Listar todas as vendas \n");
        printf("2 - Listar vendas por dia \n");
        printf("3 - Listar vendas por cliente \n");
        printf("0 - Voltar ao menu principal \n\n");

        printf("Escolha desejada: ");
        scanf(" %d", &opcao);

        OrdemDeListagem ordem;

        switch (opcao) {
            case 1:
                ordem = recebeOrdemDeListagem();
                listaTodasAsVendas(ordem);
                break;
            case 2:
                limpaTela();
                Data dataDeConsulta = recebeData();
                
                ordem = recebeOrdemDeListagem();
                listaVendasPorData(dataDeConsulta, ordem);
                break;

            case 3: 
                limpaTela();
                char nomeCliente[TAMANHO_MAX_STRING];
                scanf(" %[^\n]", nomeCliente);
                
                ordem = recebeOrdemDeListagem();
                listaVendasPorCliente(nomeCliente, ordem);
                break;
        }
    } while (opcao != 0);
}


void listaTodasAsVendas(OrdemDeListagem ordem) {
    // Aloca lista com todas as vendas
    int numeroDeVendas = calculaNumeroDeVendasTotais();
    Venda* listaDeVendas = criaListaDeVendas(numeroDeVendas);
    retornaTodasAsVendas(numeroDeVendas, listaDeVendas);
    
    imprimeLista(listaDeVendas, numeroDeVendas, ordem);

    // Libera memória de lista com todas as vendas
    free(listaDeVendas);
}


int calculaNumeroDeVendasTotais() {
    int numeroDeVendasTotais = 0;

    FILE* arquivo = fopen(NOME_ARQUIVO, "rb");

    // Testa se arquivo foi aberto com sucesso
    if (arquivo == NULL) {
        printf("Erro: falha ao tentar abrir o arquivo. \n");
        exit(1);
    }

    // Percorre arquivo contando número de vendas 
    Venda vendaBuffer;
    while(fread(&vendaBuffer, sizeof(Venda), 1, arquivo) == 1) {
        numeroDeVendasTotais++;
    }

    fclose(arquivo);

    return numeroDeVendasTotais;
}


void retornaTodasAsVendas(int numeroDeVendas, Venda* listaDeVendas) {
    FILE* arquivo = fopen(NOME_ARQUIVO, "rb");

    // Testa se arquivo foi aberto com sucesso
    if (arquivo == NULL) {
        printf("Erro: falha ao tentar abrir o arquivo. \n");
        exit(1);
    }

    // Percorre arquivo adicionando vendas em lista 
    // e salvando seu id como a possição dentro do arquivo

    int id = 0;
    int index = 0;
    Venda vendaBuffer;

    while(fread(&vendaBuffer, sizeof(Venda), 1, arquivo) == 1) {
        vendaBuffer.id = id++;
        listaDeVendas[index++] = vendaBuffer;
    }

    fclose(arquivo);
}


void listaVendasPorData(Data dataDeConsulta, OrdemDeListagem ordem) {
    // Aloca lista com vendas de uma data específica
    int numeroDeVendas = calculaNumeroDeVendasPorData(dataDeConsulta);
    Venda* listaDeVendas = criaListaDeVendas(numeroDeVendas);
    retornaVendasPorData(numeroDeVendas, listaDeVendas, dataDeConsulta);
    
    imprimeLista(listaDeVendas, numeroDeVendas, ordem);

    free(listaDeVendas);
}


int calculaNumeroDeVendasPorData(Data dataDeConsulta) {
    int numeroDeVendasTotais = 0;

    FILE* arquivo = fopen(NOME_ARQUIVO, "rb");

    // Testa se arquivo foi aberto com sucesso
    if (arquivo == NULL) {
        printf("Erro: falha ao tentar abrir o arquivo. \n");
        exit(1);
    }

    // Percorre arquivo contando o numero de vendas de um data específica
    Venda vendaBuffer;
    while(fread(&vendaBuffer, sizeof(Venda), 1, arquivo) == 1) {
        if (comparaDatas(vendaBuffer.data, dataDeConsulta))
            numeroDeVendasTotais++;
    }

    fclose(arquivo);

    return numeroDeVendasTotais;
}


void retornaVendasPorData(int numeroDeVendas, Venda* listaDeVendas, Data dataDeConsulta) {
    FILE* arquivo = fopen(NOME_ARQUIVO, "rb");

    if (arquivo == NULL) {
        printf("Erro: falha ao tentar abrir o arquivo. \n");
        exit(1);
    }

    // Percorre arquivo adicionando vendas de data específica em lista 
    // e salvando seu id como a possição dentro do arquivo

    int id = 0;
    int index = 0;
    Venda vendaBuffer;

    while(fread(&vendaBuffer, sizeof(Venda), 1, arquivo) == 1) {
        vendaBuffer.id = id++;
        if (comparaDatas(vendaBuffer.data, dataDeConsulta))
            listaDeVendas[index++] = vendaBuffer;
    }

    fclose(arquivo);
}


int comparaDatas(Data a, Data b) {
    if (a.dia == b.dia && a.mes == b.mes && a.ano == b.ano)
        return 1;
    return 0;
}


void listaVendasPorCliente(char nomeCliente[], OrdemDeListagem ordem) {
    // Aloca lista de vendas de cliente específico
    int numeroDeVendas = calculaNumeroDeVendasPorCliente(nomeCliente);
    Venda* listaDeVendas = criaListaDeVendas(numeroDeVendas);
    retornaVendasPorCliente(numeroDeVendas, listaDeVendas, nomeCliente);

    imprimeLista(listaDeVendas, numeroDeVendas, ordem);

    free(listaDeVendas);
}


int calculaNumeroDeVendasPorCliente(char nomeCliente[]) {
    int numeroDeVendasTotais = 0;

    FILE* arquivo = fopen(NOME_ARQUIVO, "rb");

    // Testa se arquivo foi aberto com sucesso
    if (arquivo == NULL) {
        printf("Erro: falha ao tentar abrir o arquivo. \n");
        exit(1);
    }

    // Percorre arquivo adicionando vendas de cliente específico em lista 
    // e salvando seu id como a possição dentro do arquivo

    Venda vendaBuffer;
    while(fread(&vendaBuffer, sizeof(Venda), 1, arquivo) == 1) {
        if (strcmp(vendaBuffer.nomeCliente, nomeCliente) == 0)
            numeroDeVendasTotais++;
    }

    fclose(arquivo);

    return numeroDeVendasTotais;
}


void retornaVendasPorCliente(int numeroDeVendas, Venda* listaDeVendas, char nomeCliente[]) {
    FILE* arquivo = fopen(NOME_ARQUIVO, "rb");

    // Testa se arquivo foi aberto com sucesso
    if (arquivo == NULL) {
        printf("Erro: falha ao tentar abrir o arquivo. \n");
        exit(1);
    }

    // Percorre arquivo adicionando vendas de cliente específico em lista 
    // e salvando seu id como a possição dentro do arquivo

    int id = 0;
    int index = 0;
    Venda vendaBuffer;

    while(fread(&vendaBuffer, sizeof(Venda), 1, arquivo) == 1) {
        vendaBuffer.id = id++;
        if (strcmp(vendaBuffer.nomeCliente, nomeCliente) == 0)
            listaDeVendas[index++] = vendaBuffer;
    }

    fclose(arquivo);
}


Venda* criaListaDeVendas(int tamanhoDaLista) {
    return (Venda*) malloc(sizeof(Venda) * tamanhoDaLista);
}


void imprimeLista(Venda* listaDeVendas, int quantidadeDeVendas, OrdemDeListagem ordem) {

    // Termina execução caso lista esteja vazia
    if (quantidadeDeVendas <= 0)
        return;

    float faturamentoBruto = calculaFaturamentoTotal(listaDeVendas, quantidadeDeVendas);
    int numeroClientes = contaNumeroClientes(listaDeVendas, quantidadeDeVendas);

    if (ordem == ORDEM_CRESCENTE) {
        quickSort(listaDeVendas, quantidadeDeVendas);
    }

    if (ordem == ORDEM_DECRESCENTE) {
        quickSort(listaDeVendas, quantidadeDeVendas);
        inverteLista(listaDeVendas, quantidadeDeVendas);
    }

    // Imprime relatórios da lista passada

    limpaTela();
    printf("Relatórios \n");
    printf("======================================== \n\n\n");
    
    printf("Quantidade de items: %d \n\n", quantidadeDeVendas);
    printf("---------------------------------------- \n\n\n");

    printf("Lista de vendas: \n\n\n");

    for (int i = 0; i < quantidadeDeVendas; i++) {
        printf("ID da venda: %d \n", listaDeVendas[i].id);
        printf("Data da venda: %02d/%02d/%04d \n", 
                listaDeVendas[i].data.dia, 
                listaDeVendas[i].data.mes, 
                listaDeVendas[i].data.ano);
        printf("Nome do cliente: %s \n", listaDeVendas[i].nomeCliente);
        printf("Código do item: %s \n", listaDeVendas[i].item.codigo);
        printf("Nome do item: %s \n", listaDeVendas[i].item.nome);
        printf("Marca do item: %s \n", listaDeVendas[i].item.marca);
        printf("Quantidade de items: %d \n", listaDeVendas[i].item.quantidade);
        printf("Preço unitário do item: %.2f \n", listaDeVendas[i].item.precoUnitario);
        printf("Preço total final dos items: %.2f \n\n", listaDeVendas[i].item.precoTotal);
    }

    printf("---------------------------------------- \n\n\n");

    printf("Faturamento bruto: %.2f \n\n", faturamentoBruto);
    printf("---------------------------------------- \n\n\n");

    printf("Quantidade de clientes: %d \n\n", numeroClientes);
    printf("---------------------------------------- \n\n\n");

    printf("Produto mais vendido: \n\n");

    Venda vendaDoItemMaisVendido = determinaVendaDoItemMaisVendido(
            listaDeVendas, quantidadeDeVendas);

    printf("ID da venda: %d \n", vendaDoItemMaisVendido.id);
    printf("Data da venda: %02d/%02d/%04d \n", 
            vendaDoItemMaisVendido.data.dia, 
            vendaDoItemMaisVendido.data.mes, 
            vendaDoItemMaisVendido.data.ano);
    printf("Nome do cliente: %s \n", vendaDoItemMaisVendido.nomeCliente);
    printf("Código do item: %s \n", vendaDoItemMaisVendido.item.codigo);
    printf("Nome do item: %s \n", vendaDoItemMaisVendido.item.nome);
    printf("Marca do item: %s \n", vendaDoItemMaisVendido.item.marca);
    printf("Quantidade de items: %d \n", vendaDoItemMaisVendido.item.quantidade);
    printf("Preço unitário do item: %.2f \n", vendaDoItemMaisVendido.item.precoUnitario);
    printf("Preço total final dos items: %.2f \n\n", vendaDoItemMaisVendido.item.precoTotal);
    printf("---------------------------------------- \n\n\n");

    printf("Produto menos vendido: \n\n");

    Venda vendaDoItemMenosVendido = determinaVendaDoItemMenosVendido(
            listaDeVendas, quantidadeDeVendas);

    printf("ID da venda: %d \n", vendaDoItemMenosVendido.id);
    printf("Data da venda: %02d/%02d/%04d \n", 
            vendaDoItemMenosVendido.data.dia, 
            vendaDoItemMenosVendido.data.mes, 
            vendaDoItemMenosVendido.data.ano);
    printf("Nome do cliente: %s \n", vendaDoItemMenosVendido.nomeCliente);
    printf("Código do item: %s \n", vendaDoItemMenosVendido.item.codigo);
    printf("Nome do item: %s \n", vendaDoItemMenosVendido.item.nome);
    printf("Marca do item: %s \n", vendaDoItemMenosVendido.item.marca);
    printf("Quantidade de items: %d \n", vendaDoItemMenosVendido.item.quantidade);
    printf("Preço unitário do item: %.2f \n", vendaDoItemMenosVendido.item.precoUnitario);
    printf("Preço total final dos items: %.2f \n\n", vendaDoItemMenosVendido.item.precoTotal);
    printf("---------------------------------------- \n\n\n");

    esperaPorInputDoUsuario();
}


float calculaFaturamentoTotal(Venda* listaDeVendas, int quantidadeDeVendas) {

    float faturamentoTotal = 0;

    for (int i = 0; i < quantidadeDeVendas; i++) {
        faturamentoTotal += listaDeVendas[i].item.precoTotal;
    }

    return faturamentoTotal;
}


int contaNumeroClientes(Venda* listaDeVendas, int quantidadeDeVendas) {
    // Termina execução caso lista esteja vazia
    if (quantidadeDeVendas <= 0)
        return 0;
    
    int quantidadeCliente = 1;
    char nomeClienteTemp[TAMANHO_MAX_STRING];
    strcpy(nomeClienteTemp, listaDeVendas[0].nomeCliente);

    for (int i = 1; i < quantidadeDeVendas; i++) {
        if (strcmp(nomeClienteTemp, listaDeVendas[i].nomeCliente) != 0) {
            quantidadeCliente++;
            strcpy(nomeClienteTemp, listaDeVendas[i].nomeCliente);
        }
    }

    return quantidadeCliente;
}


void quickSort(Venda listaDeVendas[], int tamanhoDaLista) {
    quickSortAxiliar(listaDeVendas, 0, tamanhoDaLista - 1);
}


void quickSortAxiliar(Venda vendas[], int limiteInferior, int limiteSuperior) {
    if (limiteInferior < limiteSuperior) {
        int indexPivot = particiona(vendas, limiteInferior, limiteSuperior);

        quickSortAxiliar(vendas, limiteInferior, indexPivot - 1);
        quickSortAxiliar(vendas, indexPivot + 1, limiteSuperior);
    }
}


int particiona(Venda vendas[], int limiteInferior, int limiteSuperior) {

    // Inicializa pivot
    int valorEmPivot = vendas[limiteInferior].item.precoTotal;
    
    // Inicializa indexes de busca
    int indexEsquerda = limiteInferior;
    int indexDireita = limiteSuperior;

    while (indexEsquerda < indexDireita) {
        // Encontra o primeiro elemento maior que o pivot começando pela esquerda
        while (vendas[indexEsquerda].item.precoTotal <= valorEmPivot && indexEsquerda <= limiteSuperior - 1) {
            indexEsquerda++;
        }

        // Encontra o primeiro elemento menor que o pivot começando pela direita
        while (vendas[indexDireita].item.precoTotal > valorEmPivot && indexDireita >= limiteInferior + 1) {
            indexDireita--;
        }

        if (indexEsquerda < indexDireita) {
            trocaVendas(&vendas[indexEsquerda], &vendas[indexDireita]);
        }
    }

    trocaVendas(&vendas[limiteInferior], &vendas[indexDireita]);
    return indexDireita;
}


void trocaVendas(Venda* a, Venda* b) {
    Venda vendaTemporario = *a;
    *a = *b;
    *b = vendaTemporario;
}


void inverteLista(Venda lista[], int tamanhoDaLista) {
    int inicio = 0;
    int fim = tamanhoDaLista - 1;

    while (inicio < fim) {
        // Troca os elementos nas posições inicio e fim
        Venda temp = lista[inicio];
        lista[inicio] = lista[fim];
        lista[fim] = temp;

        // Move os índices
        inicio++;
        fim--;
    }
}


Venda determinaVendaDoItemMaisVendido(Venda* listaDeVendas, int quantidadeDeVendas) {
    if (quantidadeDeVendas <= 0) {
        printf("Erro: lista vazia \n");
        exit(1);
    }
    
    // Percorre lista buscando pelo maior elemento
    Venda vendaDoItemMaisVendidoAtual = listaDeVendas[0];

    for (int i = 0; i < quantidadeDeVendas; i++) {
        if (listaDeVendas[i].item.quantidade > vendaDoItemMaisVendidoAtual.item.quantidade) {
            vendaDoItemMaisVendidoAtual = listaDeVendas[i];
        }
    }   

    return vendaDoItemMaisVendidoAtual;
}


Venda determinaVendaDoItemMenosVendido(Venda* listaDeVendas, int quantidadeDeVendas) {
    if (quantidadeDeVendas <= 0) {
        printf("Erro: lista vazia \n");
        exit(1);
    }
    
    // Percorre lista buscando pelo menor elemento
    Venda vendaDoItemMenosVendidoAtual = listaDeVendas[0];

    for (int i = 0; i < quantidadeDeVendas; i++) {
        if (listaDeVendas[i].item.quantidade < vendaDoItemMenosVendidoAtual.item.quantidade) {
            vendaDoItemMenosVendidoAtual = listaDeVendas[i];
        }
    }   

    return vendaDoItemMenosVendidoAtual;
}


Data recebeData() {
    printf("Insira a data (dd/mm/aaaa): ");
    Data data;
    scanf(" %d/%d/%d", &data.dia, &data.mes, &data.ano);
    
    return data;
}


OrdemDeListagem recebeOrdemDeListagem() {
    int opcao;
    
    limpaTela();
    printf("Escolha a ordem em que você deseja ver os items lidados: \n\n");

    printf("0 - Ordem decrescente \n");
    printf("1 - Ordem de registro \n");
    printf("2 - Ordem crescente \n\n");

    printf("Escolha desejada: ");
    scanf(" %d", &opcao);

    if (opcao < 0 || opcao > 2) {
        opcao = 1;
    }

    return opcao;
}


void editaVenda() {
    limpaTela();

    printf("Entre com o ID da venda que você quer editar: ");
    int id;
    scanf(" %d", &id);

    FILE* arquivo = fopen(NOME_ARQUIVO, "rb+");

    // Testa se arquivo foi aberto com sucesso
    if (arquivo == NULL) {
        printf("Erro: falha ao tentar abrir o arquivo. \n");
        exit(1);
    }

    // Posiciona ponteiro do arquivo em venda que será editada
    fseek(arquivo, sizeof(Venda) * id, SEEK_SET);

    // Le, exibe, e edita valores da venda desejada
    Venda vendaParaEditar;
    int teveSucessoAoGravar = fread(&vendaParaEditar, sizeof(Venda), 1, arquivo);

    if (!teveSucessoAoGravar) {
        printf("Erro: Falha ao tentar ler dados no arquivo. \n");
        exit(1);
    }


    printf("\n\nData da venda: %02d/%02d/%04d \n", 
            vendaParaEditar.data.dia, 
            vendaParaEditar.data.mes, 
            vendaParaEditar.data.ano);
    printf("Nome do cliente: %s \n", vendaParaEditar.nomeCliente);
    printf("Código do item: %s \n", vendaParaEditar.item.codigo);
    printf("Nome do item: %s \n", vendaParaEditar.item.nome);
    printf("Marca do item: %s \n", vendaParaEditar.item.marca);
    printf("Quantidade de items: %d \n", vendaParaEditar.item.quantidade);
    printf("Preço unitário do item: %.2f \n", vendaParaEditar.item.precoUnitario);
    printf("Preço total final dos items: %.2f \n\n\n", vendaParaEditar.item.precoTotal);

    
    printf("Nova data da venda (dd/mm/aaaa): ");
    scanf(" %d/%d/%d", 
            &vendaParaEditar.data.dia, 
            &vendaParaEditar.data.mes, 
            &vendaParaEditar.data.ano);

    printf("Novo nome do cliente: ");
    scanf(" %[^\n]", vendaParaEditar.nomeCliente);

    printf("Novo código do item: ");
    scanf(" %[^\n]", vendaParaEditar.item.codigo);
    
    printf("Novo nome do item: ");
    scanf(" %[^\n]", vendaParaEditar.item.nome);

    printf("Nova marca do item: ");
    scanf(" %[^\n]", vendaParaEditar.item.marca);

    printf("Nova quantidade de items: ");
    scanf(" %d", &vendaParaEditar.item.quantidade);

    printf("Novo preço unitário do item: ");
    scanf(" %f", &vendaParaEditar.item.precoUnitario);
    
    vendaParaEditar.item.precoTotal = calculaPrecoTotalDeProduto(
                vendaParaEditar.item.quantidade, vendaParaEditar.item.precoUnitario);
    printf("Novo preço total final dos items: %.2f \n\n\n", vendaParaEditar.item.precoTotal);

    esperaPorInputDoUsuario();


    fseek(arquivo, sizeof(Venda) * id, SEEK_SET);
    teveSucessoAoGravar = fwrite(&vendaParaEditar, sizeof(Venda), 1, arquivo);

    if (!teveSucessoAoGravar) {
        printf("Erro: Falha ao tentar gravar dados no arquivo. \n");
        exit(1);
    }

    fclose(arquivo); 
}  


float calculaPrecoTotalDeProduto(int quantidadeDeProdutos, float precoUnitarioDoProduto) {
    float precoTotal = quantidadeDeProdutos * precoUnitarioDoProduto;

    if (quantidadeDeProdutos >= 3)
        precoTotal *= 0.9; // Desconto de 10% para vendas de 3 produtos ou mais

    return precoTotal;
}


void deletaVenda() {
    limpaTela();

    printf("Entre com o ID da venda que você quer deletar: ");
    int id;
    scanf(" %d", &id);

    FILE* arquivo = fopen(NOME_ARQUIVO, "rb");
    FILE* arquivoTemp = fopen("temp.bin", "wb");

    // testa se arquivos forma abertos com sucesso
    if (arquivo == NULL || arquivoTemp == NULL) {
        printf("Erro: falha ao tentar abrir o arquivo. \n");
        exit(1);
    }

    // Percorre conteúdo do arquivo, 
    // reescrevendo suas vendas em arquivoTem com exeção da venda desejada

    int idAtual = 0;
    Venda vendaBuffer;
    while(fread(&vendaBuffer, sizeof(Venda), 1, arquivo) == 1) {
        if (idAtual != id) 
            fwrite(&vendaBuffer, sizeof(Venda), 1, arquivoTemp);
        
        idAtual++;
    }

    // Apaga arquivo origianl e testa se teve sucesso na ação 
    if (remove(NOME_ARQUIVO) != 0) {
        printf("Erro: Falha ao deletar arquivo. \n");
        exit(1);
    }
    
    // renomeia arquivo temporário com o nome do arquivo original 
    // e testa se teve sucesso na ação 
    if (rename("temp.bin", NOME_ARQUIVO) != 0) {
        printf("Erro: Falha ao renomear arquivo. \n");
        exit(1);
    }
    
    printf("\nArquivo deletado com sucesso.\n\n");

    esperaPorInputDoUsuario();

    fclose(arquivoTemp);
    fclose(arquivo); 
}  


void esperaPorInputDoUsuario() {
    char desejaContinuar;
    printf("Precione qualquer caracter para continuar... ");
    scanf(" %c", &desejaContinuar);
}
