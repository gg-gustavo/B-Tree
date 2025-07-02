# Nome do compilador que vamos usar
CC=gcc
# Flags de compilação: -Wall mostra todos os avisos, -g ajuda na depuração
CFLAGS=-Wall -g
# Nome do nosso programa executável
EXECUTAVEL=programa_arvore_b

# Regra padrão: o que acontece quando você digita "make"
all: $(EXECUTAVEL)

# Regra para criar o executável final
$(EXECUTAVEL): main.o b_plus_tree.o
	$(CC) $(CFLAGS) -o $(EXECUTAVEL) main.o b_plus_tree.o

# Regra para compilar o main.c em um "objeto" main.o
main.o: main.c b_plus_tree.h
	$(CC) $(CFLAGS) -c main.c

# Regra para compilar o b_plus_tree.c em um "objeto" b_plus_tree.o
b_plus_tree.o: b_plus_tree.c b_plus_tree.h
	$(CC) $(CFLAGS) -c b_plus_tree.c

# Regra para limpar os arquivos gerados (o executável e os .o)
clean:
	rm -f $(EXECUTAVEL) *.o