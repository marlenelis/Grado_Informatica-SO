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
		printf("\nModo de uso: %s <orden> <\"|\"> <orden>\n", argv[0]);
		exit(EXIT_FAILURE);
	}

		//Declaracion de variables
		char *str_command_1 , *str_command_2;
			char *str_file;//no ses necesario
		//int fd;
			int fd[2];
		//Extraemos las ordenes
		str_command_1 = argv[1];
		str_command_2 = argv[3];

		//Comprobamos el segundo parametro, tiene que ser |
		char *str_simbolo = argv[2];
		pid_t PID;

		if(strcmp(str_simbolo, "|") == 0){	

			pipe(fd);	//crea un pipe
			
			if ( (PID= fork())<0) {
				perror("fork");
				exit(EXIT_FAILURE);
			}

			if(PID == 0){ //ls

				close (fd[0]);		
				close(STDOUT_FILENO);//cierra la salida estándar del hijo	
				//duplicamos el descriptor indicado en el 3er argumento
				if (fcntl(fd[1],F_DUPFD, STDOUT_FILENO)==-1) {
					perror ("fcntl falló");
					exit(EXIT_FAILURE);
				}
				
				 if( (execlp(str_command_1, "", NULL) < 0)) {
					perror("Error en el execlp sort\n");
					exit(EXIT_FAILURE);
				}
				
			}else{//sort				

				close(fd[1]);
				close(STDIN_FILENO); //cierra la entrada estándar del padre
				//duplicamos el descriptor indicado en el 3er argumento
				if (fcntl(fd[0],F_DUPFD, STDIN_FILENO)==-1 ){ 
					perror ("fcntl falló");
					exit(EXIT_FAILURE);
				}

				//Ejecutamos el comando
			    if( (execlp(str_command_2, "", NULL) < 0)) {
					perror("Error en el execlp ls\n");
					exit(EXIT_FAILURE);
				}				
			}		

		}else{					
			printf("el segundo parámetro debe ser \"|\"\n");

		}

		
	return 0;
}
