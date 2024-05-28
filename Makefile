BIN_DIR := build
DOC_DIR := docs
EXE := simulator

.PHONY: all clean run documentation test


all: $(BIN_DIR)
	cd $(BIN_DIR) && \
	cmake .. && \
	make -j`nproc`

run: all
	./$(BIN_DIR)/$(EXE)


$(BIN_DIR):
	mkdir -p $(BIN_DIR)

$(DOC_DIR):
	mkdir -p $(DOC_DIR)

test:
	cd $(BIN_DIR) && \
	make test

clean:
	@$(RM) -rv $(BIN_DIR) $(DOC_DIR)

doxygen: $(DOC_DIR)
	doxygen Doxyfile

-include $(OBJ:.o=.d)
