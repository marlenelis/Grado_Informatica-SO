#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
int main(int argc, char *argv[]) {
	//Comprobamos si se le ha pasado los parámetros correctos
	if(argc != 3) {
		//Si no se le han pasado los parámetros correctos, mensaje de ayuda
		printf("Modo de uso: %s <programa> <origen> <destino>\n\n", argv[0]);
		exit(EXIT_FAILURE);
	} else {
		//Declaracion de variables
         struct stat sb;
		char *str_orig = argv[1];
		char *str_dest = argv[2];

		int fd_orig, fd_dest;
		char *mem_orig, *mem_dest;
		int filesize;
		//Abrimos el fichero de origen
		fd_orig = open(str_orig, O_RDONLY);
		if (fd_orig == -1) {
			perror("Fallo al abrir el archivo de origen\n");
			exit(EXIT_FAILURE);
		}
		//Obtenemos su stat, para comprobar si es regular y obtener su tamaño
        if (fstat (fd_orig, &sb) == -1) {
                printf("Error al hacer stat en el fichero de origen\n");
                exit(EXIT_FAILURE);
        }
        if (!S_ISREG (sb.st_mode)) {
                printf ("El fichero de origen no es un archivo regular\n");
                exit(EXIT_FAILURE);
        }
        //Guardamos el tamaño en una variable 
        filesize = sb.st_size;
        //Creamos el archivo de destino
        umask(0);
		fd_dest = open(str_dest, O_RDWR|O_CREAT, S_IRWXU);
		if (fd_dest == -1) {
			perror("Fallo al crear el archivo de salida");
			exit(EXIT_FAILURE);
		}  
		//Asignamos el espacion en el fichero de destino
		ftruncate(fd_dest, filesize);
		//Creamos el mapa de memoria del fichero de origen
		mem_orig = (char *) mmap(0, filesize, PROT_READ, MAP_SHARED, fd_orig, 0);
		if(mem_orig == MAP_FAILED) {
			perror("Fallo mapeando el archivo de entrada");
			exit(EXIT_FAILURE);
		}
		//Creamos el mapa de memoria del fichero de destino
		mem_dest=(char *) mmap(0,filesize, PROT_WRITE, MAP_SHARED, fd_dest, 0);
		if(mem_dest == MAP_FAILED) {			
			perror("Fallo mapeando el archivo de salida");
			exit(EXIT_FAILURE);
		}		
		//Copiamos un mapa de memoria en otro
		memcpy(mem_dest, mem_orig, filesize);
 		//Liberamos los mapas de memoria
		munmap(mem_orig, filesize);
		munmap(mem_dest, filesize);
 		//Cerramos los descriptores de fichero
		close(fd_orig);
		close(fd_dest);
		//Terminamos la ejecución del programa
		return 0;
	}
}
