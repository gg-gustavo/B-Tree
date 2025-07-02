# 🌳 Análise de Desempenho de Árvore B+

**Análise de Desempenho de Árvore B+** é um programa de console desenvolvido como trabalho para a disciplina de **Algoritmos III**, programado inteiramente em C. Este projeto me ajudou a aprender bastante sobre a **implementação de estruturas de dados complexas** e a **análise empírica de algoritmos**.

## 🎲 Funcionalidades Principais
- Implementação completa da estrutura de dados Árvore B+ em C, com operações de inserção e busca.
- Lógica de auto-balanceamento através da divisão (`split`) de nós internos e folhas.
- Script em Python para gerar uma massa de 10.000 registros de teste com dados de veículos.
- Sistema de testes automatizado para avaliar a performance da árvore com 100, 1.000 e 10.000 registros.
- Análise de tempo de busca para diferentes ordens da árvore, definidas via linha de comando.
- Gerenciamento de memória para alocar e liberar dinamicamente todos os nós da árvore.


## 🖥️ Uso do Programa
Execute o programa diretamente no terminal:

    ./programa_arvore_b <ordem>

- `<ordem>`: inteiro ≥ 2 que define a ordem da Árvore B+ a ser testada.

> Dica: teste diferentes ordens (ex: 3, 5, 10, 20, 50) e compare os tempos médios de busca para enriquecer seu relatório.

## 🚀 Como Baixar e Executar
### Pré-requisitos
- GCC (ou outro compilador C compatível)
- Python 3 (para o script gerador de dados)
- Make (opcional)

### Instruções
1. Clone o repositório:
       git clone git@github.com:gg-gustavo/B-Tree.git 
2. Compile o código:
       make
3. Gere a massa de dados:
       python3 scripts/gera_dados.py
4. Execute os testes:
       ./programa_arvore_b e passe a ordem <ordem>
5. Limpe arquivos objeto:
       make clean
