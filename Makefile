SRC_DIR := src
OBJ_DIR := obj
BIN_DIR := build
CC := g++

EXE := $(BIN_DIR)/main
SRC := $(SRC_DIR)/main.cpp
SHAPES:=$(SRC_DIR)/shapes

CPPFLAGS := -Iinclude -MMD -MP -std=c++17
CFLAGS   := -Wall -g
LDFLAGS  := -Llib
LDLIBS   := -lm

.PHONY: all clean


all: point main_prog build vector
	$(CC) -L $(BIN_DIR)/point.so -o $(EXE) $(BIN_DIR)/main.o

main_prog: build
	$(CC) -c $(CFLAGS) -o $(BIN_DIR)/main.o $(SRC)

point: build
	$(CC) -shared $(CFLAGS) -o $(BIN_DIR)/point.so $(SHAPES)/TPoint.hpp

vector: build point
	$(CC) -shared $(CFLAGS) -o $(BIN_DIR)/vector.so $(SHAPES)/TVector.hpp

build:
	mkdir $(BIN_DIR)
clean:
	@$(RM) -rv $(BIN_DIR) $(OBJ_DIR)

-include $(OBJ:.o=.d)