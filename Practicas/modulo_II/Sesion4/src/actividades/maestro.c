#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
//-----------------------------------------------------------------------
// Función que crea un proceso con fork() y este proceso creado realiza un execlp 
// cuyo resultado es el calulo de los nº primos del intervalo pasado como parámetros.
//-----------------------------------------------------------------------
void encargar_calculo(int descriptor[], char ini_inter_1[], char fin_inter_1[], pid_t ESCLAVO);

int main(int argc,char *argv[]){

	if(argc<3){
		printf("Uso: %s [inicio intervalo] [fin intervalo]\n",argv[0]);
		return(0);
	}
	//cálculo del intervalo que cada uno de los hijos va ha calcular
	int inicio, fin, mitad;

	inicio 	= atoi(argv[1]);
	fin 	= atoi(argv[2]);
	mitad	= ( fin - inicio )/2;

	char ini_inter_1[10], fin_inter_1[10],
		 ini_inter_2[10], fin_inter_2[10];

	//1er intervalo
	sprintf(ini_inter_1, "%d", inicio);
	sprintf(fin_inter_1, "%d", inicio+mitad);	

	//2do intervalo
	sprintf(ini_inter_2, "%d", inicio+(mitad+1));
	sprintf(fin_inter_2, "%d", fin);		 

	//descriptor
	int descriptor[2];

	//vrble para identificar a los hijos;
	pid_t 	ESCLAVO_1,
			ESCLAVO_2;

	//llamada al sistema para crear un pipe
	pipe(descriptor);
	//llamada a la funcion que crea un hijo y le encarga el calculo
	encargar_calculo(descriptor, ini_inter_1, fin_inter_1,ESCLAVO_1);
	
	//llamada al sistema para crear pipe
	pipe(descriptor);

	//llamada a la funcion que crea un hijo y le encarga el calculo
	encargar_calculo(descriptor, ini_inter_2, fin_inter_2,ESCLAVO_2);

return(0);
}
//==================================================================================
void encargar_calculo(int descriptor[], char ini_inter_1[], char fin_inter_1[], pid_t ESCLAVO){
	//vrble para guardar los valores leidos del cauce y
	int valor,
		i=0,j=0;//vrbles extras (printf)

	//crea el hijo (esclavo) para que calcule los números primos 
	//del intervalo pasado como parémetros
	if((ESCLAVO = fork()) <0){
		perror("Error en la creación del 1er esclavo (fork)");
		exit(EXIT_FAILURE);
	}

	//encargar el cálculo de los primos del intervalo
	if(ESCLAVO == 0){
		printf("\nSoy el esclavo con PID <%d> y mi padre con PID <%d>\n",getpid(), getppid() );
		printf("Intervalo [%s-%s]\n\n",ini_inter_1,fin_inter_1 );
		
		close(descriptor[0]);//cierra el descriptor usado para lectura
		dup2(descriptor[1], STDOUT_FILENO); // duplica 

		if((execlp("./bin/esclavo","esclavo", ini_inter_1, fin_inter_1, NULL)) < 0){
			perror("Error en execpl ");
			exit(EXIT_FAILURE);
		}
	}else {// el padre lee los valores depositados 
		close(descriptor[1]);//cierra el descriptor de escritura

		while( read(descriptor[0],&valor,sizeof(int)) > 0){ //usa el descriptor de lectura
			printf("%-9d",valor );

			i++;if(i==10){printf("\n"); i=0;}//salto de linea cada 10 valores leidos

		}//fin while
		close(descriptor[0]);//cierra el descriptor usado para lectura
		printf("\n");
	}
}