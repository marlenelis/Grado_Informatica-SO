/*
tarea2.c
Trabajo con llamadas al sistema del Sistema de Archivos ''POSIX 2.10 compliant''
*/

#include<unistd.h>  
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h> 
#include<sys/stat.h>
#include<stdio.h>
#include<errno.h>
#include<string.h>
//--------------------------------------
#define S_ISREG2(mode) (((mode) & S_IFMT) == S_IFREG)
#define S_ISREG3(mode) (mode & S_IFMT)
#define S_ISREG4(mode) S_ISREG(mode)
#define S_ISREG5(mode) (((mode) & 00170000) == 0100000)
//--------------------------------------
int main(int argc, char *argv[])
{
int i;
struct stat atributos;
char tipoArchivo[10];

if(argc<2) {
	printf("\nSintaxis de ejecucion: actividad4 [<nombre_archivo>]+\n\n");
	exit(-1);
}
for(i=1;i<argc;i++) {
	printf("%s: ", argv[i]);
	if(lstat(argv[i],&atributos) < 0) {
		printf("\nError al intentar acceder a los atributos de %s",argv[i]);
		perror("\nError en lstat");
	}
	else {
		if(S_ISREG(atributos.st_mode)){ strcpy(tipoArchivo,"Regular");
		printf("\n\tS_ISREG %s\n",tipoArchivo);	
		}
		if(S_ISREG2(atributos.st_mode)) { strcpy(tipoArchivo,"Regular");
		printf("\n\tS_ISREG2 %s\n",tipoArchivo);	
		}

		if(S_ISREG3(atributos.st_mode)) { strcpy(tipoArchivo,"Regular");
		printf("\n\tS_ISREG3 %s\n",tipoArchivo);	
		}

		if(S_ISREG4(atributos.st_mode)) { strcpy(tipoArchivo,"Regular");
		printf("\n\tS_ISREG4 %s\n",tipoArchivo);	
		}

		if(S_ISREG5(atributos.st_mode)) { strcpy(tipoArchivo,"Regular");
		printf("\n\tS_ISREG5 %s\n",tipoArchivo);	
		}
	}
}

return 0;
}
