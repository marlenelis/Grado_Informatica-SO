// tarea11.c

#include <stdio.h>
#include <signal.h>

int main()

{
sigset_t new_mask;//mascara de se�ales que deberian bloquearse durante la ejecucion del manejador
/* inicializar la nueva mascara de se�ales */
sigemptyset(&new_mask);//conjto vacio

sigaddset(&new_mask, SIGUSR1);//a�ade una se�al a un conjto de se�ales.

/*esperar a cualquier se�al excepto SIGUSR1 */
sigsuspend(&new_mask);//reemplaza temporalmente la maskara de se�al para el proceso con la dada por el argumento

}