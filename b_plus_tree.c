// Arquivo: b_plus_tree.c
// Descrição: Implementação completa das funções da Árvore B+.

#include "b_plus_tree.h"
#include <string.h>

// --- Funções de Criação e Liberação ---

NoBPlus* criar_no(int ordem, bool folha) {
    NoBPlus *no = (NoBPlus*)malloc(sizeof(NoBPlus));
    no->folha = folha;
    no->num_chaves = 0;
    no->prox = NULL;
    no->chaves = (long long*)malloc(sizeof(long long) * (2 * ordem - 1));
    no->filhos = (NoBPlus**)malloc(sizeof(NoBPlus*) * (2 * ordem));
    no->registros = (Carro**)malloc(sizeof(Carro*) * (2 * ordem - 1));
    return no;
}

ArvoreBPlus* criar_arvore(int ordem) {
    ArvoreBPlus *arvore = (ArvoreBPlus*)malloc(sizeof(ArvoreBPlus));
    arvore->ordem = ordem;
    arvore->raiz = criar_no(ordem, true);
    return arvore;
}

void liberar_no(NoBPlus *no) {
    if (no == NULL) return;
    if (!no->folha) {
        for (int i = 0; i <= no->num_chaves; i++) {
            liberar_no(no->filhos[i]);
        }
    }
    free(no->chaves);
    free(no->filhos);
    free(no->registros);
    free(no);
}

void liberar_arvore(ArvoreBPlus *arvore) {
    if (arvore != NULL) {
        liberar_no(arvore->raiz);
        free(arvore);
    }
}

// --- Função de Busca ---

Carro* buscar(ArvoreBPlus *arvore, long long renavam) {
    if (arvore == NULL || arvore->raiz == NULL) return NULL;

    NoBPlus *cursor = arvore->raiz;
    while (!cursor->folha) {
        int i = 0;
        while (i < cursor->num_chaves && renavam >= cursor->chaves[i]) {
            i++;
        }
        cursor = cursor->filhos[i];
    }

    for (int i = 0; i < cursor->num_chaves; i++) {
        if (cursor->chaves[i] == renavam) {
            return cursor->registros[i];
        }
    }
    return NULL;
}

// --- Funções de Inserção (com Split) ---

void dividir_filho(NoBPlus *pai, int indice, NoBPlus *filho, int ordem) {
    NoBPlus *novo_filho = criar_no(ordem, filho->folha);
    novo_filho->num_chaves = ordem - 1;

    for (int j = 0; j < ordem - 1; j++) {
        novo_filho->chaves[j] = filho->chaves[j + ordem];
    }
    if (!filho->folha) {
        for (int j = 0; j < ordem; j++) {
            novo_filho->filhos[j] = filho->filhos[j + ordem];
        }
    } else {
        for (int j = 0; j < ordem - 1; j++) {
            novo_filho->registros[j] = filho->registros[j + ordem];
        }
        novo_filho->prox = filho->prox;
        filho->prox = novo_filho;
    }

    filho->num_chaves = ordem - 1;

    for (int j = pai->num_chaves; j > indice; j--) {
        pai->filhos[j + 1] = pai->filhos[j];
    }
    pai->filhos[indice + 1] = novo_filho;

    for (int j = pai->num_chaves - 1; j >= indice; j--) {
        pai->chaves[j + 1] = pai->chaves[j];
    }
    pai->chaves[indice] = filho->chaves[ordem - 1];
    pai->num_chaves++;
}

void inserir_em_no_nao_cheio(NoBPlus *no, Carro *registro, int ordem) {
    long long chave_nova = registro->renavam;
    int i = no->num_chaves - 1;

    if (no->folha) {
        while (i >= 0 && chave_nova < no->chaves[i]) {
            no->chaves[i + 1] = no->chaves[i];
            no->registros[i + 1] = no->registros[i];
            i--;
        }
        no->chaves[i + 1] = chave_nova;
        no->registros[i + 1] = registro;
        no->num_chaves++;
    } else {
        while (i >= 0 && chave_nova < no->chaves[i]) {
            i--;
        }
        i++;
        if (no->filhos[i]->num_chaves == 2 * ordem - 1) {
            dividir_filho(no, i, no->filhos[i], ordem);
            if (chave_nova > no->chaves[i]) {
                i++;
            }
        }
        inserir_em_no_nao_cheio(no->filhos[i], registro, ordem);
    }
}

void inserir(ArvoreBPlus *arvore, Carro *registro) {
    NoBPlus *raiz = arvore->raiz;
    int ordem = arvore->ordem;

    if (raiz->num_chaves == 2 * ordem - 1) {
        NoBPlus *nova_raiz = criar_no(ordem, false);
        arvore->raiz = nova_raiz;
        nova_raiz->filhos[0] = raiz;
        dividir_filho(nova_raiz, 0, raiz, ordem);
        inserir_em_no_nao_cheio(nova_raiz, registro, ordem);
    } else {
        inserir_em_no_nao_cheio(raiz, registro, ordem);
    }
}