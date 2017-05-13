/* ejercicio4.c
 Implementa un programa que lance cinco procesos hijo.
 Cada uno de ellos se 	identificará en la salida estándar,
 mostrando un mensaje del tipo:
 	 Soy el hijo PID. 
 El proceso padre simplemente tendrá que esperar 
 la finalización de todos sus hijos y cada vez que 	detecte 
 la finalización de uno de sus hijos escribirá en la salida estándar
 un mensaje del tipo:
		Acaba de finalizar mi hijo con <PID>
		Sólo me quedan <NUM_HIJOS> hijos vivos
*/
#include <sys/types.h>	
#include <sys/wait.h>	
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

int main(int argc, char *argv[]){

	pid_t 	id_proceso,	id_wait; 

	int childpid, estado, n_proc= 5,
		status, count = 5;

	if(setvbuf(stdout,NULL,_IONBF,0)) {	
		perror("\nError en setvbuf");
	}
// creacion de los hijos
	for (int i = 0; i < n_proc; ++i)
	{		
		if ((childpid = fork()) ==-1){//creacion
			perror("\nError en el fork");
			exit(-1);
		}	
		if (!childpid)/* hijo*/
			break;
	}	
 //presentación del hijo
	if (!childpid)/* hijo*/
	{
		id_proceso = getpid();	//pid del proceso que invoca			
		printf("Soy el hijo: PID: %-5d \n",id_proceso);					
		exit(EXIT_SUCCESS);//finaliza el hijo
	}	
	sleep(1);
//espera del padre q que terminen sus hijos
	for (int i = 0; i < n_proc; ++i)
	{
		if(childpid){ /*padre*/	
			id_wait = wait(0);//espera			

			printf("\nAcaba de finalizar mi hijo con PID: %-5d\n",id_wait);
			printf("Sólo me quedan %d hijos vivos\n", --count);
		}		
	}
	return 0;
}