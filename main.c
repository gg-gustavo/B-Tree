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
int carregar_registros(Carro registros[TOTAL_REGISTROS], const char* nome_arquivo) {
    FILE *arquivo = fopen(nome_arquivo, "r");
    if (arquivo == NULL) {
        perror("Nao foi possivel abrir o arquivo de registros");
        return 0;
    }

    int i = 0;
    char linha[256];
    while (i < TOTAL_REGISTROS && fgets(linha, sizeof(linha), arquivo)) {
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

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Uso: %s <ordem_da_arvore>\n", argv[0]);
        return 1;
    }

    int ordem = atoi(argv[1]);
    if (ordem < 2) {
        fprintf(stderr, "A ordem da arvore deve ser no minimo 2.\n");
        return 1;
    }

    printf("--- Trabalho de Algoritmos III: Arvore B+ ---\n");
    printf("Executando testes para ORDEM = %d\n\n", ordem);

    Carro todos_registros[TOTAL_REGISTROS];
    int num_lidos = carregar_registros(todos_registros, "registros.txt");

    if (num_lidos == 0) {
        fprintf(stderr, "Nenhum registro foi carregado. Verifique o arquivo 'registros.txt'.\n");
        return 1;
    }
    
    srand(time(NULL)); // Inicializa o gerador de números aleatórios

    int tamanhos_teste[] = {100, 1000, 10000};
    int num_tamanhos = sizeof(tamanhos_teste) / sizeof(tamanhos_teste[0]);

    for (int i = 0; i < num_tamanhos; i++) {
        int n = tamanhos_teste[i];
        if (n > num_lidos) continue;

        printf("---------------------------------------------------\n");
        printf("Iniciando teste com %d registros.\n", n);

        // 1. Criar e popular a árvore
        ArvoreBPlus* arvore = criar_arvore(ordem);
        for (int j = 0; j < n; j++) {
            inserir(arvore, &todos_registros[j]);
        }
        printf("Arvore populada com %d registros.\n", n);

        // 2. Preparar chaves para a busca
        long long chaves_para_buscar[NUM_BUSCAS];
        for (int j = 0; j < NUM_BUSCAS; j++) {
            int indice_aleatorio = rand() % n; // Pega um registro que existe na árvore
            chaves_para_buscar[j] = todos_registros[indice_aleatorio].renavam;
        }

        // 3. Realizar as buscas e cronometrar
        clock_t inicio = clock();
        for (int j = 0; j < NUM_BUSCAS; j++) {
            Carro* encontrado = buscar(arvore, chaves_para_buscar[j]);
            if (encontrado == NULL) {
                 printf("AVISO: Chave %lld nao encontrada na busca!\n", chaves_para_buscar[j]);
            }
        }
        clock_t fim = clock();

        // 4. Calcular e apresentar os resultados
        double tempo_total = (double)(fim - inicio) / CLOCKS_PER_SEC;
        double tempo_medio = tempo_total / NUM_BUSCAS;

        printf("Resultado do teste para N = %d:\n", n);
        printf("Tempo total para %d buscas: %f segundos\n", NUM_BUSCAS, tempo_total);
        printf("Tempo medio por busca:      %f segundos\n", tempo_medio);
        
        // 5. Liberar a memória da árvore
        liberar_arvore(arvore);
        printf("Memoria da arvore liberada.\n");
    }
    
    printf("---------------------------------------------------\n");
    printf("Todos os testes foram concluidos.\n");

    return 0;
}