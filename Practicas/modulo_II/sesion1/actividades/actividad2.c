/*
actividad2.c

*/
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>  	/* Primitive system data types for abstraction\
			   of implementation-dependent data types.
			   POSIX Standard: 2.6 Primitive System Data Types
			   <sys/types.h>
			*/
#include<sys/stat.h>
#include<fcntl.h>
#include<errno.h>
#include<string.h>
//------------------------------------------
char buf2[80];
char titulo[25];
char salto[2]="\n";
//------------------------------------------
int main(int argc, char *argv[])
{
	int f_IN, f_OUT, leidos;
	char caracter[1];
	int contador = 0;
	int cont_caracteres = 0;
	

	if (argc == 2){
		//abre el fichero 
		f_IN = open(argv[1], O_RDONLY);//O_RDONLY compueba si tiene permiso de lectura		
		if( f_IN < 0) {//control de error
			printf("\nError %d en open",errno);
			perror("\nError en open archivo de entrada");
			exit(EXIT_FAILURE);
		}

	}else{
			//si no se facilita el fichero de entrada 
			// entrada estandar(teclado)
			f_IN =  STDIN_FILENO;
			//ctrl + d  finaliza la entrada
		}

	// creamos el archivo de salida
	f_OUT=open("salida.txt",O_CREAT|O_TRUNC|O_WRONLY,S_IRUSR|S_IWUSR);
	if( f_OUT < 0) {//control de error
		printf("\nError %d en open",errno);
		perror("\nError en open archivo de salida");
		exit(EXIT_FAILURE);
	}

	//dejamos sitio para luego escribir el titulo (modificación)
	if(lseek(f_OUT,25,SEEK_SET) < 0) { //si devuelve -1 se ha producido un error 
		perror("\nError en lseek");
		exit(EXIT_FAILURE);
	}

	//mientras se pueda leer
	while ( (leidos = read(f_IN,caracter,1)) != 0 ) {
		//la lectura se realiza caracter a caracter
		cont_caracteres++;// numero de caracteres leidos		
		if (cont_caracteres % 80 == 0 || cont_caracteres == 1)// comprueba si ha leido 80 
		{
			contador++	;
			
			if(write( f_OUT, salto ,strlen(salto)) < 0) {
				perror("\nError en write (salto)");
				exit(EXIT_FAILURE);
			}

			sprintf(buf2,"Bloque %d\n",contador );			

			if(write( f_OUT,buf2,strlen(buf2)) < 0 ) {
				perror("\nError en write (etiqueta)");
				exit(EXIT_FAILURE);
			}
		}
			//escribe el caracter leido
			if(write( f_OUT,caracter,1) < 0) {
				perror("\nError en write (bloque)");
				exit(EXIT_FAILURE);
			}
	}

	// volvemos al inicio para escribir el titulo
	if(lseek(f_OUT,0,SEEK_SET) < 0) {
		perror("\nError en lseek");
		exit(EXIT_FAILURE);
	}
	//escribimos el titulo
	sprintf(titulo,"\nNumero de Bloques %d\n",contador);

	if(write( f_OUT,titulo,strlen(titulo) )< 0) {
		perror("\nError en write (titulo)");
		exit(EXIT_FAILURE);
	}
	//cerramos los ficheros
		close(f_IN);
		close(f_OUT);

	return EXIT_SUCCESS;
}
