// tarea11.c

#include <stdio.h>
#include <signal.h>

int main()

{
sigset_t new_mask;//mascara de señales que deberian bloquearse durante la ejecucion del manejador
/* inicializar la nueva mascara de señales */
sigemptyset(&new_mask);//conjto vacio

sigaddset(&new_mask, SIGUSR1);//añade una señal a un conjto de señales.

/*esperar a cualquier señal excepto SIGUSR1 */
sigsuspend(&new_mask);//reemplaza temporalmente la maskara de señal para el proceso con la dada por el argumento

}