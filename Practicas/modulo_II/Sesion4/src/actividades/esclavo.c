/*esclavo*/
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <math.h> //incluir -lm al compilar (sqrt)

int main(int argc,char*argv[]){

    int inicio = atoi(argv[1]); 
    int fin = atoi(argv[2]);
    int divisor,i;
    int cont;    
    /*Calcula los numeros primos que hay en el intervalo desde inicio hasta fin*/
    for( i=inicio;i<fin;i++){ 
        cont=0;
        for(divisor=2;divisor <= sqrt((double)i); divisor++)
            if(i%divisor==0)//si es divisible 
                cont++;
        if(cont==0) 
            write(STDOUT_FILENO, &i, sizeof(int));//escribe en la salida standar
    }
}