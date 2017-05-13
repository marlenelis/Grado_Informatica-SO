/*
	ejercicio3.c
	Recorre la jerarquia de directorios existentes a partir de uno dado como argumento.
	y devuelve la cuenta de todos aquellos archivos regulares que tengan permiso de ejecucion
	para el grupo y para otros. Ademas del numero de archivos encontrados devuelve sus numeros de 
	inodos y la suma total del espacio acupado.
	uso: ./buscar <pathname>
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
// macro condicion
// usuario	grupo	otros
// r w x    r w x   r w x
// 0 0 0	0 0 1   0 0 1   
#define S_IXGRPUSR 011
#define condicion(mode) (((mode) & ~S_IFMT) & 011) == S_IXGRPUSR
//procedimiento para la busqueda
void buscar(DIR *dir, char pathname[] , int *cont, int *tam);

int main(int argc, char *argv[])
{
	char pathname[500];	
	//compueba el numero  de argumentos 
	if (argc == 2)
		strcpy(pathname,argv[1]);
	else //si no se pasa
		strcpy(pathname,"."); //empieza en el directorio actual

	DIR* dir; 
	struct dirent *ent; 
	struct stat atributos;	

	int contador = 0,
		tamanio = 0;

	dir = opendir(pathname);//opendir devuelve un puntero a la estructura de tipo DIR
	if (dir==NULL)
	{
		perror("\nError en opendir");
		exit(EXIT_FAILURE);
	}
	//imprime la cabecera
	printf("\nLos i-nodos son:\n\n");
	//realiza la busqueda 	
	buscar(dir, pathname,&contador,&tamanio);

	printf("\nExisten %d archivos regulares con permiso x para grupo y otros\n",contador );
	printf("El tamaño total ocupado por dichos archivos es %d bytes\n", tamanio);
	return 0;
}/*fin main*/
//----------------------------------------------------------
void buscar(DIR *dir, char pathname[] , int *cont, int *tam)
{
	DIR* dir_ac; 
	struct dirent *ent; 
	struct stat atributos;

	char cadena[500];

	while( (ent=readdir(dir) ) != NULL)
	{
		//ignorar . , ..
		if(strcmp(ent->d_name, ".")!=0 && strcmp(ent->d_name,"..")!=0){
			sprintf(cadena,"%s/%s",pathname,ent->d_name);//concatena el pathname con el archivo para el chmod		
			
			if(stat(cadena,&atributos)< 0){//obtiene los atributos
				perror("\nError en lstat");
				exit(EXIT_FAILURE);
			}

			if(S_ISDIR(atributos.st_mode)){//si es un directorio

				if( (dir_ac=opendir(cadena))== NULL ){//control de error					
					perror("\nError en opendir");
					exit(EXIT_FAILURE);
				}else{
					buscar(dir_ac, cadena, cont, tam);//busqueda recursiva
				}

			}else{
				//---------------------------------------------------
				printf("%-40s %ld\n",cadena, atributos.st_ino);
				//---------------------------------------------------
				if(S_ISREG(atributos.st_mode)){ //si es un archivo regular
				
					if( condicion(atributos.st_mode) ){//comprueba si tiene permisos de ejecucion go	
						(*cont)++;//incrementa el contador de archivos regulares
						(*tam)+=(int)atributos.st_size;// acumula el tamaño de los archivos regulares
					}		
				}
			}		
		}
	}
	closedir(dir);
}