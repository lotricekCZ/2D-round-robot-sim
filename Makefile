SRC_DIR := src
OBJ_DIR := obj
BIN_DIR := build
DOC_DIR := docs
CC := g++

EXE := $(BIN_DIR)/simulator
SRC := $(SRC_DIR)/main.cpp
SHAPES := $(SRC_DIR)/shapes

CPPFLAGS := -Iinclude -MMD -MP -std=c++17
CFLAGS := -Wall -g
LDFLAGS := -Llib
LDLIBS := -lm

.PHONY: all clean run documentation


all: $(EXE)

run: all
	@LD_LIBRARY_PATH=$(BIN_DIR) ./$(EXE)

$(EXE): $(OBJ_DIR)/main.o $(BIN_DIR)/libpoint.so $(BIN_DIR)/libvector.so | $(BIN_DIR)
	$(CC) -L $(BIN_DIR) -o $@ $^ $(LDLIBS) -I$(BIN_DIR) -lpoint -lvector


$(BIN_DIR)/libpoint.so: $(OBJ_DIR)/TPoint.o | $(BIN_DIR)
	$(CC) -shared -o $@ $<

$(BIN_DIR)/libvector.so: $(OBJ_DIR)/TVector.o | $(BIN_DIR)
	$(CC) -shared -o $@ $<

$(BIN_DIR)/libline.so: $(OBJ_DIR)/TLine.o | $(BIN_DIR)
	$(CC) -shared -o $@ $<

$(OBJ_DIR)/main.o: $(SRC) | $(OBJ_DIR)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/TPoint.o: $(SHAPES)/TPoint.cpp | $(OBJ_DIR)
	$(CC) $(CPPFLAGS) $(CFLAGS) -fPIC -c $< -o $@

$(OBJ_DIR)/TVector.o: $(SHAPES)/TVector.cpp | $(OBJ_DIR)
	$(CC) $(CPPFLAGS) $(CFLAGS) -fPIC -c $< -o $@

$(OBJ_DIR)/TLine.o: $(SHAPES)/TLine.cpp | $(OBJ_DIR)
	$(CC) $(CPPFLAGS) $(CFLAGS) -fPIC -c $< -o $@


$(BIN_DIR):
	mkdir -p $(BIN_DIR)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)


$(DOC_DIR):
	mkdir -p $(DOC_DIR)

clean:
	@$(RM) -rv $(BIN_DIR) $(OBJ_DIR)

documentation: $(DOC_DIR)
	

-include $(OBJ:.o=.d)
