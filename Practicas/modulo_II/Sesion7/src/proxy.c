#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <time.h>
#include <signal.h>
#include <errno.h>

#define TAMANIO 1024
#define TAM_FIFOP 256
#define BLOCK_FILE "block_file"
//--------------------------------------------------------------------------
//           	BLOQUEAR
//--------------------------------------------------------------------------
void bloquear(int dbloqueo, int orden) {
	struct flock cerrojo;
	// Inicializamos el cerrojo para bloquear todo el archivo
	cerrojo.l_type= orden;
	cerrojo.l_whence= SEEK_SET;
	cerrojo.l_start= 0;
	cerrojo.l_len = 0;

	//Si vamos a bloquearlo y ya lo esta, entonces el proceso duerme
	if (fcntl(dbloqueo, F_SETLKW, &cerrojo) == -1){
		perror ("Proxy: problemas al bloquear para el impresion");
		exit(1);
	}
}
//--------------------------------------------------------------------------
//					MAIN
//--------------------------------------------------------------------------
int main(int argc, char *argv[]){
	char buffer[TAMANIO];
	int nbytes, dbloqueo;
	FILE *tmp = tmpfile();//función tmpfile incluida en la biblioteca estándar para el archivo temporal que
						  // crea cada proxy, así su eliminación será automática
	char fifoproxy[TAM_FIFOP];

	// Leer bloques de 1024 bytes y escribirlos en archivo temporal.
	while((nbytes = read(STDIN_FILENO, buffer, TAMANIO)) > 0){
		fwrite(buffer, sizeof(char), nbytes, tmp);
	}
	// Abrir archivo "cerrojo".
	if ((dbloqueo = open(BLOCK_FILE, O_RDWR)) == -1)
		printf("Error al abrir block_file\n");
	
	bloquear(dbloqueo, F_WRLCK);// Bloquear cerrojo.

	// Inicio de E.M.
	// Leer fichero temporal hasta fin de archivo.
	while(!feof(tmp)){
		fread(buffer, sizeof(char), TAMANIO, tmp);
		// Escribir en la salida estandar.
		write(STDOUT_FILENO, buffer, TAMANIO);
	}
	// Fin de E.M.	

	bloquear(dbloqueo, F_UNLCK);// Desbloquear cerrojo.
	// Eliminar su fifo antes de terminar.
	sprintf(fifoproxy,"fifo.%d", getpid());
	unlink(fifoproxy);
	exit(0);
}