# FICHERO Makefile
# USO  make
BIN = bin
INC = include
CXX = gcc
#-------------------------Directorios--------------------------------
# ************ Compilación de módulos ************
$(BIN)/all: $(BIN)/servidor $(BIN)/clientes $(BIN)/proxy 



$(BIN)/%:%.c
	@$(CXX)   $^  -o $@
# ejecutar

sr:
	./$(BIN)/servidor $(BIN)/fifo 
cl:
	./$(BIN)/clientes $(BIN)/fifo 1

# ************ Limpieza ************
clean :
	-rm $(BIN)/*
rclean:
	rm -rf *.o *.*~ servidor clientes proxy fifo* *~  block_file blockfile
## ---------------------------------------------------------------------