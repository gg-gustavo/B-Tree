// Arquivo: main.c
// Descrição: Programa principal que executa os testes de desempenho.

#include "b_plus_tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TOTAL_REGISTROS 10000
#define NUM_BUSCAS 100

// Função para carregar todos os registros do arquivo para a memória
// Lê até TOTAL_REGISTROS linhas do arquivo e preenche o vetor de Carro
int carregar_registros(Carro registros[TOTAL_REGISTROS], const char *nome_arquivo)
{
    FILE *arquivo = fopen(nome_arquivo, "r");
    if (arquivo == NULL)
    {
        perror("Nao foi possivel abrir o arquivo de registros");
        return 0;
    }

    int i = 0;
    char linha[256];
    // Lê cada linha do arquivo e preenche os campos do struct Carro
    while (i < TOTAL_REGISTROS && fgets(linha, sizeof(linha), arquivo))
    {
        sscanf(linha, "%lld,%7[^,],%19[^,],%d,%14[^\n]",
               &registros[i].renavam,
               registros[i].placa,
               registros[i].modelo,
               &registros[i].ano,
               registros[i].cor);
        i++;
    }
    fclose(arquivo);
    return i; // Retorna o número de registros lidos
}

int main(int argc, char *argv[])
{
    // Verifica se o usuário passou o argumento da ordem da árvore
    if (argc != 2)
    {
        fprintf(stderr, "Uso: %s <ordem_da_arvore>\n", argv[0]);
        return 1;
    }

    // Converte o argumento para inteiro e valida
    int ordem = atoi(argv[1]);
    if (ordem < 2)
    {
        fprintf(stderr, "A ordem da arvore deve ser no minimo 2.\n");
        return 1;
    }

    // Mensagem inicial
    printf("--- Trabalho de Algoritmos III: Arvore B+ ---\n");
    printf("Executando testes para ORDEM = %d\n\n", ordem);

    // Vetor para armazenar todos os registros lidos do arquivo
    Carro todos_registros[TOTAL_REGISTROS];
    int num_lidos = carregar_registros(todos_registros, "registros.txt");

    // Verifica se conseguiu carregar registros
    if (num_lidos == 0)
    {
        fprintf(stderr, "Nenhum registro foi carregado. Verifique o arquivo 'registros.txt'.\n");
        return 1;
    }

    srand(time(NULL)); // Inicializa o gerador de números aleatórios

    // Define os tamanhos dos testes (quantidade de registros para cada rodada)
    int tamanhos_teste[] = {100, 1000, 10000};
    int num_tamanhos = sizeof(tamanhos_teste) / sizeof(tamanhos_teste[0]);

    // Loop para cada tamanho de teste
    for (int i = 0; i < num_tamanhos; i++)
    {
        int n = tamanhos_teste[i];
        if (n > num_lidos)
            continue;

        printf("---------------------------------------------------\n");
        printf("Iniciando teste com %d registros.\n", n);

        // 1. Criar e popular a árvore B+ com os registros
        ArvoreBPlus *arvore = criar_arvore(ordem);
        for (int j = 0; j < n; j++)
        {
            inserir(arvore, &todos_registros[j]);
        }
        printf("Arvore populada com %d registros.\n", n);

        // 2. Seleciona aleatoriamente NUM_BUSCAS chaves para buscar na árvore
        long long chaves_para_buscar[NUM_BUSCAS];
        int total_escolhidas = 0;
        while (total_escolhidas < NUM_BUSCAS)
        {
            int indice_aleatorio = rand() % n;
            long long chave = todos_registros[indice_aleatorio].renavam;
            int duplicado = 0;
            // Garante que não haja chaves repetidas no vetor de buscas
            for (int k = 0; k < total_escolhidas; k++)
            {
                if (chaves_para_buscar[k] == chave)
                {
                    duplicado = 1;
                    break;
                }
            }
            if (!duplicado)
            {
                chaves_para_buscar[total_escolhidas++] = chave;
            }
        }

        // 3. Realiza as buscas e mede o tempo total
        clock_t inicio = clock();
        for (int j = 0; j < NUM_BUSCAS; j++)
        {
            Carro *encontrado = buscar(arvore, chaves_para_buscar[j]);
            if (encontrado == NULL)
            {
                // Caso a chave não seja encontrada, exibe um aviso
                printf("AVISO: Chave %lld nao encontrada na busca!\n", chaves_para_buscar[j]);
            }
        }
        clock_t fim = clock();

        // 4. Calcula e exibe os resultados de tempo
        double tempo_total = (double)(fim - inicio) / CLOCKS_PER_SEC;
        double tempo_medio = tempo_total / NUM_BUSCAS;

        printf("Resultado do teste para N = %d:\n", n);
        printf("Tempo total para %d buscas: %f segundos\n", NUM_BUSCAS, tempo_total);
        printf("Tempo medio por busca:      %f segundos\n", tempo_medio);

        // 5. Libera a memória utilizada pela árvore
        liberar_arvore(arvore);
        printf("Memoria da arvore liberada.\n");
    }

    printf("---------------------------------------------------\n");
    printf("Todos os testes foram concluidos.\n");

    return 0;
}