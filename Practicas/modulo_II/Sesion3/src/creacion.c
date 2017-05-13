#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
void main(void)
{
pid_t id_proceso;
pid_t id_padre;
id_proceso = getpid();	//pid del proceso que invoca
id_padre = getppid();	//pid del proceso padre del proceso que invoca
printf("Identificador de proceso: %d\n", id_proceso);
printf("Identificador del proceso padre: %d\n", id_padre);
}