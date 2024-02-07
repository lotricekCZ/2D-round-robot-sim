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


main.obj:
	$(CC) $(CFLAGS) main.o $(SRC)

point.obj:
	$(CC) $(CFLAGS) point.o $(SHAPES)/point/point.cpp

all: point.obj main.obj
	g++ main -o main.o point.o


clean:
	@$(RM) -rv $(BIN_DIR) $(OBJ_DIR)

-include $(OBJ:.o=.d)