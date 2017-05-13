/* ejercicio3.c
 Indica qué tipo de jerarquías de procesos se generan mediante la ejecución de cada
uno de los siguientes fragmentos de código. Comprueba tu solución implementando un código
para generar 20 procesos en cada caso, en donde cada proceso imprima su PID y el del padre,
PPID.
*/

#include <sys/types.h>	
#include <sys/wait.h>	
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]){

	pid_t id_proceso;
	pid_t id_padre; 

	int childpid;
	int count = 2;//20

	if(setvbuf(stdout,NULL,_IONBF,0)) {
        perror("\nError en setvbuf") ;
    }

	/* Jerarquia de proceso tipo 1 */
	for (int i = 0; i < count; ++i)
	{
		if ((childpid = fork()) ==-1){
			fprintf(stderr, "Could not create child %d: %s\n",i,strerror(errno));
			exit(-1);
		}
		if (childpid){// el padre sale del for despues de la creacion 
			break;
		}else{ // el hijo continua en el for 
			id_proceso = getpid();	//pid del proceso que invoca
			id_padre = getppid();	//pid del proceso padre del proceso que invoca
			
			printf("\ttipo 1: PID: %-5d PPID: %-5d \n",id_proceso, id_padre);
		}
	}
	/**/
	wait(0);
	/* Jerarquia de proceso tipo 2 */
	for (int i = 0; i < count; ++i)	{
		if ((childpid = fork()) ==-1)		{
			fprintf(stderr, "Could not create child %d: %s\n",i,strerror(errno));
			exit(-1);
		}
		if (!childpid){//el hijo sale del for
			break;
		}
		else{
			id_proceso = getpid();	//pid del proceso que invoca
			id_padre = getppid();	//pid del proceso padre del proceso que invoca
			
			printf("tipo 2: PID: %-5d PPID: %-5d \n",id_proceso, id_padre);
		}
	}
	wait(0);
	/**/
	return 0;
}