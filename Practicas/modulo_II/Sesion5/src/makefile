# FICHERO Makefile
# USO  make
BIN = bin
INC = include
CXX = gcc
#-------------------------Directorios--------------------------------
# ************ Compilación de módulos ************
$(BIN)/all: $(BIN)/tarea12 $(BIN)/tarea11 $(BIN)/tarea10 $(BIN)/tarea9 $(BIN)/envioSignal $(BIN)/reciboSignal 


$(BIN)/%:%.c
	@$(CXX)   $^  -o $@


# ************ Limpieza ************
clean :
	-rm $(BIN)/*