# FICHERO Makefile
# USO  make
BIN = bin
INC = include
CXX = gcc
#-------------------------Directorios--------------------------------
# ************ Compilación de módulos ************
$(BIN)/all: $(BIN)/contador $(BIN)/ejercicio3


$(BIN)/%:%.c
	@$(CXX)   $^  -o $@


# ************ Limpieza ************
clean :
	-rm $(BIN)/*