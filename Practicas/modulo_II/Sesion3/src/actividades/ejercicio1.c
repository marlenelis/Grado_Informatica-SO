/* ejercicio1.c
 Este programa debe crea un proceso hijo que se encarga de comprobar
 si el numero pasado como argumento es un número par o impar e informa
 al usuario con un mensaje que se envia por la salida estándar.
 A su vez, el proceso padre comprueba si dicho número es divisible por 4,
 e informa si lo es o no usando la salida estándar.
*/

#include <sys/types.h>	
#include <sys/wait.h>	
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
	pid_t pid;
	int estado, numero;

	if(argc!=2){
		printf("Uso: %s <numero> \n",argv[0] );
		exit(0);		
	}
	
	numero = atoi(argv[1]);

	if( (pid=fork())<0) {
		perror("\nError en el fork");
		exit(-1);
	}
	else
		if(pid==0) {  //proceso hijo
			 //comprueba si es par
			if(numero%2 == 0) printf("Hijo: %d es par.\n",numero);
			else printf("Hijo: %d es impar.\n",numero);
			
		}else{// proceso padre
			wait(0);//espera al hijo
			//comprueba si es divisible por 4
			double res = numero%4;
			if( res == 0) printf("Padre: %d es divisible por 4.\n",numero);
			else printf("Padre: %d no es divisible por 4.\n",numero);
		}
	exit(0);
}