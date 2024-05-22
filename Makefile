BIN_DIR := build
DOC_DIR := docs
EXE := simulator

.PHONY: all clean run documentation


all: $(BIN_DIR)
	cd $(BIN_DIR) && \
	cmake .. && \
	make -j`nproc`

run:
	./$(BIN_DIR)/$(EXE)


$(BIN_DIR):
	mkdir -p $(BIN_DIR)

$(DOC_DIR):
	mkdir -p $(DOC_DIR)


clean:
	@$(RM) -rv $(BIN_DIR) $(DOC_DIR)

documentation: $(DOC_DIR)
	doxygen Doxyfile

-include $(OBJ:.o=.d)
