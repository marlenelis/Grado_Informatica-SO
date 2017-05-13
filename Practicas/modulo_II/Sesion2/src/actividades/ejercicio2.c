/*
	ejercicio2.c
*/

#include <sys/types.h>	//Primitive system data types for abstraction of implementation-dependent data types.
						//POSIX Standard: 2.6 Primitive System Data Types <sys/types.h>
#include <unistd.h>		//POSIX Standard: 2.10 Symbolic Constants         <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>		//Needed for open 
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

#include <dirent.h> // manejo de directorios
#include <string.h>

int main(int argc, char *argv[])
{
	//compueba el numero  de aragumentos 
	if (argc != 3)
	{
		printf("Uso: %s  <directorio> <permiso> \n",argv[0]);
		exit(-1);
	}

	DIR* dir; 
	struct dirent *ent; 
	struct stat atributos;

	char cadena[100];
	char * pathname;
	pathname = argv[1];
	int nuevo_permiso;
	nuevo_permiso = strtol(argv[2],0,8);//cambia a octal

	dir = opendir(pathname);//opendir devuelve un puntero a la estructura de tipo DIR
	if (dir==NULL)
	{
		perror("\nError en opendir");
		exit(EXIT_FAILURE);
	}
	//imprime la cabecera
	printf("\narchivo: \t\t\tpermisos_antiguos  \tpermisos_nuevos/errno\n\n");
	//lectura del directorio hasta que devuelva NULL(llega al final o se ha producido un error)
	while( (ent=readdir(dir) ) != NULL)
	{
		sprintf(cadena,"%s/%s",pathname,ent->d_name);//concatena el pathname (chmod)		
		if(stat(cadena,&atributos)<0){//obtiene los permisos		
			perror("Error: stat");
			exit(EXIT_FAILURE);
		}
		if(S_ISREG(atributos.st_mode)){ //si es un archivo regular

			printf("%-35s %-25o ",cadena, atributos.st_mode);
			if( (chmod(cadena, nuevo_permiso)) < 0){//cambia los peromisos	
				printf("Error: %s \n",strerror(errno) );// muestra el error 
			}else{
				lstat(cadena,&atributos);
				printf(" %o \n", atributos.st_mode);//muestra los nuevos permisos
			}			
		}
	}
	closedir(dir);
	return 0;
}
