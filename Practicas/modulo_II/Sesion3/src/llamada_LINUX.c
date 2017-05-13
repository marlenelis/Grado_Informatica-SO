 
#define _GNU_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>	
#include <sys/wait.h>	
#include <unistd.h>
#include <sys/syscall.h>
#include <errno.h>
#include <sys/utsname.h>
#include <malloc.h>

#include <sched.h>/***/

int variable=3;

int threads(void* p){
	int tid;
	printf("Soy el hijo\n");

	variable++;

	tid = syscall(SYS_gettid);
	printf("PID Y TID del hijo %d %d\n",getpid(),tid);
    printf("en el hijo la variable vale:%d\n",variable );

    sleep(5);
}

int main(){
	void **stack;
	int i, tid;
	if(setvbuf(stdout,NULL,_IONBF,0)) {
        perror("\nError en setvbuf") ;
    }

	stack = (void **)malloc(15000);

	if (!stack)	return -1;

	i = clone(threads, (char*) stack+15000, CLONE_VM|CLONE_FILES|CLONE_FS|CLONE_THREAD|CLONE_SIGHAND,NULL);

	sleep(5);

	if(i==-1) perror("clone");

	tid= syscall(SYS_gettid);

	printf("\nPID Y TID del padre %d %d\n",getpid(),tid);
    printf("en el padre la variable vale:%d\n",variable );

    return 0;
}