#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdlib.h>
#include <time.h>
#include <signal.h>
#include <errno.h>


#define longnombre 50
#define MAX_CLIENTS 100
#define BLOCK_FILE "block_file"
#define PERMISO 0777
//------------------------------------------------------------------
//				MI MANEJADOR 
//------------------------------------------------------------------
static void miManejador(int sigNum){
	pid_t pid;
	int estado;
	// Capturar pid del hijo y eliminar su archivo fifo asociado.
	pid = wait(&estado);
}
//------------------------------------------------------------------
//				MAIN
//------------------------------------------------------------------
int main(int argc, char *argv[]){

	int fde, fds, fdc, tmp_cli;
	char nombrefifoe[longnombre];
	char nombrefifos[longnombre];
	char fifoproxy[longnombre];
	int leidos, proxypid;
	pid_t pid;
	//Comprobar el uso correcto del programa
	if(argc != 2) {
		printf("Uso: Servidor <nombre_fifo>");
		exit(EXIT_FAILURE);
	}
	// Manejador de señal SIGCHLD.
	signal(SIGCHLD, miManejador);
	// Componer nombre del archivo fifo
	sprintf(nombrefifos,"%ss",argv[1]);
	sprintf(nombrefifoe,"%se",argv[1]);
	//borramos los archivos fifo por si existieran previamente
	unlink(nombrefifoe);
	unlink(nombrefifos);
	
	umask(0);
	// Crear archivos fifo
	if(mkfifo(nombrefifoe,0777) < 0){
		perror("Error en mkfifo 1\n");
		exit(EXIT_FAILURE);
	}

	if(mkfifo(nombrefifos,PERMISO) <0){
		perror("Error en mkfifo 2\n");
		exit(EXIT_FAILURE);
	}

//-------------------------------------------------------------
	//Intentar abrir los archivos fifo.
	if((fds=open(nombrefifos,O_RDWR)) < 0){
		perror("\nNo se pudo abrir el archivo fifo del servidor.");
		exit(EXIT_FAILURE);
	}
	if((fde=open(nombrefifoe,O_RDWR)) < 0){
		perror("\nNo se pudo abrir el archivo fifo del cliente.");
		exit(EXIT_FAILURE);
	}
	// Creación del archivo bloqueo que se utilizará como cerrojo.
	

	if((fdc=open(BLOCK_FILE, O_CREAT, PERMISO))<0){
	printf("\nError al crear el archivo de bloqueo.");
	exit(EXIT_FAILURE);
	}
	// Lanzar procesos mientras se reciba algo del archivo fifo cliente.
	while((leidos=read(fde, &tmp_cli, sizeof(int))) != 0){
		pid = fork();
		if (pid == 0){ //Proceso hijo.
			// Obtener pid del nuevo proceso
			proxypid = getpid();
			// Construir cadena "proxy.getpid()" para archivo fifo.
			sprintf(fifoproxy,"fifo.%d", proxypid);
			// Crear archivo fifo.
			umask(0);
			//crea fifo
			mkfifo(fifoproxy,PERMISO);
			// Escribe el pid del proxy en fifos
			write(fds, &proxypid, sizeof(int));
			// Abrir fifo para lectura.
			int fifo = open(fifoproxy,O_RDONLY);
			// Redirigir entrada standar -> archivofifo
			dup2(fifo, STDIN_FILENO);
			if(execlp("./bin/proxy", "proxy", NULL) <0){
				perror("\nError: en execlp.");
				exit(EXIT_FAILURE);
			}
		}
	}
	return 0;
}