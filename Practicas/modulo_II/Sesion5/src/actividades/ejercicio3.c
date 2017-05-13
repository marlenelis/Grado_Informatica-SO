// ejercicio3.c

#include <stdio.h>
#include <signal.h>
 
int main(){

	sigset_t new_mask;
	/* inicializar la nueva mascara de señales */
	if(sigemptyset(&new_mask) <0  )	{
		perror(" ERROR: sigemptyset");
		return 0;
	}

	if(sigfillset(&new_mask) < 0)//inicializa un conjunto con todas las señales
	{
		perror("ERROR: sigfillset");
		return 0;
	}

	if (sigdelset(&new_mask , SIGUSR1) < 0)//elimina la señal SIGUSR1
	 {
	 	perror("ERROR: sigdelset");
	 	return 0;
	 } 

	// esperar a cualquier señal menos a SIGUSR1
	if (sigsuspend(&new_mask) < 0)
	{
		perror("ERROR: sigsuspend");
	 	return 0;
	}
}