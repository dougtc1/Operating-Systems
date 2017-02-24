#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(void) {
    int status;
    pid_t childpid;

    if ((childpid=fork())==-1) {
	perror("Error al ejecutar el fork");
	exit(1);
    } else if (childpid==0) {
	if (execl("/bin/ls","ls","-l",NULL) < 0){
	    perror("Falla en la ejecucion de exec");
	    exit(1);
	}
    } else {
	wait();
    }
}


