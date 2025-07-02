// Arquivo: b_plus_tree.h
// Descrição: Define as estruturas e protótipos para a Árvore B+.

#ifndef B_PLUS_TREE_H
#define B_PLUS_TREE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Estrutura para os dados do Carro
typedef struct Carro {
    long long renavam;
    char placa[8];
    char modelo[20];
    int ano;
    char cor[15];
} Carro;

// Estrutura para o Nó da Árvore B+
typedef struct NoBPlus {
    bool folha;
    int num_chaves;
    long long *chaves;
    struct NoBPlus **filhos;
    Carro **registros; // Usado apenas em nós folha
    struct NoBPlus *prox;   // Usado apenas em nós folha
} NoBPlus;

// Estrutura para a Árvore B+
typedef struct ArvoreBPlus {
    NoBPlus *raiz;
    int ordem; // A ordem da árvore é armazenada aqui
} ArvoreBPlus;

// Protótipos das Funções
ArvoreBPlus* criar_arvore(int ordem);
void inserir(ArvoreBPlus *arvore, Carro *registro);
Carro* buscar(ArvoreBPlus *arvore, long long renavam);
void liberar_arvore(ArvoreBPlus *arvore);

#endif // B_PLUS_TREE_H