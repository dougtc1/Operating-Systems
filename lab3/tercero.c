#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
// Se crea un abanico de procesos.
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
	if (childpid == 0) {
		printf("Soy el hijo con pid %ld\n ", getpid());
		printf("Soy la i %d \n",i);
		exit(0);
		}
	} //fork
} // main
