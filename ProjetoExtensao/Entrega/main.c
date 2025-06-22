/**************************************************

    Projeto de Extenção da disciplina de algoritmos
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

#define NOME_ARQUIVO "resutaurante.bin"
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


typedef struct Refeicao {
    int possuiQuentinha;
    float peso;
    float precoQuilo;
    float precoTotal;
} Refeicao;


typedef struct Bebida {
    float preco;
    int quantidade;
    float precoTotal;
} Bebida;


typedef struct Venda {
    int id;
    Data data;
    Refeicao refeicao;
    Bebida bebida;
    float precoFinal;
} Venda;


typedef struct MesDeVenda {
    int numeroDoMes;
    char nomeDoMes[TAMANHO_MAX_STRING];
    float totalMesDeVenda;
} MesDeVenda;



///////////////// DECLARA FUNÇÕES /////////////////

void registraNovoDiaDeVenda();
void registrarVenda(Data dataDeVenda);
Venda criaVenda(Data dataDeVenda);
void recebeVenda(Venda* venda);
void salvaVendaEmArquivo(Venda venda);
void exibeRelatorios();
void consultaVendas();
void relatorioDiario();
void organizaVendasPorDia(int tamanhoDaLista, Venda listaDeVendas[]);
void relatorioMensal();
void inicializaMesesDoAno(MesDeVenda listaDeMesDeVendaEmAno[]);
int calculaNumeroDeVendasTotais();
void retornaTodasAsVendas(int numeroDeVendas, Venda* listaDeVendas);
int calculaNumeroDeVendasPorAno(int ano);
void retornaVendasPorAno(int ano, int numeroDeVendas, Venda* listaDeVendas);
Venda* criaListaDeVendas(int tamanhoDaLista);
void imprimeTodasAsVendas(Venda* listaDeVendas, int quantidadeDeVendas);
void imprimeVendasPorDia(Venda listaDeVendas[], int quantidadeDeVendas);
void quickSortMesesDoAno(MesDeVenda lista[], int (*cmp)(MesDeVenda, MesDeVenda));
void quickSortAxiliarMeses(
        MesDeVenda lista[], int limInferior, int limSuperior, int (*cmp)(MesDeVenda, MesDeVenda));
int particionaMeses(
        MesDeVenda lista[], int limInferior, int limSuperior, int (*cmp)(MesDeVenda, MesDeVenda));
void trocaMeses(MesDeVenda* a, MesDeVenda* b);
int comparaMeses(int a, int b);
int comparaMesesDeVenda(MesDeVenda a, MesDeVenda b);
void quickSortVendas(Venda listaDeVendas[], int tamanhoDaLista, int (*cmp)(Venda, Venda));
void quickSortAxiliarVendas(Venda vendas[], int limInferior, int limSuperior, int (*cmp)(Venda, Venda));
int particionaVendas(Venda vendas[], int limInferior, int limSuperior, int (*cmp)(Venda, Venda));
void trocaVendas(Venda* a, Venda* b);
int comparaDatas(Data a, Data b);
int comparaVendasPorData(Venda a, Venda b);
Data recebeDia();
void editaVenda();
void deletaVenda();
void esperaPorInputDoUsuario();



////////////////////// MAIN ///////////////////////

int main() {

    setlocale(LC_ALL, "Portuguese");

    int opcao;
    do {
        limpaTela();
        printf("Restaurante à Quilo Veiga de Almeida\n\n");

        printf("Donos do Restaurante: \n");
        printf("Igor Sousa Alves \t- 1240207519 \n");
        printf("Kamilla Lucas Tré \t- 1230106915 \n");
        printf("Thalles Henriques \t- 1240114928 \n");
        printf("Vinícius de Azevedo \t- 1240201902 \n\n\n");

        printf("Escolha o que você deseja fazer: \n\n");

        printf("1 - Registrar novo dia de venda \n");
        printf("2 - Exibir relatórios \n");
        printf("3 - Consulta todas as vendas \n");
        printf("4 - Editar venda \n");
        printf("5 - Deletar venda \n");
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
                consultaVendas();
                break;

            case 4:
                editaVenda();
                break;

            case 5:
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

    Data dataDeVenda = recebeDia();

    int opcao;
    do {
        limpaTela();
        printf("Registro de vendas do dia: %02d/%02d/%04d \n\n\n",
            dataDeVenda.dia, dataDeVenda.mes, dataDeVenda.ano);

        printf("Selecione uma opção: \n\n");
        printf("1 - Registrar nova venda \n");
        printf("0 - Voltar ao menu principal \n\n");

        printf("Opção desejada: ");
        scanf(" %d", &opcao);

        switch (opcao) {
            case 1:
                registrarVenda(dataDeVenda);
                break;
        }
    } while(opcao != 0);
}


void registrarVenda(Data dataDeVenda) {
    Venda venda = criaVenda(dataDeVenda);

    limpaTela();
    printf("Registro de venda \n\n");

    recebeVenda(&venda);

    salvaVendaEmArquivo(venda);
}


Venda criaVenda(Data dataDeVenda) {
    Venda venda;
    venda.id = 0;
    venda.data = dataDeVenda;
    return venda;
}


void recebeVenda(Venda* venda) {
    printf("Como será a sua refeição? \n\n");

    printf("0 - À quilo \n");
    printf("1 - Quentinha \n\n");

    printf("Opção desejada: ");
    scanf(" %d", &venda->refeicao.possuiQuentinha);

    if (venda->refeicao.possuiQuentinha) {
        venda->refeicao.peso = 0;
        venda->refeicao.precoQuilo = 0;
        venda->refeicao.precoTotal = 20.50;
    }
    else {
        printf("\n\nEntre com o peso da sua refeição (em quilos): ");
        scanf(" %f", &venda->refeicao.peso);

        printf("Entre com o preço do quilo do seu item refeição: ");
        scanf(" %f", &venda->refeicao.precoQuilo);

        venda->refeicao.precoTotal = venda->refeicao.peso * venda->refeicao.precoQuilo;
    }

    printf("\n\nO preço total da sua refeição foi de: %.2f \n\n\n", venda->refeicao.precoTotal);

    printf("Quantas bebidas deseja comprar: ");
    scanf(" %d", &venda->bebida.quantidade);

    if (venda->bebida.quantidade > 0) {
        printf("Entre com o preço individual da sua bebida: ");
        scanf(" %f", &venda->bebida.preco);
    }
    else {
        venda->bebida.preco = 0;
    }

    venda->bebida.precoTotal = venda->bebida.quantidade * venda->bebida.preco;

    if (venda->bebida.quantidade > 1)
        printf("\nO preço total das suas bebidas foi de: %.2f \n", venda->bebida.precoTotal);


    venda->precoFinal = venda->refeicao.precoTotal + venda->bebida.precoTotal;
    printf("\n\nO preço final da venda foi de: %.2f \n\n\n", venda->precoFinal);

    esperaPorInputDoUsuario();
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
        printf("1 - Relatório diário \n");
        printf("2 - Relatório mensal \n");
        printf("0 - Voltar ao menu principal \n\n");

        printf("Escolha desejada: ");
        scanf(" %d", &opcao);

        switch (opcao) {
            case 1:
                relatorioDiario();
                break;

            case 2:
                relatorioMensal();
                break;
        }
    } while (opcao != 0);
}


void consultaVendas() {
    limpaTela();

    int numeroDeVendas = calculaNumeroDeVendasTotais();
    Venda* listaDeVendas = criaListaDeVendas(numeroDeVendas);
    retornaTodasAsVendas(numeroDeVendas, listaDeVendas);

    imprimeTodasAsVendas(listaDeVendas, numeroDeVendas);

    esperaPorInputDoUsuario();
}


void relatorioDiario() {
    int numeroDeVendas = calculaNumeroDeVendasTotais();
    Venda* listaDeVendas = criaListaDeVendas(numeroDeVendas);
    retornaTodasAsVendas(numeroDeVendas, listaDeVendas);

    organizaVendasPorDia(numeroDeVendas, listaDeVendas);

    imprimeVendasPorDia(listaDeVendas, numeroDeVendas);

    esperaPorInputDoUsuario();
}


void organizaVendasPorDia(int tamanhoDaLista, Venda listaDeVendas[]) {
    quickSortVendas(listaDeVendas, tamanhoDaLista, comparaVendasPorData);
}


void relatorioMensal() {
    MesDeVenda setVendasDeCadaMes[12];
    inicializaMesesDoAno(setVendasDeCadaMes);

    int anoDesejado;

    limpaTela();
    printf("Relatório Mensal: \n\n\n");

    printf("Entre com o ano para o qual deseja ver o relatório: \n\n");
    scanf(" %d", &anoDesejado);

    int numeroDeVendas = calculaNumeroDeVendasPorAno(anoDesejado);
    Venda* listaDeVendas = criaListaDeVendas(numeroDeVendas);
    retornaVendasPorAno(anoDesejado, numeroDeVendas, listaDeVendas);

    if (numeroDeVendas <= 0)
        return;

    for (int i = 0; i < numeroDeVendas; i++) {
        int indexMesAtual = listaDeVendas[i].data.mes - 1;
        setVendasDeCadaMes[indexMesAtual].totalMesDeVenda += listaDeVendas[i].precoFinal;
    }

    quickSortMesesDoAno(setVendasDeCadaMes, comparaMesesDeVenda);

    printf("Meses ordenados por total de vendas: \n\n");

    for (int i = 0; i < 12; i++) {
        printf("%s: %.2f \n",
                setVendasDeCadaMes[i].nomeDoMes, setVendasDeCadaMes[i].totalMesDeVenda);
    }

    printf("\n\n");
    esperaPorInputDoUsuario();
}


void inicializaMesesDoAno(MesDeVenda listaDeMesDeVendaEmAno[]) {
    strcpy(listaDeMesDeVendaEmAno[0].nomeDoMes, "Janeiro");
    strcpy(listaDeMesDeVendaEmAno[1].nomeDoMes, "Fevereiro");
    strcpy(listaDeMesDeVendaEmAno[2].nomeDoMes, "Março");
    strcpy(listaDeMesDeVendaEmAno[3].nomeDoMes, "Abril");
    strcpy(listaDeMesDeVendaEmAno[4].nomeDoMes, "Maio");
    strcpy(listaDeMesDeVendaEmAno[5].nomeDoMes, "Junho");
    strcpy(listaDeMesDeVendaEmAno[6].nomeDoMes, "Julho");
    strcpy(listaDeMesDeVendaEmAno[7].nomeDoMes, "Agosto");
    strcpy(listaDeMesDeVendaEmAno[8].nomeDoMes, "Setembro");
    strcpy(listaDeMesDeVendaEmAno[9].nomeDoMes, "Outubro");
    strcpy(listaDeMesDeVendaEmAno[10].nomeDoMes, "Novembro");
    strcpy(listaDeMesDeVendaEmAno[11].nomeDoMes, "Dezembro");

    for (int i = 0; i < 12; i++) {
        listaDeMesDeVendaEmAno[i].numeroDoMes = i;
        listaDeMesDeVendaEmAno[i].totalMesDeVenda = 0;
    }
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



int calculaNumeroDeVendasPorAno(int ano) {
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
        if (vendaBuffer.data.ano == ano)
            numeroDeVendasTotais++;
    }

    fclose(arquivo);

    return numeroDeVendasTotais;
}


void retornaVendasPorAno(int ano, int numeroDeVendas, Venda* listaDeVendas) {
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

        if (vendaBuffer.data.ano == ano)
            listaDeVendas[index++] = vendaBuffer;
    }

    fclose(arquivo);
}


Venda* criaListaDeVendas(int tamanhoDaLista) {
    return (Venda*) malloc(sizeof(Venda) * tamanhoDaLista);
}



void imprimeTodasAsVendas(Venda* listaDeVendas, int quantidadeDeVendas) {

    // Termina execução caso lista esteja vazia
    if (quantidadeDeVendas <= 0)
        return;

    // Imprime todas as vendas em ordem de registro
    for (int i = 0; i < quantidadeDeVendas; i++){
        printf("ID: %d \n", listaDeVendas[i].id);
        printf("Data: %02d/%02d/%04d \n",
                listaDeVendas[i].data.dia,
                listaDeVendas[i].data.mes,
                listaDeVendas[i].data.ano);
        if (listaDeVendas[i].refeicao.possuiQuentinha) {
            printf("Tipo de Refeição: Quentinha \n");
            printf("Preço Total: %.2f \n", listaDeVendas[i].refeicao.precoTotal);
        }
        else {
            printf("Tipo de Refeição: À Quilo \n");
            printf("Peso: %.2f \n", listaDeVendas[i].refeicao.peso);
            printf("Preço do Quilo: %.2f \n", listaDeVendas[i].refeicao.precoQuilo);
            printf("Preço Total: %.2f \n", listaDeVendas[i].refeicao.precoTotal);
        }

        printf("Quantidade de bebidas: %d \n", listaDeVendas[i].bebida.quantidade);

        if (listaDeVendas[i].bebida.quantidade > 0) {
            printf("Preço unitário da bebida: %.2f \n", listaDeVendas[i].bebida.preco);
            printf("Preço Total: %.2f \n", listaDeVendas[i].bebida.precoTotal);
        }

        printf("Preço Final: %.2f \n\n", listaDeVendas[i].precoFinal);
    }
}



void imprimeVendasPorDia(Venda* listaDeVendas, int quantidadeDeVendas) {

    // Termina execução caso lista esteja vazia
    if (quantidadeDeVendas <= 0)
        return;

    float precoFinalDoPeriodo = 0;

    // Imprime relatórios com tabelas de vendas por dia

    limpaTela();
    printf("Relatório Diário \n");
    printf("======================================== \n\n\n");

    int i = 0;
    while (i < quantidadeDeVendas) {

        Data dataAnterior = listaDeVendas[i].data;
        Data dataAtual = listaDeVendas[i].data;

        printf("Relatório do dia %02d/%02d/%04d \n",
                listaDeVendas[i].data.dia,
                listaDeVendas[i].data.mes,
                listaDeVendas[i].data.ano);

        printf("ID   || Refeição  | Peso  | $/Kg  | Preço || Qtd. Bebidas | Preço Unidade | Preço Total || Preço Final \n");

        float precoFinalDoDia = 0;
        while (comparaDatas(dataAnterior, dataAtual) == 0 && i < quantidadeDeVendas) {
            printf("%-4d || ", listaDeVendas[i].id);

            if (listaDeVendas[i].refeicao.possuiQuentinha) {
                printf("Quentinha | ");
                printf("NA    | ");
                printf("NA    | ");
                printf("%-5.2f || ", listaDeVendas[i].refeicao.precoTotal);
            }
            else {
                printf("À Quilo   | ");
                printf("%-5.3f | ", listaDeVendas[i].refeicao.peso);
                printf("%-5.2f | ", listaDeVendas[i].refeicao.precoQuilo);
                printf("%-5.2f || ", listaDeVendas[i].refeicao.precoTotal);
            }

            if (listaDeVendas[i].bebida.quantidade > 0) {
                printf("%-5d        | ", listaDeVendas[i].bebida.quantidade);
                printf("%-5.2f         | ", listaDeVendas[i].bebida.preco);
                printf("%-5.2f       || ", listaDeVendas[i].bebida.precoTotal);
            }
            else {
                printf("%-5d        | ", listaDeVendas[i].bebida.quantidade);
                printf("NA            | ");
                printf("NA          || ");
            }

            printf("%-5.2f \n", listaDeVendas[i].precoFinal);

            precoFinalDoDia += listaDeVendas[i].precoFinal;

            i++;
            dataAtual = listaDeVendas[i].data;
        }

        printf("Preço final do dia: %.2f \n\n\n", precoFinalDoDia);
        precoFinalDoPeriodo += precoFinalDoDia;
    }

    printf("\nPreço final do período: %.2f \n\n", precoFinalDoPeriodo);
}


void quickSortMesesDoAno(MesDeVenda lista[], int (*cmp)(MesDeVenda, MesDeVenda)) {
    quickSortAxiliarMeses(lista, 0, 11, cmp);
}


void quickSortAxiliarMeses(
        MesDeVenda lista[], int limInferior, int limSuperior, int (*cmp)(MesDeVenda, MesDeVenda)) {

    if (limInferior < limSuperior) {
        int indexPivot = particionaMeses(lista, limInferior, limSuperior, cmp);

        quickSortAxiliarMeses(lista, limInferior, indexPivot - 1, cmp);
        quickSortAxiliarMeses(lista, indexPivot + 1, limSuperior, cmp);
    }
}


int particionaMeses(
        MesDeVenda lista[], int limInferior, int limSuperior, int (*cmp)(MesDeVenda, MesDeVenda)) {

    // Inicializa indexes de busca
    int indexEsquerda = limInferior;
    int indexDireita = limSuperior;

    while (indexEsquerda < indexDireita) {
        // Encontra o primeiro elemento maior que o pivot começando pela esquerda
        while ((*cmp)(lista[indexEsquerda], lista[limInferior]) <= 0 && indexEsquerda <= limSuperior - 1) {
            indexEsquerda++;
        }

        // Encontra o primeiro elemento menor que o pivot começando pela direita
        while ((*cmp)(lista[indexDireita], lista[limInferior]) > 0 && indexDireita >= limInferior + 1) {
            indexDireita--;
        }

        if (indexEsquerda < indexDireita) {
            trocaMeses(&lista[indexEsquerda], &lista[indexDireita]);
        }
    }

    trocaMeses(&lista[limInferior], &lista[indexDireita]);
    return indexDireita;
}


void trocaMeses(MesDeVenda* a, MesDeVenda* b) {
    MesDeVenda mesTemporario = *a;
    *a = *b;
    *b = mesTemporario;
}


int comparaMeses(int a, int b) {
    if (a < b)
        return 1;

    else if (a == b)
        return 0;

    else
        return -1;
}


int comparaMesesDeVenda(MesDeVenda a, MesDeVenda b) {
    return comparaMeses(a.totalMesDeVenda, b.totalMesDeVenda);
}


void quickSortVendas(Venda listaDeVendas[], int tamanhoDaLista, int (*cmp)(Venda, Venda)) {
    quickSortAxiliarVendas(listaDeVendas, 0, tamanhoDaLista - 1, cmp);
}


void quickSortAxiliarVendas(Venda vendas[], int limInferior, int limSuperior, int (*cmp)(Venda, Venda)) {
    if (limInferior < limSuperior) {
        int indexPivot = particionaVendas(vendas, limInferior, limSuperior, cmp);

        quickSortAxiliarVendas(vendas, limInferior, indexPivot - 1, cmp);
        quickSortAxiliarVendas(vendas, indexPivot + 1, limSuperior, cmp);
    }
}


int particionaVendas(Venda vendas[], int limInferior, int limSuperior, int (*cmp)(Venda, Venda)) {
    // Inicializa indexes de busca
    int indexEsquerda = limInferior;
    int indexDireita = limSuperior;

    while (indexEsquerda < indexDireita) {
        // Encontra o primeiro elemento maior que o pivot começando pela esquerda
        while ((*cmp)(vendas[indexEsquerda], vendas[limInferior]) <= 0 && indexEsquerda <= limSuperior - 1) {
            indexEsquerda++;
        }

        // Encontra o primeiro elemento menor que o pivot começando pela direita
        while ((*cmp)(vendas[indexDireita], vendas[limInferior]) > 0 && indexDireita >= limInferior + 1) {
            indexDireita--;
        }

        if (indexEsquerda < indexDireita) {
            trocaVendas(&vendas[indexEsquerda], &vendas[indexDireita]);
        }
    }

    trocaVendas(&vendas[limInferior], &vendas[indexDireita]);
    return indexDireita;
}


void trocaVendas(Venda* a, Venda* b) {
    Venda vendaTemporario = *a;
    *a = *b;
    *b = vendaTemporario;
}


int comparaDatas(Data a, Data b) {
    if (a.ano > b.ano)
        return 1;

    if (a.ano == b.ano) {
        if (a.mes > b.mes)
            return 1;

        if (a.mes == b.mes) {
            if (a.dia > b.dia)
                return 1;

            if (a.dia == b.dia)
                return 0;
        }
    }

    return -1;
}


int comparaVendasPorData(Venda a, Venda b) {
    return comparaDatas(a.data, b.data);
}


Data recebeDia() {
    Data data;

    printf("Insira a data (dd/mm/aaaa): ");
    scanf(" %d/%d/%d", &data.dia, &data.mes, &data.ano);

    return data;
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

    printf("ID: %d \n", vendaParaEditar.id);
    printf("Data: %02d/%02d/%04d \n",
            vendaParaEditar.data.dia,
            vendaParaEditar.data.mes,
            vendaParaEditar.data.ano);
    if (vendaParaEditar.refeicao.possuiQuentinha) {
        printf("Tipo de Refeição: Quentinha \n");
        printf("Preço Total: %.2f \n", vendaParaEditar.refeicao.precoTotal);
    }
    else {
        printf("Tipo de Refeição: À Quilo \n");
        printf("Peso: %.2f \n", vendaParaEditar.refeicao.peso);
        printf("Preço do Quilo: %.2f \n", vendaParaEditar.refeicao.precoQuilo);
        printf("Preço Total: %.2f \n", vendaParaEditar.refeicao.precoTotal);
    }

    printf("Quantidade de bebidas: %d \n", vendaParaEditar.bebida.quantidade);

    if (vendaParaEditar.bebida.quantidade > 0) {
        printf("Preço unitário da bebida: %.2f \n", vendaParaEditar.bebida.preco);
        printf("Preço Total: %.2f \n", vendaParaEditar.bebida.precoTotal);
    }

    printf("Preço Final: %.2f \n\n", vendaParaEditar.precoFinal);

    recebeVenda(&vendaParaEditar);

    fseek(arquivo, sizeof(Venda) * id, SEEK_SET);
    teveSucessoAoGravar = fwrite(&vendaParaEditar, sizeof(Venda), 1, arquivo);

    if (!teveSucessoAoGravar) {
        printf("Erro: Falha ao tentar gravar dados no arquivo. \n");
        exit(1);
    }

    fclose(arquivo);
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
