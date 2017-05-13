# FICHERO Makefile
# USO  make
BIN = bin
INC = include
CXX = gcc

# ************ Compilación de módulos ************
$(BIN)/all: $(BIN)/consumidorFIFO $(BIN)/productorFIFO	$(BIN)/tarea6 $(BIN)/tarea7 $(BIN)/tarea8 

$(BIN)/%:%.c
	@$(CXX)   $^  -o $@
#***************ejecución****************
con:
	./$(BIN)/consumidorFIFO &
prod: 
	./$(BIN)/productorFIFO "hola" 

# ************ Limpieza ************
clean :
	-rm $(BIN)/*

