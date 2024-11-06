# CC = gcc
# CFLAGS = -Iinclude
# OBJ = obj/main.o
# TARGET = bin/main

# all: $(TARGET)

# $(TARGET): $(OBJ)
# 	$(CC) -o $(TARGET) $(OBJ)

# obj/%.o: src/%.c
# 	$(CC) $(CFLAGS) -c -o $@ $<

# clean:
# 	rm -f $(OBJ) $(TARGET)
# Variabili
CC = gcc
CFLAGS = -Iinclude -Wall -Wextra -g -lncurses
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin
TARGET = $(BIN_DIR)/app

# Lista dei file sorgenti e degli oggetti corrispondenti
SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

# Regola principale
all: $(TARGET)

# Regola per creare l'eseguibile
$(TARGET): $(OBJS) | $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

# Regola per creare gli oggetti
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Creazione delle cartelle se non esistono
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# Pulizia dei file compilati
clean:
	rm -rf $(OBJ_DIR)/*.o $(TARGET)

# Pulizia completa (compresi binari)
distclean: clean
	rm -rf $(BIN_DIR)

.PHONY: all clean distclean
