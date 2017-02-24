#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h> 

void main (int argc, char *argv[]) {

int status;
pid_t childpid;

if ((childpid=fork())==-1) {
    perror("Error al ejecutar fork");
    exit(1);
} else if (childpid==0) {
    if (execvp(argv[1],&argv[1]) < 0) {
	perror("Falla en la ejecucion del comando");
	exit(1);
    }
} else {
    while (childpid != wait(&status))
	if (childpid == -1) break;
	    exit(0);
    }
}
