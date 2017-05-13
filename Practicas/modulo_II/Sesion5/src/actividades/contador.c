/* 
 * File:   contador.c
 * Author: Marlene E. Vásquez
 *
 * Created on 12 de diciembre de 2016, 9:59
 /*
 * Escribe un programa en C llamado contador, tal que cada vez que reciba una
 * señal que se pueda manejar, muestre por pantalla la señal y el número de veces que se ha
 * recibido ese tipo de señal, y un mensaje inicial indicando las señales que no puede manejar.  
 * 
 * compilación: gcc contador.c -o contador
 */
#include <sys/types.h>
#include <stdio.h>
#include <signal.h>
#include <errno.h> 
#include <unistd.h>
#include <stdlib.h>

const static int TAM = 31;
static int contador[31];
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
static void contador_handler(int nSignal){
        contador[nSignal]++;
        printf("\nLa señal %d se ha realizado %d veces.\n", nSignal, contador[nSignal]);   
}
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
int main(int argc, char** argv) {
    
    struct sigaction sig_USR;
    
    if(setvbuf(stdout,NULL,_IONBF,0))
        perror("\nError en setvbuf");   

    //inicializacion de la estructura ,asociacion de la funcion del manejador
    sig_USR.sa_handler = contador_handler;

    //inicializamos el conjunto de señales
   sigemptyset(&sig_USR.sa_mask);

    sig_USR.sa_flags = 0;
    
    int i;
    for(i=1 ;i < TAM ;i++)
        contador[i]=0;
       
    for(i=1; i<TAM; i++){
        if(sigaction(i, &sig_USR, NULL) < 0){
            printf("\nNo se puede manejar la señal  %d\n",i);
        }
    }
    printf("\nEsperando el envio de señales...\n");
    while(1);//no termina el programa   
}
