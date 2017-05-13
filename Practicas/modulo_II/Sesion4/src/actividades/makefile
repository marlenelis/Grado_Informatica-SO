# FICHERO Makefile
# USO  make
BIN = bin
CXX = gcc

# ************ Compilación de módulos ************
$(BIN)/all: $(BIN)/maestro  $(BIN)/esclavo

$(BIN)/%:%.c
	@$(CXX)   $^  -o $@ -lm

es: 
	./$(BIN)/esclavo  100 1500
ma:
	./$(BIN)/maestro 1000  1500 
ma2:
	./$(BIN)/maestro 10  20 

# ************ Limpieza ************
clean :
	-rm $(BIN)/*

