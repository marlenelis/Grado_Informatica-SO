#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>//strcmp
#include <errno.h>
int main(int argc, char *argv[]) {
	//Comprobamos si se le ha pasado un pathname y unos permisos como parámetros
	if(argc != 4) 
	{
		//Si no se le han pasado los parámetros correctos, mensaje de ayuda		
		printf("\nModo de uso: %s <comando> <simbolo> <archivo>\n", argv[0]);
		printf("Simbolos: \"<\" o \">\" debe pasarse entre comillas.\n\n");
		exit(EXIT_FAILURE);
	} 
		//Declaracion de variables
		char *str_command;
		char *str_file;
		int fd, rdir;

		//Extraemos el comando
		str_command = argv[1];
		//Extraemos el fichero
		str_file = argv[3];
		//Comprobamos el segundo parametro, tiene que ser < o >
		char *str_simbolo = argv[2];

		if (strcmp(str_simbolo, "<") == 0) {
			//abre el fichero para lectura
			fd = open (str_file, O_RDONLY);
			if(fd <0){
				perror("open falló");
				exit(EXIT_FAILURE);
			}
			rdir = STDIN_FILENO;
			//cierra el descriptor de entrada
			close(STDIN_FILENO);		

		} else if (strcmp(str_simbolo, ">") == 0) {
			//abre el fichero para escritura, si no existe lo crea 		
			fd = open (str_file, O_CREAT|O_WRONLY, S_IRUSR|S_IWUSR);
			if(fd <0){
				perror("open falló");
				exit(EXIT_FAILURE);
			}
			// guardamos el tipo de redirecionamiento
			rdir = STDOUT_FILENO;
			//cierra  el descriptor de salida
			close (STDOUT_FILENO);			

		} else  {
		//Si no se le han pasado el parametro correcto, mensaje de ayuda
		  printf("Modo de uso: %s [comando] [opciones: \"<\" o \">\" ] [archivo]\n\n", argv[0]);
		  exit(EXIT_FAILURE);
		}
		//duplicamos fd, el descriptor duplicado depende del valor de rdir 
		if (fcntl(fd,F_DUPFD, rdir)==-1) {
			perror ("fcntl falló");
			exit(EXIT_FAILURE);
		}
		//Ejecutamos el comando
	    if( (execlp(str_command, "", NULL) < 0)) {
			perror("Error en el execlp\n");
			exit(EXIT_FAILURE);
		}
		//Cerramos el fichero
		close(fd);
		return 0;	
}
