# Makefile pour le projet BlackBox

CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -g
TARGET = blackbox
OBJS = main.o memory.o physics.o files.o

# Règle par défaut
all: $(TARGET)

# Compilation de l'exécutable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) -lm

# Compilation des fichiers objets
main.o: main.c blackbox.h
	$(CC) $(CFLAGS) -c main.c

memory.o: memory.c blackbox.h
	$(CC) $(CFLAGS) -c memory.c

physics.o: physics.c blackbox.h
	$(CC) $(CFLAGS) -c physics.c

files.o: files.c blackbox.h
	$(CC) $(CFLAGS) -c files.c

# Nettoyage
clean:
	rm -f $(OBJS) $(TARGET) crash.bin

# Exécution
run: $(TARGET)
	./$(TARGET)

# Test automatique
test: $(TARGET)
	@echo "Test de compilation réussi!"
	@./$(TARGET)

.PHONY: all clean run test