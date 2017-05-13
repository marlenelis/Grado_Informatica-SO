// tarea9.c 

#include <stdio.h>
#include <signal.h>

int main()
{
	struct sigaction sa;
	sa.sa_handler = SIG_IGN; // ignora la señal
	sigemptyset(&sa.sa_mask); //inicializa a vacio el conjto de señales return (0,-1)

	//Reiniciar las funciones que hayan sido interrumpidas por un manejador 
	sa.sa_flags = SA_RESTART; 

	if (sigaction(SIGINT, &sa, NULL) == -1)//establece la accion que realizara un proceso com respuesta a la recpcion de la señal
	 	printf("error en el manejador");
	while(1);
}
/*
sa_handler especifica la acción que se va a asociar con la señal signum pudiendo ser:
- SIG_DFL para la acción predeterminada,
- SIG_IGN para ignorar la señal
- o un puntero a una función manejadora para la señal
*/

//SIGINT  => interrupcion procedente del teclado CTRL+C