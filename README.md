# 🌳 Análise de Desempenho de Árvore B+

**Análise de Desempenho de Árvore B+** é um programa de console desenvolvido como trabalho para a disciplina de **Algoritmos III**, programado inteiramente em C. Este projeto me ajudou a aprender bastante sobre a **implementação de estruturas de dados complexas** e a **análise empírica de algoritmos**.

## 🎲 Funcionalidades Principais
- Implementação completa da estrutura de dados Árvore B+ em C, com operações de inserção e busca.
- Lógica de auto-balanceamento através da divisão (`split`) de nós internos e folhas.
- Script em Python para gerar uma massa de 10.000 registros de teste com dados de veículos.
- Sistema de testes automatizado para avaliar a performance da árvore com 100, 1.000 e 10.000 registros.
- Análise de tempo de busca para diferentes ordens da árvore, definidas via linha de comando.
- Gerenciamento de memória para alocar e liberar dinamicamente todos os nós da árvore.


**Compilando o projeto com `make` (ou `gcc`):**
```bash
$ make
gcc -Wall -g -c main.c
gcc -Wall -g -c b_plus_tree.c
gcc -Wall -g -o programa_arvore_b main.o b_plus_tree.o