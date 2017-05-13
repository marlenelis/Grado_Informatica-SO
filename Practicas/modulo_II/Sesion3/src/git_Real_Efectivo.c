// obtiene información sobre el proceso que las ejecuta.
// grupo principal del usuario
// ver tambien en /etc/passwd

#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
void main(void)
{
	printf("Identificador de  usuario: %d\n", getuid());
	printf("Identificador de  usuario efectivo: %d\n", geteuid());
	printf("Identificador de  grupo: %d\n", getgid());
	printf("Identificador de  grupo efectivo: %d\n", getegid());
}