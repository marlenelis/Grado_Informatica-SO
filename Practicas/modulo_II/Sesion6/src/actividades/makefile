
# FICHERO Makefile
# USO  make
BIN = bin
INC = include
CXX = gcc
#-------------------------Directorios--------------------------------
# ************ Compilación de módulos ************
$(BIN)/all: $(BIN)/ejercicio1 $(BIN)/ejercicio2  $(BIN)/ejercicio3 $(BIN)/ejercicio5


$(BIN)/%:%.c
	@$(CXX)   $^  -o $@


# ************ Limpieza ************
clean :
	-rm $(BIN)/*