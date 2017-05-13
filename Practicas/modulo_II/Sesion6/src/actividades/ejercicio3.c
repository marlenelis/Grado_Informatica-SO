#include <unistd.h>//sleep
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
int main(int argc, char *argv[]) {
	//Declaracion de variables
	struct flock cerrojo;
	int fd, i;

	if(argc != 2) {
		//Si no se le han pasado los parámetros correctos, mensaje de ayuda
		printf("Modo de uso: %s <archivo>\n\n", argv[0]);
		exit(1);
	} else {

		//Extraemos el nombre del archivo a usar (por comodidad)
		char *str_file = argv[1];
		//Abrimos el archivo
		if ((fd = open(str_file, O_RDWR)) == -1 ){
			perror("Fallo al abrir el archivo");
			exit(EXIT_FAILURE);
		}
		//creación de la estructura del cerrojo
		cerrojo.l_type 	= F_WRLCK;//cerrojo para escritura
		cerrojo.l_whence= SEEK_SET;//desde el origen del archivo
		//Bloquearemos el archivo entero
		cerrojo.l_start	= 0;//situandose en el byte 0
		cerrojo.l_len	= 0; //bloquea hasta el final del archivo

		//Intentamos un bloqueo de escritura del archivo
		printf ("Intentando bloquear %s\n", str_file);

		//Si el cerrojo falla, mostramos un mensaje
		//al utilizar F_SETLKW El proceso se bloquea, si otro proceso esta usando el archivo
		if (fcntl (fd, F_SETLKW, &cerrojo) == -1){ 
			printf(" error en el bloqueo ");				
			if(errno == EDEADLK) printf(" ha dado un EDEADLK %d\n",errno);	
			printf("\n");
			exit(EXIT_FAILURE);			
		}  
		 
			//Ahora el bloqueo tiene exito y podemos procesar el archivo
		printf ("Procesando el archivo %s\n", str_file);
		//sleep para que de tiempo de lanzar otra vez el programa		
		sleep(20);				
		//Una vez finalizado el trabajo, desbloqueamos el archivo
		cerrojo.l_type	= F_UNLCK;
		cerrojo.l_whence= SEEK_SET;
		cerrojo.l_start	= 0;
		cerrojo.l_len	= 0;

		if (fcntl (fd, F_SETLKW, &cerrojo) == -1) {
			perror ("Error al desbloquear el archivo");
		}		
		return 0;
	}
}