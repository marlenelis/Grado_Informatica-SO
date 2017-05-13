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
MODIFICACION: 
 el proceso padre espera primero a los hijos creados en orden impar (1o,3o,5o) y
 después a los hijos pares (2o y 4o)

*/

#include <sys/types.h>	
#include <sys/wait.h>	
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

int main(int argc, char *argv[]){

	pid_t 	id_proceso,
			id_wait_; 

	int childpid[5], 
		estado,
		n_proc= 5,
		count = 5;


	if(setvbuf(stdout,NULL,_IONBF,0)) {
        perror("\nError en setvbuf") ;
    }

	for (int i = 0; i < n_proc; ++i)
	{
		if ((childpid[i] = fork()) ==-1){//creacion
			perror("\nError en el fork");
			exit(-1);
		}	
		if (!childpid[i])// hijo
		{
			id_proceso = getpid();	//pid del proceso que invoca
			if((i+1)%2==0)	printf("Soy el hijo [%d] \tPID: %-2d \n",i+1,id_proceso);
			else printf("Soy el hijo [%d] \tPID: %-2d \n",i+1,id_proceso);			
			exit(EXIT_SUCCESS);
		}	
	}
	sleep(1);
/*IMPAR*/
	
		for (int i = 0; i < n_proc; ++i)
		{
			if(childpid[i]){ //padre

				if((i+1)%2!=0){ 				

					do{ 
						id_wait_ = waitpid(childpid[i],&estado,0);

						if (id_wait_ == -1) {
		                       perror("waitpid");
		                       exit(EXIT_FAILURE);
		                   } else                  
								count--;

		            } while (!WIFEXITED(estado));//mientras el estado != exit

					printf("\nAcaba de finalizar mi hijo [%d] con PID: %-2d\n",i+1,childpid[i]);
					printf("Sólo me quedan %d hijos vivos\n", count);					
				}
			}
		}
		/*PAR*/
		for (int i = 0; i < n_proc; ++i)
		{
			if((i+1)%2==0){ 			

				do{ 
					id_wait_ = waitpid(childpid[i],&estado,0);

					if (id_wait_ == -1) {
	                       perror("waitpid");
	                       exit(EXIT_FAILURE);
	                   } else                  
							count--;

	            } while (!WIFEXITED(estado));//mientras el estado != exit

				printf("\nAcaba de finalizar mi hijo [%d] con PID: %-2d\n",i+1,childpid[i]);
				printf("Sólo me quedan %d hijos vivos\n", count);					
			}
		}


	return 0;
}