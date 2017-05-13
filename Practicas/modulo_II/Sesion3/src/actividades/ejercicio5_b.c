#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/wait.h>
	
int main(int argc, char *argv[])
{
    int childpid[5], id_wait;
   // pid_t PID;
    int estado, count = 5, i;

    if(setvbuf(stdout,NULL,_IONBF,0)) {
        perror("\nError en setvbuf") ;
    }
    // creación de los hijos, y presentacion de los hijos
    for(i=0; i<5; i++)
    {
        if( (childpid[i]=fork())<0) {
            perror("\nError en el fork" );
            exit(-1);
        }
            
        if( (childpid[i])==0) {  //proceso hijo ejecutando el programa                
            printf("Soy el hijo [%d] con PID <%d>\n",i+1, getpid());   
            exit(0);                    
        }
    }
    
    //padre espera a los hijos impares

    for(i=0; i<5; i ++){  //proceso padre ejecutando el programa
        if((i+1)%2!=0){
            id_wait = waitpid(childpid[i],&estado,0);
             
            printf("\nAcaba de finalizar mi hijo  con PID <%d> \n", id_wait);
            printf("Solo me quedan %d hijos vivos\n", --count);
        }
    }
    //padre espera a los hijos pares

    for(i=0; i<5; i ++){  //proceso padre ejecutando el programa
        if((i+1)%2==0){
            id_wait = waitpid(childpid[i],&estado,0);
            printf("\nAcaba de finalizar mi hijo  con PID <%d> \n", id_wait);
            printf("Solo me quedan %d hijos vivos\n", --count);
        }
    }
    return 0;
}
