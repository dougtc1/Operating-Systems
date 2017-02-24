#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
// Se crea una linea de procesos.
void main() {
	int status, i,nprocesos;
	pid_t childpid;
	nprocesos = 4;
	for (i = 0; i < nprocesos; ++i) {
		if ((childpid = fork()) < 0) {
		perror("fork:");
		exit(1);
	}
	// Codigo que ejecutaran los hijos

	// Los padres se mueren. Los hijos siguen en el for
	if (childpid > 0) {
		break;
		}
	} //fork
} // main
