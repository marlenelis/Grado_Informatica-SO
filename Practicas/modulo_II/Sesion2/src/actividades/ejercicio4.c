/* Recorre la jerarquia de directorios existentes a partir de uno dado como argumento.
	y devuelve la cuenta de todos aquellos archivos regulares que tengan permiso de ejecucion
	para el grupo y para otros. Ademas del numero de archivos encontrados devuelve sus numeros de 
	inodos y la suma total del espacio acupado (con la función nftw )*/
#define _XOPEN_SOURCE 500
#include <ftw.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

// macro condicion
// usuario  grupo   otros
// r w x    r w x   r w x
// 0 0 0    0 0 1   0 0 1   
#define S_IXGRPUSR 011
#define condicion(mode) (((mode) & ~S_IFMT) & 011) == S_IXGRPUSR

int tamanio=0;
int contador=0;
static int
buscar(const char *fpath, const struct stat *atributos,
             int tflag, struct FTW *ftwbuf)
{
        if(S_ISREG(atributos->st_mode))
            if( condicion(atributos->st_mode) ){
                contador++;
                tamanio+= (int)atributos->st_size;
            }

        printf("%-40s %7jd \n",fpath,(intmax_t) atributos->st_ino);
    
    return 0;       
}

int
main(int argc, char *argv[])
{
    int flags = 0;
    char * pathname;
    pathname = argv[1];
    printf("\nLos i-nodos son:\n\n");
   if (nftw((argc < 2) ? "." : pathname, buscar, 20, flags) == -1) {
        perror("nftw");
        exit(EXIT_FAILURE);
    }

    printf("\nExisten %d archivos regulares con permiso x para grupo y otros\n",contador );
    printf("El tamaño total ocupado por dichos archivos es %d bytes\n", tamanio);
    
    exit(EXIT_SUCCESS);
}