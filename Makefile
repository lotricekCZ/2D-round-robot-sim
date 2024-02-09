SRC_DIR := src
OBJ_DIR := obj
BIN_DIR := bin
CC := g++

EXE := $(BIN_DIR)/main
SRC := $(SRC_DIR)/main.cpp
SHAPES:=$(SRC_DIR)/shapes
# OBJ := $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

CPPFLAGS := -Iinclude -MMD -MP -std=c++17
CFLAGS   := -Wall -g
LDFLAGS  := -Llib
LDLIBS   := -lm

.PHONY: all clean


all: point main_prog
	$(CC) -o main TPoint.o main.o

main_prog:
	$(CC) -c $(CFLAGS) $(SRC)

point:
	$(CC) -c $(CFLAGS) $(SHAPES)/point/TPoint.hpp


clean:
	@$(RM) -rv $(BIN_DIR) $(OBJ_DIR)

-include $(OBJ:.o=.d)