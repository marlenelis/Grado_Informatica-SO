/* ejercicio 7. 
Escribe un programa que acepte como argumentos el nombre de un programa,
sus argumentos si los tiene, y opcionalmente la cadena “bg”.
Nuesto programa deberá 	ejecutar el programa pasado como primer argumento en foreground 
si no se especifica la 	cadena “bg” y en background en caso contrario. 
Si el programa tiene argumentos hay que ejecutarlo con éstos.

*/

#include <sys/types.h>	
#include <sys/wait.h>	
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>	

int main(int argc, char *argv[]){

	int arg;
	bool backg;
	char paramts[100];
	char *prog;
	if(argc < 2){
		printf("Modo de uso: %s <programa> [opciones] [bg]\n\n", argv[0]);
		exit(EXIT_SUCCESS);
	}
	
	arg = argc;// control de numero de argumentos
	prog = argv[1];// obtenemos la prog a ejecutar
	backg = strcmp(argv[argc-1],"bg") ? false : true , arg-- ; //compara y decrementa

 	int i;
	for (i = 2; i < arg; i++)
	{// obtenemos los parametros
		strcat(paramts, argv[i]);
		strcat(paramts, " ");	
	}

	sleep(1);
	int childpid;		

		if (backg)//en background
		{	/*creacion  un hijo*/
			if ((childpid = fork()) ==-1){
				perror("\nError en el fork");
				exit(EXIT_FAILURE);
			}

			if(!childpid){ 	 // el hijo ejecuta
				if( (execl(prog,paramts,paramts, NULL)<0) ) { 
					perror("\nError en el excl");
					exit(EXIT_FAILURE);		
				}		
			}else{//el padre realiza exit

				exit(EXIT_SUCCESS);
			}			
		}else{//no background
				if( (execl(prog,paramts,paramts, NULL)<0) ) { 
					perror("\nError en el excl");
					exit(EXIT_FAILURE);		
				}
			}
	return 0;
}