# Nom de l'exécutable attendu par le shell
EXEC = wildwater

# Compilateur
CC = gcc

# Options de compilation
CFLAGS = -Wall -Wextra -g

# Fichiers sources
SRC = mainhisto.c histo.c fonction_base.c

# Fichiers objets
OBJ = $(SRC:.c=.o)

# Règle par défaut
all: $(EXEC)

# Création de l'exécutable
$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) -o $(EXEC) $(OBJ)

# Compilation des fichiers .c en .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Nettoyage
clean:
	rm -f $(OBJ) $(EXEC)
